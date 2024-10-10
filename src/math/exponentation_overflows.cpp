module;

#include <cmath>
#include <concepts>
#include <limits>

export module xieite:math.exponentationOverflows;

import :concepts.Arithmetic;

export namespace xieite::math {
    template <xieite::concepts::Arithmetic First, std::convertible_to<First>... Rest>
    [[nodiscard]] constexpr bool exponentiationOverflows(First first, const Rest... rest) noexcept {
        return first && (first != 1) && (std::unsigned_integral<First> || (first != static_cast<First>(-1))) && (... || ([&first, rest] {
                                                                                                                     // Store power in some deduced fractional type
                                                                                                                     const auto power = std::pow(first, rest);
                                                                                                                     if ((power > std::numeric_limits<First>::max()) || (!std::unsigned_integral<First> && (power < std::numeric_limits<First>::min()))) {
                                                                                                                         return true;
                                                                                                                     }
                                                                                                                     first = static_cast<First>(power);
                                                                                                                     return false;
                                                                                                                 })());
    }
}
