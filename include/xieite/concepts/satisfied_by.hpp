#pragma once

namespace xieite::concepts {
	template<auto validator, typename... Types>
	concept SatisfiedBy = requires { validator.template operator()<Types...>(); };
}
