module;

#include <type_traits>

export module xieite:containers.CopyMoveAssignable;

import :containers.MaybeMoveAssignable;

export namespace xieite::containers {
    template <typename Type>
    using CopyMoveAssignable = xieite::containers::MaybeMoveAssignable<std::is_move_assignable_v<Type>>;
}
