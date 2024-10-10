#pragma once

#include <concepts>
#include <limits>
#include "../concepts/arithmetic.hpp"
#include "../math/is_negative.hpp"

namespace xieite::math {
	template<xieite::concepts::Arithmetic First, std::convertible_to<First>... Rest>
	[[nodiscard]] constexpr bool subtractionOverflows(First first, const Rest... rest) noexcept {
		return first && (... || ([&first, rest] {
			if (rest && (xieite::math::isNegative(rest) ? ((std::numeric_limits<First>::max() + rest) < first) : ((std::numeric_limits<First>::min() + rest) > first))) {
				return true;
			}
			first -= static_cast<First>(rest);
			return false;
		})());
	}
}
