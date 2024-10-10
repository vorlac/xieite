#pragma once

#include <cmath>
#include <type_traits>
#include "../concepts/arithmetic.hpp"
#include "../math/almost_equal.hpp"

namespace xieite::math {
	template<xieite::concepts::Arithmetic Arithmetic>
	[[nodiscard]] constexpr bool almostEqualSlope(const Arithmetic value1, const std::type_identity_t<Arithmetic> value2) noexcept {
		return (std::isinf(value1) && std::isinf(value2)) || xieite::math::almostEqual(value1, value2);
	}

	template<xieite::concepts::Arithmetic Arithmetic>
	[[nodiscard]] constexpr bool almostEqualSlope(const Arithmetic value1, const std::type_identity_t<Arithmetic> value2, const std::type_identity_t<Arithmetic> epsilon) noexcept {
		return (std::isinf(value1) && std::isinf(value2)) || xieite::math::almostEqual(value1, value2, epsilon);
	}
}
