# XIEITE_ARROW_DECL

The `XIEITE_ARROW_DECL` macro is a specialized parameter declaration variant of the XIEITE Arrow macro family that enables concise function definitions with explicit parameter specification. This macro combines arrow function syntax with sophisticated parameter handling, providing a powerful tool for template metaprogramming with advanced parameter patterns including variadic templates and perfect forwarding.

## Implementation

Located in `include/xieite/pp/arrow.hpp` at lines 45-51:

```cpp
#define XIEITE_ARROW_DECL(_params, ...) \
    XIEITE_EVAL( \
        noexcept(requires DETAIL_XIEITE_ARROW_PARAMS(XIEITE_UNWRAP(_params)) { requires(noexcept(__VA_ARGS__)); }) \
        -> decltype(auto) \
        requires(requires DETAIL_XIEITE_ARROW_PARAMS(XIEITE_UNWRAP(_params)) { __VA_ARGS__; }) \
        { return __VA_ARGS__; } \
    )
```

## Architecture Analysis

### Macro Parameter Structure

The `XIEITE_ARROW_DECL` macro accepts two primary components:

1. **`_params`**: Parameter declaration specification (processed with `XIEITE_UNWRAP`)
2. **`__VA_ARGS__`**: Function body expression

### Helper Macro Integration

The macro relies on several helper macros:

- **`XIEITE_EVAL`**: Ensures proper macro expansion order
- **`DETAIL_XIEITE_ARROW_PARAMS`**: Processes parameter declarations
- **`XIEITE_UNWRAP`**: Removes parentheses from parameter specifications

### Parameter Processing Mechanism

Located at line 61 in the same file:

```cpp
#define DETAIL_XIEITE_ARROW_PARAMS(...) __VA_OPT__((DETAIL_XIEITE_EACH_HELPER(DETAIL_XIEITE_ARROW_PARAM, __VA_ARGS__)))
#define DETAIL_XIEITE_ARROW_PARAM(_param) XIEITE_IF(XIEITE_WRAPPED(_param))(decltype _param&&... XIEITE_UNWRAP(_param))(decltype(_param)&& _param)
```

This creates sophisticated parameter handling that supports:
- Perfect forwarding with `&&` references
- Variadic template expansion with `...`
- Conditional parameter processing based on wrapping

## Template Instantiation Mechanics

```cpp
// Usage example:
template<typename... Args>
auto variadic_function XIEITE_ARROW_DECL(
    (Args, args),                             // Parameter specification
    process_all(std::forward<Args>(args)...)  // Function body
)

// Expands approximately to:
template<typename... Args>
auto variadic_function(Args&&... args)
    noexcept(requires(Args&&... args) { requires(noexcept(process_all(std::forward<Args>(args)...))); })
    -> decltype(auto)
    requires(requires(Args&&... args) { process_all(std::forward<Args>(args)...); })
{
    return process_all(std::forward<Args>(args)...);
}
```

## Parameter Declaration Patterns

### Simple Parameter Declaration

```cpp
// Basic parameter with perfect forwarding
template<typename T>
auto simple_wrapper XIEITE_ARROW_DECL(
    (T, value),                               // Parameter: T&& value
    transform(std::forward<T>(value))
)

// Multiple parameters
template<typename T, typename U>
auto binary_operation XIEITE_ARROW_DECL(
    ((T, a), (U, b)),                        // Parameters: T&& a, U&& b
    combine(std::forward<T>(a), std::forward<U>(b))
)
```

### Variadic Parameter Patterns

```cpp
// Variadic template with pack expansion
template<typename... Types>
auto variadic_processor XIEITE_ARROW_DECL(
    (Types, values),                          // Expands to: Types&&... values
    fold_operation(std::forward<Types>(values)...)
)

// Mixed parameters with variadic pack
template<typename First, typename... Rest>
auto mixed_params XIEITE_ARROW_DECL(
    ((First, first), (Rest, rest)),          // First&& first, Rest&&... rest
    process_with_head(std::forward<First>(first), std::forward<Rest>(rest)...)
)
```

### Complex Parameter Specifications

```cpp
// Nested template parameters
template<template<typename> class Container, typename T>
auto container_operation XIEITE_ARROW_DECL(
    (Container<T>, container),                // Container<T>&& container
    analyze_container(std::forward<Container<T>>(container))
)

// Function object parameters
template<typename Callable, typename... Args>
auto invoke_wrapper XIEITE_ARROW_DECL(
    ((Callable, func), (Args, args)),        // Callable&& func, Args&&... args
    std::invoke(std::forward<Callable>(func), std::forward<Args>(args)...)
)
```

## Advanced Usage Patterns

### SFINAE-Friendly Parameter Constraints

