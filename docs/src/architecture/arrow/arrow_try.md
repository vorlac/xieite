# XIEITE_ARROW_TRY

The `XIEITE_ARROW_TRY` macro is a sophisticated exception handling variant of the XIEITE Arrow macro family that enables concise try-catch block definitions with automatic exception recovery. This macro combines arrow function syntax with comprehensive exception handling capabilities, providing a powerful tool for robust error management in template metaprogramming contexts.

## Implementation

Located in `include/xieite/pp/arrow.hpp` at lines 38-44:

```cpp
#define XIEITE_ARROW_TRY(_body, ...) \
    XIEITE_EVAL( \
        noexcept __VA_OPT__((DETAIL_XIEITE_ARROW_TRY(requires noexcept, __VA_ARGS__))) \
        -> decltype(auto) \
        requires(DETAIL_XIEITE_ARROW_TRY(,, _body, __VA_ARGS__)) \
        try { return XIEITE_UNWRAP(_body); } DETAIL_XIEITE_ARROW_CATCH(__VA_ARGS__) \
    )
```

## Architecture Analysis

### Macro Parameter Structure

The `XIEITE_ARROW_TRY` macro uses a variadic parameter structure:

1. **`_body`**: Main expression to execute within try block (wrapped with `XIEITE_UNWRAP`)
2. **`__VA_ARGS__`**: Variable number of exception handling pairs

### Exception Handler Syntax

Each exception handler in `__VA_ARGS__` follows the pattern:
```cpp
(exception_type), recovery_expression
```

The macro processes these pairs using helper macros:
- `DETAIL_XIEITE_ARROW_TRY`: Validates exception handling at compile time
- `DETAIL_XIEITE_ARROW_CATCH`: Generates catch blocks with recovery expressions

### Template Instantiation Mechanics

```cpp
// Usage example:
template<typename T>
auto safe_convert(T value) XIEITE_ARROW_TRY(
    risky_operation(value),                    // Try body
    (std::runtime_error), default_value(),    // Catch runtime_error
    (std::logic_error), fallback_value()      // Catch logic_error
)

// Expands approximately to:
template<typename T>
auto safe_convert(T value)
    noexcept((requires { risky_operation(value); } && noexcept(risky_operation(value)))
             || (requires { default_value(); } && noexcept(default_value()))
             || (requires { fallback_value(); } && noexcept(fallback_value())))
    -> decltype(auto)
    requires(/* complex requirements validation */)
try {
    return risky_operation(value);
} catch (std::runtime_error) {
    return default_value();
} catch (std::logic_error) {
    return fallback_value();
}
```

## Exception Safety Patterns

### Basic Exception Recovery

```cpp
// Simple exception handling with fallback
template<typename T>
auto safe_access(std::vector<T>& vec, std::size_t index) XIEITE_ARROW_TRY(
    vec.at(index),                            // May throw std::out_of_range
    (std::out_of_range), T{}                  // Return default value
)

// File operation with recovery
auto read_config() XIEITE_ARROW_TRY(
    load_from_file("config.json"),            // May throw std::filesystem::filesystem_error
    (std::filesystem::filesystem_error), default_config()
)
```

### Multi-Exception Handling

```cpp
// Handle multiple exception types
template<typename T>
auto robust_parse(const std::string& input) XIEITE_ARROW_TRY(
    parse_value<T>(input),                    // Primary parsing attempt
    (std::invalid_argument), T{},             // Invalid format
    (std::out_of_range), T{},                 // Value out of range
    (std::bad_alloc), throw                   // Re-throw memory errors
)

// Complex resource management
template<typename Resource>
auto safe_acquire() XIEITE_ARROW_TRY(
    std::make_unique<Resource>(),             // May throw multiple exceptions
    (std::bad_alloc), nullptr,                // Memory allocation failure
    (Resource::initialization_error), nullptr, // Resource-specific error
    (...), nullptr                            // Catch-all for other exceptions
)
```

### Exception Type Specialization

```cpp
// Template specialization based on exception handling
template<typename T>
auto convert_with_fallback(const std::string& str) XIEITE_ARROW_TRY(
    std::stoi(str),                           // Try integer conversion
    (std::invalid_argument), 0,               // Invalid format
    (std::out_of_range), std::numeric_limits<int>::max() // Range overflow
)

// Floating point with different recovery strategies
template<typename FloatType>
auto safe_divide(FloatType a, FloatType b) XIEITE_ARROW_TRY(
    divide_checked(a, b),                     // May throw division_by_zero
    (division_by_zero), std::numeric_limits<FloatType>::infinity()
)
```

## Advanced Exception Handling Patterns

### Conditional Exception Handling

