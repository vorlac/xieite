#pragma once

#include <cstddef>
#include <string_view>
#include "../math/sign_cast.hpp"

namespace xieite::hashes {
	[[nodiscard]] constexpr std::size_t djb2(const std::string_view value) noexcept {
		std::size_t result = 5381;
		for (const char character : value) {
			result = result * 33 + xieite::math::signCast<std::size_t>(character);
		}
		return result;
	}
}