```cpp
// Parameter-dependent SFINAE
template<typename T>
auto conditional_operation XIEITE_ARROW_DECL(
    (T, value),
    std::conditional_t<std::is_arithmetic_v<T>,
        arithmetic_process(std::forward<T>(value)),
        generic_process(std::forward<T>(value))
    >
)

// Concept-based parameter validation
template<typename Container>
    requires requires { typename Container::value_type; }
auto container_sum XIEITE_ARROW_DECL(
    (Container, c),
    std::accumulate(c.begin(), c.end(), typename Container::value_type{})
)
```

### Perfect Forwarding Patterns

```cpp
// Universal reference forwarding
template<typename T>
auto perfect_forward XIEITE_ARROW_DECL(
    (T, obj),                                 // T&& obj with perfect forwarding
    process_object(std::forward<T>(obj))
)

// Selective forwarding based on type properties
template<typename T>
auto smart_forward XIEITE_ARROW_DECL(
    (T, value),
    std::conditional_t<std::is_rvalue_reference_v<T>,
        move_process(std::forward<T>(value)),
        copy_process(std::forward<T>(value))
    >
)
```

### Functional Programming Integration

```cpp
// Currying with explicit parameter specification
template<typename F, typename... CurriedArgs>
auto curry_function XIEITE_ARROW_DECL(
    ((F, func), (CurriedArgs, curried_args)),
    [func = std::forward<F>(func), curried_args...]<typename... NewArgs>(NewArgs&&... new_args) {
        return std::invoke(func, curried_args..., std::forward<NewArgs>(new_args)...);
    }
)

// Higher-order function patterns
template<typename Transformer, typename... Inputs>
auto transform_all XIEITE_ARROW_DECL(
    ((Transformer, transform), (Inputs, inputs)),
    std::make_tuple(std::invoke(transform, std::forward<Inputs>(inputs))...)
)
```

## Integration with XIEITE Systems

### With Type Traits

```cpp
#include <xieite/trait/is_container.hpp>
#include <xieite/pp/arrow.hpp>

template<typename Container>
    requires xieite::is_container<Container>
auto safe_container_access XIEITE_ARROW_DECL(
    ((Container, c), (std::size_t, index)),
    index < c.size() ? std::optional{c[index]} : std::nullopt
)
```

### With Mathematical Functions

```cpp
#include <xieite/math/abs.hpp>
#include <xieite/pp/arrow.hpp>

template<typename T>
    requires std::is_arithmetic_v<T>
auto mathematical_operation XIEITE_ARROW_DECL(
    ((T, a), (T, b)),
    xieite::abs(a) + xieite::abs(b)
)
```

### With Functional Utilities

```cpp
#include <xieite/fn/curry.hpp>
#include <xieite/pp/arrow.hpp>

template<typename F, typename Arg>
auto curry_wrapper XIEITE_ARROW_DECL(
    ((F, func), (Arg, arg)),
    xieite::curry(std::forward<F>(func))(std::forward<Arg>(arg))
)
```

## Exception Safety and Noexcept Specification

### Sophisticated Noexcept Calculation

The macro's noexcept specification evaluates parameter-dependent expressions:

```cpp
noexcept(requires DETAIL_XIEITE_ARROW_PARAMS(XIEITE_UNWRAP(_params)) { requires(noexcept(__VA_ARGS__)); })
```

This ensures that the function is noexcept only when:
1. **Parameter types are properly deducible**
2. **Function body expression is noexcept for those parameter types**

### Exception Safety Examples

```cpp
// Conditionally noexcept based on parameter operations
template<typename T>
auto safe_operation XIEITE_ARROW_DECL(
    (T, value),
    safe_transform(std::forward<T>(value))    // noexcept if safe_transform is noexcept
)

// Exception safety with multiple parameters
template<typename T, typename U>
auto binary_safe XIEITE_ARROW_DECL(
    ((T, a), (U, b)),
    combine_safely(std::forward<T>(a), std::forward<U>(b))
) // noexcept depends on combine_safely and parameter types
```

## Performance Characteristics

### Zero-Cost Parameter Forwarding

The macro generates optimal parameter passing code:

```cpp
// Generates efficient forwarding without overhead
template<typename Container>
auto efficient_access XIEITE_ARROW_DECL(
    (Container, c),
    c.front()                                 // Direct access, perfect forwarding
)
```

### Compile-Time Parameter Analysis

```cpp
// Enables compile-time optimizations based on parameter types
template<typename T>
auto optimized_process XIEITE_ARROW_DECL(
    (T, value),
    std::conditional_t<sizeof(T) <= sizeof(void*),
        process_small(std::forward<T>(value)),   // Optimized for small types
        process_large(std::forward<T>(value))    // Optimized for large types
    >
)
```

## Best Practices

### 1. Use Appropriate Parameter Wrapping

```cpp
// Good: Properly wrapped parameters
template<typename T, typename U>
auto good_params XIEITE_ARROW_DECL(
    ((T, first), (U, second)),              // Clear parameter separation
    process(std::forward<T>(first), std::forward<U>(second))
)

// Problematic: Unprotected parameter specifications
template<typename T>
auto risky_params XIEITE_ARROW_DECL(
    (std::pair<T, int>, p),                 // Comma in type may cause issues
    process_pair(std::forward<std::pair<T, int>>(p))
)
```

