#pragma once

#include <type_traits>

namespace xieite::concepts {
	template<typename Type>
	concept Volatile = std::is_volatile_v<std::remove_reference_t<Type>>;
}
