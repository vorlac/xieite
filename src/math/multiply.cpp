module;

#include <array>
#include <bit>
#include <cmath>
#include <concepts>
#include <cstdint>
#include <ranges>
#include <utility>

export module xieite:math.multiply;

import :bits.size;
import :math.DoubleInteger;

export namespace xieite::math {
    template <std::unsigned_integral UnsignedIntegral>
    [[nodiscard]] constexpr xieite::math::DoubleInteger<UnsignedIntegral> multiply(const UnsignedIntegral multiplier, const std::type_identity_t<UnsignedIntegral> multiplicand) noexcept {
        constexpr static UnsignedIntegral halfSize = sizeof(UnsignedIntegral) / 2;
        constexpr static UnsignedIntegral halfBits = std::numeric_limits<UnsignedIntegral>::max() >> halfSize;
        const UnsignedIntegral multiplierLow = multiplier & halfBits;
        const UnsignedIntegral multiplierHigh = multiplier >> halfSize;
        const UnsignedIntegral multiplicandLow = multiplicand & halfBits;
        const UnsignedIntegral multiplicandHigh = multiplicand >> halfSize;
        const UnsignedIntegral product1 = multiplierLow * multiplicandLow;
        const UnsignedIntegral product2 = multiplierLow * multiplicandHigh;
        const UnsignedIntegral product3 = multiplierHigh * multiplicandLow;
        return xieite::math::DoubleInteger<UnsignedIntegral>(product1 + (product2 << halfSize) + (product3 << halfSize), multiplierHigh * multiplicandHigh + (product2 >> halfSize) + (product3 >> halfSize) + (halfBits & (((product1 >> halfSize) + (product2 & halfBits) + (product3 & halfBits)) >> halfSize)));
    }
}
