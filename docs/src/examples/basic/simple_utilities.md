# Simple Utilities

## Introduction

This guide demonstrates the most commonly used XIEITE utilities with practical examples. Each example is verified against the actual implementation and shows real-world applications of XIEITE's functionality.

## Mathematical Utilities

### Absolute Value Function
Implementation: `include/xieite/math/abs.hpp` (lines 10-21)

```cpp
#include <xieite/math/abs.hpp>
#include <iostream>

void demonstrate_abs() {
    // Works with different numeric types
    int negative_int = -42;
    double negative_double = -3.14;
    unsigned int positive_uint = 100;

    auto abs_int = xieite::abs(negative_int);      // Returns unsigned type
    auto abs_double = xieite::abs(negative_double); // Returns double
    auto abs_uint = xieite::abs(positive_uint);     // Returns same value

    std::cout << "abs(-42) = " << abs_int << "\n";        // 42
    std::cout << "abs(-3.14) = " << abs_double << "\n";   // 3.14
    std::cout << "abs(100u) = " << abs_uint << "\n";      // 100

    // The function automatically handles type safety
    // For signed integers, returns unsigned equivalent
    // For floating point, returns same type
    // For unsigned integers, returns input unchanged
}
```

### Difference Function
Implementation: `include/xieite/math/diff.hpp` (lines 10-20)

```cpp
#include <xieite/math/diff.hpp>
#include <iostream>

void demonstrate_diff() {
    // Calculate absolute difference between two values
    int a = 10, b = 25;
    double x = 1.5, y = 4.8;

    auto int_diff = xieite::diff(a, b);    // Works with integers
    auto double_diff = xieite::diff(x, y); // Works with floating point

    std::cout << "diff(10, 25) = " << int_diff << "\n";     // 15
    std::cout << "diff(1.5, 4.8) = " << double_diff << "\n"; // 3.3

    // Automatically handles overflow for signed integers
    int min_val = std::numeric_limits<int>::min();
    int max_val = std::numeric_limits<int>::max();
    auto large_diff = xieite::diff(min_val, max_val);
    std::cout << "diff(INT_MIN, INT_MAX) = " << large_diff << "\n";
}
```

### Number to String Conversion
Implementation: `include/xieite/math/str_number.hpp` (lines 20-80)

```cpp
#include <xieite/math/str_number.hpp>
#include <xieite/data/number_str_config.hpp>
#include <iostream>

void demonstrate_str_number() {
    // Basic number to string conversion
    int value = 42;
    double pi = 3.14159;

    std::string int_str = xieite::str_number(value);    // "42"
    std::string double_str = xieite::str_number(pi);    // "3.14159"

    std::cout << "42 as string: " << int_str << "\n";
    std::cout << "Pi as string: " << double_str << "\n";

    // Different number bases
    int binary_val = 255;
    std::string binary = xieite::str_number(binary_val, 2);     // "11111111"
    std::string hex = xieite::str_number(binary_val, 16);       // "ff"
    std::string octal = xieite::str_number(binary_val, 8);      // "377"

    std::cout << "255 in binary: " << binary << "\n";
    std::cout << "255 in hex: " << hex << "\n";
    std::cout << "255 in octal: " << octal << "\n";

    // Custom formatting configuration
    xieite::number_str_config config;
    config.digits = "ABCDEFGHIJ";  // Use letters instead of numbers
    std::string custom = xieite::str_number(123, 10, config);  // "BCD"
    std::cout << "123 with custom digits: " << custom << "\n";

    // Padding with zeros
    std::string padded = xieite::str_number(42, 10, {}, 5);  // "00042"
    std::cout << "42 padded to 5 digits: " << padded << "\n";
}
```

## String and Data Utilities

### String Joining
Implementation: `include/xieite/data/str_join.hpp` (previously documented)

