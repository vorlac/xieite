# Cross-Platform Development

This document covers cross-platform development strategies using XIEITE, including platform detection, conditional compilation, and portable code patterns that work across different operating systems and architectures.

## Platform Detection

### Operating System Detection

XIEITE provides comprehensive platform detection macros:

```cpp
#include <xieite/pp/platform.hpp>
#include <xieite/pp/if.hpp>

// Platform-specific code organization
namespace platform {
    XIEITE_PP_IF(XIEITE_PLATFORM_WINDOWS)(
        namespace windows {
            void platform_specific_function() {
                // Windows-specific implementation
            }
        }
    )

    XIEITE_PP_IF(XIEITE_PLATFORM_UNIX)(
        namespace unix_like {
            void platform_specific_function() {
                // Unix/Linux-specific implementation
            }
        }
    )

    XIEITE_PP_IF(XIEITE_PLATFORM_MACOS)(
        namespace macos {
            void platform_specific_function() {
                // macOS-specific implementation
            }
        }
    )

    // Unified interface
    void cross_platform_function() {
        XIEITE_PP_IF(XIEITE_PLATFORM_WINDOWS)(
            windows::platform_specific_function();
        )
        XIEITE_PP_IF(XIEITE_PLATFORM_UNIX && !XIEITE_PLATFORM_MACOS)(
            unix_like::platform_specific_function();
        )
        XIEITE_PP_IF(XIEITE_PLATFORM_MACOS)(
            macos::platform_specific_function();
        )
    }
}
```

### Architecture Detection

Handling different CPU architectures:

```cpp
#include <xieite/pp/arch.hpp>
#include <xieite/pp/if.hpp>
#include <xieite/trait/is_arith.hpp>

template<xieite::is_arith T>
class optimized_math {
public:
    static T fast_multiply(T a, T b) {
        XIEITE_PP_IF(XIEITE_ARCH_X86_64)(
            return x86_64_multiply(a, b);
        )
        XIEITE_PP_IF(XIEITE_ARCH_ARM64)(
            return arm64_multiply(a, b);
        )
        XIEITE_PP_IF(XIEITE_ARCH_ARM32)(
            return arm32_multiply(a, b);
        )
        // Fallback for other architectures
        return generic_multiply(a, b);
    }

private:
    XIEITE_PP_IF(XIEITE_ARCH_X86_64)(
        static T x86_64_multiply(T a, T b) {
            // x86-64 specific optimizations
            return a * b;
        }
    )

    XIEITE_PP_IF(XIEITE_ARCH_ARM64)(
        static T arm64_multiply(T a, T b) {
            // ARM64 specific optimizations
            return a * b;
        }
    )

    XIEITE_PP_IF(XIEITE_ARCH_ARM32)(
        static T arm32_multiply(T a, T b) {
            // ARM32 specific optimizations
            return a * b;
        }
    )

    static T generic_multiply(T a, T b) {
        return a * b;
    }
};
```

## Compiler Compatibility

### Compiler-Specific Features

Handling different compiler capabilities:

```cpp
#include <xieite/pp/compiler.hpp>
#include <xieite/pp/if.hpp>
#include <xieite/pp/attr.hpp>

// Compiler-specific attribute handling
#define XIEITE_FORCE_INLINE \
    XIEITE_PP_IF(XIEITE_COMPILER_GCC)(__attribute__((always_inline))) \
    XIEITE_PP_IF(XIEITE_COMPILER_CLANG)(__attribute__((always_inline))) \
    XIEITE_PP_IF(XIEITE_COMPILER_MSVC)(__forceinline)

// Cross-compiler function attributes
template<typename T>
XIEITE_FORCE_INLINE constexpr T cross_platform_abs(T value) noexcept {
    XIEITE_PP_IF(XIEITE_COMPILER_GCC)(
        return __builtin_abs(value);
    )
    XIEITE_PP_IF(XIEITE_COMPILER_CLANG)(
        return __builtin_abs(value);
    )
    // Fallback implementation
    return value < T{} ? -value : value;
}

// Compiler-specific optimizations
template<typename T>
class compiler_optimized {
public:
    XIEITE_PP_IF(XIEITE_COMPILER_GCC)(
        __attribute__((hot))
    )
    XIEITE_PP_IF(XIEITE_COMPILER_CLANG)(
        __attribute__((hot))
    )
    static T optimized_function(T value) {
        // Hot path optimization hints
        return value * value + value;
    }

    XIEITE_PP_IF(XIEITE_COMPILER_MSVC)(
        __declspec(noinline)
    )
    XIEITE_PP_IF(XIEITE_COMPILER_GCC)(
        __attribute__((noinline))
    )
    static T debug_function(T value) {
        // Prevent inlining for debugging
        return value + 1;
    }
};
```

