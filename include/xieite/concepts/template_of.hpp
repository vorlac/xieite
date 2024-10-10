#pragma once

#include "../concepts/specialization_of.hpp"

namespace xieite::concepts {
	template<template<typename...> typename Template, typename Type>
	concept TemplateOf = xieite::concepts::SpecializationOf<Type, Template>;
}
