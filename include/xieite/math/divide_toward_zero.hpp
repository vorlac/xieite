#pragma once

#include <cmath>
#include <concepts>
#include <type_traits>
#include "../concepts/arithmetic.hpp"

namespace xieite::math {
	template<xieite::concepts::Arithmetic Arithmetic>
	[[nodiscard]] constexpr Arithmetic divideTowardZero(const Arithmetic dividend, const std::type_identity_t<Arithmetic> divisor) noexcept {
		if constexpr (std::floating_point<Arithmetic>) {
			return std::floor(dividend / divisor) + ((dividend < 0) != (divisor < 0));
		} else {
			return dividend / divisor;
		}
	}
}
