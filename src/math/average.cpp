module;

#include <concepts>

export module xieite:math.average;

export namespace xieite::math {
    template <std::integral First, std::convertible_to<First>... Rest>
    [[nodiscard]] constexpr First average(const First first, const Rest... rest) noexcept {
        constexpr static First size = static_cast<First>(sizeof...(rest) + 1);
        return (first / size + (... + (rest / size))) + (first % size + (... + (rest % size))) / size;
    }
}
