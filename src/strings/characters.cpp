module;

#include <string_view>

export module xieite:strings.characters;

export namespace xieite::strings::characters {
    constexpr std::size_t alphabetSize = 26;

    constexpr std::string_view uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    constexpr std::string_view lowercase = "abcdefghijklmnopqrstuvwxyz";

    constexpr std::string_view digits = "0123456789";

    constexpr std::string_view alphanumeric = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    constexpr std::string_view vowels = "AEIOUaeiou";

    constexpr std::string_view consonants = "BCDFGHJKLMNPQRSTVWXYZbcdfghjklmnpqrstvwxyz";

    constexpr std::string_view whitespaces = "\t\n\v\f\r ";
}
