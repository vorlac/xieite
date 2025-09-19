# Compiler Support

This document provides detailed information about compiler compatibility, version requirements, and compiler-specific considerations for XIEITE.

## Supported Compilers

### GCC (GNU Compiler Collection)

#### Minimum Requirements
- **Minimum Version**: GCC 10.0
- **Recommended Version**: GCC 11.0 or later
- **C++ Standard**: C++20 (required)

#### Version Support Matrix

| GCC Version | C++20 Support | Concepts | Modules | XIEITE Status |
|-------------|---------------|----------|---------|---------------|
| 13.x        | ✅ Full       | ✅ Full  | ✅ Full | ✅ Fully Supported |
| 12.x        | ✅ Full       | ✅ Full  | ⚠️ Partial | ✅ Fully Supported |
| 11.x        | ✅ Full       | ✅ Full  | ⚠️ Partial | ✅ Fully Supported |
| 10.x        | ⚠️ Partial   | ✅ Full  | ❌ None | ⚠️ Basic Support |
| 9.x         | ❌ None      | ❌ None  | ❌ None | ❌ Not Supported |

#### GCC-Specific Features

```cpp
// GCC-specific optimizations detected by XIEITE
#include <xieite/pp/compiler.hpp>

XIEITE_PP_IF(XIEITE_COMPILER_GCC)(
    // GCC builtin functions available
    #pragma GCC optimize("O3")
    #pragma GCC target("native")

    // Use GCC-specific attributes
    __attribute__((hot))
    __attribute__((cold))
    __attribute__((always_inline))
)
```

#### Known Issues and Workarounds

**Issue**: Template instantiation depth limits
```cpp
// Default limit is 1024, may need increase for complex metaprogramming
#pragma GCC diagnostic ignored "-Wtemplate-backtrace-limit"
```

**Workaround**:
```bash
# Compile with increased template depth
g++ -ftemplate-depth=2048 source.cpp
```

**Issue**: Concepts with SFINAE interactions
```cpp
// Some complex concept + SFINAE combinations may fail in GCC 10
template<typename T>
concept complex_concept = /* complex definition */;

// Workaround: Simplify concept or use GCC 11+
```

### Clang (LLVM)

#### Minimum Requirements
- **Minimum Version**: Clang 10.0
- **Recommended Version**: Clang 14.0 or later
- **C++ Standard**: C++20 (required)

#### Version Support Matrix

| Clang Version | C++20 Support | Concepts | Modules | XIEITE Status |
|---------------|---------------|----------|---------|---------------|
| 16.x+         | ✅ Full       | ✅ Full  | ✅ Full | ✅ Fully Supported |
| 15.x          | ✅ Full       | ✅ Full  | ⚠️ Partial | ✅ Fully Supported |
| 14.x          | ✅ Full       | ✅ Full  | ⚠️ Partial | ✅ Fully Supported |
| 13.x          | ✅ Full       | ✅ Full  | ⚠️ Experimental | ✅ Fully Supported |
| 12.x          | ✅ Good       | ✅ Full  | ⚠️ Experimental | ✅ Fully Supported |
| 11.x          | ✅ Good       | ✅ Full  | ❌ None | ✅ Fully Supported |
| 10.x          | ⚠️ Basic     | ✅ Full  | ❌ None | ⚠️ Basic Support |

#### Clang-Specific Features

```cpp
#include <xieite/pp/compiler.hpp>

XIEITE_PP_IF(XIEITE_COMPILER_CLANG)(
    // Clang-specific features
    #pragma clang optimize on

    // Use Clang attributes
    __attribute__((annotate("hot_path")))
    __attribute__((no_sanitize("address")))

    // Clang diagnostic control
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wunused-variable"
)
```

#### Known Issues and Workarounds

**Issue**: Module support varies significantly
```cpp
// Modules are experimental in Clang < 16
// Stick to header-only approach for better compatibility
```

**Issue**: Some C++20 library features missing in older versions
```cpp
#include <xieite/pp/ver.hpp>

XIEITE_PP_IF(__clang_major__ < 14)(
    // Use XIEITE compatibility layers
    #include <xieite/trait/is_arith.hpp>
)
XIEITE_PP_IF(__clang_major__ >= 14)(
    // Can use standard library features
    #include <concepts>
)
```

### MSVC (Microsoft Visual C++)

#### Minimum Requirements
- **Minimum Version**: MSVC 19.29 (Visual Studio 2019 16.10)
- **Recommended Version**: MSVC 19.30+ (Visual Studio 2022)
- **C++ Standard**: C++20 (/std:c++20)

#### Version Support Matrix

