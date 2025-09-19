# Getting Started with XIEITE

## Overview

XIEITE is a modern C++20/23 header-only utility library providing 616 utilities across 8 categories. This guide will help you quickly integrate and start using XIEITE in your projects.

## Installation

### Requirements

- **C++ Standard**: C++20 or later (C++23 for some features)
- **Compilers**: GCC 11+, Clang 14+, MSVC 19.29+
- **Build System**: Any (CMake recommended)

### Option 1: Direct Include

Simply copy the `include/xieite` directory to your project:

```bash
git clone https://github.com/Eczbek/xieite.git
cp -r xieite/include/xieite /path/to/your/project/include/
```

### Option 2: CMake Integration

Add XIEITE as a subdirectory:

```cmake
add_subdirectory(external/xieite)
target_link_libraries(your_target PRIVATE xieite::xieite)
```

Or use FetchContent:

```cmake
include(FetchContent)
FetchContent_Declare(
    xieite
    GIT_REPOSITORY https://github.com/Eczbek/xieite.git
    GIT_TAG main
)
FetchContent_MakeAvailable(xieite)

target_link_libraries(your_target PRIVATE xieite::xieite)
```

### Option 3: Single Header Include

For specific utilities, include individual headers:

```cpp
#include <xieite/pp/arrow.hpp>     // Just arrow macros
#include <xieite/trait/is_all.hpp> // Just is_all trait
#include <xieite/fn/memoize.hpp>   // Just memoize function
```

## Your First XIEITE Program

### Hello World with XIEITE

```cpp
#include <xieite/pp/arrow.hpp>
#include <iostream>
#include <string>

auto greet(std::string_view name)
    XIEITE_ARROW("Hello, " + std::string(name) + "!")

int main() {
    std::cout << greet("XIEITE") << std::endl;
    return 0;
}
```

### Compile and Run

```bash
# With g++
g++ -std=c++20 -I/path/to/xieite/include hello.cpp -o hello
./hello

# With clang++ (C++23 required for some features)
clang++ -std=c++23 -I/path/to/xieite/include hello.cpp -o hello
./hello

# With CMake
cmake -B build
cmake --build build
./build/hello
```

## Core Features Quick Tour

### 1. Arrow Macros - Simplified Function Syntax

```cpp
#include <xieite/pp/arrow.hpp>

// Traditional
auto multiply_traditional(int a, int b) -> int {
    return a * b;
}

// With XIEITE arrow macro
auto multiply(int a, int b)
    XIEITE_ARROW(a * b)

// Auto-deduced return type and noexcept
auto safe_divide(double a, double b)
    XIEITE_ARROW_IF(b != 0, a / b, 0.0)
```

### 2. Type Traits - Advanced Type Queries

```cpp
#include <xieite/trait/is_all.hpp>
#include <xieite/trait/is_any.hpp>

template<typename... Ts>
    requires xieite::is_all_v<std::is_integral, Ts...>
auto sum(Ts... values)
    XIEITE_ARROW((... + values))

static_assert(sum(1, 2, 3) == 6);
// sum(1.0, 2, 3);  // Compilation error - not all integral
```

### 3. Functional Programming

```cpp
#include <xieite/fn/memoize.hpp>
#include <xieite/fn/reverse_args.hpp>

// Memoization
auto expensive_fib = xieite::memoize([](int n) {
    if (n <= 1) return n;
    return expensive_fib(n - 1) + expensive_fib(n - 2);
});
auto result = expensive_fib(20);  // Fast with memoization

// Argument reversal
auto divide = [](int a, int b) { return a / b; };
auto rev_divide = xieite::reverse_args(divide);
auto result2 = rev_divide(2, 10);  // 10/2 = 5
```

### 4. Compile-Time Utilities

```cpp
#include <xieite/data/fixed_array.hpp>
#include <xieite/math/factorial.hpp>
#include <xieite/math/fib.hpp>

// Compile-time array operations
constexpr xieite::fixed_array<int, 5> arr{1, 2, 3, 4, 5};
constexpr auto sum = arr.apply([](auto... values) { return (values + ...); });  // 15
static_assert(sum == 15);

// Compile-time math - factorial and fib are lookup tables
constexpr auto fact = xieite::factorial<int>[5];
static_assert(fact == 120);

constexpr auto fibonacci = xieite::fib<int>[10];
static_assert(fibonacci == 55);
```

### 5. String Manipulation

```cpp
#include <xieite/data/str_split.hpp>
#include <xieite/data/str_join.hpp>
#include <string>
#include <iostream>

// String utilities available in XIEITE
std::string input = "hello,world,from,xieite";
// Example: split string using str_split function
```

### 6. Scope Guards

```cpp
#include <xieite/fn/scope_guard.hpp>
#include <fstream>

void process_file(const std::string& path) {
    std::ifstream file(path);

    auto guard = xieite::scope_guard([&] {
        if (file.is_open()) {
            file.close();
            std::cout << "File closed\n";
        }
    });

    // Process file...
    // File automatically closed on scope exit
}
```

## Common Use Cases

### Platform Detection

