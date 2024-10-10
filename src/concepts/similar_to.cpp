module;

#include <concepts>

export module xieite:concepts.SimilarTo;

export namespace xieite::concepts {
    template <typename First, typename Second>
    concept SimilarTo = std::same_as<std::remove_cvref_t<First>, std::remove_cvref_t<Second>>;
}
