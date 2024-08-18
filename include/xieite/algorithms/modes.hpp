#ifndef XIEITE_HEADER_ALGORITHMS_MODES
#	define XIEITE_HEADER_ALGORITHMS_MODES

#	include <cstddef>
#	include <functional>
#	include <iterator>
#	include <ranges>
#	include <vector>
#	include <type_traits>
#	include "../concepts/arithmetic.hpp"
#	include "../concepts/functor.hpp"

namespace xieite::algorithms {
	template<std::ranges::input_range Range, xieite::concepts::Functor<bool(std::ranges::range_const_reference_t<Range>, std::ranges::range_const_reference_t<Range>)> Functor = std::ranges::greater>
	requires(xieite::concepts::Arithmetic<std::ranges::range_value_t<Range>>)
	[[nodiscard]] constexpr std::vector<std::ranges::iterator_t<Range>> modes(Range& range, Functor&& comparator = Functor())
	noexcept(std::is_nothrow_invocable_v<Functor, std::ranges::range_const_reference_t<Range>, std::ranges::range_const_reference_t<Range>>) {
		std::vector<std::ranges::iterator_t<Range>> iterators;
		const std::size_t rangeSize = std::ranges::size(range);
		if (rangeSize == 1) {
			iterators.push_back(std::ranges::begin(range));
		}
		if (rangeSize <= 1) {
			return iterators;
		}
		auto previous = std::ranges::begin(range);
		auto iterator = std::ranges::next(previous);
		for (std::size_t i = 1; i < (rangeSize - 1); ++i) {
			if (std::invoke(comparator, *iterator, *previous)) {
				const auto next = std::ranges::next(iterator);
				if (std::invoke(comparator, *iterator, *next)) {
					iterators.push_back(iterator);
				} else if (i == (rangeSize - 2)) {
					iterators.push_back(next);
				}
			} else if (i == 1) {
				iterators.push_back(previous);
			}
			previous = iterator++;
		}
		if (std::ranges::size(range) && !iterators.size()) {
			iterators.push_back(std::ranges::begin(range));
		}
		return iterators;
	}
}

#endif
