#pragma once

#include "../concepts/specialization_of.hpp"

namespace xieite::concepts {
	template<typename Type, template<typename> typename... Templates>
	concept SpecializationOfAny = (... || xieite::concepts::SpecializationOf<Type, Templates>);
}
