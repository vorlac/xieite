# XIEITE_ARROW_CHOOSE

The `XIEITE_ARROW_CHOOSE` macro is a sophisticated conditional value selection variant of the XIEITE Arrow macro family that enables compile-time branching between different return expressions. This macro provides a powerful tool for template metaprogramming with conditional value selection based on compile-time predicates.

## Implementation

Located in `include/xieite/pp/arrow.hpp` at lines 33-37:

```cpp
#define XIEITE_ARROW_CHOOSE(_cond, _then, ...) \
    noexcept((static_cast<bool>(_cond) && noexcept(_then)) __VA_OPT__(|| (!static_cast<bool>(_cond) && noexcept(__VA_ARGS__)))) \
    -> decltype(auto) \
    requires((static_cast<bool>(_cond) && requires { _then; }) __VA_OPT__(|| (!static_cast<bool>(_cond) && requires { __VA_ARGS__; }))) \
    { if constexpr (static_cast<bool>(_cond)) { return XIEITE_UNWRAP(_then); } else { return __VA_ARGS__; } }
```

## Architecture Analysis

### Macro Parameters

The `XIEITE_ARROW_CHOOSE` macro accepts three parameters:

1. **`_cond`**: Compile-time boolean condition (must be constexpr-evaluable)
2. **`_then`**: Expression to return when condition is true (wrapped with `XIEITE_UNWRAP`)
3. **`__VA_ARGS__`**: Expression to return when condition is false

### Key Differences from XIEITE_ARROW_IF

Unlike `XIEITE_ARROW_IF` which executes side effects conditionally but always returns the same expression, `XIEITE_ARROW_CHOOSE` selects between different return values:

```cpp
// XIEITE_ARROW_IF: conditional side effect, fixed return
auto func1(T value) XIEITE_ARROW_IF(condition, side_effect(), return_expr)
// Executes: if (condition) side_effect(); return return_expr;

// XIEITE_ARROW_CHOOSE: conditional return selection
auto func2(T value) XIEITE_ARROW_CHOOSE(condition, expr_if_true, expr_if_false)
// Executes: if (condition) return expr_if_true; else return expr_if_false;
```

### XIEITE_UNWRAP Integration

The macro uses `XIEITE_UNWRAP` on the `_then` parameter, enabling support for wrapped expressions:

```cpp
// XIEITE_UNWRAP removes one layer of parentheses
XIEITE_UNWRAP((expression))  // → expression
XIEITE_UNWRAP(expression)    // → expression

// Enables complex expressions in _then parameter
auto func(T value) XIEITE_ARROW_CHOOSE(
    condition,
    (complex_expression_with_commas(a, b, c)),  // Wrapped to protect commas
    simple_expression
)
```

## Template Instantiation Mechanics

```cpp
// Usage example:
template<typename T>
auto optimal_size() XIEITE_ARROW_CHOOSE(
    sizeof(T) <= 4,                    // Condition
    (std::uint32_t{sizeof(T)}),       // Then expression (wrapped)
    std::uint64_t{sizeof(T)}          // Else expression
)

// Expands to:
template<typename T>
auto optimal_size()
    noexcept((static_cast<bool>(sizeof(T) <= 4) && noexcept(std::uint32_t{sizeof(T)}))
             || (!static_cast<bool>(sizeof(T) <= 4) && noexcept(std::uint64_t{sizeof(T)})))
    -> decltype(auto)
    requires((static_cast<bool>(sizeof(T) <= 4) && requires { std::uint32_t{sizeof(T)}; })
             || (!static_cast<bool>(sizeof(T) <= 4) && requires { std::uint64_t{sizeof(T)}; }))
{
    if constexpr (static_cast<bool>(sizeof(T) <= 4)) {
        return std::uint32_t{sizeof(T)};
    } else {
        return std::uint64_t{sizeof(T)};
    }
}
```

## Conditional Value Selection Patterns

### Type-Dependent Value Selection

```cpp
// Select optimal numeric type based on requirements
template<std::size_t N>
constexpr auto optimal_uint() XIEITE_ARROW_CHOOSE(
    N <= 255,
    (std::uint8_t{N}),
    N <= 65535 ? std::uint16_t{N} : std::uint32_t{N}
)

// Platform-dependent constants
template<typename T>
constexpr auto alignment_size() XIEITE_ARROW_CHOOSE(
    alignof(T) <= 8,
    (alignof(T)),
    16
)
```

