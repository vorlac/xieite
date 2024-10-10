#pragma once

#include <type_traits>
#include "../concepts/arithmetic.hpp"
#include "../math/divide_toward_infinity.hpp"

namespace xieite::math {
	template<xieite::concepts::Arithmetic Arithmetic>
	[[nodiscard]] constexpr Arithmetic roundTowardInfinity(const Arithmetic value, const std::type_identity_t<Arithmetic> step = 1) noexcept {
		return xieite::math::divideTowardInfinity(value, step) * step;
	}
}
