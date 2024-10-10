module;

#include <type_traits>

export module xieite:concepts.Enumeration;

export namespace xieite::concepts {
    template <typename Type>
    concept Enumeration = std::is_enum_v<Type>;
}
