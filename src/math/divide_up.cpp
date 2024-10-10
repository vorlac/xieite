module;

#include <cmath>
#include <concepts>

export module xieite:math.divideUp;

import :concepts.Arithmetic;
import :math.sign;

export namespace xieite::math {
    template <xieite::concepts::Arithmetic Arithmetic>
    [[nodiscard]] constexpr Arithmetic divideUp(const Arithmetic dividend, const std::type_identity_t<Arithmetic> divisor) {
        if constexpr (std::floating_point<Arithmetic>) {
            return std::ceil(dividend / divisor);
        }
        else {
            return static_cast<Arithmetic>(dividend / divisor + !!(dividend % divisor) * (xieite::math::sign(dividend, divisor) > 0));
        }
    }
}
