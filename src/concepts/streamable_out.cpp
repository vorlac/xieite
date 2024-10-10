module;

#include <concepts>
#include <ostream>

export module xieite:concepts.StreamableOut;

export namespace xieite::concepts {
    template <typename Type>
    concept StreamableOut = requires(Type value, std::ostream outputStream) {
        { outputStream << value } -> std::convertible_to<std::ostream&>;
    };
}

// Thanks to fux for original code
