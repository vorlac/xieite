module;

#include <concepts>
#include <istream>

export module xieite:concepts.StreamableIn;

export namespace xieite::concepts {
    template <typename Type>
    concept StreamableIn = requires(Type value, std::istream inputStream) {
        { inputStream >> value } -> std::convertible_to<std::istream&>;
    };
}
