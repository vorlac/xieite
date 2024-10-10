#pragma once

#include <type_traits>

namespace xieite::concepts {
	template<typename Type>
	concept DefaultConstructible = std::is_default_constructible_v<Type>;
}
