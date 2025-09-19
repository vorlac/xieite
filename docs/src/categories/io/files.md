# File Operations

## Overview

XIEITE provides file operation utilities for reading files and executing processes with pipe communication. These utilities offer cross-platform abstractions over system-level file operations with RAII-based resource management.

## Core Components

### File Pipe Operations
Implementation: `include/xieite/io/file_pipe.hpp` (lines 15-78)

```cpp
namespace xieite {
    struct file_pipe {
        [[nodiscard]] file_pipe(const std::string& cmd, const std::string& mode) noexcept;

        int close() noexcept;

        operator bool() const noexcept;
        operator std::FILE*() const noexcept;
    };
}
```

### File Reading
Implementation: `include/xieite/io/read.hpp` (lines 11-44)

```cpp
namespace xieite {
    [[nodiscard]] std::string read(std::FILE* file) noexcept;
    [[nodiscard]] std::string read(const std::string& path) noexcept;
}
```

## Process Pipe Communication

### Creating Process Pipes
```cpp
#include <xieite/io/file_pipe.hpp>

// Execute command and read output
xieite::file_pipe pipe("ls -la", "r");
if (pipe) {
    std::string output = xieite::read(pipe);
    int exit_status = pipe.close();

    if (exit_status == 0) {
        std::cout << "Command output:\n" << output;
    }
}
```

### Platform-Specific Implementation
The file_pipe uses platform-specific functions:
- Unix/Linux: Uses `popen()` and `pclose()` (file_pipe.hpp:28-29)
- Windows: Uses `_popen()` and `_pclose()` (file_pipe.hpp:31-32)

## File Reading Operations

### Reading Entire Files
```cpp
#include <xieite/io/read.hpp>

// Read from file path
std::string content = xieite::read("config.txt");

// Read from FILE* handle
std::FILE* file = std::fopen("data.txt", "r");
if (file) {
    std::string data = xieite::read(file);
    std::fclose(file);
}
```

### Implementation Details
The read functions handle:
- Automatic buffer management (read.hpp:17-39)
- Error checking with errno (read.hpp:21)
- Complete file reading until EOF (read.hpp:25-37)
- RAII cleanup via unique_ptr with custom deleter (read.hpp:15)

## Error Handling

### Process Status Codes
```cpp
xieite::file_pipe compiler("g++ test.cpp -o test", "r");
std::string errors = xieite::read(compiler);
int status = compiler.close();

switch (status) {
    case 0:
        std::cout << "Compilation successful\n";
        break;
    case 1:
        std::cout << "Compilation failed:\n" << errors;
        break;
    default:
        std::cout << "Unknown error: " << status << "\n";
}
```

### File Operation Errors
```cpp
// Read returns empty string on error
std::string config = xieite::read("missing.cfg");
if (config.empty()) {
    // Check errno for specific error
    if (errno == ENOENT) {
        std::cerr << "File not found\n";
    }
}
```

## Common Use Cases

### Running System Commands
```cpp
// Get system information
xieite::file_pipe uname("uname -a", "r");
std::string system_info = xieite::read(uname);
uname.close();

// Check disk usage
xieite::file_pipe df("df -h", "r");
std::string disk_usage = xieite::read(df);
df.close();
```

### Processing Command Output
```cpp
// Find files and process results
xieite::file_pipe find("find . -name '*.cpp'", "r");
std::string files = xieite::read(find);

std::istringstream stream(files);
std::string line;
while (std::getline(stream, line)) {
    std::cout << "Found: " << line << "\n";
}
find.close();
```

### Configuration File Reading
```cpp
// Load application settings
std::string load_config(const std::string& filename) {
    std::string content = xieite::read(filename);

    if (content.empty()) {
        // Fall back to default config
        content = xieite::read("default.cfg");
    }

    return content;
}
```

## Best Practices

1. **Always close pipes** - Call close() to get exit status
2. **Check pipe validity** - Use operator bool() before operations
3. **Handle empty returns** - Empty string may indicate error
4. **Platform considerations** - Test on target platforms

## Implementation Notes

### Resource Management
- file_pipe uses RAII for automatic cleanup (file_pipe.hpp:44-48)
- Custom deleter ensures proper pipe closure (file_pipe.hpp:70-78)
- Move semantics supported, copy disabled (file_pipe.hpp:50-68)

### Buffer Strategy
- Read uses dynamic buffering (read.hpp:25-37)
- Grows string as needed for large files
- Efficient for both small and large files

## Platform Compatibility

| Platform | Process Pipes | File Reading |
|----------|--------------|--------------|
| Linux | ✓ popen/pclose | ✓ Standard C |
| macOS | ✓ popen/pclose | ✓ Standard C |
| Windows | ✓ _popen/_pclose | ✓ Standard C |
| BSD | ✓ popen/pclose | ✓ Standard C |

## See Also

- [Stream Utilities](./streams.md) - Stream manipulation
- [Scanning/Parsing](./scanning.md) - Input parsing utilities
- [Debug Output](./debug.md) - Debug printing utilities
- [I/O API Reference](../../reference/api/io.md)