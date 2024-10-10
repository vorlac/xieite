module;

#include <type_traits>

export module xieite:concepts.TriviallyDestructible;

export namespace xieite::concepts {
    template <typename Type>
    concept TriviallyDestructible = std::is_trivially_destructible_v<Type>;
}
