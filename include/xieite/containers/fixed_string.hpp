#pragma once

#include <algorithm>
#include <array>
#include <concepts>
#include <cstddef>
#include <ranges>
#include <string_view>
#include "../concepts/no_throw_operable_range.hpp"
#include "../containers/make_array.hpp"
#include "../preprocessor/forward.hpp"

namespace xieite::containers {
	template<std::size_t characters, typename Character = char>
	struct FixedString {
		static constexpr std::size_t size = characters;
		std::array<Character, characters> data;

		constexpr FixedString(const Character(&data)[characters]) noexcept {
			std::ranges::copy(data, this->data.begin());
		}

		template<std::ranges::input_range Range>
		requires(std::same_as<std::ranges::range_value_t<Range>, Character>)
		constexpr FixedString(Range&& data)
		noexcept(xieite::concepts::NoThrowOperableRange<Range>)
		: data(xieite::containers::makeArray<Character, characters>(XIEITE_FORWARD(data))) {}

		[[nodiscard]] constexpr std::string_view view() const noexcept {
			return std::string_view(this->data.begin(), this->data.end());
		}
	};

	template<auto characters, typename Character>
	FixedString(const Character(&)[characters]) -> FixedString<characters, Character>;
}
