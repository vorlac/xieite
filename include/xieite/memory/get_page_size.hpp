#pragma once

#include <cstddef>
#include <memory>
#include "../preprocessor/platform.hpp"

#if XIEITE_PLATFORM_TYPE_UNIX
#	include <unistd.h>
#elif XIEITE_PLATFORM_TYPE_WINDOWS
#	include <windows.h>
#else
#	warning "unsupported platform.hpp"
#endif

namespace xieite::memory {
	[[nodiscard]] std::size_t getPageSize() noexcept {
#if XIEITE_PLATFORM_TYPE_UNIX
		return static_cast<std::size_t>(::sysconf(_SC_PAGE_SIZE));
#elif XIEITE_PLATFORM_TYPE_WINDOWS
		::SYSTEM_INFO info;
		::GetSystemInfo(std::addressof(info));
		return info.dwPageSize;
#endif
	}
}
