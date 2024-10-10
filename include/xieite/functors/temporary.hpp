#pragma once

namespace xieite::functors {
	template<typename Type>
	[[nodiscard]] constexpr Type& temporary(Type&& value = Type()) noexcept {
		return value;
	}
}