### 2. Explicit Perfect Forwarding

```cpp
// Good: Explicit forwarding for clarity
template<typename T>
auto explicit_forward XIEITE_ARROW_DECL(
    (T, value),
    process(std::forward<T>(value))         // Clear forwarding intent
)

// Avoid: Implicit forwarding that may be unclear
template<typename T>
auto implicit_forward XIEITE_ARROW_DECL(
    (T, value),
    process(value)                          // May not forward correctly
)
```

### 3. Type Alias for Complex Types

```cpp
// Good: Use type aliases for complex parameter types
template<typename Key, typename Value>
using map_type = std::unordered_map<Key, Value>;

template<typename Key, typename Value>
auto process_map XIEITE_ARROW_DECL(
    (map_type<Key, Value>, m),
    analyze_map(std::forward<map_type<Key, Value>>(m))
)
```

### 4. Document Parameter Expectations

```cpp
/**
 * @brief Processes container with perfect forwarding
 * @param container Container to process (any STL-compatible container)
 * @return Processing result
 * @note Uses perfect forwarding to preserve value category
 */
template<typename Container>
auto documented_processor XIEITE_ARROW_DECL(
    (Container, container),
    std::accumulate(container.begin(), container.end(), 0)
)
```

## Limitations and Considerations

### 1. Complex Parameter Syntax

The parameter specification syntax can become complex:

```cpp
// Complex nested specifications may be hard to read
template<template<typename...> class Container, typename... Types>
auto complex_spec XIEITE_ARROW_DECL(
    (Container<Types...>, c),               // Complex template parameter
    process_complex(std::forward<Container<Types...>>(c))
)
```

### 2. Macro Expansion Debugging

Parameter processing through macros can complicate debugging:

```cpp
// Error messages may reference internal macro details
template<typename T>
auto debug_difficult XIEITE_ARROW_DECL(
    (T, invalid_param_spec),                // Errors may be cryptic
    process(std::forward<T>(invalid_param_spec))
)
```

### 3. Template Instantiation Cost

Complex parameter specifications may impact compilation time:

```cpp
// Many parameters with complex types increase compilation cost
template<typename A, typename B, typename C, typename D>
auto many_params XIEITE_ARROW_DECL(
    ((A, a), (B, b), (C, c), (D, d)),      // Each parameter adds complexity
    complex_operation(std::forward<A>(a), std::forward<B>(b), std::forward<C>(c), std::forward<D>(d))
)
```

### 4. Perfect Forwarding Limitations

Perfect forwarding has inherent limitations that the macro inherits:

```cpp
// Cannot perfectly forward template template parameters
template<template<typename> class Template>
auto template_forward XIEITE_ARROW_DECL(
    (Template<int>, t),                     // Template types can't be perfectly forwarded
    process_template(std::forward<Template<int>>(t))
)
```

## Comparison with Other Arrow Macros

| Macro | Parameter Handling | Declaration Style | Primary Use Case |
|-------|-------------------|-------------------|------------------|
| `XIEITE_ARROW` | Traditional | Standard syntax | Simple functions |
| `XIEITE_ARROW_DECL` | **Explicit specification** | **Advanced syntax** | **Complex parameters** |
| `XIEITE_ARROW_CTOR` | Constructor parameters | Constructor syntax | Class constructors |

### Selection Guidelines

```cpp
// Use XIEITE_ARROW_DECL when:
// 1. Need explicit parameter control
// 2. Using variadic templates
// 3. Require perfect forwarding
// 4. Complex parameter types

// Example: Complex parameters (use DECL)
template<typename... Args>
auto variadic_func XIEITE_ARROW_DECL((Args, args), process(std::forward<Args>(args)...))

// Example: Simple function (use ARROW)
auto simple(int x) XIEITE_ARROW(x * 2)
```

## Advanced Integration Examples

### With Standard Library Algorithms

```cpp
template<typename Container, typename Predicate>
auto find_if_wrapper XIEITE_ARROW_DECL(
    ((Container, c), (Predicate, pred)),
    std::find_if(c.begin(), c.end(), std::forward<Predicate>(pred))
)
```

### With Custom Iterator Types

```cpp
template<typename Iterator>
auto iterator_processor XIEITE_ARROW_DECL(
    ((Iterator, first), (Iterator, last)),
    std::distance(first, last)
)
```

### With Function Objects

```cpp
template<typename Callable, typename... Args>
auto invoke_with_timing XIEITE_ARROW_DECL(
    ((Callable, func), (Args, args)),
    time_execution([&] { return std::invoke(std::forward<Callable>(func), std::forward<Args>(args)...); })
)
```

---

*See also: [XIEITE_ARROW_CTOR](arrow_ctor.md) | [Perfect Forwarding Patterns](../template_patterns.md) | [Parameter Pack Utilities](../../categories/meta/)*