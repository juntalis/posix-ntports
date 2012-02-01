#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/cygwin.h>
#include "cmdargs.h"

#define zstr(str,sz) memset(str, '\0', sz)

#ifndef MAX_PATH
#	define MAX_PATH 260
#endif

typedef int (*pConvPathFunc)(const char *, char *);

static struct gengetopt_args_info args;

static int conv_to_win32(int mixed)
{
	char *buffer;
	int result;
	int i; char* p;
	pConvPathFunc func;
	const char* target = (const char *)args.inputs[0];
	int bufferlen = MAX_PATH;
	
	if(args.path_given) {
		if((bufferlen = cygwin32_posix_to_win32_path_list_buf_size(target)) > 0) {
			func = (pConvPathFunc)(&cygwin32_posix_to_win32_path_list);
		} else {
			return EXIT_FAILURE;
		}
	} else if(args.absolute_given) {
		func = (pConvPathFunc)(&cygwin32_conv_to_full_win32_path);
	} else {
		func = (pConvPathFunc)(&cygwin32_conv_to_win32_path);
	}
	bufferlen++;
	buffer = (char*)malloc(sizeof(char) * (bufferlen));
	zstr(buffer, bufferlen);
	result = (func(target, buffer) == -1);
	if(!result) {
		p = buffer;
		if(!mixed)
			for(i = 0; p[i]; i++)
				if(p[i] == '/') p[i] = '\\';
	} else if(strlen(target)) {
		p = (char*)target;
		if(!mixed)
			for(i = 0; p[i]; i++)
				if(p[i] == '/') p[i] = '\\';
	}
	printf(p);
	free(buffer);
	return result;
}

static int conv_to_posix()
{
	char *buffer;
	int result;
	pConvPathFunc func;
	const char* target = (const char *)args.inputs[0];
	int bufferlen = MAX_PATH;
	
	if(args.path_given) {
		if((bufferlen = cygwin32_win32_to_posix_path_list_buf_size(target)) > 0) {
			func = (pConvPathFunc)(&cygwin32_win32_to_posix_path_list);
		} else {
			return EXIT_FAILURE;
		}
	} else if(args.absolute_given) {
		func = (pConvPathFunc)(&cygwin32_conv_to_full_posix_path);
	} else {
		func = (pConvPathFunc)(&cygwin32_conv_to_posix_path);
	}
	bufferlen++;
	buffer = (char*)malloc(sizeof(char) * (bufferlen));
	zstr(buffer, bufferlen);
	result = (func(target, buffer) == -1);
	if(!result) {
		printf(buffer);
	} else {
		printf(target);
	}
	free(buffer);
	return result;
}

int main(int argc, char* argv[])
{
	cmdline_parser(argc, argv, &args);
	
	if(args.file_given) {
		printf("Not yet implemented.\n");
		exit(EXIT_SUCCESS);
	}
	
	if(args.inputs_num == 0) {
		printf("Not filepath specified for conversion.\n");
		exit(EXIT_FAILURE);
	}
	
	if(args.windows_given || args.mixed_given) {
		return conv_to_win32(args.mixed_given);
	} else if(args.unix_given) {
		return conv_to_posix();
	}
	
	return EXIT_SUCCESS;
}
