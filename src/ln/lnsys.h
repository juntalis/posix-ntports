#ifndef _POSIX_PATH_H_
#define _POSIX_PATH_H_
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define CYGWIN_DLL "cygwin1.dll"
#define MSYS_DLL "msys-1.0.dll"

#define CYGWIN_INIT "cygwin_dll_init"
#define MSYS_INIT "msys_dll_init"

#define CYGWIN_DETACH "cygwin_detach_dll"
#define MSYS_DETACH "msys_detach_dll"

#define SYMLINK_FUNCT "symlink"

#define FUNC_WIN32_LIST			"cygwin32_posix_to_win32_path_list"
#define FUNC_WIN32_LIST_SIZE	"cygwin32_posix_to_win32_path_list_buf_size"
#define FUNC_POSIX_LIST			"cygwin32_win32_to_posix_path_list"
#define FUNC_POSIX_LIST_SIZE	"cygwin32_win32_to_posix_path_list_buf_size"

#define FUNC_WIN32_PATH			"cygwin_conv_to_win32_path"
#define FUNC_WIN32_FULL_PATH	"cygwin_conv_to_full_win32_path"
#define FUNC_POSIX_PATH			"cygwin_conv_to_posix_path"
#define FUNC_POSIX_FULL_PATH	"cygwin_conv_to_full_posix_path"

// void cygwin_dll_init()
typedef void (*pInit)();
#define SetInitFunc(h,m) GetFunction(h,pInit,m,initFunc)

// int cygwin_conv_to_win32_path (const char *, char *)
typedef int (*pConvPathFunc)(const char *, char *);
#define SetConvPathFunc(h,m,f) GetFunction(h,pConvPathFunc,m,f)

// int symlink(const char *name1, const char *name2)
typedef int (*pSymLink)(const char *, const char *);
#define SetSymLinkFunc(h,m) GetFunction(h,pSymLink,m,SYMLINK_FUNCT)

// int cygwin_posix_to_win32_path_list_buf_size (const char *)
typedef int (*pPathBufferSizeFunc)(const char *);
#define SetPathBufferSizeFunc(h,m,f) GetFunction(h,pPathBufferSizeFunc,m,f)

typedef struct {
	HMODULE hInstance;
	pInit Init;
	pConvPathFunc ToWin32List;
	pPathBufferSizeFunc ToWin32ListBuffSize;
	pConvPathFunc ToPosixList;
	pPathBufferSizeFunc ToPosixListBuffSize;
	pConvPathFunc ToWin32Path;
	pConvPathFunc ToWin32FullPath;
	pConvPathFunc ToPosixPath;
	pConvPathFunc ToPosixFullPath;
	pSymLink SymLink;
	BOOL isLoaded;
} PosixSys, *pPosixSys;

#define DEFAULT_POSIXSYS {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, FALSE}

typedef enum {
	TARGET_SYMLINK = 0,
	TARGET_HARDLINK,
	TARGET_JUNCTION,
	TARGET_CYGLINK
} TargetType;

BOOL IsJunctionSupported(pPathElement path);
BOOL IsHardLinkSupported(pPathElement path);
BOOL IsSymLinkSupported(pPathElement path);
BOOL IsCygLinkSupported();
BOOL ResolvePath(pPathElement path);
BOOL HardLink(pPathElement source, pPathElement link);
BOOL SymbolicLink(pPathElement source, pPathElement link);
BOOL Junction(pPathElement source, pPathElement link);
BOOL CygLink(pPathElement source, pPathElement link);

#ifdef __cplusplus
}
#endif

#endif /* _POSIX_PATH_H_ */