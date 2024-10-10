module;

#include <type_traits>

export module xieite:math.SignedSize;

export namespace xieite::math {
    using SignedSize = std::make_signed_t<std::size_t>;
}
