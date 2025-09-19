# Version Detection

## Overview

XIEITE provides version detection macros for tracking the library version and performing version comparisons at compile time. These utilities enable conditional compilation based on library version requirements.

## Version Constants

### Current Version
Implementation: `include/xieite/pp/ver.hpp` (lines 4-6)

```cpp
#define XIEITE_VER_MAJOR 0     // Major version number
#define XIEITE_VER_MINOR 118   // Minor version number
#define XIEITE_VER_PATCH 2     // Patch version number
```

Current XIEITE version: **0.118.2**

## Version Comparison

### Version Check Macro
Implementation: `include/xieite/pp/ver.hpp` (lines 7-9)

```cpp
#define XIEITE_VER(cmp, major, ...)
// Compare current version with specified version
// cmp: Comparison operator (==, !=, <, <=, >, >=)
// major: Major version to compare
// minor: Optional minor version (defaults to 0)
// patch: Optional patch version (defaults to 0)
```

## Usage Examples

### Basic Version Checks
```cpp
#include <xieite/pp/ver.hpp>

// Check exact version
#if XIEITE_VER(==, 0, 118, 2)
    // Code for version 0.118.2
#endif

// Check minimum version
#if XIEITE_VER(>=, 0, 118, 0)
    // Code requiring at least version 0.118.0
#endif

// Check major version only
#if XIEITE_VER(>=, 1)
    // Code for version 1.x.x or later
#endif
```

### Feature Availability
```cpp
// Enable features based on version
#if XIEITE_VER(>=, 0, 120, 0)
    #define USE_NEW_FEATURE 1
    // New feature available in 0.120.0+
#else
    #define USE_NEW_FEATURE 0
    // Fallback for older versions
#endif

void process() {
    #if USE_NEW_FEATURE
        use_new_algorithm();
    #else
        use_legacy_algorithm();
    #endif
}
```

### Version-Based Deprecation
```cpp
// Deprecate old APIs
#if XIEITE_VER(<, 1, 0, 0)
    [[deprecated("Use new_function() instead")]]
    void old_function();
#endif

// Remove very old APIs
#if XIEITE_VER(>=, 2, 0, 0)
    // old_function no longer available
#else
    void old_function() { /* legacy implementation */ }
#endif
```

### Compatibility Guards
```cpp
// Ensure minimum version requirement
#if !XIEITE_VER(>=, 0, 100, 0)
    #error "This code requires XIEITE version 0.100.0 or later"
#endif

// Warn about untested versions
#if XIEITE_VER(>, 1, 0, 0)
    #pragma message("Warning: This code has not been tested with XIEITE > 1.0.0")
#endif
```

## Implementation Details

### Version Comparison Logic
The XIEITE_VER macro (ver.hpp:9) implements complex version comparison:
- Handles all comparison operators (==, !=, <, <=, >, >=)
- Compares major, minor, and patch numbers hierarchically
- Defaults missing version components to 0
- Uses preprocessor arithmetic for compile-time evaluation

### Comparison Algorithm
The macro expands to check:
1. Operator validity using compile-time tests
2. Major version comparison first
3. Minor version if major matches
4. Patch version if major and minor match
4. Combines results based on comparison operator

## Advanced Patterns

### Multi-Version Support
```cpp
// Support multiple library versions
#if XIEITE_VER(>=, 0, 118, 0) && XIEITE_VER(<, 1, 0, 0)
    // Code for 0.118.x versions
    using implementation = v0_impl;
#elif XIEITE_VER(>=, 1, 0, 0) && XIEITE_VER(<, 2, 0, 0)
    // Code for 1.x versions
    using implementation = v1_impl;
#else
    // Future versions
    using implementation = latest_impl;
#endif
```

### Version Range Checking
```cpp
// Define supported version range
#define MIN_SUPPORTED_VERSION(x) XIEITE_VER(>=, 0, 100, 0)
#define MAX_SUPPORTED_VERSION(x) XIEITE_VER(<=, 0, 200, 0)

#if !MIN_SUPPORTED_VERSION()
    #error "XIEITE version too old"
#elif !MAX_SUPPORTED_VERSION()
    #error "XIEITE version too new"
#endif
```