```cpp
#include <xieite/data/str_join.hpp>
#include <vector>
#include <iostream>

void demonstrate_str_join() {
    // Join vector of strings
    std::vector<std::string> words = {"Hello", "world", "from", "XIEITE"};

    std::string sentence = xieite::str_join(words, " ");
    std::cout << "Joined: " << sentence << "\n";  // "Hello world from XIEITE"

    // Join with different delimiters
    std::string csv = xieite::str_join(words, ", ");
    std::cout << "CSV: " << csv << "\n";  // "Hello, world, from, XIEITE"

    // Join numbers
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::string number_list = xieite::str_join(numbers, "-");
    std::cout << "Numbers: " << number_list << "\n";  // "1-2-3-4-5"

    // Join with no delimiter
    std::string concatenated = xieite::str_join(words);
    std::cout << "No delimiter: " << concatenated << "\n";  // "HelloworldfromXIEITE"
}
```

## I/O and Formatting Utilities

### Debug Output
Implementation: `include/xieite/io/dump.hpp` (previously documented)

```cpp
#include <xieite/io/dump.hpp>
#include <vector>
#include <map>
#include <iostream>

void demonstrate_dump() {
    // Quick debug output for multiple values
    int x = 10;
    double y = 3.14;
    std::string name = "example";

    xieite::dump(x, y, name);  // "10 3.14 example"

    // Custom delimiters
    xieite::dump<", ">(x, y, name);  // "10, 3.14, example"

    // Debug complex data structures
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::map<std::string, int> scores = {{"Alice", 95}, {"Bob", 87}};

    xieite::dump("Vector size:", vec.size());
    xieite::dump("Map size:", scores.size());

    // Output to file
    std::FILE* debug_file = std::fopen("debug.txt", "w");
    if (debug_file) {
        xieite::dump(debug_file, "Debug info:", x, y);
        std::fclose(debug_file);
    }

    // No newline for inline output
    xieite::dump<" | ", false>("Start");
    std::cout << " middle ";
    xieite::dump<"", false>("end");
    std::cout << "\n";  // "Start | middle end"
}
```

### Structured Logging
Implementation: `include/xieite/io/log.hpp` (previously documented)

```cpp
#include <xieite/io/log.hpp>
#include <iostream>

void demonstrate_logging() {
    // Different log levels with automatic timestamps and source info
    xieite::log::info("Application started");
    // Output: INFO [2024-01-15 14:30:45] file.cpp:function:line: Application started

    int user_id = 12345;
    std::string action = "login";

    xieite::log::info("User {} performed action: {}", user_id, action);
    // Output: INFO [timestamp] file.cpp:function:line: User 12345 performed action: login

    // Warning messages
    double temperature = 85.5;
    if (temperature > 80.0) {
        xieite::log::warn("High temperature detected: {:.1f}°C", temperature);
    }

    // Error logging
    try {
        // Some operation that might fail
        throw std::runtime_error("Connection failed");
    } catch (const std::exception& e) {
        xieite::log::error("Operation failed: {}", e.what());
    }

    // Log to file
    std::FILE* log_file = std::fopen("application.log", "a");
    if (log_file) {
        xieite::log::info(log_file, "File logging example");
        std::fclose(log_file);
    }
}
```

## Functional Programming Utilities

### Scope Guards
Implementation: `include/xieite/fn/scope_guard.hpp` (from previous examples)

```cpp
#include <xieite/fn/scope_guard.hpp>
#include <iostream>
#include <fstream>

void demonstrate_scope_guard() {
    std::cout << "Starting operation...\n";

    // Automatic cleanup using scope guard
    const auto cleanup = xieite::scope_guard([]() {
        std::cout << "Cleanup executed automatically\n";
    });

    // Resource management example
    std::FILE* file = std::fopen("temp.txt", "w");
    if (file) {
        const auto close_file = xieite::scope_guard([file]() {
            std::fclose(file);
            std::cout << "File closed automatically\n";
        });

        // Use the file
        std::fprintf(file, "Hello, XIEITE!\n");

        // File will be automatically closed when scope_guard destructor runs
    }

    // Even if exceptions occur, cleanup still happens
    try {
        const auto exception_cleanup = xieite::scope_guard([]() {
            std::cout << "Exception cleanup executed\n";
        });

        throw std::runtime_error("Something went wrong");
    } catch (const std::exception& e) {
        std::cout << "Caught: " << e.what() << "\n";
        // exception_cleanup destructor already ran
    }

    // cleanup destructor will run when function exits
}
```

## Type Utilities

