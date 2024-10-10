#pragma once

#include <concepts>
#include <cstddef>

namespace xieite::bits {
	template<std::integral Integral>
	[[nodiscard]] constexpr Integral xorShift(const Integral value, const std::size_t bits) noexcept {
		return value ^ (value >> bits);
	}
}
