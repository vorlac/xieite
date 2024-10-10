module;

#include <type_traits>

export module xieite:concepts.Aggregate;

export namespace xieite::concepts {
    template <typename Type>
    concept Aggregate = std::is_aggregate_v<Type>;
}
