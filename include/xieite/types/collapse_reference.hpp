#pragma once

#include <type_traits>
#include "../types/copy_constant.hpp"
#include "../types/copy_volatile.hpp"

namespace xieite::types {
	template<typename Source, typename Target>
	using CollapseReference = xieite::types::CopyVolatile<Source, xieite::types::CopyConstant<Source, std::conditional_t<std::is_lvalue_reference_v<Source>, std::add_lvalue_reference_t<Target>, std::add_rvalue_reference_t<Target>>>>;
}
