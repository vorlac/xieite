# Common Patterns

## Introduction

This guide demonstrates frequently used programming patterns with XIEITE utilities. These patterns represent practical applications that solve common development challenges using modern C++ techniques combined with XIEITE's powerful utilities.

## RAII Patterns

### Scope Guards for Resource Management

XIEITE provides `xieite::scope_guard` for automatic resource cleanup:

```cpp
#include <xieite/fn/scope_guard.hpp>
#include <iostream>
#include <fstream>

void file_processing_example() {
    std::ofstream file("temp.txt");

    // Automatically close and clean up file regardless of how function exits
    auto cleanup = xieite::scope_guard([&]() {
        file.close();
        std::remove("temp.txt");
        std::cout << "File cleaned up automatically\n";
    });

    // Do work with file
    file << "Temporary data\n";

    // cleanup.release(); // Call this to prevent cleanup if needed

    // Cleanup happens automatically when scope_guard destructor runs
}
```

**Source Reference**: `include/xieite/fn/scope_guard.hpp:9-28`

The scope guard accepts any invocable and ensures it runs on destruction unless `release()` is called.

### Multiple Resource Management

```cpp
#include <xieite/fn/scope_guard.hpp>
#include <memory>

class ResourceManager {
    std::unique_ptr<int[]> buffer;
    FILE* file_handle = nullptr;

public:
    bool initialize(size_t size, const char* filename) {
        // Allocate buffer
        buffer = std::make_unique<int[]>(size);

        // Set up cleanup for partial initialization failures
        auto cleanup = xieite::scope_guard([&]() {
            if (file_handle) {
                fclose(file_handle);
                file_handle = nullptr;
            }
            buffer.reset();
        });

        // Open file
        file_handle = fopen(filename, "w");
        if (!file_handle) {
            return false; // cleanup runs automatically
        }

        // Success - prevent cleanup
        cleanup.release();
        return true;
    }

    ~ResourceManager() {
        if (file_handle) fclose(file_handle);
        // buffer auto-cleaned by unique_ptr
    }
};
```

## Template Patterns

### Arrow Macros for Clean Function Definitions

XIEITE's arrow macros provide concise function definitions with automatic return type deduction:

```cpp
#include <xieite/pp/arrow.hpp>
#include <xieite/trait/is_arith.hpp>
#include <type_traits>

// Simple arithmetic function with automatic noexcept and return type
template<xieite::is_arith T>
constexpr auto square(T value)
    XIEITE_ARROW(value * value)

// Conditional compilation with arrow macros
template<typename T>
constexpr auto safe_divide(T a, T b)
    XIEITE_ARROW_IF(
        std::floating_point<T>,
        a / b,
        (b != 0) ? a / b : T{}
    )

// No-except guaranteed operations
template<std::integral T>
constexpr auto increment(T value)
    XIEITE_ARROW_NOEX(value + 1)
```

**Source Reference**: `include/xieite/pp/arrow.hpp:12-37`

### Concept-Based Function Overloading

```cpp
#include <xieite/trait/is_arith.hpp>
#include <xieite/pp/arrow.hpp>
#include <string>
#include <iostream>

// Different behavior based on type concepts
template<xieite::is_arith T>
void print_value(T value)
    XIEITE_ARROW(std::cout << "Number: " << value << '\n')

template<typename T>
requires std::convertible_to<T, std::string>
void print_value(const T& value)
    XIEITE_ARROW(std::cout << "String: " << std::string(value) << '\n')

void concept_overloading_example() {
    print_value(42);        // Calls arithmetic version
    print_value(3.14);      // Calls arithmetic version
    print_value("hello");   // Calls string version
}
```

## Error Handling Patterns

### Exception-Safe Operations

```cpp
#include <xieite/fn/scope_guard.hpp>
#include <vector>
#include <stdexcept>

class SafeVector {
    std::vector<int> data;
    bool valid_state = true;

public:
    void risky_operation(const std::vector<int>& new_data) {
        // Save current state
        auto old_data = data;
        auto old_state = valid_state;

        // Set up rollback on failure
        auto rollback = xieite::scope_guard([&]() {
            data = old_data;
            valid_state = old_state;
        });

        // Perform risky operations
        data.clear();
        valid_state = false;

        for (auto value : new_data) {
            if (value < 0) {
                throw std::invalid_argument("Negative values not allowed");
                // rollback happens automatically
            }
            data.push_back(value * 2);
        }

        valid_state = true;
        rollback.release(); // Success - don't rollback
    }
};
```

