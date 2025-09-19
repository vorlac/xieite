# Architecture Detection

## Overview

XIEITE provides comprehensive processor architecture detection capabilities through preprocessor macros. The architecture detection system automatically identifies the target processor architecture and provides version information where available, supporting over 50 different architectures including modern, legacy, and embedded processors.

## Core Architecture Detection

### Primary Architecture Detection
Implementation: `include/xieite/pp/arch.hpp` (lines 6-238)

The library defines `XIEITE_ARCH_TYPE_*` macros for each supported architecture when detected:

```cpp
// Example architecture detections
#if defined(__aarch64__)
#    define XIEITE_ARCH_TYPE_AARCH64 1
#elif defined(__arm__)
#    define XIEITE_ARCH_TYPE_ARM 1
#elif defined(__x86_64__) || defined(_M_X64)
#    define XIEITE_ARCH_TYPE_X86_64 1
#elif defined(__i386__) || defined(_M_IX86)
#    define XIEITE_ARCH_TYPE_X86 1
#endif
```

Each architecture detection sets exactly one macro to `1`, allowing conditional compilation based on target architecture.

### Comprehensive Architecture Support
Implementation: `include/xieite/pp/arch.hpp` (lines 6-238)

Supported architectures include:

**ARM Family:**
- `XIEITE_ARCH_TYPE_AARCH64` - ARM 64-bit (ARMv8+)
- `XIEITE_ARCH_TYPE_ARM` - ARM 32-bit (ARMv4+)

**x86 Family:**
- `XIEITE_ARCH_TYPE_X86_64` - x86-64 (AMD64/Intel 64)
- `XIEITE_ARCH_TYPE_X86` - x86 32-bit (IA-32)

**MIPS Family:**
- `XIEITE_ARCH_TYPE_MIPS64` - MIPS 64-bit
- `XIEITE_ARCH_TYPE_MIPS` - MIPS 32-bit

**PowerPC Family:**
- `XIEITE_ARCH_TYPE_POWERPC64` - PowerPC 64-bit
- `XIEITE_ARCH_TYPE_POWERPC` - PowerPC 32-bit

**RISC-V Family:**
- `XIEITE_ARCH_TYPE_RISCV64` - RISC-V 64-bit
- `XIEITE_ARCH_TYPE_RISCV` - RISC-V 32-bit

**SPARC Family:**
- `XIEITE_ARCH_TYPE_SPARC64` - SPARC 64-bit (UltraSPARC)
- `XIEITE_ARCH_TYPE_SPARC` - SPARC 32-bit

**Legacy and Embedded:**
- `XIEITE_ARCH_TYPE_ALPHA` - DEC Alpha
- `XIEITE_ARCH_TYPE_BLACKFIN` - Analog Devices Blackfin
- `XIEITE_ARCH_TYPE_CONVEX` - Convex Computer
- `XIEITE_ARCH_TYPE_EPIPHANY` - Adapteva Epiphany
- `XIEITE_ARCH_TYPE_HPPA` - HP PA-RISC
- `XIEITE_ARCH_TYPE_IA64` - Intel Itanium (IA-64)
- `XIEITE_ARCH_TYPE_M68K` - Motorola 68000
- `XIEITE_ARCH_TYPE_MICROBLAZE` - Xilinx MicroBlaze
- `XIEITE_ARCH_TYPE_PYRAMID` - Pyramid Technology
- `XIEITE_ARCH_TYPE_RS6000` - IBM RS/6000
- `XIEITE_ARCH_TYPE_SH` - SuperH
- `XIEITE_ARCH_TYPE_SYSTEMZ` - IBM System z
- `XIEITE_ARCH_TYPE_TMS320` - Texas Instruments TMS320
- `XIEITE_ARCH_TYPE_TMS470` - Texas Instruments TMS470

## Usage Examples

### Basic Architecture Detection
```cpp
#include <xieite/pp/arch.hpp>

// Check current architecture
#if defined(XIEITE_ARCH_TYPE_X86_64)
    // x86-64 specific code
    constexpr std::size_t cache_line_size = 64;
    constexpr bool has_simd = true;
#elif defined(XIEITE_ARCH_TYPE_ARM) || defined(XIEITE_ARCH_TYPE_AARCH64)
    // ARM specific code
    constexpr std::size_t cache_line_size = 64;
    constexpr bool has_simd = true;
#elif defined(XIEITE_ARCH_TYPE_MIPS)
    // MIPS specific code
    constexpr std::size_t cache_line_size = 32;
    constexpr bool has_simd = false;
#else
    // Generic fallback
    constexpr std::size_t cache_line_size = 32;
    constexpr bool has_simd = false;
#endif
```

