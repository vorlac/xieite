module;

#include <chrono>

export module xieite:time.Centuries;

export namespace xieite::time {
    using Centuries = std::chrono::duration<std::intmax_t, std::ratio<3155695200>>;
}
