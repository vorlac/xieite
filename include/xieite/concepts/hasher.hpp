#pragma once

#include <cstddef>
#include "../concepts/invocable.hpp"

namespace xieite::concepts {
	template<typename Type, typename Argument>
	concept Hasher = xieite::concepts::Invocable<Type, std::size_t(Argument)>;
}
