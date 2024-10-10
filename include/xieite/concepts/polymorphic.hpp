#pragma once

#include <type_traits>

namespace xieite::concepts {
	template<typename Type>
	concept Polymorphic = std::is_polymorphic_v<Type>;
}
