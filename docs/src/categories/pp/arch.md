# Architecture Detection

## Overview

XIEITE's architecture detection system provides comprehensive CPU architecture identification across 55+ different processor families. This preprocessor-based system enables compile-time architecture-specific optimizations and conditional compilation based on the target hardware platform.

## Architecture Detection Macros

### Macro Structure

Each architecture follows a consistent naming pattern:

```cpp
#define XIEITE_ARCH_TYPE_<ARCHITECTURE> 0/1     // Architecture present flag
#define XIEITE_ARCH_MAJOR_<ARCHITECTURE> n       // Major version number
#define XIEITE_ARCH_MINOR_<ARCHITECTURE> n       // Minor version number
#define XIEITE_ARCH_PATCH_<ARCHITECTURE> n       // Patch version number
```

### Version Comparison

The `XIEITE_ARCH_VER` macro enables version comparisons:

```cpp
#define XIEITE_ARCH_VER(type, cmp, major, ...)
// Usage: XIEITE_ARCH_VER(X86_64, >=, 2, 0, 0)
```

## Supported Architectures

### ARM Architectures

#### AArch32 (32-bit ARM)

Detection markers:
- `_ARM`, `_M_ARM`, `__arm__`, `__thumb__`
- ARM architecture versions 2-7

```cpp
#if XIEITE_ARCH_TYPE_AARCH32
    // 32-bit ARM specific code
    #if XIEITE_ARCH_MAJOR_AARCH32 >= 7
        // ARMv7+ specific optimizations
    #endif
#endif
```

#### AArch64 (64-bit ARM)

Detection markers:
- `__aarch64__`, `__arm64__`, `_M_ARM64`
- ARM architecture versions 8-9

```cpp
#if XIEITE_ARCH_TYPE_AARCH64
    // 64-bit ARM specific code
    #if XIEITE_ARCH_VER(AARCH64, >=, 9, 0)
        // ARMv9+ features
    #endif
#endif
```

### x86 Architectures

#### x86-32 (Intel/AMD 32-bit)

Detection markers:
- `_M_IX86`, `__i386__`, `__i486__`, `__i586__`, `__i686__`

```cpp
#if XIEITE_ARCH_TYPE_X86_32
    #if XIEITE_ARCH_MAJOR_X86_32 >= 6
        // Pentium Pro and later
    #elif XIEITE_ARCH_MAJOR_X86_32 == 5
        // Pentium
    #elif XIEITE_ARCH_MAJOR_X86_32 == 4
        // 486
    #endif
#endif
```

#### x86-64 (Intel/AMD 64-bit)

Detection markers:
- `__x86_64__`, `__amd64__`, `_M_X64`, `_M_AMD64`

```cpp
#if XIEITE_ARCH_TYPE_X86_64
    // 64-bit x86 specific code
    // All x86-64 processors support SSE2
#endif
```

### RISC Architectures

#### PowerPC

Detection markers:
- `__powerpc__`, `__ppc__`, `_M_PPC`
- Versions: POWER4-9, PowerPC 6xx series

```cpp
#if XIEITE_ARCH_TYPE_POWERPC
    #if XIEITE_ARCH_MAJOR_POWERPC >= 900
        // POWER9 features
    #endif
#endif
```

#### RISC-V

Detection markers:
- `__riscv`, `__riscv64`, `__riscv_xlen`

```cpp
#if XIEITE_ARCH_TYPE_RISC_V
    // RISC-V specific code
#endif
```

#### MIPS

Detection markers:
- `__mips__`, `_MIPS_ISA`, `_M_MRX000`
- MIPS I-V, MIPS32, MIPS64

```cpp
#if XIEITE_ARCH_TYPE_MIPS
    #if XIEITE_ARCH_MAJOR_MIPS == 64
        // MIPS64 specific
    #elif XIEITE_ARCH_MAJOR_MIPS == 32
        // MIPS32 specific
    #endif
#endif
```

#### SPARC

Detection markers:
- `__sparc__`, `__sparcv8`, `__sparcv9`

```cpp
#if XIEITE_ARCH_TYPE_SPARC
    #if XIEITE_ARCH_MAJOR_SPARC >= 9
        // SPARCv9 (64-bit)
    #endif
#endif
```

### Enterprise/Mainframe Architectures

#### IBM System/Z

Detection markers:
- `__s390__`, `__s390x__`, `__zarch__`

