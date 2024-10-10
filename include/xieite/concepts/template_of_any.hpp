#pragma once

#include "../concepts/template_of.hpp"

namespace xieite::concepts {
	template<template<typename...> typename Template, typename... Types>
	concept TemplateOfAny = (... || xieite::concepts::TemplateOf<Template, Types>);
}
