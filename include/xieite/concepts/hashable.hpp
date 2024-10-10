#pragma once

#include <cstddef>
#include <functional>
#include "../concepts/invocable.hpp"

namespace xieite::concepts {
	template<typename Type, typename Hasher = std::hash<Type>>
	concept Hashable = xieite::concepts::Invocable<Hasher, std::size_t(Type)>;
}
