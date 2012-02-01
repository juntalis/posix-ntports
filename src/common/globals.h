#ifndef _GLOBALS_H_
#define _GLOBALS_H_
#pragma once

#include "targetver.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef DEBUG
#	include <conio.h>
#endif

/* Macros for prettier code. */
#ifndef MAX_PATH
#	define MAX_PATH _MAX_PATH
#endif

#ifndef MAX_ENV
#	define MAX_ENV _MAX_ENV
#endif

/* Function Annotations/Declarations */
// Declare inline for MSVC's C compiler
#ifndef inline
#	define inline __inline
#endif

/* TCHAR Macros */
#include <tchar.h>

#ifndef bool
#	define bool BOOL
#	define true TRUE
#	define false FALSE
#endif

// I like lowercase
#ifndef tchar
#	define tchar TCHAR
#endif

#ifndef tstr
#	define tstr LPTSTR
#endif

#ifndef ctstr
#	define ctstr LPCTSTR
#endif

// Undefine any existing macros that would conflict with ours.
#ifdef searchenv
#	undef searchenv
#endif

// App-level stuff

// Program entry point
#define app_main _tmain


// Environment variables
#ifndef envvars
#	ifdef _UNICODE
#		define envvars _wenviron
#	else
#		define envvars _environ
#	endif
#endif

#define searchenv	_tsearchenv_s
#define genv		_tgetenv
#define genvs		_tgetenv_s
#define denv		_dupenv_s
#define penv		_tputenv
#define penvs		_tputenv_s


// String functions
#define slen		_tcslen
#define sclen		_tcsclen
#define snlen		_tcsnlen


// Format string functions
#define sfmtv		_stprintf
#define sfmtvp		_stprintf_p
#define sfmtvs		_stprintf_s
#define sfmto		_tprintf
#define sfmtop		_tprintf_p
#define sfmtos		_tprintf_s
#define sfmtf		_ftprintf
#define sfmtfp		_ftprintf_p
#define sfmtfs		_ftprintf_s


// wrap string with tchar.
#ifndef TC
#	define TC(s) __T(s)
#endif

#ifdef _UNICODE
#	define I(x) ((long)x)
#elifdef _MBCS
#	define I(x) ((unsigned int)x)
#else
#	define I(x) ((int)x)
#endif

/* Global defines & macros */

// newline & newline tchar
#ifdef NL
#	undef NL
#endif
#ifdef TNL
#	undef TNL
#endif
#define NL "\n"
#define TNL TC(NL)

// PATH env var
#define T_ENV_PATH TC(ENV_PATH)
#define ENV_PATH "PATH"

// PATHEXT env var
#define T_ENV_PATHEXT TC(ENV_PATHEXT)
#define ENV_PATHEXT "PATHEXT"

// Output prefixes
#define ERR_PREFIX "Error: "

// Output macros
#define error(M,...) err(ERR_PREFIX M, __VA_ARGS__)
#define out(M,...) sfmtos(TC(M), __VA_ARGS__)
#define err(M,...) sfmtfs(stderr, TC(M), __VA_ARGS__)

// Fatal error
#define fatal(M,...) { error(M,__VA_ARGS__); exit(EXIT_FAILURE); }

// Utility macros
#define success(x) ((x) == EXIT_SUCCESS)
#define failed(x) ((x) == EXIT_FAILURE)
#define alloc(V, T1, T2, SZ) (V = (T1) GlobalAlloc(GPTR, SZ * sizeof(T2)))
#define unalloc GlobalFree
#define not_null(x) ((x) != NULL)
#define is_null(x) ((x) == NULL)

#define env_split(v) _tcstok(v, (LPCTSTR)(TC(";")))
#define next_env(v) (v =_tcstok(NULL, (LPCTSTR)(TC(";"))))

#ifdef __cplusplus
#	define CEXTERN_BEGIN CEXTERN_DECL {
#	define CEXTERN_END }
#	define CEXTERN_DECL extern "C"
#else
#	define CEXTERN_BEGIN
#	define CEXTERN_END
#	define CEXTERN_DECL extern
#endif

#ifdef WITH_WHICH
#	include <which.inl>
#endif

#ifdef WITH_PARENT
#	include <parent.inl>
#endif

#endif