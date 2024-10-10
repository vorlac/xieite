module;

#include <concepts>

export module xieite:math.isNegative;

import :concepts.Arithmetic;

export namespace xieite::math {
    template <xieite::concepts::Arithmetic Arithmetic>
    [[nodiscard]] constexpr bool isNegative(const Arithmetic value) noexcept {
        if constexpr (!std::unsigned_integral<Arithmetic>) {
            return value < 0;
        }
        else {
            return false;
        }
    }
}
