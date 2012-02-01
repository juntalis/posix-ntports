#include <globals.h>
#include <process.h>
#include "env.h"

static env_opts_info env_opts = { false, false, NULL };
static char** exec_argv = NULL;
static int exec_argc = 0;

static void exit_usage(int exitCode)
{
	ctstr usage = TC("Usage: env [OPTION]... [-] [NAME=VALUE]... [COMMAND [ARG]...]\n"
		"Set each NAME to VALUE in the environment and run COMMAND.\n\n"
		"  -i, --ignore-environment  start with an empty environment\n"
		"  -0, --null           end each output line with 0 byte rather than newline\n"
		"  -u, --unset=NAME     remove variable from the environment\n"
		"      --help     display this help and exit\n"
		"      --version  output version information and exit\n\n"
		"A mere - implies -i.  If no COMMAND, print the resulting environment.\n\n"
		"Report env bugs to the project site: <https://github.com/Juntalis/posix-ntports>\n");
	out(usage);
	exit(exitCode);
}

static void exit_version()
{
	out("env v" ENV_VERSION NL);
	exit(EXIT_SUCCESS);
}

static int unset_var_name(tstr varName)
{
#if 0
	// Main DLL we will need to load
	HANDLE hProcess = NULL;
	LPCSTR pszVarNameRemote = NULL;
	HANDLE hRemoteThread = NULL; 
	HMODULE msvcrt = NULL;
	PROCESS_INFORMATION pi;
	
	// Main function we will need to import
	FARPROC rputenv = NULL;
	int cch = 0;
	int cb = 0;
	int result = EXIT_SUCCESS;
	ctstr buffer = NULL;
		// Get the address of the main DLL
	msvcrt = LoadLibraryA("msvcrt.dll");
	if(!msvcrt) {
		out("Could not load MSVCRT.dll\n");
		return EXIT_FAILURE;
	}
	
	// Get our functions
	#ifdef _UNICODE
	rputenv = GetProcAddress(msvcrt, "_wputenv");
	#else
	rputenv = GetProcAddress(msvcrt, "_putenv");
	#endif
	
	if (!parent_process( &pi )) {
		error("Could not get parent process.\n");
		goto cleanup;
	}
	
	hProcess = OpenProcess(
		PROCESS_QUERY_INFORMATION |	 
		PROCESS_CREATE_THREAD		 | 
		PROCESS_VM_OPERATION |
		PROCESS_VM_WRITE,	// For CreateRemoteThread
		FALSE, pi.dwProcessId
	);
	
	if( !hProcess ) {
		error("Couldn't open parent process.\n");
		return EXIT_FAILURE;
	}
	
	// len(var) + len(=) + 1
	cch = lstrlen(varName) + 2;
	cb	= cch * sizeof(const tchar);
	
	buffer = (ctstr*)malloc(cb);
	if(buffer == NULL) {
		error("Could not allocate memory for our buffer.\n");
		goto cleanup;
	}
	
	memset((void*)buffer, 0, cb);
	sfmtv((tstr)buffer, TC("%s="), varName);
	
	pszVarNameRemote = (ctstr) VirtualAllocEx( hProcess, NULL, cb, MEM_COMMIT, PAGE_READWRITE);
	if ( pszVarNameRemote == NULL) 
	{
		error("Unable to allocate memory in our parent process\n");
		result = EXIT_FAILURE;
		goto cleanup;
	}
	
	if (!WriteProcessMemory(hProcess, (LPVOID)pszVarNameRemote,
		(LPCVOID)buffer, (SIZE_T)cb, NULL)) 
	{
		error("Failed to write to parent process memory.\n");
		result = EXIT_FAILURE;
		goto cleanup;
	};
	
	// Create remote thread and inject the function call.
	hRemoteThread = CreateRemoteThread( hProcess, NULL, 0, 
		(LPTHREAD_START_ROUTINE)rputenv, 
		(LPVOID)pszVarNameRemote, 0L, NULL);

	if( !hRemoteThread )
	{
		error("Failed to update process.\n");
		result = EXIT_FAILURE;
		goto cleanup;
	}

	WaitForSingleObject( hRemoteThread, INFINITE );
	goto cleanup;
cleanup:
	// Free the remote memory that contained the DLL's pathname
	if (pszVarNameRemote != NULL) 
		VirtualFreeEx(hProcess, (LPVOID)pszVarNameRemote, 0, MEM_RELEASE);

	if ( hRemoteThread != NULL) 
		CloseHandle(hRemoteThread);

	if ( buffer != NULL)
		free((void*)buffer);
	
	if ( hProcess != NULL) 
		CloseHandle(hProcess);
	
	if ( msvcrt != NULL)
		FreeLibrary(msvcrt);
	
	return result;
#endif
	// Just realized env doesn't actually unset the variable in the current shell - just in the
	// child and current process. Lame.
	tstr buffer = NULL;
	int result = EXIT_SUCCESS;
	size_t cch = lstrlen(varName) + 2;
	if(alloc(buffer, tstr, tchar, cch) == NULL)
		fatal("Could not allocate memory for our buffer.\n")
	memset((void*)buffer, 0, cch*sizeof(tchar));
	sfmtv((tstr)buffer, TC("%s="), varName);
	if(penv(buffer) == -1) {
		error("Could not unset the environment variable: %s\n", varName);
		result = EXIT_FAILURE;
	}
	unalloc(buffer);
	return result;
}

