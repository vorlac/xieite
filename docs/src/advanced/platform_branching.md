# Platform Branching

This document covers advanced platform branching techniques using XIEITE's preprocessor utilities, enabling sophisticated conditional compilation strategies for different platforms, architectures, and environments.

## Conditional Compilation Strategies

### Multi-Level Platform Detection

XIEITE enables hierarchical platform branching:

```cpp
#include <xieite/pp/platform.hpp>
#include <xieite/pp/if.hpp>
#include <xieite/pp/arch.hpp>
#include <xieite/pp/compiler.hpp>

// Multi-level platform-specific optimization
template<typename T>
class platform_optimized_container {
public:
    void insert(const T& value) {
        // Top-level OS branching
        XIEITE_PP_IF(XIEITE_PLATFORM_WINDOWS)(
            insert_windows_impl(value);
        )
        XIEITE_PP_IF(XIEITE_PLATFORM_UNIX)(
            // Second-level architecture branching within Unix
            XIEITE_PP_IF(XIEITE_ARCH_X86_64)(
                insert_unix_x64_impl(value);
            )
            XIEITE_PP_IF(XIEITE_ARCH_ARM64)(
                insert_unix_arm64_impl(value);
            )
            XIEITE_PP_IF(!XIEITE_ARCH_X86_64 && !XIEITE_ARCH_ARM64)(
                insert_unix_generic_impl(value);
            )
        )
        XIEITE_PP_IF(!XIEITE_PLATFORM_WINDOWS && !XIEITE_PLATFORM_UNIX)(
            insert_generic_impl(value);
        )
    }

private:
    std::vector<T> data_;

    XIEITE_PP_IF(XIEITE_PLATFORM_WINDOWS)(
        void insert_windows_impl(const T& value) {
            // Windows-specific implementation with compiler sub-branching
            XIEITE_PP_IF(XIEITE_COMPILER_MSVC)(
                // MSVC-specific optimizations
                data_.push_back(value);
            )
            XIEITE_PP_IF(!XIEITE_COMPILER_MSVC)(
                // MinGW or other Windows compilers
                data_.push_back(value);
            )
        }
    )

    XIEITE_PP_IF(XIEITE_PLATFORM_UNIX)(
        XIEITE_PP_IF(XIEITE_ARCH_X86_64)(
            void insert_unix_x64_impl(const T& value) {
                // Unix x86-64 specific optimizations
                data_.push_back(value);
            }
        )

        XIEITE_PP_IF(XIEITE_ARCH_ARM64)(
            void insert_unix_arm64_impl(const T& value) {
                // Unix ARM64 specific optimizations
                data_.push_back(value);
            }
        )

        XIEITE_PP_IF(!XIEITE_ARCH_X86_64 && !XIEITE_ARCH_ARM64)(
            void insert_unix_generic_impl(const T& value) {
                // Generic Unix implementation
                data_.push_back(value);
            }
        )
    )

    void insert_generic_impl(const T& value) {
        // Fallback implementation
        data_.push_back(value);
    }
};
```

### Feature-Based Branching

Branching based on available features rather than platforms:

