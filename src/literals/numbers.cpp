module;

#include <cstdint>
#include <utility>

#include <xieite/feature.hpp>

export module xieite:literals.numbers;

import :math.SignedSize;

#if XIEITE_FEATURE_UNSIGNED_128
import :math.Unsigned128;
#endif

#if XIEITE_FEATURE_SIGNED_128
import :math.Signed128;
#endif

export namespace xieite::literals::numbers {
    [[nodiscard]] constexpr auto operator""_i(const unsigned long long int value) noexcept {
        return static_cast<int>(value);
    }

    [[nodiscard]] constexpr auto operator""_i(const long double value) noexcept {
        return static_cast<signed int>(value);
    }

    [[nodiscard]] constexpr auto operator""_u(const unsigned long long int value) noexcept {
        return static_cast<unsigned int>(value);
    }

    [[nodiscard]] constexpr auto operator""_u(const long double value) noexcept {
        return static_cast<unsigned int>(value);
    }

    [[nodiscard]] constexpr auto operator""_il(const unsigned long long int value) noexcept {
        return static_cast<long int>(value);
    }

    [[nodiscard]] constexpr auto operator""_il(const long double value) noexcept {
        return static_cast<long int>(value);
    }

    [[nodiscard]] constexpr auto operator""_ul(const unsigned long long int value) noexcept {
        return static_cast<unsigned long int>(value);
    }

    [[nodiscard]] constexpr auto operator""_ul(const long double value) noexcept {
        return static_cast<unsigned long int>(value);
    }

    [[nodiscard]] constexpr auto operator""_ill(const unsigned long long int value) noexcept {
        return static_cast<long long int>(value);
    }

    [[nodiscard]] constexpr auto operator""_ill(const long double value) noexcept {
        return static_cast<long long int>(value);
    }

    [[nodiscard]] constexpr auto operator""_ull(const unsigned long long int value) noexcept {
        return static_cast<unsigned long long int>(value);
    }

    [[nodiscard]] constexpr auto operator""_ull(const long double value) noexcept {
        return static_cast<unsigned long long int>(value);
    }

    [[nodiscard]] constexpr auto operator""_is(const unsigned long long int value) noexcept {
        return static_cast<short int>(value);
    }

    [[nodiscard]] constexpr auto operator""_is(const long double value) noexcept {
        return static_cast<short int>(value);
    }

    [[nodiscard]] constexpr auto operator""_us(const unsigned long long int value) noexcept {
        return static_cast<unsigned short int>(value);
    }

    [[nodiscard]] constexpr auto operator""_us(const long double value) noexcept {
        return static_cast<unsigned short int>(value);
    }

    [[nodiscard]] constexpr auto operator""_b(const unsigned long long int value) noexcept {
        return static_cast<bool>(value);
    }

    [[nodiscard]] constexpr auto operator""_b(const long double value) noexcept {
        return static_cast<bool>(value);
    }

    [[nodiscard]] constexpr auto operator""_c(const unsigned long long int value) noexcept {
        return static_cast<char>(value);
    }

    [[nodiscard]] constexpr auto operator""_c(const long double value) noexcept {
        return static_cast<char>(value);
    }

    [[nodiscard]] constexpr auto operator""_uc(const unsigned long long int value) noexcept {
        return static_cast<unsigned char>(value);
    }

    [[nodiscard]] constexpr auto operator""_uc(const long double value) noexcept {
        return static_cast<unsigned char>(value);
    }

    [[nodiscard]] constexpr auto operator""_ic(const unsigned long long int value) noexcept {
        return static_cast<signed char>(value);
    }

    [[nodiscard]] constexpr auto operator""_ic(const long double value) noexcept {
        return static_cast<signed char>(value);
    }