| MSVC Version | VS Version | C++20 Support | Concepts | Modules | XIEITE Status |
|--------------|------------|---------------|----------|---------|---------------|
| 19.35+       | VS 2022 17.5+ | ✅ Full    | ✅ Full  | ✅ Good | ✅ Fully Supported |
| 19.30-19.34  | VS 2022      | ✅ Good     | ✅ Full  | ⚠️ Basic | ✅ Fully Supported |
| 19.29        | VS 2019 16.10+ | ⚠️ Basic | ✅ Basic | ❌ None | ⚠️ Basic Support |
| 19.28        | VS 2019 16.9  | ❌ None    | ❌ None  | ❌ None | ❌ Not Supported |

#### MSVC-Specific Features

```cpp
#include <xieite/pp/compiler.hpp>

XIEITE_PP_IF(XIEITE_COMPILER_MSVC)(
    // MSVC-specific optimizations
    #pragma optimize("gty", on)

    // Use MSVC attributes
    __forceinline
    __declspec(noinline)
    __declspec(novtable)

    // MSVC diagnostic control
    #pragma warning(push)
    #pragma warning(disable: 4996)
)
```

#### Known Issues and Workarounds

**Issue**: Constexpr evaluation limits
```cpp
// MSVC has stricter constexpr limits
template<std::size_t N>
constexpr auto factorial() {
    // Use iterative approach for MSVC compatibility
    std::size_t result = 1;
    for (std::size_t i = 1; i <= N; ++i) {
        result *= i;
    }
    return result;
}
```

**Issue**: Template argument deduction differences
```cpp
// MSVC may require explicit template arguments where GCC/Clang don't
template<typename T>
auto func(T&& value) { /* implementation */ }

// May need explicit specification on MSVC
func<int>(42);  // Instead of just func(42)
```

**Issue**: Preprocessor conformance
```cpp
// MSVC preprocessor needs /Zc:preprocessor for full C++20 conformance
// Or use XIEITE's compatibility macros
#include <xieite/pp/eval.hpp>
XIEITE_PP_EVAL(complex_macro_expression)
```

## Compiler Detection and Configuration

### Automatic Detection

XIEITE automatically detects compilers and versions:

```cpp
#include <xieite/pp/compiler.hpp>

// Compiler detection macros
XIEITE_PP_IF(XIEITE_COMPILER_GCC)(
    // GCC-specific code
)
XIEITE_PP_IF(XIEITE_COMPILER_CLANG)(
    // Clang-specific code
)
XIEITE_PP_IF(XIEITE_COMPILER_MSVC)(
    // MSVC-specific code
)

// Version checking
XIEITE_PP_IF(XIEITE_COMPILER_GCC && __GNUC__ >= 11)(
    // GCC 11+ features
)
```

### Manual Configuration

For fine-grained control:

```cpp
// Explicitly define compiler features if detection fails
#ifndef XIEITE_COMPILER_GCC
    #if defined(__GNUC__) && !defined(__clang__)
        #define XIEITE_COMPILER_GCC 1
    #endif
#endif

// Feature availability
#if defined(__cpp_concepts) && __cpp_concepts >= 201907L
    #define XIEITE_HAS_CONCEPTS 1
#endif
```

## Compilation Flags and Options

### Recommended Compilation Settings

#### GCC
```bash
# Debug build
g++ -std=c++20 -Wall -Wextra -Wpedantic -g -O0 -fsanitize=address,undefined

# Release build
g++ -std=c++20 -O3 -DNDEBUG -march=native -flto

# With XIEITE-specific optimizations
g++ -std=c++20 -O3 -DNDEBUG -ftemplate-depth=2048 -fconstexpr-depth=2048
```

#### Clang
```bash
# Debug build
clang++ -std=c++20 -Wall -Wextra -Wpedantic -g -O0 -fsanitize=address,undefined

# Release build
clang++ -std=c++20 -O3 -DNDEBUG -march=native -flto=thin

# With enhanced diagnostics
clang++ -std=c++20 -Weverything -Wno-c++98-compat -Wno-padded
```

#### MSVC
```cmd
REM Debug build
cl /std:c++20 /W4 /Zi /Od /MDd

REM Release build
cl /std:c++20 /O2 /MD /DNDEBUG /GL

REM With conformance mode
cl /std:c++20 /permissive- /Zc:preprocessor /Zc:__cplusplus
```

### CMake Configuration

```cmake
# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler-specific flags
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(myapp PRIVATE
        -Wall -Wextra -Wpedantic
        $<$<CONFIG:Release>:-O3 -march=native>
        $<$<CONFIG:Debug>:-O0 -g -fsanitize=address,undefined>
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(myapp PRIVATE
        -Wall -Wextra -Wpedantic
        $<$<CONFIG:Release>:-O3 -march=native>
        $<$<CONFIG:Debug>:-O0 -g -fsanitize=address,undefined>
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(myapp PRIVATE
        /W4 /permissive-
        $<$<CONFIG:Release>:/O2>
        $<$<CONFIG:Debug>:/Od /Zi>
    )
endif()
```

## Cross-Compiler Compatibility

