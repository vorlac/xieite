# Compile-Time vs Runtime

This document explores the distinction between compile-time and runtime computation in XIEITE, demonstrating how to leverage the library's features to maximize compile-time evaluation and minimize runtime overhead.

## Fundamental Concepts

### Compile-Time Evaluation

XIEITE emphasizes compile-time computation to achieve zero-cost abstractions:

```cpp
#include <xieite/trait/is_arith.hpp>
#include <xieite/math/abs.hpp>
#include <xieite/pp/arrow.hpp>

// Compile-time constants - computed during compilation
template<xieite::is_arith T>
constexpr auto compile_time_factorial(T n)
XIEITE_ARROW(
    n <= 1 ? 1 : n * compile_time_factorial(n - 1)
)

// These values are computed at compile-time
constexpr auto fact_5 = compile_time_factorial(5);     // = 120
constexpr auto fact_10 = compile_time_factorial(10);   // = 3628800

// No runtime computation cost for these operations
```

### Runtime Evaluation

When compile-time evaluation isn't possible or appropriate:

```cpp
#include <xieite/trait/is_arith.hpp>

template<xieite::is_arith T>
auto runtime_factorial(T n) -> T {
    T result = 1;
    for (T i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// Must be computed at runtime due to dynamic input
auto dynamic_result(int user_input) {
    return runtime_factorial(user_input);
}
```

## Template Metaprogramming and Compile-Time

### Type Computation at Compile-Time

XIEITE's type traits enable sophisticated compile-time type manipulation:

```cpp
#include <xieite/trait/is_arith.hpp>
#include <xieite/trait/can_alias.hpp>
#include <xieite/meta/try_subst.hpp>

// Complex type computation at compile-time
template<typename T>
struct optimal_storage {
    using type = std::conditional_t<
        xieite::is_arith<T> && sizeof(T) <= 8,
        T,                                    // Store arithmetic types directly
        std::conditional_t<
            sizeof(T) <= 16,
            T,                                // Small objects by value
            std::unique_ptr<T>                // Large objects by pointer
        >
    >;
};

// Type selection happens at compile-time
template<typename T>
using optimal_storage_t = typename optimal_storage<T>::type;

// Usage - type determined at compile-time
optimal_storage_t<int> small_value;         // int
optimal_storage_t<std::array<int, 100>> large_value;  // std::unique_ptr<std::array<int, 100>>
```

### Compile-Time Algorithm Selection

Using XIEITE features to select algorithms at compile-time:

```cpp
#include <xieite/trait/is_arith.hpp>
#include <xieite/meta/try_subst.hpp>

// Detect if type has fast multiplication
template<typename T>
using has_fast_multiply = xieite::try_subst<
    decltype(T::fast_multiply),
    std::false_type
>;

template<typename T>
constexpr bool use_fast_algorithm() {
    if constexpr (xieite::is_arith<T>) {
        if constexpr (!std::is_void_v<has_fast_multiply<T>>) {
            return T::fast_multiply;
        } else {
            return sizeof(T) >= 4;  // Heuristic for built-in types
        }
    }
    return false;
}

// Algorithm selection at compile-time - no runtime overhead
template<typename T>
auto multiply_optimized(T a, T b) {
    if constexpr (use_fast_algorithm<T>()) {
        return fast_multiply_impl(a, b);    // Compile-time selection
    } else {
        return generic_multiply_impl(a, b); // Compile-time selection
    }
}
```

## Constexpr and Consteval Patterns

### Constexpr Functions

Functions that can execute at both compile-time and runtime:

```cpp
#include <xieite/trait/is_arith.hpp>
#include <xieite/math/abs.hpp>

template<xieite::is_arith T>
constexpr auto power(T base, unsigned exp) -> T {
    T result = 1;
    for (unsigned i = 0; i < exp; ++i) {
        result *= base;
    }
    return result;
}

// Compile-time usage
constexpr auto compile_time_result = power(2, 10);  // Computed at compile-time

// Runtime usage when input is not constant
auto runtime_power(int base, unsigned exp) {
    return power(base, exp);  // Computed at runtime
}
```

### Consteval Functions (C++20)

Functions that must execute at compile-time:

```cpp
#include <xieite/trait/is_arith.hpp>

template<xieite::is_arith T>
consteval auto compile_time_only_factorial(T n) -> T {
    T result = 1;
    for (T i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// Must be called with compile-time constants
constexpr auto fact_7 = compile_time_only_factorial(7);

// This would be a compile error:
// auto bad_usage(int n) { return compile_time_only_factorial(n); }
```

### Conditional Constexpr

Using XIEITE to conditionally enable compile-time evaluation:

```cpp
#include <xieite/trait/is_arith.hpp>
#include <xieite/pp/arrow.hpp>

template<typename T>
concept compile_time_safe =
    xieite::is_arith<T> &&
    !std::is_floating_point_v<T>;

template<compile_time_safe T>
constexpr auto safe_compile_time_operation(T value)
XIEITE_ARROW(
    value * value + value + 1
)

template<typename T>
requires (!compile_time_safe<T>)
auto runtime_operation(T value)
XIEITE_ARROW(
    value * value + value + 1
)
```

