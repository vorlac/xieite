#pragma once

#include "../concepts/similar_to.hpp"

namespace xieite::concepts {
	template<typename First, typename... Rest>
	concept SimilarToAny = (... && xieite::concepts::SimilarTo<First, Rest>);
}
