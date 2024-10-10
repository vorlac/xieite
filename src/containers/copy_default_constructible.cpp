module;

#include <type_traits>

export module xieite:containers.CopyDefaultConstructible;

import :containers.MaybeDefaultConstructible;

export namespace xieite::containers {
    template <typename Type>
    using CopyDefaultConstructible = xieite::containers::MaybeDefaultConstructible<std::is_default_constructible_v<Type>>;
}
