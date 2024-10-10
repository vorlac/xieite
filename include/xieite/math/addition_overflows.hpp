#pragma once

#include <concepts>
#include <limits>
#include "../concepts/arithmetic.hpp"
#include "../math/is_negative.hpp"

namespace xieite::math {
	template<xieite::concepts::Arithmetic First, std::convertible_to<First>... Rest>
	[[nodiscard]] constexpr bool additionOverflows(First first, const Rest... rest) noexcept {
		return first && (... || ([&first, rest] {
			if (rest && (xieite::math::isNegative(first) ? ((std::numeric_limits<First>::min() - first) > rest) : ((std::numeric_limits<First>::max() - first) < rest))) {
				return true;
			}
			first += static_cast<First>(rest);
			return false;
		})());
	}
}
