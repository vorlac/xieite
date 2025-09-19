# Format Helpers

## Overview

XIEITE provides C++20-based formatting utilities that extend the standard library's formatting capabilities with convenient debug output, logging, and pretty-printing functions. These utilities leverage `std::format` and `std::print` to provide modern, type-safe formatting with compile-time format string validation.

## Debug Output Utilities

### Generic Value Dumping
Implementation: `include/xieite/io/dump.hpp` (lines 15-32)

```cpp
template<xieite::fixed_str delim = " ", bool newline = true, typename... Args>
void dump(std::FILE* file, Args&&... args) noexcept {
    static constexpr auto segment = xieite::fixed_str("{}") + delim;
    static constexpr std::size_t size = sizeof...(Args) * segment.size() - (!!sizeof...(Args) * delim.size());
    static constexpr auto fmt = xieite::unroll<size>([]<std::size_t... i> {
        return xieite::fixed_array { segment[i % segment.size()]... };
    });
    if constexpr (newline) {
        std::println(file, std::format_string<Args...>(std::string_view(fmt.data(), size)), XIEITE_FWD(args)...);
    } else {
        std::print(file, std::format_string<Args...>(std::string_view(fmt.data(), size)), XIEITE_FWD(args)...);
    }
}

template<xieite::fixed_str delim = " ", bool newline = true>
void dump(auto&&... args) noexcept {
    return xieite::dump<delim, newline>(stdout, XIEITE_FWD(args)...);
}
```

Provides debug output with customizable delimiters and optional newlines.

## Structured Logging

### Logging System
Implementation: `include/xieite/io/log.hpp` (lines 14-51)

```cpp
namespace DETAIL_XIEITE::log {
    template<int color, xieite::fixed_str tag, typename... Args>
    struct impl {
        explicit impl(std::format_string<Args...> fmt, Args&&... args,
                     std::source_location src = std::source_location::current()) noexcept;
        explicit impl(std::FILE* file, std::format_string<Args...> fmt, Args&&... args,
                     std::source_location src = std::source_location::current()) noexcept;
    };
}

namespace xieite::log {
    DETAIL_XIEITE_LOGGER(info, 0, "INFO ")    // White text
    DETAIL_XIEITE_LOGGER(warn, 33, "WARN ")   // Yellow text
    DETAIL_XIEITE_LOGGER(error, 31, "ERROR")  // Red text
}
```

Provides structured logging with automatic source location and colored output.

## Position Utilities

### 2D Position Representation
Implementation: `include/xieite/io/pos.hpp` (lines 7-19)

```cpp
struct pos {
    xieite::ssize_t row;
    xieite::ssize_t col;

    [[nodiscard]] explicit(false) constexpr pos() noexcept : row(0), col(0) {}
    [[nodiscard]] constexpr pos(xieite::ssize_t row, xieite::ssize_t col) noexcept
        : row(row), col(col) {}
    [[nodiscard]] friend bool operator==(const xieite::pos&, const xieite::pos&) = default;
};
```

Represents 2D positions for text formatting and cursor positioning.

## Usage Examples

### Basic Debug Output
```cpp
#include <xieite/io/dump.hpp>
#include <vector>
#include <string>

void debug_examples() {
    // Simple value dumping
    xieite::dump(42, 3.14, "hello");
    // Output: 42 3.14 hello

    // Custom delimiter
    xieite::dump<", ">(1, 2, 3, 4, 5);
    // Output: 1, 2, 3, 4, 5

    // No newline (for inline output)
    xieite::dump<" | ", false>(std::string("start"), 100, std::string("end"));
    std::cout << " <-- inline output\n";
    // Output: start | 100 | end <-- inline output

    // Output to file
    std::FILE* file = std::fopen("debug.txt", "w");
    xieite::dump<"\n">(file, "Line 1", "Line 2", "Line 3");
    std::fclose(file);
    // File contents:
    // Line 1
    // Line 2
    // Line 3

    // Complex types
    std::vector<int> vec{1, 2, 3};
    std::string text = "formatted";
    xieite::dump<" -> ">(vec.size(), text, vec.capacity());
    // Output: 3 -> formatted -> 3
}
```

### Structured Logging
```cpp
#include <xieite/io/log.hpp>
#include <fstream>

void logging_examples() {
    // Basic logging (outputs to stdout with colors)
    xieite::log::info("Application started successfully");
    // Output: INFO  [2024-01-15 14:30:45] main.cpp:main:42: Application started successfully

    xieite::log::warn("Configuration file not found, using defaults");
    // Output: WARN  [2024-01-15 14:30:45] main.cpp:main:43: Configuration file not found, using defaults

    xieite::log::error("Failed to connect to database: {}", "Connection timeout");
    // Output: ERROR [2024-01-15 14:30:45] main.cpp:main:44: Failed to connect to database: Connection timeout

    // Logging to file (no color codes)
    std::FILE* log_file = std::fopen("application.log", "a");
    xieite::log::info(log_file, "User {} logged in from IP {}", "john_doe", "192.168.1.100");
    xieite::log::error(log_file, "Database error: code {}, message: {}", 1045, "Access denied");
    std::fclose(log_file);
    // File output (no ANSI color codes):
    // INFO  [2024-01-15 14:30:45] main.cpp:main:50: User john_doe logged in from IP 192.168.1.100
    // ERROR [2024-01-15 14:30:45] main.cpp:main:51: Database error: code 1045, message: Access denied

    // Format string validation at compile time
    int user_id = 12345;
    std::string action = "file_upload";
    xieite::log::info("User {} performed action '{}' at timestamp {}",
                      user_id, action, std::time(nullptr));
}
```

