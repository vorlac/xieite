#pragma once

#include <atomic>
#include <cstddef>

namespace XIEITE_DETAIL {
	std::atomic<std::size_t> nextThreadIdentifier = 0;
}

namespace xieite::threads {
	thread_local const std::size_t identifier = XIEITE_DETAIL::nextThreadIdentifier++;
}
