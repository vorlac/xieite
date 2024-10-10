#pragma once

#include <concepts>

namespace xieite::concepts {
	template<typename Base, typename Derived>
	concept BaseOf = std::derived_from<Derived, Base>;
}
