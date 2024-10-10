module;

#include <string>

export module xieite:strings.repeat;

export namespace xieite::strings {
    [[nodiscard]] constexpr std::string repeat(std::size_t count, const std::string_view string) noexcept {
        std::string result;
        result.reserve(string.size() * count);
        while (count--) {
            result += string;
        }
        return result;
    }
}
