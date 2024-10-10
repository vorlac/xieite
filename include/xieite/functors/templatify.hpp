#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>
#include "../functors/unroll.hpp"
#include "../preprocessor/forward.hpp"

namespace xieite::functors {
	constexpr void templatify(auto&& lambda, const std::uint8_t value) {
		xieite::functors::unroll<(1uz << std::numeric_limits<std::uint8_t>::digits)>([&lambda, value]<std::size_t... i> {
			(..., [&lambda, value] {
				static constexpr std::uint8_t index = static_cast<std::uint8_t>(i);
				if (value == index) {
					XIEITE_FORWARD(lambda).template operator()<index>();
				}
			});
		});
	}
}
