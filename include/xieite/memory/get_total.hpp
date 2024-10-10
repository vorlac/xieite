#pragma once

#include <cstddef>
#include <memory>
#include "../memory/get_page_size.hpp"
#include "../preprocessor/platform.hpp"

#if XIEITE_PLATFORM_TYPE_UNIX
#	include <unistd.h>
#elif XIEITE_PLATFORM_TYPE_WINDOWS
#	include <windows.h>
#else
#	warning "unsupported platform"
#endif

namespace xieite::memory {
	[[nodiscard]] std::size_t getTotal() noexcept {
#if XIEITE_PLATFORM_TYPE_UNIX
		return static_cast<std::size_t>(::sysconf(_SC_PHYS_PAGES)) * xieite::memory::getPageSize();
#elif XIEITE_PLATFORM_TYPE_WINDOWS
		::MEMORYSTATUSEX status;
		status.dwLength = sizeof(status);
		::GlobalMemoryStatusEx(std::addressof(status));
		return status.ullTotalPhys;
#endif
	}
}
