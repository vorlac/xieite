#ifndef XIEITE_HEADER_MACROS_ARCHITECTURE
#	define XIEITE_HEADER_MACROS_ARCHITECTURE

#	define XIEITE_ARCHITECTURE_TYPE_AARCH64 0
#	define XIEITE_ARCHITECTURE_TYPE_ALPHA 0
#	define XIEITE_ARCHITECTURE_TYPE_ARM 0
#	define XIEITE_ARCHITECTURE_TYPE_BLACKFIN 0
#	define XIEITE_ARCHITECTURE_TYPE_CONVEX 0
#	define XIEITE_ARCHITECTURE_TYPE_EPIPHANY 0
#	define XIEITE_ARCHITECTURE_TYPE_ITANIUM 0
#	define XIEITE_ARCHITECTURE_TYPE_MIPS 0
#	define XIEITE_ARCHITECTURE_TYPE_MOTOROLA_68000 0
#	define XIEITE_ARCHITECTURE_TYPE_PA_RISC 0
#	define XIEITE_ARCHITECTURE_TYPE_POWERPC 0
#	define XIEITE_ARCHITECTURE_TYPE_PYRAMID_9810 0
#	define XIEITE_ARCHITECTURE_TYPE_RS_6000 0
#	define XIEITE_ARCHITECTURE_TYPE_SPARC 0
#	define XIEITE_ARCHITECTURE_TYPE_SUPERH 0
#	define XIEITE_ARCHITECTURE_TYPE_TMS320 0
#	define XIEITE_ARCHITECTURE_TYPE_TMS470 0
#	define XIEITE_ARCHITECTURE_TYPE_X86_32 0
#	define XIEITE_ARCHITECTURE_TYPE_X86_64 0
#	define XIEITE_ARCHITECTURE_TYPE_Z 0

