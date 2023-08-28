#ifndef XIEITE_HEADER__LOGIC__AND_VALUE
#	define XIEITE_HEADER__LOGIC__AND_VALUE

#	include <concepts>
#	include "../concepts/NoThrowConvertibleTo.hpp"

namespace xieite::logic {
	template<std::convertible_to<bool> Value>
	constexpr Value& andValue(Value& value1, Value& value2)
	noexcept(noexcept(xieite::concepts::NoThrowConvertibleTo<Value, bool>)) {
		return static_cast<bool>(value1) ? value2 : value1;
	}

	template<std::convertible_to<bool> Value>
	constexpr const Value& andValue(const Value& value1, const Value& value2)
	noexcept(noexcept(xieite::concepts::NoThrowConvertibleTo<Value, bool>)) {
		return static_cast<bool>(value1) ? value2 : value1;
	}
}

#endif