### Architecture-Specific Optimizations
```cpp
#include <xieite/pp/arch.hpp>

template<typename T>
void optimized_memcpy(T* dest, const T* src, std::size_t count) {
#if defined(XIEITE_ARCH_TYPE_X86_64)
    // Use x86-64 SIMD instructions
    if constexpr (sizeof(T) == 4 && alignof(T) >= 16) {
        // SSE-optimized copy for 32-bit aligned data
        __m128i* dest_simd = reinterpret_cast<__m128i*>(dest);
        const __m128i* src_simd = reinterpret_cast<const __m128i*>(src);

        for (std::size_t i = 0; i < count / 4; ++i) {
            _mm_store_si128(dest_simd + i, _mm_load_si128(src_simd + i));
        }

        // Handle remaining elements
        std::size_t remaining = count % 4;
        std::memcpy(dest + count - remaining, src + count - remaining,
                   remaining * sizeof(T));
    } else {
        std::memcpy(dest, src, count * sizeof(T));
    }
#elif defined(XIEITE_ARCH_TYPE_AARCH64)
    // Use ARM NEON instructions
    if constexpr (sizeof(T) == 4 && alignof(T) >= 16) {
        // NEON-optimized copy for 32-bit aligned data
        float32x4_t* dest_neon = reinterpret_cast<float32x4_t*>(dest);
        const float32x4_t* src_neon = reinterpret_cast<const float32x4_t*>(src);

        for (std::size_t i = 0; i < count / 4; ++i) {
            vst1q_f32(reinterpret_cast<float*>(dest_neon + i),
                     vld1q_f32(reinterpret_cast<const float*>(src_neon + i)));
        }

        // Handle remaining elements
        std::size_t remaining = count % 4;
        std::memcpy(dest + count - remaining, src + count - remaining,
                   remaining * sizeof(T));
    } else {
        std::memcpy(dest, src, count * sizeof(T));
    }
#else
    // Generic implementation
    std::memcpy(dest, src, count * sizeof(T));
#endif
}
```

### Memory Alignment Strategies
```cpp
#include <xieite/pp/arch.hpp>

// Architecture-specific alignment requirements
template<typename T>
class AlignedAllocator {
private:
    static constexpr std::size_t get_alignment() {
#if defined(XIEITE_ARCH_TYPE_X86_64)
        // x86-64: Align to cache line for optimal performance
        return std::max(alignof(T), 64uz);
#elif defined(XIEITE_ARCH_TYPE_AARCH64)
        // ARM64: Align to cache line
        return std::max(alignof(T), 64uz);
#elif defined(XIEITE_ARCH_TYPE_ARM)
        // ARM32: More conservative alignment
        return std::max(alignof(T), 32uz);
#elif defined(XIEITE_ARCH_TYPE_MIPS) || defined(XIEITE_ARCH_TYPE_MIPS64)
        // MIPS: Align to cache line boundary
        return std::max(alignof(T), 32uz);
#else
        // Conservative default
        return std::max(alignof(T), 16uz);
#endif
    }

public:
    static constexpr std::size_t alignment = get_alignment();

    T* allocate(std::size_t n) {
        return static_cast<T*>(std::aligned_alloc(alignment, n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t) {
        std::free(p);
    }
};
```

## Advanced Patterns

