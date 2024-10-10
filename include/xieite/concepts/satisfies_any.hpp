#pragma once

#include "../concepts/satisfies.hpp"

namespace xieite::concepts {
	template<typename Type, auto... validators>
	concept SatisfiesAny = (... || xieite::concepts::Satisfies<Type, validators>);
}
