#pragma once

#include "../concepts/satisfies.hpp"

namespace xieite::concepts {
	template<typename Type, auto validator>
	concept Dissatisfies = !xieite::concepts::Satisfies<Type, validator>;
}
