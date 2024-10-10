#pragma once

#include <concepts>
#include <istream>
#include <type_traits>

namespace xieite::concepts {
	template<typename Type>
	concept InputStream = std::same_as<std::remove_cv_t<Type>, std::istream> || std::derived_from<std::remove_cv_t<Type>, std::istream>;
}
