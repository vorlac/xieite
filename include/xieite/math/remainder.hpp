#pragma once

#include <cmath>
#include <concepts>
#include <type_traits>
#include "../concepts/arithmetic.hpp"

namespace xieite::math {
	template<xieite::concepts::Arithmetic Arithmetic>
	[[nodiscard]] constexpr Arithmetic remainder(const Arithmetic dividend, const std::type_identity_t<Arithmetic> divisor) noexcept {
		if constexpr (std::floating_point<Arithmetic>) {
			return std::fmod(dividend, divisor);
		} else {
			return dividend % divisor;
		}
	}
}