### Standard Library Compatibility

Handling different standard library implementations:

```cpp
#include <xieite/pp/stdlib.hpp>
#include <xieite/pp/if.hpp>

// Handle different standard library implementations
namespace xieite_compat {
    template<typename T>
    bool is_finite_impl(T value) {
        XIEITE_PP_IF(XIEITE_STDLIB_LIBSTDCXX)(
            return std::isfinite(value);
        )
        XIEITE_PP_IF(XIEITE_STDLIB_LIBC)(
            return std::isfinite(value);
        )
        XIEITE_PP_IF(XIEITE_STDLIB_MSVC)(
            return _finite(value) != 0;
        )
        // Fallback implementation
        return value == value && value != std::numeric_limits<T>::infinity() && value != -std::numeric_limits<T>::infinity();
    }

    // String formatting compatibility
    template<typename... Args>
    std::string format_string(const std::string& format, Args&&... args) {
        XIEITE_PP_IF(XIEITE_STDLIB_LIBSTDCXX && __cplusplus >= 202002L)(
            return std::format(format, std::forward<Args>(args)...);
        )
        XIEITE_PP_IF(XIEITE_STDLIB_MSVC && _MSVC_LANG >= 202002L)(
            return std::format(format, std::forward<Args>(args)...);
        )
        // Fallback using stringstream
        std::ostringstream oss;
        format_fallback(oss, format, std::forward<Args>(args)...);
        return oss.str();
    }
}
```

## File System Abstraction

### Path Handling

Cross-platform path manipulation:

```cpp
#include <xieite/pp/platform.hpp>
#include <xieite/pp/if.hpp>
#include <string>
#include <filesystem>

namespace xieite_fs {
    class portable_path {
        std::filesystem::path path_;

    public:
        explicit portable_path(const std::string& path) : path_(path) {
            normalize();
        }

        std::string string() const {
            XIEITE_PP_IF(XIEITE_PLATFORM_WINDOWS)(
                return path_.string();
            )
            XIEITE_PP_IF(!XIEITE_PLATFORM_WINDOWS)(
                return path_.generic_string();
            )
        }

        std::string native_string() const {
            return path_.string();
        }

        portable_path operator/(const std::string& component) const {
            return portable_path((path_ / component).string());
        }

        bool exists() const {
            return std::filesystem::exists(path_);
        }

        bool is_directory() const {
            return std::filesystem::is_directory(path_);
        }

    private:
        void normalize() {
            XIEITE_PP_IF(XIEITE_PLATFORM_WINDOWS)(
                // Windows-specific normalization
                path_ = path_.lexically_normal();
            )
            XIEITE_PP_IF(!XIEITE_PLATFORM_WINDOWS)(
                // Unix-like normalization
                path_ = path_.lexically_normal();
            )
        }
    };

    // Cross-platform directory operations
    class directory_utils {
    public:
        static std::vector<portable_path> list_directory(const portable_path& dir) {
            std::vector<portable_path> result;

            try {
                for (const auto& entry : std::filesystem::directory_iterator(dir.native_string())) {
                    result.emplace_back(entry.path().string());
                }
            } catch (const std::filesystem::filesystem_error&) {
                // Handle errors gracefully
            }

            return result;
        }

        static bool create_directory(const portable_path& dir) {
            try {
                return std::filesystem::create_directories(dir.native_string());
            } catch (const std::filesystem::filesystem_error&) {
                return false;
            }
        }

        static portable_path get_temp_directory() {
            XIEITE_PP_IF(XIEITE_PLATFORM_WINDOWS)(
                char* temp_path = nullptr;
                size_t len = 0;
                if (_dupenv_s(&temp_path, &len, "TEMP") == 0 && temp_path) {
                    std::string result(temp_path);
                    free(temp_path);
                    return portable_path(result);
                }
                return portable_path("C:\\temp");
            )
            XIEITE_PP_IF(!XIEITE_PLATFORM_WINDOWS)(
                const char* temp_path = std::getenv("TMPDIR");
                if (!temp_path) temp_path = std::getenv("TMP");
                if (!temp_path) temp_path = "/tmp";
                return portable_path(temp_path);
            )
        }
    };
}
```

