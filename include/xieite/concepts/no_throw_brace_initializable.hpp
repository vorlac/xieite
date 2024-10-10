#pragma once

#include <utility>
#include "../concepts/brace_initializable.hpp"

namespace xieite::concepts {
	template<typename Type, typename... Arguments>
	concept NoThrowBraceInitializable = xieite::concepts::BraceInitializable<Type, Arguments...> && noexcept(Type { std::declval<Arguments>()... });
}
