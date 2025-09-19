# SFINAE Helpers

## Overview

XIEITE provides SFINAE (Substitution Failure Is Not An Error) helper traits that enable safe type manipulations and conditional template instantiation. These helpers allow graceful handling of type operations that might otherwise cause compilation errors, providing fallback behaviors when operations are not valid for certain types.

## Core SFINAE Patterns in XIEITE

### Try Operations

The `try_*` family of traits attempts type operations and provides fallbacks:

```cpp
// try_signed - Attempts to make a type signed, fallback to original
template<typename T>
using try_signed = std::conditional_t<
    xieite::is_unsigned<T>,
    std::make_signed<T>,
    std::type_identity<T>
>::type;

// try_unsigned - Attempts to make a type unsigned, fallback to original
template<typename T>
using try_unsigned = std::conditional_t<
    xieite::is_signed<T>,
    std::make_unsigned<T>,
    std::type_identity<T>
>::type;
```

### Maybe Types

Conditional type wrappers based on properties:

```cpp
// maybe_ref - Conditionally wrap in reference_wrapper
template<typename T>
using maybe_ref = std::conditional_t<
    std::is_reference_v<T>,
    std::reference_wrapper<std::remove_reference_t<T>>,
    T
>;

// maybe_base - Extract base type if derived
template<typename T, typename Base>
using maybe_base = std::conditional_t<
    std::is_base_of_v<Base, T>,
    Base,
    T
>;
```

## SFINAE Detection Patterns

### Concept-Based Detection

XIEITE primarily uses C++20 concepts for detection, which are inherently SFINAE-friendly:

```cpp
// Detection via requires expression
template<typename T>
concept has_value_type = requires {
    typename T::value_type;
};

// Detection via valid expression
template<typename T>
concept has_size = requires(T t) {
    { t.size() } -> std::convertible_to<std::size_t>;
};

// Detection via nested requirements
template<typename T>
concept serializable = requires(T t) {
    { t.serialize() } -> std::convertible_to<std::string>;
    requires requires(std::string s) {
        { T::deserialize(s) } -> std::same_as<T>;
    };
};
```

### Traditional SFINAE Patterns

For compatibility and special cases, traditional SFINAE patterns are also used:

```cpp
// Detection using void_t pattern
template<typename T, typename = void>
struct has_typedef_member : std::false_type {};

template<typename T>
struct has_typedef_member<T, std::void_t<typename T::type>>
    : std::true_type {};

// Detection using decltype
template<typename T>
auto has_begin_impl(int) -> decltype(
    std::declval<T>().begin(),
    std::true_type{}
);

template<typename T>
auto has_begin_impl(...) -> std::false_type;

template<typename T>
using has_begin = decltype(has_begin_impl<T>(0));
```

## Safe Type Transformations

### Conditional Transformations

Operations that only apply when valid:

```cpp
// Add pointer only if not already pointer
template<typename T>
using safe_add_pointer = std::conditional_t<
    std::is_pointer_v<T>,
    T,
    std::add_pointer_t<T>
>;

// Remove extent only if array
template<typename T>
using safe_remove_extent = std::conditional_t<
    std::is_array_v<T>,
    std::remove_extent_t<T>,
    T
>;

// Decay only if not already decayed
template<typename T>
using safe_decay = std::conditional_t<
    xieite::is_decayed<T>,
    T,
    std::decay_t<T>
>;
```

### Fallback Type Selection

Providing alternative types when operations fail:

```cpp
// Select first valid type from list
template<typename Default, typename... Ts>
struct first_valid {
    using type = Default;
};

template<typename Default, typename T, typename... Rest>
    requires std::is_complete_v<T>
struct first_valid<Default, T, Rest...> {
    using type = T;
};

template<typename Default, typename T, typename... Rest>
    requires (!std::is_complete_v<T>)
struct first_valid<Default, T, Rest...>
    : first_valid<Default, Rest...> {};
```

## Expression SFINAE Helpers

### Valid Expression Detection

```cpp
// Check if expression is valid
template<typename T, typename... Args>
concept constructible_from = requires {
    T{std::declval<Args>()...};
};

// Check if operation is valid
template<typename T, typename U>
concept addable = requires(T t, U u) {
    { t + u } -> std::convertible_to<std::common_type_t<T, U>>;
};

// Check if method exists with specific signature
template<typename T>
concept has_const_size = requires(const T& t) {
    { t.size() } -> std::same_as<std::size_t>;
};
```

