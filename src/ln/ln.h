#ifndef _LN_H_
#define _LN_H_
#pragma once

/* Global defines */
#define NEWLINE "\n"

#define A2W(quote) _AW2(quote)
#define _AW2(quote) L## quote

#define zstr(str,sz) memset(str, '\0', sz)

#define FATAL_PREFIX "Fatal Error: "

#ifndef MAX_PATH
#	define MAX_PATH _MAX_PATH
#endif

/* Global macros */
// Load dll or get the handle to a dll already loaded.

// char variation
#define GetLibraryA(h,d) if((h = GetModuleHandleA(d)) == NULL) \
		if((h = LoadLibraryA(d)) == NULL) \
			fatalA("Could not load %s.", d)

// wchar_t variation
#define GetLibraryW(h,d) if((h = GetModuleWHandleA(d)) == NULL) \
		if((h = LoadLibraryW(d)) == NULL) \
			fatalW(L"Could not load %s.", d)

// Get a function from a loaded module.
#define GetFunction(h,t,v,f) if((v = (t)GetProcAddress(h, f)) == NULL) {\
		FreeLibrary(h); \
		fatalA("Failed to load function %s.", f); \
	}

// Prototypes
void fatalA(const char* format, ...);
void fatalW(const wchar_t* format, ...);
bool isFolder(char* pszPath);


/* And unicode/ascii definitions. */
#ifdef _UNICODE
#	define GetLibrary GetLibraryW
#else
#	define GetLibrary GetLibraryA
#endif

#ifndef EXIT_SUCCESS
#	define EXIT_SUCCESS 0
#endif

#ifndef EXIT_FAILURE
#	define EXIT_FAILURE 1
#endif

typedef enum {
	PATH_WIN32 = 0,
	PATH_POSIX,
	PATH_MIXED
} PathType;

typedef struct {
	bool isRelative;
	bool isFolder;
	PathType pathType;
	char* original;
	char* resolved;
} PathElement, *pPathElement;

#endif /* _LN_H_ */