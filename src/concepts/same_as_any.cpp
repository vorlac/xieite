module;

#include <concepts>

export module xieite:concepts.SameAsAny;

export namespace xieite::concepts {
    template <typename First, typename... Rest>
    concept SameAsAny = (... || std::same_as<First, Rest>);
}
