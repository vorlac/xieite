module;

#include <memory>

#include <xieite/forward.hpp>

export module xieite:functors.ScopeGuard;

import :functors.Function;

export namespace xieite::functors {
    struct ScopeGuard {
    public:
        template <std::invocable<> Functor>
        constexpr ScopeGuard(Functor&& callback) noexcept
            : callback(std::forward<decltype(callback)>(callback)) {
        }

        constexpr ~ScopeGuard() {
            if (!this->released) {
                this->callback();
            }
        }

        constexpr void release() noexcept {
            this->released = true;
        }

    private:
        xieite::functors::Function<void()> callback;
        bool released = false;
    };
}
