module;

#include <cmath>
#include <concepts>

export module xieite:math.absolute;

import :concepts.Arithmetic;
import :math.isNegative;
import :types.TryUnsigned;

export namespace xieite::math {
    template <xieite::concepts::Arithmetic Arithmetic>
    [[nodiscard]] constexpr xieite::types::TryUnsigned<Arithmetic> absolute(const Arithmetic value) noexcept {
        if constexpr (std::floating_point<Arithmetic>) {
            return std::abs(value);
        }
        else {
            return xieite::math::isNegative(value)
                     ? -static_cast<xieite::types::TryUnsigned<Arithmetic>>(value)
                     : static_cast<xieite::types::TryUnsigned<Arithmetic>>(value);
        }
    }
}
