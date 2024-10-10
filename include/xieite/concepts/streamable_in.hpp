#pragma once

#include <concepts>
#include <istream>

namespace xieite::concepts {
	template<typename Type>
	concept StreamableIn = requires(Type value, std::istream inputStream) {
		{ inputStream >> value } -> std::convertible_to<std::istream&>;
	};
}
