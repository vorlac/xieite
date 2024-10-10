module;

#include <cmath>
#include <concepts>
#include <ranges>
#include <stdexcept>

export module xieite:math.power;

import :concepts.Arithmetic;
import :math.isNegative;
import :math.splitBoolean;

export namespace xieite::math {
    template <xieite::concepts::Arithmetic Arithmetic>
    [[nodiscard]] constexpr Arithmetic power(Arithmetic base, std::type_identity_t<Arithmetic> exponent) {
        if constexpr (std::floating_point<Arithmetic>) {
            return std::pow(base, exponent);
        }
        else {
            if ((base == 1) || (exponent == 1)) {
                return base;
            }
            if (!std::unsigned_integral<Arithmetic> && (base == static_cast<Arithmetic>(-1))) {
                return base * xieite::math::splitBoolean(!!(exponent & 1));
            }
            if (!base || !exponent) {
                if (xieite::math::isNegative(exponent)) {
                    throw std::out_of_range("must not take power of zero to negative exponent");
                }
                return !exponent;
            }
            Arithmetic result = 1;
            while (exponent) {
                if (exponent & 1) {
                    result *= base;
                }
                exponent >>= 1;
                base *= base;
            }
            return result;
        }
    }
}
