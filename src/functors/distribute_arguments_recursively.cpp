module;

#include <concepts>
#include <tuple>
#include <utility>

#include <xieite/forward.hpp>

export module xieite:functors.distributeArgumentsRecursively;

import :containers.spliceTuple;
import :functors.unroll;
import :types.Any;
import :types.List;

export namespace xieite::functors {
    template <std::size_t arity, std::size_t previousResultIndex = 0, typename Functor, typename... Arguments>
    // requires(xieite::types::List<xieite::types::Any>::Repeat<arity>::Prepend<Functor>::To<std::is_invocable>::value)
    /* discardable */ constexpr decltype(auto) distributeArgumentsRecursively(Functor&& functor, Arguments&&... arguments) {
        static_assert(previousResultIndex < arity, "index of previous result must be within functor arity");
        static_assert((arity > 1) || !sizeof...(Arguments), "arguments must be distributable across functor calls");
        static_assert(sizeof...(Arguments) >= arity, "number of arguments must not be less than functor arity");
        if constexpr (sizeof...(Arguments) == arity) {
            return std::invoke(std::forward<decltype(functor)>(functor), std::forward<decltype(arguments)>(arguments)...);
        }
        else {
            // TODO: double check my edits, pretty sure i broke this...
            const std::tuple<Arguments&&...> argumentsTuple = std::forward_as_tuple(std::forward<decltype(arguments)>(arguments)...);
            const auto resultsTuple = xieite::containers::spliceTuple<previousResultIndex + arity>(argumentsTuple, std::forward_as_tuple(std::apply(functor, xieite::containers::spliceTuple<arity, sizeof...(Arguments) - arity>(argumentsTuple))));
            return xieite::functors::unroll<sizeof...(Arguments) - arity + 1>([&functor, &resultsTuple]<std::size_t... i> {
                return resultsTuple.at(std::get<0>(resultsTuple)).contains(std::make_tuple(std::get<i + 1>(resultsTuple)...));
            });
        }
    }
}
