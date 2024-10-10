#pragma once

#include "../concepts/satisfied_by.hpp"

namespace xieite::concepts {
	template<auto validator, typename... Types>
	concept SatisfiedByAll = (... && xieite::concepts::SatisfiedBy<validator, Types>);
}