### Position-Based Formatting
```cpp
#include <xieite/io/pos.hpp>
#include <xieite/io/dump.hpp>
#include <vector>
#include <iostream>

class TextGrid {
private:
    std::vector<std::string> lines_;
    xieite::pos cursor_;

public:
    TextGrid(std::size_t rows, std::size_t cols)
        : lines_(rows, std::string(cols, ' ')) {}

    void set_cursor(xieite::pos position) {
        cursor_ = position;
    }

    void write_at(xieite::pos position, char c) {
        if (position.row >= 0 && position.row < static_cast<xieite::ssize_t>(lines_.size()) &&
            position.col >= 0 && position.col < static_cast<xieite::ssize_t>(lines_[position.row].size())) {
            lines_[position.row][position.col] = c;
        }
    }

    void write_string_at(xieite::pos position, const std::string& text) {
        for (std::size_t i = 0; i < text.length(); ++i) {
            write_at({position.row, position.col + static_cast<xieite::ssize_t>(i)}, text[i]);
        }
    }

    void move_cursor(xieite::ssize_t delta_row, xieite::ssize_t delta_col) {
        cursor_.row += delta_row;
        cursor_.col += delta_col;
    }

    void print() const {
        for (const auto& line : lines_) {
            std::cout << line << "\n";
        }
        xieite::dump<"">("Cursor at: ({}, {})", cursor_.row, cursor_.col);
    }
};

void position_example() {
    TextGrid grid(5, 20);

    // Draw a simple pattern
    grid.write_string_at({0, 0}, "Hello, World!");
    grid.write_string_at({1, 2}, "XIEITE");
    grid.write_string_at({2, 0}, "Grid Example");

    // Set cursor and move it
    grid.set_cursor({3, 5});
    grid.move_cursor(0, 3);  // Move right 3 positions

    grid.print();
}
```

## Advanced Patterns

### Custom Formatter Integration
```cpp
#include <xieite/io/dump.hpp>
#include <xieite/io/log.hpp>
#include <format>
#include <vector>
#include <map>

// Custom formattable type
struct Point3D {
    double x, y, z;
};

// Custom formatter for Point3D
template<>
struct std::formatter<Point3D> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    auto format(const Point3D& point, std::format_context& ctx) const {
        return std::format_to(ctx.out(), "({:.2f}, {:.2f}, {:.2f})",
                             point.x, point.y, point.z);
    }
};

void custom_formatting_examples() {
    Point3D origin{0.0, 0.0, 0.0};
    Point3D vertex{1.5, 2.7, -0.8};

    // Works with dump
    xieite::dump<" | ">(origin, vertex);
    // Output: (0.00, 0.00, 0.00) | (1.50, 2.70, -0.80)

    // Works with logging
    xieite::log::info("Calculated distance between {} and {}: {:.3f}",
                      origin, vertex,
                      std::sqrt(vertex.x*vertex.x + vertex.y*vertex.y + vertex.z*vertex.z));
}
```

### Performance Monitoring Formatter
```cpp
#include <xieite/io/log.hpp>
#include <xieite/io/dump.hpp>
#include <chrono>
#include <format>

class PerformanceLogger {
private:
    std::chrono::high_resolution_clock::time_point start_time_;
    std::string operation_name_;

public:
    PerformanceLogger(const std::string& operation)
        : start_time_(std::chrono::high_resolution_clock::now())
        , operation_name_(operation) {
        xieite::log::info("Started operation: {}", operation_name_);
    }

    ~PerformanceLogger() {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
            end_time - start_time_);

        if (duration.count() > 10000) {  // > 10ms
            xieite::log::warn("Slow operation '{}' took {:.3f}ms",
                             operation_name_, duration.count() / 1000.0);
        } else {
            xieite::log::info("Completed operation '{}' in {}μs",
                             operation_name_, duration.count());
        }
    }

    void checkpoint(const std::string& checkpoint_name) {
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(
            now - start_time_);
        xieite::log::info("Checkpoint '{}' in operation '{}': {}μs elapsed",
                         checkpoint_name, operation_name_, elapsed.count());
    }
};

void performance_example() {
    {
        PerformanceLogger logger("Data Processing");

        // Simulate work
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        logger.checkpoint("Data loaded");

        std::this_thread::sleep_for(std::chrono::milliseconds(3));
        logger.checkpoint("Data processed");

        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        // Destructor logs completion time
    }
}
```

