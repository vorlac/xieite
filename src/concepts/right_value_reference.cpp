module;

#include <concepts>

export module xieite:concepts.RightValueReference;

export namespace xieite::concepts {
    template <typename Type>
    concept RightValueReference = std::is_rvalue_reference_v<Type>;
}
