module;

#include <type_traits>

export module xieite:concepts.CopyConstructible;

export namespace xieite::concepts {
    template <typename Type>
    concept CopyConstructible = std::is_copy_constructible_v<Type>;
}
