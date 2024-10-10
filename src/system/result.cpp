module;

#include <string>

export module xieite:system.Result;

export namespace xieite::system {
    struct Result {
        std::string output;
        int status = 0;
    };
}
