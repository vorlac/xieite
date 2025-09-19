# Header-Only Design

## Overview

XIEITE is designed as a completely header-only library, meaning all functionality is implemented directly in header files with no separate compilation units required. This architectural decision brings significant advantages for a modern C++ utility library.

## Design Principles

### No Compilation Required

Every component of XIEITE exists solely in header files:
- All 616 headers are self-contained
- No `.cpp` files to compile
- No static or dynamic libraries to link
- Simply include and use

### Template-Heavy Implementation

The header-only design naturally aligns with template-based programming:
```cpp
// All templates must be in headers anyway
template<typename T>
constexpr auto square(T value) noexcept {
    return value * value;
}

// Concepts defined inline
template<typename T>
concept arithmetic = std::is_arithmetic_v<T>;
```

### Inline Everything

All non-template functions are marked `inline` to prevent ODR violations:
```cpp
namespace xieite {
    // Inline for ODR compliance
    inline std::string get_env(const std::string& name) {
        if (auto* value = std::getenv(name.c_str())) {
            return value;
        }
        return {};
    }
}
```

## Implementation Patterns

### Header Guards

Every header uses a consistent guard pattern:
```cpp
#ifndef XIEITE_HEADER_CATEGORY_NAME
#define XIEITE_HEADER_CATEGORY_NAME

namespace xieite {
    // Implementation here
}

#endif
```

### Constexpr Maximization

Header-only design enables extensive compile-time computation:
```cpp
// Compile-time lookup tables
template<typename T>
constexpr auto factorial = []<std::size_t... i>(std::index_sequence<i...>) {
    return std::array<T, sizeof...(i)>{
        compute_factorial<T>(i)...
    };
}(std::make_index_sequence<21>{});

// Usage: xieite::factorial<int>[5] // Computed at compile time
```

### Dependency Management

Headers include only what they need:
```cpp
// math/abs.hpp
#ifndef XIEITE_HEADER_MATH_ABS
#define XIEITE_HEADER_MATH_ABS

#include <concepts>           // For std::integral
#include <limits>            // For numeric_limits
#include "../trait/is_int.hpp"  // Internal dependency

namespace xieite {
    template<is_int T>
    constexpr T abs(T value) noexcept {
        // Implementation
    }
}

#endif
```

## Advantages

### Ease of Integration

1. **Simple Installation**
   ```bash
   # Just copy the include directory
   cp -r xieite/include/xieite /your/project/third_party/
   ```

2. **Package Manager Friendly**
   - Works with vcpkg, Conan, build2
   - No build configuration needed
   - Header-only CMake target

3. **IDE Support**
   - Full IntelliSense/autocomplete
   - Go-to-definition works instantly
   - No build step for navigation

### Performance Benefits

1. **Maximum Inlining**
   - Compiler sees all code
   - Cross-function optimization
   - No function call overhead

2. **Link-Time Optimization**
   - No separate translation units
   - Whole program optimization
   - Dead code elimination

3. **Template Instantiation**
   - Only what you use gets compiled
   - No code bloat from unused templates
   - Optimal for each type used

### Development Advantages

1. **Rapid Iteration**
   - Change header, recompile user code
   - No library rebuild needed
   - Instant testing of changes

2. **Debugging**
   - Step into library code
   - See actual implementation
   - No opaque library boundaries

3. **Customization**
   - Easy to patch locally
   - Can specialize templates
   - Override with local definitions

## Potential Drawbacks and Mitigations

### Compilation Time

**Issue**: Every translation unit recompiles library code

**Mitigations**:
- Use precompiled headers
- Forward declarations where possible
- Modular includes (not monolithic)
- C++20 modules support (future)

```cpp
// Precompiled header example
// pch.hpp
#pragma once
#include <xieite/trait/is_int.hpp>
#include <xieite/math/abs.hpp>
#include <xieite/data/fixed_str.hpp>
// Commonly used headers
```

### Binary Size

**Issue**: Multiple instantiations across translation units

**Mitigations**:
- Link-time optimization (`-flto`)
- Explicit instantiation for common types
- `extern template` declarations

```cpp
// Explicit instantiation declaration
extern template class xieite::fixed_array<int, 10>;

// In one translation unit:
template class xieite::fixed_array<int, 10>;
```

### Dependency Exposure

**Issue**: All dependencies visible in headers

**Mitigations**:
- Minimal includes
- Forward declarations
- Pimpl idiom where applicable
- Clear dependency documentation

## Integration Examples

### CMake Integration

```cmake
# Header-only library target
add_library(xieite INTERFACE)
target_include_directories(xieite INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(xieite INTERFACE cxx_std_23)

# Usage
target_link_libraries(my_app PRIVATE xieite)
```

### Direct Include

```cpp
// No build system needed
#include <xieite/pp/arrow.hpp>
#include <xieite/trait/is_int.hpp>
#include <xieite/math/factorial.hpp>

// Use directly
auto double_it(int x) XIEITE_ARROW(x * 2)

constexpr auto fact_10 = xieite::factorial<int>[10];
```

### Precompiled Header Setup

```cpp
// stdafx.h or pch.h
#pragma once

// STL headers
#include <vector>
#include <string>
#include <algorithm>

// Frequently used XIEITE headers
#include <xieite/pp/arrow.hpp>
#include <xieite/trait/is_int.hpp>
#include <xieite/data/fixed_str.hpp>
```

## Best Practices

### For Library Users

1. **Use specific includes**
   ```cpp
   // Good: Include only what you need
   #include <xieite/math/abs.hpp>

   // Avoid: Including unnecessary headers
   ```

2. **Consider precompiled headers** for frequently used components

3. **Enable link-time optimization** in release builds

### For Library Developers

1. **Keep headers focused** - One concept per header

2. **Minimize dependencies** - Include only essentials

3. **Use forward declarations** where possible

4. **Document dependencies** clearly in each header

## Comparison with Compiled Libraries

| Aspect | Header-Only | Compiled Library |
|--------|------------|------------------|
| **Installation** | Copy headers | Build & link |
| **Compilation Time** | Longer per TU | Faster per TU |
| **Binary Size** | Potentially larger | Controlled |
| **Optimization** | Maximum | Limited by ABI |
| **Debugging** | Full visibility | Requires debug symbols |
| **ABI Stability** | N/A | Must maintain |
| **Distribution** | Source only | Binary packages |

## Future Considerations

### C++20 Modules

When compiler support matures:
```cpp
// Future: xieite.ixx
export module xieite;

export namespace xieite {
    // Export interface
}
```

### Hybrid Approach

Optional compiled components for heavy utilities:
```cpp
#ifdef XIEITE_HEADER_ONLY
    inline
#else
    XIEITE_API
#endif
std::string heavy_function() {
    // Implementation
}
```

## Conclusion

The header-only design of XIEITE provides maximum flexibility, performance, and ease of use at the cost of increased compilation time. This trade-off is ideal for a utility library where:

- Templates are prevalent
- Performance is critical
- Ease of integration is paramount
- Cross-platform support is required
- Users need full control and visibility

The design aligns perfectly with modern C++ practices and the library's goal of providing zero-overhead abstractions for systems programming.