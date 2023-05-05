#pragma once

#include <limits>
#include <cstdint>

namespace xieite::graphics {
	struct Color final {
		std::uint8_t red;
		std::uint8_t green;
		std::uint8_t blue;
		std::uint8_t alpha;

		constexpr Color(const std::uint8_t red, const std::uint8_t green, const std::uint8_t blue, const std::uint8_t alpha = std::numeric_limits<std::uint8_t>::max()) noexcept
		: red(red), green(green), blue(blue), alpha(alpha) {}

		constexpr Color(const std::uint32_t value) noexcept
		: red(value >> (3 * std::numeric_limits<std::uint8_t>::digits)), green(value >> (2 * std::numeric_limits<std::uint8_t>::digits) & std::numeric_limits<std::uint8_t>::max()), blue(value >> std::numeric_limits<std::uint8_t>::digits & std::numeric_limits<std::uint8_t>::max()), alpha(value & std::numeric_limits<std::uint8_t>::max()) {}

		constexpr bool operator==(const xieite::graphics::Color& color) const noexcept {
			return (this->red == color.red) && (this->green == color.green) && (this->blue == color.blue) && (this->alpha == color.alpha);
		}

		constexpr std::uint32_t value() noexcept {
			return (this->red << (3 * std::numeric_limits<std::uint8_t>::digits)) + (this->green << (2 * std::numeric_limits<std::uint8_t>::digits)) + (this->blue << std::numeric_limits<std::uint8_t>::digits) + this->alpha;
		}
	};
}
