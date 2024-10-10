module;

#include <algorithm>
#include <concepts>
#include <ranges>
#include <utility>

#include <xieite/arrow.hpp>

export module xieite:algorithms.findOccurrence;

import :algorithms.getOccurrence;
import :concepts.Invocable;

export namespace xieite::algorithms {
    template <std::ranges::forward_range Range, xieite::concepts::Invocable<bool(std::ranges::range_reference_t<Range>, std::ranges::range_reference_t<Range>)> Functor = std::ranges::equal_to>
        requires(std::ranges::sized_range<Range>)
    [[nodiscard]] constexpr std::ranges::iterator_t<Range> findOccurrence(Range& range, std::size_t count, const std::ranges::range_reference_t<Range> value, Functor&& comparator = Functor())
        XIEITE_ARROW_BASE(xieite::algorithms::getOccurrence(range, count, [&value, &comparator](const std::ranges::range_reference_t<Range> other) noexcept(noexcept(std::invoke_r<bool>(comparator, value, other))) -> decltype(std::invoke_r<bool>(comparator, value, other)) {
            return std::invoke_r<bool>(comparator, value, other);
        }))
}
