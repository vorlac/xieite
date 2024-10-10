module;

#include <concepts>

export module xieite:types.identifier;

import :functors.counter;

constexpr auto identifierCounterTag = [] {
};

export namespace xieite::types {
    template <typename>
    constexpr std::size_t identifier = xieite::functors::counter<identifierCounterTag>();
}
