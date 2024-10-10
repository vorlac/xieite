module;

#include <atomic>

export module xieite:threads.identifier;

namespace {
    std::atomic<std::size_t> nextThreadIdentifier = 0;
}

export namespace xieite::threads {
    thread_local const std::size_t identifier = nextThreadIdentifier++;
}
