module;

#include <concepts>
#include <thread>

export module xieite:threads.Loop;

export namespace xieite::threads {
    struct Loop {
    public:
        template <std::invocable<> Functor>
        explicit Loop(Functor&& callback) noexcept
            : thread([&callback](const std::stop_token stopToken) {
                while (!stopToken.stop_requested()) {
                    std::invoke(callback);
                }
            }) {
        }

        ~Loop() {
            if (*this) {
                this->stop();
            }
        }

        [[nodiscard]] explicit operator bool() const noexcept {
            return this->thread.joinable();
        }

        void stop() noexcept {
            this->thread.request_stop();
            this->thread.detach();
        }

    private:
        std::jthread thread;
    };
}

// Thanks to uno20001 (https://github.com/uno20001) for help