### Algorithm Selection

```cpp
// Choose algorithm based on container properties
template<typename Container>
auto efficient_find(Container& c, const auto& value) XIEITE_ARROW_CHOOSE(
    requires { c.find(value); },
    (c.find(value)),                    // Use member find if available
    std::find(c.begin(), c.end(), value) // Otherwise use std::find
)

// Optimization level selection
template<typename T>
auto compute_hash(const T& value) XIEITE_ARROW_CHOOSE(
    std::is_trivially_copyable_v<T> && sizeof(T) <= 8,
    (bit_cast_hash(value)),             // Fast bit-based hash
    std::hash<T>{}(value)               // Standard hash
)
```

### Compile-Time Resource Selection

```cpp
// Memory allocation strategy
template<std::size_t N>
auto make_storage() XIEITE_ARROW_CHOOSE(
    N <= 1024,
    (std::array<std::byte, N>{}),       // Stack allocation for small sizes
    std::vector<std::byte>(N)           // Heap allocation for large sizes
)

// String representation choice
template<typename T>
auto to_string_optimal(T value) XIEITE_ARROW_CHOOSE(
    std::is_arithmetic_v<T>,
    (std::to_string(value)),            // Fast arithmetic conversion
    static_cast<std::ostringstream&>(std::ostringstream{} << value).str()
)
```

## Exception Safety Analysis

### Dual-Path Noexcept Specification

The macro's noexcept specification evaluates both branches:

```cpp
noexcept((static_cast<bool>(_cond) && noexcept(_then))
         __VA_OPT__(|| (!static_cast<bool>(_cond) && noexcept(__VA_ARGS__))))
```

This results in `noexcept(true)` when:
- **Condition is true** AND **then-expression is noexcept**, OR
- **Condition is false** AND **else-expression is noexcept**

### Exception Safety Examples

```cpp
// Safe when both branches are noexcept
template<typename T>
auto safe_convert(T value) XIEITE_ARROW_CHOOSE(
    std::is_integral_v<T>,
    (static_cast<double>(value)),       // noexcept
    static_cast<double>(value)          // noexcept
) // Entire function is noexcept

// Potentially throwing when branches differ
template<typename T>
auto risky_convert(T value) XIEITE_ARROW_CHOOSE(
    std::is_integral_v<T>,
    (static_cast<double>(value)),       // noexcept
    std::to_string(value)               // may throw
) // noexcept(false) for non-integral types
```

## Advanced Usage Patterns

### Template Metaprogramming Integration

```cpp
// Conditional concept application
template<typename T>
auto smart_access(T&& container, std::size_t index) XIEITE_ARROW_CHOOSE(
    requires { container.at(index); },
    (container.at(index)),              // Bounds-checked access
    container[index]                    // Direct access
)

// Type trait dependent selection
template<typename T>
auto get_zero() XIEITE_ARROW_CHOOSE(
    std::is_floating_point_v<T>,
    (T{0.0}),
    T{0}
)
```

### SFINAE-Friendly Patterns

```cpp
// Enable different implementations based on type capabilities
template<typename T>
auto serialize(const T& value) XIEITE_ARROW_CHOOSE(
    requires { value.serialize(); },
    (value.serialize()),                // Use member function
    generic_serialize(value)            // Use generic implementation
)

// Conditional member access
template<typename T>
auto get_size(const T& container) XIEITE_ARROW_CHOOSE(
    requires { container.size(); },
    (container.size()),                 // STL containers
    std::distance(container.begin(), container.end()) // Range-based
)
```

### Performance Optimization Patterns

```cpp
// Branch-free conditional assignment
template<typename T>
constexpr auto abs_diff(T a, T b) XIEITE_ARROW_CHOOSE(
    a >= b,
    (a - b),
    b - a
)

// Platform-specific optimizations
template<typename T>
auto fast_multiply(T a, T b) XIEITE_ARROW_CHOOSE(
    SUPPORTS_NATIVE_MUL<T>,
    (native_multiply(a, b)),            // Hardware acceleration
    a * b                               // Standard multiplication
)
```

