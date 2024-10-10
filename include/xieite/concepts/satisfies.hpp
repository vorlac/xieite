#pragma once

#include "../concepts/satisfied_by.hpp"

namespace xieite::concepts {
	template<typename Type, auto validator>
	concept Satisfies = xieite::concepts::SatisfiedBy<validator, Type>;
}
