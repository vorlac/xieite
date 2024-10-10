module;

#include <concepts>

export module xieite:types.Value;

export namespace xieite::types {
    template <auto value>
    using Value = std::integral_constant<decltype(value), value>;
}
