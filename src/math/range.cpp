module;

#include <array>
#include <cmath>
#include <concepts>
#include <cstdint>
#include <ranges>

export module xieite:math.range;

import :functors.unroll;

export namespace xieite::math {
    template <std::size_t size, auto start = 0, std::same_as<decltype(start)> auto step = 1, std::integral Value = decltype(start)>
    constexpr std::array<Value, size> range = ([] {
        return xieite::functors::unroll<size>([]<std::size_t... i> {
            return std::array<Value, size>{ (static_cast<Value>(i) * step + start)... };
        });
    })();
}
