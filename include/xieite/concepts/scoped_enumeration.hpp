#pragma once

#include <type_traits>

namespace xieite::concepts {
	template<typename Type>
	concept ScopedEnumeration = std::is_scoped_enum_v<Type>;
}
