module;

#include <tuple>

export module xieite:containers.reverseTuple;

import :concepts.NoThrowConvertibleTo;
import :functors.unroll;

// import :types.List; // ICE

export namespace xieite::containers {
    // template <typename... Types>
    // [[nodiscard]] constexpr typename xieite::types::List<Types...>::Reverse::template To<std::tuple> reverseTuple(const std::tuple<Types...>& tuple) noexcept {
    //     return xieite::functors::unroll<Types...>([&tuple]<std::size_t... i> {
    //         return xieite::types::List<Types...>::Reverse::template To<std::tuple>(std::get<sizeof...(Types) - i - 1>(tuple)...);
    //     });
    // }
}
