# Compiler Detection

## Overview

XIEITE's compiler detection system provides comprehensive identification of 100+ C/C++ compilers with version information extraction. This preprocessor-based system enables compile-time compiler-specific optimizations, workarounds, and feature detection across a vast array of development environments.

## Compiler Detection Macros

### Macro Structure

Each compiler follows a consistent naming pattern:

```cpp
#define XIEITE_COMPILER_TYPE_<COMPILER> 0/1     // Compiler present flag
#define XIEITE_COMPILER_MAJOR_<COMPILER> n       // Major version number
#define XIEITE_COMPILER_MINOR_<COMPILER> n       // Minor version number
#define XIEITE_COMPILER_PATCH_<COMPILER> n       // Patch version number
```

### Version Comparison

The `XIEITE_COMPILER_VER` macro enables version comparisons:

```cpp
#define XIEITE_COMPILER_VER(type, cmp, major, ...)
// Usage: XIEITE_COMPILER_VER(GCC, >=, 11, 0, 0)
```

## Major Compiler Families

### GCC (GNU Compiler Collection)

Detection markers:
- `__GNUC__`, `__GNUC_MINOR__`, `__GNUC_PATCHLEVEL__`

```cpp
#if XIEITE_COMPILER_TYPE_GCC
    #if XIEITE_COMPILER_VER(GCC, >=, 11, 0, 0)
        // GCC 11+ features (concepts, coroutines)
    #elif XIEITE_COMPILER_VER(GCC, >=, 10, 0, 0)
        // GCC 10+ features
    #endif
#endif
```

Version extraction:
```cpp
XIEITE_COMPILER_MAJOR_GCC = __GNUC__
XIEITE_COMPILER_MINOR_GCC = __GNUC_MINOR__
XIEITE_COMPILER_PATCH_GCC = __GNUC_PATCHLEVEL__
```

### Clang/LLVM

Detection markers:
- `__clang__`, `__clang_major__`, `__clang_minor__`, `__clang_patchlevel__`

```cpp
#if XIEITE_COMPILER_TYPE_CLANG
    #if XIEITE_COMPILER_VER(CLANG, >=, 15, 0, 0)
        // Clang 15+ features
    #endif

    // Check for Apple Clang variant
    #ifdef __apple_build_version__
        // Apple Clang specific
    #endif
#endif
```

### Microsoft Visual C++

Detection markers:
- `_MSC_VER`, `_MSC_FULL_VER`, `_MSC_BUILD`

```cpp
#if XIEITE_COMPILER_TYPE_MSVC
    #if _MSC_VER >= 1930
        // Visual Studio 2022
    #elif _MSC_VER >= 1920
        // Visual Studio 2019
    #elif _MSC_VER >= 1910
        // Visual Studio 2017
    #endif
#endif
```

Version mapping:
```cpp
// MSVC version scheme:
// _MSC_VER = VVMM (VV = major, MM = minor)
// 1930+ = VS 2022
// 1920-1929 = VS 2019
// 1910-1919 = VS 2017
// 1900 = VS 2015
```

### Intel Compilers

#### Intel C++ Compiler Classic (ICC)

Detection markers:
- `__INTEL_COMPILER`, `__ICC`

```cpp
#if XIEITE_COMPILER_TYPE_ICC
    #if __INTEL_COMPILER >= 2021
        // Intel oneAPI Classic
    #endif
#endif
```

#### Intel DPC++/C++ Compiler (ICX)

Detection markers:
- `__INTEL_LLVM_COMPILER`

```cpp
#if XIEITE_COMPILER_TYPE_ICX
    // Intel oneAPI DPC++/C++ Compiler
    // Based on LLVM/Clang
#endif
```

## Specialized Compilers

### Embedded System Compilers

#### ARM Compiler

Detection markers:
- `__CC_ARM`, `__ARMCC_VERSION`, `__ARMCOMPILER_VERSION`

```cpp
#if XIEITE_COMPILER_TYPE_ARMCC
    #if XIEITE_COMPILER_MAJOR_ARMCC >= 6
        // ARM Compiler 6 (LLVM-based)
    #else
        // ARM Compiler 5 and earlier
    #endif
#endif
```

#### IAR Systems

Detection markers:
- `__IAR_SYSTEMS_ICC__`

```cpp
#if XIEITE_COMPILER_TYPE_IAR
    // IAR Embedded Workbench
    #if __VER__ >= 9000000
        // Version 9.x
    #endif
#endif
```

#### Green Hills

