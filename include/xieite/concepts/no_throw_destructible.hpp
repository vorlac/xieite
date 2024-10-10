#pragma once

#include <type_traits>

namespace xieite::concepts {
	template<typename Type>
	concept NoThrowDestructible = std::is_nothrow_destructible_v<Type>;
}