### RAII for Temporary State Changes

```cpp
#include <xieite/fn/scope_guard.hpp>

class Configuration {
    bool debug_mode = false;
    int verbosity_level = 1;

public:
    template<typename Func>
    auto with_debug_mode(Func&& func) {
        // Temporarily enable debug mode
        bool old_debug = debug_mode;
        debug_mode = true;

        auto restore = xieite::scope_guard([&]() {
            debug_mode = old_debug;
        });

        return func();
    }

    template<typename Func>
    auto with_verbosity(int level, Func&& func) {
        int old_level = verbosity_level;
        verbosity_level = level;

        auto restore = xieite::scope_guard([&]() {
            verbosity_level = old_level;
        });

        return func();
    }
};
```

## Performance Patterns

### Compile-Time Computation

```cpp
#include <xieite/fn/repeat.hpp>
#include <xieite/meta/make_seq.hpp>
#include <array>

// Compile-time array generation using repeat patterns
template<std::size_t N>
consteval auto generate_fibonacci() {
    std::array<int, N> result{};

    if constexpr (N > 0) result[0] = 1;
    if constexpr (N > 1) result[1] = 1;

    // Use compile-time repetition for calculation
    xieite::repeat<N - 2>([&]<auto i>(auto...) {
        constexpr auto index = i + 2;
        result[index] = result[index - 1] + result[index - 2];
    });

    return result;
}

// Usage - computed entirely at compile time
constexpr auto fib_10 = generate_fibonacci<10>();
```

**Source Reference**: `include/xieite/fn/repeat.hpp:11-20`

### Template-Based Loop Unrolling

```cpp
#include <xieite/fn/repeat.hpp>
#include <array>

template<std::size_t N>
constexpr void optimized_array_process(std::array<float, N>& arr) {
    // Unroll loop at compile time for better performance
    xieite::repeat<N>([&]<auto i>(auto...) {
        arr[i] = arr[i] * 2.0f + 1.0f;
    });
}

// Alternative: process in chunks
template<std::size_t N, std::size_t ChunkSize = 4>
constexpr void chunked_process(std::array<float, N>& arr) {
    constexpr auto chunks = N / ChunkSize;
    constexpr auto remainder = N % ChunkSize;

    // Process full chunks
    xieite::repeat<chunks>([&]<auto chunk>(auto...) {
        xieite::repeat<ChunkSize>([&]<auto i>(auto...) {
            constexpr auto index = chunk * ChunkSize + i;
            arr[index] = arr[index] * 2.0f + 1.0f;
        });
    });

    // Process remainder
    if constexpr (remainder > 0) {
        xieite::repeat<remainder>([&]<auto i>(auto...) {
            constexpr auto index = chunks * ChunkSize + i;
            arr[index] = arr[index] * 2.0f + 1.0f;
        });
    }
}
```

## Cross-Platform Patterns

### Platform Detection for Conditional Compilation

```cpp
#include <xieite/pp/platform.hpp>

// Platform-specific implementations
#if XIEITE_PLATFORM_TYPE_WINDOWS
    #include <windows.h>
    void platform_sleep(int milliseconds) {
        Sleep(milliseconds);
    }
#elif XIEITE_PLATFORM_TYPE_UNIX || XIEITE_PLATFORM_TYPE_LINUX
    #include <unistd.h>
    void platform_sleep(int milliseconds) {
        usleep(milliseconds * 1000);
    }
#else
    #include <thread>
    #include <chrono>
    void platform_sleep(int milliseconds) {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
#endif
```

**Source Reference**: `include/xieite/pp/platform.hpp:1-50` (comprehensive platform detection)

### Architecture-Aware Code

```cpp
#include <xieite/pp/platform.hpp>

template<typename T>
constexpr T byte_swap(T value) {
    if constexpr (sizeof(T) == 2) {
        return (value << 8) | (value >> 8);
    } else if constexpr (sizeof(T) == 4) {
        return ((value << 24) & 0xFF000000) |
               ((value << 8)  & 0x00FF0000) |
               ((value >> 8)  & 0x0000FF00) |
               ((value >> 24) & 0x000000FF);
    }
    // Add more sizes as needed
}

template<typename T>
constexpr T to_big_endian(T value) {
    #if XIEITE_ENDIAN_LITTLE
        return byte_swap(value);
    #else
        return value;
    #endif
}
```