```cpp
#include <xieite/pp/feat.hpp>
#include <xieite/pp/if.hpp>
#include <xieite/pp/has_incl.hpp>

// Feature detection and conditional compilation
namespace feature_detection {
    // Check for specific header availability
    XIEITE_PP_IF(XIEITE_PP_HAS_INCL(<immintrin.h>))(
        #include <immintrin.h>
        #define XIEITE_HAS_SIMD 1
    )

    XIEITE_PP_IF(XIEITE_PP_HAS_INCL(<arm_neon.h>))(
        #include <arm_neon.h>
        #define XIEITE_HAS_NEON 1
    )

    template<typename T>
    class feature_optimized_math {
    public:
        static void vector_add(const T* a, const T* b, T* result, std::size_t count) {
            XIEITE_PP_IF(XIEITE_HAS_SIMD && std::is_same_v<T, float>)(
                vector_add_sse(a, b, result, count);
            )
            XIEITE_PP_IF(XIEITE_HAS_NEON && std::is_same_v<T, float>)(
                vector_add_neon(a, b, result, count);
            )
            XIEITE_PP_IF((!XIEITE_HAS_SIMD && !XIEITE_HAS_NEON) || !std::is_same_v<T, float>)(
                vector_add_generic(a, b, result, count);
            )
        }

    private:
        XIEITE_PP_IF(XIEITE_HAS_SIMD)(
            static void vector_add_sse(const float* a, const float* b, float* result, std::size_t count) {
                std::size_t simd_count = count & ~3; // Round down to multiple of 4
                for (std::size_t i = 0; i < simd_count; i += 4) {
                    __m128 va = _mm_loadu_ps(&a[i]);
                    __m128 vb = _mm_loadu_ps(&b[i]);
                    __m128 vr = _mm_add_ps(va, vb);
                    _mm_storeu_ps(&result[i], vr);
                }
                // Handle remaining elements
                for (std::size_t i = simd_count; i < count; ++i) {
                    result[i] = a[i] + b[i];
                }
            }
        )

        XIEITE_PP_IF(XIEITE_HAS_NEON)(
            static void vector_add_neon(const float* a, const float* b, float* result, std::size_t count) {
                std::size_t simd_count = count & ~3; // Round down to multiple of 4
                for (std::size_t i = 0; i < simd_count; i += 4) {
                    float32x4_t va = vld1q_f32(&a[i]);
                    float32x4_t vb = vld1q_f32(&b[i]);
                    float32x4_t vr = vaddq_f32(va, vb);
                    vst1q_f32(&result[i], vr);
                }
                // Handle remaining elements
                for (std::size_t i = simd_count; i < count; ++i) {
                    result[i] = a[i] + b[i];
                }
            }
        )

        static void vector_add_generic(const T* a, const T* b, T* result, std::size_t count) {
            for (std::size_t i = 0; i < count; ++i) {
                result[i] = a[i] + b[i];
            }
        }
    };
}
```

## Advanced Branching Patterns

### Version-Based Branching

Conditional compilation based on language and library versions:

```cpp
#include <xieite/pp/ver.hpp>
#include <xieite/pp/if.hpp>

namespace version_branching {
    template<typename T>
    class modern_container {
    public:
        // Use C++20 features when available
        XIEITE_PP_IF(__cplusplus >= 202002L)(
            template<typename... Args>
            requires std::constructible_from<T, Args...>
            void emplace_back(Args&&... args) {
                data_.emplace_back(std::forward<Args>(args)...);
            }

            auto begin() const noexcept requires std::ranges::range<std::vector<T>> {
                return data_.begin();
            }

            auto end() const noexcept requires std::ranges::range<std::vector<T>> {
                return data_.end();
            }
        )

        // Fallback for C++17
        XIEITE_PP_IF(__cplusplus < 202002L)(
            template<typename... Args>
            void emplace_back(Args&&... args) {
                static_assert(std::is_constructible_v<T, Args...>, "T must be constructible from Args...");
                data_.emplace_back(std::forward<Args>(args)...);
            }

            typename std::vector<T>::const_iterator begin() const noexcept {
                return data_.begin();
            }

            typename std::vector<T>::const_iterator end() const noexcept {
                return data_.end();
            }
        )

        // Modern format support
        XIEITE_PP_IF(__cplusplus >= 202002L && __has_include(<format>))(
            std::string to_string() const {
                std::string result = "[";
                bool first = true;
                for (const auto& item : data_) {
                    if (!first) result += ", ";
                    if constexpr (requires { std::format("{}", item); }) {
                        result += std::format("{}", item);
                    } else {
                        result += "item";
                    }
                    first = false;
                }
                result += "]";
                return result;
            }
        )

        // Fallback string conversion
        XIEITE_PP_IF(__cplusplus < 202002L || !__has_include(<format>))(
            std::string to_string() const {
                std::ostringstream oss;
                oss << "[";
                bool first = true;
                for (const auto& item : data_) {
                    if (!first) oss << ", ";
                    oss << item;
                    first = false;
                }
                oss << "]";
                return oss.str();
            }
        )

    private:
        std::vector<T> data_;
    };
}
```