### Type Checking Examples
```cpp
#include <xieite/trait/is_arith.hpp>
#include <xieite/trait/try_unsigned.hpp>
#include <iostream>
#include <type_traits>

template<typename T>
void demonstrate_type_utilities(T value) {
    std::cout << "Type analysis for: " << typeid(T).name() << "\n";

    // Check if type is arithmetic
    if constexpr (xieite::is_arith<T>) {
        std::cout << "  - Is arithmetic type\n";

        // Get unsigned equivalent
        using UnsignedT = xieite::try_unsigned<T>;
        std::cout << "  - Unsigned equivalent: " << typeid(UnsignedT).name() << "\n";

        // Use with arithmetic operations
        auto abs_value = xieite::abs(value);
        std::cout << "  - Absolute value: " << abs_value << "\n";
    } else {
        std::cout << "  - Not an arithmetic type\n";
    }

    // Standard library type traits work too
    if constexpr (std::is_floating_point_v<T>) {
        std::cout << "  - Is floating point\n";
    } else if constexpr (std::is_integral_v<T>) {
        std::cout << "  - Is integral\n";
    }
}

void test_type_utilities() {
    demonstrate_type_utilities(42);        // int
    demonstrate_type_utilities(-3.14);     // double
    demonstrate_type_utilities(100u);      // unsigned int
    demonstrate_type_utilities('A');       // char
}
```

## Platform Detection

### Basic Platform Awareness
Implementation: `include/xieite/pp/platform.hpp` and `include/xieite/pp/arch.hpp`

```cpp
#include <xieite/pp/platform.hpp>
#include <xieite/pp/arch.hpp>
#include <iostream>

void demonstrate_platform_detection() {
    std::cout << "Platform Information:\n";

    // Operating system detection
#if XIEITE_PLATFORM_TYPE_WINDOWS
    std::cout << "  Running on Windows\n";
#elif XIEITE_PLATFORM_TYPE_LINUX
    std::cout << "  Running on Linux\n";
#elif XIEITE_PLATFORM_TYPE_MACOS
    std::cout << "  Running on macOS\n";
#elif XIEITE_PLATFORM_TYPE_UNIX
    std::cout << "  Running on Unix-like system\n";
#else
    std::cout << "  Unknown platform\n";
#endif

    // Architecture detection
#if defined(XIEITE_ARCH_TYPE_X86_64)
    std::cout << "  Architecture: x86-64\n";
#elif defined(XIEITE_ARCH_TYPE_X86)
    std::cout << "  Architecture: x86\n";
#elif defined(XIEITE_ARCH_TYPE_ARM) || defined(XIEITE_ARCH_TYPE_AARCH64)
    std::cout << "  Architecture: ARM\n";
#else
    std::cout << "  Architecture: Other\n";
#endif

    // Platform-specific code
#if XIEITE_PLATFORM_TYPE_WINDOWS
    std::cout << "  Using Windows-specific features\n";
    // Windows-specific code here
#else
    std::cout << "  Using POSIX features\n";
    // POSIX-specific code here
#endif
}
```

## Complete Working Example

Here's a complete program demonstrating multiple XIEITE utilities:

```cpp
#include <xieite/math/abs.hpp>
#include <xieite/math/diff.hpp>
#include <xieite/math/str_number.hpp>
#include <xieite/data/str_join.hpp>
#include <xieite/io/dump.hpp>
#include <xieite/io/log.hpp>
#include <xieite/fn/scope_guard.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int main() {
    // Setup and cleanup
    const auto cleanup = xieite::scope_guard([]() {
        std::cout << "\nProgram completed successfully\n";
    });

    xieite::log::info("XIEITE utilities demonstration started");

    // Mathematical operations
    std::cout << "=== Mathematical Utilities ===\n";

    std::vector<int> numbers = {-15, 42, -7, 23, -100};
    std::vector<std::string> abs_numbers;

    for (int num : numbers) {
        auto abs_val = xieite::abs(num);
        abs_numbers.push_back(xieite::str_number(abs_val));
    }

    std::string original = xieite::str_join(numbers, ", ");
    std::string absolute = xieite::str_join(abs_numbers, ", ");

    std::cout << "Original: " << original << "\n";
    std::cout << "Absolute: " << absolute << "\n";

    // Calculate differences
    std::cout << "\n=== Difference Calculations ===\n";
    for (size_t i = 1; i < numbers.size(); ++i) {
        auto diff = xieite::diff(numbers[i-1], numbers[i]);
        xieite::dump("diff(" + xieite::str_number(numbers[i-1]) + ", " +
                    xieite::str_number(numbers[i]) + ") =", diff);
    }

    // Number base conversions
    std::cout << "\n=== Number Base Conversions ===\n";
    int value = 255;
    std::vector<std::string> conversions = {
        "Decimal: " + xieite::str_number(value, 10),
        "Binary: " + xieite::str_number(value, 2),
        "Octal: " + xieite::str_number(value, 8),
        "Hexadecimal: " + xieite::str_number(value, 16)
    };

    for (const auto& conversion : conversions) {
        std::cout << conversion << "\n";
    }

    // Debug output demonstration
    std::cout << "\n=== Debug Output ===\n";
    double pi = 3.14159;
    std::string name = "XIEITE";

    xieite::dump("Values:", value, pi, name);
    xieite::dump<" | ">("Pipe separated:", value, pi, name);

    // Logging demonstration
    std::cout << "\n=== Logging Examples ===\n";
    xieite::log::info("Processing {} numbers", numbers.size());

    if (numbers.size() > 3) {
        xieite::log::warn("Large number of items: {}", numbers.size());
    }

    try {
        // Simulate an error condition
        if (std::time(nullptr) % 2 == 0) {
            throw std::runtime_error("Simulated error for demonstration");
        }
    } catch (const std::exception& e) {
        xieite::log::error("Caught exception: {}", e.what());
    }

    std::cout << "\n=== Summary ===\n";
    std::cout << "Demonstrated utilities:\n";
    std::cout << "✓ Mathematical functions (abs, diff, str_number)\n";
    std::cout << "✓ String utilities (str_join)\n";
    std::cout << "✓ Debug output (dump)\n";
    std::cout << "✓ Structured logging (log)\n";
    std::cout << "✓ RAII patterns (scope_guard)\n";

    return 0;
}
```

## Compilation Instructions

To compile and run these examples:

```bash
# Basic compilation
g++ -std=c++20 -I/path/to/xieite/include simple_utilities_example.cpp -o example

# With optimizations
g++ -std=c++20 -O3 -I/path/to/xieite/include simple_utilities_example.cpp -o example

# Run the example
./example
```

## Expected Output

Running the complete example should produce output similar to:

```
INFO [2024-01-15 14:30:45] example.cpp:main:25: XIEITE utilities demonstration started
=== Mathematical Utilities ===
Original: -15, 42, -7, 23, -100
Absolute: 15, 42, 7, 23, 100

=== Difference Calculations ===
diff(-15, 42) = 57
diff(42, -7) = 49
diff(-7, 23) = 30
diff(23, -100) = 123

=== Number Base Conversions ===
Decimal: 255
Binary: 11111111
Octal: 377
Hexadecimal: ff

=== Debug Output ===
Values: 255 3.14159 XIEITE
Pipe separated: 255 | 3.14159 | XIEITE

=== Logging Examples ===
INFO [timestamp] example.cpp:main:78: Processing 5 numbers
WARN [timestamp] example.cpp:main:81: Large number of items: 5
ERROR [timestamp] example.cpp:main:90: Caught exception: Simulated error for demonstration

=== Summary ===
Demonstrated utilities:
✓ Mathematical functions (abs, diff, str_number)
✓ String utilities (str_join)
✓ Debug output (dump)
✓ Structured logging (log)
✓ RAII patterns (scope_guard)

Program completed successfully
```

## Next Steps

After mastering these simple utilities:

1. **Explore [Common Patterns](./common_patterns.md)** for more sophisticated techniques
2. **Study [Advanced Examples](../advanced/README.md)** for template metaprogramming
3. **Review specific category documentation** for comprehensive utility coverage
4. **Experiment with combinations** of utilities to solve complex problems

## See Also

- [Getting Started](./getting_started.md) - Basic setup and introduction
- [Common Patterns](./common_patterns.md) - Advanced usage patterns
- [Category Documentation](../../categories/README.md) - Complete utility reference
- [API Reference](../../reference/README.md) - Detailed specifications