Detection markers:
- `__ghs__`, `__GHS_VERSION_NUMBER__`

```cpp
#if XIEITE_COMPILER_TYPE_GREEN_HILLS
    // Green Hills MULTI compiler
#endif
```

### High-Performance Computing

#### Cray

Detection markers:
- `_CRAYC`

```cpp
#if XIEITE_COMPILER_TYPE_CRAY_C
    // Cray C compiler
    #if _RELEASE >= 10
        // Cray compiler 10+
    #endif
#endif
```

#### PGI/NVIDIA HPC

Detection markers:
- `__PGI`, `__NVCOMPILER`

```cpp
#if XIEITE_COMPILER_TYPE_PGI
    // PGI/NVIDIA HPC compiler
#elif XIEITE_COMPILER_TYPE_NVHPC
    // NVIDIA HPC SDK compiler
#endif
```

#### Fujitsu

Detection markers:
- `__FCC_VERSION`, `__fcc_version`

```cpp
#if XIEITE_COMPILER_TYPE_FUJITSU_CPP
    // Fujitsu C++ compiler
#endif
```

### Cross-Platform/Web

#### Emscripten

Detection markers:
- `__EMSCRIPTEN__`

```cpp
#if XIEITE_COMPILER_TYPE_EMSCRIPTEN
    // WebAssembly target
    #if __EMSCRIPTEN_major__ >= 3
        // Emscripten 3.x features
    #endif
#endif
```

#### Digital Mars

Detection markers:
- `__DMC__`

```cpp
#if XIEITE_COMPILER_TYPE_DIGITAL_MARS
    // Digital Mars C/C++
#endif
```

## Compiler Feature Detection

### C++ Standard Support

```cpp
// Combine compiler and version for feature detection
#if XIEITE_COMPILER_TYPE_GCC && XIEITE_COMPILER_VER(GCC, >=, 11, 0, 0)
    #define HAS_FULL_CPP20_SUPPORT
#elif XIEITE_COMPILER_TYPE_CLANG && XIEITE_COMPILER_VER(CLANG, >=, 14, 0, 0)
    #define HAS_FULL_CPP20_SUPPORT
#elif XIEITE_COMPILER_TYPE_MSVC && _MSC_VER >= 1929
    #define HAS_FULL_CPP20_SUPPORT
#endif
```

### Compiler Extensions

```cpp
// Detect compiler-specific attributes
#if XIEITE_COMPILER_TYPE_GCC || XIEITE_COMPILER_TYPE_CLANG
    #define XIEITE_ALWAYS_INLINE __attribute__((always_inline))
    #define XIEITE_NOINLINE __attribute__((noinline))
    #define XIEITE_LIKELY(x) __builtin_expect(!!(x), 1)
    #define XIEITE_UNLIKELY(x) __builtin_expect(!!(x), 0)
#elif XIEITE_COMPILER_TYPE_MSVC
    #define XIEITE_ALWAYS_INLINE __forceinline
    #define XIEITE_NOINLINE __declspec(noinline)
    #define XIEITE_LIKELY(x) (x)
    #define XIEITE_UNLIKELY(x) (x)
#else
    #define XIEITE_ALWAYS_INLINE inline
    #define XIEITE_NOINLINE
    #define XIEITE_LIKELY(x) (x)
    #define XIEITE_UNLIKELY(x) (x)
#endif
```

### Warning Control

```cpp
// Compiler-specific warning pragmas
#if XIEITE_COMPILER_TYPE_GCC
    #define XIEITE_PRAGMA_WARN_PUSH _Pragma("GCC diagnostic push")
    #define XIEITE_PRAGMA_WARN_POP _Pragma("GCC diagnostic pop")
    #define XIEITE_PRAGMA_WARN_DISABLE(w) _Pragma(GCC diagnostic ignored #w)
#elif XIEITE_COMPILER_TYPE_CLANG
    #define XIEITE_PRAGMA_WARN_PUSH _Pragma("clang diagnostic push")
    #define XIEITE_PRAGMA_WARN_POP _Pragma("clang diagnostic pop")
    #define XIEITE_PRAGMA_WARN_DISABLE(w) _Pragma(clang diagnostic ignored #w)
#elif XIEITE_COMPILER_TYPE_MSVC
    #define XIEITE_PRAGMA_WARN_PUSH __pragma(warning(push))
    #define XIEITE_PRAGMA_WARN_POP __pragma(warning(pop))
    #define XIEITE_PRAGMA_WARN_DISABLE(w) __pragma(warning(disable: w))
#endif
```