### Nested Type Detection

```cpp
// Check for nested types
template<typename T>
concept has_iterator = requires {
    typename T::iterator;
    typename T::const_iterator;
};

// Check for specific nested type properties
template<typename T>
concept has_standard_typedefs = requires {
    typename T::value_type;
    typename T::size_type;
    typename T::difference_type;
    typename T::reference;
    typename T::const_reference;
    typename T::pointer;
    typename T::const_pointer;
};
```

## Advanced SFINAE Patterns

### Substitution Failure Detection

```cpp
// Detect if substitution succeeds
template<template<typename> class Op, typename T>
concept substitutable = requires {
    typename Op<T>;
};

// Example usage
template<typename T>
using make_signed_op = std::make_signed<T>;

template<typename T>
    requires substitutable<make_signed_op, T>
using safe_make_signed = std::make_signed_t<T>;
```

### Overload Resolution Control

```cpp
// Priority tags for overload selection
template<int N> struct priority : priority<N-1> {};
template<> struct priority<0> {};

// Use priority for SFINAE-based overload selection
template<typename T>
auto process_impl(T&& t, priority<2>)
    -> decltype(t.specialized_process()) {
    return t.specialized_process();
}

template<typename T>
auto process_impl(T&& t, priority<1>)
    -> decltype(t.general_process()) {
    return t.general_process();
}

template<typename T>
auto process_impl(T&& t, priority<0>) {
    return default_process(t);
}

template<typename T>
auto process(T&& t) {
    return process_impl(std::forward<T>(t), priority<2>{});
}
```

### Conditional Member Types

```cpp
// Conditionally define member types
template<typename T>
struct conditional_traits {
    // Only define if T is integral
    template<typename U = T>
        requires std::integral<U>
    using unsigned_type = std::make_unsigned_t<U>;

    // Only define if T has value_type
    template<typename U = T>
        requires requires { typename U::value_type; }
    using element_type = typename U::value_type;

    // Provide fallback for non-containers
    using size_type = std::conditional_t<
        requires { typename T::size_type; },
        typename T::size_type,
        std::size_t
    >;
};
```

## Usage Examples

### Safe Type Operations

```cpp
#include <xieite/trait/try_signed.hpp>
#include <xieite/trait/try_unsigned.hpp>

// Safe conversion to signed - no error if already signed
template<typename T>
auto make_signed_safe(T value) {
    using signed_type = xieite::try_signed<T>;
    return static_cast<signed_type>(value);
}

// Works with any numeric type
auto s1 = make_signed_safe(42u);    // int
auto s2 = make_signed_safe(42);     // int (unchanged)
auto s3 = make_signed_safe(42.0);   // double (unchanged)
```

### Conditional Functionality

```cpp
// Enable method only if type supports it
template<typename Container>
class wrapper {
    Container data;

public:
    // Only available if Container has reserve
    template<typename C = Container>
        requires requires(C& c) { c.reserve(1); }
    void reserve(std::size_t n) {
        data.reserve(n);
    }

    // Always available
    auto size() const {
        if constexpr (requires { data.size(); }) {
            return data.size();
        } else {
            return std::size_t(1);  // Fallback
        }
    }
};
```

### Type Selection

```cpp
// Select appropriate storage type
template<typename T>
using storage_type = std::conditional_t<
    sizeof(T) <= sizeof(void*) && std::is_trivially_copyable_v<T>,
    T,                              // Store by value if small
    std::conditional_t<
        std::is_move_constructible_v<T>,
        std::unique_ptr<T>,         // Use unique_ptr if movable
        std::shared_ptr<T>          // Use shared_ptr otherwise
    >
>;
```

## Integration with Concepts

### Concept-Based SFINAE

```cpp
// Combine multiple requirements
template<typename T>
concept container_like = requires(T t) {
    typename T::value_type;
    typename T::iterator;
    { t.begin() } -> std::same_as<typename T::iterator>;
    { t.end() } -> std::same_as<typename T::iterator>;
    { t.size() } -> std::convertible_to<std::size_t>;
};

// Use in SFINAE context
template<container_like C>
auto process_container(C&& c) {
    // Container-specific processing
}

template<typename T>
    requires (!container_like<T>)
auto process_container(T&& t) {
    // Non-container fallback
}
```

### Subsumption Control

