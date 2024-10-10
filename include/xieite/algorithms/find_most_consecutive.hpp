#pragma once

#include <functional>
#include <ranges>
#include "../algorithms/get_most_consecutive.hpp"
#include "../concepts/invocable.hpp"
#include "../preprocessor/arrow.hpp"

namespace xieite::algorithms {
	template<std::ranges::forward_range Range, xieite::concepts::Invocable<bool(std::ranges::range_common_reference_t<Range>, std::ranges::range_common_reference_t<Range>)> Functor = std::ranges::equal_to>
	requires(std::ranges::sized_range<Range>)
	[[nodiscard]] constexpr std::ranges::subrange<std::ranges::iterator_t<Range>> findMostConsecutive(Range& range, const std::ranges::range_common_reference_t<Range> value, Functor&& comparator = Functor())
	XIEITE_ARROW_BASE(xieite::algorithms::getMostConsecutive(range, [&value, &comparator](const std::ranges::range_common_reference_t<Range> other) XIEITE_ARROW(std::invoke_r<bool>(comparator, value, other))))
}