```cpp
#include <xieite/pp/platform.hpp>
#include <xieite/pp/arch.hpp>

void optimize_for_platform() {
    #if XIEITE_OS_TYPE_WINDOWS
        std::cout << "Running on Windows\n";
    #elif XIEITE_OS_TYPE_LINUX
        std::cout << "Running on Linux\n";
    #elif XIEITE_OS_TYPE_MACOS
        std::cout << "Running on macOS\n";
    #endif

    #if XIEITE_ARCH_TYPE_X86_64
        std::cout << "x64 architecture\n";
    #elif XIEITE_ARCH_TYPE_AARCH64
        std::cout << "ARM64 architecture\n";
    #endif
}
```

### Safe Arithmetic

```cpp
#include <xieite/math/add_sat.hpp>
#include <xieite/math/mul_sat.hpp>

// Saturating arithmetic prevents overflow
auto a = xieite::add_sat(INT_MAX, 1);      // Returns INT_MAX
auto b = xieite::mul_sat(1000000, 1000000); // Returns INT_MAX
```

### Container Algorithms

```cpp
#include <vector>
#include <iostream>
#include <algorithm>

std::vector<std::string> names{"Alice", "Bob", "Charlie"};
std::vector<int> ages{25, 30, 35};

// Iterate with index
for (size_t i = 0; i < names.size(); ++i) {
    std::cout << i << ": " << names[i] << '\n';
}

// Iterate both containers
for (size_t i = 0; i < std::min(names.size(), ages.size()); ++i) {
    std::cout << names[i] << " is " << ages[i] << " years old\n";
}
```

## Project Structure Example

```
my_project/
├── CMakeLists.txt
├── external/
│   └── xieite/          # XIEITE library
├── include/
│   └── my_app/
│       └── config.hpp
├── src/
│   └── main.cpp
└── tests/
    └── test_utilities.cpp
```

### Sample CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.16)
project(MyApp CXX)

set(CMAKE_CXX_STANDARD 23)  # Use C++23 for all features
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add XIEITE
add_subdirectory(external/xieite)

# Create executable
add_executable(my_app src/main.cpp)

# Link XIEITE
target_link_libraries(my_app PRIVATE xieite::xieite)

# Include directories
target_include_directories(my_app PRIVATE include)
```

## Best Practices

### 1. Include What You Use

```cpp
// Include only the headers you need
#include <xieite/pp/arrow.hpp>
#include <xieite/fn/memoize.hpp>
```

### 2. Leverage Compile-Time Features

```cpp
// Use constexpr where possible - remember lookup tables!
constexpr auto result = xieite::fib<int>[10];

// Use concepts for better error messages
template<typename T>
    requires xieite::is_numeric_v<T>
auto process(T value) { /* ... */ }
```

### 3. Platform-Specific Code

```cpp
#if XIEITE_COMPILER_TYPE_GCC
    #pragma GCC optimize("O3")
#elif XIEITE_COMPILER_TYPE_CLANG
    #pragma clang optimize on
#endif
```

## Troubleshooting

### Common Issues and Solutions

#### Issue: Compilation Errors with Concepts
**Solution**: Ensure C++20 is enabled (C++23 for some features):
```bash
clang++ -std=c++23 ...  # For full feature set
g++ -std=c++20 ...      # For basic features
```

#### Issue: Header Not Found
**Solution**: Check include path:
```bash
g++ -I/path/to/xieite/include ...
```

#### Issue: Linker Errors
**Solution**: XIEITE is header-only, no linking required. If you see linker errors, they're from your code or other libraries.

#### Issue: factorial or fib not working
**Solution**: These are lookup tables, not functions:
```cpp
// Wrong:
auto f = xieite::factorial(5);

// Correct:
auto f = xieite::factorial<int>[5];
```

## Next Steps

1. **Explore Categories**: Browse the different utility categories:
   - [Preprocessor Utilities](../../categories/pp/README.md)
   - [Type Traits](../../categories/trait/README.md)
   - [Functional Programming](../../categories/fn/README.md)
   - [Data Structures](../../categories/data/README.md)

2. **Read API Reference**: Detailed documentation for all 616 utilities:
   - [Complete API Reference](../../reference/README.md)

3. **Advanced Examples**: See complex usage patterns:
   - [Advanced Patterns](../advanced/README.md)
   - [Template Metaprogramming](../advanced/templates.md)

4. **Integration Examples**: Real-world integration:
   - [CMake Integration](../integration/cmake.md)
   - [Application Example](../integration/application.md)

## Quick Reference Card

| Category | Key Headers | Common Uses |
|----------|------------|-------------|
| `pp` | `arrow.hpp`, `toggle.hpp` | Function macros, conditional compilation |
| `trait` | `is_all.hpp`, `add_const.hpp` | Type traits, SFINAE helpers |
| `math` | `factorial.hpp`, `add_sat.hpp` | Math lookup tables, safe arithmetic |
| `data` | `str_split.hpp`, `fixed_array.hpp` | String/container utilities |
| `fn` | `memoize.hpp`, `scope_guard.hpp` | Functional programming, RAII |
| `meta` | `type_list.hpp`, `apply.hpp` | Template metaprogramming |
| `pp` | `platform.hpp`, `arch.hpp` | Platform detection |
| `io` | `print.hpp`, `scan.hpp` | I/O utilities |

## Community and Support

- **Repository**: [github.com/Eczbek/xieite](https://github.com/Eczbek/xieite)
- **Issues**: Report bugs or request features on GitHub
- **License**: [Check repository for license details]

Welcome to XIEITE! Start with simple utilities and gradually explore the advanced features as you become comfortable with the library.