## Memory Management

### Platform-Specific Allocation

Handling different memory allocation strategies:

```cpp
#include <xieite/pp/platform.hpp>
#include <xieite/pp/if.hpp>
#include <xieite/trait/is_arith.hpp>

namespace xieite_memory {
    template<typename T>
    class aligned_allocator {
    public:
        using value_type = T;
        static constexpr std::size_t alignment = alignof(T);

        T* allocate(std::size_t n) {
            std::size_t size = n * sizeof(T);

            XIEITE_PP_IF(XIEITE_PLATFORM_WINDOWS)(
                void* ptr = _aligned_malloc(size, alignment);
                if (!ptr) throw std::bad_alloc{};
                return static_cast<T*>(ptr);
            )
            XIEITE_PP_IF(XIEITE_PLATFORM_UNIX)(
                void* ptr = nullptr;
                if (posix_memalign(&ptr, alignment, size) != 0) {
                    throw std::bad_alloc{};
                }
                return static_cast<T*>(ptr);
            )
            // Fallback
            return static_cast<T*>(std::aligned_alloc(alignment, size));
        }

        void deallocate(T* ptr, std::size_t) noexcept {
            XIEITE_PP_IF(XIEITE_PLATFORM_WINDOWS)(
                _aligned_free(ptr);
            )
            XIEITE_PP_IF(!XIEITE_PLATFORM_WINDOWS)(
                std::free(ptr);
            )
        }
    };
}
```

## Threading and Concurrency

### Platform-Specific Threading

Cross-platform threading utilities:

```cpp
#include <xieite/pp/platform.hpp>
#include <xieite/pp/if.hpp>
#include <thread>
#include <mutex>

namespace xieite_threading {
    // Platform-specific thread priorities
    enum class thread_priority {
        low,
        normal,
        high,
        realtime
    };

    class thread_utils {
    public:
        static void set_thread_priority(std::thread& thread, thread_priority priority) {
            XIEITE_PP_IF(XIEITE_PLATFORM_WINDOWS)(
                set_priority_windows(thread.native_handle(), priority);
            )
            XIEITE_PP_IF(XIEITE_PLATFORM_UNIX)(
                set_priority_unix(thread.native_handle(), priority);
            )
        }

        static void set_thread_affinity(std::thread& thread, std::size_t cpu_mask) {
            XIEITE_PP_IF(XIEITE_PLATFORM_WINDOWS)(
                SetThreadAffinityMask(thread.native_handle(), static_cast<DWORD_PTR>(cpu_mask));
            )
            XIEITE_PP_IF(XIEITE_PLATFORM_UNIX)(
                cpu_set_t cpuset;
                CPU_ZERO(&cpuset);
                for (std::size_t i = 0; i < sizeof(cpu_mask) * 8; ++i) {
                    if (cpu_mask & (1ULL << i)) {
                        CPU_SET(i, &cpuset);
                    }
                }
                pthread_setaffinity_np(thread.native_handle(), sizeof(cpuset), &cpuset);
            )
        }

    private:
        XIEITE_PP_IF(XIEITE_PLATFORM_WINDOWS)(
            static void set_priority_windows(std::thread::native_handle_type handle, thread_priority priority) {
                int win_priority;
                switch (priority) {
                    case thread_priority::low: win_priority = THREAD_PRIORITY_BELOW_NORMAL; break;
                    case thread_priority::normal: win_priority = THREAD_PRIORITY_NORMAL; break;
                    case thread_priority::high: win_priority = THREAD_PRIORITY_ABOVE_NORMAL; break;
                    case thread_priority::realtime: win_priority = THREAD_PRIORITY_TIME_CRITICAL; break;
                }
                SetThreadPriority(handle, win_priority);
            }
        )

        XIEITE_PP_IF(XIEITE_PLATFORM_UNIX)(
            static void set_priority_unix(std::thread::native_handle_type handle, thread_priority priority) {
                int policy;
                struct sched_param param;
                pthread_getschedparam(handle, &policy, &param);

                switch (priority) {
                    case thread_priority::low:
                        param.sched_priority = sched_get_priority_min(SCHED_OTHER);
                        policy = SCHED_OTHER;
                        break;
                    case thread_priority::normal:
                        param.sched_priority = 0;
                        policy = SCHED_OTHER;
                        break;
                    case thread_priority::high:
                        param.sched_priority = sched_get_priority_max(SCHED_OTHER);
                        policy = SCHED_OTHER;
                        break;
                    case thread_priority::realtime:
                        param.sched_priority = sched_get_priority_max(SCHED_FIFO);
                        policy = SCHED_FIFO;
                        break;
                }

                pthread_setschedparam(handle, policy, &param);
            }
        )
    };
}
```

