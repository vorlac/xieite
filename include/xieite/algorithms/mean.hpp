#pragma once

#include <ranges>
#include <type_traits>
#include "../concepts/arithmetic.hpp"

namespace xieite::algorithms {
	template<std::ranges::forward_range Range>
	requires(std::ranges::sized_range<Range> && xieite::concepts::Arithmetic<std::ranges::range_value_t<Range>>)
	[[nodiscard]] constexpr std::common_type_t<double, std::ranges::range_value_t<Range>> mean(Range&& range) noexcept {
		using Result = std::common_type_t<double, std::ranges::range_value_t<Range>>;
		Result result = 0;
		const auto end = std::ranges::end(range);
		for (auto iterator = std::ranges::begin(range); iterator != end; ++iterator) {
			result += static_cast<Result>(*iterator);
		}
		return result / std::ranges::size(range);
	}
}
