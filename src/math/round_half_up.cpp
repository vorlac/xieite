module;

#include <concepts>

export module xieite:math.roundHalfUp;

import :concepts.Arithmetic;
import :math.divideHalfUp;

export namespace xieite::math {
    template <xieite::concepts::Arithmetic Arithmetic>
    [[nodiscard]] constexpr Arithmetic roundHalfUp(const Arithmetic value, const std::type_identity_t<Arithmetic> step = 1) noexcept {
        return xieite::math::divideHalfUp(value, step) * step;
    }
}
