module;

#include <concepts>

export module xieite:concepts.Arithmetic;

export namespace xieite::concepts {
    template <typename Type>
    concept Arithmetic = std::integral<Type> || std::floating_point<Type>;
}
