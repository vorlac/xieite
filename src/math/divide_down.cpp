module;

#include <cmath>
#include <concepts>

export module xieite:math.divideDown;

import :concepts.Arithmetic;
import :math.sign;

export namespace xieite::math {
    template <xieite::concepts::Arithmetic Arithmetic>
    [[nodiscard]] constexpr Arithmetic divideDown(const Arithmetic dividend, const std::type_identity_t<Arithmetic> divisor) noexcept {
        if constexpr (std::floating_point<Arithmetic>) {
            return std::floor(dividend / divisor);
        }
        else {
            return static_cast<Arithmetic>(dividend / divisor - !!(dividend % divisor) * (xieite::math::sign(dividend, divisor) < 0));
        }
    }
}