#	define XIEITE_ARCHITECTURE_VERSION_MAJOR_AARCH64 0
#	define XIEITE_ARCHITECTURE_VERSION_MINOR_AARCH64 0
#	define XIEITE_ARCHITECTURE_VERSION_PATCH_AARCH64 0
#	define XIEITE_ARCHITECTURE_VERSION_MAJOR_ALPHA 0
#	define XIEITE_ARCHITECTURE_VERSION_MINOR_ALPHA 0
#	define XIEITE_ARCHITECTURE_VERSION_PATCH_ALPHA 0
#	define XIEITE_ARCHITECTURE_VERSION_MAJOR_ARM 0
#	define XIEITE_ARCHITECTURE_VERSION_MINOR_ARM 0
#	define XIEITE_ARCHITECTURE_VERSION_PATCH_ARM 0
#	define XIEITE_ARCHITECTURE_VERSION_MAJOR_BLACKFIN 0
#	define XIEITE_ARCHITECTURE_VERSION_MINOR_BLACKFIN 0
#	define XIEITE_ARCHITECTURE_VERSION_PATCH_BLACKFIN 0
#	define XIEITE_ARCHITECTURE_VERSION_MAJOR_CONVEX 0
#	define XIEITE_ARCHITECTURE_VERSION_MINOR_CONVEX 0
#	define XIEITE_ARCHITECTURE_VERSION_PATCH_CONVEX 0
#	define XIEITE_ARCHITECTURE_VERSION_MAJOR_EPIPHANY 0
#	define XIEITE_ARCHITECTURE_VERSION_MINOR_EPIPHANY 0
#	define XIEITE_ARCHITECTURE_VERSION_PATCH_EPIPHANY 0
#	define XIEITE_ARCHITECTURE_VERSION_MAJOR_ITANIUM 0
#	define XIEITE_ARCHITECTURE_VERSION_MINOR_ITANIUM 0
#	define XIEITE_ARCHITECTURE_VERSION_PATCH_ITANIUM 0
#	define XIEITE_ARCHITECTURE_VERSION_MAJOR_MIPS 0
#	define XIEITE_ARCHITECTURE_VERSION_MINOR_MIPS 0
#	define XIEITE_ARCHITECTURE_VERSION_PATCH_MIPS 0
#	define XIEITE_ARCHITECTURE_VERSION_MAJOR_MOTOROLA_68000 0
#	define XIEITE_ARCHITECTURE_VERSION_MINOR_MOTOROLA_68000 0
#	define XIEITE_ARCHITECTURE_VERSION_PATCH_MOTOROLA_68000 0
#	define XIEITE_ARCHITECTURE_VERSION_MAJOR_PA_RISC 0
#	define XIEITE_ARCHITECTURE_VERSION_MINOR_PA_RISC 0
#	define XIEITE_ARCHITECTURE_VERSION_PATCH_PA_RISC 0
#	define XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC 0
#	define XIEITE_ARCHITECTURE_VERSION_MINOR_POWERPC 0
#	define XIEITE_ARCHITECTURE_VERSION_PATCH_POWERPC 0
#	define XIEITE_ARCHITECTURE_VERSION_MAJOR_PYRAMID_9810 0
#	define XIEITE_ARCHITECTURE_VERSION_MINOR_PYRAMID_9810 0
#	define XIEITE_ARCHITECTURE_VERSION_PATCH_PYRAMID_9810 0
#	define XIEITE_ARCHITECTURE_VERSION_MAJOR_RS_6000 0
#	define XIEITE_ARCHITECTURE_VERSION_MINOR_RS_6000 0
#	define XIEITE_ARCHITECTURE_VERSION_PATCH_RS_6000 0
#	define XIEITE_ARCHITECTURE_VERSION_MAJOR_SPARC 0
#	define XIEITE_ARCHITECTURE_VERSION_MINOR_SPARC 0
#	define XIEITE_ARCHITECTURE_VERSION_PATCH_SPARC 0
#	define XIEITE_ARCHITECTURE_VERSION_MAJOR_SUPERH 0
#	define XIEITE_ARCHITECTURE_VERSION_MINOR_SUPERH 0
#	define XIEITE_ARCHITECTURE_VERSION_PATCH_SUPERH 0
#	define XIEITE_ARCHITECTURE_VERSION_MAJOR_TMS320 0
#	define XIEITE_ARCHITECTURE_VERSION_MINOR_TMS320 0
#	define XIEITE_ARCHITECTURE_VERSION_PATCH_TMS320 0
#	define XIEITE_ARCHITECTURE_VERSION_MAJOR_TMS470 0
#	define XIEITE_ARCHITECTURE_VERSION_MINOR_TMS470 0
#	define XIEITE_ARCHITECTURE_VERSION_PATCH_TMS470 0
#	define XIEITE_ARCHITECTURE_VERSION_MAJOR_X86_32 0
#	define XIEITE_ARCHITECTURE_VERSION_MINOR_X86_32 0
#	define XIEITE_ARCHITECTURE_VERSION_PATCH_X86_32 0
#	define XIEITE_ARCHITECTURE_VERSION_MAJOR_X86_64 0
#	define XIEITE_ARCHITECTURE_VERSION_MINOR_X86_64 0
#	define XIEITE_ARCHITECTURE_VERSION_PATCH_X86_64 0
#	define XIEITE_ARCHITECTURE_VERSION_MAJOR_Z 0
#	define XIEITE_ARCHITECTURE_VERSION_MINOR_Z 0
#	define XIEITE_ARCHITECTURE_VERSION_PATCH_Z 0

#	define XIEITE_ARCHITECTURE_VERSION_LEAST(architecture, major, minor, patch) (XIEITE_ARCHITECTURE_TYPE_##architecture && ((XIEITE_ARCHITECTURE_VERSION_MAJOR_##architecture > (major)) || (XIEITE_ARCHITECTURE_VERSION_MAJOR_##architecture == (major)) && ((XIEITE_ARCHITECTURE_VERSION_MINOR_##architecture > (minor)) || (XIEITE_ARCHITECTURE_VERSION_MINOR_##architecture == (minor)) && (XIEITE_ARCHITECTURE_VERSION_PATCH_##architecture >= (patch)))))
#	define XIEITE_ARCHITECTURE_VERSION_MOST(architecture, major, minor, patch) (XIEITE_ARCHITECTURE_TYPE_##architecture && ((XIEITE_ARCHITECTURE_VERSION_MAJOR_##architecture < (major)) || (XIEITE_ARCHITECTURE_VERSION_MAJOR_##architecture == (major)) && ((XIEITE_ARCHITECTURE_VERSION_MINOR_##architecture < (minor)) || (XIEITE_ARCHITECTURE_VERSION_MINOR_##architecture == (minor)) && (XIEITE_ARCHITECTURE_VERSION_PATCH_##architecture <= (patch)))))