### Runtime Configuration Branching

Combining compile-time and runtime branching:

```cpp
#include <xieite/pp/platform.hpp>
#include <xieite/pp/if.hpp>

namespace hybrid_branching {
    enum class optimization_level {
        none,
        basic,
        aggressive
    };

    template<typename T>
    class configurable_processor {
    public:
        explicit configurable_processor(optimization_level level) : opt_level_(level) {}

        void process(std::vector<T>& data) {
            // Compile-time platform selection with runtime optimization level
            XIEITE_PP_IF(XIEITE_PLATFORM_WINDOWS)(
                process_windows(data);
            )
            XIEITE_PP_IF(XIEITE_PLATFORM_UNIX)(
                process_unix(data);
            )
            XIEITE_PP_IF(!XIEITE_PLATFORM_WINDOWS && !XIEITE_PLATFORM_UNIX)(
                process_generic(data);
            )
        }

    private:
        optimization_level opt_level_;

        XIEITE_PP_IF(XIEITE_PLATFORM_WINDOWS)(
            void process_windows(std::vector<T>& data) {
                switch (opt_level_) {
                    case optimization_level::none:
                        process_windows_basic(data);
                        break;
                    case optimization_level::basic:
                        process_windows_optimized(data);
                        break;
                    case optimization_level::aggressive:
                        process_windows_aggressive(data);
                        break;
                }
            }

            void process_windows_basic(std::vector<T>& data) {
                // Basic Windows implementation
                for (auto& item : data) {
                    item = process_item_basic(item);
                }
            }

            void process_windows_optimized(std::vector<T>& data) {
                // Optimized Windows implementation
                std::for_each(std::execution::par_unseq, data.begin(), data.end(),
                    [this](T& item) { item = process_item_optimized(item); });
            }

            void process_windows_aggressive(std::vector<T>& data) {
                // Aggressive Windows implementation with platform-specific optimizations
                // Could use Windows-specific APIs for maximum performance
                process_windows_optimized(data);
            }
        )

        XIEITE_PP_IF(XIEITE_PLATFORM_UNIX)(
            void process_unix(std::vector<T>& data) {
                switch (opt_level_) {
                    case optimization_level::none:
                        process_unix_basic(data);
                        break;
                    case optimization_level::basic:
                        process_unix_optimized(data);
                        break;
                    case optimization_level::aggressive:
                        process_unix_aggressive(data);
                        break;
                }
            }

            void process_unix_basic(std::vector<T>& data) {
                // Basic Unix implementation
                for (auto& item : data) {
                    item = process_item_basic(item);
                }
            }

            void process_unix_optimized(std::vector<T>& data) {
                // Optimized Unix implementation
                std::for_each(std::execution::par_unseq, data.begin(), data.end(),
                    [this](T& item) { item = process_item_optimized(item); });
            }

            void process_unix_aggressive(std::vector<T>& data) {
                // Aggressive Unix implementation
                process_unix_optimized(data);
            }
        )

        void process_generic(std::vector<T>& data) {
            // Generic fallback implementation
            for (auto& item : data) {
                item = process_item_basic(item);
            }
        }

        T process_item_basic(const T& item) {
            return item; // Placeholder
        }

        T process_item_optimized(const T& item) {
            return item; // Placeholder
        }
    };
}
```

## Macro-Based Branching Utilities

### Custom Branching Macros

Creating specialized branching macros for complex conditions:

