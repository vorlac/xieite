module;

#include <concepts>
#include <cstdint>
#include <utility>
#include <vector>

export module xieite:math.factorial;

import :concepts.Arithmetic;
import :containers.makeArray;
import :math.multiplicationOverflows;

export namespace xieite::math {
    template <xieite::concepts::Arithmetic Arithmetic>
    constexpr auto factorial = ([] {
        constexpr static auto get = [] {
            std::vector<Arithmetic> result = { 1 };
            for (std::size_t i = 1; !xieite::math::multiplicationOverflows(static_cast<Arithmetic>(i), result[i - 1]); ++i) {
                result.push_back(static_cast<Arithmetic>(i) * result[i - 1]);
            }
            return result;
        };
        return xieite::containers::makeArray<Arithmetic, get().size()>(get());
    })();
}
