#include <globals.h>
#include "ln.h"
#include "lnargs.h"
#include "lnsys.h"

static struct gengetopt_args_info args;
static PathElement pathargs[2] = {
	{ false, false, PATH_WIN32, NULL, NULL },
	{ false, false, PATH_WIN32, NULL, NULL }
};

int main (int argc, char *argv[])
{
	int i; int result = EXIT_SUCCESS;
	cmdline_parser(argc, argv, &args);
	
	if(args.inputs_num != 2) {
		cmdline_parser_print_help();
		return 0;
	}
	
	for(i = 0; i < (int)args.inputs_num; i++) {
		if(!strlen(args.inputs[i])) {
			if(i>0) free(pathargs[0].resolved);
			fatalA("An empty path was specified for one of the arguments.");
		}
		pathargs[i].original = args.inputs[i];
		
		if(pathargs[i].original[0] == '/')
			pathargs[i].pathType = PATH_POSIX;
		
		if(pathargs[i].original[0] == '.')
			pathargs[i].isRelative = true;
		
		if((pathargs[i].pathType == PATH_WIN32) &&
			(pathargs[i].original[1] != ':'))
				pathargs[i].isRelative = true;
		
		if((pathargs[i].pathType == PATH_WIN32) &&
			(strrchr(pathargs[i].original, '/') != NULL))
				pathargs[i].pathType = PATH_MIXED;
		
		pathargs[i].resolved = (char*)malloc(sizeof(char) * (_MAX_PATH + 1));
		zstr(pathargs[i].resolved, (MAX_PATH + 1));
		
		if(!ResolvePath(&pathargs[i])) {
			free(pathargs[i].resolved);
			if(i>0) free(pathargs[0].resolved);
			fatalA("Failed to resolve path: %s", pathargs[i].original);
		}
		
		if(!pathargs[i].isRelative)
			pathargs[i].resolved[0] = toupper(pathargs[i].resolved[0]);
		
		pathargs[i].isFolder = isFolder(pathargs[i].resolved);
	}
	
	if(args.symbolic_given) {
		if(!IsSymLinkSupported(&pathargs[0]) ||
			!IsSymLinkSupported(&pathargs[1])) {
				printf("Symbolic links are only supported on Vista and higher on NTFS file systems.\n");
				result = EXIT_FAILURE;
		} else if(!SymbolicLink(&pathargs[0], &pathargs[1])) {
			printf("Failed to create symbolic link.\n\nResolved paths:\n\tNew Link Path: %s\n\tTarget Path: %s\n", pathargs[1].resolved, pathargs[0].resolved);
			result = EXIT_FAILURE;
		}
	} else if(args.cyglink_given) {
		if(!IsCygLinkSupported()) {
			printf("To create cygwin-style symbolic links, you must be in a cygwin shell.\n");
			result = EXIT_FAILURE;
		} else if(!CygLink(&pathargs[0], &pathargs[1])) {
			printf("Failed to create a cygwin-style symbolic link.\n\nResolved Windows Paths:\n\tNew Link Path: %s\n\tTarget Path: %s\n", pathargs[1].resolved, pathargs[0].resolved);
			result = EXIT_FAILURE;
		}
	} else if(args.directory_given) {
		if(!IsJunctionSupported(&pathargs[0]) ||
			!IsJunctionSupported(&pathargs[1])) {
				printf("Junctions are only supported on WINNT or higher, and can only be made from folders on NTFS file systems.\n");
				result = EXIT_FAILURE;
		} else if(!Junction(&pathargs[0], &pathargs[1])) {
			printf("Failed to create a junction point.\n\nResolved Paths:\n\tNew Junction Path: %s\n\tTarget Path: %s\n", pathargs[1].resolved, pathargs[0].resolved);
			result = EXIT_FAILURE;
		}
	} else {
		if(!IsHardLinkSupported(&pathargs[0]) ||
			!IsHardLinkSupported(&pathargs[1])) {
				printf("Hard links are only supported on WINNT or higher, and cannot be point at folders. They are supported on NTFS filesystems, as well as UDF file systems.");
				result = EXIT_FAILURE;
		} else if(!HardLink(&pathargs[0], &pathargs[1])) {
			printf("Failed to create a new hard link.\n\nResolved Paths:\n\tNew Junction Path: %s\n\tTarget Path: %s\n", pathargs[1].resolved, pathargs[0].resolved);
			result = EXIT_FAILURE;
		}
	}
	if(result == EXIT_SUCCESS) {
		printf("%s was created successfully.\n", pathargs[1].resolved);
	}
	free(pathargs[0].resolved);
	free(pathargs[1].resolved);
	return result;
}