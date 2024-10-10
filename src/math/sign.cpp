module;

#include <concepts>

export module xieite:math.sign;

import :concepts.Arithmetic;
import :math.isNegative;

export namespace xieite::math {
    template <xieite::concepts::Arithmetic First, xieite::concepts::Arithmetic... Rest>
    [[nodiscard]] constexpr int sign(const First first, const Rest... rest) noexcept {
        constexpr static auto get = [](const First value) {
            return (value > 0) - xieite::math::isNegative(value);
        };
        return (get(first) * ... * get(rest));
    }
}
