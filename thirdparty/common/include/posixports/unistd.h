#ifndef _UNISTD_H
#define _UNISTD_H

#ifdef __MINGW32__
#	include_next <unistd.h>
#else

#	include <io.h>
#	include <process.h>

#	ifndef ssize_t
#		define ssize_t int
#	endif

#	ifndef R_OK
#		define R_OK 4
#	endif


#endif

#endif /* _UNISTD_H */