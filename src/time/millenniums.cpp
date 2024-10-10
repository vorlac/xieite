module;

#include <chrono>

export module xieite:time.Millenniums;

export namespace xieite::time {
    using Millenniums = std::chrono::duration<std::intmax_t, std::ratio<31556952000>>;
}
