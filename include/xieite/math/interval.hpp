#pragma once

#include "../concepts/arithmetic.hpp"

namespace xieite::math {
	template<xieite::concepts::Arithmetic Arithmetic>
	struct Interval {
		Arithmetic start;
		Arithmetic end;
	};
}
