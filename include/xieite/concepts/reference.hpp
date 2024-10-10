#pragma once

#include <type_traits>

namespace xieite::concepts {
	template<typename Type>
	concept Reference = std::is_reference_v<Type>;
}
