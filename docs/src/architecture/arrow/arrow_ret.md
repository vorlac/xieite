# XIEITE_ARROW_RET

The `XIEITE_ARROW_RET` macro is a specialized variant of the XIEITE Arrow macro family designed for functions that require explicit return type specification. This macro combines the conciseness of arrow function syntax with explicit return type control, enabling precise type management in template metaprogramming contexts.

## Implementation

Located in `include/xieite/pp/arrow.hpp` at lines 18-22:

```cpp
#define XIEITE_ARROW_RET(...) \
    noexcept __VA_OPT__( \
        (noexcept(__VA_ARGS__)) \
        requires(requires { __VA_ARGS__; }) \
    ) { return __VA_ARGS__; }
```

## Architecture Analysis

### Macro Expansion Pattern

The `XIEITE_ARROW_RET` macro implements a unique design that **omits automatic return type deduction**, requiring explicit specification:

1. **Explicit Return Type Requirement**: Unlike other arrow macros, this does NOT include `-> decltype(auto)`
2. **Conditional Noexcept**: Uses `noexcept(noexcept(__VA_ARGS__))` for expression-dependent exception specification
3. **Expression Validation**: Employs `requires(requires { __VA_ARGS__; })` for compile-time validation
4. **Automatic Return**: Wraps the expression in a return statement

### Template Instantiation Mechanics

```cpp
// Usage example with explicit return type:
template<typename T>
bool is_positive(T value) XIEITE_ARROW_RET(value > T{0})

// Expands to:
template<typename T>
bool is_positive(T value) noexcept(noexcept(value > T{0}))
    requires(requires { value > T{0}; })
{ return value > T{0}; }
```

## Type Control Applications

### Explicit Type Conversion

The primary advantage of `XIEITE_ARROW_RET` is precise control over return types:

```cpp
// Force specific return type despite expression type
template<typename T>
double as_double(T value) XIEITE_ARROW_RET(static_cast<double>(value))

// Boolean conversion regardless of expression type
template<typename Container>
bool has_elements(const Container& c) XIEITE_ARROW_RET(!c.empty())

// Integer promotion control
template<typename T>
int promoted_size() XIEITE_ARROW_RET(sizeof(T))
```

### Template Specialization Control

Enable template specialization based on return types:

```cpp
// Specialization dispatcher
template<typename T>
struct result_type {
    using type = T;
};

template<typename T>
typename result_type<int>::type integer_result(T value) XIEITE_ARROW_RET(
    static_cast<int>(value)
)

template<typename T>
typename result_type<double>::type double_result(T value) XIEITE_ARROW_RET(
    static_cast<double>(value)
)
```

### SFINAE-Friendly Type Control

```cpp
// Enable different overloads based on return type requirements
template<typename T>
std::enable_if_t<std::is_integral_v<T>, bool>
is_even(T value) XIEITE_ARROW_RET(value % 2 == 0)

template<typename T>
std::enable_if_t<std::is_floating_point_v<T>, bool>
is_even(T value) XIEITE_ARROW_RET(std::fmod(value, 2.0) == 0.0)
```

## Advanced Usage Patterns

### Concept-Based Return Type Selection

```cpp
template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template<Arithmetic T>
std::common_type_t<T, double> normalize(T value) XIEITE_ARROW_RET(
    static_cast<double>(value) / std::numeric_limits<T>::max()
)
```

### Metaprogramming Type Transformations

```cpp
// Transform input types to specific output types
template<typename T>
std::conditional_t<std::is_signed_v<T>, T, std::make_signed_t<T>>
ensure_signed(T value) XIEITE_ARROW_RET(
    static_cast<std::conditional_t<std::is_signed_v<T>, T, std::make_signed_t<T>>>(value)
)

// Type-dependent result selection
template<typename T>
std::conditional_t<sizeof(T) <= 4, std::uint32_t, std::uint64_t>
type_hash() XIEITE_ARROW_RET(
    sizeof(T) <= 4 ?
        static_cast<std::uint32_t>(typeid(T).hash_code()) :
        static_cast<std::uint64_t>(typeid(T).hash_code())
)
```

### Functional Programming Patterns

```cpp
// Higher-order function with controlled return types
template<typename F, typename T>
std::invoke_result_t<F, T> apply_function(F&& f, T&& value) XIEITE_ARROW_RET(
    std::forward<F>(f)(std::forward<T>(value))
)

// Monad-like transformations
template<typename T>
std::optional<T> safe_divide(T numerator, T denominator) XIEITE_ARROW_RET(
    denominator != T{0} ?
        std::optional<T>{numerator / denominator} :
        std::nullopt
)
```

