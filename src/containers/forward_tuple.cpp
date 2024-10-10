module;

#include <concepts>
#include <memory>
#include <tuple>

#include <xieite/forward.hpp>

export module xieite:containers.forwardTuple;

import :concepts.SpecializationOf;

export namespace xieite::containers {
    template <xieite::concepts::SpecializationOf<std::tuple> Tuple>
    [[nodiscard]] constexpr auto forwardTuple(Tuple&& tuple) noexcept {
        return std::apply(
            [](auto&&... values) {
                return std::forward_as_tuple(std::forward<decltype(values)>(values)...);
            },
            std::forward<decltype(tuple)>(tuple));
    }
}
