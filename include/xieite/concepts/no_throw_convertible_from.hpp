#pragma once

#include "../concepts/no_throw_convertible_to.hpp"

namespace xieite::concepts {
	template<typename Target, typename Source>
	concept NoThrowConvertibleFrom = xieite::concepts::NoThrowConvertibleTo<Source, Target>;
}
