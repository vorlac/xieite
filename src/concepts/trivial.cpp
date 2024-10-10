module;

#include <concepts>

export module xieite:concepts.Trivial;

export namespace xieite::concepts {
    template <typename Type>
    concept Trivial = std::is_trivial_v<Type>;
}
