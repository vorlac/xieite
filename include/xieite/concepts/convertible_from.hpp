#pragma once

#include <concepts>

namespace xieite::concepts {
	template<typename Target, typename Source>
	concept ConvertibleFrom = std::convertible_to<Source, Target>;
}
