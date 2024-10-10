module;

#include <array>

export module xieite:literals.radix;

export namespace xieite::literals::radix {
    template <char... characters>
    [[nodiscard]] constexpr std::size_t operator""_radix() noexcept {
        constexpr static std::array<char, sizeof...(characters)> value = { characters... };
        if constexpr ((value.size() > 1) && (value[0] == '0')) {
            switch (value[1]) {
                case 'x':
                case 'X':
                    return 16;
                case 'b':
                case 'B':
                    return 2;
            }
            return 8;
        }
        return 10;
    }
}
