#pragma once

#include "../concepts/convertible_from.hpp"

namespace xieite::concepts {
	template<typename Target, typename... Sources>
	concept ConvertibleFromAny = (... || xieite::concepts::ConvertibleFrom<Target, Sources>);
}
