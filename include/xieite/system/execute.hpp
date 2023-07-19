#ifndef XIEITE_HEADER_SYSTEM_EXECUTE
#	define XIEITE_HEADER_SYSTEM_EXECUTE

#	include <xieite/macros/SYSTEM_TYPE.hpp>

#	if XIEITE_SYSTEM_TYPE_UNIX
#		include <cstddef>
#		include <cstdio>
#		include <memory>
#		include <stdio.h>
#		include <string>
#		include <string_view>
#		include <xieite/memory/bufferSize.hpp>

namespace xieite::system {
	inline std::string execute(const std::string_view command) noexcept {
		const auto pipe = std::unique_ptr<std::FILE, decltype([](std::FILE* const file) noexcept -> void {
			pclose(file);
		})>(popen(command.data(), "r"));
		std::string result;
		while (true) {
			std::string buffer = std::string(xieite::memory::bufferSize, '\0');
			const std::size_t bytesRead = std::fread(buffer.data(), sizeof(char), buffer.size(), pipe.get());
			if (!bytesRead) {
				break;
			}
			result += buffer;
		}
		return result;
	}
}

#	else
#		error "System not supported"
#	endif

#endif
