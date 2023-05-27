#ifndef XIEITE_HEADER_ALGORITHMS_PARTIALREVERSE
#	define XIEITE_HEADER_ALGORITHMS_PARTIALREVERSE

#	include <algorithm>
#	include <cstddef>
#	include <iterator>
#	include <ranges>
#	include <vector>
#	include <xieite/concepts/Functional.hpp>

namespace xieite::algorithms {
	template<std::ranges::range Range>
	constexpr void partialReverse(const Range& range, const xieite::concepts::Functional<bool(std::ranges::range_value_t<Range>)> auto& selector) {
		std::ranges::iterator_t<const Range&> begin = std::ranges::begin(range);
		std::ranges::const_iterator_t<const Range&> end = std::ranges::end(range);
		std::vector<std::ranges::iterator_t<const Range&>> iterators;
		for (; begin != end; ++begin) {
			if (selector(*begin)) {
				iterators.push_back(begin);
			}
		}
		const std::size_t iteratorsSize = iterators.size();
		for (std::size_t i = 0; i < iteratorsSize / 2; ++i) {
			std::iter_swap(iterators[i], iterators[iteratorsSize - i - 1]);
		}
	}
}

#endif
