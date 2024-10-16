#pragma once

#include <xieite/platform.hpp>

#if XIEITE_PLATFORM_TYPE_UNIX
#	include <unistd.h>
#endif

#define XIEITE_UNIX_STANDARD_POSIX_1988 0
#define XIEITE_UNIX_STANDARD_POSIX_1990 0
#define XIEITE_UNIX_STANDARD_POSIX_1993 0
#define XIEITE_UNIX_STANDARD_POSIX_1996 0
#define XIEITE_UNIX_STANDARD_POSIX_2001 0
#define XIEITE_UNIX_STANDARD_POSIX_2008 0
#define XIEITE_UNIX_STANDARD_POSIX_1992 0
#define XIEITE_UNIX_STANDARD_XOPEN_1989 0
#define XIEITE_UNIX_STANDARD_XOPEN_1992 0
#define XIEITE_UNIX_STANDARD_XOPEN_1995 0
#define XIEITE_UNIX_STANDARD_XOPEN_1998 0
#define XIEITE_UNIX_STANDARD_XOPEN_2003 0
#define XIEITE_UNIX_STANDARD_XOPEN_2008 0
#define XIEITE_UNIX_STANDARD_LSB 0

#ifdef _POSIX_VERSION
#	if _POSIX_VERSION >= 198808
#		undef XIEITE_UNIX_STANDARD_POSIX_1998
#		define XIEITE_UNIX_STANDARD_POSIX_1988 1
#	endif

#	if _POSIX_VERSION >= 199009
#		undef XIEITE_UNIX_STANDARD_POSIX_1990
#		define XIEITE_UNIX_STANDARD_POSIX_1990 1
#	endif

#	if _POSIX_VERSION >= 199309
#		undef XIEITE_UNIX_STANDARD_POSIX_1993
#		define XIEITE_UNIX_STANDARD_POSIX_1993 1
#	endif

#	if _POSIX_VERSION >= 199506
#		undef XIEITE_UNIX_STANDARD_POSIX_1996
#		define XIEITE_UNIX_STANDARD_POSIX_1996 1
#	endif

#	if _POSIX_VERSION >= 200112
#		undef XIEITE_UNIX_STANDARD_POSIX_2001
#		define XIEITE_UNIX_STANDARD_POSIX_2001 1
#	endif

#	if _POSIX_VERSION >= 200809
#		undef XIEITE_UNIX_STANDARD_POSIX_2008
#		define XIEITE_UNIX_STANDARD_POSIX_2008 1
#	endif
#endif

#ifdef _POSIX2_C_VERSION
#	if _POSIX2_C_VERSION >= 199209
#		undef XIEITE_UNIX_STANDARD_POSIX_1992
#		define XIEITE_UNIX_STANDARD_POSIX_1992 1
#	endif
#endif

#ifdef _XOPEN_VERSION
#	if _XOPEN_VERSION >= 3
#		undef XIEITE_UNIX_STANDARD_XOPEN_1989
#		define XIEITE_UNIX_STANDARD_XOPEN_1989 1
#	endif

#	if _XOPEN_VERSION >= 4
#		undef XIEITE_UNIX_STANDARD_XOPEN_1992
#		define XIEITE_UNIX_STANDARD_XOPEN_1992 1
#	endif

#	if (_XOPEN_VERSION >= 4) && defined(_XOPEN_UNIX)
#		undef XIEITE_UNIX_STANDARD_XOPEN_1995
#		define XIEITE_UNIX_STANDARD_XOPEN_1995 1
#	endif

#	if _XOPEN_VERSION >= 500
#		undef XIEITE_UNIX_STANDARD_XOPEN_1998
#		define XIEITE_UNIX_STANDARD_XOPEN_1998 1
#	endif

#	if _XOPEN_VERSION >= 600
#		undef XIEITE_UNIX_STANDARD_XOPEN_2003
#		define XIEITE_UNIX_STANDARD_XOPEN_2003 1
#	endif

#	if _XOPEN_VERSION >= 700
#		undef XIEITE_UNIX_STANDARD_XOPEN_2008
#		define XIEITE_UNIX_STANDARD_XOPEN_2008 1
#	endif
#endif

#ifdef __LSB_VERSION__
#	undef XIEITE_UNIX_STANDARD_LSB
#	define XIEITE_UNIX_STANDARD_LSB 1
#endif

// https://sourceforge.net/p/predef/wiki/Standards/
