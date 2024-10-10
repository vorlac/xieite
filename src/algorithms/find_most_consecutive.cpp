module;

#include <concepts>
#include <ranges>

#include <xieite/arrow.hpp>

export module xieite:algorithms.findMostConsecutive;

import :algorithms.getMostConsecutive;
import :concepts.Invocable;

export namespace xieite::algorithms {
    template <std::ranges::forward_range Range, xieite::concepts::Invocable<bool(std::ranges::range_common_reference_t<Range>, std::ranges::range_common_reference_t<Range>)> Functor = std::ranges::equal_to>
        requires(std::ranges::sized_range<Range>)
    [[nodiscard]] constexpr std::ranges::subrange<std::ranges::iterator_t<Range>> findMostConsecutive(Range& range, const std::ranges::range_common_reference_t<Range> value, Functor&& comparator = Functor()) noexcept(noexcept(xieite::algorithms::getMostConsecutive(range, [&value, &comparator](const std::ranges::range_common_reference_t<Range> other) noexcept(noexcept(std::invoke_r<bool>(comparator, value, other))) -> decltype(std::invoke_r<bool>(comparator, value, other)) {
        return std::invoke_r<bool>(comparator, value, other);
    }))) {
        return xieite::algorithms::getMostConsecutive(range, [&value, &comparator](const std::ranges::range_common_reference_t<Range> other) noexcept(noexcept(std::invoke_r<bool>(comparator, value, other))) -> decltype(std::invoke_r<bool>(comparator, value, other)) {
            return std::invoke_r<bool>(comparator, value, other);
        });
    }
}