## Compiler Workarounds

### Known Issues Database

```cpp
// GCC bug workarounds
#if XIEITE_COMPILER_TYPE_GCC && XIEITE_COMPILER_VER(GCC, <, 10, 0, 0)
    // GCC < 10 has issues with certain constexpr contexts
    #define XIEITE_CONSTEXPR_WORKAROUND const
#else
    #define XIEITE_CONSTEXPR_WORKAROUND constexpr
#endif

// MSVC conformance workarounds
#if XIEITE_COMPILER_TYPE_MSVC && _MSC_VER < 1920
    // MSVC < 2019 needs /permissive- for conformance
    #define XIEITE_NEEDS_PERMISSIVE_FLAG
#endif

// Clang template instantiation quirks
#if XIEITE_COMPILER_TYPE_CLANG && XIEITE_COMPILER_VER(CLANG, <, 12, 0, 0)
    // Clang < 12 has issues with certain SFINAE patterns
    #define XIEITE_SFINAE_WORKAROUND
#endif
```

### Optimization Hints

```cpp
// Compiler-specific optimization pragmas
#if XIEITE_COMPILER_TYPE_GCC || XIEITE_COMPILER_TYPE_CLANG
    #define XIEITE_HOT __attribute__((hot))
    #define XIEITE_COLD __attribute__((cold))
    #define XIEITE_PURE __attribute__((pure))
#elif XIEITE_COMPILER_TYPE_MSVC
    #define XIEITE_HOT
    #define XIEITE_COLD
    #define XIEITE_PURE
#endif
```

## Usage Patterns

### Basic Compiler Detection

```cpp
#include <xieite/pp/compiler.hpp>

#if XIEITE_COMPILER_TYPE_GCC
    // GCC-specific code
    void use_gcc_builtins() {
        int x = __builtin_popcount(42);
    }
#elif XIEITE_COMPILER_TYPE_MSVC
    // MSVC-specific code
    void use_msvc_intrinsics() {
        int x = __popcnt(42);
    }
#else
    // Generic fallback
    void use_portable_code() {
        // Portable implementation
    }
#endif
```

### Version-Based Features

```cpp
// Enable features based on compiler support
#if XIEITE_COMPILER_TYPE_GCC && XIEITE_COMPILER_VER(GCC, >=, 10, 0, 0)
    #define USE_CONCEPTS
    #define USE_COROUTINES
#elif XIEITE_COMPILER_TYPE_CLANG && XIEITE_COMPILER_VER(CLANG, >=, 11, 0, 0)
    #define USE_CONCEPTS
    // Clang coroutines need different version
    #if XIEITE_COMPILER_VER(CLANG, >=, 14, 0, 0)
        #define USE_COROUTINES
    #endif
#elif XIEITE_COMPILER_TYPE_MSVC && _MSC_VER >= 1928
    #define USE_CONCEPTS
    #define USE_COROUTINES
#endif
```

### Compiler Families

```cpp
// Group related compilers
#define IS_GCC_COMPATIBLE (XIEITE_COMPILER_TYPE_GCC || \
                           XIEITE_COMPILER_TYPE_CLANG || \
                           XIEITE_COMPILER_TYPE_ICC || \
                           XIEITE_COMPILER_TYPE_ICX)

#define IS_MSVC_COMPATIBLE (XIEITE_COMPILER_TYPE_MSVC || \
                            XIEITE_COMPILER_TYPE_CLANG_CL || \
                            XIEITE_COMPILER_TYPE_ICC_WIN)

#if IS_GCC_COMPATIBLE
    // Use GCC-style attributes and builtins
#elif IS_MSVC_COMPATIBLE
    // Use MSVC-style pragmas and intrinsics
#endif
```

## Integration with Other Systems

### Platform and Architecture

```cpp
#include <xieite/pp/platform.hpp>
#include <xieite/pp/arch.hpp>
#include <xieite/pp/compiler.hpp>

#if XIEITE_PLATFORM_TYPE_LINUX && \
    XIEITE_ARCH_TYPE_X86_64 && \
    XIEITE_COMPILER_TYPE_GCC
    // Linux + x86-64 + GCC specific optimizations
    #define USE_PLATFORM_SPECIFIC_OPTIMIZATIONS
#endif
```

### Language Standard Detection

