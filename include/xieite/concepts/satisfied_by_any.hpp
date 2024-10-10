#pragma once

#include "../concepts/satisfied_by.hpp"

namespace xieite::concepts {
	template<auto validator, typename... Types>
	concept SatisfiedByAny = (... || xieite::concepts::SatisfiedBy<validator, Types>);
}
