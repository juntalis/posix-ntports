#include <globals.h>
#include "which.h"

static OPTS optsWhich;

static void exit_usage(tstr whichExe, int exitCode)
{
	ctstr strUsage =
		TC("Usage: %s [-h] [-x] [-n] [-a] program\n"
		"\n"
		"Options:\n"
		"\t"	"-h\t"	"Print this help text.\n"
		"\t"	"-x\t"	"Do not use PATHEXT in search.\n"
		"\t"	"-a\t"	"Show all matches. (Default: Show first match)\n"
		"\n");
	out(strUsage, whichExe);
	exit(exitCode);
}

static void print_cmd(ctstr execpath, bool first)
{
	if(first) out(execpath);
	else out("\n%s", execpath);
}

// Entry-point of the executable.
int app_main(int argc, tchar* argv[])
{
	tstr strTarget = NULL;
	int iResult = EXIT_FAILURE;
	int i = 1;

	// Set default args.
	optsWhich.usePathExt = true;
	optsWhich.showAll = false;
	

	// Parse args.
	if(argc > 1) {
		for(i = 1; i < argc; i++) {
			if(IS_OPT(i,argv)) {
				switch(OPT(i)) {
					case OPT_HELP1:
					case OPT_HELP2:
						exit_usage(WHICH_EXE, EXIT_SUCCESS);
						break;
					case OPT_SHOWALL:
						optsWhich.showAll = true;
						break;
					case OPT_PATHEXT:
						optsWhich.usePathExt = false;
						break;
					default:
						error("Unrecognized option %s", argv[i]);
						exit_usage(WHICH_EXE, EXIT_FAILURE);
						break;
				}
			} else {
				if(strTarget != NULL) {
					error("Target program/file already specified and at this time, this program does not support searching for multiple programs. "
					"If the filename contains a space, remember to surround it with \"s.", argv[i]);
					exit_usage(WHICH_EXE, EXIT_FAILURE);
				}
				strTarget = argv[i];
			}
		}
	} else {
		exit_usage(WHICH_EXE, EXIT_SUCCESS);
	}
	
	if(strTarget == NULL) {
		error("Target program not specified.");
		exit_usage(WHICH_EXE, EXIT_FAILURE);
	}
	if(!which_cmd(strTarget, optsWhich.showAll, optsWhich.usePathExt, &print_cmd))
		error("%s: no %s in (%s)", WHICH_EXE, strTarget, genv(ENV_PATH));

	#ifdef _DEBUG
	out("Press any key to continue.\n");
	_gettch();
	#endif
	return iResult;
}

