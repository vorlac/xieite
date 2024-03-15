#ifndef XIEITE_HEADER_STRINGS_PAD_BACK
#	define XIEITE_HEADER_STRINGS_PAD_BACK

#	include <cstddef>
#	include <string>
#	include <string_view>

namespace xieite::strings {
	[[nodiscard]] constexpr std::string padBack(const std::string_view value, const std::size_t size, const char padding = ' ') noexcept {
		std::string result = std::string(value);
		result.reserve(size);
		const std::size_t valueSize = value.size();
		if (valueSize < size) {
			result += std::string(size - valueSize, padding);
		}
		return result;
	}
}

#endif
