# Basic Usage Example

## Simple Utility Usage Patterns

This example demonstrates basic usage of XIEITE utilities for common programming tasks.

```cpp
// basic_example.cpp
#include <iostream>
#include <vector>
#include <string>

// Math utilities
#include <xieite/math/abs.hpp>
#include <xieite/math/clamp.hpp>
#include <xieite/math/almost_equal.hpp>
#include <xieite/math/sign.hpp>

// String utilities
#include <xieite/data/split_str.hpp>
#include <xieite/data/join_str.hpp>
#include <xieite/data/trim_str.hpp>

// Function utilities
#include <xieite/fn/scope_exit.hpp>
#include <xieite/fn/finally.hpp>

// I/O utilities
#include <xieite/io/log.hpp>
#include <xieite/io/dump.hpp>

// System utilities
#include <xieite/sys/nproc.hpp>
#include <xieite/sys/stopwatch.hpp>

int main() {
    // Math operations with overflow safety
    {
        xieite::log::info("=== Math Utilities ===");

        // Safe absolute value
        int negative = -42;
        auto positive = xieite::abs(negative);
        xieite::log::info("abs({}) = {}", negative, positive);

        // Clamping values
        double value = 150.0;
        auto clamped = xieite::clamp(value, 0.0, 100.0);
        xieite::log::info("clamp({}, 0, 100) = {}", value, clamped);

        // Floating-point comparison
        double a = 0.1 + 0.2;
        double b = 0.3;
        bool equal = xieite::almost_equal(a, b);
        xieite::log::info("{} ≈ {} : {}", a, b, equal);

        // Sign detection
        for (int x : {-5, 0, 10}) {
            xieite::log::info("sign({}) = {}", x, xieite::sign(x));
        }
    }

    // String manipulation
    {
        xieite::log::info("\n=== String Utilities ===");

        // String splitting
        std::string csv = "apple,banana,orange,grape";
        auto fruits = xieite::split_str(csv, ',');
        xieite::log::info("Split '{}' into {} parts", csv, fruits.size());

        // String joining
        std::vector<std::string> words = {"Hello", "XIEITE", "World"};
        auto sentence = xieite::join_str(words, " ");
        xieite::log::info("Joined: '{}'", sentence);

        // String trimming
        std::string padded = "  \t Hello World \n ";
        auto trimmed = xieite::trim_str(padded);
        xieite::log::info("Trimmed: '{}' -> '{}'", padded, trimmed);
    }

    // RAII and scope guards
    {
        xieite::log::info("\n=== Scope Guards ===");

        // Automatic cleanup
        {
            xieite::scope_exit cleanup([] {
                xieite::log::info("Scope exited - cleaning up");
            });

            xieite::log::info("Doing work in scope...");
            // Work happens here
        } // cleanup runs here

        // Finally block pattern
        auto process_file = [](const std::string& filename) {
            auto finally = xieite::finally([&] {
                xieite::log::info("Closing file: {}", filename);
            });

            xieite::log::info("Processing file: {}", filename);
            // File processing logic

            if (filename.empty()) {
                xieite::log::error("Empty filename!");
                return false;
            }
            return true;
        };

        process_file("data.txt");
        process_file("");
    }

    // System information
    {
        xieite::log::info("\n=== System Information ===");

        // CPU count
        auto cpus = xieite::nproc();
        xieite::log::info("Available CPUs: {}", cpus);

        // Timing operations
        xieite::stopwatch timer;
        timer.start();

        // Simulate work
        std::vector<int> data(1000000);
        std::generate(data.begin(), data.end(), std::rand);
        std::sort(data.begin(), data.end());

        timer.stop();
        auto elapsed = timer.total<std::chrono::milliseconds>();
        xieite::log::info("Sorting took {} ms", elapsed.count());
    }

    // Debug output
    {
        xieite::log::info("\n=== Debug Output ===");

        int x = 42;
        std::vector<int> vec{1, 2, 3, 4, 5};
        std::string str = "Debug";

        // Dump variables for debugging
        xieite::dump(x);
        xieite::dump(vec);
        xieite::dump(str);

        // Multiple values at once
        xieite::dump(x, vec, str);
    }

    xieite::log::info("\n=== Example Complete ===");
    return 0;
}
```