#	ifdef __aarch64__
#		undef XIEITE_ARCHITECTURE_TYPE_AARCH64
#		define XIEITE_ARCHITECTURE_TYPE_AARCH64 1
#	endif

#	if defined(__alpha__) || defined(__alpha) || defined(_M_ALPHA)
#		undef XIEITE_ARCHITECTURE_TYPE_ALPHA
#		define XIEITE_ARCHITECTURE_TYPE_ALPHA 1

#		ifdef __alpha_ev4__
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_ALPHA
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_ALPHA 4
#		endif

#		ifdef __alpha_ev5__
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_ALPHA
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_ALPHA 5
#		endif

#		ifdef __alpha_ev6__
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_ALPHA
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_ALPHA 6
#		endif

#		ifdef __alpha_ev7__
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_ALPHA
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_ALPHA 7
#		endif
#	endif

#	if defined(__arm__) || defined(__thumb__) || defined(__TARGET_ARCH_ARM) || defined(__TARGET_ARCH_THUMB) || defined(_ARM) || defined(_M_ARM) || defined(_ARMT) || defined(__arm)
#		undef XIEITE_ARCHITECTURE_TYPE_ARM
#		define XIEITE_ARCHITECTURE_TYPE_ARM 1

#		ifdef __ARM_ARCH_2__
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_ARM
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_ARM 2
#		endif

#		if defined(__ARM_ARCH_3__) || defined(__ARM_ARCH_3M__)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_ARM
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_ARM 3
#		endif

#		if defined(__ARM_ARCH_4T__) || defined(__TARGET_ARM_4T)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_ARM
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_ARM 4
#		endif

#		if defined(__ARM_ARCH_5__) || defined(__ARM_ARCH_5E__) || defined(__ARM_ARCH_5T__) || defined(__ARM_ARCH_5TE__) || defined(__ARM_ARCH_5TEJ__)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_ARM
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_ARM 5
#		endif

#		if defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__) || defined(__ARM_ARCH_6T2__)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_ARM
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_ARM 6
#		endif

#		if defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7S__)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_ARM
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_ARM 7
#		endif
#	endif

#	if defined(__bfin) || defined(__BFIN__)
#		undef XIEITE_ARCHITECTURE_TYPE_BLACKFIN
#		define XIEITE_ARCHITECTURE_TYPE_BLACKFIN 1
#	endif

#	ifdef __convex__
#		undef XIEITE_ARCHITECTURE_TYPE_CONVEX
#		define XIEITE_ARCHITECTURE_TYPE_CONVEX 1

#		ifdef __convex_c1__
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_CONVEX
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_CONVEX 1
#		endif

#		ifdef __convex_c2__
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_CONVEX
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_CONVEX 2
#		endif

#		ifdef __convex_c32__
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_CONVEX
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_CONVEX 32
#		endif

#		ifdef __convex_c34__
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_CONVEX
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_CONVEX 34
#		endif

#		ifdef __convex_c38__
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_CONVEX
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_CONVEX 38
#		endif
#	endif

#	ifdef __epiphany__
#		undef XIEITE_ARCHITECTURE_TYPE_EPIPHANY
#		define XIEITE_ARCHITECTURE_TYPE_EPIPHANY 1
#	endif

#	if defined(__ia64__) || defined(_IA64) || defined(__IA64__) || defined(__ia64) || defined(_M_IA64) || defined(__itanium__)
#		undef XIEITE_ARCHITECTURE_TYPE_ITANIUM
#		define XIEITE_ARCHITECTURE_TYPE_ITANIUM 1

#		undef XIEITE_ARCHITECTURE_VERSION_MAJOR_ITANIUM
#		define XIEITE_ARCHITECTURE_VERSION_MAJOR_ITANIUM (_M_IA64 % 64000 / 100)

