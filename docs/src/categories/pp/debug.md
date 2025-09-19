# Debug Macros

## Overview

XIEITE provides comprehensive debug and diagnostic macros for controlling compiler warnings, generating diagnostic messages, and detecting debug builds. These utilities enable fine-grained control over compiler diagnostics across different compilers.

## Debug Detection

### Debug Mode Detection
Implementation: `include/xieite/pp/debug.hpp` (lines 4-8)

```cpp
#define XIEITE_DEBUG  // 1 if debug mode, 0 otherwise
```

The macro detects debug mode by checking for:
- `DEBUG` defined
- `NDEBUG` not defined
- `_DEBUG` defined (MSVC)
- `QT_DEBUG` defined (Qt framework)

## Diagnostic Messages

### Message Generation
Implementation: `include/xieite/pp/diagnostic.hpp` (lines 7-18)

```cpp
#define XIEITE_DIAGNOSTIC_MSG(msg)     // Informational message
#define XIEITE_DIAGNOSTIC_WARN(msg)    // Warning message
#define XIEITE_DIAGNOSTIC_ERROR(msg)   // Error message
```

### Compiler-Specific Messages
```cpp
#define XIEITE_DIAGNOSTIC_MSG_GCC(msg)    // GCC only
#define XIEITE_DIAGNOSTIC_MSG_CLANG(msg)  // Clang only
#define XIEITE_DIAGNOSTIC_MSG_MSVC(msg)   // MSVC only
```

## Warning Control

### Diagnostic Stack Management
Implementation: `include/xieite/pp/diagnostic.hpp` (lines 19-26)

```cpp
#define XIEITE_DIAGNOSTIC_PUSH()  // Save diagnostic state
#define XIEITE_DIAGNOSTIC_POP()   // Restore diagnostic state
```

### Warning Level Control
Implementation: `include/xieite/pp/diagnostic.hpp` (lines 27-35)

```cpp
#define XIEITE_DIAGNOSTIC_ON_GCC(id)      // Set warning to default
#define XIEITE_DIAGNOSTIC_STRICT_GCC(id)  // Treat warning as error
#define XIEITE_DIAGNOSTIC_OFF_GCC(id)     // Disable warning
```

## Usage Examples

### Debug Mode Branching
```cpp
#include <xieite/pp/debug.hpp>

void process_data(const Data& data) {
    #if XIEITE_DEBUG
        validate_data(data);
        std::cout << "Processing: " << data.debug_string() << "\n";
    #endif

    // Production code
    data.process();

    #if XIEITE_DEBUG
        verify_result(data);
    #endif
}
```

### Diagnostic Messages
```cpp
#include <xieite/pp/diagnostic.hpp>

// Compile-time messages
XIEITE_DIAGNOSTIC_MSG("Building with experimental features")

#ifdef DEPRECATED_API
    XIEITE_DIAGNOSTIC_WARN("Using deprecated API")
#endif

#ifdef BROKEN_FEATURE
    XIEITE_DIAGNOSTIC_ERROR("Broken feature enabled")
#endif
```

### Selective Warning Suppression
```cpp
#include <xieite/pp/diagnostic.hpp>

// Suppress specific warnings for a code block
XIEITE_DIAGNOSTIC_PUSH()
XIEITE_DIAGNOSTIC_OFF_GCC("-Wunused-variable")
XIEITE_DIAGNOSTIC_OFF_CLANG("-Wunused-variable")
XIEITE_DIAGNOSTIC_OFF_MSVC(4101)  // unreferenced local variable

void legacy_function() {
    int unused = 42;  // Warning suppressed
    // Legacy code with known warnings
}

XIEITE_DIAGNOSTIC_POP()  // Restore original warning state
```

### Compiler-Specific Diagnostics
```cpp
// Platform-specific warnings
XIEITE_DIAGNOSTIC_WARN_GCC("GCC-specific issue detected")
XIEITE_DIAGNOSTIC_WARN_CLANG("Clang optimization may fail here")
XIEITE_DIAGNOSTIC_WARN_MSVC("MSVC requires different approach")

// Strict mode for critical sections
XIEITE_DIAGNOSTIC_PUSH()
XIEITE_DIAGNOSTIC_STRICT_GCC("-Wconversion")  // Treat as error

void critical_calculation(float f) {
    int i = f;  // Will error with -Wconversion as error
}

XIEITE_DIAGNOSTIC_POP()
```