```cpp
#include <xieite/pp/if.hpp>
#include <xieite/pp/platform.hpp>
#include <xieite/pp/arch.hpp>
#include <xieite/pp/eval.hpp>

// Complex condition evaluation macro
#define XIEITE_IF_WINDOWS_X64(code) \
    XIEITE_PP_IF(XIEITE_PLATFORM_WINDOWS && XIEITE_ARCH_X86_64)(code)

#define XIEITE_IF_UNIX_ARM(code) \
    XIEITE_PP_IF(XIEITE_PLATFORM_UNIX && (XIEITE_ARCH_ARM32 || XIEITE_ARCH_ARM64))(code)

#define XIEITE_IF_MOBILE_PLATFORM(code) \
    XIEITE_PP_IF(XIEITE_PLATFORM_ANDROID || XIEITE_PLATFORM_IOS)(code)

// Conditional definition macro
#define XIEITE_DEFINE_IF(condition, name, definition) \
    XIEITE_PP_IF(condition)( \
        definition \
    )

// Multi-platform function definition
#define XIEITE_MULTIPLATFORM_FUNC(name, return_type, params, win_impl, unix_impl, generic_impl) \
    return_type name params { \
        XIEITE_PP_IF(XIEITE_PLATFORM_WINDOWS)( \
            win_impl \
        ) \
        XIEITE_PP_IF(XIEITE_PLATFORM_UNIX)( \
            unix_impl \
        ) \
        XIEITE_PP_IF(!XIEITE_PLATFORM_WINDOWS && !XIEITE_PLATFORM_UNIX)( \
            generic_impl \
        ) \
    }

// Usage examples
class platform_specific_operations {
public:
    // Conditional member functions
    XIEITE_IF_WINDOWS_X64(
        static void windows_x64_optimization() {
            // Windows x64 specific code
        }
    )

    XIEITE_IF_UNIX_ARM(
        static void unix_arm_optimization() {
            // Unix ARM specific code
        }
    )

    // Multi-platform function using macro
    XIEITE_MULTIPLATFORM_FUNC(
        get_cpu_count,
        int,
        (),
        return std::thread::hardware_concurrency();,  // Windows
        return sysconf(_SC_NPROCESSORS_ONLN);,        // Unix
        return 1;                                     // Generic
    )
};
```

### Nested Branching Macros

Creating macros for deeply nested conditional compilation:

```cpp
#include <xieite/pp/if.hpp>
#include <xieite/pp/platform.hpp>
#include <xieite/pp/compiler.hpp>

// Nested branching for compiler and platform combinations
#define XIEITE_COMPILER_PLATFORM_BRANCH(gcc_win, gcc_unix, clang_win, clang_unix, msvc_win, generic) \
    XIEITE_PP_IF(XIEITE_COMPILER_GCC)( \
        XIEITE_PP_IF(XIEITE_PLATFORM_WINDOWS)( \
            gcc_win \
        ) \
        XIEITE_PP_IF(XIEITE_PLATFORM_UNIX)( \
            gcc_unix \
        ) \
    ) \
    XIEITE_PP_IF(XIEITE_COMPILER_CLANG)( \
        XIEITE_PP_IF(XIEITE_PLATFORM_WINDOWS)( \
            clang_win \
        ) \
        XIEITE_PP_IF(XIEITE_PLATFORM_UNIX)( \
            clang_unix \
        ) \
    ) \
    XIEITE_PP_IF(XIEITE_COMPILER_MSVC)( \
        XIEITE_PP_IF(XIEITE_PLATFORM_WINDOWS)( \
            msvc_win \
        ) \
    ) \
    XIEITE_PP_IF(!( \
        (XIEITE_COMPILER_GCC && (XIEITE_PLATFORM_WINDOWS || XIEITE_PLATFORM_UNIX)) || \
        (XIEITE_COMPILER_CLANG && (XIEITE_PLATFORM_WINDOWS || XIEITE_PLATFORM_UNIX)) || \
        (XIEITE_COMPILER_MSVC && XIEITE_PLATFORM_WINDOWS) \
    ))( \
        generic \
    )

// Usage example
class optimized_allocator {
public:
    static void* allocate_aligned(std::size_t size, std::size_t alignment) {
        XIEITE_COMPILER_PLATFORM_BRANCH(
            // GCC + Windows
            return _aligned_malloc(size, alignment);,

            // GCC + Unix
            void* ptr; \
            if (posix_memalign(&ptr, alignment, size) != 0) return nullptr; \
            return ptr;,

            // Clang + Windows
            return _aligned_malloc(size, alignment);,

            // Clang + Unix
            void* ptr; \
            if (posix_memalign(&ptr, alignment, size) != 0) return nullptr; \
            return ptr;,

            // MSVC + Windows
            return _aligned_malloc(size, alignment);,

            // Generic fallback
            return std::aligned_alloc(alignment, size);
        )
    }
};
```

