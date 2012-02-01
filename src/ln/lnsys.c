#include <globals.h>
#include "ln.h"
#include "lnsys.h"
#include <io.h>

/**
  DLL: Kernel32.dll
  BOOLEAN WINAPI CreateSymbolicLinkA(LPSTR lpSymlinkFileName, LPSTR lpTargetFileName, DWORD dwFlags)
*/
BOOLEAN (__stdcall* pCreateSymbolicLink)(LPSTR, LPSTR, DWORD);
/**
  DLL: Kernel32.dll
  BOOL WINAPI CreateHardLinkA(LPCSTR lpFileName, LPCSTR lpExistingFileName, LPSECURITY_ATTRIBUTES lpSecurityAttributes)
*/
BOOL (__stdcall* pCreateHardLink)(LPCSTR,LPCSTR,LPSECURITY_ATTRIBUTES);

/**
 DLL: cygwin1.dll/msys-1.0.dll
 See lnsys.h
*/
static PosixSys sys = DEFAULT_POSIXSYS;

/**
 HMODULE for our eventual LoadLibrary call to Kernel32.dll
*/
static HMODULE hKernel = NULL;

typedef enum {
	SYS_WIN32 = 0,
	SYS_CYG,
	SYS_MSYS
} WinSysType;

static WinSysType FindSysType()
{
	char* msys = NULL;
	char* term = getenv("TERM");
	if(getenv("SHLVL") && term && (_stricmp(term, "cygwin") == 0)) {
		msys = getenv("MSYSTEM");
		return (msys && (_stricmp(msys, "MINGW32") == 0)) ? SYS_MSYS : SYS_CYG;
	} else {
		return SYS_WIN32;
	}
}

static void LoadWin32Sys(TargetType target)
{
	if(target == TARGET_SYMLINK || target == TARGET_HARDLINK) {
		GetLibraryA(hKernel, "Kernel32.dll");
		if(target == TARGET_SYMLINK) {
			GetFunction(hKernel, BOOLEAN (__stdcall*)(LPSTR,LPSTR,DWORD), pCreateSymbolicLink, "CreateSymbolicLinkA");
		} else {
			GetFunction(hKernel, BOOL (__stdcall*)(LPCSTR,LPCSTR,LPSECURITY_ATTRIBUTES), pCreateHardLink, "CreateHardLinkA");
		}
	}
}

static void LoadPosixSys(WinSysType sysType)
{
	char *dllName, *initFunc;
	
	// Leaving this here for the time-being in case
	// the STATUS_ACCESS_VIOLATION bug when calling msys_init_dll gets fixed.
	// See:
	// https://sourceforge.net/mailarchive/forum.php?thread_name=CA%2Bsc5mk_9K%2BMQ6ubSgdvDOFb5B0rYKdzR%2BEwh4M_c5wtmNwnTw%40mail.gmail.com&forum_name=mingw-users
	if(sysType == SYS_MSYS) {
		dllName =  MSYS_DLL;
		initFunc = MSYS_INIT;
	} else {
		dllName = CYGWIN_DLL;
		initFunc = CYGWIN_INIT;
	}
	
	GetLibrary(sys.hInstance, dllName);
	SetInitFunc(sys.hInstance, sys.Init);
	
	SetConvPathFunc(sys.hInstance, sys.ToWin32List, FUNC_WIN32_LIST);
	SetPathBufferSizeFunc(sys.hInstance, sys.ToWin32ListBuffSize, FUNC_WIN32_LIST_SIZE);
	
	SetConvPathFunc(sys.hInstance, sys.ToPosixList, FUNC_POSIX_LIST);
	SetPathBufferSizeFunc(sys.hInstance, sys.ToPosixListBuffSize, FUNC_POSIX_LIST_SIZE);
	
	SetConvPathFunc(sys.hInstance, sys.ToWin32Path, FUNC_WIN32_PATH);
	SetConvPathFunc(sys.hInstance, sys.ToWin32FullPath, FUNC_WIN32_FULL_PATH);
	
	SetConvPathFunc(sys.hInstance, sys.ToPosixPath, FUNC_POSIX_PATH);
	SetConvPathFunc(sys.hInstance, sys.ToPosixFullPath, FUNC_POSIX_FULL_PATH);

	// This is only being used on cygwin anyways, so I might as well put this here.
	SetSymLinkFunc(sys.hInstance, sys.SymLink);
	sys.Init();
	sys.isLoaded = TRUE;
}

