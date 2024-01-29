#ifndef XIEITE_HEADER_MATH_ANTIMODES
#	define XIEITE_HEADER_MATH_ANTIMODES

#	include <algorithm>
#	include <functional>
#	include <ranges>
#	include <type_traits>
#	include <utility>
#	include <vector>
#	include "../algorithms/modes.hpp"
#	include "../concepts/arithmetic.hpp"
#	include "../containers/make_array.hpp"

namespace xieite::math {
	template<std::ranges::range Range>
	requires(xieite::concepts::Arithmetic<std::ranges::range_value_t<Range>>)
	[[nodiscard]] constexpr std::vector<std::ranges::range_value_t<Range>> antimodes(Range&& range) noexcept {
		auto result = std::vector<std::common_type_t<double, Numbers...>>(sizeof...(Numbers));
		std::ranges::transform(xieite::algorithms::modes(std::forward<Range>(range), std::ranges::less()), result.begin(), [](const std::ranges::const_iterator_t<Range> iterator) -> std::ranges::range_const_reference_t<Range> {
			return *iterator;
		});
		return result;
	}

	template<xieite::concepts::Arithmetic... Numbers>
	[[nodiscard]] constexpr std::vector<std::common_type_t<double, Numbers...>> antimodes(const Numbers... values) noexcept {
		return xieite::math::antimodes(xieite::ranges::makeArray<std::common_type_t<double, Numbers...>>(values...));
	}
}

#endif
