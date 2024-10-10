module;

#include <concepts>

export module xieite:concepts.Reference;

export namespace xieite::concepts {
    template <typename Type>
    concept Reference = std::is_reference_v<Type>;
}