static BOOL ResolveCygwinPath(const char* path, char* buffer)
{
	if(!sys.isLoaded) LoadPosixSys(SYS_CYG);
	return sys.ToWin32Path(path, buffer) != -1;
}

static BOOL Win32ToCygwinPath(const char* path, char* buffer)
{
	if(!sys.isLoaded) LoadPosixSys(SYS_CYG);
	return sys.ToPosixPath(path, buffer) != -1;
}

static BOOL ResolveMsysPath(const char* path, char* buffer)
{
	int result = FALSE;
	// Just realized, MSYS automatically converts paths when it detects
	// that the target app is not a MSYS app. So this should be fine.
	fatalA("Don't know how you got here, but you're on your own.");
	#if 0
	#define MSYSPATH_EXE ".\\msyspath.exe"
	FILE *pPipe; char* pCmd;
	UINT cpOld = GetConsoleOutputCP();
	// strlen(\"MSYSPATH_EXE\" -w \"path\"\0)
	size_t pathLen = strlen(MSYSPATH_EXE) + strlen(path) + 7;
	if((pCmd = (char*)malloc(sizeof(char)*pathLen)) == NULL) return FALSE;
	zstr(pCmd, pathLen);
	SetConsoleOutputCP(1252);
	// Run msyspath -w path
	if( (sprintf(pCmd,"%s -w \"%s\"", MSYSPATH_EXE, path) != -1)
		&& ((pPipe = _popen(pCmd, "rt")) != NULL ) ) {
		printf("%s\n", pCmd);
		while(fgets(buffer, MAX_PATH, pPipe));
		if (feof( pPipe)) {
			_pclose( pPipe );
			result = TRUE;
		}
	}
	free(pCmd);
	SetConsoleOutputCP(cpOld);
	#endif
	return result;
}

static BOOL ResolveMixedPath(const char* path, char* buffer)
{
	int i;
	strcpy(buffer, path);
	for(i = 0; buffer[i]; i++)
		if(buffer[i] == '/')
			buffer[i] = '\\';
	return TRUE;
}

static BOOL ResolvePosixPath(const char* path, char* buffer)
{
	WinSysType sysType = FindSysType();
	if(sysType == SYS_WIN32)
		fatalA("Cannot resolve a POSIX-style path if we are not currently in a POSIX-style environment. (Cygwin/MSYS)\n"
			"Path specified: %s", path);
	return (sysType == SYS_CYG) ?
		ResolveCygwinPath(path, buffer) :
		ResolveMixedPath(path, buffer);
}

static BOOL AbsWin32Path(const char* path, char* buffer)
{
	char fileDir[MAX_PATH+1] = "\0"; size_t bufflen;
	char* tempBuffer; BOOL result;
	if(_access(path, 0) == -1) {
		if(!GetCurrentDirectory(MAX_PATH+1, fileDir))
			return FALSE;
		bufflen = strlen(fileDir) + strlen(path) + 2;
		tempBuffer = (char*)malloc(sizeof(char) * bufflen);
		zstr(tempBuffer, bufflen);
		sprintf(tempBuffer, "%s\\%s", fileDir, path);
		result = GetFullPathNameA(tempBuffer, MAX_PATH+1, buffer, NULL) != 0;
		free(tempBuffer);
		return result;
	} else {
		return GetFullPathNameA(path, MAX_PATH+1, buffer, NULL) != 0;
	}
	
}

static BOOL OsAtLeast(DWORD dwMajorVersion)
{
	DWORD dwVersion = 0; 
	DWORD dwCurrentMajor = 0;
	DWORD dwMinorVersion = 0; 
	DWORD dwBuild = 0;

	dwVersion = GetVersion();

	// Get the Windows version.

	dwCurrentMajor = (DWORD)(LOBYTE(LOWORD(dwVersion)));
	dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));
	return (dwCurrentMajor >= dwMajorVersion ? TRUE : FALSE);
}

static BOOL IsNTFS(char* path, BOOL UDF_OK)
{
	char buffer[MAX_PATH+1] = "\0";
	char fileSystem[MAX_PATH+1] = "\0";
	strncpy(buffer, path, 1);
	buffer[1] = ':'; buffer[2] = '\\';
	GetVolumeInformationA( buffer, NULL, 0, NULL, NULL, NULL, fileSystem, MAX_PATH+1);
	if(_stricmp((const char*)fileSystem, "NTFS")) {
		printf("fileSystem: %s\n", fileSystem);
		if(!UDF_OK) {
			return FALSE;
		} else if(_stricmp((const char*)fileSystem, "UDF")) {
			return FALSE;
		}
	}
	return TRUE;
}