## Advanced Patterns

### Function Composition Chains

```cpp
#include <xieite/pp/arrow.hpp>
#include <xieite/trait/is_arith.hpp>

// Chainable operations using arrow macros
template<xieite::is_arith T>
struct MathChain {
    T value;

    constexpr MathChain(T v) : value(v) {}

    constexpr auto add(T x) const
        XIEITE_ARROW(MathChain{value + x})

    constexpr auto multiply(T x) const
        XIEITE_ARROW(MathChain{value * x})

    constexpr auto square() const
        XIEITE_ARROW(MathChain{value * value})

    constexpr operator T() const
        XIEITE_ARROW(value)
};

// Usage: fluent interface pattern
constexpr auto result = MathChain{5}
    .add(3)
    .multiply(2)
    .square()
    .add(1);  // (((5 + 3) * 2)^2 + 1) = 257
```

### Template Parameter Pack Processing

```cpp
#include <xieite/fn/repeat.hpp>
#include <iostream>

template<typename... Args>
void print_indexed_args(Args&&... args) {
    auto arg_tuple = std::forward_as_tuple(args...);

    xieite::repeat<sizeof...(Args)>([&]<auto i>(auto...) {
        std::cout << "Arg " << i << ": " << std::get<i>(arg_tuple) << '\n';
    });
}

// Process variadic templates with compile-time indexing
template<typename... Types>
constexpr auto sum_sizes() {
    std::size_t total = 0;
    xieite::repeat<sizeof...(Types)>([&]<auto i>(auto...) {
        using Type = std::tuple_element_t<i, std::tuple<Types...>>;
        total += sizeof(Type);
    });
    return total;
}
```

## Best Practices

### Combining Patterns

```cpp
#include <xieite/fn/scope_guard.hpp>
#include <xieite/pp/arrow.hpp>
#include <xieite/trait/is_arith.hpp>

template<xieite::is_arith T>
class SafeCalculator {
    T accumulator = T{};
    bool error_state = false;

public:
    // RAII + Arrow macros + Error handling
    template<typename Func>
    auto with_transaction(Func&& func) -> decltype(func(*this)) {
        // Save state
        T old_accumulator = accumulator;
        bool old_error = error_state;

        // Setup rollback
        auto rollback = xieite::scope_guard([&]() {
            accumulator = old_accumulator;
            error_state = old_error;
        });

        // Execute operation
        auto result = func(*this);

        // Commit if no error
        if (!error_state) {
            rollback.release();
        }

        return result;
    }

    constexpr auto add(T value)
        XIEITE_ARROW_IF(
            !error_state,
            (accumulator += value, *this),
            (error_state = true, *this)
        )

    constexpr auto get() const
        XIEITE_ARROW(error_state ? T{} : accumulator)
};
```

## Usage Guidelines

### When to Use These Patterns

1. **RAII Patterns**: For any resource management, temporary state changes, or cleanup operations
2. **Arrow Macros**: For simple functions where return type deduction and noexcept specification are desired
3. **Concept Overloading**: When you need type-safe function dispatch based on type properties
4. **Compile-time Patterns**: For performance-critical code that can be computed at compile time
5. **Platform Patterns**: When writing portable code that needs platform-specific behavior

### Performance Considerations

- Arrow macros have zero runtime overhead
- Scope guards have minimal overhead (one function pointer and bool)
- Compile-time repetition eliminates runtime loops
- Platform detection happens entirely at compile time

### Integration with STL

These patterns work seamlessly with standard library components:

```cpp
#include <xieite/fn/scope_guard.hpp>
#include <algorithm>
#include <vector>

void stl_integration_example() {
    std::vector<int> data{3, 1, 4, 1, 5, 9};

    // Temporarily sort, then restore original order
    auto original_data = data;
    auto restore = xieite::scope_guard([&]() {
        data = original_data;
    });

    std::sort(data.begin(), data.end());

    // Work with sorted data...
    auto it = std::lower_bound(data.begin(), data.end(), 4);

    // restore() happens automatically
}
```

These patterns demonstrate how XIEITE utilities integrate with modern C++ idioms to create clean, efficient, and maintainable code. The combination of compile-time computation, automatic resource management, and type safety provides a powerful foundation for robust applications.