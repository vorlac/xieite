#pragma once

#include <concepts>

namespace xieite::concepts {
	template<typename Type>
	concept Arithmetic = std::integral<Type> || std::floating_point<Type>;
}