#		undef XIEITE_ARCHITECTURE_VERSION_MINOR_ITANIUM
#		define XIEITE_ARCHITECTURE_VERSION_MINOR_ITANIUM (_M_IA64 % 100)
#	endif

#	if defined(__mips__) || defined(mips) || defined(__mips) || defined(__MIPS__)
#		undef XIEITE_ARCHITECTURE_TYPE_MIPS
#		define XIEITE_ARCHITECTURE_TYPE_MIPS 1

#		if defined(_MIPS_ISA) && (_MIPS_ISA == _MIPS_ISA_MIPS1) || defined(__mips) && (__mips == 1)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_MIPS
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_MIPS 1
#		endif

#		if defined(_MIPS_ISA) && (_MIPS_ISA == _MIPS_ISA_MIPS2) || defined(__mips) && (__mips == 2) || defined(__MIPS_ISA2__) || defined(_R3000)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_MIPS
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_MIPS 2
#		endif

#		if defined(_MIPS_ISA) && (_MIPS_ISA == _MIPS_ISA_MIPS3) || defined(__mips) && (__mips == 3) || defined(__MIPS_ISA3__) || defined(_R4000)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_MIPS
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_MIPS 3
#		endif

#		if defined(_MIPS_ISA) && (_MIPS_ISA == _MIPS_ISA_MIPS4) || defined(__mips) && (__mips == 4) || defined(__MIPS_ISA4__)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_MIPS
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_MIPS 4
#		endif

#		if defined(_MIPS_ISA) && (_MIPS_ISA == _MIPS_ISA_MIPS5) || defined(__mips) && (__mips == 5) || defined(__MIPS_ISA5__)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_MIPS
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_MIPS 5
#		endif

#		if defined(_MIPS_ISA) && (_MIPS_ISA == _MIPS_ISA_MIPS32) || defined(__mips) && (__mips == 32) || defined(__MIPS_ISA6__)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_MIPS
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_MIPS 6
#		endif

#		if defined(_MIPS_ISA) && (_MIPS_ISA == _MIPS_ISA_MIPS64) || defined(__mips) && (__mips == 64)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_MIPS
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_MIPS 7
#		endif
#	endif

#	if defined(__m68k__) || defined(M68000) || defined(__MC68K__)
#		undef XIEITE_ARCHITECTURE_TYPE_MOTOROLA_68000
#		define XIEITE_ARCHITECTURE_TYPE_MOTOROLA_68000 1

#		if defined(__mc68000__) || defined(__mc68000) || defined(mc68000) || defined(__MC68000__) || defined(__mc68010__) || defined(__mc68010) || defined(mc68010) || defined(__MC68010__)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_MOTOROLA_68000
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_MOTOROLA_68000 1
#		endif

#		if defined(__mc68020__) || defined(__mc68020) || defined(mc68020) || defined(__MC68020__) || defined(__mc68030__) || defined(__mc68030) || defined(mc68030) || defined(__MC68030__)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_MOTOROLA_68000
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_MOTOROLA_68000 2
#		endif

#		if defined(__mc68040__) || defined(__mc68040) || defined(mc68040) || defined(__MC68040__)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_MOTOROLA_68000
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_MOTOROLA_68000 3
#		endif

#		if defined(__mc68060__) || defined(__mc68060) || defined(mc68060) || defined(__MC68060__)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_MOTOROLA_68000
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_MOTOROLA_68000 4
#		endif
#	endif

#	if defined(__hppa__) || defined(__HPPA__) || defined(__hppa)
#		undef XIEITE_ARCHITECTURE_TYPE_PA_RISC
#		define XIEITE_ARCHITECTURE_TYPE_PA_RISC 1

#		ifdef _PA_RISC1_0
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_PA_RISC
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_PA_RISC 1
#		endif

#		if defined(_PA_RISC1_1) || defined(__HPPA11__) || defined(__PA7100__)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_PA_RISC
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_PA_RISC 1

#			undef XIEITE_ARCHITECTURE_VERSION_MINOR_PA_RISC
#			define XIEITE_ARCHITECTURE_VERSION_MINOR_PA_RISC 1
#		endif

