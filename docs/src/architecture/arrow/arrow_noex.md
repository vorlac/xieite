# XIEITE_ARROW_NOEX

The `XIEITE_ARROW_NOEX` macro is a specialized variant of the XIEITE Arrow macro family that enforces `noexcept(true)` guarantees on function definitions. This macro enables concise function definitions with explicit noexcept specification, providing both syntactic convenience and compile-time exception safety guarantees.

## Implementation

Located in `include/xieite/pp/arrow.hpp` at lines 23-27:

```cpp
#define XIEITE_ARROW_NOEX(...) \
    noexcept __VA_OPT__( \
        -> decltype(auto) \
        requires(requires { __VA_ARGS__; }) \
    ) { return __VA_ARGS__; }
```

## Architecture Analysis

### Macro Expansion Pattern

The `XIEITE_ARROW_NOEX` macro employs a sophisticated expansion pattern that combines:

1. **Forced noexcept Specification**: Always applies `noexcept` without condition evaluation
2. **Conditional Type Deduction**: Uses `__VA_OPT__` to enable return type deduction only when arguments are provided
3. **Expression Validity Checking**: Employs `requires(requires { __VA_ARGS__; })` for compile-time validation
4. **Automatic Return**: Wraps the expression in a return statement

### Template Instantiation Mechanics

```cpp
// Expansion example:
template<typename T>
auto process(T&& value) XIEITE_ARROW_NOEX(std::forward<T>(value) * 2)

// Expands to:
template<typename T>
auto process(T&& value) noexcept -> decltype(auto)
    requires(requires { std::forward<T>(value) * 2; })
{ return std::forward<T>(value) * 2; }
```

## Exception Safety Guarantees

### Noexcept Enforcement

Unlike `XIEITE_ARROW` which conditionally evaluates `noexcept`, `XIEITE_ARROW_NOEX` **unconditionally** applies `noexcept(true)`:

```cpp
// XIEITE_ARROW - conditional noexcept
auto func1(int x) XIEITE_ARROW(x * 2)  // noexcept(noexcept(x * 2))

// XIEITE_ARROW_NOEX - forced noexcept
auto func2(int x) XIEITE_ARROW_NOEX(x * 2)  // noexcept (always true)
```

### Compile-Time Validation

The macro's `requires` clause provides early error detection:

```cpp
// Valid - arithmetic operations are noexcept
auto safe_multiply(int a, int b) XIEITE_ARROW_NOEX(a * b)

// Compilation error - throwing functions violate noexcept guarantee
auto unsafe_operation() XIEITE_ARROW_NOEX(std::vector<int>(1000000))  // May throw
```

## Usage Patterns

### Performance-Critical Functions

Use `XIEITE_ARROW_NOEX` for functions that must guarantee no exceptions:

```cpp
template<typename T>
constexpr auto square(T value) XIEITE_ARROW_NOEX(value * value)

template<typename T>
constexpr auto abs_diff(T a, T b) XIEITE_ARROW_NOEX(
    a > b ? a - b : b - a
)

// Template specialization with noexcept guarantee
template<std::integral T>
constexpr auto bit_count(T value) XIEITE_ARROW_NOEX(
    std::popcount(static_cast<std::make_unsigned_t<T>>(value))
)
```

### Low-Level System Functions

Ideal for system-level operations requiring exception safety:

```cpp
// Memory operations
template<typename T>
constexpr auto byte_size() XIEITE_ARROW_NOEX(sizeof(T))

template<typename T>
constexpr auto alignment() XIEITE_ARROW_NOEX(alignof(T))

// Bit manipulation
template<typename T>
constexpr auto low_bit(T value) XIEITE_ARROW_NOEX(value & -value)

template<typename T>
constexpr auto is_power_of_two(T value) XIEITE_ARROW_NOEX(
    value > 0 && (value & (value - 1)) == 0
)
```

### Arithmetic Optimizations

Mathematical functions with guaranteed no-throw behavior:

```cpp
template<std::floating_point T>
constexpr auto fast_reciprocal(T x) XIEITE_ARROW_NOEX(T{1} / x)

template<std::integral T>
constexpr auto gcd_binary(T a, T b) XIEITE_ARROW_NOEX(
    a == 0 ? b : gcd_binary(b % a, a)
)

// Compile-time constant evaluation
template<std::size_t N>
constexpr auto factorial() XIEITE_ARROW_NOEX(
    N == 0 ? 1 : N * factorial<N - 1>()
)
```

