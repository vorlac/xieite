module;

#include <concepts>
#include <string_view>

#include <xieite/compiler.hpp>
#include <xieite/function_signature.hpp>

export module xieite:types.name;

import :containers.makeArray;
import :strings.after;
import :strings.between;

template <typename _>
[[nodiscard]] consteval std::string_view getName() noexcept {
    constexpr static auto get = [string = std::string_view(XIEITE_FUNCTION_SIGNATURE)] {
#if XIEITE_COMPILER_TYPE_GCC
        return xieite::strings::between(string, "= ", ';');
#elif XIEITE_COMPILER_TYPE_CLANG
        return xieite::strings::between(string, "= ", ']');
#elif XIEITE_COMPILER_TYPE_WINDOWS
        return xieite::strings::between(xieite::strings::after(string, " __"), '<', ">(");
#endif
    };
    constexpr static auto data = xieite::containers::makeArray<char, get().size()>(get());
    return std::string_view(data.begin(), data.end());
}

export namespace xieite::types {
    template <typename Type>
    constexpr std::string_view name = getName<Type>();
}