    [[nodiscard]] constexpr auto operator""_cw(const unsigned long long int value) noexcept {
        return static_cast<wchar_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_cw(const long double value) noexcept {
        return static_cast<wchar_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_c8(const unsigned long long int value) noexcept {
        return static_cast<char8_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_c8(const long double value) noexcept {
        return static_cast<char8_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_c16(const unsigned long long int value) noexcept {
        return static_cast<char16_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_c16(const long double value) noexcept {
        return static_cast<char16_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_c32(const unsigned long long int value) noexcept {
        return static_cast<char32_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_c32(const long double value) noexcept {
        return static_cast<char32_t>(value);
    }

#if XIEITE_FEATURE_UNSIGNED_8
    [[nodiscard]] constexpr auto operator""_u8(const unsigned long long int value) noexcept {
        return static_cast<std::uint8_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_u8(const long double value) noexcept {
        return static_cast<std::uint8_t>(value);
    }
#endif

#if XIEITE_FEATURE_SIGNED_8
    [[nodiscard]] constexpr auto operator""_i8(const unsigned long long int value) noexcept {
        return static_cast<std::int8_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_i8(const long double value) noexcept {
        return static_cast<std::int8_t>(value);
    }
#endif

    [[nodiscard]] constexpr auto operator""_u8f(const unsigned long long int value) noexcept {
        return static_cast<std::uint_fast8_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_u8f(const long double value) noexcept {
        return static_cast<std::uint_fast8_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_i8f(const unsigned long long int value) noexcept {
        return static_cast<std::int_fast8_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_i8f(const long double value) noexcept {
        return static_cast<std::int_fast8_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_u8l(const unsigned long long int value) noexcept {
        return static_cast<std::uint_least8_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_u8l(const long double value) noexcept {
        return static_cast<std::uint_least8_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_i8l(const unsigned long long int value) noexcept {
        return static_cast<std::int_least8_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_i8l(const long double value) noexcept {
        return static_cast<std::int_least8_t>(value);
    }

#if XIEITE_FEATURE_UNSIGNED_16
    [[nodiscard]] constexpr auto operator""_u16(const unsigned long long int value) noexcept {
        return static_cast<std::uint16_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_u16(const long double value) noexcept {
        return static_cast<std::uint16_t>(value);
    }
#endif

#if XIEITE_FEATURE_SIGNED_16
    [[nodiscard]] constexpr auto operator""_i16(const unsigned long long int value) noexcept {
        return static_cast<std::int16_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_i16(const long double value) noexcept {
        return static_cast<std::int16_t>(value);
    }
#endif

    [[nodiscard]] constexpr auto operator""_u16f(const unsigned long long int value) noexcept {
        return static_cast<std::uint_fast16_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_u16f(const long double value) noexcept {
        return static_cast<std::uint_fast16_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_i16f(const unsigned long long int value) noexcept {
        return static_cast<std::int_fast16_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_i16f(const long double value) noexcept {
        return static_cast<std::int_fast16_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_u16l(const unsigned long long int value) noexcept {
        return static_cast<std::uint_least16_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_u16l(const long double value) noexcept {
        return static_cast<std::uint_least16_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_i16l(const unsigned long long int value) noexcept {
        return static_cast<std::int_least16_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_i16l(const long double value) noexcept {
        return static_cast<std::int_least16_t>(value);
    }

#if XIEITE_FEATURE_UNSIGNED_32
    [[nodiscard]] constexpr auto operator""_u32(const unsigned long long int value) noexcept {
        return static_cast<std::uint32_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_u32(const long double value) noexcept {
        return static_cast<std::uint32_t>(value);
    }
#endif

#if XIEITE_FEATURE_SIGNED_32
    [[nodiscard]] constexpr auto operator""_i32(const unsigned long long int value) noexcept {
        return static_cast<std::int32_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_i32(const long double value) noexcept {
        return static_cast<std::int32_t>(value);
    }
#endif

    [[nodiscard]] constexpr auto operator""_u32f(const unsigned long long int value) noexcept {
        return static_cast<std::uint_fast32_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_u32f(const long double value) noexcept {
        return static_cast<std::uint_fast32_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_i32f(const unsigned long long int value) noexcept {
        return static_cast<std::int_fast32_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_i32f(const long double value) noexcept {
        return static_cast<std::int_fast32_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_u32l(const unsigned long long int value) noexcept {
        return static_cast<std::uint_least32_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_u32l(const long double value) noexcept {
        return static_cast<std::uint_least32_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_i32l(const unsigned long long int value) noexcept {
        return static_cast<std::int_least32_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_i32l(const long double value) noexcept {
        return static_cast<std::int_least32_t>(value);
    }

#if XIEITE_FEATURE_UNSIGNED_64
    [[nodiscard]] constexpr auto operator""_u64(const unsigned long long int value) noexcept {
        return static_cast<std::uint64_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_u64(const long double value) noexcept {
        return static_cast<std::uint64_t>(value);
    }
#endif

#if XIEITE_FEATURE_SIGNED_64
    [[nodiscard]] constexpr auto operator""_i64(const unsigned long long int value) noexcept {
        return static_cast<std::int64_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_i64(const long double value) noexcept {
        return static_cast<std::int64_t>(value);
    }
#endif

    [[nodiscard]] constexpr auto operator""_u64f(const unsigned long long int value) noexcept {
        return static_cast<std::uint_fast64_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_u64f(const long double value) noexcept {
        return static_cast<std::uint_fast64_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_i64f(const unsigned long long int value) noexcept {
        return static_cast<std::int_fast64_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_i64f(const long double value) noexcept {
        return static_cast<std::int_fast64_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_u64l(const unsigned long long int value) noexcept {
        return static_cast<std::uint_least64_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_u64l(const long double value) noexcept {
        return static_cast<std::uint_least64_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_i64l(const unsigned long long int value) noexcept {
        return static_cast<std::int_least64_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_i64l(const long double value) noexcept {
        return static_cast<std::int_least64_t>(value);
    }

#if XIEITE_FEATURE_UNSIGNED_128
    [[nodiscard]] constexpr auto operator""_u128(const unsigned long long int value) noexcept {
        return static_cast<xieite::math::Unsigned128>(value);
    }

    // [[nodiscard]] constexpr auto operator""_u128(const long double value) noexcept {
    //     return static_cast<xieite::math::Unsigned128>(value);
    // }
#endif

#if XIEITE_FEATURE_SIGNED_128
    [[nodiscard]] constexpr auto operator""_i128(const unsigned long long int value) noexcept {
        return static_cast<xieite::math::Signed128>(value);
    }

    // [[nodiscard]] constexpr auto operator""_i128(const long double value) noexcept {
    //     return static_cast<xieite::math::Signed128>(value);
    // }
#endif

    [[nodiscard]] constexpr auto operator""_um(const unsigned long long int value) noexcept {
        return static_cast<std::uintmax_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_um(const long double value) noexcept {
        return static_cast<std::uintmax_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_im(const unsigned long long int value) noexcept {
        return static_cast<std::intmax_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_im(const long double value) noexcept {
        return static_cast<std::intmax_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_up(const unsigned long long int value) noexcept {
        return static_cast<std::uintptr_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_up(const long double value) noexcept {
        return static_cast<std::uintptr_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_ip(const unsigned long long int value) noexcept {
        return static_cast<std::intptr_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_ip(const long double value) noexcept {
        return static_cast<std::intptr_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_pd(const unsigned long long int value) noexcept {
        return static_cast<std::ptrdiff_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_pd(const long double value) noexcept {
        return static_cast<std::ptrdiff_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_uz(const unsigned long long int value) noexcept {
        return static_cast<std::size_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_uz(const long double value) noexcept {
        return static_cast<std::size_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_iz(const unsigned long long int value) noexcept {
        return static_cast<xieite::math::SignedSize>(value);
    }

    [[nodiscard]] constexpr auto operator""_iz(const long double value) noexcept {
        return static_cast<xieite::math::SignedSize>(value);
    }

    [[nodiscard]] constexpr auto operator""_f(const unsigned long long int value) noexcept {
        return static_cast<float>(value);
    }

    [[nodiscard]] constexpr auto operator""_f(const long double value) noexcept {
        return static_cast<float>(value);
    }

    [[nodiscard]] constexpr auto operator""_d(const unsigned long long int value) noexcept {
        return static_cast<double>(value);
    }

    [[nodiscard]] constexpr auto operator""_d(const long double value) noexcept {
        return static_cast<double>(value);
    }

    [[nodiscard]] constexpr auto operator""_dl(const unsigned long long int value) noexcept {
        return static_cast<long double>(value);
    }

    [[nodiscard]] constexpr auto operator""_dl(const long double value) noexcept {
        return static_cast<long double>(value);
    }

#if XIEITE_FEATURE_FLOAT_16
    [[nodiscard]] constexpr auto operator""_f16(const unsigned long long int value) noexcept {
        return static_cast<std::float16_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_f16(const long double value) noexcept {
        return static_cast<std::float16_t>(value);
    }
#endif

#if XIEITE_FEATURE_FLOAT_32
    [[nodiscard]] constexpr auto operator""_f32(const unsigned long long int value) noexcept {
        return static_cast<std::float32_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_f32(const long double value) noexcept {
        return static_cast<std::float32_t>(value);
    }
#endif

#if XIEITE_FEATURE_FLOAT_64
    [[nodiscard]] constexpr auto operator""_f64(const unsigned long long int value) noexcept {
        return static_cast<std::float64_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_f64(const long double value) noexcept {
        return static_cast<std::float64_t>(value);
    }
#endif

#if XIEITE_FEATURE_FLOAT_128
    [[nodiscard]] constexpr auto operator""_f128(const unsigned long long int value) noexcept {
        return static_cast<std::float128_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_f128(const long double value) noexcept {
        return static_cast<std::float128_t>(value);
    }
#endif

#if XIEITE_FEATURE_FLOAT_BRAIN
    [[nodiscard]] constexpr auto operator""_fb(const unsigned long long int value) noexcept {
        return static_cast<std::bfloat16_t>(value);
    }

    [[nodiscard]] constexpr auto operator""_fb(const long double value) noexcept {
        return static_cast<std::bfloat16_t>(value);
    }
#endif
}