## Performance Optimization Patterns

### Compile-Time Type Selection

```cpp
// Select optimal integer type for size
template<std::size_t N>
std::conditional_t<(N <= 255), std::uint8_t,
    std::conditional_t<(N <= 65535), std::uint16_t,
        std::conditional_t<(N <= 4294967295ULL), std::uint32_t, std::uint64_t>>>
optimal_uint_for() XIEITE_ARROW_RET(
    static_cast<std::conditional_t<(N <= 255), std::uint8_t,
        std::conditional_t<(N <= 65535), std::uint16_t,
            std::conditional_t<(N <= 4294967295ULL), std::uint32_t, std::uint64_t>>>>(N)
)
```

### Zero-Cost Abstractions

```cpp
// Wrapper with precise type control
template<typename T>
class strong_type {
    T value_;
public:
    explicit constexpr strong_type(T value) : value_(value) {}

    // Explicit conversion with type control
    T get() const XIEITE_ARROW_RET(value_)

    // Arithmetic operations with type preservation
    strong_type add(const strong_type& other) const XIEITE_ARROW_RET(
        strong_type{value_ + other.value_}
    )
};
```

## Integration with XIEITE Systems

### With Type Traits

```cpp
#include <xieite/trait/is_numeric.hpp>
#include <xieite/pp/arrow.hpp>

template<typename T>
    requires xieite::is_numeric<T>
std::make_unsigned_t<T> to_unsigned(T value) XIEITE_ARROW_RET(
    static_cast<std::make_unsigned_t<T>>(value)
)
```

### With Mathematical Functions

```cpp
#include <xieite/math/abs.hpp>
#include <xieite/pp/arrow.hpp>

template<typename T>
double normalized_abs(T value) XIEITE_ARROW_RET(
    static_cast<double>(xieite::abs(value)) / std::numeric_limits<T>::max()
)
```

### With Template Metaprogramming

```cpp
#include <xieite/meta/type_list.hpp>
#include <xieite/pp/arrow.hpp>

template<typename TypeList>
std::size_t type_list_size() XIEITE_ARROW_RET(TypeList::size)

template<std::size_t I, typename TypeList>
typename TypeList::template at<I> get_type_at() XIEITE_ARROW_RET(
    typename TypeList::template at<I>{}
)
```

## Comparison with Other Arrow Macros

| Macro | Return Type | Noexcept Behavior | Primary Use Case |
|-------|-------------|-------------------|------------------|
| `XIEITE_ARROW` | `decltype(auto)` | `noexcept(expr)` | General-purpose |
| `XIEITE_ARROW_NOEX` | `decltype(auto)` | `noexcept` (forced) | Exception-safe code |
| `XIEITE_ARROW_RET` | **Explicit** | `noexcept(expr)` | **Type control** |

### Selection Guidelines

```cpp
// Use XIEITE_ARROW_RET when:
// 1. Explicit return type needed
// 2. Type conversions required
// 3. Template specialization based on return type
// 4. SFINAE patterns require specific types

// Example scenarios:
auto func1(int x) XIEITE_ARROW(x * 2)           // Auto deduction OK
auto func2(int x) XIEITE_ARROW_NOEX(x * 2)      // Need noexcept guarantee
bool func3(int x) XIEITE_ARROW_RET(x > 0)       // Need specific bool type
```

## Advanced Template Patterns

### CRTP Integration

```cpp
template<typename Derived>
class comparable {
public:
    bool operator<(const Derived& other) const XIEITE_ARROW_RET(
        static_cast<const Derived&>(*this).compare(other) < 0
    )

    bool operator>(const Derived& other) const XIEITE_ARROW_RET(
        static_cast<const Derived&>(*this).compare(other) > 0
    )
};
```

### Policy-Based Design

```cpp
template<typename ValueType, typename ComparisonPolicy>
class ordered_value {
    ValueType value_;
public:
    bool less_than(const ordered_value& other) const XIEITE_ARROW_RET(
        ComparisonPolicy::compare(value_, other.value_) < 0
    )

    ValueType extract() const XIEITE_ARROW_RET(value_)
};
```

### Expression Template Patterns

```cpp
template<typename LHS, typename RHS>
class binary_expression {
    LHS lhs_;
    RHS rhs_;
public:
    auto evaluate() const XIEITE_ARROW_RET(lhs_.evaluate() + rhs_.evaluate())

    // Explicit type control for different operations
    double as_double() const XIEITE_ARROW_RET(
        static_cast<double>(lhs_.evaluate() + rhs_.evaluate())
    )
};
```

## Error Handling and Diagnostics

### Compile-Time Error Detection

