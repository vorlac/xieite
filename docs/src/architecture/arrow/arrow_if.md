# XIEITE_ARROW_IF

The `XIEITE_ARROW_IF` macro is a sophisticated control flow variant of the XIEITE Arrow macro family that enables conditional execution with automatic return value handling. This macro combines compile-time conditional logic with arrow function syntax, providing a powerful tool for template metaprogramming and conditional function definitions.

## Implementation

Located in `include/xieite/pp/arrow.hpp` at lines 28-32:

```cpp
#define XIEITE_ARROW_IF(_cond, _then, ...) \
    noexcept((!static_cast<bool>(_cond) || noexcept(_then)) __VA_OPT__(&& noexcept(__VA_ARGS__))) \
    -> decltype(auto) \
    requires((!static_cast<bool>(_cond) || requires { _then; }) __VA_OPT__(&& requires { __VA_ARGS__; })) \
    { if constexpr (static_cast<bool>(_cond)) { _then; } return __VA_ARGS__; }
```

## Architecture Analysis

### Macro Parameters

The `XIEITE_ARROW_IF` macro accepts three parameters:

1. **`_cond`**: Compile-time boolean condition (must be constexpr-evaluable)
2. **`_then`**: Statement or expression to execute when condition is true
3. **`__VA_ARGS__`**: Return expression (always evaluated and returned)

### Expansion Pattern

The macro implements a sophisticated pattern combining:

1. **Conditional Noexcept**: Complex noexcept specification that considers both branches
2. **Automatic Return Type Deduction**: Uses `-> decltype(auto)` for type inference
3. **Compile-Time Requirements**: Validates both conditional and return expressions
4. **Constexpr Conditional Execution**: Uses `if constexpr` for compile-time branching

### Template Instantiation Mechanics

```cpp
// Usage example:
template<typename T>
auto safe_process(T value) XIEITE_ARROW_IF(
    std::is_arithmetic_v<T>,           // Condition
    validate_arithmetic(value),        // Then statement
    transform_value(value)             // Return expression
)

// Expands to:
template<typename T>
auto safe_process(T value)
    noexcept((!static_cast<bool>(std::is_arithmetic_v<T>) || noexcept(validate_arithmetic(value)))
             && noexcept(transform_value(value)))
    -> decltype(auto)
    requires((!static_cast<bool>(std::is_arithmetic_v<T>) || requires { validate_arithmetic(value); })
             && requires { transform_value(value); })
{
    if constexpr (static_cast<bool>(std::is_arithmetic_v<T>)) {
        validate_arithmetic(value);
    }
    return transform_value(value);
}
```

## Control Flow Semantics

### Conditional Execution Model

The macro implements a unique execution model:

1. **Condition Evaluation**: `_cond` is evaluated at compile time
2. **Conditional Statement**: `_then` executes only if condition is true
3. **Unconditional Return**: `__VA_ARGS__` always executes and becomes the return value

```cpp
// Execution flow visualization:
template<bool condition>
auto example() XIEITE_ARROW_IF(
    condition,              // if constexpr (condition)
    side_effect(),         // { side_effect(); }
    compute_result()       // return compute_result();
)

// When condition = true:  side_effect() runs, then returns compute_result()
// When condition = false: only returns compute_result()
```

### Side Effect Management

```cpp
// Logging with conditional debugging
template<typename T>
auto process_with_logging(T value) XIEITE_ARROW_IF(
    DEBUG_MODE,
    std::cout << "Processing: " << value << std::endl,
    value * 2
)

// Resource management with conditional cleanup
template<typename Resource>
auto use_resource(Resource& res) XIEITE_ARROW_IF(
    requires_cleanup<Resource>,
    res.prepare(),
    res.get_value()
)
```

## Advanced Usage Patterns

### Template Metaprogramming Integration

```cpp
// Conditional static assertions
template<typename T>
auto validate_type(T value) XIEITE_ARROW_IF(
    std::is_class_v<T>,
    static_assert(std::is_default_constructible_v<T>, "Class must be default constructible"),
    value
)

// Conditional template instantiation
template<typename T>
auto optimize_for_size(T container) XIEITE_ARROW_IF(
    sizeof(T) > 1024,
    container.shrink_to_fit(),
    std::move(container)
)
```

### SFINAE and Concept Integration

```cpp
// Conditional constraint application
template<typename T>
auto smart_convert(T value) XIEITE_ARROW_IF(
    std::is_floating_point_v<T>,
    check_precision_loss(value),
    static_cast<int>(value)
) requires (std::is_arithmetic_v<T>)

// Conditional concept enforcement
template<typename Container>
auto safe_access(Container& c, std::size_t index) XIEITE_ARROW_IF(
    has_bounds_checking<Container>,
    c.at(index),                    // Bounds-checked access
    c[index]                        // Direct access
)
```

