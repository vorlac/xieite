module;

#include <concepts>
#include <type_traits>
#include <utility>

export module xieite:concepts.Hashable;

import :concepts.Invocable;

export namespace xieite::concepts {
    template <typename Type, typename Hasher = std::hash<Type>>
    concept Hashable = xieite::concepts::Invocable<Hasher, std::size_t(Type)>;
}
