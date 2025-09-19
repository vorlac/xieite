# Stream Utilities

## Overview

XIEITE provides stream manipulation utilities focused on file handle management and terminal I/O operations. The utilities handle platform-specific differences between Unix and Windows systems.

## File Stream Wrapper

### xieite::file Structure
The `file` structure (io/file.hpp:27-180) provides a RAII wrapper around FILE* handles with platform-specific support:

```cpp
// io/file.hpp:27-28
struct file {
public:
    [[nodiscard]] file(std::FILE* const stream = nullptr) noexcept;
```

### Construction Methods
```cpp
// io/file.hpp:32-34 - Open file from path
file(const std::string& path, const std::string& mode) noexcept;

// io/file.hpp:36-40 - Windows wide string support
#if XIEITE_PLATFORM_TYPE_WINDOWS
    file(const std::wstring& path, const std::wstring& mode) noexcept;
#endif

// io/file.hpp:42-44 - From file descriptor
file(int desc, const std::string& mode) noexcept;

// io/file.hpp:52-55 - From C++ stream
template<xieite::is_stream Stream>
file(Stream& stream) noexcept;
```

### Stream Trait Detection
The library uses traits to identify stream types (trait/is_stream.hpp, trait/is_istream.hpp, trait/is_ostream.hpp):

```cpp
// io/file.hpp:105-116 - Standard stream detection
if constexpr (xieite::is_istream<Stream>) {
    if (ptr == &std::cin) {
        return stdin;
    }
} else if constexpr (xieite::is_ostream<Stream>) {
    if (ptr == &std::cout) {
        return stdout;
    }
    if ((ptr == &std::cerr) || (ptr == &std::clog)) {
        return stderr;
    }
}
```

### Platform-Specific Implementation

#### Unix Systems
```cpp
// io/file.hpp:15-17
#if XIEITE_PLATFORM_TYPE_UNIX
    #include <fcntl.h>
    #include <unistd.h>

// io/file.hpp:127-131 - Append mode detection
if (::fcntl(desc, F_GETFL) & O_APPEND) {
    mode += "a";
}
```

#### Windows Systems
```cpp
// io/file.hpp:88-89 - Windows file descriptor opening
#if XIEITE_PLATFORM_TYPE_WINDOWS
    this->stream = ::_fdopen(desc, mode.c_str());

// io/file.hpp:165-166 - Windows file number retrieval
    return ::_fileno(this->stream);
```

#### GCC-Specific Features
```cpp
// io/file.hpp:134-136 - GCC stdio_filebuf access
#if XIEITE_COMPILER_TYPE_GCC
    return static_cast<__gnu_cxx::stdio_filebuf<typename Stream::char_type,
                                                 typename Stream::traits_type>*>
           (stream.rdbuf())->file();
```

## Terminal Operations

### Terminal Control (io/term.hpp)
Terminal manipulation functions for cursor and screen control:

```cpp
// Terminal control sequences
namespace xieite {
    // Terminal operations structure
    struct term {
        // Platform-specific terminal control
    };
}
```

### Position Management (io/pos.hpp)
Cursor position tracking and manipulation:

```cpp
// Position tracking
namespace xieite {
    // Position management utilities
    struct pos {
        // Cursor positioning
    };
}
```

## Output Utilities

### Dump Function (io/dump.hpp:16-33)
Template-based formatted output with customizable delimiters:

```cpp
// io/dump.hpp:15-27 - Formatted dump to file
template<xieite::fixed_str delim = " ", bool newline = true, typename... Args>
void dump(std::FILE* file, Args&&... args) noexcept {
    static constexpr auto segment = xieite::fixed_str("{}") + delim;
    static constexpr std::size_t size = sizeof...(Args) * segment.size()
                                      - (!!sizeof...(Args) * delim.size());
    // Format string construction at compile-time
    static constexpr auto fmt = xieite::unroll<size>([]<std::size_t... i> {
        return xieite::fixed_array { segment[i % segment.size()]... };
    });

    if constexpr (newline) {
        std::println(file, std::format_string<Args...>(
            std::string_view(fmt.data(), size)), XIEITE_FWD(args)...);
    } else {
        std::print(file, std::format_string<Args...>(
            std::string_view(fmt.data(), size)), XIEITE_FWD(args)...);
    }
}

// io/dump.hpp:29-32 - Stdout overload
template<xieite::fixed_str delim = " ", bool newline = true>
void dump(auto&&... args) noexcept {
    return xieite::dump<delim, newline>(stdout, XIEITE_FWD(args)...);
}
```

### Log Operations (io/log.hpp)
Logging utilities for debugging and output:

```cpp
namespace xieite {
    // Logging functionality
    // Structure in io/log.hpp
}
```

## Input Operations

### Read Function (io/read.hpp)
Input reading utilities:

```cpp
namespace xieite {
    // Read operations
    // Implementation in io/read.hpp
}
```

### Keyboard Input (io/keys.hpp, io/keys_char.hpp)
Keyboard input handling:

```cpp
namespace xieite {
    // Key input structures
    // keys.hpp: Key codes
    // keys_char.hpp: Character input
}
```

## File Operations

### File Pipe (io/file_pipe.hpp)
Pipe operations for inter-process communication:

```cpp
namespace xieite {
    // File pipe utilities
    struct file_pipe {
        // Pipe management
    };
}
```

## Usage Examples

### Basic File Operations
```cpp
// Open file with RAII
xieite::file f("data.txt", "r");
if (f) {
    std::FILE* raw = f.get();
    // Use raw FILE*
}  // Automatically closed

// From stream
std::ifstream ifs("input.txt");
xieite::file f2(ifs);
```

### Platform-Specific File Handling
```cpp
#if XIEITE_PLATFORM_TYPE_WINDOWS
    // Windows wide string path
    xieite::file f(L"C:\\data\\file.txt", L"r");
#else
    // Unix path
    xieite::file f("/home/user/file.txt", "r");
#endif
```

### Formatted Output
```cpp
// Default space delimiter with newline
xieite::dump(1, 2, 3);  // Output: "1 2 3\n"

// Custom delimiter
xieite::dump<", ">(1, 2, 3);  // Output: "1, 2, 3\n"

// No newline
xieite::dump<" ", false>(1, 2, 3);  // Output: "1 2 3"
```

## Platform Considerations

### Platform Detection
The library uses preprocessor macros for platform-specific code:
- `XIEITE_PLATFORM_TYPE_UNIX` (io/file.hpp:15)
- `XIEITE_PLATFORM_TYPE_WINDOWS` (io/file.hpp:18)
- `XIEITE_COMPILER_TYPE_GCC` (io/file.hpp:22)

### Standard Stream Handling
Special handling for stdin, stdout, stderr (io/file.hpp:154):
```cpp
// io/file.hpp:154-157
if (this->stream && (this->stream != stdin) &&
    (this->stream != stdout) && (this->stream != stderr)) {
    return std::fclose(this->release());
}
```

## Error Handling

### File Operations
- Returns `nullptr` on failure (io/file.hpp:137)
- Returns `EOF` for erroneous close (io/file.hpp:157)
- Boolean conversion operator for validity check (io/file.hpp:71-73)

## See Also

- [I/O API Reference](../../reference/api/io.md)
- [File Operations](./files.md)
- [Platform Detection](../sys/platform.md)