module;

#include <type_traits>

export module xieite:concepts.Volatile;

export namespace xieite::concepts {
    template <typename Type>
    concept Volatile = std::is_volatile_v<std::remove_reference_t<Type>>;
}
