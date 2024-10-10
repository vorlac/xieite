#pragma once

#include <type_traits>
#include "../concepts/arithmetic.hpp"
#include "../math/divide_down.hpp"

namespace xieite::math {
	template<xieite::concepts::Arithmetic Arithmetic>
	[[nodiscard]] constexpr Arithmetic roundDown(const Arithmetic value, const std::type_identity_t<Arithmetic> step = 1) noexcept {
		return xieite::math::divideDown(value, step) * step;
	}
}