### Architecture Feature Detection
```cpp
#include <xieite/pp/arch.hpp>

// Compile-time architecture feature detection
struct ArchitectureTraits {
    // Pointer size detection
    static constexpr std::size_t pointer_size =
#if defined(XIEITE_ARCH_TYPE_X86_64) || defined(XIEITE_ARCH_TYPE_AARCH64) || \
    defined(XIEITE_ARCH_TYPE_MIPS64) || defined(XIEITE_ARCH_TYPE_POWERPC64) || \
    defined(XIEITE_ARCH_TYPE_SPARC64) || defined(XIEITE_ARCH_TYPE_IA64) || \
    defined(XIEITE_ARCH_TYPE_RISCV64)
        8;
#else
        4;
#endif

    // Endianness hints (architecture-specific)
    static constexpr bool likely_little_endian =
#if defined(XIEITE_ARCH_TYPE_X86) || defined(XIEITE_ARCH_TYPE_X86_64) || \
    defined(XIEITE_ARCH_TYPE_AARCH64) || defined(XIEITE_ARCH_TYPE_RISCV) || \
    defined(XIEITE_ARCH_TYPE_RISCV64)
        true;
#elif defined(XIEITE_ARCH_TYPE_SPARC) || defined(XIEITE_ARCH_TYPE_SPARC64) || \
      defined(XIEITE_ARCH_TYPE_SYSTEMZ)
        false;
#else
        true; // Most modern architectures are little-endian
#endif

    // SIMD availability hints
    static constexpr bool has_vector_instructions =
#if defined(XIEITE_ARCH_TYPE_X86) || defined(XIEITE_ARCH_TYPE_X86_64) || \
    defined(XIEITE_ARCH_TYPE_ARM) || defined(XIEITE_ARCH_TYPE_AARCH64) || \
    defined(XIEITE_ARCH_TYPE_POWERPC) || defined(XIEITE_ARCH_TYPE_POWERPC64)
        true;
#else
        false;
#endif

    // Cache line size hints
    static constexpr std::size_t cache_line_size =
#if defined(XIEITE_ARCH_TYPE_X86) || defined(XIEITE_ARCH_TYPE_X86_64) || \
    defined(XIEITE_ARCH_TYPE_AARCH64)
        64;
#elif defined(XIEITE_ARCH_TYPE_ARM) || defined(XIEITE_ARCH_TYPE_MIPS) || \
      defined(XIEITE_ARCH_TYPE_MIPS64)
        32;
#else
        32; // Conservative default
#endif
};

// Usage
static_assert(ArchitectureTraits::pointer_size == sizeof(void*));
std::cout << "Architecture: " << ArchitectureTraits::pointer_size * 8 << "-bit\n";
std::cout << "Cache line size: " << ArchitectureTraits::cache_line_size << " bytes\n";
```

### Cross-Platform Data Structures
```cpp
#include <xieite/pp/arch.hpp>

// Architecture-aware data structure sizing
template<typename T>
struct OptimalVector {
private:
    // Choose container size based on architecture
    static constexpr std::size_t get_optimal_capacity() {
#if defined(XIEITE_ARCH_TYPE_X86_64) || defined(XIEITE_ARCH_TYPE_AARCH64)
        // 64-bit architectures: larger default capacity
        return 64;
#elif defined(XIEITE_ARCH_TYPE_X86) || defined(XIEITE_ARCH_TYPE_ARM)
        // 32-bit architectures: smaller default capacity
        return 32;
#else
        // Embedded/unknown: very conservative
        return 16;
#endif
    }

    static constexpr std::size_t optimal_capacity = get_optimal_capacity();

    // Architecture-specific storage strategy
#if defined(XIEITE_ARCH_TYPE_X86) || defined(XIEITE_ARCH_TYPE_X86_64)
    // x86: Use std::vector for good cache behavior
    std::vector<T> data_;
#elif defined(XIEITE_ARCH_TYPE_ARM) || defined(XIEITE_ARCH_TYPE_AARCH64)
    // ARM: Use std::vector with custom allocator
    std::vector<T, AlignedAllocator<T>> data_;
#else
    // Others: Simple array-based storage
    std::array<T, optimal_capacity> data_;
    std::size_t size_ = 0;
#endif

public:
    OptimalVector() {
#if !defined(XIEITE_ARCH_TYPE_ARM) && !defined(XIEITE_ARCH_TYPE_AARCH64) && \
    !defined(XIEITE_ARCH_TYPE_X86) && !defined(XIEITE_ARCH_TYPE_X86_64)
        // Initialize only for array-based storage
        data_.fill(T{});
#else
        data_.reserve(optimal_capacity);
#endif
    }

    void push_back(const T& value) {
#if defined(XIEITE_ARCH_TYPE_X86) || defined(XIEITE_ARCH_TYPE_X86_64) || \
    defined(XIEITE_ARCH_TYPE_ARM) || defined(XIEITE_ARCH_TYPE_AARCH64)
        data_.push_back(value);
#else
        if (size_ < optimal_capacity) {
            data_[size_++] = value;
        }
#endif
    }

    std::size_t size() const {
#if defined(XIEITE_ARCH_TYPE_X86) || defined(XIEITE_ARCH_TYPE_X86_64) || \
    defined(XIEITE_ARCH_TYPE_ARM) || defined(XIEITE_ARCH_TYPE_AARCH64)
        return data_.size();
#else
        return size_;
#endif
    }
};
```

