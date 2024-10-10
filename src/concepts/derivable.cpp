module;

#include <concepts>

export module xieite:concepts.Derivable;

export namespace xieite::concepts {
    template <typename Type>
    concept Derivable = !std::is_final_v<Type>;
}
