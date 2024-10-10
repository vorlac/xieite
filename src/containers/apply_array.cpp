module;

#include <array>
#include <concepts>
#include <memory>
#include <type_traits>
#include <utility>

#include <xieite/arrow.hpp>
#include <xieite/forward.hpp>

export module xieite:containers.applyArray;

import :functors.unroll;

export namespace xieite::containers {
    template <typename Functor, typename Value, std::size_t size, std::convertible_to<std::array<Value, size>> Array>
    constexpr auto applyArray(Functor&& functor, Array&& array) noexcept(noexcept(xieite::functors::unroll<size>([&functor, &array]<std::size_t... i> {
        return std::invoke(([&]<auto = [] {
                           }> {
                               if constexpr (::std::same_as<decltype(functor), decltype(functor)> && !::std::same_as<decltype(functor), decltype((functor))>) {
                                   return static_cast<::std::add_rvalue_reference_t<decltype(functor)>>(functor);
                               }
                               else {
                                   return (functor);
                               }
                           })(),
                           std::forward_like<Array>(array[i])...);
    }))) {
        return xieite::functors::unroll<size>([&functor, &array]<std::size_t... i> {
            return std::invoke(([&]<auto = [] {
                               }> {
                                   if constexpr (::std::same_as<decltype(functor), decltype(functor)> && !::std::same_as<decltype(functor), decltype((functor))>) {
                                       return static_cast<::std::add_rvalue_reference_t<decltype(functor)>>(functor);
                                   }
                                   else {
                                       return (functor);
                                   }
                               })(),
                               std::forward_like<Array>(array[i])...);
        });
    }

    template <typename Structure, typename Value, std::size_t size, std::convertible_to<std::array<Value, size>> Array>
    [[nodiscard]] constexpr Structure applyArray(Array&& array)
        XIEITE_ARROW_BASE(xieite::functors::unroll<size>([&array]<std::size_t... i> {
            return Structure(std::forward_like<Array>(array[i])...);
        }))
}
