# Platform Detection

The XIEITE platform detection system provides comprehensive cross-platform identification capabilities through preprocessor macros. This system enables developers to write conditional code that adapts to different operating systems, architectures, and environments at compile time.

## Overview

The platform detection system is implemented in `include/xieite/pp/platform.hpp` and provides:

- **200+ Platform Support**: Detection for over 200 different platforms, operating systems, and environments
- **Version Information**: Where available, extracts major, minor, and patch version numbers
- **Standardized Interface**: Consistent macro naming and structure across all platforms
- **Zero Runtime Cost**: All detection occurs at preprocessor/compile time

## Architecture

### Macro Structure

Each platform follows a consistent four-macro pattern:

```cpp
XIEITE_PLATFORM_TYPE_<PLATFORM>    // 1 if platform detected, 0 otherwise
XIEITE_PLATFORM_MAJOR_<PLATFORM>   // Major version number (0 if unknown)
XIEITE_PLATFORM_MINOR_<PLATFORM>   // Minor version number (0 if unknown)
XIEITE_PLATFORM_PATCH_<PLATFORM>   // Patch version number (0 if unknown)
```

### Detection Logic

The system initializes all platform macros to 0, then selectively sets them to 1 based on compiler-defined preprocessor symbols:

```cpp
// Default initialization
#define XIEITE_PLATFORM_TYPE_LINUX 0
#define XIEITE_PLATFORM_MAJOR_LINUX 0
#define XIEITE_PLATFORM_MINOR_LINUX 0
#define XIEITE_PLATFORM_PATCH_LINUX 0

// Detection and override
#ifdef __linux__
#    undef XIEITE_PLATFORM_TYPE_LINUX
#    define XIEITE_PLATFORM_TYPE_LINUX 1
    // Version detection logic...
#endif
```

## Version Comparison

The system provides the `XIEITE_PLATFORM_VER` macro for version comparisons:

```cpp
XIEITE_PLATFORM_VER(platform, comparison, major, minor, patch)
```

### Usage Examples

```cpp
// Check if running on Linux
#if XIEITE_PLATFORM_TYPE_LINUX
    // Linux-specific code
#endif

// Check for specific Windows version or higher
#if XIEITE_PLATFORM_VER(WINDOWS, >=, 10, 0, 0)
    // Windows 10+ specific features
#endif

// Check for macOS version range
#if XIEITE_PLATFORM_VER(MACOS, >=, 10, 15, 0) && XIEITE_PLATFORM_VER(MACOS, <, 12, 0, 0)
    // macOS 10.15 to 11.x specific code
#endif
```

## Supported Platforms

### Major Operating Systems

#### Unix-like Systems
- **Linux**: Various distributions and kernels
- **BSD Family**: FreeBSD, OpenBSD, NetBSD, DragonFly BSD
- **macOS/Darwin**: All versions from classic Mac OS to modern macOS
- **Solaris/SunOS**: Oracle Solaris and legacy SunOS
- **AIX**: IBM AIX with version detection

#### Microsoft Windows
- **Windows**: All versions from Windows 95 to Windows 11
- **Windows CE**: Embedded Windows systems
- **Cygwin**: Windows compatibility layer
- **MinGW**: Minimalist GNU for Windows

#### Mobile Platforms
- **Android**: Google Android OS
- **iOS**: Apple iOS and iPadOS
- **Windows Phone**: Microsoft mobile platforms
- **BlackBerry**: BlackBerry OS variants

### Gaming Consoles
- **PlayStation**: PS2, PS3, PS4, PS5, PSP, PS Vita
- **Xbox**: Original Xbox, Xbox 360, Xbox One, Xbox Series
- **Nintendo**: DS, 3DS, Wii, Wii U, Switch
- **Sega**: Dreamcast and legacy systems

### Embedded and Specialized Systems
- **QNX**: Real-time operating system
- **VxWorks**: Real-time OS for embedded systems
- **RTEMS**: Real-Time Executive for Multiprocessor Systems
- **FreeRTOS**: Real-time operating system kernel
- **Nucleus**: Real-time operating system
- **ThreadX**: Microsoft real-time OS

### Legacy and Retro Systems
- **MS-DOS**: Microsoft Disk Operating System
- **OS/2**: IBM/Microsoft OS/2
- **AmigaOS**: Classic Amiga operating systems
- **Atari**: Various Atari computer systems
- **Commodore**: C64, Amiga, and other Commodore systems
- **Apple II**: Classic Apple computer systems

### Scientific and Supercomputing
- **Blue Gene**: IBM Blue Gene supercomputer systems
- **Cray**: Cray supercomputer environments
- **UNICOS**: Cray's Unix-based operating system

