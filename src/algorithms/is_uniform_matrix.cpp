module;

#include <algorithm>
#include <ranges>

#include <xieite/lift.hpp>

export module xieite:algorithms.isUniformMatrix;

import :concepts.NoThrowOperableRange;

export namespace xieite::algorithms {
    template <std::ranges::input_range Range>
        requires(std::ranges::input_range<std::ranges::range_value_t<Range>>)
    [[nodiscard]] constexpr bool isUniformMatrix(Range&& matrix) noexcept(([]<typename Subrange, typename Self>(this Self self) {
                                                                              if constexpr (!std::ranges::input_range<Subrange>) {
                                                                                  return true;
                                                                              }
                                                                              else if constexpr (!xieite::concepts::NoThrowOperableRange<Subrange>) {
                                                                                  return false;
                                                                              }
                                                                              else {
                                                                                  return self.template operator()<std::ranges::range_value_t<Range>>();
                                                                              }
                                                                          }).template operator()<Range>()) {
        if constexpr (std::ranges::input_range<std::ranges::range_value_t<std::ranges::range_value_t<Range>>>) {
            return std::ranges::all_of(matrix, xieite::algorithms::isUniformMatrix);
        }
        else {
            const std::size_t firstSize = std::ranges::size(*std::ranges::begin(matrix));
            return std::ranges::all_of(matrix, [firstSize](const std::ranges::range_common_reference_t<Range> item) {
                return std::ranges::size(item) == firstSize;
            });
        }
    }
}
