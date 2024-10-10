#pragma once

#include "../concepts/constant.hpp"
#include "../types/maybe_constant.hpp"

namespace xieite::types {
	template<typename Source, typename Target>
	using CopyConstant = xieite::types::MaybeConstant<Target, xieite::concepts::Constant<Source>>;
}
