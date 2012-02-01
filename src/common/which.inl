
typedef void (*which_callback)(ctstr execpath, bool first);

inline bool which_cmd(tstr strExec, bool all, bool pathext, which_callback cb)
{
	tchar strBuffer[MAX_PATH];
	bool blResult = false;
	bool blFirst = true;
	tstr strSearch, strExt, envPathExt;
	size_t szSearch;
	size_t szExtLen;
	size_t i = 0;

	if(is_null(envPathExt = genv(T_ENV_PATHEXT)))
		fatal("Getting PATHEXT environmental variable returned NULL. Check PATHEXT and try again.");

	szExtLen = slen((ctstr)envPathExt);
	for(i = 0; i < szExtLen; i++)
		envPathExt[i] = (tchar)tolower((int)envPathExt[i]);

	if(is_null(strExt = env_split(envPathExt)))
		fatal("Could not split PATHEXT by delimiter \";\". Check your environment variables and try again." NL "\tPATHEXT = %s", envPathExt);
	
	searchenv(strExec, T_ENV_PATH, strBuffer, MAX_PATH);
	if(*strBuffer) {
		cb((ctstr)strBuffer, blFirst);
		if(!all)return true;
		blFirst = false;
	}

	if(pathext == true) {
		do {
			// Search for file in PATH environment variable:
			szSearch = slen(strExec) + slen(strExt) + 1;
			if(is_null(alloc(strSearch, tstr, tchar, szSearch)))
				fatal("Could not allocate memory for %s%s", strExec, strExt);
			sfmtvs(strSearch, szSearch, TC("%s%s\0"), (ctstr)strExec, (ctstr)strExt);
			searchenv(strSearch, T_ENV_PATH, strBuffer, MAX_PATH);
			unalloc(strSearch);
			if(*strBuffer) {
				blResult = true;
				cb((ctstr)strBuffer, blFirst);
				if(!all) return blResult;
				if(blFirst) blFirst = false;
			}
		} while(not_null(next_env(strExt)));
	}
	return blResult;
}