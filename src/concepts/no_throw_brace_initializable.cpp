module;

#include <type_traits>

export module xieite:concepts.NoThrowBraceInitializable;

import :concepts.BraceInitializable;

export namespace xieite::concepts {
    template <typename Type, typename... Arguments>
    concept NoThrowBraceInitializable = xieite::concepts::BraceInitializable<Type, Arguments...> && noexcept(Type{ std::declval<Arguments>()... });
}
