// Target Windows 2000 & higher
#define WINVER 0x0500
#define _WIN32_WINNT 0x0500

// Set to use multibyte characters.
#define _MBCS 1

// Speed up build process with minimal headers.
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN

// Eliminate some warnings.
#ifndef _CRT_SECURE_NO_WARNINGS
#	define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef _CRT_NONSTDC_NO_WARNINGS
#	define _CRT_NONSTDC_NO_WARNINGS
#endif

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <process.h>

// Resulting path
static char MyExecutable[_MAX_PATH] = "\0";

extern int _access(const char*, int);

// Just to make things prettier.
#define access _access
#define fgetcnl _fgetc_nolock
#define ftellnl _ftell_nolock
#define fseeknl _fseek_nolock

size_t get_file_length(FILE* pFile)
{
	long lCurrPos, lEndPos;
	size_t result = -1;
	lCurrPos = ftellnl(pFile);
	if(lCurrPos == -1)
		return result;
	if(fseeknl(pFile, 0L, SEEK_END) == -1)
		return result;
	lEndPos = ftellnl(pFile);
	if(lEndPos == -1)
		return result;
	result = (size_t)(lEndPos - lCurrPos);
	if(fseeknl(pFile, 0L, SEEK_SET) == -1)
		return -1;
	return result;
}

int process_file(const char* sFile)
{
	FILE* pInputFile = NULL;
	int result = FALSE;
	char temp;
	size_t bufflen = 0;
	int i = 1;
	char* buffer = NULL;
	pInputFile = fopen(sFile, "r");
	if((bufflen = get_file_length(pInputFile)) <= 0) goto error;
	buffer = (char*)malloc((bufflen+1) * sizeof(char));
	if(buffer == NULL) goto error;
	memset(buffer, 0, bufflen+1);
	if(fgetcnl(pInputFile) != '#' || fgetcnl(pInputFile) != '!') goto finally;
	while( (((temp = (char)fgetcnl(pInputFile)) == ' ') || (temp == '\t')) && temp && (temp != '\r') && (temp != '\r') );
	buffer[0] = temp;
	while( ((buffer[i] = (char)fgetcnl(pInputFile)) != EOF) && buffer[i] && (buffer[i] != '\r') && (buffer[i] != '\n') ) i++;
	buffer[i] = '\0';
	strcpy(MyExecutable, (const char*)buffer);
	result = TRUE;
	goto finally;
error:
	fprintf(stderr, "Error reading file: %s\n", sFile);
finally:
	fclose(pInputFile);
	if(buffer != NULL) free(buffer);
	return result;
}

int main(int argc, char* argv[])
{
	int i, result;
	char* buffer = NULL;
	int check = 0;
	int checked = 0;
	size_t bufflen = 0;
	if(argc == 1)
		return 1;
	for(i = 1; i < argc; i++) {
		size_t slen = strlen(argv[i]);
		bufflen += slen + 1; // strlen(" \"argv[i]\")
		if(checked) continue;
		if(!argv[i][0] || argv[i][0] == '-' || !slen) continue;
		if(access(argv[i], 4) == -1) continue;
		check = process_file((const char*)argv[i]);
		checked = 1;
	}
	if(check) argv[0] = MyExecutable;
	bufflen += strlen(argv[0]) + 5;
	buffer = (char*)malloc((bufflen) * sizeof(char));
	if(buffer == NULL) {
		printf("Failed to allocate buffer.\n");
		return 1;
	}
	memset(buffer, 0, bufflen);
	sprintf(buffer, "\"%s\"", argv[0]);
	for(i = 1; i < argc; i++) {
		strcat(buffer, " ");
		strcat(buffer, (const char*)argv[i]);
		//strcat(buffer, "\"");
	}
	strcat(buffer, "\r\n");
	result = system(buffer);
	free(buffer);
	return result;
}