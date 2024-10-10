module;

#include <concepts>

export module xieite:concepts.ConvertibleFrom;

export namespace xieite::concepts {
    template <typename Target, typename Source>
    concept ConvertibleFrom = std::convertible_to<Source, Target>;
}
