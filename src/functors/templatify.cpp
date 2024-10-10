module;

#include <limits>
#include <utility>

#include <xieite/forward.hpp>

export module xieite:functors.templatify;

import :functors.unroll;

export namespace xieite::functors {
    // constexpr void templatify(auto&& lambda, const std::uint8_t value) {
    //     xieite::functors::unroll<(1uz << std::numeric_limits<std::uint8_t>::digits)>([&lambda, value]<std::size_t... i> {
    //         (..., [&lambda, value] {
    //             constexpr static std::uint8_t index = static_cast<std::uint8_t>(i);
    //             if (value == index) {
    //                 std::forward<decltype(lambda)>(lambda).template operator()<index>();
    //             }
    //         });
    //     });
    // }
}
