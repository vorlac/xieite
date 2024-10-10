module;

#include <chrono>

export module xieite:time.Decades;

export namespace xieite::time {
    using Decades = std::chrono::duration<std::intmax_t, std::ratio<315569520>>;
}
