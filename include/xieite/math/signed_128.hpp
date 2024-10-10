#pragma once

#include "../preprocessor/compiler.hpp"

#if XIEITE_COMPILER_TYPE_MSVC
#	include <__msvc_int128.hpp>
#elif !XIEITE_COMPILER_TYPE_GCC && !XIEITE_COMPILER_TYPE_CLANG
#	warning "unsupported compiler.hpp"
#endif

namespace xieite::math {
#if XIEITE_COMPILER_TYPE_MSVC
	using Signed128 = std::_Signed128;
#else
	__extension__ using Signed128 = __int128;
#endif
}
