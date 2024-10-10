module;

#include <concepts>
#include <utility>

#include <xieite/arrow.hpp>
#include <xieite/forward.hpp>

export module xieite:functors.unroll;

export namespace xieite::functors {
    template <std::integral auto count>
    /* discardable */ constexpr auto unroll(auto&& lambda) {
        return ([&lambda]<auto... i>(std::integer_sequence<decltype(count), i...>) {
            return ([&]<auto = [] {
                   }> {
                       if constexpr (::std::same_as<decltype(lambda), decltype(lambda)> && !::std::same_as<decltype(lambda), decltype((lambda))>) {
                           return static_cast<::std::add_rvalue_reference_t<decltype(lambda)>>(lambda);
                       }
                       else {
                           return (lambda);
                       }
                   })()
                .template operator()<i...>();
        })(std::make_integer_sequence<decltype(count), count>());
    }

    template <typename... Types>
    /* discardable */ constexpr auto unroll(auto&& lambda) {
        return xieite::functors::unroll<sizeof...(Types)>(std::forward<decltype(lambda)>(lambda));
    }

    template <auto... values>
    /* discardable */ constexpr auto unroll(auto&& lambda)
        XIEITE_ARROW(xieite::functors::unroll<sizeof...(values)>(std::forward<decltype(lambda)>(lambda)))
}
