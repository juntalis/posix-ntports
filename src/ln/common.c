#include <globals.h>
#include <stdarg.h>
#include "ln.h"

void fatalA(const char* format, ...)
{
	va_list ap;
	fprintf(stderr, FATAL_PREFIX);
	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);
	fprintf(stderr, NEWLINE); // TODO: Print to log here.
	exit(EXIT_FAILURE);
}

void fatalW(const wchar_t* format, ...)
{
	va_list ap;
	fwprintf(stderr, A2W(FATAL_PREFIX));
	va_start(ap, format);
	vfwprintf(stderr, format, ap);
	va_end(ap);
	fwprintf(stderr, A2W(NEWLINE)); // TODO: Print to log here.
	exit(EXIT_FAILURE);
}

bool isFolder(char* pszPath)
{
	return (GetFileAttributesA(pszPath) & FILE_ATTRIBUTE_DIRECTORY);
}