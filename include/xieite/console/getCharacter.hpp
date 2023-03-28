#pragma once

#include <iostream>
#include <xieite/console/RawLock.hpp>

namespace xieite::console {
	inline char getCharacter(const bool echo = true) noexcept {
		xieite::console::RawLock rawLock(echo);
		return std::cin.get();
	}
}
