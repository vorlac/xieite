module;

#include <concepts>
#include <cstdint>
#include <type_traits>

export module xieite:algorithms.rotate;

import :concepts.Constant;

export namespace xieite::algorithms {
    template <typename Type, typename... Types>
        requires(!xieite::concepts::Constant<Type> && (... && !xieite::concepts::Constant<Types>))
    constexpr void rotate(std::size_t distance, Type& first, Types&... rest) noexcept {
        distance %= sizeof...(Types) + 1;
        while (distance--) {
            Type last = std::move(first);
            ([](this const auto self, auto& first, auto& second, auto&... rest) {
                first = std::move(second);
                if constexpr (sizeof...(rest)) {
                    self(second, rest...);
                }
            })(first, rest..., last);
        }
    }
}
