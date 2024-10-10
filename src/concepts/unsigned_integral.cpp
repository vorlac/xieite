module;

#include <concepts>

export module xieite:concepts.UnsignedIntegral;

export namespace xieite::concepts {
    template <typename Type>
    concept UnsignedIntegral = std::unsigned_integral<Type> && !std::same_as<std::remove_cv_t<Type>, bool>;
}
