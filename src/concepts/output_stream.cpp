module;

#include <concepts>
#include <iostream>

export module xieite:concepts.OutputStream;

export namespace xieite::concepts {
    template <typename Type>
    concept OutputStream = std::same_as<std::remove_cvref_t<Type>, std::ostream> || std::derived_from<std::remove_cvref_t<Type>, std::ostream>;
}