### Performance Tuning Macros
```cpp
#include <xieite/pp/arch.hpp>

// Architecture-specific performance hints
#if defined(XIEITE_ARCH_TYPE_X86) || defined(XIEITE_ARCH_TYPE_X86_64)
    #define ARCH_LIKELY_BRANCH(x) __builtin_expect(!!(x), 1)
    #define ARCH_UNLIKELY_BRANCH(x) __builtin_expect(!!(x), 0)
    #define ARCH_PREFETCH(addr) __builtin_prefetch(addr, 0, 3)
    #define ARCH_FORCE_INLINE __forceinline
#elif defined(XIEITE_ARCH_TYPE_ARM) || defined(XIEITE_ARCH_TYPE_AARCH64)
    #define ARCH_LIKELY_BRANCH(x) __builtin_expect(!!(x), 1)
    #define ARCH_UNLIKELY_BRANCH(x) __builtin_expect(!!(x), 0)
    #define ARCH_PREFETCH(addr) __builtin_prefetch(addr, 0, 1)
    #define ARCH_FORCE_INLINE __attribute__((always_inline)) inline
#else
    #define ARCH_LIKELY_BRANCH(x) (x)
    #define ARCH_UNLIKELY_BRANCH(x) (x)
    #define ARCH_PREFETCH(addr) ((void)0)
    #define ARCH_FORCE_INLINE inline
#endif

// Usage in performance-critical code
ARCH_FORCE_INLINE int fast_search(const int* data, std::size_t size, int target) {
    for (std::size_t i = 0; i < size; ++i) {
        ARCH_PREFETCH(&data[i + 8]); // Prefetch ahead

        if (ARCH_LIKELY_BRANCH(data[i] != target)) {
            continue;
        }

        return static_cast<int>(i);
    }

    return -1; // Not found
}
```

## Implementation Details

### Detection Strategy
The architecture detection (arch.hpp:6-238) uses:
- Compiler-defined preprocessor macros for architecture identification
- Hierarchical checking from most specific to most general architectures
- Single-macro activation ensuring exactly one architecture is detected

### Compiler Support Matrix
The detection supports macros from:
- **GCC**: `__x86_64__`, `__i386__`, `__arm__`, `__aarch64__`, etc.
- **Clang**: Same as GCC plus additional Clang-specific macros
- **MSVC**: `_M_X64`, `_M_IX86`, `_M_ARM`, `_M_ARM64`, etc.
- **Intel ICC**: Intel-specific architecture macros
- **Embedded**: Various embedded compiler macro sets

### Fallback Handling
When no architecture is detected:
- No `XIEITE_ARCH_TYPE_*` macros are defined
- Code should provide generic fallbacks for unrecognized architectures
- Conservative defaults should be used for performance parameters

## Best Practices

1. **Always provide fallbacks** - Unknown architectures should have safe defaults
2. **Use architecture hints, not absolutes** - Architecture detection guides optimization, doesn't guarantee features
3. **Test on target hardware** - Architecture detection enables optimizations but requires validation
4. **Consider embedded constraints** - Many architectures have limited resources

## Common Use Cases

### Conditional Compilation for Libraries
```cpp
#include <xieite/pp/arch.hpp>

// Library providing architecture-specific implementations
namespace fast_math {

#if defined(XIEITE_ARCH_TYPE_X86_64)
    // x86-64 SSE/AVX implementations
    float vector_sum(const float* data, std::size_t count);
#elif defined(XIEITE_ARCH_TYPE_AARCH64)
    // ARM NEON implementations
    float vector_sum(const float* data, std::size_t count);
#else
    // Generic C++ implementation
    inline float vector_sum(const float* data, std::size_t count) {
        float sum = 0.0f;
        for (std::size_t i = 0; i < count; ++i) {
            sum += data[i];
        }
        return sum;
    }
#endif

} // namespace fast_math
```

### Build System Integration
```cpp
// In CMakeLists.txt or build configuration:
// -DXIEITE_TARGET_ARCH_X86_64=1 for x86-64 builds
// -DXIEITE_TARGET_ARCH_ARM=1 for ARM builds

#include <xieite/pp/arch.hpp>

// Verify build configuration matches runtime detection
#if defined(XIEITE_TARGET_ARCH_X86_64) && !defined(XIEITE_ARCH_TYPE_X86_64)
    #error "Build configured for x86-64 but compiler detects different architecture"
#elif defined(XIEITE_TARGET_ARCH_ARM) && !defined(XIEITE_ARCH_TYPE_ARM) && !defined(XIEITE_ARCH_TYPE_AARCH64)
    #error "Build configured for ARM but compiler detects different architecture"
#endif
```

## See Also

- [Platform Detection](./platform.md) - Operating system detection
- [Compiler Detection](../pp/compiler.md) - Compiler identification macros
- [Conditional Compilation](../pp/conditional.md) - Conditional compilation utilities
- [System API Reference](../../reference/api/sys.md)