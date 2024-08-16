#ifndef XIEITE_HEADER_MATH_IS_BETWEEN_MAGNITUDE
#	define XIEITE_HEADER_MATH_IS_BETWEEN_MAGNITUDE

#	include "../concepts/arithmetic.hpp"
#	include "../math/closest_to.hpp"

namespace xieite::math {
	template<xieite::concepts::Arithmetic Arithmetic>
	[[nodiscard]] constexpr bool isBetweenMagnitude(const Arithmetic value, const Arithmetic limit1, const Arithmetic limit2, const bool downInclusive = true, const bool upInclusive = true) noexcept {
		const Arithmetic down = xieite::math::closestTo(static_cast<Arithmetic>(0), limit1, limit2);
		const Arithmetic up = (down == limit1) ? limit2 : limit1;
		return (downInclusive ? (value >= down) : (value > down)) && (upInclusive ? (value <= up) : (value < up)) || (downInclusive ? (value <= down) : (value < down)) && (upInclusive ? (value >= up) : (value > up));
	}
}

#endif
