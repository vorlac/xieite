#pragma once
#include <cmath> // std::isinf
#include <concepts> // std::derived_from
#include <optional> // std::nullopt, std::optional
#include <xieite/geometry/LineLike.hpp>
#include <xieite/geometry/Point.hpp>
#include <xieite/geometry/getSlope.hpp>

namespace xieite::geometry {
	template<std::derived_from<xieite::geometry::LineLike> L>
	[[nodiscard]]
	constexpr std::optional<xieite::geometry::Point> getInterceptY(const L& lineLike) noexcept {
		return std::isinf(xieite::geometry::getSlope(lineLike)) ? std::nullopt : std::optional(xieite::geometry::Point(0, lineLike.start.y - lineLike.start.x * (lineLike.end.y - lineLike.start.y) / (lineLike.end.x - lineLike.start.x)));
	}
}