```cpp
#if XIEITE_ARCH_TYPE_IBM_SYSTEM_390 || XIEITE_ARCH_TYPE_IBM_Z
    // IBM mainframe specific code
#endif
```

#### Intel Itanium (IA-64)

Detection markers:
- `__ia64__`, `_M_IA64`, `__itanium__`

```cpp
#if XIEITE_ARCH_TYPE_IA64
    // Itanium specific code
    // Major.Minor version from _M_IA64
#endif
```

### Embedded Architectures

#### Motorola 68000

Detection markers:
- `__m68k__`, `__MC68K__`, `_M_M68K`

```cpp
#if XIEITE_ARCH_TYPE_MOTOROLA_68000
    #if XIEITE_ARCH_MAJOR_MOTOROLA_68000 >= 4
        // 68040/68060
    #elif XIEITE_ARCH_MAJOR_MOTOROLA_68000 >= 2
        // 68020/68030
    #endif
#endif
```

#### Texas Instruments DSPs

Detection for TMS320 and TMS470 families:

```cpp
#if XIEITE_ARCH_TYPE_TMS320
    #if XIEITE_ARCH_MAJOR_TMS320 >= 6000
        // C6000 DSP family
    #endif
#endif
```

#### Blackfin DSP

Detection markers:
- `__BFIN__`, `__ADSPBLACKFIN__`

```cpp
#if XIEITE_ARCH_TYPE_BLACKFIN
    // Blackfin DSP specific code
#endif
```

### Modern/Specialized Architectures

#### LoongArch

Chinese processor architecture:

```cpp
#if XIEITE_ARCH_TYPE_LOONGARCH
    #if XIEITE_ARCH_MAJOR_LOONGARCH == 64
        // 64-bit LoongArch
    #else
        // 32-bit LoongArch
    #endif
#endif
```

#### NVIDIA PTX

GPU compute architecture:

```cpp
#if XIEITE_ARCH_TYPE_PTX
    // CUDA/PTX specific code
    // __CUDA_ARCH__ provides compute capability
#endif
```

#### Hexagon DSP

Qualcomm Hexagon DSP:

```cpp
#if XIEITE_ARCH_TYPE_HEXAGON
    #ifdef __HVX_ARCH__
        // Hexagon Vector Extensions
    #endif
#endif
```

## Usage Patterns

### Basic Architecture Detection

```cpp
#include <xieite/pp/arch.hpp>

#if XIEITE_ARCH_TYPE_X86_64
    // x86-64 specific implementation
    void optimize_for_x64() {
        // Use x64 specific instructions
    }
#elif XIEITE_ARCH_TYPE_AARCH64
    // ARM64 specific implementation
    void optimize_for_arm64() {
        // Use ARM64 specific instructions
    }
#else
    // Generic fallback
    void optimize_generic() {
        // Portable implementation
    }
#endif
```

### Version-Based Optimization

```cpp
// Enable AVX on modern x86
#if XIEITE_ARCH_TYPE_X86_64 || \
    (XIEITE_ARCH_TYPE_X86_32 && XIEITE_ARCH_MAJOR_X86_32 >= 6)
    #define USE_SIMD_OPTIMIZATIONS
#endif

// Use ARM NEON on ARMv7+
#if XIEITE_ARCH_TYPE_AARCH32 && XIEITE_ARCH_MAJOR_AARCH32 >= 7
    #define USE_NEON
#endif

// Enable Power9 features
#if XIEITE_ARCH_TYPE_POWERPC && XIEITE_ARCH_VER(POWERPC, >=, 900)
    #define USE_POWER9_FEATURES
#endif
```

### Architecture Families

```cpp
// Group related architectures
#define IS_ARM_FAMILY (XIEITE_ARCH_TYPE_AARCH32 || XIEITE_ARCH_TYPE_AARCH64)
#define IS_X86_FAMILY (XIEITE_ARCH_TYPE_X86_32 || XIEITE_ARCH_TYPE_X86_64)
#define IS_IBM_MAINFRAME (XIEITE_ARCH_TYPE_IBM_SYSTEM_370 || \
                         XIEITE_ARCH_TYPE_IBM_SYSTEM_390 || \
                         XIEITE_ARCH_TYPE_IBM_Z)

#if IS_ARM_FAMILY
    // ARM-specific code (both 32 and 64-bit)
#endif
```

### Endianness Detection

Many architectures imply endianness:

