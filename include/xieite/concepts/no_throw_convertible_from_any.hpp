#pragma once

#include "../concepts/no_throw_convertible_from.hpp"

namespace xieite::concepts {
	template<typename Target, typename... Sources>
	concept NoThrowConvertibleFromAny = (... && xieite::concepts::NoThrowConvertibleFrom<Target, Sources>);
}