### Compile-Time Optimization Patterns

```cpp
// Platform-specific optimizations
template<typename T>
auto optimized_copy(const T* src, T* dest, std::size_t count) XIEITE_ARROW_IF(
    std::is_trivially_copyable_v<T> && (sizeof(T) % alignof(T) == 0),
    std::memcpy(dest, src, count * sizeof(T)),
    std::copy(src, src + count, dest)
)

// Architecture-specific implementations
template<typename T>
auto fast_multiply(T a, T b) XIEITE_ARROW_IF(
    TARGET_ARCH_X86_64,
    use_x86_intrinsics(a, b),
    a * b
)
```

## Exception Safety Analysis

### Noexcept Specification Logic

The macro's noexcept specification implements sophisticated logic:

```cpp
noexcept((!static_cast<bool>(_cond) || noexcept(_then)) __VA_OPT__(&& noexcept(__VA_ARGS__)))
```

This evaluates to `true` when:
1. **Condition is false** (then-branch never executes), AND
2. **Return expression is noexcept**

OR when:
1. **Condition is true**, AND
2. **Then-statement is noexcept**, AND
3. **Return expression is noexcept**

### Exception Safety Examples

```cpp
// Safe arithmetic operations
template<typename T>
auto safe_increment(T& value) XIEITE_ARROW_IF(
    std::is_arithmetic_v<T>,
    ++value,                        // noexcept for arithmetic types
    value                           // noexcept return
) // Entire function is noexcept for arithmetic types

// Potentially throwing operations
template<typename T>
auto risky_operation(T value) XIEITE_ARROW_IF(
    needs_validation<T>,
    validate_expensive(value),      // May throw
    process_value(value)            // May throw
) // noexcept(false) when validation is needed
```

## Practical Applications

### Debug and Release Builds

```cpp
// Conditional debugging without runtime overhead
template<typename T>
auto debug_process(T value) XIEITE_ARROW_IF(
    DEBUG_BUILD,
    log_processing_step(value),
    expensive_computation(value)
)

// Conditional profiling
template<typename F, typename... Args>
auto profile_call(F&& func, Args&&... args) XIEITE_ARROW_IF(
    PROFILING_ENABLED,
    start_timer(),
    std::forward<F>(func)(std::forward<Args>(args)...)
)
```

### Resource Management

```cpp
// Conditional resource acquisition
template<typename Resource>
auto acquire_resource() XIEITE_ARROW_IF(
    Resource::requires_initialization,
    Resource::initialize_global_state(),
    Resource{}
)

// Conditional cleanup with RAII
template<typename T>
auto scoped_operation(T& resource) XIEITE_ARROW_IF(
    requires_locking<T>,
    resource.lock(),
    perform_operation(resource)
)
```

### Type-Safe Programming

```cpp
// Conditional type conversions
template<typename From, typename To>
auto safe_cast(From value) XIEITE_ARROW_IF(
    std::is_convertible_v<From, To> && sizeof(From) <= sizeof(To),
    verify_no_precision_loss(value),
    static_cast<To>(value)
)

// Conditional algorithm selection
template<typename Iterator>
auto efficient_sort(Iterator first, Iterator last) XIEITE_ARROW_IF(
    std::is_same_v<typename std::iterator_traits<Iterator>::iterator_category,
                   std::random_access_iterator_tag>,
    std::sort(first, last),
    std::stable_sort(first, last)
)
```

## Integration with XIEITE Systems

### With Conditional Compilation

```cpp
#include <xieite/pp/conditional.hpp>
#include <xieite/pp/arrow.hpp>

template<typename T>
auto platform_optimized(T value) XIEITE_ARROW_IF(
    XIEITE_PLATFORM_TYPE_WINDOWS,
    use_windows_api(value),
    generic_implementation(value)
)
```

### With Type Traits

```cpp
#include <xieite/trait/is_numeric.hpp>
#include <xieite/pp/arrow.hpp>

template<typename T>
auto numeric_operation(T value) XIEITE_ARROW_IF(
    xieite::is_numeric<T>,
    validate_numeric_range(value),
    compute_result(value)
)
```

### With Mathematical Functions

```cpp
#include <xieite/math/abs.hpp>
#include <xieite/pp/arrow.hpp>

template<typename T>
auto safe_absolute(T value) XIEITE_ARROW_IF(
    std::is_signed_v<T>,
    check_overflow_potential(value),
    xieite::abs(value)
)
```

## Performance Characteristics

### Compile-Time Optimization

