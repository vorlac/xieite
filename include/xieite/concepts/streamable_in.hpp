#ifndef XIEITE_HEADER_CONCEPTS_STREAMABLE_IN
#	define XIEITE_HEADER_CONCEPTS_STREAMABLE_IN

#	include <concepts>
#	include <istream>

namespace xieite::concepts {
	template<typename Type>
	concept StreamableIn = requires(Type value, std::istream inputStream) {
		{ inputStream >> value } -> std::same_as<std::istream&>;
	};
}

#endif
