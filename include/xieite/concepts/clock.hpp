#pragma once

#include <chrono>

namespace xieite::concepts {
	template<typename Type>
	concept Clock = std::chrono::is_clock_v<Type>;
}