```cpp
// More specific concept subsumes less specific
template<typename T>
concept has_member_func = requires(T t) {
    t.func();
};

template<typename T>
concept has_const_member_func = has_member_func<T> &&
    requires(const T t) {
        t.func();
    };

// Overload resolution prefers more specific
template<has_member_func T>
void call_func(T& t) { t.func(); }

template<has_const_member_func T>  // Preferred when applicable
void call_func(const T& t) { t.func(); }
```

## Common Patterns

### Detection Idiom

```cpp
// Generic detection template
template<typename T, template<typename...> class Op, typename... Args>
concept detected = requires {
    typename Op<T, Args...>;
};

// Specific detections
template<typename T>
using has_value_type_t = typename T::value_type;

template<typename T>
concept has_value_type = detected<T, has_value_type_t>;
```

### Valid If Pattern

```cpp
// Operation valid only under certain conditions
template<typename T>
    requires std::integral<T> || std::floating_point<T>
auto safe_divide(T a, T b) -> std::optional<T> {
    if (b != T{0}) {
        return a / b;
    }
    return std::nullopt;
}
```

### Fallback Chain

```cpp
// Try operations in order until one succeeds
template<typename T>
auto get_size(const T& t) {
    if constexpr (requires { t.size(); }) {
        return t.size();
    } else if constexpr (requires { t.length(); }) {
        return t.length();
    } else if constexpr (requires { std::size(t); }) {
        return std::size(t);
    } else if constexpr (std::is_array_v<T>) {
        return std::extent_v<T>;
    } else {
        return std::size_t(1);
    }
}
```

## Best Practices

### 1. Prefer Concepts to Traditional SFINAE

```cpp
// Good: Clear and composable
template<typename T>
concept arithmetic = std::integral<T> || std::floating_point<T>;

// Avoid: Complex and hard to read
template<typename T, typename = std::enable_if_t<
    std::is_integral_v<T> || std::is_floating_point_v<T>>>
void old_style(T t);
```

### 2. Use if constexpr for Runtime Branches

```cpp
template<typename T>
auto process(T&& t) {
    if constexpr (requires { t.optimize(); }) {
        return t.optimize();
    } else {
        return default_process(t);
    }
}
```

### 3. Provide Clear Fallbacks

```cpp
template<typename T>
using safe_value_type = std::conditional_t<
    requires { typename T::value_type; },
    typename T::value_type,
    T  // Clear fallback: the type itself
>;
```

### 4. Document SFINAE Behavior

```cpp
// Returns iterator to found element, or end() if not found
// Note: Only participates in overload resolution if T has find()
template<typename T, typename Key>
    requires requires(T t, Key k) { t.find(k); }
auto safe_find(T& container, const Key& key) {
    return container.find(key);
}
```

## Common Pitfalls

### 1. Immediate Context Rule

```cpp
// Bad: Error not in immediate context
template<typename T>
concept bad_concept = requires {
    T::type::value;  // Error if T::type doesn't have 'value'
};

// Good: All checks in immediate context
template<typename T>
concept good_concept = requires {
    typename T::type;
    requires requires { T::type::value; };
};
```

### 2. Conflicting Constraints

```cpp
// Bad: Ambiguous overloads
template<std::integral T> void func(T);
template<std::signed_integral T> void func(T);  // Ambiguous!

// Good: Mutually exclusive
template<std::unsigned_integral T> void func(T);
template<std::signed_integral T> void func(T);  // Clear distinction
```

### 3. Missing Fallbacks

```cpp
// Bad: No fallback for non-arithmetic types
template<typename T>
using make_signed_bad = std::make_signed_t<T>;  // Error if T not integral

// Good: Safe fallback
template<typename T>
using make_signed_good = xieite::try_signed<T>;  // Returns T if not applicable
```

## Performance Considerations

- **Compile-time cost**: SFINAE can increase compilation time
- **No runtime overhead**: All SFINAE resolution happens at compile time
- **Template instantiation**: Each SFINAE check may instantiate templates
- **Concept caching**: Concepts are cached, reducing redundant evaluations

## Summary

XIEITE's SFINAE helpers provide safe, expressive ways to handle conditional type operations and template specialization. By combining modern C++20 concepts with traditional SFINAE techniques, the library offers robust tools for template metaprogramming that gracefully handle edge cases and provide clear fallback behaviors. The emphasis on safety and clarity makes complex template code more maintainable and less error-prone.