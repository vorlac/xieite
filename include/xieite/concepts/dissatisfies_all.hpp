#pragma once

#include "../concepts/satisfies_all.hpp"

namespace xieite::concepts {
	template<typename Type, auto... validators>
	concept DissatisfiesAll = !xieite::concepts::SatisfiesAll<Type, validators...>;
}
