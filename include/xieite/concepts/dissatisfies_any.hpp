#pragma once

#include "../concepts/satisfies_any.hpp"

namespace xieite::concepts {
	template<typename Type, auto... validators>
	concept DissatisfiesAny = !xieite::concepts::SatisfiesAny<Type, validators...>;
}
