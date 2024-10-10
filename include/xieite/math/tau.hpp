#pragma once

#include "../concepts/arithmetic.hpp"
#include "../math/pi.hpp"

namespace xieite::math {
	template<xieite::concepts::Arithmetic Arithmetic>
	constexpr Arithmetic tau = xieite::math::pi<Arithmetic> * 2;
}
