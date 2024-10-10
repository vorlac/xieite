module;

#include <concepts>
#include <memory>
#include <utility>

export module xieite:memory.Shredder;

import :concepts.TriviallyDestructible;

// ICE >:-D
export namespace xieite::memory {
    // template <typename Type>
    //     requires(std::is_trivially_destructible_v<Type>)
    // struct Shredder {
    // public:
    //     constexpr Shredder() {
    //         this->shred();
    //     }

    //     template <typename... Arguments>
    //         requires(std::constructible_from<Type, Arguments...>)
    //     constexpr Shredder(Arguments&&... arguments) noexcept
    //         : value(std::forward<decltype(arguments)>(arguments)...) {
    //     }

    //     template <typename Self>
    //     [[nodiscard]] constexpr auto&& data(this Self&& self) noexcept {
    //         return std::forward_like<Self>(self.value);
    //     }

    //     constexpr void shred() noexcept {
    //         if (!std::is_constant_evaluated()) {
    //             const auto byte = reinterpret_cast<volatile std::byte*>(std::addressof(this->value));
    //             for (std::size_t i = 0; i < sizeof(Type); ++i) {
    //                 byte[i] = static_cast<std::byte>(0);
    //             }
    //         }
    //     }

    //     constexpr ~Shredder() {
    //         this->shred();
    //     }

    // private:
    //     mutable Type value;
    // };
}
