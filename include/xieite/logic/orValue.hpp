#ifndef XIEITE_HEADER__LOGIC__OR_VALUE
#	define XIEITE_HEADER__LOGIC__OR_VALUE

#	include <concepts>
#	include "../concepts/NoThrowConvertibleTo.hpp"

namespace xieite::logic {
	template<std::convertible_to<bool> Value>
	constexpr Value& orValue(Value& value1, Value& value2)
	noexcept(noexcept(xieite::concepts::NoThrowConvertibleTo<Value, bool>)) {
		return static_cast<bool>(value1) ? value1 : value2;
	}

	template<std::convertible_to<bool> Value>
	constexpr const Value& orValue(const Value& value1, const Value& value2)
	noexcept(noexcept(xieite::concepts::NoThrowConvertibleTo<Value, bool>)) {
		return static_cast<bool>(value1) ? value1 : value2;
	}
}

#endif
