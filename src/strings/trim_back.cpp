module;

#include <string_view>

export module xieite:strings.trimBack;

export namespace xieite::strings {
    [[nodiscard]] constexpr std::string_view trimBack(const std::string_view string, const std::string_view characters) noexcept {
        const std::size_t end = string.find_last_not_of(characters);
        return (end == std::string_view::npos) ? "" : string.substr(0, end + 1);
    }

    [[nodiscard]] constexpr std::string_view trimBack(const std::string_view string, const char character) noexcept {
        return xieite::strings::trimBack(string, std::string_view(&character, 1));
    }
}
