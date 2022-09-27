#pragma once

#include <cstddef>
#include <functional>
#include <gcufl/concepts/Comparator.hpp>
#include <iterator>
#include <vector>


namespace gcufl::algorithms {
	template<std::forward_iterator I, gcufl::concepts::Comparator<const typename std::iterator_traits<I>::value_type> F>
	constexpr void partialReverse(I begin, const I end, const F& selector) noexcept {
		std::vector<I> iterators;
		for (; begin != end; ++begin)
			if (selector(*begin))
				iterators.push_back(begin);
		const std::size_t iteratorsSize = iterators.size();
		for (std::size_t i = 0; i < iteratorsSize / 2; ++i)
			std::iter_swap(iterators[i], iterators[iteratorsSize - i - 1]);
	}
}