### Virtualization and Containers
- **VMware**: VMware virtualization environments
- **Xen**: Xen hypervisor
- **Docker**: Container environments (detected through underlying OS)

## Implementation Examples

### Basic Platform Detection

```cpp
#include <xieite/pp/platform.hpp>
#include <iostream>

int main() {
#if XIEITE_PLATFORM_TYPE_WINDOWS
    std::cout << "Running on Windows\n";
#elif XIEITE_PLATFORM_TYPE_LINUX
    std::cout << "Running on Linux\n";
#elif XIEITE_PLATFORM_TYPE_MACOS
    std::cout << "Running on macOS\n";
#else
    std::cout << "Unknown platform\n";
#endif
    return 0;
}
```

### Platform-Specific Features

```cpp
#include <xieite/pp/platform.hpp>

class FileSystem {
public:
    static constexpr char path_separator() noexcept {
#if XIEITE_PLATFORM_TYPE_WINDOWS
        return '\\';
#else
        return '/';
#endif
    }

    static std::string home_directory() {
#if XIEITE_PLATFORM_TYPE_WINDOWS
        return std::getenv("USERPROFILE");
#else
        return std::getenv("HOME");
#endif
    }
};
```

### Version-Aware Compilation

```cpp
#include <xieite/pp/platform.hpp>

// Use modern Windows APIs only on Windows 10+
#if XIEITE_PLATFORM_VER(WINDOWS, >=, 10, 0, 0)
    #define USE_MODERN_WINDOWS_API 1
    #include <winrt/base.h>
#else
    #define USE_MODERN_WINDOWS_API 0
    #include <windows.h>
#endif

void platform_specific_function() {
#if USE_MODERN_WINDOWS_API
    // Use Windows Runtime APIs
    winrt::init_apartment();
#else
    // Use legacy Win32 APIs
    CoInitialize(nullptr);
#endif
}
```

## Advanced Usage Patterns

### Multi-Platform Libraries

```cpp
#include <xieite/pp/platform.hpp>

namespace platform_utils {
    // Threading primitives
#if XIEITE_PLATFORM_TYPE_WINDOWS
    using native_thread_handle = HANDLE;
    using native_mutex_handle = CRITICAL_SECTION;
#elif XIEITE_PLATFORM_TYPE_LINUX || XIEITE_PLATFORM_TYPE_MACOS
    using native_thread_handle = pthread_t;
    using native_mutex_handle = pthread_mutex_t;
#endif

    // Platform-specific optimizations
    template<typename T>
    constexpr bool use_platform_optimized_sort() noexcept {
#if XIEITE_PLATFORM_TYPE_WINDOWS && XIEITE_PLATFORM_VER(WINDOWS, >=, 8, 0, 0)
        return true;  // Use Windows 8+ sorting optimizations
#elif XIEITE_PLATFORM_TYPE_LINUX && defined(__GLIBC__)
        return true;  // Use glibc optimizations
#else
        return false; // Use generic implementation
#endif
    }
}
```

### Build System Integration

```cpp
// CMakeLists.txt configuration based on platform detection
#include <xieite/pp/platform.hpp>

#if XIEITE_PLATFORM_TYPE_WINDOWS
    #pragma comment(lib, "ws2_32.lib")
    #pragma comment(lib, "advapi32.lib")
#elif XIEITE_PLATFORM_TYPE_LINUX
    // Link with pthread and rt libraries automatically detected
#elif XIEITE_PLATFORM_TYPE_MACOS
    // Use Accelerate framework on macOS
    #pragma comment(lib, "-framework Accelerate")
#endif
```

## Compiler and Toolchain Detection

The platform detection system integrates with compiler-specific preprocessor definitions:

### GCC-based Detection
```cpp
// Detects platforms through GCC predefined macros
#ifdef __linux__        // Linux
#ifdef __CYGWIN__       // Cygwin
#ifdef __MINGW32__      // MinGW
#ifdef __APPLE__        // Apple platforms
```

### MSVC Detection
```cpp
// Microsoft Visual C++ specific macros
#ifdef _WIN32           // Windows (32-bit and 64-bit)
#ifdef _WIN64           // Windows 64-bit
#ifdef _XBOX_ONE        // Xbox One
#ifdef _DURANGO         // Xbox One (codename)
```

### Embedded Compilers
```cpp
// Specialized embedded system detection
#ifdef __CC_ARM         // ARM Compiler
#ifdef __ICCARM__       // IAR ARM Compiler
#ifdef __GNUC__         // GCC for embedded
```

## Integration with Other XIEITE Components

