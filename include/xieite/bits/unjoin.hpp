#ifndef XIEITE_HEADER_BITS_UNJOIN
#	define XIEITE_HAEDER_BITS_UNJOIN

#	include <array>
#	include <bitset>
#	include <concepts>
#	include <cstddef>
#	include <tuple>
#	include <utility>
#	include "../bits/size.hpp"

namespace xieite::bits {
	template<std::integral... Integrals, std::size_t bits>
	requires(bits >= (... + xieite::bits::size<Integrals>))
	[[nodiscard]] constexpr std::tuple<Integrals...> unjoin(std::bitset<bits> value) noexcept {
		std::tuple<Integrals...> result;
		([&value, &result]<std::size_t... i>(std::index_sequence<i...>) -> void {
			(..., ([&value, &result] -> void {
				std::get<i>(result) = static_cast<Integrals>(value.to_ullong());
				value >>= xieite::bits::size<Integrals>;
			})());
		})(std::make_index_sequence<sizeof...(Integrals)>());
		return result;
	}

	template<std::integral Integral, std::size_t size, std::size_t bits>
	requires(bits >= (xieite::bits::size<Integral> * size))
	[[nodiscard]] constexpr std::array<Integral, size> unjoin(std::bitset<bits> value) noexcept {
		std::array<Integral, size> result;
		for (std::size_t i = 0; i < size; ++i) {
			result[i] = static_cast<Integral>(value.to_ullong());
			value >>= xieite::bits::size<Integral>;
		}
		return result;
	}
}

#endif
