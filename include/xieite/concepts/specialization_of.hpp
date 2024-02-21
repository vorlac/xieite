#ifndef XIEITE_HEADER_CONCEPTS_SPECIALIZATION_OF
#	define XIEITE_HEADER_CONCEPTS_SPECIALIZATION_OF

#	include <type_traits>
#	include "../traits/is_specialization_of.hpp"

namespace xieite::concepts {
	template<typename Type, template<typename...> typename Template>
	concept SpecializationOf = xieite::traits::IsSpecializationOf<std::remove_cv_t<Type>, Template>::value;
}

#endif