```cpp
// Exception handling based on type properties
template<typename T>
auto safe_construction() XIEITE_ARROW_TRY(
    T{complex_initialization()},             // May throw in constructor
    (std::exception), std::conditional_t<
        std::is_default_constructible_v<T>,
        T{},                                  // Use default constructor
        std::optional<T>{}                    // Or return empty optional
    >
)
```

### Exception Chaining and Recovery

```cpp
// Multi-level exception recovery
template<typename T>
auto resilient_operation(T input) XIEITE_ARROW_TRY(
    primary_algorithm(input),                 // Primary attempt
    (algorithm_error), secondary_algorithm(input), // Fallback algorithm
    (std::runtime_error), safe_fallback(input),    // Safe fallback
    (...), default_result<T>()                     // Ultimate fallback
)
```

### Resource Acquisition with Exception Safety

```cpp
// RAII-style resource management
template<typename ResourceType>
auto acquire_with_fallback() XIEITE_ARROW_TRY(
    ResourceType::acquire_optimal(),          // Optimal resource acquisition
    (ResourceType::unavailable_error), ResourceType::acquire_basic(),
    (std::bad_alloc), ResourceType::null_resource(),
    (...), ResourceType::emergency_resource()
)
```

## Integration with XIEITE Systems

### With Type Traits

```cpp
#include <xieite/trait/is_numeric.hpp>
#include <xieite/pp/arrow.hpp>

template<typename T>
    requires xieite::is_numeric<T>
auto safe_numeric_convert(const std::string& str) XIEITE_ARROW_TRY(
    string_to_numeric<T>(str),                // May throw conversion errors
    (conversion_error), T{0},                 // Default numeric value
    (std::bad_alloc), throw                   // Re-throw memory errors
)
```

### With Mathematical Functions

```cpp
#include <xieite/math/abs.hpp>
#include <xieite/pp/arrow.hpp>

template<typename T>
auto safe_mathematical_operation(T value) XIEITE_ARROW_TRY(
    complex_math_function(value),             // May throw math_error
    (math_error), xieite::abs(value),         // Fallback to simple abs
    (std::overflow_error), T{0}               // Handle overflow
)
```

### With System Utilities

```cpp
#include <xieite/sys/os.hpp>
#include <xieite/pp/arrow.hpp>

auto platform_specific_operation() XIEITE_ARROW_TRY(
    platform_optimized_function(),           // May not be available
    (platform_error), generic_implementation(),
    (std::runtime_error), fallback_operation()
)
```

## Exception Specification Analysis

### Noexcept Calculation

The macro's noexcept specification evaluates all possible code paths:

```cpp
noexcept __VA_OPT__((DETAIL_XIEITE_ARROW_TRY(requires noexcept, __VA_ARGS__)))
```

This results in `noexcept(true)` when:
1. **Try body is noexcept**, OR
2. **All catch blocks are noexcept and handle all possible exceptions**

### Exception Safety Examples

```cpp
// Guaranteed noexcept when all paths are safe
auto always_safe() XIEITE_ARROW_TRY(
    noexcept_operation(),                     // noexcept
    (...), noexcept_fallback()                // noexcept fallback
) // Entire function is noexcept

// Potentially throwing when recovery may throw
auto may_throw() XIEITE_ARROW_TRY(
    risky_operation(),                        // May throw
    (std::exception), throwing_recovery()     // Recovery may also throw
) // noexcept(false)
```

## Performance Characteristics

### Zero-Cost Exception Safety

When exceptions don't occur, the macro generates efficient code:

```cpp
// Optimizes to direct call when no exceptions thrown
template<typename T>
auto fast_path(T value) XIEITE_ARROW_TRY(
    optimized_operation(value),               // Fast path
    (rare_exception), slow_fallback(value)    // Exception path (rarely taken)
)
```

### Compile-Time Exception Path Analysis

```cpp
// Compiler can optimize based on exception specifications
template<typename T>
auto conditional_safety(T value) XIEITE_ARROW_TRY(
    std::conditional_t<std::is_nothrow_constructible_v<T>,
        fast_construction<T>,
        safe_construction<T>
    >(value),
    (construction_error), T{}
)
```

## Best Practices

### 1. Specific Exception Types

```cpp
// Good: Catch specific exception types
auto parse_int(const std::string& str) XIEITE_ARROW_TRY(
    std::stoi(str),
    (std::invalid_argument), 0,               // Specific handling
    (std::out_of_range), INT_MAX              // Specific handling
)

// Avoid: Overly broad exception catching
auto risky_parse(const std::string& str) XIEITE_ARROW_TRY(
    std::stoi(str),
    (...), 0                                  // Too broad - may hide bugs
)
```

### 2. Meaningful Recovery

