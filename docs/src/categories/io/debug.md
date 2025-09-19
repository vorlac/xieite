# Debug Output

## Overview

XIEITE provides debug output capabilities primarily through the utilities documented in [Format Helpers](./formatting.md). The debug functionality centers around the `xieite::dump` utility for quick value output and the structured logging system for development and production debugging.

## Primary Debug Utilities

### Value Dumping
Implementation: `include/xieite/io/dump.hpp`

The `xieite::dump` function provides the core debug output functionality:

```cpp
template<xieite::fixed_str delim = " ", bool newline = true, typename... Args>
void dump(std::FILE* file, Args&&... args) noexcept;

template<xieite::fixed_str delim = " ", bool newline = true>
void dump(auto&&... args) noexcept;
```

### Structured Logging
Implementation: `include/xieite/io/log.hpp`

The logging system provides debug-level output with source location tracking:

```cpp
namespace xieite::log {
    info("Debug message: {}", value);    // Information logging
    warn("Warning: {}", condition);      // Warning logging
    error("Error occurred: {}", error);  // Error logging
}
```

## Quick Reference

### Basic Debug Output
```cpp
#include <xieite/io/dump.hpp>

void debug_function() {
    int x = 42;
    std::string msg = "debug";

    // Simple value dumping
    xieite::dump(x, msg);
    // Output: 42 debug

    // Custom delimiter
    xieite::dump<", ">(x, msg, 3.14);
    // Output: 42, debug, 3.14
}
```

### Development Logging
```cpp
#include <xieite/io/log.hpp>

void debug_with_logging() {
    int value = 100;

    xieite::log::info("Processing value: {}", value);
    // Output: INFO [timestamp] file.cpp:function:line: Processing value: 100

    if (value > 50) {
        xieite::log::warn("High value detected: {}", value);
    }
}
```

### Conditional Debug Output
```cpp
#include <xieite/io/dump.hpp>

template<bool DebugEnabled>
void conditional_debug(auto&&... args) {
    if constexpr (DebugEnabled) {
        xieite::dump(std::forward<decltype(args)>(args)...);
    }
}

// Usage
#ifdef DEBUG
    constexpr bool debug_mode = true;
#else
    constexpr bool debug_mode = false;
#endif

conditional_debug<debug_mode>("Debug:", value, "processed");
```

## Additional Debug Features

### Terminal-Based Debug Output
The terminal utilities in [Scanning and Parsing](./scanning.md) provide additional debug capabilities:

- **Colored output**: Using `xieite::term` for colored debug messages
- **Cursor positioning**: For formatted debug layouts
- **Real-time debugging**: Interactive debug sessions

### File-Based Debug Output
Debug output can be directed to files using the file stream variants:

```cpp
std::FILE* debug_file = std::fopen("debug.log", "a");
xieite::dump(debug_file, "Debug info:", values...);
xieite::log::info(debug_file, "Debug message: {}", info);
std::fclose(debug_file);
```

## See Also

- [Format Helpers](./formatting.md) - Comprehensive formatting and logging utilities
- [Scanning and Parsing](./scanning.md) - Terminal-based debug interaction
- [Stream Utilities](./streams.md) - Stream manipulation for debug output
- [I/O API Reference](../../reference/api/io.md)