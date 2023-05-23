#ifndef XIEITE_HEADER_MACROS_SYSTEM_TYPE
#	define XIEITE_HEADER_MACROS_SYSTEM_TYPE

#	ifdef _AIX
#		define XIEITE_SYSTEM_TYPE_AIX
#	endif

#	ifdef __ANDROID__
#		define XIEITE_SYSTEM_TYPE_ANDROID
#	endif

#	ifdef UTS
#		define XIEITE_SYSTEM_TYPE_UTS
#	endif

#	if defined(AMIGA) || defined(__amigaos__)
#		define XIEITE_SYSTEM_TYPE_AMIGAOS
#	endif

#	ifdef aegis
#		define XIEITE_SYSTEM_TYPE_AEGIS
#	endif

#	ifdef apollo
#		define XIEITE_SYSTEM_TYPE_DOMAIN_OS
#	endif

#	ifdef __BEOS__
#		define XIEITE_SYSTEM_TYPE_BEOS
#	endif

#	if defined(__bg__) || defined(__THW_BLUEGENE__)
#		define XIEITE_SYSTEM_TYPE_BLUE_GENE
#	endif

#	if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__) || defined(_SYSTYPE_BSD)
#		define XIEITE_SYSTEM_TYPE_BSD
#	endif

#	ifdef __bsdi__
#		define XIEITE_SYSTEM_TYPE_BSD_OS
#	endif

#	ifdef __convex__
#		define XIEITE_SYSTEM_TYPE_CONVEXOS
#	endif

#	ifdef __SYGWIN__
#		define XIEITE_SYSTEM_TYPE_SYGWIN
#	endif

#	if defined(DGUX) || defined(__DGUX__) || defined(__dgux__)
#		define XIEITE_SYSTEM_TYPE_DG_UX
#	endif

#	ifdef __DragonFly__
#		define XIEITE_SYSTEM_TYPE_DRAGONFLY
#	endif

#	if defined(_SEQUENT_) || defined(sequent)
#		define XIEITE_SYSTEM_TYPE_DYNIX
#	endif

#	ifdef __ECOS
#		define XIEITE_SYSTEM_TYPE_ECOS
#	endif

#	ifdef __EMX__
#		define XIEITE_SYSTEM_TYPE_EMX
#	endif

#	if defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
#		define XIEITE_SYSTEM_TYPE_FREEBSD
#	endif

#	if defined(__GNU__) || defined(__gnu_hurd__)
#		define XIEITE_SYSTEM_TYPE_GNU_HURD
#	endif

#	if defined(__FreeBSD_kernel__) && defined(__GLIBC__)
#		define XIEITE_SYSTEM_TYPE_GNU_KFREEBSD
#	endif

#	ifdef __gnu_linux__
#		define XIEITE_SYSTEM_TYPE_GNU_LINUX
#	endif

#	ifdef __hiuxmpp
#		define XIEITE_SYSTEM_TYPE_HI_UX_MPP
#	endif

#	ifdef __OS400__
#		define XIEITE_SYSTEM_TYPE_OS_400
#	endif

#	ifdef __INTEGRITY
#		define XIEITE_SYSTEM_TYPE_INTEGRITY
#	endif

#	ifdef __INTERIX
#		define XIEITE_SYSTEM_TYPE_INTERIX
#	endif

#	if defined(sgi) || defined(__sgi)
#		define XIEITE_SYSTEM_TYPE_IRIX
#	endif

#	ifdef __linux__
#		define XIEITE_SYSTEM_TYPE_LINUX
#	endif

#	ifdef __Lynx__
#		define XIEITE_SYSTEM_TYPE_LYNXOS
#	endif

#	if defined(macintosh) || defined(Macintosh) || defined(__APPLE__) && defined(__MACH__)
#		define XIEITE_SYSTEM_TYPE_MACOS
#	endif

#	if defined(__OS9000) || defined(_OSK)
#		define XIEITE_SYSTEM_TYPE_OS_9
#	endif

#	ifdef __minix
#		define XIEITE_SYSTEM_TYPE_MINIX
#	endif

#	ifdef __MORPHOS__
#		define XIEITE_SYSTEM_TYPE_MORPHOS
#	endif