## Build System Integration

### CMake Integration

Cross-platform build configuration:

```cmake
# Platform detection in CMake
if(WIN32)
    target_compile_definitions(myproject PRIVATE XIEITE_PLATFORM_WINDOWS=1)
elseif(APPLE)
    target_compile_definitions(myproject PRIVATE XIEITE_PLATFORM_MACOS=1)
elseif(UNIX)
    target_compile_definitions(myproject PRIVATE XIEITE_PLATFORM_UNIX=1)
endif()

# Architecture detection
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
    target_compile_definitions(myproject PRIVATE XIEITE_ARCH_X86_64=1)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64")
    target_compile_definitions(myproject PRIVATE XIEITE_ARCH_ARM64=1)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
    target_compile_definitions(myproject PRIVATE XIEITE_ARCH_ARM32=1)
endif()

# Compiler-specific flags
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_definitions(myproject PRIVATE XIEITE_COMPILER_GCC=1)
    target_compile_options(myproject PRIVATE -Wall -Wextra)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_definitions(myproject PRIVATE XIEITE_COMPILER_CLANG=1)
    target_compile_options(myproject PRIVATE -Wall -Wextra)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_definitions(myproject PRIVATE XIEITE_COMPILER_MSVC=1)
    target_compile_options(myproject PRIVATE /W4)
endif()
```

## Testing Across Platforms

### Cross-Platform Testing Framework

Ensuring code works across all target platforms:

```cpp
#include <xieite/pp/platform.hpp>
#include <xieite/pp/if.hpp>
#include <xieite/trait/is_arith.hpp>

namespace xieite_testing {
    class platform_test_suite {
    public:
        static void run_all_tests() {
            test_platform_detection();
            test_arithmetic_operations();
            test_file_operations();
            test_threading();
        }

    private:
        static void test_platform_detection() {
            XIEITE_PP_IF(XIEITE_PLATFORM_WINDOWS)(
                assert(get_platform_name() == "Windows");
            )
            XIEITE_PP_IF(XIEITE_PLATFORM_UNIX && !XIEITE_PLATFORM_MACOS)(
                assert(get_platform_name() == "Unix");
            )
            XIEITE_PP_IF(XIEITE_PLATFORM_MACOS)(
                assert(get_platform_name() == "macOS");
            )
        }

        static void test_arithmetic_operations() {
            // Test arithmetic operations across platforms
            auto result = optimized_math<double>::fast_multiply(3.14, 2.0);
            assert(std::abs(result - 6.28) < 1e-10);
        }

        static void test_file_operations() {
            // Test file operations across platforms
            auto temp_dir = xieite_fs::directory_utils::get_temp_directory();
            assert(!temp_dir.string().empty());
        }

        static void test_threading() {
            // Test threading operations across platforms
            std::thread test_thread([]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            });

            xieite_threading::thread_utils::set_thread_priority(test_thread, xieite_threading::thread_priority::normal);
            test_thread.join();
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

### Cross-Platform Guidelines

1. **Use XIEITE Macros**: Leverage XIEITE's platform detection macros for conditional compilation
2. **Abstract Platform Differences**: Create unified interfaces that hide platform-specific details
3. **Test on All Targets**: Ensure code works on all intended platforms and architectures
4. **Handle Endianness**: Use XIEITE's endianness detection for binary data operations
5. **Portable Path Handling**: Use XIEITE's path utilities for cross-platform file operations
6. **Compiler Compatibility**: Use XIEITE's compiler detection for feature-specific code
7. **Standard Library Variations**: Account for differences in standard library implementations

### Common Pitfalls

1. **Hardcoded Paths**: Avoid platform-specific path separators and conventions
2. **Compiler Extensions**: Don't rely on compiler-specific extensions without fallbacks
3. **Endianness Assumptions**: Always check byte order for binary operations
4. **Threading Differences**: Account for platform-specific threading capabilities
5. **Memory Alignment**: Consider different alignment requirements across architectures

This comprehensive cross-platform approach ensures XIEITE-based applications work seamlessly across different environments while maintaining optimal performance and functionality.