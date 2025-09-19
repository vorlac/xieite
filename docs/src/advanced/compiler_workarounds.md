# Compiler Workarounds

This document covers compiler-specific workarounds and compatibility strategies when using XIEITE, addressing common compiler bugs, limitations, and differences in C++20 support across different toolchains.

## Compiler Detection and Handling

### Comprehensive Compiler Detection

XIEITE provides detailed compiler detection capabilities:

```cpp
#include <xieite/pp/compiler.hpp>
#include <xieite/pp/if.hpp>
#include <xieite/pp/ver.hpp>

namespace compiler_detection {
    // Detailed compiler information
    struct compiler_info {
        const char* name;
        int major_version;
        int minor_version;
        bool supports_concepts;
        bool supports_modules;
        bool has_reliable_constexpr;
    };

    constexpr compiler_info get_compiler_info() {
        XIEITE_PP_IF(XIEITE_COMPILER_GCC)(
            return {
                "GCC",
                __GNUC__,
                __GNUC_MINOR__,
                __GNUC__ >= 10,     // Concepts support
                __GNUC__ >= 11,     // Modules support
                __GNUC__ >= 9       // Reliable constexpr
            };
        )
        XIEITE_PP_IF(XIEITE_COMPILER_CLANG)(
            return {
                "Clang",
                __clang_major__,
                __clang_minor__,
                __clang_major__ >= 10,  // Concepts support
                __clang_major__ >= 12,  // Modules support (experimental)
                __clang_major__ >= 9    // Reliable constexpr
            };
        )
        XIEITE_PP_IF(XIEITE_COMPILER_MSVC)(
            return {
                "MSVC",
                _MSC_VER / 100,
                (_MSC_VER / 10) % 10,
                _MSC_VER >= 1929,   // Concepts support (VS 2019 16.10+)
                false,              // Limited modules support
                _MSC_VER >= 1920    // Reliable constexpr
            };
        )
        // Unknown compiler
        return {"Unknown", 0, 0, false, false, false};
    }
}
```

## Template Metaprogramming Workarounds

### SFINAE vs Concepts Compatibility

Handling differences in template constraint mechanisms:

```cpp
#include <xieite/pp/compiler.hpp>
#include <xieite/pp/if.hpp>
#include <xieite/trait/is_arith.hpp>

namespace template_workarounds {
    // Compiler-specific template constraint handling
    template<typename T>
    class arithmetic_operations {
    public:
        // Modern approach with concepts (GCC 10+, Clang 10+, MSVC 2019 16.10+)
        XIEITE_PP_IF(XIEITE_COMPILER_GCC && __GNUC__ >= 10)(
            template<xieite::is_arith U = T>
            requires std::same_as<U, T>
            constexpr auto modern_add(U a, U b) -> U {
                return a + b;
            }
        )

        XIEITE_PP_IF(XIEITE_COMPILER_CLANG && __clang_major__ >= 10)(
            template<xieite::is_arith U = T>
            requires std::same_as<U, T>
            constexpr auto modern_add(U a, U b) -> U {
                return a + b;
            }
        )

        XIEITE_PP_IF(XIEITE_COMPILER_MSVC && _MSC_VER >= 1929)(
            template<xieite::is_arith U = T>
            requires std::same_as<U, T>
            constexpr auto modern_add(U a, U b) -> U {
                return a + b;
            }
        )

        // Fallback SFINAE approach for older compilers
        XIEITE_PP_IF(
            (XIEITE_COMPILER_GCC && __GNUC__ < 10) ||
            (XIEITE_COMPILER_CLANG && __clang_major__ < 10) ||
            (XIEITE_COMPILER_MSVC && _MSC_VER < 1929)
        )(
            template<typename U = T>
            constexpr auto modern_add(U a, U b)
                -> std::enable_if_t<xieite::is_arith<U> && std::is_same_v<U, T>, U> {
                return a + b;
            }
        )

        // Universal interface that works on all compilers
        constexpr T add(T a, T b) {
            static_assert(xieite::is_arith<T>, "T must be arithmetic");
            return modern_add(a, b);
        }
    };
}
```