### Feature Detection Pattern
```cpp
// Check for feature availability by version
#define HAS_ARROW_MACROS XIEITE_VER(>=, 0, 50, 0)
#define HAS_CONCEPTS XIEITE_VER(>=, 0, 80, 0)
#define HAS_RANGES XIEITE_VER(>=, 0, 100, 0)

template<typename T>
#if HAS_CONCEPTS
    requires std::integral<T>
#endif
auto process(T value) {
    #if HAS_ARROW_MACROS
        return value * 2;
    #else
        return multiply(value, 2);
    #endif
}
```

### Version Information Display
```cpp
// Generate version string
#define XIEITE_VERSION_STRING \
    XIEITE_STR(XIEITE_VER_MAJOR) "." \
    XIEITE_STR(XIEITE_VER_MINOR) "." \
    XIEITE_STR(XIEITE_VER_PATCH)

// Display at compile time
#pragma message("Using XIEITE version " XIEITE_VERSION_STRING)

// Runtime version info
constexpr const char* get_xieite_version() {
    return XIEITE_VERSION_STRING;
}
```

## Version Numbering Scheme

XIEITE follows semantic versioning:
- **Major**: Breaking API changes
- **Minor**: New features, backwards compatible
- **Patch**: Bug fixes, no API changes

Example progression:
- 0.118.2 → 0.118.3 (bug fix)
- 0.118.3 → 0.119.0 (new feature)
- 0.119.0 → 1.0.0 (major release/breaking change)

## Migration Support

### Smooth Version Transitions
```cpp
// Support old and new API during transition
#if XIEITE_VER(<, 1, 0, 0)
    // Old API
    #define xieite_function old_function_name
#else
    // New API
    #define xieite_function new_function_name
#endif

// User code remains unchanged
xieite_function();
```

### Gradual Deprecation
```cpp
// Phase 1: Introduction (0.100.0)
#if XIEITE_VER(>=, 0, 100, 0)
    void new_api();
#endif

// Phase 2: Deprecation (0.110.0)
#if XIEITE_VER(>=, 0, 110, 0)
    [[deprecated("Use new_api()")]]
    void old_api();
#else
    void old_api();
#endif

// Phase 3: Removal (0.120.0)
#if XIEITE_VER(<, 0, 120, 0)
    void old_api() { /* still available */ }
#endif
// old_api no longer available in 0.120.0+
```

## Best Practices

1. **Always specify all three version components** for exact comparisons
2. **Use >= for minimum requirements** rather than exact versions
3. **Document version requirements** in code comments
4. **Test with multiple versions** when possible
5. **Provide migration paths** for breaking changes

## Common Pitfalls

1. **Forgetting default values** - Minor and patch default to 0
2. **Wrong operator precedence** - Parenthesize complex checks
3. **Version number overflow** - Keep numbers reasonable
4. **Assuming version availability** - Always check first

## Integration with Build Systems

### CMake Integration
```cmake
# Extract version from ver.hpp
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/include/xieite/pp/ver.hpp" VERSION_FILE)
string(REGEX MATCH "XIEITE_VER_MAJOR ([0-9]+)" _ ${VERSION_FILE})
set(XIEITE_VERSION_MAJOR ${CMAKE_MATCH_1})
# Similar for MINOR and PATCH
```

### Package Managers
Version information can be used by:
- Conan recipes
- vcpkg ports
- CMake find modules
- pkg-config files

## Compatibility

- Works with all C/C++ preprocessors
- No compiler-specific features required
- Pure preprocessor evaluation (compile-time only)
- Compatible with C++98 and later

## See Also

- [Conditional Compilation](./conditional.md) - Build configuration
- [Compiler Detection](./compiler.md) - Compiler-specific code
- [Debug Macros](./debug.md) - Debug mode detection
- [Preprocessor API Reference](../../reference/api/pp.md)