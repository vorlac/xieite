#pragma once

#include <bit>
#include <concepts>

namespace xieite::bits {
	template<std::integral Integral>
	[[nodiscard]] constexpr Integral littleEndify(const Integral value) noexcept {
		return (std::endian::native == std::endian::big) ? std::byteswap(value) : value;
	}
}
