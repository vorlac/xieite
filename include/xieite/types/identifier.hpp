#pragma once

#include <cstddef>
#include "../functors/counter.hpp"

namespace XIEITE_DETAIL {
	constexpr auto identifierCounterTag = [] {};
}

namespace xieite::types {
	template<typename>
	constexpr std::size_t identifier = xieite::functors::counter<XIEITE_DETAIL::identifierCounterTag>();
}
