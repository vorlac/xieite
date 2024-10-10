module;

#include <type_traits>

export module xieite:concepts.Pointer;

export namespace xieite::concepts {
    template <typename Type>
    concept Pointer = std::is_pointer_v<std::remove_reference_t<Type>>;
}