## Static vs Dynamic Dispatch

### Compile-Time Polymorphism

Using templates for compile-time dispatch:

```cpp
#include <xieite/trait/is_arith.hpp>
#include <xieite/pp/arrow.hpp>

// Compile-time polymorphism - no virtual function overhead
template<typename Shape>
constexpr auto calculate_area(const Shape& shape)
XIEITE_ARROW(
    shape.area()
)

struct Rectangle {
    double width, height;

    constexpr auto area() const
    XIEITE_ARROW(width * height)
};

struct Circle {
    double radius;

    constexpr auto area() const
    XIEITE_ARROW(3.14159 * radius * radius)
};

// All dispatch resolved at compile-time
constexpr Rectangle rect{5.0, 3.0};
constexpr Circle circle{2.0};

constexpr auto rect_area = calculate_area(rect);   // No runtime overhead
constexpr auto circle_area = calculate_area(circle); // No runtime overhead
```

### Runtime Polymorphism

When dynamic dispatch is necessary:

```cpp
#include <xieite/trait/is_arith.hpp>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;  // Runtime dispatch
};

class RuntimeRectangle : public Shape {
    double width_, height_;
public:
    RuntimeRectangle(double w, double h) : width_(w), height_(h) {}

    double area() const override {
        return width_ * height_;
    }
};

// Runtime dispatch when shape type is not known at compile-time
auto process_unknown_shape(const Shape& shape) {
    return shape.area();  // Virtual function call
}
```

## Memory Layout and Compile-Time

### Compile-Time Memory Layout

Using XIEITE's fixed containers for predictable layout:

```cpp
#include <xieite/data/fixed_array.hpp>
#include <xieite/trait/is_arith.hpp>

template<xieite::is_arith T, std::size_t N>
struct compile_time_matrix {
    xieite::fixed_array<T, N * N> data;

    // Compile-time indexing - bounds checking eliminated
    constexpr T& at(std::size_t row, std::size_t col) noexcept {
        return data[row * N + col];
    }

    constexpr const T& at(std::size_t row, std::size_t col) const noexcept {
        return data[row * N + col];
    }

    // Compile-time operations
    constexpr auto multiply(const compile_time_matrix& other) const {
        compile_time_matrix result{};

        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t j = 0; j < N; ++j) {
                for (std::size_t k = 0; k < N; ++k) {
                    result.at(i, j) += at(i, k) * other.at(k, j);
                }
            }
        }

        return result;
    }
};

// Compile-time matrix operations
constexpr compile_time_matrix<int, 3> m1{};
constexpr compile_time_matrix<int, 3> m2{};
constexpr auto result = m1.multiply(m2);  // Computed at compile-time if inputs are constexpr
```

### Runtime Memory Management

Dynamic allocation when compile-time size is unknown:

```cpp
#include <xieite/trait/is_arith.hpp>
#include <xieite/fn/scope_guard.hpp>

template<xieite::is_arith T>
class dynamic_matrix {
    std::vector<T> data_;
    std::size_t rows_, cols_;

public:
    dynamic_matrix(std::size_t rows, std::size_t cols)
        : data_(rows * cols), rows_(rows), cols_(cols) {}

    T& at(std::size_t row, std::size_t col) {
        return data_[row * cols_ + col];
    }

    const T& at(std::size_t row, std::size_t col) const {
        return data_[row * cols_ + col];
    }

    // Runtime matrix multiplication
    auto multiply(const dynamic_matrix& other) const {
        if (cols_ != other.rows_) {
            throw std::invalid_argument("Matrix dimensions incompatible");
        }

        dynamic_matrix result(rows_, other.cols_);

        for (std::size_t i = 0; i < rows_; ++i) {
            for (std::size_t j = 0; j < other.cols_; ++j) {
                for (std::size_t k = 0; k < cols_; ++k) {
                    result.at(i, j) += at(i, k) * other.at(k, j);
                }
            }
        }

        return result;
    }
};
```

## Compile-Time String Processing

### Compile-Time String Operations

Using XIEITE for compile-time string manipulation:

```cpp
#include <xieite/data/fixed_str.hpp>
#include <xieite/pp/arrow.hpp>

// Compile-time string hashing
constexpr auto compile_time_hash(const char* str, std::size_t length) -> std::size_t {
    std::size_t hash = 0;
    for (std::size_t i = 0; i < length; ++i) {
        hash = hash * 31 + static_cast<std::size_t>(str[i]);
    }
    return hash;
}

// Compile-time string literal processing
template<xieite::fixed_str Str>
constexpr auto process_string() {
    constexpr auto hash = compile_time_hash(Str.data(), Str.size());
    constexpr auto length = Str.size();

    return std::pair<std::size_t, std::size_t>{hash, length};
}

// Usage with string literals - computed at compile-time
constexpr auto result1 = process_string<"Hello">();
constexpr auto result2 = process_string<"World">();
```

