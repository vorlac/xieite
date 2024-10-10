module;

#include <array>
#include <type_traits>
#include <vector>

export module xieite:math.fibonacci;

import :concepts.Arithmetic;
import :containers.makeArray;
import :math.additionOverflows;

export namespace xieite::math {
    template <xieite::concepts::Arithmetic Arithmetic>
    constexpr auto fibonacci = ([] {
        constexpr static auto get = [] {
            std::vector<Arithmetic> result = { 0, 1 };
            for (std::size_t i = 2; !xieite::math::additionOverflows(result[i - 1], result[i - 2]); ++i) {
                result.push_back(result[i - 1] + result[i - 2]);
            }
            return result;
        };
        return xieite::containers::makeArray<Arithmetic, get().size()>(get());
    })();
}