### Writing Portable Code

```cpp
#include <xieite/pp/compiler.hpp>
#include <xieite/pp/attr.hpp>

// Use XIEITE macros for cross-compiler compatibility
template<typename T>
class portable_class {
    // Force inline across compilers
    XIEITE_PP_IF(XIEITE_COMPILER_GCC)(__attribute__((always_inline)))
    XIEITE_PP_IF(XIEITE_COMPILER_CLANG)(__attribute__((always_inline)))
    XIEITE_PP_IF(XIEITE_COMPILER_MSVC)(__forceinline)
    T compute(T value) const {
        return value * 2;
    }

    // Conditional noexcept specification
    void process() noexcept(
        XIEITE_PP_IF(XIEITE_COMPILER_MSVC)(false)  // MSVC may throw
        XIEITE_PP_IF(!XIEITE_COMPILER_MSVC)(true)  // Others are safe
    ) {
        // Implementation
    }
};
```

### Common Compatibility Patterns

```cpp
// Handle different standard library implementations
#include <xieite/pp/stdlib.hpp>

XIEITE_PP_IF(XIEITE_STDLIB_LIBSTDCXX)(
    // GNU libstdc++ specific
)
XIEITE_PP_IF(XIEITE_STDLIB_LIBC)(
    // LLVM libc++ specific
)
XIEITE_PP_IF(XIEITE_STDLIB_MSVC)(
    // MSVC STL specific
)

// Attribute compatibility
#define XIEITE_LIKELY(x) \
    XIEITE_PP_IF(XIEITE_COMPILER_GCC || XIEITE_COMPILER_CLANG)( \
        __builtin_expect(!!(x), 1) \
    ) \
    XIEITE_PP_IF(XIEITE_COMPILER_MSVC)( \
        (x) \
    )
```

## Testing Across Compilers

### Continuous Integration Setup

```yaml
# GitHub Actions matrix for multiple compilers
strategy:
  matrix:
    include:
      - compiler: gcc-11
        os: ubuntu-latest
      - compiler: gcc-12
        os: ubuntu-latest
      - compiler: clang-14
        os: ubuntu-latest
      - compiler: clang-15
        os: ubuntu-latest
      - compiler: msvc
        os: windows-latest
```

### Compiler-Specific Test Cases

```cpp
#include <xieite/pp/compiler.hpp>

namespace compiler_tests {
    void run_all_tests() {
        XIEITE_PP_IF(XIEITE_COMPILER_GCC)(
            test_gcc_specific_features();
        )
        XIEITE_PP_IF(XIEITE_COMPILER_CLANG)(
            test_clang_specific_features();
        )
        XIEITE_PP_IF(XIEITE_COMPILER_MSVC)(
            test_msvc_specific_features();
        )

        test_common_features();
    }
}
```

## Compiler-Specific Optimizations

### GCC Optimizations

```cpp
#include <xieite/pp/compiler.hpp>

XIEITE_PP_IF(XIEITE_COMPILER_GCC)(
    // Use GCC vector extensions
    typedef int v4si __attribute__ ((vector_size (16)));

    // Profile-guided optimization
    __attribute__((hot))
    int hot_function(int x) {
        return x * x;
    }

    // Link-time optimization hints
    __attribute__((used))
    void referenced_function();
)
```

### Clang Optimizations

```cpp
XIEITE_PP_IF(XIEITE_COMPILER_CLANG)(
    // Use Clang's loop vectorization hints
    #pragma clang loop vectorize(enable)
    for (int i = 0; i < n; ++i) {
        // Vectorizable loop
    }

    // Memory layout optimization
    struct optimized_struct {
        int data[4] __attribute__((aligned(16)));
    };
)
```

### MSVC Optimizations

```cpp
XIEITE_PP_IF(XIEITE_COMPILER_MSVC)(
    // Use MSVC-specific pragmas
    #pragma intrinsic(_BitScanForward)

    // Profile-guided optimization
    #pragma optimize("gty", on)

    // Restrict pointer optimization
    void process_arrays(int* __restrict a, int* __restrict b);
)
```

## Troubleshooting

### Common Compiler Issues

1. **Template Error Cascades**: Use concepts to improve error messages
2. **Compilation Speed**: Use precompiled headers and parallel compilation
3. **Binary Size**: Enable link-time optimization and dead code elimination
4. **Debug Information**: Ensure proper debug flag usage across compilers

### Performance Comparison

| Feature | GCC | Clang | MSVC |
|---------|-----|-------|------|
| Compile Speed | Good | Excellent | Good |
| Runtime Performance | Excellent | Excellent | Good |
| Debug Information | Excellent | Excellent | Excellent |
| Template Instantiation | Good | Good | Fair |
| Link-Time Optimization | Excellent | Excellent | Good |

This compiler support reference ensures optimal XIEITE usage across different development environments and toolchains.