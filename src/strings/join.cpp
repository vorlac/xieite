module;

#include <concepts>
#include <ranges>
#include <string>
#include <string_view>

#include <xieite/forward.hpp>

export module xieite:strings.join;

export namespace xieite::strings {
    template <std::ranges::input_range Range>
        requires(std::constructible_from<std::string, std::ranges::range_common_reference_t<Range>>)
    [[nodiscard]] constexpr std::string join(Range&& range, const std::string_view delimiter = "", const std::string_view prefix = "", const std::string_view suffix = "") noexcept {
        auto iterator = std::ranges::begin(range);
        const auto end = std::ranges::end(range);
        if (iterator == end) {
            return "";
        }
        std::string result = std::string(*iterator);
        while (++iterator != end) {
            result += std::string(delimiter);
            result += std::string(*iterator);
        }
        return std::string(prefix) + result + std::string(suffix);
    }

    template <std::ranges::input_range Range>
        requires(std::constructible_from<std::string, std::ranges::range_common_reference_t<Range>>)
    [[nodiscard]] constexpr std::string join(Range&& range, const char delimiter, const std::string_view prefix = "", const std::string_view suffix = "") noexcept {
        return xieite::strings::join(std::forward<decltype(range)>(range), std::string_view(&delimiter, 1), prefix, suffix);
    }

    template <std::ranges::input_range Range>
        requires(std::constructible_from<std::string, std::ranges::range_common_reference_t<Range>>)
    [[nodiscard]] constexpr std::string join(Range&& range, const std::string_view delimiter, const char prefix, const std::string_view suffix = "") noexcept {
        return xieite::strings::join(std::forward<decltype(range)>(range), delimiter, std::string_view(&prefix, 1), suffix);
    }

    template <std::ranges::input_range Range>
        requires(std::constructible_from<std::string, std::ranges::range_common_reference_t<Range>>)
    [[nodiscard]] constexpr std::string join(Range&& range, const char delimiter, const char prefix, const std::string_view suffix = "") noexcept {
        return xieite::strings::join(std::forward<decltype(range)>(range), std::string_view(&delimiter, 1), std::string_view(&prefix, 1), suffix);
    }

    template <std::ranges::input_range Range>
        requires(std::constructible_from<std::string, std::ranges::range_common_reference_t<Range>>)
    [[nodiscard]] constexpr std::string join(Range&& range, const std::string_view delimiter, const std::string_view prefix, const char suffix) noexcept {
        return xieite::strings::join(std::forward<decltype(range)>(range), delimiter, prefix, std::string_view(&suffix, 1));
    }

    template <std::ranges::input_range Range>
        requires(std::constructible_from<std::string, std::ranges::range_common_reference_t<Range>>)
    [[nodiscard]] constexpr std::string join(Range&& range, const char delimiter, const std::string_view prefix, const char suffix) noexcept {
        return xieite::strings::join(std::forward<decltype(range)>(range), std::string_view(&delimiter, 1), prefix, std::string_view(&suffix, 1));
    }

    template <std::ranges::input_range Range>
        requires(std::constructible_from<std::string, std::ranges::range_common_reference_t<Range>>)
    [[nodiscard]] constexpr std::string join(Range&& range, const std::string_view delimiter, const char prefix, const char suffix) noexcept {
        return xieite::strings::join(std::forward<decltype(range)>(range), delimiter, std::string_view(&prefix, 1), std::string_view(&suffix, 1));
    }

    template <std::ranges::input_range Range>
        requires(std::constructible_from<std::string, std::ranges::range_common_reference_t<Range>>)
    [[nodiscard]] constexpr std::string join(Range&& range, const char delimiter, const char prefix, const char suffix) noexcept {
        return xieite::strings::join(std::forward<decltype(range)>(range), std::string_view(&delimiter, 1), std::string_view(&prefix, 1), std::string_view(&suffix, 1));
    }
}
