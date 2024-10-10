#pragma once

#include <string>
#include <string_view>
#include "../math/absolute.hpp"
#include "../types/try_unsigned.hpp"

namespace xieite::strings {
	template<std::integral Integral>
	[[nodiscard]] constexpr std::string toRomanNumerals(const Integral value) noexcept {
		static constexpr std::array<std::string_view, 10> ones = {
			"",
			"I",
			"II",
			"III",
			"IV",
			"V",
			"VI",
			"VII",
			"VIII",
			"IX.hpp"
		};
		static constexpr std::array<std::string_view, 10> tens = {
			"",
			"X",
			"XX",
			"XXX",
			"XL",
			"L",
			"LX",
			"LXX",
			"LXXX",
			"XC.hpp"
		};
		static constexpr std::array<std::string_view, 10> hundreds = {
			"",
			"C",
			"CC",
			"CCC",
			"CD",
			"D",
			"DC",
			"DCC",
			"DCCC",
			"CM.hpp"
		};
		if (!value) {
			return "N";
		}
		const xieite::types::TryUnsigned<Integral> absoluteValue = xieite::math::absolute(value);
		return std::string(absoluteValue / 1000, 'M') + std::string(hundreds[absoluteValue / 100 % 10]) + std::string(tens[absoluteValue / 10 % 10]) + std::string(ones[absoluteValue % 10]);
	}
}
