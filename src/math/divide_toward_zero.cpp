module;

#include <cmath>
#include <concepts>

export module xieite:math.divideTowardZero;

import :concepts.Arithmetic;
import :math.sign;

export namespace xieite::math {
    template <xieite::concepts::Arithmetic Arithmetic>
    [[nodiscard]] constexpr Arithmetic divideTowardZero(const Arithmetic dividend, const std::type_identity_t<Arithmetic> divisor) noexcept {
        if constexpr (std::floating_point<Arithmetic>) {
            return std::floor(dividend / divisor) + ((dividend < 0) != (divisor < 0));
        }
        else {
            return dividend / divisor;
        }
    }
}
