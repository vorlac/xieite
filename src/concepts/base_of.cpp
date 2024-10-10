module;

#include <concepts>

export module xieite:concepts.BaseOf;

export namespace xieite::concepts {
    template <typename Base, typename Derived>
    concept BaseOf = std::derived_from<Derived, Base>;
}