### Conditional Debug Output
```cpp
#include <xieite/io/dump.hpp>
#include <xieite/io/log.hpp>

template<bool DebugEnabled>
class ConditionalDebugger {
public:
    template<typename... Args>
    void debug_dump(Args&&... args) const {
        if constexpr (DebugEnabled) {
            xieite::dump<" | ", true>(std::forward<Args>(args)...);
        }
    }

    template<typename... Args>
    void debug_log(std::format_string<Args...> fmt, Args&&... args) const {
        if constexpr (DebugEnabled) {
            xieite::log::info(fmt, std::forward<Args>(args)...);
        }
    }

    template<typename... Args>
    void trace_log(std::format_string<Args...> fmt, Args&&... args) const {
        if constexpr (DebugEnabled) {
            xieite::log::info("[TRACE] " + std::string(fmt.get()), std::forward<Args>(args)...);
        }
    }
};

void conditional_debug_example() {
    // Debug build
    constexpr bool is_debug =
#ifdef NDEBUG
        false;
#else
        true;
#endif

    ConditionalDebugger<is_debug> debugger;

    int x = 42;
    std::string msg = "processing";

    debugger.debug_dump("Value:", x, "Status:", msg);  // Only outputs in debug builds
    debugger.debug_log("Processing value {} with status '{}'", x, msg);
    debugger.trace_log("Function entry: x={}", x);
}
```

## Implementation Details

### Compile-Time Format String Generation
The dump utility (dump.hpp:17-21) employs:
- Compile-time string concatenation using `xieite::fixed_str`
- Template-based format string generation with `xieite::unroll`
- Constexpr array construction for format patterns

### Source Location Integration
The logging system (log.hpp:17, 20) utilizes:
- `std::source_location::current()` for automatic file/line/function capture
- Default parameter mechanism for transparent source location passing
- Formatted timestamp integration with `std::chrono`

### ANSI Color Code Management
The logging implementation (log.hpp:26-30) handles:
- Conditional color output based on file stream type
- ANSI escape sequence injection for terminal output
- Plain text output for file redirection

### Template Deduction Guides
Both utilities provide (dump.hpp:29-32, log.hpp:42-45):
- Class template argument deduction for automatic type inference
- Overloaded constructors for different output targets
- Perfect forwarding for argument preservation

## Performance Considerations

- **Compile-time optimization**: Format strings generated at compile time
- **Zero-cost abstractions**: Debug output can be completely eliminated in release builds
- **Stream efficiency**: Uses modern `std::print` and `std::println` for optimal output
- **Memory efficiency**: Fixed-size compile-time strings avoid dynamic allocation

## Best Practices

1. **Use appropriate log levels** - info for normal operation, warn for recoverable issues, error for failures
2. **Leverage compile-time format validation** - Format string errors caught at compile time
3. **Consider output destinations** - Use file output for production logging, stdout for debugging
4. **Minimize format complexity** - Simple format strings compile faster and are more readable

## Common Use Cases

### Application Diagnostics
```cpp
#include <xieite/io/log.hpp>

void application_startup() {
    xieite::log::info("Application version {} starting up", "1.2.3");
    xieite::log::info("Configuration loaded from {}", "config.json");
    xieite::log::info("Database connection established");
}

void handle_user_request(int user_id, const std::string& action) {
    xieite::log::info("User {} requested action: {}", user_id, action);

    try {
        // Process request
        xieite::log::info("Successfully processed {} for user {}", action, user_id);
    } catch (const std::exception& e) {
        xieite::log::error("Failed to process {} for user {}: {}", action, user_id, e.what());
    }
}
```

### Development Debugging
```cpp
#include <xieite/io/dump.hpp>

void debug_algorithm(const std::vector<int>& data) {
    xieite::dump("Input size:", data.size());

    for (std::size_t i = 0; i < data.size(); ++i) {
        if (data[i] < 0) {
            xieite::dump<"">("Negative value at index {}: {}", i, data[i]);
        }
    }

    auto result = std::accumulate(data.begin(), data.end(), 0);
    xieite::dump("Sum:", result);
}
```

### Text Processing Utilities
```cpp
#include <xieite/io/pos.hpp>

class TextEditor {
private:
    std::vector<std::string> lines_;
    xieite::pos cursor_;

public:
    void insert_at(xieite::pos pos, char c) {
        // Implementation for character insertion
    }

    xieite::pos find_next_word() {
        // Find next word boundary from cursor position
        // Return new position
    }

    void format_region(xieite::pos start, xieite::pos end) {
        // Format text in specified region
    }
};
```

## See Also

- [Debug Output](./debug.md) - Additional debugging utilities
- [Stream Utilities](./streams.md) - Stream manipulation functions
- [File Operations](./files.md) - File I/O utilities
- [I/O API Reference](../../reference/api/io.md)