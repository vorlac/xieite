module;

#include <concepts>

export module xieite:concepts.Destructible;

export namespace xieite::concepts {
    template <typename Type>
    concept Destructible = std::is_destructible_v<Type>;
}
