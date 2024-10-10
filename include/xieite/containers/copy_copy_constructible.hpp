#pragma once

#include <type_traits>
#include "../containers/maybe_copy_constructible.hpp"

namespace xieite::containers {
	template<typename Type>
	using CopyCopyConstructible = xieite::containers::MaybeCopyConstructible<std::is_copy_constructible_v<Type>>;
}
