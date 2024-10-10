#pragma once

#include <type_traits>

namespace xieite::concepts {
	template<typename Type>
	concept Destructible = std::is_destructible_v<Type>;
}
