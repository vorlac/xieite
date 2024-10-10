#pragma once

#include "../concepts/satisfied_by_any.hpp"

namespace xieite::concepts {
	template<auto validator, typename... Types>
	concept DissatisfiedByAny = !xieite::concepts::SatisfiedByAny<validator, Types...>;
}