#		if defined(_PA_RISC2_0) || defined(__RISC2_0__) || defined(__HPPA20__) || defined(__PA8000__)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_PA_RISC
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_PA_RISC 2
#		endif
#	endif

#	if defined(__powerpc) || defined(__powerpc__) || defined(__powerpc64__) || defined(__POWERPC__) || defined(__ppc__) || defined(__ppc64__) || defined(__PPC__) || defined(__PPC64__) || defined(_ARCH_PPC) || defined(_ARCH_PPC64) || defined(_M_PPC) || defined(__ppc)
#		undef XIEITE_ARCHITECTURE_TYPE_POWERPC
#		define XIEITE_ARCHITECTURE_TYPE_POWERPC 1

#		ifdef _ARCH_PWR4
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC 400
#		endif

#		if defined(_ARCH_440) || defined(__ppc440__)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC 440
#		endif

#		if defined(_ARCH_450) || defined(__ppc450__)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC 450
#		endif

#		ifdef _ARCH_PWR5
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC 500
#		endif

#		ifdef _ARCH_PWR6
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC 600
#		endif

#		if defined(_ARCH_601) || defined(__ppc601__)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC 601
#		endif

#		if defined(_ARCH_602) || defined(__ppc602__)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC 602
#		endif

#		if defined(_ARCH_603) || defined(__ppc603__)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC 603
#		endif

#		if defined(_ARCH_604) || defined(__ppc604__)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC 604
#		endif

#		if defined(_ARCH_605) || defined(__ppc605__)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC 605
#		endif

#		if defined(_ARCH_620) || defined(__ppc620__)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC 620
#		endif

#		ifdef _ARCH_PWR7
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC 700
#		endif

#		ifdef _ARCH_PWR8
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC 800
#		endif

#		ifdef _ARCH_PWR9
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_POWERPC 900
#		endif
#	endif

#	ifdef pyr
#		undef XIEITE_ARCHITECTURE_TYPE_PYRAMID_9810
#		define XIEITE_ARCHITECTURE_TYPE_PYRAMID_9810 1
#	endif

#	if defined(__THW_RS6000) || defined(_IBMR2) || defined(_POWER) || defined(_ARCH_PWR) || defined(_ARCH_PWR2) || defined(_ARCH_PWR3) || defined(_ARCH_PWR4)
#		undef XIEITE_ARCHITECTURE_TYPE_RS_6000
#		define XIEITE_ARCHITECTURE_TYPE_RS_6000 1
#	endif

#	if defined(__sparc__) || defined(__sparc)
#		undef XIEITE_ARCHITECTURE_TYPE_SPARC
#		define XIEITE_ARCHITECTURE_TYPE_SPARC 1

#		if defined(__sparc_v1__) || defined(__sparcv1)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_SPARC
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_SPARC 1
#		endif

#		if defined(__sparc_v2__) || defined(__sparcv2)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_SPARC
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_SPARC 2
#		endif

#		if defined(__sparc_v3__) || defined(__sparcv3)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_SPARC
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_SPARC 3
#		endif

#		if defined(__sparc_v4__) || defined(__sparcv4)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_SPARC
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_SPARC 4
#		endif

#		if defined(__sparc_v5__) || defined(__sparcv5)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_SPARC
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_SPARC 5
#		endif

#		if defined(__sparc_v6__) || defined(__sparcv6)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_SPARC
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_SPARC 6
#		endif

#		if defined(__sparc_v7__) || defined(__sparcv7)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_SPARC
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_SPARC 7
#		endif

#		if defined(__sparc_v8__) || defined(__sparcv8)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_SPARC
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_SPARC 8
#		endif

#		if defined(__sparc_v9__) || defined(__sparcv9)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_SPARC
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_SPARC 9
#		endif
#	endif

#	ifdef __sh__
#		undef XIEITE_ARCHITECTURE_TYPE_SUPERH
#		define XIEITE_ARCHITECTURE_TYPE_SUPERH 1

#		if defined(__sh1__) || defined(__SH1__)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_SUPERH
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_SUPERH 1
#		endif

#		if defined(__sh2__) || defined(__SH2__)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_SUPERH
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_SUPERH 2
#		endif

