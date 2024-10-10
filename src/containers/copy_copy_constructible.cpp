module;

#include <concepts>

export module xieite:containers.CopyCopyConstructible;

import :containers.MaybeCopyConstructible;

export namespace xieite::containers {
    template <typename Type>
    using CopyCopyConstructible = xieite::containers::MaybeCopyConstructible<std::is_copy_constructible_v<Type>>;
}
