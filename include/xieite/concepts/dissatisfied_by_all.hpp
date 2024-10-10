#pragma once

#include "../concepts/satisfied_by_all.hpp"

namespace xieite::concepts {
	template<auto validator, typename... Types>
	concept DissatisfiedByAll = !xieite::concepts::SatisfiedByAll<validator, Types...>;
}
