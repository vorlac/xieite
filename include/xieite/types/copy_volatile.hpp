#pragma once

#include "../concepts/volatile.hpp"
#include "../types/maybe_volatile.hpp"

namespace xieite::types {
	template<typename Source, typename Target>
	using CopyVolatile = xieite::types::MaybeVolatile<Target, xieite::concepts::Volatile<Source>>;
}
