module;

#include <concepts>

export module xieite:concepts.DerivedFromAll;

export namespace xieite::concepts {
    template <typename Derived, typename... Bases>
    concept DerivedFromAll = (... && std::derived_from<Derived, Bases>);
}
