#pragma once

#include <cmath>
#include <concepts>
#include <type_traits>
#include "../concepts/arithmetic.hpp"
#include "../math/sign.hpp"

namespace xieite::math {
	template<xieite::concepts::Arithmetic Arithmetic>
	[[nodiscard]] constexpr Arithmetic divideTowardInfinity(const Arithmetic dividend, const std::type_identity_t<Arithmetic> divisor) noexcept {
		if constexpr (std::floating_point<Arithmetic>) {
			return std::ceil(dividend / divisor) - ((dividend < 0) != (divisor < 0));
		} else {
			return static_cast<Arithmetic>(dividend / divisor + !!(dividend % divisor) * xieite::math::sign(dividend, divisor));
		}
	}
}
