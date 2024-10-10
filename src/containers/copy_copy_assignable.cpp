module;

#include <type_traits>

export module xieite:containers.CopyCopyAssignable;

import :containers.MaybeCopyAssignable;

export namespace xieite::containers {
    template <typename Type>
    using CopyCopyAssignable = xieite::containers::MaybeCopyAssignable<std::is_copy_assignable_v<Type>>;
}
