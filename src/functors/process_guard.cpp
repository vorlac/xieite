module;

#include <memory>

#include <xieite/forward.hpp>

export module xieite:functors.ProcessGuard;

import :functors.Function;

export namespace xieite::functors {
    struct ProcessGuard {
    public:
        template <std::invocable<> Functor, auto = [] {
        }>
        ProcessGuard(Functor&& callback) noexcept {
            struct Guard {
                const xieite::functors::Function<void()> callback;
                bool released = false;

                ~Guard() {
                    if (!this->released) {
                        this->callback();
                    }
                }
            };

            static Guard guard = Guard(std::forward<decltype(callback)>(callback));
            this->released = &guard.released;
        }

        void release() noexcept {
            *this->released = true;
        }

    private:
        bool* released;
    };
}
