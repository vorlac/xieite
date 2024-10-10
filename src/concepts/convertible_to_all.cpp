module;

#include <concepts>

export module xieite:concepts.ConvertibleToAll;

export namespace xieite::concepts {
    template <typename Source, typename... Targets>
    concept ConvertibleToAll = (... && std::convertible_to<Source, Targets>);
}
