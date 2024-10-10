module;

#include <algorithm>
#include <array>
#include <concepts>
#include <iterator>
#include <memory>
#include <ranges>
#include <utility>
#include <vector>

#include <xieite/arrow.hpp>
#include <xieite/forward.hpp>
#include <xieite/lift.hpp>

export module xieite:containers.makeArray;

import :concepts.Invocable;
import :functors.unroll;

export namespace xieite::containers {
    template <typename Value, std::size_t size, std::ranges::input_range Range, xieite::concepts::Invocable<Value(std::ranges::range_common_reference_t<Range>)> Functor>
    [[nodiscard]] constexpr std::array<Value, size> makeArray(Range&& range, Functor&& converter = Functor()) {
        return xieite::functors::unroll<size>([&range, &converter]<std::size_t... i> {
            auto iterator = std::ranges::begin(std::forward<decltype(range)>(range));
            return std::array<Value, size>{ ([&converter, &iterator] {
                if constexpr (!!i) {
                    ++iterator;
                }
                return std::invoke(converter, *iterator);
            })()... };
        });
    }
}