```cpp
// Good: Meaningful recovery strategies
template<typename T>
auto safe_factory() XIEITE_ARROW_TRY(
    T::create_optimal(),                      // Try optimal creation
    (creation_error), T::create_basic(),      // Fallback to basic
    (std::bad_alloc), nullptr                 // Clear failure indication
)

// Avoid: Silent failure without indication
template<typename T>
auto silent_factory() XIEITE_ARROW_TRY(
    T::create_optimal(),
    (...), T{}                                // May hide important errors
)
```

### 3. Exception Safety Guarantees

```cpp
// Good: Document exception safety level
/**
 * @brief Safely processes input with strong exception safety
 * @param input Input to process
 * @return Processed result or safe fallback
 * @throw Never throws - all exceptions handled internally
 */
template<typename T>
auto strong_safety(T input) XIEITE_ARROW_TRY(
    process_input(input),
    (...), safe_default<T>()
)
```

### 4. Resource Management

```cpp
// Good: Proper resource cleanup in exception paths
template<typename Resource>
auto safe_resource_use() XIEITE_ARROW_TRY(
    use_resource_optimally(),
    (resource_error), cleanup_and_fallback(),
    (std::exception), emergency_cleanup()
)
```

## Limitations and Considerations

### 1. Macro Parameter Complexity

Complex exception handlers may require careful parenthesization:

```cpp
// Risk: Template arguments with commas
auto complex_types() XIEITE_ARROW_TRY(
    operation(),
    (std::pair<int, std::string>), default_pair() // May be parsed incorrectly
)

// Solution: Use type aliases or extra parentheses
using pair_type = std::pair<int, std::string>;
auto safe_complex() XIEITE_ARROW_TRY(
    operation(),
    (pair_type), default_pair()
)
```

### 2. Exception Specification Complexity

The macro's exception specification can become very complex:

```cpp
// Complex noexcept calculation with multiple handlers
template<typename T>
auto complex_handling(T value) XIEITE_ARROW_TRY(
    complex_operation(value),
    (error_a), recovery_a(),
    (error_b), recovery_b(),
    (error_c), recovery_c()
) // noexcept depends on all operations
```

### 3. Debugging Challenges

Exception handling in macros can complicate debugging:

```cpp
// Error locations may reference macro internals
template<typename T>
auto debug_difficult() XIEITE_ARROW_TRY(
    problematic_operation(),
    (some_exception), problematic_recovery()  // Stack traces may be unclear
)
```

### 4. Template Instantiation Cost

Complex exception handling may impact compilation time:

```cpp
// Many exception handlers increase compilation cost
template<typename T>
auto many_handlers() XIEITE_ARROW_TRY(
    operation(),
    (exception_1), handler_1(),
    (exception_2), handler_2(),
    // ... many more handlers
)
```

## Comparison with Other Arrow Macros

| Macro | Exception Handling | Return Behavior | Primary Use Case |
|-------|-------------------|-----------------|------------------|
| `XIEITE_ARROW` | None | Single expression | Simple functions |
| `XIEITE_ARROW_IF` | None | Conditional execution | Side effects |
| `XIEITE_ARROW_CHOOSE` | None | Conditional values | Value selection |
| `XIEITE_ARROW_TRY` | **Full try-catch** | **Exception recovery** | **Error handling** |

### Selection Guidelines

```cpp
// Use XIEITE_ARROW_TRY when:
// 1. Operations may throw exceptions
// 2. Want concise exception handling
// 3. Need automatic recovery strategies
// 4. Require exception safety guarantees

// Example: Exception handling (use TRY)
auto safe_op() XIEITE_ARROW_TRY(risky_call(), (std::exception), fallback())

// Example: Simple function (use ARROW)
auto simple(int x) XIEITE_ARROW(x * 2)
```

## Advanced Integration Examples

### With RAII and Smart Pointers

```cpp
template<typename T>
auto safe_unique_ptr() XIEITE_ARROW_TRY(
    std::make_unique<T>(complex_args()),
    (std::bad_alloc), std::unique_ptr<T>{},
    (construction_error), std::make_unique<T>()
)
```

### With Async Operations

```cpp
template<typename Future>
auto safe_future_get(Future&& fut) XIEITE_ARROW_TRY(
    fut.get(),
    (std::future_error), typename Future::value_type{},
    (std::exception), default_value<typename Future::value_type>()
)
```

### With Standard Library Algorithms

```cpp
template<typename Container, typename Predicate>
auto safe_find_if(Container&& c, Predicate&& pred) XIEITE_ARROW_TRY(
    std::find_if(c.begin(), c.end(), std::forward<Predicate>(pred)),
    (std::exception), c.end()  // Return end iterator on any exception
)
```

---

*See also: [XIEITE_ARROW](arrow.md) | [XIEITE_ARROW_DECL](arrow_decl.md) | [Exception Safety Patterns](../error_handling.md)*