#pragma once

#include <cmath>
#include <concepts>
#include "../concepts/arithmetic.hpp"
#include "../math/is_negative.hpp"
#include "../types/try_unsigned.hpp"

namespace xieite::math {
	template<xieite::concepts::Arithmetic Arithmetic>
	[[nodiscard]] constexpr xieite::types::TryUnsigned<Arithmetic> absolute(const Arithmetic value) noexcept {
		if constexpr (std::floating_point<Arithmetic>) {
			return std::abs(value);
		} else {
			return xieite::math::isNegative(value)
				? -static_cast<xieite::types::TryUnsigned<Arithmetic>>(value)
				: static_cast<xieite::types::TryUnsigned<Arithmetic>>(value);
		}
	}
}