### Constexpr Evaluation Workarounds

Handling differences in constexpr evaluation:

```cpp
#include <xieite/pp/compiler.hpp>
#include <xieite/pp/if.hpp>

namespace constexpr_workarounds {
    // MSVC has issues with certain constexpr patterns
    template<std::size_t N>
    constexpr auto fibonacci() {
        XIEITE_PP_IF(XIEITE_COMPILER_MSVC && _MSC_VER < 1925)(
            // Workaround for older MSVC constexpr limitations
            if constexpr (N <= 1) {
                return N;
            } else {
                // Use iterative approach instead of recursive for MSVC
                std::size_t a = 0, b = 1;
                for (std::size_t i = 2; i <= N; ++i) {
                    std::size_t temp = a + b;
                    a = b;
                    b = temp;
                }
                return b;
            }
        )
        XIEITE_PP_IF(!XIEITE_COMPILER_MSVC || _MSC_VER >= 1925)(
            // Standard recursive approach for other compilers
            if constexpr (N <= 1) {
                return N;
            } else {
                return fibonacci<N-1>() + fibonacci<N-2>();
            }
        )
    }

    // Template recursion depth workarounds
    template<std::size_t N, std::size_t Limit = 500>
    struct safe_factorial {
        static_assert(N <= Limit, "Factorial too large for template recursion");

        XIEITE_PP_IF(XIEITE_COMPILER_MSVC)(
            // MSVC has lower default template recursion limits
            static constexpr std::size_t value = N <= 1 ? 1 : N * safe_factorial<N-1, Limit>::value;
        )
        XIEITE_PP_IF(!XIEITE_COMPILER_MSVC)(
            // GCC and Clang can handle deeper recursion
            static constexpr std::size_t value = N <= 1 ? 1 : N * safe_factorial<N-1, 1000>::value;
        )
    };
}
```

## Language Feature Workarounds

### Aggregate Initialization Issues

Handling compiler differences in aggregate initialization:

```cpp
#include <xieite/pp/compiler.hpp>
#include <xieite/pp/if.hpp>

namespace aggregate_workarounds {
    template<typename T, std::size_t N>
    struct fixed_array {
        T data[N];

        // MSVC and older GCC have issues with certain initialization patterns
        XIEITE_PP_IF(XIEITE_COMPILER_MSVC || (XIEITE_COMPILER_GCC && __GNUC__ < 9))(
            // Explicit constructor workaround
            template<typename... Args>
            constexpr fixed_array(Args&&... args) : data{static_cast<T>(args)...} {
                static_assert(sizeof...(args) <= N, "Too many initializers");
            }

            constexpr fixed_array() : data{} {}
        )

        XIEITE_PP_IF(!XIEITE_COMPILER_MSVC && !(XIEITE_COMPILER_GCC && __GNUC__ < 9))(
            // Standard aggregate initialization for modern compilers
            constexpr fixed_array() = default;
        )

        constexpr T& operator[](std::size_t index) noexcept {
            return data[index];
        }

        constexpr const T& operator[](std::size_t index) const noexcept {
            return data[index];
        }

        constexpr std::size_t size() const noexcept {
            return N;
        }
    };
}
```

### Lambda and Capture Workarounds

Handling compiler-specific lambda issues:

```cpp
#include <xieite/pp/compiler.hpp>
#include <xieite/pp/if.hpp>

namespace lambda_workarounds {
    template<typename T>
    class lambda_helper {
    public:
        // MSVC has issues with certain lambda capture patterns
        auto create_processor() {
            XIEITE_PP_IF(XIEITE_COMPILER_MSVC)(
                // Explicit capture workaround for MSVC
                return [this](const T& value) -> T {
                    return this->process_value(value);
                };
            )
            XIEITE_PP_IF(!XIEITE_COMPILER_MSVC)(
                // Standard capture for other compilers
                return [*this](const T& value) -> T {
                    return process_value(value);
                };
            )
        }

        // Template lambda workarounds
        auto create_generic_processor() {
            XIEITE_PP_IF(XIEITE_COMPILER_GCC && __GNUC__ < 9)(
                // Workaround for older GCC template lambda issues
                struct processor {
                    const lambda_helper* helper;

                    template<typename U>
                    auto operator()(const U& value) const -> U {
                        return helper->template process_generic<U>(value);
                    }
                };
                return processor{this};
            )
            XIEITE_PP_IF(!XIEITE_COMPILER_GCC || __GNUC__ >= 9)(
                // Standard template lambda
                return [this]<typename U>(const U& value) -> U {
                    return process_generic<U>(value);
                };
            )
        }

    private:
        T process_value(const T& value) const {
            return value; // Placeholder
        }

        template<typename U>
        U process_generic(const U& value) const {
            return value; // Placeholder
        }
    };
}
```

## Standard Library Workarounds

### Missing or Incomplete STL Features

Providing compatibility shims for missing features:

```cpp
#include <xieite/pp/compiler.hpp>
#include <xieite/pp/if.hpp>
#include <xieite/pp/stdlib.hpp>

namespace stdlib_workarounds {
    // std::format availability varies
    template<typename... Args>
    std::string format_string(const std::string& fmt, Args&&... args) {
        XIEITE_PP_IF(__cpp_lib_format >= 201907L)(
            return std::format(fmt, std::forward<Args>(args)...);
        )
        XIEITE_PP_IF(__cpp_lib_format < 201907L)(
            // Fallback implementation using stringstream
            std::ostringstream oss;
            format_impl(oss, fmt, std::forward<Args>(args)...);
            return oss.str();
        )
    }

    // std::span compatibility
    template<typename T>
    class span_compat {
        T* data_;
        std::size_t size_;

    public:
        constexpr span_compat(T* data, std::size_t size) : data_(data), size_(size) {}

        template<std::size_t N>
        constexpr span_compat(T (&array)[N]) : data_(array), size_(N) {}

        template<typename Container>
        constexpr span_compat(Container& container)
            : data_(container.data()), size_(container.size()) {}

        constexpr T* data() const noexcept { return data_; }
        constexpr std::size_t size() const noexcept { return size_; }
        constexpr bool empty() const noexcept { return size_ == 0; }

        constexpr T& operator[](std::size_t index) const noexcept {
            return data_[index];
        }

        constexpr T* begin() const noexcept { return data_; }
        constexpr T* end() const noexcept { return data_ + size_; }
    };

    // Use std::span if available, otherwise use compatibility version
    XIEITE_PP_IF(__cpp_lib_span >= 202002L)(
        template<typename T>
        using span = std::span<T>;
    )
    XIEITE_PP_IF(__cpp_lib_span < 202002L)(
        template<typename T>
        using span = span_compat<T>;
    )

private:
    template<typename... Args>
    static void format_impl(std::ostringstream& oss, const std::string& fmt, Args&&... args) {
        // Simple format implementation - real implementation would be more complex
        oss << fmt;
        ((oss << " " << args), ...);
    }
}
```

## Preprocessor and Macro Workarounds

### Variadic Macro Issues

Handling compiler differences in variadic macro support:

```cpp
#include <xieite/pp/compiler.hpp>
#include <xieite/pp/if.hpp>

// MSVC has different __VA_ARGS__ handling
XIEITE_PP_IF(XIEITE_COMPILER_MSVC)(
    #define XIEITE_EXPAND(x) x
    #define XIEITE_VA_ARGS_COUNT(...) XIEITE_EXPAND(XIEITE_VA_ARGS_COUNT_IMPL(__VA_ARGS__, 16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0))
    #define XIEITE_VA_ARGS_COUNT_IMPL(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,N,...) N
)

XIEITE_PP_IF(!XIEITE_COMPILER_MSVC)(
    #define XIEITE_VA_ARGS_COUNT(...) XIEITE_VA_ARGS_COUNT_IMPL(__VA_ARGS__, 16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
    #define XIEITE_VA_ARGS_COUNT_IMPL(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,N,...) N
)

// Cross-compiler macro dispatch
#define XIEITE_OVERLOAD_MACRO(name, ...) \
    XIEITE_PP_IF(XIEITE_COMPILER_MSVC)( \
        XIEITE_EXPAND(XIEITE_CONCAT(name, XIEITE_VA_ARGS_COUNT(__VA_ARGS__))(__VA_ARGS__)) \
    ) \
    XIEITE_PP_IF(!XIEITE_COMPILER_MSVC)( \
        XIEITE_CONCAT(name, XIEITE_VA_ARGS_COUNT(__VA_ARGS__))(__VA_ARGS__) \
    )

#define XIEITE_CONCAT(a, b) XIEITE_CONCAT_IMPL(a, b)
#define XIEITE_CONCAT_IMPL(a, b) a##b
```

## Debugging and Diagnostic Workarounds

### Compiler-Specific Diagnostics

Handling different warning and error reporting:

```cpp
#include <xieite/pp/compiler.hpp>
#include <xieite/pp/if.hpp>

namespace diagnostic_workarounds {
    // Compiler-specific warning suppression
    XIEITE_PP_IF(XIEITE_COMPILER_GCC)(
        #define XIEITE_SUPPRESS_WARNING_PUSH _Pragma("GCC diagnostic push")
        #define XIEITE_SUPPRESS_WARNING_POP _Pragma("GCC diagnostic pop")
        #define XIEITE_SUPPRESS_UNUSED_VARIABLE _Pragma("GCC diagnostic ignored \"-Wunused-variable\"")
        #define XIEITE_SUPPRESS_UNUSED_PARAMETER _Pragma("GCC diagnostic ignored \"-Wunused-parameter\"")
    )

    XIEITE_PP_IF(XIEITE_COMPILER_CLANG)(
        #define XIEITE_SUPPRESS_WARNING_PUSH _Pragma("clang diagnostic push")
        #define XIEITE_SUPPRESS_WARNING_POP _Pragma("clang diagnostic pop")
        #define XIEITE_SUPPRESS_UNUSED_VARIABLE _Pragma("clang diagnostic ignored \"-Wunused-variable\"")
        #define XIEITE_SUPPRESS_UNUSED_PARAMETER _Pragma("clang diagnostic ignored \"-Wunused-parameter\"")
    )

    XIEITE_PP_IF(XIEITE_COMPILER_MSVC)(
        #define XIEITE_SUPPRESS_WARNING_PUSH __pragma(warning(push))
        #define XIEITE_SUPPRESS_WARNING_POP __pragma(warning(pop))
        #define XIEITE_SUPPRESS_UNUSED_VARIABLE __pragma(warning(disable: 4101))
        #define XIEITE_SUPPRESS_UNUSED_PARAMETER __pragma(warning(disable: 4100))
    )

    // Usage example
    template<typename T>
    void function_with_suppressed_warnings(T value) {
        XIEITE_SUPPRESS_WARNING_PUSH
        XIEITE_SUPPRESS_UNUSED_VARIABLE

        int unused_var = 42; // Warning suppressed

        XIEITE_SUPPRESS_WARNING_POP

        // Use value to avoid parameter warning
        (void)value;
    }
}
```

## Performance Workarounds

### Optimization Differences

Handling compiler-specific optimization issues:

```cpp
#include <xieite/pp/compiler.hpp>
#include <xieite/pp/if.hpp>

namespace optimization_workarounds {
    // Force inlining across compilers
    XIEITE_PP_IF(XIEITE_COMPILER_GCC)(
        #define XIEITE_FORCE_INLINE __attribute__((always_inline)) inline
    )
    XIEITE_PP_IF(XIEITE_COMPILER_CLANG)(
        #define XIEITE_FORCE_INLINE __attribute__((always_inline)) inline
    )
    XIEITE_PP_IF(XIEITE_COMPILER_MSVC)(
        #define XIEITE_FORCE_INLINE __forceinline
    )

    // Hot/cold path annotations
    XIEITE_PP_IF(XIEITE_COMPILER_GCC || XIEITE_COMPILER_CLANG)(
        #define XIEITE_HOT __attribute__((hot))
        #define XIEITE_COLD __attribute__((cold))
        #define XIEITE_LIKELY(x) __builtin_expect(!!(x), 1)
        #define XIEITE_UNLIKELY(x) __builtin_expect(!!(x), 0)
    )
    XIEITE_PP_IF(XIEITE_COMPILER_MSVC)(
        #define XIEITE_HOT
        #define XIEITE_COLD
        #define XIEITE_LIKELY(x) (x)
        #define XIEITE_UNLIKELY(x) (x)
    )

    // Example usage
    template<typename T>
    class performance_critical {
    public:
        XIEITE_FORCE_INLINE XIEITE_HOT
        T hot_path_function(T value) {
            if XIEITE_LIKELY(value > T{}) {
                return value * value;
            } else {
                return cold_path_function(value);
            }
        }

    private:
        XIEITE_COLD
        T cold_path_function(T value) {
            // Complex error handling
            return T{};
        }
    };
}
```

## Testing Compiler Workarounds

### Workaround Validation

Ensuring workarounds function correctly:

```cpp
#include <xieite/pp/compiler.hpp>
#include <xieite/pp/if.hpp>

namespace workaround_testing {
    class compiler_workaround_tests {
    public:
        static void run_all_tests() {
            test_template_constraints();
            test_constexpr_evaluation();
            test_lambda_functionality();
            test_stdlib_compatibility();
        }

    private:
        static void test_template_constraints() {
            template_workarounds::arithmetic_operations<int> ops;
            auto result = ops.add(5, 3);
            assert(result == 8);
        }

        static void test_constexpr_evaluation() {
            constexpr auto fib_10 = constexpr_workarounds::fibonacci<10>();
            static_assert(fib_10 == 55, "Fibonacci calculation incorrect");
        }

        static void test_lambda_functionality() {
            lambda_workarounds::lambda_helper<int> helper;
            auto processor = helper.create_processor();
            auto result = processor(42);
            assert(result == 42);
        }

        static void test_stdlib_compatibility() {
            auto formatted = stdlib_workarounds::format_string("Hello {}", "World");
            assert(!formatted.empty());
        }
    };
}
```

## Best Practices for Compiler Workarounds

### Guidelines

1. **Document Workarounds**: Clearly document why each workaround is necessary
2. **Version Specific**: Be specific about compiler versions that need workarounds
3. **Test Thoroughly**: Test workarounds on all target compilers
4. **Plan for Removal**: Remove workarounds when minimum compiler versions are raised
5. **Minimal Impact**: Keep workarounds as localized as possible
6. **Prefer Standards**: Use standard C++ features over compiler extensions when possible

### Common Pitfalls

1. **Over-Engineering**: Creating complex workarounds for minor issues
2. **Maintenance Burden**: Not removing obsolete workarounds
3. **Performance Impact**: Workarounds that significantly impact performance
4. **Portability Issues**: Workarounds that break on new compiler versions
5. **Code Duplication**: Duplicating logic across compiler-specific branches

This comprehensive approach to compiler workarounds ensures XIEITE-based code works reliably across different compiler toolchains while maintaining performance and readability.