```cpp
// Combine with __cplusplus for standard detection
#if XIEITE_COMPILER_TYPE_GCC || XIEITE_COMPILER_TYPE_CLANG
    #if __cplusplus >= 202002L
        #define CPP20_AVAILABLE
    #elif __cplusplus >= 201703L
        #define CPP17_AVAILABLE
    #endif
#elif XIEITE_COMPILER_TYPE_MSVC
    #if _MSVC_LANG >= 202002L
        #define CPP20_AVAILABLE
    #elif _MSVC_LANG >= 201703L
        #define CPP17_AVAILABLE
    #endif
#endif
```

## Special Compiler Categories

### Static Analyzers

```cpp
#if XIEITE_COMPILER_TYPE_COVERITY_STATIC_ANALYZER
    // Coverity static analysis
    // Suppress false positives
    #define COVERITY_SUPPRESS(warning_id)
#endif

#if XIEITE_COMPILER_TYPE_PVS_STUDIO
    // PVS-Studio analysis
    //-V::warning_id
#endif
```

### Cross Compilers

```cpp
#if XIEITE_COMPILER_TYPE_MINGW32 || XIEITE_COMPILER_TYPE_MINGW64
    // MinGW cross-compilation
    #define CROSS_COMPILING_TO_WINDOWS
#endif

#if XIEITE_COMPILER_TYPE_DJGPP
    // DOS cross-compilation
    #define CROSS_COMPILING_TO_DOS
#endif
```

### Exotic/Historical Compilers

The system also detects many historical and specialized compilers:
- Borland C++ Builder
- Watcom C/C++
- Zortech C++
- Aztec C
- Lattice C
- SAS/C
- DICE C (Amiga)
- And many more...

## Implementation Notes

### Detection Priority

Compilers are detected in a specific order to handle:
1. Compilers that define multiple markers
2. Compilers based on other compilers (ICX based on Clang)
3. Compilers with multiple versions/variants

### Version Extraction

Version information is extracted from various sources:
- Direct version macros (`__GNUC__`, `__clang_major__`)
- Encoded version numbers (`_MSC_VER`, `__INTEL_COMPILER`)
- Build numbers and patch levels

### Compiler Emulation

Some compilers emulate others:
```cpp
// Intel ICX defines __clang__
// Must check ICX before Clang
#if defined(__INTEL_LLVM_COMPILER)
    // ICX
#elif defined(__clang__)
    // Clang
#endif
```

## Best Practices

### 1. Check Most Specific First

```cpp
// Good: Check specific compilers before generic
#if XIEITE_COMPILER_TYPE_APPLE_CLANG
    // Apple Clang specific
#elif XIEITE_COMPILER_TYPE_CLANG
    // Generic Clang
#elif XIEITE_COMPILER_TYPE_GCC
    // GCC
#endif
```

### 2. Provide Fallbacks

```cpp
#if XIEITE_COMPILER_TYPE_GCC && XIEITE_COMPILER_VER(GCC, >=, 11, 0, 0)
    // Modern GCC features
    using my_type = decltype([]<typename T>(T){});
#elif XIEITE_COMPILER_TYPE_CLANG && XIEITE_COMPILER_VER(CLANG, >=, 12, 0, 0)
    // Modern Clang features
    using my_type = decltype([]<typename T>(T){});
#else
    // Fallback for older compilers
    template<typename T> struct my_type_impl {};
    using my_type = my_type_impl<void>;
#endif
```

### 3. Document Requirements

```cpp
// Requires: GCC 10+, Clang 11+, MSVC 2019+, or ICC 2021+
// For full C++20 concept support
#if (XIEITE_COMPILER_TYPE_GCC && XIEITE_COMPILER_VER(GCC, >=, 10, 0, 0)) || \
    (XIEITE_COMPILER_TYPE_CLANG && XIEITE_COMPILER_VER(CLANG, >=, 11, 0, 0)) || \
    (XIEITE_COMPILER_TYPE_MSVC && _MSC_VER >= 1928) || \
    (XIEITE_COMPILER_TYPE_ICC && __INTEL_COMPILER >= 2021)
    #define CONCEPTS_SUPPORTED
#endif
```

## Maintenance

The compiler detection system is maintained by:
- Monitoring compiler releases and version changes
- Testing on various compiler versions
- Community feedback and contributions
- Reference to compiler documentation

## Summary

XIEITE's compiler detection system provides comprehensive identification of 100+ compilers with detailed version information. This enables portable code that can leverage compiler-specific optimizations and features while providing appropriate workarounds for known issues. The consistent macro naming and version comparison system makes it easy to write compiler-aware code that maximizes performance and compatibility across diverse development environments.