module;

#include <type_traits>

export module xieite:concepts.NoThrowDestructible;

export namespace xieite::concepts {
    template <typename Type>
    concept NoThrowDestructible = std::is_nothrow_destructible_v<Type>;
}
