module;

#include <chrono>

export module xieite:time.Eons;

export namespace xieite::time {
    using Eons = std::chrono::duration<std::intmax_t, std::ratio<31556952000000000>>;
}
