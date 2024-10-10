#pragma once

#include <type_traits>
#include "../types/copy_reference.hpp"

namespace xieite::types {
	template<typename Type, bool qualified>
	using MaybeVolatile = xieite::types::CopyReference<Type, std::conditional_t<qualified, volatile std::remove_reference_t<Type>, std::remove_volatile_t<std::remove_reference_t<Type>>>>;
}
