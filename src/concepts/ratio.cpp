module;

#include <concepts>
#include <cstdint>
#include <ratio>

export module xieite:concepts.Ratio;

export namespace xieite::concepts {
    template <typename Type>
    concept Ratio = requires { ([]<std::intmax_t numerator, std::intmax_t denominator>(std::type_identity<std::ratio<numerator, denominator>>) {
                               })(std::type_identity<std::remove_cv_t<Type>>()); };
}
