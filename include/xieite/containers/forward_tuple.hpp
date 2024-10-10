#pragma once

#include <tuple>
#include "../concepts/specialization_of.hpp"
#include "../preprocessor/forward.hpp"

namespace xieite::containers {
	template<xieite::concepts::SpecializationOf<std::tuple> Tuple>
	[[nodiscard]] constexpr auto forwardTuple(Tuple&& tuple) noexcept {
		return std::apply(
			[](auto&&... values) {
				return std::forward_as_tuple(XIEITE_FORWARD(values)...);
			},
			XIEITE_FORWARD(tuple)
		);
	}
}
