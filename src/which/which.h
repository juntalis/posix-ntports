#ifndef _WHICH_H_
#define _WHICH_H_

#pragma once

// Other stuff
#define WHICH_EXE argv[0]

// Arg handling helpers
#define IS_OPT(i,a) (a[i][0] == TC('-')) && (slen(a[i]) == 2)

#ifdef _UNICODE
	#define I(x) ((long)x)
#elifdef _MBCS
	#define I(x) ((unsigned int)x)
#else
	#define I(x) ((int)x)
#endif

#define OPT(i) I(argv[i][1])
#define OPT_NEWLINE I(TC('n'))
#define OPT_SHOWALL I(TC('a'))
#define OPT_PATHEXT I(TC('x'))
#define OPT_HELP1 I(TC('h'))
#define OPT_HELP2 I(TC('?'))

typedef struct {
	bool showAll;
	bool usePathExt;
} OPTS;

#endif
