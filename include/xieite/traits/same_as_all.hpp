#ifndef XIEITE_HEADER_TRAITS_SAME_AS_ALL
#	define XIEITE_HEADER_TRAITS_SAME_AS_ALL

#	include <type_traits>
#	include "../concepts/same_as_all.hpp"

namespace xieite::traits {
	template<typename Source, typename... Targets>
	struct SameAsAll
	: std::bool_constant<xieite::concepts::SameAsAll<Source, Targets...>> {};
}

#endif