```cpp
// Big-endian architectures
#if XIEITE_ARCH_TYPE_SPARC || \
    XIEITE_ARCH_TYPE_IBM_SYSTEM_390 || \
    XIEITE_ARCH_TYPE_IBM_Z || \
    (XIEITE_ARCH_TYPE_POWERPC && !defined(_LITTLE_ENDIAN))
    #define BIG_ENDIAN_ARCH
#endif

// Bi-endian architectures (runtime selectable)
#if XIEITE_ARCH_TYPE_AARCH64 || \
    XIEITE_ARCH_TYPE_POWERPC || \
    XIEITE_ARCH_TYPE_MIPS
    // May be either endianness
#endif
```

## Integration with Other Systems

### Platform Detection

Architecture detection complements platform detection:

```cpp
#include <xieite/pp/platform.hpp>
#include <xieite/pp/arch.hpp>

#if XIEITE_PLATFORM_TYPE_LINUX && XIEITE_ARCH_TYPE_X86_64
    // Linux on x86-64
#elif XIEITE_PLATFORM_TYPE_WINDOWS && XIEITE_ARCH_TYPE_AARCH64
    // Windows on ARM64
#endif
```

### Compiler-Specific Features

```cpp
#include <xieite/pp/compiler.hpp>

#if XIEITE_COMPILER_TYPE_GCC && XIEITE_ARCH_TYPE_X86_64
    // GCC on x86-64 - use GCC built-ins
    #define USE_GCC_BUILTINS
#elif XIEITE_COMPILER_TYPE_MSVC && XIEITE_ARCH_TYPE_X86_64
    // MSVC on x86-64 - use MSVC intrinsics
    #define USE_MSVC_INTRINSICS
#endif
```

## Implementation Notes

### Detection Priority

The system uses cascading detection with priority:
1. Compiler-specific macros (most reliable)
2. Architecture-specific defines
3. Generic markers (fallback)

### Version Extraction

Version numbers are extracted from various sources:
- Compiler defines (`_M_IX86`, `__ARM_ARCH`)
- Architecture-specific macros
- Feature detection macros

### Zero Initialization

All architecture macros are pre-initialized to 0:
```cpp
#define XIEITE_ARCH_TYPE_<NAME> 0
#define XIEITE_ARCH_MAJOR_<NAME> 0
#define XIEITE_ARCH_MINOR_<NAME> 0
#define XIEITE_ARCH_PATCH_<NAME> 0
```

This ensures clean conditional compilation without undefined macro warnings.

## Best Practices

### 1. Use Type Checks First

```cpp
// Good: Check type before version
#if XIEITE_ARCH_TYPE_AARCH64
    #if XIEITE_ARCH_MAJOR_AARCH64 >= 9
        // ARMv9 specific
    #endif
#endif

// Bad: Version check without type
#if XIEITE_ARCH_MAJOR_AARCH64 >= 9  // May be 0 on non-ARM
    // ...
#endif
```

### 2. Provide Fallbacks

```cpp
#if XIEITE_ARCH_TYPE_X86_64
    // Optimized x64 implementation
    uint64_t fast_multiply(uint64_t a, uint64_t b) {
        // Use x64 specific multiply
    }
#elif XIEITE_ARCH_TYPE_AARCH64
    // Optimized ARM64 implementation
    uint64_t fast_multiply(uint64_t a, uint64_t b) {
        // Use ARM64 specific multiply
    }
#else
    // Portable fallback
    uint64_t fast_multiply(uint64_t a, uint64_t b) {
        return a * b;
    }
#endif
```

### 3. Document Architecture Requirements

```cpp
// Requires: x86-64 or ARMv8+ for optimal performance
// Fallback: Generic C++ implementation
#if XIEITE_ARCH_TYPE_X86_64 || \
    (XIEITE_ARCH_TYPE_AARCH64 && XIEITE_ARCH_MAJOR_AARCH64 >= 8)
    #define HAS_SIMD_ACCELERATION
#endif
```

## Maintenance

The architecture detection system is maintained based on:
- Compiler documentation
- Architecture vendor specifications
- Community predef project
- Testing on actual hardware

References are included as comments in the source file for verification and updates.

## Summary

XIEITE's architecture detection provides a unified interface for identifying and versioning 55+ processor architectures. This enables portable code that can leverage architecture-specific optimizations while maintaining fallback implementations for maximum compatibility. The consistent macro naming and version comparison system makes it easy to write architecture-aware code without deep knowledge of platform-specific defines.