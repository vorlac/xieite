#pragma once

#include <chrono>
#include <type_traits>
#include "../concepts/arithmetic.hpp"
#include "../concepts/ratio.hpp"

namespace xieite::concepts {
	template<typename Type>
	concept Duration = requires { ([]<xieite::concepts::Arithmetic Arithmetic, xieite::concepts::Ratio Ratio>(std::type_identity<std::chrono::duration<Arithmetic, Ratio>>) {})(std::type_identity<std::remove_cv_t<Type>>()); };
}
