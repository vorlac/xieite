#pragma once

#include <type_traits>

namespace xieite::concepts {
	template<typename Type>
	concept CopyConstructible = std::is_copy_constructible_v<Type>;
}
