#pragma once

#include <type_traits>

namespace xieite::types {
	template<auto value>
	using Value = std::integral_constant<decltype(value), value>;
}
