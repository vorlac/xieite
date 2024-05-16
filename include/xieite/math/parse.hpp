#ifndef XIEITE_HEADER_MATH_PARSE
#	define XIEITE_HEADER_MATH_PARSE

#	include <cmath>
#	include <concepts>
#	include <cstddef>
#	include <string_view>
#	include <type_traits>
#	include "../concepts/arithmetic.hpp"
#	include "../concepts/specialization_of.hpp"
#	include "../strings/number_components.hpp"
#	include "../math/signed_size.hpp"
#	include "../math/split_boolean.hpp"

namespace xieite::math {
	template<std::unsigned_integral>
	struct BigInteger;

	template<typename Number_>
	requires(xieite::concepts::Arithmetic<Number_> || xieite::concepts::SpecializationOf<Number_, xieite::math::BigInteger>)
	[[nodiscard]] constexpr Number_ parse(const std::string_view value, const std::conditional_t<std::floating_point<Number_>, xieite::math::SignedSize, Number_> radix = 10, const xieite::strings::NumberComponents components = xieite::strings::NumberComponents()) noexcept {
		if (!radix) {
			return 0;
		}
		const bool negative = components.negatives.contains(value[0]);
		const std::size_t valueSize = value.size();
		if constexpr (std::floating_point<Number_>) {
			Number_ integral = 0;
			Number_ fractional = 0;
			std::size_t point = 0;
			xieite::math::SignedSize power = 0;
			for (std::size_t i = negative || components.positives.contains(value[0]); i < valueSize; ++i) {
				const std::size_t index = components.digits.find(value[i]);
				if (index == std::string_view::npos) {
					if (components.points.contains(value[i])) {
						if (point) {
							break;
						}
						point = 1;
					} else if (components.exponents.contains(value[i])) {
						power = xieite::math::parse<xieite::math::SignedSize>(value.substr(i + 1));
						break;
					}
					continue;
				}
				Number_& part = (point ? fractional : integral);
				part = part * static_cast<Number_>(radix) + static_cast<Number_>(index);
				point += !!point;
			}
			return xieite::math::splitBoolean(!negative) * (integral + fractional / std::pow(radix, point - 1)) * std::pow(radix, power);
		} else {
			Number_ result = 0;
			xieite::math::SignedSize power = 0;
			for (std::size_t i = negative || components.positives.contains(value[0]); i < valueSize; ++i) {
				const std::size_t index = components.digits.find(value[i]);
				if (index == std::string_view::npos) {
					break;
				}
				result = result * radix + static_cast<Number_>(index);
			}
			return negative ? -result : result;
		}
	}
}

#endif
