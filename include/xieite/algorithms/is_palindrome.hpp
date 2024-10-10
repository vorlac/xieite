#pragma once

#include <concepts>
#include <cstddef>
#include <functional>
#include <ranges>
#include "../concepts/invocable.hpp"
#include "../concepts/no_throw_invocable.hpp"
#include "../concepts/no_throw_operable_range.hpp"
#include "../math/reverse.hpp"

namespace xieite::algorithms {
	template<std::ranges::forward_range Range, xieite::concepts::Invocable<bool(std::ranges::range_reference_t<Range>, std::ranges::range_reference_t<Range>)> Functor = std::ranges::equal_to>
	requires(std::ranges::sized_range<Range>)
	[[nodiscard]] constexpr bool isPalindrome(Range&& range, Functor&& comparator = Functor())
	noexcept(xieite::concepts::NoThrowInvocable<Functor, bool(std::ranges::range_reference_t<Range>, std::ranges::range_reference_t<Range>)> && xieite::concepts::NoThrowOperableRange<Range>) {
		auto iterator = std::ranges::begin(range);
		auto end = std::ranges::end(range);
		for (std::size_t i = std::ranges::size(range) / 2; i--;) {
			--end;
			if (!std::invoke_r<bool>(comparator, *iterator, *end)) {
				return false;
			}
			++iterator;
		}
		return true;
	}

	template<std::integral Integral>
	[[nodiscard]] constexpr bool isPalindrome(const Integral value, const Integral radix = 10) noexcept {
		return value == xieite::math::reverse(value, radix);
	}
}
