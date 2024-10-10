module;

#include <cmath>
#include <concepts>

export module xieite:math.almostEqualSlope;

import :concepts.Arithmetic;
import :math.almostEqual;

export namespace xieite::math {
    template <xieite::concepts::Arithmetic Arithmetic>
    [[nodiscard]] constexpr bool almostEqualSlope(const Arithmetic value1, const std::type_identity_t<Arithmetic> value2) noexcept {
        return (std::isinf(value1) && std::isinf(value2)) || xieite::math::almostEqual(value1, value2);
    }

    template <xieite::concepts::Arithmetic Arithmetic>
    [[nodiscard]] constexpr bool almostEqualSlope(const Arithmetic value1, const std::type_identity_t<Arithmetic> value2, const std::type_identity_t<Arithmetic> epsilon) noexcept {
        return (std::isinf(value1) && std::isinf(value2)) || xieite::math::almostEqual(value1, value2, epsilon);
    }
}
