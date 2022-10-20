#pragma once
#include <cstddef>
#include <termios.h>

namespace gcufl::console::locks {
	class Raw {
	private:
		termios cookedMode;

	public:
		[[nodiscard]]
		Raw(const bool echo = false) noexcept;

		~Raw();
	};
}
