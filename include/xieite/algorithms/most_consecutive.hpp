#ifndef XIEITE_HEADER_ALGORITHMS_MOST_CONSECUTIVE
#	define XIEITE_HEADER_ALGORITHMS_MOST_CONSECUTIVE

#	include <functional>
#	include <iterator>
#	include <ranges>
#	include "../concepts/functable.hpp"
#	include "../concepts/no_throw_invocable.hpp"

namespace xieite::algorithms {
	template<std::ranges::range Range, xieite::concepts::Functable<bool(std::ranges::range_const_reference_t<Range>)> Functor>
	[[nodiscard]] constexpr std::ranges::subrange<std::ranges::iterator_t<Range>> mostConsecutive(Range&& range, Functor&& selector = Functor())
	noexcept(xieite::concepts::NoThrowInvocable<Functor, std::ranges::range_const_reference_t<Range>>) {
		auto iterator = std::ranges::begin(range);
		const auto rangeEnd = std::ranges::end(range);
		auto currentStart = iterator;
		auto currentEnd = iterator;
		auto resultStart = currentStart;
		auto resultEnd = currentEnd;
		bool previous = false;
		for (; iterator != rangeEnd; ++iterator) {
			const bool current = std::invoke(selector, *iterator);
			if (current) {
				if (!previous) {
					currentStart = iterator;
					currentEnd = iterator;
				}
				++currentEnd;
			} else if (previous && (std::ranges::distance(currentStart, currentEnd) > std::ranges::distance(resultStart, resultEnd))) {
				resultStart = currentStart;
				resultEnd = currentEnd;
			}
			previous = current;
		}
		if (previous && (std::ranges::distance(currentStart, currentEnd) > std::ranges::distance(resultStart, resultEnd))) {
			return std::ranges::subrange<std::ranges::iterator_t<Range>>(currentStart, currentEnd);
		}
		return std::ranges::subrange<std::ranges::iterator_t<Range>>(resultStart, resultEnd);
	}
}

#endif
