#pragma once

#include <type_traits>
#include "../concepts/arithmetic.hpp"
#include "../math/difference.hpp"

namespace xieite::math {
	template<xieite::concepts::Arithmetic Arithmetic>
	[[nodiscard]] constexpr Arithmetic farthestFrom(const Arithmetic target, std::type_identity_t<Arithmetic> value1, std::type_identity_t<Arithmetic> value2) noexcept {
		return (xieite::math::difference(target, value1) < xieite::math::difference(target, value2)) ? value2 : value1;
	}
}
