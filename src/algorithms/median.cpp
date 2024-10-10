module;
#include <algorithm>
#include <cmath>
#include <concepts>
#include <ranges>
#include <utility>
#include <vector>

export module xieite:algorithms.median;

import :algorithms.mean;
import :concepts.Arithmetic;

export namespace xieite::algorithms {
    template <std::ranges::forward_range Range>
        requires(std::ranges::sized_range<Range> && xieite::concepts::Arithmetic<std::ranges::range_value_t<Range>>)
    [[nodiscard]] constexpr std::common_type_t<double, std::ranges::range_value_t<Range>> median(Range&& range) noexcept {
        using Iterator = std::ranges::iterator_t<Range>;
        std::vector<Iterator> iterators;
        iterators.reserve(std::ranges::size(range));
        const Iterator end = std::ranges::end(range);
        for (Iterator iterator = std::ranges::begin(range); iterator != end; ++iterator) {
            iterators.push_back(iterator);
        }
        std::ranges::sort(iterators, std::ranges::less());
        const std::size_t rangeSize = std::ranges::size(range);
        return (rangeSize % 2)
                 ? *iterators[(rangeSize - 1) / 2]
                 : xieite::algorithms::mean(*iterators[rangeSize / 2 - 1], *iterators[rangeSize / 2]);
    }
}
