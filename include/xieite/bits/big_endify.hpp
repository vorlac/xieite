#pragma once

#include <bit>
#include <concepts>

namespace xieite::bits {
	template<std::integral Integral>
	[[nodiscard]] constexpr Integral bigEndify(const Integral value) noexcept {
		return (std::endian::native == std::endian::little) ? std::byteswap(value) : value;
	}
}
