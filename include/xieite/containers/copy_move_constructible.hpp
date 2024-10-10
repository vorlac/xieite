#pragma once

#include <type_traits>
#include "../containers/maybe_move_constructible.hpp"

namespace xieite::containers {
	template<typename Type>
	using CopyMoveConstructible = xieite::containers::MaybeMoveConstructible<std::is_move_constructible_v<Type>>;
}