The macro enables several compiler optimizations:

1. **Dead Code Elimination**: False branches are completely removed
2. **Constant Folding**: Compile-time conditions enable aggressive optimization
3. **Inlining**: Simple expressions typically inline completely
4. **Branch Prediction**: Static branches improve runtime performance

### Zero-Cost Abstractions

```cpp
// Generates optimal assembly for each case
template<typename T>
auto optimized_access(T* ptr, std::size_t index) XIEITE_ARROW_IF(
    std::is_const_v<T>,
    prefetch_readonly(ptr + index),     // Optimizes to prefetch instruction
    ptr[index]                          // Optimizes to direct memory access
)
```

## Best Practices

### 1. Use for Compile-Time Conditions

```cpp
// Good: Compile-time condition
template<typename T>
auto func(T value) XIEITE_ARROW_IF(
    std::is_arithmetic_v<T>,        // Compile-time constant
    arithmetic_validation(value),
    value
)

// Avoid: Runtime conditions
template<typename T>
auto func(T value, bool runtime_flag) XIEITE_ARROW_IF(
    runtime_flag,                   // Runtime value - defeats optimization
    some_operation(value),
    value
)
```

### 2. Keep Side Effects Simple

```cpp
// Good: Simple side effects
auto func(int x) XIEITE_ARROW_IF(
    DEBUG_MODE,
    std::cout << x,                 // Simple output
    x * 2
)

// Consider regular function for complex side effects
auto func(int x) {
    if constexpr (DEBUG_MODE) {
        complex_logging_setup();
        detailed_trace(x);
        update_statistics();
    }
    return x * 2;
}
```

### 3. Ensure Type Compatibility

```cpp
// Good: Consistent return types
template<typename T>
auto process(T value) XIEITE_ARROW_IF(
    needs_preprocessing<T>,
    preprocess(value),              // Side effect
    transform(value)                // Return value of compatible type
)

// Problematic: Incompatible return types in complex scenarios
```

### 4. Document Conditional Behavior

```cpp
/**
 * @brief Processes value with optional validation
 * @param value Input value
 * @return Processed value
 * @note When T is arithmetic, performs range validation before processing
 */
template<typename T>
auto safe_process(T value) XIEITE_ARROW_IF(
    std::is_arithmetic_v<T>,
    validate_range(value),
    process_value(value)
)
```

## Limitations and Considerations

### 1. Side Effect Ordering

The macro enforces a specific execution order that may not suit all use cases:

```cpp
// Fixed order: condition check → then statement → return expression
// Cannot interleave side effects with return computation
```

### 2. Complex Conditional Logic

For multiple conditions, consider alternative approaches:

```cpp
// Limited: Single condition
auto func(T value) XIEITE_ARROW_IF(cond, then_stmt, return_expr)

// Better for complex logic: Traditional function
auto func(T value) {
    if constexpr (cond1) { stmt1; }
    if constexpr (cond2) { stmt2; }
    return complex_computation(value);
}
```

### 3. Error Message Clarity

Macro expansion can make error messages less clear:

```cpp
// Error messages may reference macro internals rather than user code
template<typename T>
auto func(T value) XIEITE_ARROW_IF(
    invalid_condition,              // Error may be cryptic
    invalid_statement,
    invalid_return
)
```

### 4. Template Instantiation Context

The requires clause may interact unexpectedly with SFINAE:

```cpp
// May cause SFINAE issues in complex template hierarchies
template<template<typename> class Container, typename T>
auto process(Container<T> c) XIEITE_ARROW_IF(
    has_member_function<Container<T>>,
    c.special_operation(),
    c.standard_operation()
)
```

## Comparison with Other Control Flow Macros

| Macro | Conditional Execution | Return Behavior | Primary Use Case |
|-------|----------------------|-----------------|------------------|
| `XIEITE_ARROW_IF` | Compile-time if | Always returns | Conditional side effects |
| `XIEITE_ARROW_CHOOSE` | Compile-time choice | Conditional return | Alternative values |
| `XIEITE_ARROW_TRY` | Exception handling | Error recovery | Exception safety |

### Selection Guidelines

```cpp
// Use XIEITE_ARROW_IF when:
// 1. Need conditional side effects before return
// 2. Always want to return the same expression
// 3. Side effects are simple statements

// Use XIEITE_ARROW_CHOOSE when:
// 1. Need to choose between different return values
// 2. No side effects needed
// 3. Branching based on compile-time conditions
```

---

*See also: [XIEITE_ARROW_CHOOSE](arrow_choose.md) | [XIEITE_ARROW_TRY](arrow_try.md) | [Arrow Macro Family](../arrow_macros.md)*