#		if defined(__sh3__) || defined(__SH3__)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_SUPERH
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_SUPERH 3
#		endif

#		if defined(__sh4__) || defined(__SH4__)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_SUPERH
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_SUPERH 4
#		endif

#		if defined(__sh5__) || defined(__SH5__)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_SUPERH
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_SUPERH 5
#		endif
#	endif

#	if defined(_TMS320C2XX) || defined(__TMS320C2000__) || defined(_TMS320C5X) || defined(__TMS320C55X__) || defined(_TMS320C6X) || defined(__TMS320C6X__)
#		undef XIEITE_ARCHITECTURE_TYPE_TMS320
#		define XIEITE_ARCHITECTURE_TYPE_TMS320 1

#		ifdef _TMS320C28X
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_TMS320
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_TMS320 2800
#		endif

#		ifdef _TMS320C5XX
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_TMS320
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_TMS320 5400
#		endif

#		ifdef __TMS320C55X__
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_TMS320
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_TMS320 5500
#		endif

#		ifdef _TMS320C6200
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_TMS320
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_TMS320 6200
#		endif

#		ifdef _TMS320C6400
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_TMS320
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_TMS320 6400
#		endif

#		ifdef _TMS320C6400_PLUS
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_TMS320
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_TMS320 6400

#			undef XIEITE_ARCHITECTURE_VERSION_MINOR_TMS320
#			define XIEITE_ARCHITECTURE_VERSION_MINOR_TMS320 1
#		endif

#		ifdef _TMS320C6600
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_TMS320
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_TMS320 6600
#		endif

#		ifdef _TMS320C6700
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_TMS320
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_TMS320 6700
#		endif

#		ifdef _TMS320C6700_PLUS
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_TMS320
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_TMS320 6700

#			undef XIEITE_ARCHITECTURE_VERSION_MINOR_TMS320
#			define XIEITE_ARCHITECTURE_VERSION_MINOR_TMS320 1
#		endif

#		ifdef _TMS320C6740
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_TMS320
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_TMS320 6740
#		endif

#	endif

#	ifdef __TMS470__
#		undef XIEITE_ARCHITECTURE_TYPE_TMS470
#		define XIEITE_ARCHITECTURE_TYPE_TMS470 1
#	endif

#	if defined(i386) || defined(__i386) || defined(__i386__) || defined(__IA32__) || defined(_M_I86) || defined(_M_IX86) || defined(__X86__) || defined(_X86_) || defined(__THW_INTEL__) || defined(__I86__) || defined(__INTEL__) || defined(__386)
#		undef XIEITE_ARCHITECTURE_TYPE_X86_32
#		define XIEITE_ARCHITECTURE_TYPE_X86_32 1

#		if defined(__i386__) || defined(_M_IX86) && (_M_IX86 == 300) || defined(__I86__) && (__I86__ == 3)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_X86_32
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_X86_32 3
#		endif

#		if defined(__i486__) || defined(_M_IX86) && (_M_IX86 == 400) || defined(__I86__) && (__I86__ == 4)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_X86_32
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_X86_32 4
#		endif

#		if defined(__i586__) || defined(_M_IX86) && (_M_IX86 == 500) || defined(__I86__) && (__I86__ == 5)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_X86_32
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_X86_32 5
#		endif

#		if defined(__i686__) || defined(_M_IX86) && (_M_IX86 == 600) || defined(__I86__) && (__I86__ == 6)
#			undef XIEITE_ARCHITECTURE_VERSION_MAJOR_X86_32
#			define XIEITE_ARCHITECTURE_VERSION_MAJOR_X86_32 6
#		endif
#	endif

#	if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_AMD64)
#		undef XIEITE_ARCHITECTURE_TYPE_X86_64
#		define XIEITE_ARCHITECTURE_TYPE_X86_64 1
#	endif

#	if defined(__370__) || defined(__THW_370__) || defined(__s390__) || defined(__s390x__) || defined(__zarch__) || defined(__SYSC_ZARCH__)
#		undef XIEITE_ARCHITECTURE_TYPE_Z
#		define XIEITE_ARCHITECTURE_TYPE_Z 1
#	endif
#endif

// https://sourceforge.net/p/predef/wiki/Architectures/
