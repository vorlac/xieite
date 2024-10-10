#pragma once

#include <type_traits>

namespace xieite::concepts {
	template<typename Type>
	concept LeftValueReference = std::is_lvalue_reference_v<Type>;
}
