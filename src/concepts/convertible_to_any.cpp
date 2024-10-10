module;

#include <type_traits>

export module xieite:concepts.ConvertibleToAny;

export namespace xieite::concepts {
    template <typename Source, typename... Targets>
    concept ConvertibleToAny = (... || std::convertible_to<Source, Targets>);
}
