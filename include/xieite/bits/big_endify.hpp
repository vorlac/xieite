#ifndef XIEITE_HEADER_BITS_BIG_ENDIFY
#	define XIEITE_HEADER_BITS_BIG_ENDIFY

#	include <bit>
#	include <concepts>
#	include "../system/endian.hpp"

namespace xieite::bits {
	template<std::integral Integral>
	[[nodiscard]] constexpr Integral bigEndify(const Integral value) noexcept {
		return xieite::system::endian::little ? std::byteswap(value) : value;
	}
}

#endif
