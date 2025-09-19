# I/O API Reference

## Overview

The io category contains input/output utilities, including file operations, terminal control, logging, and debug output utilities.


## Core I/O Utilities

### `dump`
- **Header**: `io/dump.hpp`
- **Purpose**: Debug output and data dumping utilities

### `file`
- **Header**: `io/file.hpp`
- **Synopsis**: `struct file` - RAII wrapper for FILE* operations
- **Purpose**: Cross-platform file operations with automatic resource management
- **Description**: Provides a modern C++ wrapper around C FILE operations with RAII semantics. Supports Windows wide character paths, file descriptor operations, and automatic cleanup. Handles platform differences transparently.
- **Example**:
    ```cpp
    #include <xieite/io/file.hpp>
    #include <iostream>

    // RAII file handling
    {
        xieite::file f("data.txt", "w");
        if (f) {
            std::fprintf(f.get(), "Hello, World!\n");
        }
        // File automatically closed when f goes out of scope
    }

    // Open from file descriptor
    xieite::file f2(STDOUT_FILENO, "w");

    // Open from standard streams
    xieite::file f3(std::cout);

    // Manual operations
    xieite::file f4;
    f4.open("output.txt", "a");
    if (f4) {
        int fd = f4.desc();  // Get file descriptor
        f4.close();
    }
    ```

### `file_pipe`
- **Header**: `io/file_pipe.hpp`
- **Purpose**: File pipe operations for inter-process communication

### `keys`
- **Header**: `io/keys.hpp`
- **Purpose**: Keyboard input handling

### `keys_char`
- **Header**: `io/keys_char.hpp`
- **Purpose**: Character-based keyboard input

### `log`
- **Header**: `io/log.hpp`
- **Synopsis**: Structured logging with colored output and source location tracking
- **Purpose**: Provides info, warn, and error logging with automatic timestamps and source location
- **Description**: Creates structured log messages with color coding for terminal output, timestamps, and automatic source location tracking. Supports standard format strings and file output.
- **Example**:
    ```cpp
    #include <xieite/io/log.hpp>
    #include <cstdio>

    // Basic logging to stdout with color and source location
    xieite::log::info("Starting application");
    xieite::log::warn("Low memory warning: {}MB remaining", 512);
    xieite::log::error("Failed to open file: {}", "config.txt");

    // Log to specific file
    std::FILE* logfile = std::fopen("app.log", "a");
    xieite::log::info(logfile, "Application event: {}", "startup");
    std::fclose(logfile);

    // Output format: "INFO  [2024-01-15 14:30:25] main.cpp:main:42: Starting application"
    ```

### `pos`
- **Header**: `io/pos.hpp`
- **Purpose**: Position and cursor control

### `read`
- **Header**: `io/read.hpp`
- **Synopsis**: `std::string read(std::istream& stream, int delim = EOF)` and `std::string read(std::FILE* stream, int delim = EOF)`
- **Purpose**: Read content from streams with optional delimiter
- **Description**: Reads from input streams until EOF or a specified delimiter. Supports both C++ streams (istream) and C FILE pointers. Optimized for large file reading with efficient buffering.
- **Example**:
    ```cpp
    #include <xieite/io/read.hpp>
    #include <iostream>
    #include <sstream>
    #include <cstdio>

    // Read entire stream content
    std::istringstream iss("Hello\nWorld\nTest");
    auto content = xieite::read(iss);
    // content contains "Hello\nWorld\nTest"

    // Read until delimiter
    std::istringstream iss2("line1\nline2\nline3");
    auto line = xieite::read(iss2, '\n');
    // line contains "line1"

    // Read from C FILE pointer
    std::FILE* file = std::fopen("data.txt", "r");
    if (file) {
        auto file_content = xieite::read(file);
        std::fclose(file);
    }
    ```

### `term`
- **Header**: `io/term.hpp`
- **Synopsis**: Terminal control and manipulation utilities
- **Purpose**: Provides terminal control functions for cross-platform terminal operations
- **Description**: Contains utilities for terminal manipulation, cursor control, and terminal state management.
- **Example**:
    ```cpp
    #include <xieite/io/term.hpp>
    // Terminal control utilities
    // Terminal control example
    ```

## Usage Notes

The I/O module in XIEITE is minimal. Common I/O operations are:

1. **In other modules**: Check `data/` for string operations
2. **Use standard library**: Many common I/O operations should use `<iostream>`, `<fstream>`, etc.
3. **Platform-specific**: Some operations may be in `sys/` for system-level I/O

## Common I/O Tasks

### File Operations
```cpp
#include <xieite/io/file.hpp>
#include <xieite/io/read.hpp>

// RAII file management
xieite::file f("data.txt", "r");
if (f) {
    auto content = xieite::read(f.get());
    // Process content...
}
```

### Terminal Control
```cpp
#include <xieite/io/term.hpp>
// Terminal manipulation utilities
```

### Logging
```cpp
#include <xieite/io/log.hpp>

// Structured logging with color and timestamps
xieite::log::info("Application started");
xieite::log::warn("Memory usage: {}%", usage);
xieite::log::error("Connection failed: {}", error_msg);
```

### Keyboard Input
```cpp
#include <xieite/io/keys.hpp>
#include <xieite/io/keys_char.hpp>
// Keyboard input handling
```

## Integration with Other Modules

The I/O utilities often work with:
- **Data structures** from `data/` for string manipulation
- **System utilities** from `sys/` for platform-specific I/O
- **Preprocessor macros** from `pp/` for conditional compilation

## Best Practices

1. **Use standard library when appropriate**: XIEITE's I/O module is minimal by design
2. **Platform considerations**: Some I/O operations may be platform-specific

## See Also

- [Data Structures API](./data.md) - For string and container operations
- [System Utilities API](./sys.md) - For system-level I/O operations
- [Complete API Reference](../README.md)
