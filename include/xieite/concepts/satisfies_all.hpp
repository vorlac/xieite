#pragma once

#include "../concepts/satisfies.hpp"

namespace xieite::concepts {
	template<typename Type, auto... validators>
	concept SatisfiesAll = (... && xieite::concepts::Satisfies<Type, validators>);
}