## Building and Running

### With CMake

```cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(xieite_basic_example)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find XIEITE
find_package(xieite REQUIRED)

add_executable(basic_example basic_example.cpp)
target_link_libraries(basic_example PRIVATE xieite::xieite)
```

```bash
mkdir build && cd build
cmake ..
cmake --build .
./basic_example
```

### Direct Compilation

```bash
# GCC/Clang
g++ -std=c++20 -I/path/to/xieite/include basic_example.cpp -o basic_example

# MSVC
cl /std:c++20 /I"C:\path\to\xieite\include" basic_example.cpp
```

## Expected Output

```
INFO  [2024-01-15 10:30:45] basic_example.cpp:main:35: === Math Utilities ===
INFO  [2024-01-15 10:30:45] basic_example.cpp:main:40: abs(-42) = 42
INFO  [2024-01-15 10:30:45] basic_example.cpp:main:45: clamp(150, 0, 100) = 100
INFO  [2024-01-15 10:30:45] basic_example.cpp:main:51: 0.3 ≈ 0.3 : true
INFO  [2024-01-15 10:30:45] basic_example.cpp:main:55: sign(-5) = -1
INFO  [2024-01-15 10:30:45] basic_example.cpp:main:55: sign(0) = 0
INFO  [2024-01-15 10:30:45] basic_example.cpp:main:55: sign(10) = 1

INFO  [2024-01-15 10:30:45] basic_example.cpp:main:60: === String Utilities ===
INFO  [2024-01-15 10:30:45] basic_example.cpp:main:65: Split 'apple,banana,orange,grape' into 4 parts
INFO  [2024-01-15 10:30:45] basic_example.cpp:main:70: Joined: 'Hello XIEITE World'
INFO  [2024-01-15 10:30:45] basic_example.cpp:main:75: Trimmed: '   Hello World  ' -> 'Hello World'

INFO  [2024-01-15 10:30:45] basic_example.cpp:main:79: === Scope Guards ===
INFO  [2024-01-15 10:30:45] basic_example.cpp:main:86: Doing work in scope...
INFO  [2024-01-15 10:30:45] basic_example.cpp:main:83: Scope exited - cleaning up
INFO  [2024-01-15 10:30:45] basic_example.cpp:main:95: Processing file: data.txt
INFO  [2024-01-15 10:30:45] basic_example.cpp:main:92: Closing file: data.txt
INFO  [2024-01-15 10:30:45] basic_example.cpp:main:95: Processing file:
ERROR [2024-01-15 10:30:45] basic_example.cpp:main:99: Empty filename!
INFO  [2024-01-15 10:30:45] basic_example.cpp:main:92: Closing file:

INFO  [2024-01-15 10:30:45] basic_example.cpp:main:109: === System Information ===
INFO  [2024-01-15 10:30:45] basic_example.cpp:main:113: Available CPUs: 8
INFO  [2024-01-15 10:30:45] basic_example.cpp:main:126: Sorting took 73 ms

INFO  [2024-01-15 10:30:45] basic_example.cpp:main:131: === Debug Output ===
x = 42
vec = {1, 2, 3, 4, 5}
str = "Debug"
x = 42, vec = {1, 2, 3, 4, 5}, str = "Debug"

INFO  [2024-01-15 10:30:45] basic_example.cpp:main:146: === Example Complete ===
```

## Key Takeaways

1. **Header-Only**: Simply include the headers you need
2. **Namespace**: All utilities are in the `xieite` namespace
3. **Type Safety**: Templates provide compile-time type checking
4. **RAII**: Scope guards ensure cleanup happens
5. **Cross-Platform**: Works on Linux, Windows, and macOS
6. **Zero Dependencies**: XIEITE is self-contained

---

*Next: [Advanced Template Metaprogramming Example](advanced_templates.md)*