## Advanced Template Patterns

### SFINAE Integration

`XIEITE_ARROW_NOEX` integrates seamlessly with SFINAE patterns:

```cpp
// Enable only for trivially copyable types
template<typename T>
    requires std::is_trivially_copyable_v<T>
constexpr auto trivial_hash(const T& value) XIEITE_ARROW_NOEX(
    std::hash<std::remove_cv_t<T>>{}(value)
)

// Conditional compilation based on type properties
template<typename T>
constexpr auto safe_cast(auto value) XIEITE_ARROW_NOEX(
    static_cast<T>(value)
) requires std::is_arithmetic_v<T> && noexcept(static_cast<T>(value))
```

### Concept-Based Overloading

Leverage concepts for precise function selection:

```cpp
template<xieite::is_arithmetic T>
constexpr auto magnitude(T value) XIEITE_ARROW_NOEX(
    value < T{0} ? -value : value
)

template<xieite::is_floating_point T>
constexpr auto epsilon_equal(T a, T b) XIEITE_ARROW_NOEX(
    magnitude(a - b) < std::numeric_limits<T>::epsilon()
)
```

### Metaprogramming Applications

Use in template metaprogramming for compile-time computations:

```cpp
template<typename... Ts>
constexpr auto type_count() XIEITE_ARROW_NOEX(sizeof...(Ts))

template<std::size_t I, typename... Ts>
using nth_type = std::tuple_element_t<I, std::tuple<Ts...>>;

template<std::size_t I, typename... Ts>
constexpr auto nth_type_size() XIEITE_ARROW_NOEX(
    sizeof(nth_type<I, Ts...>)
)
```

## Performance Characteristics

### Compile-Time Optimization

The macro enables aggressive compiler optimizations:

1. **Guaranteed No-Throw**: Enables move semantics and copy elision
2. **Inline Expansion**: Simple expressions typically inline completely
3. **Constant Folding**: Constexpr expressions evaluate at compile time
4. **Dead Code Elimination**: Unused branches are removed

### Runtime Performance

```cpp
// Zero-overhead arithmetic wrapper
template<typename T>
class safe_arithmetic {
    T value_;
public:
    constexpr auto get() const XIEITE_ARROW_NOEX(value_)
    constexpr auto add(T x) const XIEITE_ARROW_NOEX(value_ + x)
    constexpr auto mul(T x) const XIEITE_ARROW_NOEX(value_ * x)
};

// Generates identical assembly to raw arithmetic operations
```

## Integration with XIEITE Systems

### With Type Traits

```cpp
#include <xieite/trait/is_arithmetic.hpp>
#include <xieite/pp/arrow.hpp>

template<typename T>
    requires xieite::is_arithmetic<T>
constexpr auto twice(T value) XIEITE_ARROW_NOEX(value + value)
```

### With Mathematical Functions

```cpp
#include <xieite/math/abs.hpp>
#include <xieite/pp/arrow.hpp>

template<typename T>
constexpr auto safe_abs(T value) XIEITE_ARROW_NOEX(xieite::abs(value))
```

### With Preprocessor Utilities

```cpp
#include <xieite/pp/conditional.hpp>
#include <xieite/pp/arrow.hpp>

#define XIEITE_SAFE_OP(op, a, b) \
    XIEITE_IF(std::is_arithmetic_v<decltype(a)>, \
        [](auto x, auto y) XIEITE_ARROW_NOEX(x op y), \
        [](auto, auto) { static_assert(false, "Invalid operation"); } \
    )(a, b)
```

## Best Practices

### 1. Exception Safety First

Only use `XIEITE_ARROW_NOEX` when the expression is genuinely noexcept:

```cpp
// Good: Arithmetic operations are noexcept
auto add(int a, int b) XIEITE_ARROW_NOEX(a + b)

// Bad: Vector construction may throw
auto make_vector(std::size_t n) XIEITE_ARROW_NOEX(std::vector<int>(n))  // Undefined behavior
```

### 2. Prefer for Simple Expressions

Best suited for simple, single-expression functions:

```cpp
// Good: Simple expression
auto square(double x) XIEITE_ARROW_NOEX(x * x)

// Consider regular function for complex logic
auto complex_calculation(int x) {  // Traditional function preferred
    if (x < 0) return -x;
    else if (x > 100) return x / 2;
    else return x * x;
}
```

### 3. Combine with Concepts

