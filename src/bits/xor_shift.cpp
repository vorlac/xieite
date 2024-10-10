module;

#include <concepts>

export module xieite:bits.xorShift;

export namespace xieite::bits {
    template <std::integral Integral>
    [[nodiscard]] constexpr Integral xorShift(const Integral value, const std::size_t bits) noexcept {
        return value ^ (value >> bits);
    }
}
