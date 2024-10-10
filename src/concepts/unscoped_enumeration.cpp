module;

#include <type_traits>

export module xieite:concepts.UnscopedEnumeration;

export namespace xieite::concepts {
    template <typename Type>
    concept UnscopedEnumeration = std::is_enum_v<Type> && !std::is_scoped_enum_v<Type>;
}
