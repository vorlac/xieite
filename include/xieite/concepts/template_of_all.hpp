#ifndef XIEITE_HEADER_CONCEPTS_TEMPLATE_OF_ALL
#	define XIEITE_HEADER_CONCEPTS_TEMPLATE_OF_ALL

#	include "../concepts/template_of.hpp"

namespace xieite::concepts {
	template<template<typename...> typename Template, typename... Types>
	concept TemplateOfAll = (... && xieite::concepts::TemplateOf<Template, Types>)
}

#endif