## Integration with XIEITE Systems

### With Type Traits

```cpp
#include <xieite/trait/is_numeric.hpp>
#include <xieite/pp/arrow.hpp>

template<typename T>
auto safe_negate(T value) XIEITE_ARROW_CHOOSE(
    xieite::is_numeric<T> && std::is_signed_v<T>,
    (-value),
    value  // Cannot negate unsigned types safely
)
```

### With Mathematical Functions

```cpp
#include <xieite/math/abs.hpp>
#include <xieite/pp/arrow.hpp>

template<typename T>
auto robust_abs(T value) XIEITE_ARROW_CHOOSE(
    std::is_arithmetic_v<T>,
    (xieite::abs(value)),               // Use XIEITE abs for arithmetic
    std::abs(value)                     // Use std::abs for others
)
```

### With Platform Detection

```cpp
#include <xieite/pp/platform.hpp>
#include <xieite/pp/arrow.hpp>

template<typename T>
auto platform_optimized_hash(T value) XIEITE_ARROW_CHOOSE(
    XIEITE_PLATFORM_TYPE_WINDOWS,
    (windows_hash_function(value)),     // Windows-specific hash
    portable_hash_function(value)       // Portable implementation
)
```

## Complex Expression Handling

### Protecting Comma Expressions

The `XIEITE_UNWRAP` mechanism allows complex expressions with commas in the `_then` branch:

```cpp
// Complex expressions with commas need wrapping
template<typename T>
auto complex_operation(T value) XIEITE_ARROW_CHOOSE(
    std::is_complex_v<T>,
    (std::make_pair(value.real(), value.imag())), // Wrapped to protect comma
    std::make_pair(value, T{0})
)

// Function calls with multiple arguments
template<typename Container>
auto range_check(Container& c, std::size_t index) XIEITE_ARROW_CHOOSE(
    index < c.size(),
    (std::make_optional(c[index])),     // Wrapped for safety
    std::nullopt
)
```

### Template Argument Protection

```cpp
// Protect template arguments in complex expressions
template<typename Key, typename Value>
auto make_map_entry(Key key, Value value) XIEITE_ARROW_CHOOSE(
    std::is_default_constructible_v<Value>,
    (std::pair<Key, Value>{key, value}), // Wrapped template instantiation
    std::make_pair(key, value)
)
```

## Comparison with Other Arrow Macros

| Macro | Execution Model | Return Behavior | Primary Use Case |
|-------|----------------|-----------------|------------------|
| `XIEITE_ARROW_IF` | Conditional execution + fixed return | Fixed expression | Side effects with return |
| `XIEITE_ARROW_CHOOSE` | **Conditional return selection** | **Branch-dependent** | **Value selection** |
| `XIEITE_ARROW_TRY` | Exception handling | Error recovery | Exception safety |

### Selection Guidelines

```cpp
// Use XIEITE_ARROW_CHOOSE when:
// 1. Need different return values based on condition
// 2. No side effects required
// 3. Compile-time branch selection needed

// Example: Value selection (use CHOOSE)
auto get_capacity() XIEITE_ARROW_CHOOSE(debug_mode, 1024, 4096)

// Example: Side effect execution (use IF)
auto process() XIEITE_ARROW_IF(debug_mode, log_debug(), compute_result())
```

## Best Practices

### 1. Use for Pure Value Selection

```cpp
// Good: Pure value selection without side effects
template<typename T>
constexpr auto default_value() XIEITE_ARROW_CHOOSE(
    std::is_arithmetic_v<T>,
    (T{0}),
    T{}
)

// Avoid: Side effects in return expressions
template<typename T>
auto with_side_effects() XIEITE_ARROW_CHOOSE(
    condition,
    (log_message(), compute_value()),   // Side effect in comma expression
    other_value()
)
```

### 2. Wrap Complex Expressions

```cpp
// Good: Properly wrapped complex expressions
auto make_result(auto... args) XIEITE_ARROW_CHOOSE(
    sizeof...(args) > 1,
    (std::make_tuple(args...)),         // Wrapped to protect parameter pack
    std::make_tuple(args..., default_value())
)

// Risk: Unprotected comma expressions
auto risky(auto a, auto b) XIEITE_ARROW_CHOOSE(
    condition,
    std::make_pair(a, b),               // May be parsed incorrectly
    default_pair()
)
```

