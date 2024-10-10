#pragma once

#include "../math/exponent.hpp"

namespace xieite::literals::exponent {
	[[nodiscard]] constexpr auto operator""_exponent(const unsigned long long int value) noexcept {
		return xieite::math::Exponent(value);
	}

	[[nodiscard]] constexpr auto operator""_exponent(const long double value) noexcept {
		return xieite::math::Exponent(value);
	}
}
