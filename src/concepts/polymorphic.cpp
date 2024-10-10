module;

#include <concepts>

export module xieite:concepts.Polymorphic;

export namespace xieite::concepts {
    template <typename Type>
    concept Polymorphic = std::is_polymorphic_v<Type>;
}
