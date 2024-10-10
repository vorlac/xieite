#pragma once

#include <type_traits>
#include "../containers/maybe_move_assignable.hpp"

namespace xieite::containers {
	template<typename Type>
	using CopyMoveAssignable = xieite::containers::MaybeMoveAssignable<std::is_move_assignable_v<Type>>;
}