### Runtime String Processing

When string content is not known at compile-time:

```cpp
#include <string>
#include <string_view>

auto runtime_hash(std::string_view str) -> std::size_t {
    std::size_t hash = 0;
    for (char c : str) {
        hash = hash * 31 + static_cast<std::size_t>(c);
    }
    return hash;
}

// Runtime string processing
auto process_user_input(const std::string& input) {
    auto hash = runtime_hash(input);
    auto length = input.length();

    return std::pair<std::size_t, std::size_t>{hash, length};
}
```

## Performance Implications

### Compile-Time Benefits

1. **Zero Runtime Cost**: Computations happen during compilation
2. **Optimized Machine Code**: Compiler can optimize based on known values
3. **Reduced Binary Size**: No need to include computation code
4. **Better Cache Performance**: Results are embedded as constants

### Compile-Time Costs

1. **Longer Compilation Time**: Complex computations slow down builds
2. **Memory Usage**: Compiler uses more memory for large computations
3. **Template Instantiation**: Can lead to code bloat if not managed

### Decision Matrix

Choose compile-time when:
- Input values are known at compile-time
- Computation is expensive but infrequent
- Result doesn't depend on runtime data
- Code size and performance are critical

Choose runtime when:
- Input values are dynamic
- Computation is simple and fast
- Memory usage during compilation is a concern
- Compilation time is critical

## Best Practices

### Hybrid Approaches

Combining compile-time and runtime strategies:

```cpp
#include <xieite/trait/is_arith.hpp>
#include <xieite/pp/arrow.hpp>

template<xieite::is_arith T>
class adaptive_calculator {
    // Compile-time lookup table for common values
    static constexpr std::array<T, 10> precomputed_squares = {
        0, 1, 4, 9, 16, 25, 36, 49, 64, 81
    };

public:
    constexpr auto square(T value) const -> T {
        if constexpr (std::is_integral_v<T>) {
            if (value >= 0 && value < 10) {
                return precomputed_squares[value];  // Compile-time lookup
            }
        }
        return value * value;  // Runtime computation
    }
};

// Usage combines both approaches optimally
constexpr adaptive_calculator<int> calc;
constexpr auto small_result = calc.square(5);  // Uses precomputed table
auto large_result = calc.square(100);          // Uses runtime computation
```

### Gradual Optimization

Moving from runtime to compile-time incrementally:

```cpp
#include <xieite/trait/is_arith.hpp>

// Step 1: Runtime implementation
template<xieite::is_arith T>
auto basic_function(T value) -> T {
    return value * value + value + 1;
}

// Step 2: Add constexpr for compile-time capability
template<xieite::is_arith T>
constexpr auto improved_function(T value) -> T {
    return value * value + value + 1;
}

// Step 3: Add template specialization for compile-time optimization
template<>
constexpr auto improved_function<int>(int value) -> int {
    // Optimized implementation for integers
    return ((value + 1) * value) + 1;
}

// Step 4: Use concepts for fine-grained control
template<typename T>
concept optimizable = xieite::is_arith<T> && sizeof(T) <= 8;

template<optimizable T>
constexpr auto optimized_function(T value) -> T {
    return ((value + 1) * value) + 1;
}
```

## Debugging and Diagnostics

### Compile-Time Debugging

Techniques for debugging compile-time code:

```cpp
#include <xieite/pp/static_assert.hpp>

template<std::size_t N>
constexpr auto debug_factorial() {
    constexpr auto result = compile_time_factorial(N);

    // Compile-time assertions for verification
    static_assert(N == 0 || result > 0, "Factorial should be positive");
    static_assert(N <= 1 || result > N, "Factorial should be greater than input");

    return result;
}

// Compile-time value inspection
template<auto Value>
struct compile_time_inspector {
    static constexpr auto value = Value;

    // Forces compiler to show the value in error messages
    static_assert(Value != Value, "Inspecting compile-time value");
};

// Usage: uncomment to see the value in compiler output
// compile_time_inspector<debug_factorial<5>()> inspector;
```

### Runtime vs Compile-Time Detection

Detecting when code runs at compile-time vs runtime:

```cpp
#include <xieite/pp/arrow.hpp>

constexpr auto is_constant_evaluated() -> bool {
    return std::is_constant_evaluated();
}

template<typename T>
constexpr auto adaptive_algorithm(T value) -> T {
    if (std::is_constant_evaluated()) {
        // Compile-time implementation - may be slower but constexpr-compatible
        T result = 1;
        for (T i = 1; i <= value; ++i) {
            result *= i;
        }
        return result;
    } else {
        // Runtime implementation - can use optimized libraries
        return optimized_runtime_factorial(value);
    }
}
```

This comprehensive understanding of compile-time vs runtime trade-offs enables optimal use of XIEITE's capabilities for maximum performance and expressiveness.