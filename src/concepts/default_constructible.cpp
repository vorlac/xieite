module;

#include <type_traits>

export module xieite:concepts.DefaultConstructible;

export namespace xieite::concepts {
    template <typename Type>
    concept DefaultConstructible = std::is_default_constructible_v<Type>;
}
