#pragma once

#include <type_traits>

namespace xieite::concepts {
	template<typename Type>
	concept RightValueReference = std::is_rvalue_reference_v<Type>;
}
