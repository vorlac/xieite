#pragma once

#include "../concepts/base_of.hpp"

namespace xieite::concepts {
	template<typename Base, typename... Derived>
	concept BaseOfAny = (... || xieite::concepts::BaseOf<Base, Derived>);
}
