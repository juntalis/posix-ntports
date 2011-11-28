
#include "which.h"
#ifdef _DEBUG
#include <conio.h>
#endif

STATIC TCHAR strEnvPath[] = ENV_PATH;
STATIC TCHAR strEnvPathExt[] = ENV_PATHEXT;
STATIC OPTS optsWhich;

STATIC VOID ExitUsage(LPTSTR whichExe, INT exitCode)
{
	LPCTSTR strUsage =
		T("Usage: %s [-h] [-x] [-n] [-a] program\r\n"
		"\r\n"
		"Options:\r\n"
		"\t"	"-h\t"	"Print this help text.\r\n"
		"\t"	"-x\t"	"Do not use PATHEXT in search.\r\n"
		"\t"	"-n\t"	"Do not print newline.\r\n"
	//	"\t"	"-a\t"	"Show all matches. (Default: Show first match)\r\n"
		"\r\n");
	info(strUsage, whichExe);
	exit(exitCode);
}

STATIC INT Which(LPTSTR strExec)
{
	TCHAR strBuffer[MAX_PATH];
	INT iResult = EXIT_FAILURE;
	LPTSTR envPathExt;
	SIZE_T szSearch; LPTSTR strSearch;
	LPTSTR strExt;

	if((envPathExt = tgetenv(strEnvPathExt)) == NULL) {
		error("Error: Getting PATHEXT environmental variable returned NULL. Check PATHEXT and try again.\r\n");
		exit(EXIT_FAILURE);
	}

	strExt = ENV_SPLIT(envPathExt);
	if(strExt == NULL) {
		error1("Error: Could not split PATHEXT by delimiter \";\". Check your environment variables and try again.\r\n\r\nPATHEXT: %s\r\n", envPathExt);
		exit(EXIT_FAILURE);
	}
	
	searchenv(strExec, strEnvPath, strBuffer, MAX_PATH);
	if((optsWhich.usePathExt == TRUE) && (*strBuffer == T('\0'))) {
		do {
			// Search for file in PATH environment variable:
			szSearch = slen(strExec) + slen(strExt) + 1;
			if(ALLOC(strSearch, LPTSTR, TCHAR, szSearch) == NULL) {
				error("Error: Could not allocate memory for .\r\n");
				exit(EXIT_FAILURE);
			}
			tsprintf(strSearch, szSearch, T("%s%s\0"), (LPCTSTR)strExec, (LPCTSTR)strExt);
			searchenv(strSearch, strEnvPath, strBuffer, MAX_PATH);
			GlobalFree(strSearch);
			if(*strBuffer != T('\0'))
				break;
		} while(NEXT_ENV(strExt) != NULL);
	}
	if(*strBuffer != T('\0'))
		iResult = info(T("%s"), strBuffer) == -1;

	if(optsWhich.printNewLine && !iResult)
		info(T("\r\n"));
	
	return iResult;
}

// Entry-point of the executable.
INT Main(INT argc, LPTSTR argv[])
{
	LPTSTR strTarget = NULL;
	INT iResult = EXIT_FAILURE;
	INT i = 1;

	// Set default args.
	optsWhich.printNewLine = TRUE;
	optsWhich.usePathExt = TRUE;
	optsWhich.showAll = FALSE;
	

	// Parse args.
	if(argc > 1) {
		for(i = 1; i < argc; i++) {
			if(IS_OPT(i,argv)) {
				switch(OPT(i)) {
					case OPT_HELP1:
					case OPT_HELP2:
						ExitUsage(WHICH_EXE, EXIT_SUCCESS);
						break;
					case OPT_NEWLINE:
						optsWhich.printNewLine = FALSE;
						break;
					case OPT_PATHEXT:
						optsWhich.usePathExt = FALSE;
						break;
					case OPT_SHOWALL:
						optsWhich.showAll = TRUE;
						info(T("This option is not implemented quite yet. Sorry.\r\n"));
						exit(0);
						break;
					default:
						error1("Error: Unrecognized option %s\r\n\r\n", argv[i]);
						ExitUsage(WHICH_EXE, EXIT_FAILURE);
						break;
				}
			} else {
				if(strTarget != NULL) {
					error1("Error: Target program/file already specified and at this time, this program does not support searching for multiple programs. "
					"If the filename contains a space, remember to surround it with \"s.\r\n\r\n", argv[i]);
					ExitUsage(WHICH_EXE, EXIT_FAILURE);
				}
				strTarget = argv[i];
			}
		}
	} else {
		ExitUsage(WHICH_EXE, EXIT_SUCCESS);
	}
	
	if(strTarget == NULL) {
		error("Error: Target program not specified.\r\n\r\n");
		ExitUsage(WHICH_EXE, EXIT_FAILURE);
	}

	if(!SUCCESS(iResult = Which(strTarget)))
		error3("%s: no %s in (%s)\r\n", WHICH_EXE, strTarget, tgetenv(ENV_PATH));

	#ifdef _DEBUG
	info(T("Press any key to continue.\r\n"));
	_gettch();
	#endif
	return iResult;
}

