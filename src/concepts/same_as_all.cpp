module;

#include <concepts>

export module xieite:concepts.SameAsAll;

export namespace xieite::concepts {
    template <typename First, typename... Rest>
    concept SameAsAll = (... || std::same_as<First, Rest>);
}
