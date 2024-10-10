#pragma once

#include <tuple>
#include <type_traits>
#include "../preprocessor/forward.hpp"

namespace xieite::containers {
	template<typename... Arguments>
	[[nodiscard]] constexpr std::tuple<std::decay_t<Arguments>...> decayAsTuple(Arguments&&... arguments) noexcept {
		return std::tuple<std::decay_t<Arguments>...>(XIEITE_FORWARD(arguments)...);
	}
}
