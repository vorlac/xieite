#pragma once

#include "../concepts/specialization_of.hpp"

namespace xieite::concepts {
	template<typename Type, template<typename> typename... Templates>
	concept SpecializationOfAll = (... && xieite::concepts::SpecializationOf<Type, Templates>);
}