### With Conditional Compilation
```cpp
#include <xieite/pp/platform.hpp>
#include <xieite/pp/conditional.hpp>

// Combine platform detection with conditional macros
#define XIEITE_NATIVE_FILESYSTEM \
    XIEITE_IF(XIEITE_PLATFORM_TYPE_WINDOWS, std::filesystem, boost::filesystem)
```

### With Architecture Detection
```cpp
#include <xieite/pp/platform.hpp>
#include <xieite/pp/arch.hpp>

// Platform + architecture specific optimizations
#if XIEITE_PLATFORM_TYPE_LINUX && XIEITE_ARCH_TYPE_X86_64
    #define USE_LINUX_X64_OPTIMIZATIONS 1
#endif
```

## Best Practices

### 1. Prefer Specific Over General
```cpp
// Good: Specific platform detection
#if XIEITE_PLATFORM_TYPE_WINDOWS
    // Windows-specific code
#elif XIEITE_PLATFORM_TYPE_MACOS
    // macOS-specific code
#endif

// Avoid: Overly broad categories
#ifdef _WIN32  // Too compiler-specific
```

### 2. Version-Aware Programming
```cpp
// Good: Check for required features
#if XIEITE_PLATFORM_VER(WINDOWS, >=, 10, 0, 17763)
    // Use Windows 10 October 2018 Update features
#endif

// Avoid: Assuming latest version
#if XIEITE_PLATFORM_TYPE_WINDOWS
    // May not work on older Windows versions
#endif
```

### 3. Graceful Fallbacks
```cpp
// Good: Provide fallback implementations
#if XIEITE_PLATFORM_TYPE_LINUX
    // Linux-optimized implementation
#elif XIEITE_PLATFORM_TYPE_WINDOWS
    // Windows-optimized implementation
#else
    // Generic portable implementation
#endif
```

### 4. Documentation
```cpp
// Good: Document platform requirements
/**
 * @brief High-performance file monitoring
 * @note Requires:
 *   - Windows 10+ (uses ReadDirectoryChangesW)
 *   - Linux with inotify support
 *   - macOS 10.7+ (uses FSEvents)
 */
class FileWatcher {
    // Implementation...
};
```

## Limitations and Considerations

### Detection Accuracy
- Platform detection relies on compiler-provided preprocessor macros
- Some environments may provide incomplete or inaccurate macro definitions
- Virtual machines and containers may report host OS rather than guest OS

### Version Information
- Version detection accuracy varies by platform
- Some platforms don't provide version information through preprocessor macros
- Runtime version detection may be needed for precise version checking

### Performance Impact
- All detection occurs at compile time (zero runtime cost)
- Large number of macros may impact compilation time
- Consider using forward declarations to minimize header inclusion

## Cross-Platform Development Guidelines

### Conditional Compilation Strategy
1. **Start with standards-compliant code** where possible
2. **Add platform-specific optimizations** as needed
3. **Provide fallback implementations** for unsupported platforms
4. **Test on all target platforms** regularly

### Debugging Platform Issues
```cpp
// Diagnostic macro to print detected platform
#include <xieite/pp/platform.hpp>
#include <iostream>

void print_platform_info() {
    std::cout << "Platform Detection Results:\n";

#if XIEITE_PLATFORM_TYPE_WINDOWS
    std::cout << "Windows detected - Version: "
              << XIEITE_PLATFORM_MAJOR_WINDOWS << "."
              << XIEITE_PLATFORM_MINOR_WINDOWS << "."
              << XIEITE_PLATFORM_PATCH_WINDOWS << "\n";
#endif

#if XIEITE_PLATFORM_TYPE_LINUX
    std::cout << "Linux detected\n";
#endif

#if XIEITE_PLATFORM_TYPE_MACOS
    std::cout << "macOS detected - Version: "
              << XIEITE_PLATFORM_MAJOR_MACOS << "."
              << XIEITE_PLATFORM_MINOR_MACOS << "."
              << XIEITE_PLATFORM_PATCH_MACOS << "\n";
#endif

    // Add checks for other platforms as needed
}
```

## References and Standards

The XIEITE platform detection system is based on:

- **C Preprocessor Standards**: ISO/IEC 9899 preprocessor specifications
- **Compiler Documentation**: GCC, Clang, MSVC, and other compiler manuals
- **Platform Documentation**: Official OS and SDK documentation
- **Community Resources**:
  - [C Preprocessor Predefined Macros](https://github.com/cpredef/predef)
  - [CC65 Compiler Documentation](https://cc65.github.io/doc/cc65.html)

Special thanks to Ian Pike ([@Rinzii](https://github.com/Rinzii)) for contributing detection macros for specialized platforms.

---

*See also: [Architecture Detection](arch.md) | [Compiler Detection](compiler.md) | [Conditional Compilation](conditional.md)*