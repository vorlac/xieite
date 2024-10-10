module;

#include <iostream>

export module xieite:concepts.InputStream;

export namespace xieite::concepts {
    template <typename Type>
    concept InputStream = std::same_as<std::remove_cv_t<Type>, std::istream> || std::derived_from<std::remove_cv_t<Type>, std::istream>;
}
