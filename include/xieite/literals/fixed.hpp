#pragma once

#include "../containers/fixed_string.hpp"

namespace xieite::literals::fixed {
	template<xieite::containers::FixedString string>
	[[nodiscard]] constexpr auto operator""_fixed() noexcept {
		return string;
	}
}