Use concepts to ensure type safety:

```cpp
template<xieite::is_numeric T>
constexpr auto increment(T value) XIEITE_ARROW_NOEX(value + T{1})
```

### 4. Document Noexcept Requirements

```cpp
/**
 * @brief Computes the square of a numeric value
 * @param value Input value (must be arithmetic type)
 * @return value * value
 * @note Guaranteed noexcept for all arithmetic types
 */
template<std::arithmetic T>
constexpr auto square(T value) XIEITE_ARROW_NOEX(value * value)
```

## Limitations and Considerations

### 1. Expression Complexity

The macro is designed for single expressions:

```cpp
// Good: Single expression
auto func(int x) XIEITE_ARROW_NOEX(x * 2 + 1)

// Problematic: Multiple statements require traditional function body
auto func(int x) {  // Use regular function instead
    auto temp = x * 2;
    return temp + 1;
}
```

### 2. Exception Safety Verification

The compiler cannot always verify noexcept requirements at macro expansion time:

```cpp
// Runtime undefined behavior if expression throws
template<typename T>
auto risky(T&& value) XIEITE_ARROW_NOEX(std::forward<T>(value).throwing_method())
```

### 3. Template Instantiation Context

The `requires` clause may interfere with certain template patterns:

```cpp
// May cause SFINAE issues in complex template hierarchies
template<template<typename> class Container, typename T>
auto extract(const Container<T>& c) XIEITE_ARROW_NOEX(*c.begin())
```

### 4. Debugging Challenges

Macro expansion can complicate debugging:

```cpp
// Error messages may be less clear with macro usage
auto func(auto x) XIEITE_ARROW_NOEX(undefined_operation(x))  // Cryptic error
```

## Comparison with Other Arrow Macros

| Macro | Noexcept Behavior | Return Type | Use Case |
|-------|-------------------|-------------|----------|
| `XIEITE_ARROW` | `noexcept(expr)` | `decltype(auto)` | General-purpose |
| `XIEITE_ARROW_NOEX` | `noexcept` (forced) | `decltype(auto)` | Exception-safe code |
| `XIEITE_ARROW_RET` | `noexcept(expr)` | Explicit type | Type-controlled returns |

### Selection Criteria

```cpp
// Use XIEITE_ARROW_NOEX when:
// 1. Exception safety is critical
// 2. Expression is guaranteed noexcept
// 3. Performance requires no-throw guarantee

// Use XIEITE_ARROW when:
// 1. Exception safety depends on expression
// 2. Conditional noexcept is acceptable
// 3. Expression may or may not throw

// Use XIEITE_ARROW_RET when:
// 1. Explicit return type control needed
// 2. Type conversions required
// 3. Template specialization based on return type
```

## Compile-Time Verification Patterns

### Static Assertions

```cpp
template<typename T>
constexpr auto safe_operation(T value) XIEITE_ARROW_NOEX(value * 2) {
    static_assert(noexcept(value * 2), "Operation must be noexcept");
}
```

### Concept Requirements

```cpp
template<typename T>
concept NoexceptMultiplicable = requires(T t) {
    { t * 2 } noexcept;
};

template<NoexceptMultiplicable T>
constexpr auto safe_double(T value) XIEITE_ARROW_NOEX(value * 2)
```

## Advanced Use Cases

### Template Metaprogramming

```cpp
template<std::size_t N>
struct fibonacci {
    static constexpr auto value() XIEITE_ARROW_NOEX(
        N <= 1 ? N : fibonacci<N-1>::value() + fibonacci<N-2>::value()
    )
};
```

### Functional Programming Patterns

```cpp
template<typename F, typename... Args>
constexpr auto apply_noexcept(F&& f, Args&&... args) XIEITE_ARROW_NOEX(
    std::forward<F>(f)(std::forward<Args>(args)...)
) requires noexcept(std::forward<F>(f)(std::forward<Args>(args)...))
```

### CRTP Pattern Integration

```cpp
template<typename Derived>
class arithmetic_base {
protected:
    constexpr auto self() const XIEITE_ARROW_NOEX(
        static_cast<const Derived&>(*this)
    )

    constexpr auto self() XIEITE_ARROW_NOEX(
        static_cast<Derived&>(*this)
    )
};
```

---

*See also: [XIEITE_ARROW](arrow.md) | [Arrow Macro Family](../arrow_macros.md) | [Preprocessor Utilities](../../categories/pp/)*