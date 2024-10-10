#pragma once

#include <numbers>
#include "../units/unit.hpp"

namespace xieite::units {
	using Radian = xieite::units::Unit<"angle">;
	using Degree = xieite::units::Unit<"angle", [](auto x) { return x * std::numbers::pi / 180.0; }, [](auto x) { return x * 180.0 / std::numbers::pi; }>;
}
