#pragma once

#include <concepts>
#include <type_traits>

namespace xieite::concepts {
	template<typename First, typename Second>
	concept SimilarTo = std::same_as<std::remove_cvref_t<First>, std::remove_cvref_t<Second>>;
}