#	if defined(mpeix) || defined(__mpexl)
#		define XIEITE_SYSTEM_TYPE_MPE_IX
#	endif

#	if defined(MSDOS) || defined(__MSDOS__) || defined(_MSDOS) || defined(__DOS__)
#		define XIEITE_SYSTEM_TYPE_MS_DOS
#	endif

#	ifdef __NetBSD__
#		define XIEITE_SYSTEM_TYPE_NETBSD
#	endif

#	ifdef __TANDEM
#		define XIEITE_SYSTEM_TYPE_NONSTOP
#	endif

#	ifdef __nucleus__
#		define XIEITE_SYSTEM_TYPE_NUCLEUS_RTOS
#	endif

#	ifdef __OpenBSD__
#		define XIEITE_SYSTEM_TYPE_OPENBSD
#	endif

#	if defined(OS2) || defined(_OS2) || defined(__OS2__) || defined(__TOS_OS2__)
#		define XIEITE_SYSTEM_TYPE_OS_2
#	endif

#	ifdef __palmos__
#		define XIEITE_SYSTEM_TYPE_PALM_OS
#	endif

#	ifdef EPLAN9
#		define XIEITE_SYSTEM_TYPE_PLAN_9
#	endif

#	ifdef pyr
#		define XIEITE_SYSTEM_TYPE_DC_OSX
#	endif

#	if defined(__QNX__) || defined(__QNXNTO__)
#		define XIEITE_SYSTEM_TYPE_QNX
#	endif

#	ifdef sinux
#		define XIEITE_SYSTEM_TYPE_SINIX
#	endif

#	if defined(M_I386) || defined(M_XENIX) || defined(_SCO_DS)
#		define XIEITE_SYSTEM_TYPE_OPENSERVER
#	endif

#	if defined(sun) || defined(__sun)
#		define XIEITE_SYSTEM_TYPE_SOLARIS
#	endif

#	ifdef __VOS__
#		define XIEITE_SYSTEM_TYPE_VOS
#	endif

#	if defined(__sysv__) || defined(__SVR4) || defined(__svr4__) || defined(_SYSTYPE_SVR4)
#		define XIEITE_SYSTEM_TYPE_SYSTEM_V
#	endif

#	ifdef __SYLLABLE__
#		define XIEITE_SYSTEM_TYPE_SYLLABLE
#	endif

#	ifdef __SYMBIAN32__
#		define XIEITE_SYSTEM_TYPE_SYMBIAN
#	endif

#	if defined(__osf__) || defined(__osf)
#		define XIEITE_SYSTEM_TYPE_TRU64
#	endif

#	if defined(ultrix) || defined(__ultrix) || defined(__ultrix__) || defined(unix) && defined(vax)
#		define XIEITE_SYSTEM_TYPE_ULTRIX
#	endif

#	ifdef _UNICOS
#		define XIEITE_SYSTEM_TYPE_UNICOS
#	endif

#	if defined(_CRAY) || defined(__crayx1)
#		define XIEITE_SYSTEM_TYPE_UNICOS_MP
#	endif

#	if defined(__unix__) || defined(__unix)
#		define XIEITE_SYSTEM_TYPE_UNIX
#	endif

#	if defined(sco) || defined(_UNIXWARE7)
#		define XIEITE_SYSTEM_TYPE_UNIXWARE
#	endif

#	ifdef _UWIN
#		define XIEITE_SYSTEM_TYPE_UWIN
#	endif

#	if defined(VMS) || defined(__VMS)
#		define XIEITE_SYSTEM_TYPE_VMS
#	endif

#	if defined(__VXWORKS__) || defined(__vxworks)
#		define XIEITE_SYSTEM_TYPE_VXWORKS
#	endif

#	if defined(_WIN16) || defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
#		define XIEITE_SYSTEM_TYPE_WINDOWS
#	endif

#	ifdef _WIN32_WCE
#		define XIEITE_SYSTEM_TYPE_WINDOWS_CE
#	endif

#	ifdef _WINDU_SOURCE
#		define XIEITE_SYSTEM_TYPE_WIND_U
#	endif

#	if defined(__MVS__) || defined(__HOS_MVS__) || defined(__TOS_MVS__)
#		define XIEITE_SYSTEM_TYPE_Z_OS
#	endif

#endif