BOOL IsJunctionSupported(pPathElement path)
{
	char* buffer = NULL; BOOL cleanUp = FALSE;
	BOOL result = FALSE;
	if((path->isFolder == FALSE) || (OsAtLeast(5) == FALSE))
		return FALSE;
	if(path->isRelative == TRUE) {
		buffer = (char*)malloc(sizeof(char) * (MAX_PATH+1));
		zstr(buffer, MAX_PATH + 1);
		if(!AbsWin32Path((const char*)path->resolved, buffer)) {
			free(buffer);
			return FALSE;
		}
		cleanUp = TRUE;
	} else {
		buffer = path->resolved;
	}
	if(IsNTFS(buffer, FALSE))
		result = TRUE;
	if(cleanUp)
		free(buffer);
	return result;
}

BOOL IsHardLinkSupported(pPathElement path)
{
	char* buffer = NULL; BOOL cleanUp = FALSE;
	BOOL result = FALSE;
	if((path->isFolder == TRUE) || (OsAtLeast(5) == FALSE))
		return FALSE;
	
	if(path->isRelative == TRUE) {
		buffer = (char*)malloc(sizeof(char) * (MAX_PATH+1));
		zstr(buffer, MAX_PATH + 1);
		if(!AbsWin32Path((const char*)path->resolved, buffer)) {
			free(buffer);
			return FALSE;
		}
		cleanUp = TRUE;
	} else {
		buffer = path->resolved;
	}
	if(IsNTFS(buffer, TRUE))
		result = TRUE;
	if(cleanUp)
		free(buffer);
	return result;
}

BOOL IsSymLinkSupported(pPathElement path)
{
	char* buffer = NULL; BOOL cleanUp = FALSE;
	BOOL result = FALSE;
	if(OsAtLeast(6) == FALSE)
		return FALSE;
	if(path->isRelative == TRUE) {
		buffer = (char*)malloc(sizeof(char) * (MAX_PATH+1));
		if(!AbsWin32Path((const char*)path->resolved, buffer)) {
			free(buffer);
			return FALSE;
		}
		cleanUp = TRUE;
	} else {
		buffer = path->resolved;
	}
	if(IsNTFS(buffer, FALSE))
		result = TRUE;
	if(cleanUp)
		free(buffer);
	return result;
}

BOOL IsCygLinkSupported()
{
	return FindSysType() == SYS_CYG;
}

BOOL ResolvePath(pPathElement path)
{
	BOOL result;
	switch(path->pathType) {
		case PATH_WIN32:
			strcpy(path->resolved, (const char*)path->original);
			result = TRUE;
			break;
		case PATH_POSIX:
			result = ResolvePosixPath((const char*)path->original, path->resolved);
			break;
		case PATH_MIXED:
			result = ResolveMixedPath((const char*)path->original, path->resolved);
			break;
	}
	return result;
}

BOOL CygLink(pPathElement source, pPathElement link)
{
	// MAX_PATH + strlen('/cygdrive') + 1
	char buffer_source[MAX_PATH + 10] = "\0";
	char buffer_link[MAX_PATH + 10] = "\0";
	if(!Win32ToCygwinPath((const char*)source->resolved, buffer_source))
		return FALSE;
	if(!Win32ToCygwinPath((const char*)link->resolved, buffer_link))
		return FALSE;
	return sys.SymLink(buffer_source, buffer_link) != -1;
}


BOOL Junction(pPathElement source, pPathElement link)
{
	return FALSE;
}

BOOL HardLink(pPathElement source, pPathElement link)
{
	if(hKernel == NULL) LoadWin32Sys(TARGET_HARDLINK);
	return pCreateHardLink((const char*)link->resolved, (const char*)source->resolved, NULL) != 0;
}

BOOL SymbolicLink(pPathElement source, pPathElement link)
{
	DWORD dwFlags = 0x0;
	if(hKernel == NULL) LoadWin32Sys(TARGET_SYMLINK);
	if(source->isFolder) dwFlags = 0x1;
	return pCreateSymbolicLink(link->resolved, source->resolved, dwFlags) != 0;
}