#if 0
static void unset_var(tstr varline)
{
	int i = 0;
	tstr substr = NULL;
	tstr buffer = _tcsdup((ctstr)varline);
	if(buffer == NULL)
		fatal("Could not allocate memory for buffer.\n");
	substr = _tcschr(buffer, TC('='));
	while(*(substr++) != NULL) *substr = TC('\0');
	out("%s\n", buffer);
	if(penv((ctstr)buffer) == -1) {
		free(buffer);
		fatal("Could not unset environment variable.\n");
	}
	free(buffer);
}
#endif

static void show_var(tstr varline)
{
	if(env_opts.null_delim) {
		out("%s\0", varline);
	} else {
		out("%s\n", varline);
	}
}

static int on_all_vars(with_var callback)
{
	int i = 0;
	if(envvars == NULL) genv(T_ENV_PATH);
	while(not_null(envvars[i])) {
		callback(envvars[i]);
		i++;
	}
	return EXIT_SUCCESS;
}

static int handle_short_opt(int argc, tchar* argv[], int* indx)
{
	tchar buffer[MAX_ENV] = "\0";
	size_t arglen = slen(argv[*indx]);
	if(arglen == 1) {
		env_opts.ignore_env = true;
		return EXIT_SUCCESS;
	}
	switch(short_opt(*indx))
	{
		case sopt_help:
			exit_usage(EXIT_SUCCESS);
			break;
		case sopt_ignore:
			env_opts.ignore_env = true;
			break;
		case sopt_null:
			env_opts.null_delim = true;
			break;
		case sopt_unset:
			if(arglen > 2) {
				arglen -= 2;
				_tcsncpy(buffer, argv[*indx] + 2, arglen);
				return unset_var_name(buffer);
			} else {
				if(*indx == (argc - 1)) {
					error("You must specify a variable to unset when using the -u option.\n");
					return EXIT_FAILURE;
				}
				(*indx)++;
				return unset_var_name(argv[*indx]);
			}
			break;
		default:
			error("Unrecognized option specified: %s\n", argv[*indx]);
			exit_usage(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}

static int handle_long_opt(tstr arg)
{
	tchar buffer[MAX_ENV] = "\0";
	size_t arglen = slen(arg);
	if(is_lopt_help(arg)) {
		exit_usage(EXIT_SUCCESS);
	} else if(is_lopt_vers(arg)) {
		exit_version();
	} else if(is_lopt_null(arg)) {
		env_opts.null_delim = true;
	} else if(is_lopt_ignore(arg)) {
		env_opts.ignore_env = true;
	} else if(is_lopt_unset(arg)) {
		validate_lopt_unset(arg);
		arglen -= 8;
		_tcsncpy(buffer, arg + 8, arglen);
		return unset_var_name(buffer);
	} else {
		error("Unrecognized option specified: %s\n", arg);
		exit_usage(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}

static int exec_cmd()
{
	const tchar* const* envp = {NULL};
	if(env_opts.ignore_env)
		return (int)_tspawnvpe(_P_WAIT, env_opts.exe, (const tchar* const*)env_opts.argv, envp);
	else
		return (int)_tspawnvp(_P_WAIT, env_opts.exe,  (const tchar* const*)env_opts.argv);
}

// Entry-point of the executable.
int app_main(int argc, tchar* argv[])
{
	opt_type optTemp; int i;
	size_t argbufflen;
	int indx;
	int result = EXIT_SUCCESS;

	env_opts.argc = argc;
	for(i = 1; i < argc; i++) {
		optTemp = get_opt_type(argv,i);
		if(optTemp == OPT_INPUT)
			break;
		if(optTemp == OPT_SHORT) {
			if(failed(handle_short_opt(argc, argv, &i)))
				return EXIT_FAILURE;
		} else {
			if(failed(handle_long_opt(argv[i])))
				return EXIT_FAILURE;
		}
		env_opts.argc--;
	}
	
	if(i >= argc)
		return on_all_vars(&show_var);
	
	argbufflen = env_opts.argc * sizeof(tchar*);
	env_opts.argv = (tchar**)malloc(argbufflen);
	memset((void*)env_opts.argv, 0, argbufflen);
	
	env_opts.exe = (const tchar*)argv[i];
	for(indx = 0; i < argc; i++, indx++) {
		size_t arglen = slen(argv[i]);
		if(!arglen) {
			env_opts.argc--;
			indx--;
			continue;
		}
		arglen += 3; // length of " + " + \0
		env_opts.argv[indx] = (tchar*)malloc(sizeof(tchar) * arglen);
		memset((void*)env_opts.argv[indx], 0, arglen);
		sfmtv(env_opts.argv[indx], TC("\"%s\""), argv[i]);
		
	}
	
	env_opts.argv[indx] = NULL;
	result = exec_cmd();
	for(i = 0; i < env_opts.argc; i++) {
		if(env_opts.argv[i] != NULL)
			free((void*)env_opts.argv[i]);
	}
	free((void*)env_opts.argv);
	return result;
}

