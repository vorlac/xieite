#ifndef XIEITE_HEADER_GEOMETRY_REFLECT
#	define XIEITE_HEADER_GEOMETRY_REFLECT

#	include "../concepts/linear_shape.hpp"
#	include "../geometry/point.hpp"
#	include "../geometry/polygon.hpp"
#	include "../geometry/rotate.hpp"

namespace xieite::geometry {
	template<xieite::concepts::LinearShape LinearShape>
	[[nodiscard]] constexpr xieite::geometry::Point reflect(const xieite::geometry::Point point, const LinearShape& mirror) noexcept {
		return xieite::geometry::rotate(point, (mirror.angle() - mirror.start.angleTo(point)) * 2);
	}

	template<xieite::concepts::LinearShape LinearShape1, xieite::concepts::LinearShape LinearShape2>
	[[nodiscard]] constexpr LinearShape1 reflect(const LinearShape1& line, const LinearShape2& mirror) noexcept {
		return LinearShape1(xieite::geometry::rotate(line.start, (mirror.angle() - mirror.start.angleTo(line.start)) * 2), xieite::geometry::rotate(line.end, (mirror.angle() - mirror.start.angleTo(line.end)) * 2));
	}

	template<xieite::concepts::LinearShape LinearShape>
	[[nodiscard]] constexpr xieite::geometry::Polygon reflect(xieite::geometry::Polygon polygon, const LinearShape& mirror) noexcept {
		for (xieite::geometry::Point& point : polygon.points) {
			point = xieite::geometry::rotate(point, (mirror.angle() - mirror.start.angleTo(point)) * 2);
		}
		return polygon;
	}
}

#endif
