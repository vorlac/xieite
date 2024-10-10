module;

#include <concepts>

export module xieite:concepts.NoThrowConvertibleTo;

export namespace xieite::concepts {
    template <typename Source, typename Target>
    concept NoThrowConvertibleTo = std::is_nothrow_convertible_v<Source, Target> && requires { static_cast<Target>(std::declval<Source>()); };
}
