#pragma once

#include <type_traits>
#include "../containers/maybe_default_constructible.hpp"

namespace xieite::containers {
	template<typename Type>
	using CopyDefaultConstructible = xieite::containers::MaybeDefaultConstructible<std::is_default_constructible_v<Type>>;
}
