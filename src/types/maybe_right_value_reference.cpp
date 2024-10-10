module;

#include <concepts>

export module xieite:types.MaybeRightValueReference;

export namespace xieite::types {
    template <typename Type, bool qualified>
    using MaybeRightValueReference = std::conditional_t<qualified, std::remove_reference_t<Type>&&, std::remove_reference_t<Type>>;
}