```cpp
template<typename T>
T safe_cast(auto value) XIEITE_ARROW_RET(static_cast<T>(value))
    requires std::is_convertible_v<decltype(value), T>

// Usage that generates clear error messages
// auto result = safe_cast<int>("hello");  // Clear conversion error
```

### Static Assertion Integration

```cpp
template<typename From, typename To>
To verified_cast(From value) XIEITE_ARROW_RET(static_cast<To>(value)) {
    static_assert(std::is_convertible_v<From, To>,
                 "Types must be convertible");
    static_assert(sizeof(To) >= sizeof(From) || std::is_floating_point_v<To>,
                 "Cast may lose precision");
}
```

## Best Practices

### 1. Explicit Type Requirements

Always use when explicit return type control is needed:

```cpp
// Good: Explicit bool for predicate functions
template<typename T>
bool is_positive(T value) XIEITE_ARROW_RET(value > T{0})

// Avoid: Auto deduction may not give desired type
template<typename T>
auto is_positive(T value) XIEITE_ARROW(value > T{0})  // May return int, not bool
```

### 2. Type Safety in Generic Code

```cpp
// Good: Guaranteed type safety
template<typename T>
std::string to_string_safe(T value) XIEITE_ARROW_RET(std::to_string(value))
    requires requires { std::to_string(value); }

// Risk: Auto deduction might not match expectations
template<typename T>
auto to_string_unsafe(T value) XIEITE_ARROW(std::to_string(value))
```

### 3. Performance-Critical Type Control

```cpp
// Good: Optimal type selection
template<std::size_t N>
std::conditional_t<N <= 255, std::uint8_t, std::uint16_t>
optimal_index() XIEITE_ARROW_RET(static_cast<
    std::conditional_t<N <= 255, std::uint8_t, std::uint16_t>>(N))
```

### 4. Documentation of Type Contracts

```cpp
/**
 * @brief Converts value to normalized double in range [0.0, 1.0]
 * @param value Input value of arithmetic type
 * @return double Normalized value (explicit type guarantee)
 */
template<std::arithmetic T>
double normalize_to_unit(T value) XIEITE_ARROW_RET(
    static_cast<double>(value) / static_cast<double>(std::numeric_limits<T>::max())
)
```

## Limitations and Considerations

### 1. Verbose Type Specifications

The requirement for explicit return types can make code verbose:

```cpp
// Verbose but precise
std::conditional_t<std::is_signed_v<T>, std::make_unsigned_t<T>, T>
process(T value) XIEITE_ARROW_RET(/* expression */)

// Consider type aliases for complex types
template<typename T>
using processed_type = std::conditional_t<std::is_signed_v<T>, std::make_unsigned_t<T>, T>;

template<typename T>
processed_type<T> process(T value) XIEITE_ARROW_RET(/* expression */)
```

### 2. Template Instantiation Overhead

Complex return type expressions may impact compilation time:

```cpp
// May slow compilation
template<typename T>
std::enable_if_t<
    std::is_arithmetic_v<T> && !std::is_same_v<T, bool>,
    std::conditional_t<std::is_floating_point_v<T>, T, double>
> complex_return(T value) XIEITE_ARROW_RET(/* expression */)
```

### 3. Type Deduction Conflicts

May interfere with template argument deduction:

```cpp
// Deduction may be ambiguous
template<typename T>
T identity(T value) XIEITE_ARROW_RET(value)

// auto result = identity(42);  // T deduced as int, but what if expression changes type?
```

## Integration Examples

### With Standard Library

```cpp
#include <algorithm>
#include <vector>

template<typename Container>
bool has_duplicates(const Container& c) XIEITE_ARROW_RET(
    std::adjacent_find(c.begin(), c.end()) != c.end()
)

template<typename Iterator>
std::size_t distance_safe(Iterator first, Iterator last) XIEITE_ARROW_RET(
    static_cast<std::size_t>(std::distance(first, last))
)
```

### With Custom Type Systems

```cpp
// Strong typing system
template<typename Tag, typename T>
class strong_typedef {
    T value_;
public:
    explicit strong_typedef(T value) : value_(value) {}

    T value() const XIEITE_ARROW_RET(value_)

    bool operator==(const strong_typedef& other) const XIEITE_ARROW_RET(
        value_ == other.value_
    )
};

using user_id = strong_typedef<struct user_id_tag, std::uint64_t>;
using order_id = strong_typedef<struct order_id_tag, std::uint64_t>;
```

---

*See also: [XIEITE_ARROW](arrow.md) | [XIEITE_ARROW_NOEX](arrow_noex.md) | [Arrow Macro Family](../arrow_macros.md)*