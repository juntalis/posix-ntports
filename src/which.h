#pragma once

#include "targetver.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

/* TChar Macros */
// Undefine any existing macros that would conflict with ours.
#ifdef searchenv
#undef searchenv
#endif

#define searchenv _tsearchenv_s
#define tgetenv _tgetenv
#define slen _tcslen
#define sclen _tcsclen
#define tsprintf _stprintf_s

/* Macros for my own benefit */
#ifndef MAX_PATH
#define MAX_PATH _MAX_PATH
#endif

#ifndef T
#define T TEXT
#endif

// Function annotations
#define STATIC static
#define INLINE inline

// Output macros
#define info _tprintf_s
#define error(M) _ftprintf_s(stdout, T(M))
#define error1(M, A1) _ftprintf_s(stdout, T(M), A1)
#define error2(M, A1, A2) _ftprintf_s(stdout, T(M), A1, A2)
#define error3(M, A1, A2, A3) _ftprintf_s(stdout, T(M), A1, A2, A3)
#define error4(M, A1, A2, A3, A4) _ftprintf_s(stdout, T(M), A1, A2, A3, A4)

// Utility macros
#define SUCCESS(x) ((x) == EXIT_SUCCESS)
#define ALLOC(V, T1, T2, SZ) (V = (T1) GlobalAlloc(GPTR, SZ * sizeof(T2)))

// Program entry point
#define Main _tmain

// Environment variables
#define ENV_PATH T("PATH")
#define ENV_PATHEXT T("PATHEXT")
#define ENV_SPLIT(v) _tcstok(v, (LPCTSTR)(";"))
#define NEXT_ENV(v) (v =_tcstok(NULL, (LPCTSTR)(";")))


// Other stuff
#define WHICH_EXE argv[0]

// Arg handling helpers
#define IS_OPT(i,a) (a[i][0] == '-') && (slen(a[i]) == 2)

#ifdef _UNICODE
	#define I(x) ((long)x)
#elifdef _MBCS
	#define I(x) ((unsigned int)x)
#else
	#define I(x) ((int)x)
#endif

#define OPT(i) I(argv[i][1])
#define OPT_NEWLINE I(T('n'))
#define OPT_SHOWALL I(T('a'))
#define OPT_PATHEXT I(T('x'))
#define OPT_HELP1 I(T('h'))
#define OPT_HELP2 I(T('?'))

typedef struct {
	BOOL printNewLine;
	BOOL showAll;
	BOOL usePathExt;
} OPTS;