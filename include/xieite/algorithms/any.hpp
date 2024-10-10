#pragma once

#include <functional>
#include "../preprocessor/arrow.hpp"
#include "../preprocessor/forward.hpp"

namespace xieite::algorithms {
	template<typename... Values, typename Functor>
	[[nodiscard]] constexpr bool any(Functor&& functor, Values&&... values)
	XIEITE_ARROW_BASE((... || std::invoke_r<bool>(functor, XIEITE_FORWARD(values))))
}