### 3. Ensure Type Compatibility

```cpp
// Good: Compatible return types
template<typename T>
auto safe_size() XIEITE_ARROW_CHOOSE(
    has_size_method<T>,
    (static_cast<std::size_t>(container.size())), // Explicit cast
    std::size_t{0}
)

// Problematic: Incompatible return types may cause issues
template<typename T>
auto mixed_types() XIEITE_ARROW_CHOOSE(
    condition,
    (std::string{"hello"}),             // string type
    42                                  // int type - may cause deduction issues
)
```

### 4. Document Conditional Logic

```cpp
/**
 * @brief Selects optimal integer type based on value range
 * @param value Input value to store
 * @return Smallest integer type that can hold the value
 * @note Uses uint8_t for values ≤ 255, otherwise uint32_t
 */
template<std::size_t N>
constexpr auto optimal_int() XIEITE_ARROW_CHOOSE(
    N <= 255,
    (std::uint8_t{N}),
    std::uint32_t{N}
)
```

## Limitations and Considerations

### 1. Branch Type Deduction

Both branches must be valid for template instantiation:

```cpp
// Problematic: Invalid branch may cause compilation failure
template<typename T>
auto conditional_access() XIEITE_ARROW_CHOOSE(
    has_member<T>,
    (obj.member()),                     // May fail if T doesn't have member
    default_value()
)

// Better: Use SFINAE or concepts to constrain template
template<typename T>
    requires has_member<T> || std::is_default_constructible_v<T>
auto safe_access() XIEITE_ARROW_CHOOSE(
    has_member<T>,
    (obj.member()),
    T{}
)
```

### 2. Macro Argument Parsing

Complex expressions may require careful parenthesization:

```cpp
// Risk: Template arguments with commas
auto func() XIEITE_ARROW_CHOOSE(
    condition,
    std::map<int, std::string>{},       // Comma interpreted as macro separator
    default_map()
)

// Solution: Use wrapping or type aliases
using map_type = std::map<int, std::string>;
auto func() XIEITE_ARROW_CHOOSE(
    condition,
    (map_type{}),                       // Wrapped
    default_map()
)
```

### 3. Exception Specification Complexity

The dual-path noexcept specification may be counterintuitive:

```cpp
// Function may be noexcept for some instantiations but not others
template<typename T>
auto convert(T value) XIEITE_ARROW_CHOOSE(
    std::is_integral_v<T>,
    (static_cast<double>(value)),       // noexcept
    std::to_string(value)               // may throw
)
// noexcept specification depends on T
```

### 4. Debugging Complexity

Macro expansion can complicate error messages and debugging:

```cpp
// Error messages may reference macro internals
template<typename T>
auto problematic() XIEITE_ARROW_CHOOSE(
    invalid_condition<T>,
    (invalid_expression()),
    another_invalid_expression()
)
```

## Advanced Integration Examples

### With Expression Templates

```cpp
template<typename LHS, typename RHS>
class binary_expr {
public:
    auto evaluate() const XIEITE_ARROW_CHOOSE(
        std::is_same_v<LHS, RHS>,
        (lhs_.value() + rhs_.value()),   // Same type optimization
        static_cast<double>(lhs_.value()) + static_cast<double>(rhs_.value())
    )
};
```

### With Policy-Based Design

```cpp
template<typename T, typename Policy>
class configurable_container {
public:
    auto access(std::size_t index) XIEITE_ARROW_CHOOSE(
        Policy::bounds_checking_enabled,
        (data_.at(index)),               // Bounds-checked access
        data_[index]                     // Direct access
    )
private:
    std::vector<T> data_;
};
```

### With Compile-Time Strings

```cpp
template<auto Str>
constexpr auto string_length() XIEITE_ARROW_CHOOSE(
    std::is_array_v<decltype(Str)>,
    (sizeof(Str) - 1),                  // C-string (subtract null terminator)
    Str.size()                          // String object
)
```

---

*See also: [XIEITE_ARROW_IF](arrow_if.md) | [XIEITE_ARROW_TRY](arrow_try.md) | [XIEITE_UNWRAP](../../categories/pp/unwrap.md)*