#ifndef XIEITE_HEADER_CONCEPTS_POLYMORPHIC
#	define XIEITE_HEADER_CONCEPTS_POLYMORPHIC

#	include <type_traits>

namespace xieite::concepts {
	template<typename Type>
	concept Polymorphic = std::is_polymorphic_v<Type>;
}

#endif
