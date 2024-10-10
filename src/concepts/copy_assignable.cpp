module;

#include <type_traits>

export module xieite:concepts.CopyAssignable;

export namespace xieite::concepts {
    template <typename Type>
    concept CopyAssignable = std::is_copy_assignable_v<Type>;
}
