module;

#include "../macros/compiler.hpp"

#if XIEITE_COMPILER_TYPE_MSVC
#	include <__msvc_int128.hpp>
#elif !XIEITE_COMPILER_TYPE_GCC && !XIEITE_COMPILER_TYPE_CLANG
#	warning "Compiler not supported"
#endif

export module xieite:math.Signed128;

export namespace xieite::math {
#if XIEITE_COMPILER_TYPE_MSVC
	using Signed128 = std::_Signed128;
#else
	using Signed128 = __int128;
#endif
}
