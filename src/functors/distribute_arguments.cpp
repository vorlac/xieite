module;

#include <concepts>
#include <memory>

export module xieite:functors.distributeArguments;

import :functors.unroll;
import :types.Any;

// import :types.List;  // <-- ICE >:-D

export namespace xieite::functors {
    template <std::size_t arity, typename Functor, typename... Arguments>
    // requires(xieite::types::List<xieite::types::Any>::template Repeat<arity>::template Prepend<Functor>::template To<std::is_invocable>::value)
    constexpr void distributeArguments(Functor&& functor, Arguments&&... arguments) {
        static_assert(!!arity || !sizeof...(Arguments), "arguments must be distributable across functor calls");
        static_assert(sizeof...(Arguments) >= arity, "number of arguments must not be less than functor arity");
        if constexpr (sizeof...(Arguments) == arity) {
            std::invoke(std::forward<decltype(functor)>(functor), std::forward<decltype(arguments)>(arguments)...);
        }
        else {
            const std::tuple<Arguments&&...> argumentsTuple = std::forward_as_tuple(std::forward<decltype(arguments)>(arguments)...);
            xieite::functors::unroll<arity>([&functor, &argumentsTuple]<std::size_t... i> {
                std::invoke(functor, std::get<i>(std::move(argumentsTuple))...);
            });
            xieite::functors::unroll<sizeof...(Arguments) - arity>([&functor, &argumentsTuple]<std::size_t... i> {
                xieite::functors::distributeArguments<arity>(std::forward<decltype(functor)>(functor), std::get<i + arity>(std::move(argumentsTuple))...);
            });
        }
    }
}
