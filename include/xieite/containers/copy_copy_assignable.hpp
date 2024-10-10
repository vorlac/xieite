#pragma once

#include <type_traits>
#include "../containers/maybe_copy_assignable.hpp"

namespace xieite::containers {
	template<typename Type>
	using CopyCopyAssignable = xieite::containers::MaybeCopyAssignable<std::is_copy_assignable_v<Type>>;
}
