#ifndef _ENV_H_
#define _ENV_H_

#pragma once

#define ENV_VERSION "1.0"

// Arg handling macros
#define OPT_INPUT 0
#define OPT_SHORT 1
#define OPT_LONG 2

#define opt_type int
#define get_opt_type(a,i) (a[i][0] == TC('-')) ? (\
					((slen(a[i]) > 2) && (a[i][1] == TC('-'))) ? OPT_LONG : OPT_SHORT \
					) : OPT_INPUT



typedef void (*with_var)(tstr varline);


#define short_opt(i) I(argv[i][1])
#define sopt_help I(TC('h'))
#define sopt_null I(TC('0'))
#define sopt_ignore I(TC('i'))
#define sopt_unset I(TC('u'))

#define is_opt(v,b,n)		(_tcsnccmp((ctstr)v, b, n) == 0)
#define is_lopt_help(v)		is_opt(v, TC("--help"), 6)
#define is_lopt_vers(v)		is_opt(v, TC("--version"), 9)
#define is_lopt_null(v)		is_opt(v, TC("--null"), 6)
#define is_lopt_ignore(v)	is_opt(v, TC("--ignore-environment"), 20)
#define is_lopt_unset(v)	is_opt(v, TC("--unset="), 8)

#define validate_lopt_unset(v) if(slen(v) <= 8) fatal("env: cannot unset `': Invalid argument\n");


typedef struct {
	bool ignore_env;
	bool null_delim;
	const tchar* exe;
	tchar** argv;
	int argc;
} env_opts_info;

#endif