## Testing Platform Branches

### Comprehensive Branch Testing

Testing all platform branches systematically:

```cpp
#include <xieite/pp/platform.hpp>
#include <xieite/pp/if.hpp>

namespace branch_testing {
    class platform_branch_tester {
    public:
        static void test_all_branches() {
            test_platform_detection();
            test_conditional_compilation();
            test_feature_detection();
        }

    private:
        static void test_platform_detection() {
            // Test that exactly one platform is detected
            int platform_count = 0;

            XIEITE_PP_IF(XIEITE_PLATFORM_WINDOWS)(
                ++platform_count;
                assert(get_platform_name() == "Windows");
            )

            XIEITE_PP_IF(XIEITE_PLATFORM_UNIX)(
                ++platform_count;
                assert(get_platform_name() == "Unix");
            )

            XIEITE_PP_IF(XIEITE_PLATFORM_MACOS)(
                ++platform_count;
                assert(get_platform_name() == "macOS");
            )

            assert(platform_count >= 1); // At least one platform should be detected
        }

        static void test_conditional_compilation() {
            // Test that platform-specific code compiles correctly
            platform_optimized_container<int> container;
            container.insert(42);

            // This should compile and work on all platforms
            assert(!container.empty());
        }

        static void test_feature_detection() {
            // Test feature-based branching
            feature_detection::feature_optimized_math<float> math;

            std::vector<float> a = {1.0f, 2.0f, 3.0f, 4.0f};
            std::vector<float> b = {1.0f, 1.0f, 1.0f, 1.0f};
            std::vector<float> result(4);

            math.vector_add(a.data(), b.data(), result.data(), 4);

            // Verify results regardless of implementation path
            for (std::size_t i = 0; i < 4; ++i) {
                assert(std::abs(result[i] - (a[i] + b[i])) < 1e-6f);
            }
        }

        static std::string get_platform_name() {
            XIEITE_PP_IF(XIEITE_PLATFORM_WINDOWS)(
                return "Windows";
            )
            XIEITE_PP_IF(XIEITE_PLATFORM_UNIX && !XIEITE_PLATFORM_MACOS)(
                return "Unix";
            )
            XIEITE_PP_IF(XIEITE_PLATFORM_MACOS)(
                return "macOS";
            )
            return "Unknown";
        }
    };
}
```

## Best Practices

### Branching Guidelines

1. **Minimize Complexity**: Keep branching logic as simple as possible
2. **Test All Paths**: Ensure every branch is tested on appropriate platforms
3. **Document Conditions**: Clearly document why each branch exists
4. **Provide Fallbacks**: Always include generic fallback implementations
5. **Use Feature Detection**: Prefer feature-based over platform-based branching when possible
6. **Avoid Deep Nesting**: Limit the depth of nested conditional compilation
7. **Consistent Naming**: Use consistent naming patterns for platform-specific functions

### Common Anti-Patterns

1. **Over-Branching**: Creating too many platform-specific code paths
2. **Missing Fallbacks**: Not providing generic implementations
3. **Untested Branches**: Having conditional code that's never tested
4. **Hard-Coded Assumptions**: Making assumptions about platform capabilities
5. **Inconsistent Interfaces**: Platform-specific functions with different signatures

### Debugging Branching Issues

1. **Preprocessor Output**: Use compiler flags to see preprocessor output
2. **Conditional Logging**: Add platform-specific debug output
3. **Static Assertions**: Use static assertions to verify branch conditions
4. **Build Matrix**: Test all platform/compiler combinations
5. **Documentation**: Maintain clear documentation of supported configurations

This comprehensive approach to platform branching ensures robust, maintainable code that works efficiently across all target platforms while remaining readable and testable.