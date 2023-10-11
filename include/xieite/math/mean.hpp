#ifndef XIEITE_HEADER_MATH_MEAN
#	define XIEITE_HEADER_MATH_MEAN

#	include "../concepts/numeric.hpp"
#	include "../math/result.hpp"

namespace xieite::math {
	template<xieite::concepts::Numeric... Numbers>
	[[nodiscard]] constexpr xieite::math::Result<Numbers...> mean(const Numbers... values) noexcept {
		if constexpr (sizeof...(Numbers)) {
			return (... + (static_cast<xieite::math::Result<Numbers...>>(values) / sizeof...(Numbers)));
		}
		return 0;
	}
}

#endif
