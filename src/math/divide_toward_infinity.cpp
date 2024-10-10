module;

#include <cmath>
#include <concepts>

export module xieite:math.divideTowardInfinity;

import :concepts.Arithmetic;
import :math.sign;

export namespace xieite::math {
    template <xieite::concepts::Arithmetic Arithmetic>
    [[nodiscard]] constexpr Arithmetic divideTowardInfinity(const Arithmetic dividend, const std::type_identity_t<Arithmetic> divisor) noexcept {
        if constexpr (std::floating_point<Arithmetic>) {
            return std::ceil(dividend / divisor) - ((dividend < 0) != (divisor < 0));
        }
        else {
            return static_cast<Arithmetic>(dividend / divisor + !!(dividend % divisor) * xieite::math::sign(dividend, divisor));
        }
    }
}
