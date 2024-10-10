#pragma once

#include <type_traits>

namespace xieite::concepts {
	template<typename Type>
	concept TriviallyDestructible = std::is_trivially_destructible_v<Type>;
}
