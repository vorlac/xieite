#pragma once

#include <string_view>
#include "../containers/make_array.hpp"
#include "../preprocessor/compiler.hpp"
#include "../preprocessor/function_signature.hpp"
#include "../strings/after.hpp"
#include "../strings/between.hpp"

namespace XIEITE_DETAIL {
	template<typename _>
	[[nodiscard]] consteval std::string_view getName() noexcept {
		static constexpr auto get = [string = std::string_view(XIEITE_FUNCTION_SIGNATURE)] {
#if XIEITE_COMPILER_TYPE_GCC
			return xieite::strings::between(string, "= ", ';');
#elif XIEITE_COMPILER_TYPE_CLANG
			return xieite::strings::between(string, "= ", ']');
#elif XIEITE_COMPILER_TYPE_WINDOWS
			return xieite::strings::between(xieite::strings::after(string, " __"), '<', ">(");
#endif
		};
		static constexpr auto data = xieite::containers::makeArray<char, get().size()>(get());
		return std::string_view(data.begin(), data.end());
	}
}

namespace xieite::types {
	template<typename Type>
	constexpr std::string_view name = XIEITE_DETAIL::getName<Type>();
}
