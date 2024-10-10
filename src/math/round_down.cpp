module;

#include <concepts>

export module xieite:math.roundDown;

import :concepts.Arithmetic;
import :math.divideDown;

export namespace xieite::math {
    template <xieite::concepts::Arithmetic Arithmetic>
    [[nodiscard]] constexpr Arithmetic roundDown(const Arithmetic value, const std::type_identity_t<Arithmetic> step = 1) noexcept {
        return xieite::math::divideDown(value, step) * step;
    }
}
