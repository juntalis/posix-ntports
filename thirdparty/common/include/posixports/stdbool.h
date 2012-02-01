/* Copyright (C) 1998, 1999, 2000, 2009 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */

/*
 * ISO C Standard:  7.16  Boolean type and values  <stdbool.h>
 */

#ifndef _STDBOOL_H
#define _STDBOOL_H

#ifndef __cplusplus

#define bool _Bool
#define true 1
#define false 0

#ifdef _MSC_VER
#	ifndef _WINDOWS_

#		include <WinSDKVer.h> 

/* Speed up build process with minimal headers. */
#		ifndef WIN32_LEAN_AND_MEAN
#			define WIN32_LEAN_AND_MEAN
#			define UNDEF_WIN32_LEAN
#		endif

#		ifndef VC_EXTRALEAN
#			define VC_EXTRALEAN
#			define UNDEF_VC_EXTRALEAN
#		endif

#		include <windows.h>
#		include <SDKDDKVer.h>

#		ifdef UNDEF_WIN32_LEAN
#			undef WIN32_LEAN_AND_MEAN
#			undef UNDEF_WIN32_LEAN
#		endif

#		ifdef UNDEF_VC_EXTRALEAN
#			undef VC_EXTRALEAN
#			undef UNDEF_VC_EXTRALEAN
#		endif

#	endif

#	ifndef _Bool
#		define _Bool BOOL
#	endif
#endif

#else /* __cplusplus */

/* Supporting <stdbool.h> in C++ is a GCC extension.  */
#define _Bool	bool
#define bool	bool
#define false	false
#define true	true

#endif /* __cplusplus */

/* Signal that all the definitions are present.  */
#define __bool_true_false_are_defined	1

#endif	/* stdbool.h */
