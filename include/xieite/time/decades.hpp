#pragma once

#include <chrono>
#include <cstdint>
#include <ratio>

namespace xieite::time {
	using Decades = std::chrono::duration<std::intmax_t, std::ratio<315569520>>;
}
