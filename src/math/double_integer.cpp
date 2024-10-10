module;

#include <concepts>

export module xieite:math.DoubleInteger;

export namespace xieite::math {
    template <std::unsigned_integral UnsignedIntegral>
    struct DoubleInteger {
        UnsignedIntegral lower;
        UnsignedIntegral upper;
    };
}
