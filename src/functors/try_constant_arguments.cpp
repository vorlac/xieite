module;

#include <xieite/arrow.hpp>
#include <xieite/forward.hpp>

export module xieite:functors.tryConstantArguments;

// import :types.List;
import :types.MaybeConstant;

export namespace xieite::functors {
    // template <typename Functor, typename... Arguments>
    // /* discardable */ constexpr auto tryConstantArguments(Functor&& functor, Arguments&&... arguments) { return xieite::types::List<Arguments...>::template Transform<1, []<typename Argument, typename... First> {
    //         return std::type_identity<std::conditional_t<xieite::types::List<Arguments...>::template Slice<sizeof...(First) + 1>::template Prepend<Functor, First..., xieite::types::MaybeConstant<Argument, true>>::template To<std::is_invocable>::value, xieite::types::MaybeConstant<Argument, true>, Argument>>(); }>::apply([&functor, &arguments... ]<typename... MaybeConstantArguments> {(std::invoke(std::forward<decltype(functor)>(functor), std::forward_like<MaybeConstantArguments>(arguments)...)));
    //      }
    // }
}
