#pragma once

#include <cstddef>
#include <vector>
#include "../concepts/arithmetic.hpp"
#include "../containers/make_array.hpp"
#include "../math/multiplication_overflows.hpp"

namespace xieite::math {
	template<xieite::concepts::Arithmetic Arithmetic>
	constexpr auto factorial = ([] {
		static constexpr auto get = [] {
			std::vector<Arithmetic> result = { 1 };
			for (std::size_t i = 1; !xieite::math::multiplicationOverflows(static_cast<Arithmetic>(i), result[i - 1]); ++i) {
				result.push_back(static_cast<Arithmetic>(i) * result[i - 1]);
			}
			return result;
		};
		return xieite::containers::makeArray<Arithmetic, get().size()>(get());
	})();
}
