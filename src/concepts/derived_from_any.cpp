module;

#include <concepts>

export module xieite:concepts.DerivedFromAny;

export namespace xieite::concepts {
    template <typename Derived, typename... Bases>
    concept DerivedFromAny = (... || std::derived_from<Derived, Bases>);
}
