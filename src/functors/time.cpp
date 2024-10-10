module;

#include <chrono>
#include <concepts>

#include <xieite/forward.hpp>

export module xieite:functors.time;

import :concepts.Clock;
import :concepts.Duration;
import :time.Stopwatch;

export namespace xieite::functors {
    template <xieite::concepts::Duration Duration = std::chrono::nanoseconds, xieite::concepts::Clock Clock = std::chrono::steady_clock, typename... Arguments, std::invocable<Arguments...> Functor>
    [[nodiscard]] Duration time(Functor&& functor, Arguments&&... arguments) noexcept(std::is_nothrow_invocable_v<Functor, Arguments...>) {
        xieite::time::Stopwatch<Clock> stopwatch;
        stopwatch.start();
        std::invoke(std::forward<decltype(functor)>(functor), std::forward<decltype(arguments)>(arguments)...);
        return stopwatch.template total<Duration>();
    }
}