## Implementation Details

### Debug Detection Logic
The debug detection (debug.hpp:4-8) checks multiple common debug macros:
- Standard `NDEBUG` (inverted logic)
- Common `DEBUG` macro
- MSVC's `_DEBUG`
- Qt's `QT_DEBUG`

### Compiler-Specific Implementation
Diagnostic macros adapt to compiler (diagnostic.hpp:37-156):
- **MSVC**: Uses `#pragma message` and `#pragma warning`
- **Clang**: Uses `#pragma clang diagnostic`
- **GCC**: Uses `#pragma GCC diagnostic`

### Message Formatting
- MSVC adds ANSI color codes for warnings/errors (diagnostic.hpp:42, 45)
- GCC/Clang use native diagnostic pragmas (diagnostic.hpp:57, 60, 72, 75)

## Advanced Patterns

### Conditional Debug Logging
```cpp
#if XIEITE_DEBUG
    #define LOG_DEBUG(msg) std::cerr << "[DEBUG] " << msg << "\n"
#else
    #define LOG_DEBUG(msg) ((void)0)
#endif

void algorithm() {
    LOG_DEBUG("Starting algorithm");
    // ...
    LOG_DEBUG("Intermediate result: " << value);
    // ...
    LOG_DEBUG("Algorithm complete");
}
```

### Warning Management Wrapper
```cpp
// Create warning-free zone for third-party headers
#define THIRD_PARTY_INCLUDE_BEGIN() \
    XIEITE_DIAGNOSTIC_PUSH() \
    XIEITE_DIAGNOSTIC_OFF_GCC("-Wdeprecated-declarations") \
    XIEITE_DIAGNOSTIC_OFF_CLANG("-Wdeprecated-declarations") \
    XIEITE_DIAGNOSTIC_OFF_MSVC(4996)

#define THIRD_PARTY_INCLUDE_END() \
    XIEITE_DIAGNOSTIC_POP()

// Usage
THIRD_PARTY_INCLUDE_BEGIN()
#include <legacy_library.h>
THIRD_PARTY_INCLUDE_END()
```

### Build Configuration Messages
```cpp
// Report build configuration
#if XIEITE_DEBUG
    XIEITE_DIAGNOSTIC_MSG("Debug build enabled")
#else
    XIEITE_DIAGNOSTIC_MSG("Release build")
#endif

#ifdef ENABLE_PROFILING
    XIEITE_DIAGNOSTIC_MSG("Profiling enabled")
#endif

#ifdef USE_EXPERIMENTAL
    XIEITE_DIAGNOSTIC_WARN("Experimental features active")
#endif
```

## Compiler-Specific Warning IDs

### Common GCC/Clang Warnings
- `-Wunused-variable`: Unused variables
- `-Wconversion`: Type conversions
- `-Wshadow`: Variable shadowing
- `-Wdeprecated-declarations`: Deprecated features

### Common MSVC Warnings
- `4100`: Unreferenced formal parameter
- `4101`: Unreferenced local variable
- `4996`: Deprecated functions
- `4244`: Conversion warnings

Reference: diagnostic.hpp:159 links to Microsoft's warning documentation

## Best Practices

1. **Use XIEITE_DEBUG for debug-only code** - Automatic removal in release
2. **Push/pop diagnostic state** - Always restore original settings
3. **Document suppressed warnings** - Explain why warnings are disabled
4. **Prefer fixing over suppressing** - Only suppress when necessary
5. **Test both debug and release** - Ensure code works in both modes

## Common Pitfalls

1. **Forgetting to pop diagnostics** - Leaves warnings disabled
2. **Wrong warning IDs** - Different compilers use different IDs
3. **Over-suppression** - Hiding real problems
4. **Debug-only bugs** - Code that only works in debug mode

## Compatibility

- Works with GCC, Clang, MSVC
- Compiler detection automatic via XIEITE_COMPILER_TYPE
- Graceful degradation on unknown compilers
- No runtime overhead (compile-time only)

## See Also

- [Compiler Detection](./compiler.md) - Compiler identification
- [Conditional Compilation](./conditional.md) - Build configuration
- [Version Detection](./version.md) - Version macros
- [Preprocessor API Reference](../../reference/api/pp.md)