#pragma once

#include <concepts>

namespace xieite::math {
	template<std::unsigned_integral UnsignedIntegral>
	struct DoubleInteger {
		UnsignedIntegral lower;
		UnsignedIntegral upper;
	};
}
