# SFINAE Patterns

SFINAE (Substitution Failure Is Not An Error) is a fundamental C++ template metaprogramming technique that XIEITE leverages extensively for compile-time type introspection and conditional template instantiation. While C++20 concepts provide a cleaner alternative, XIEITE maintains sophisticated SFINAE patterns for compatibility and specific use cases where concepts alone are insufficient.

## Understanding SFINAE in XIEITE

SFINAE allows templates to be conditionally removed from overload resolution based on whether certain type operations are valid. XIEITE uses this principle to:

1. **Detect type properties** without causing compilation errors
2. **Enable conditional functionality** based on type capabilities
3. **Provide fallback implementations** when primary approaches fail
4. **Create sophisticated type trait implementations**

## Core SFINAE Patterns

### Detection Idiom

XIEITE implements the detection idiom for type introspection:

```cpp
// Base detection pattern from XIEITE's trait system
namespace detail {
    template<typename T, typename = void>
    struct has_member_impl : std::false_type {};

    template<typename T>
    struct has_member_impl<T, std::void_t<decltype(std::declval<T>().member())>>
        : std::true_type {};
}

template<typename T>
inline constexpr bool has_member = detail::has_member_impl<T>::value;
```

### Expression SFINAE

XIEITE uses expression SFINAE for fine-grained control:

```cpp
// Pattern for detecting valid expressions
template<typename T>
auto has_size_impl(int) -> decltype(std::declval<T>().size(), std::true_type{});

template<typename T>
auto has_size_impl(...) -> std::false_type;

template<typename T>
inline constexpr bool has_size = decltype(has_size_impl<T>(0))::value;
```

### Return Type SFINAE

Pattern for conditional return types based on type properties:

```cpp
// From XIEITE's functional utilities
template<typename F, typename... Args>
auto invoke_if_callable(F&& f, Args&&... args)
    -> std::enable_if_t<
        std::is_invocable_v<F, Args...>,
        std::invoke_result_t<F, Args...>
    >
{
    return std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
}

template<typename F, typename... Args>
auto invoke_if_callable(F&&, Args&&...)
    -> std::enable_if_t<
        !std::is_invocable_v<F, Args...>,
        std::nullopt_t
    >
{
    return std::nullopt;
}
```

## Advanced SFINAE Techniques

### Conjunction and Disjunction Patterns

XIEITE combines multiple SFINAE conditions:

```cpp
// Multiple requirement checking
template<typename T>
using is_container_like = std::conjunction<
    has_begin<T>,
    has_end<T>,
    has_size<T>
>;

// Alternative requirements
template<typename T>
using is_numeric = std::disjunction<
    std::is_integral<T>,
    std::is_floating_point<T>,
    has_numeric_operations<T>
>;
```

### Recursive SFINAE

Pattern for recursive type introspection:

```cpp
// Detect nested types recursively
template<typename T, typename = void>
struct has_nested_value_type : std::false_type {};

template<typename T>
struct has_nested_value_type<T, std::void_t<typename T::value_type>>
    : has_nested_value_type<typename T::value_type> {};

template<>
struct has_nested_value_type<void> : std::true_type {};
```

### SFINAE-Friendly Function Objects

XIEITE patterns for SFINAE-friendly callables:

```cpp
// Function object with SFINAE-enabled operator()
struct safe_dereference {
    template<typename T>
    auto operator()(T&& t) const
        -> decltype(*std::forward<T>(t))
    {
        return *std::forward<T>(t);
    }

    // Fallback for non-dereferenceable types
    template<typename T>
    auto operator()(T&& t) const
        -> std::enable_if_t<!is_dereferenceable_v<T>, T&&>
    {
        return std::forward<T>(t);
    }
};
```

## SFINAE vs Concepts Integration

XIEITE seamlessly integrates SFINAE with C++20 concepts:

### Concept-Constrained SFINAE

```cpp
// Combining concepts with SFINAE for backward compatibility
template<typename T>
concept arithmetic = std::is_arithmetic_v<T>;

template<typename T>
auto process(T value)
    -> std::enable_if_t<arithmetic<T>, T>
{
    return value * 2;
}

// Concept subsumes SFINAE constraint
template<arithmetic T>
    requires (sizeof(T) > 4)
auto process(T value) -> T
{
    return value * 3;  // More specific overload
}
```

### SFINAE Fallback for Concepts

```cpp
// Primary concept-based template
template<typename T>
    requires std::ranges::range<T>
auto process_range(T&& range) {
    return std::ranges::size(range);
}

// SFINAE fallback for pre-ranges types
template<typename T>
auto process_range(T&& container)
    -> std::enable_if_t<
        !std::ranges::range<T> && has_size<T>,
        std::size_t
    >
{
    return container.size();
}
```

## Type Trait Implementation Patterns

### Binary Type Traits

XIEITE's pattern for binary type relationships:

```cpp
// Check if types are comparable
template<typename T, typename U, typename = void>
struct is_comparable : std::false_type {};

template<typename T, typename U>
struct is_comparable<T, U, std::void_t<
    decltype(std::declval<T>() == std::declval<U>()),
    decltype(std::declval<T>() != std::declval<U>()),
    decltype(std::declval<T>() < std::declval<U>()),
    decltype(std::declval<T>() > std::declval<U>()),
    decltype(std::declval<T>() <= std::declval<U>()),
    decltype(std::declval<T>() >= std::declval<U>())
>> : std::true_type {};

template<typename T, typename U>
inline constexpr bool is_comparable_v = is_comparable<T, U>::value;
```

### Variadic Type Traits

Pattern for traits accepting variable arguments:

```cpp
// Check if all types are constructible from arguments
template<typename... Ts>
struct are_all_constructible;

template<>
struct are_all_constructible<> : std::true_type {};

template<typename T, typename... Rest>
struct are_all_constructible<T, Rest...>
    : std::conjunction<
        std::is_constructible<T>,
        are_all_constructible<Rest...>
    > {};

template<typename... Ts>
inline constexpr bool are_all_constructible_v = are_all_constructible<Ts...>::value;
```

### Transformation Traits

SFINAE patterns for type transformations:

```cpp
// Add pointer levels conditionally
template<typename T, std::size_t N>
struct add_pointer_n {
    using type = typename add_pointer_n<T*, N-1>::type;
};

template<typename T>
struct add_pointer_n<T, 0> {
    using type = T;
};

template<typename T, std::size_t N>
    requires (!std::is_function_v<T> && !std::is_reference_v<T>)
using add_pointer_n_t = typename add_pointer_n<T, N>::type;
```

## Member Detection Patterns

### Method Detection with Specific Signature

```cpp
// Detect method with exact signature
template<typename T>
class has_specific_method {
    template<typename U>
    static auto test(int) -> decltype(
        std::declval<U>().method(std::declval<int>(), std::declval<double>()),
        std::true_type{}
    );

    template<typename>
    static std::false_type test(...);

public:
    static constexpr bool value = decltype(test<T>(0))::value;
};
```

### Operator Detection

XIEITE patterns for operator availability:

```cpp
// Comprehensive operator detection
#define DEFINE_HAS_OPERATOR(op_name, op_symbol)                 \
    template<typename T, typename U = T, typename = void>       \
    struct has_operator_##op_name : std::false_type {};         \
                                                                \
    template<typename T, typename U>                            \
    struct has_operator_##op_name<T, U, std::void_t<            \
        decltype(std::declval<T>() op_symbol std::declval<U>()) \
    >> : std::true_type {};                                     \
                                                                \
    template<typename T, typename U = T>                        \
    inline constexpr bool has_operator_##op_name##_v =          \
        has_operator_##op_name<T, U>::value;

DEFINE_HAS_OPERATOR(plus, +)
DEFINE_HAS_OPERATOR(minus, -)
DEFINE_HAS_OPERATOR(multiply, *)
DEFINE_HAS_OPERATOR(divide, /)
```

### Nested Type Detection

```cpp
// Detect nested types with specific properties
template<typename T, typename = void>
struct has_allocator_type : std::false_type {};

template<typename T>
struct has_allocator_type<T, std::void_t<
    typename T::allocator_type,
    std::enable_if_t<std::is_class_v<typename T::allocator_type>>
>> : std::true_type {};
```

## Overload Resolution Control

### Priority Tag Pattern

XIEITE uses priority tags for controlled overload resolution:

```cpp
// Priority levels for overload selection
template<int N> struct priority_tag : priority_tag<N-1> {};
template<> struct priority_tag<0> {};

// Highest priority: exact match
template<typename T>
auto convert_impl(T&& value, priority_tag<2>)
    -> decltype(value.to_string())
{
    return value.to_string();
}

// Medium priority: stream conversion
template<typename T>
auto convert_impl(T&& value, priority_tag<1>)
    -> decltype((std::ostringstream{} << value).str())
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

// Lowest priority: fallback
template<typename T>
std::string convert_impl(T&&, priority_tag<0>)
{
    return "unconvertible";
}

template<typename T>
std::string to_string_safe(T&& value)
{
    return convert_impl(std::forward<T>(value), priority_tag<2>{});
}
```

### Tag Dispatch with SFINAE

```cpp
// Tag types for dispatch
struct random_access_tag {};
struct bidirectional_tag {};
struct forward_tag {};

// SFINAE-based tag selection
template<typename Iterator>
using iterator_tag = std::conditional_t<
    std::is_base_of_v<std::random_access_iterator_tag,
                     typename std::iterator_traits<Iterator>::iterator_category>,
    random_access_tag,
    std::conditional_t<
        std::is_base_of_v<std::bidirectional_iterator_tag,
                         typename std::iterator_traits<Iterator>::iterator_category>,
        bidirectional_tag,
        forward_tag
    >
>;

// Overloads selected by tag
template<typename Iterator>
void advance_impl(Iterator& it, std::ptrdiff_t n, random_access_tag)
{
    it += n;  // O(1) for random access
}

template<typename Iterator>
void advance_impl(Iterator& it, std::ptrdiff_t n, bidirectional_tag)
{
    if (n >= 0) {
        while (n--) ++it;
    } else {
        while (n++) --it;
    }
}
```

## Substitution Failure Detection

### Valid Expression Checking

```cpp
// Generic valid expression detector
template<typename... Ts>
using void_t = void;

template<template<typename...> class Expr, typename Enabler, typename... Args>
struct is_valid_impl : std::false_type {};

template<template<typename...> class Expr, typename... Args>
struct is_valid_impl<Expr, void_t<Expr<Args...>>, Args...> : std::true_type {};

template<template<typename...> class Expr, typename... Args>
inline constexpr bool is_valid = is_valid_impl<Expr, void, Args...>::value;

// Usage: Define expression to test
template<typename T>
using has_value_member_t = decltype(std::declval<T>().value);

// Test if type has .value member
static_assert(is_valid<has_value_member_t, std::optional<int>>);
```

### Substitution Ordering

XIEITE patterns for controlling substitution order:

```cpp
// Force specific substitution order
template<typename T>
struct defer_substitution {
    using type = T;
};

template<typename T>
auto process(T&& value)
    -> typename defer_substitution<
        decltype(complex_operation(std::forward<T>(value)))
    >::type
{
    return complex_operation(std::forward<T>(value));
}
```

## SFINAE in Constructors

### Conditionally Explicit Constructors

```cpp
template<typename T>
class wrapper {
    T value_;

public:
    // Explicit only for non-arithmetic types
    template<typename U = T>
    explicit(!std::is_arithmetic_v<U>)
    wrapper(U&& val) : value_(std::forward<U>(val)) {}

    // SFINAE-disabled copy constructor for certain types
    template<typename U = T>
    wrapper(const wrapper& other,
            std::enable_if_t<std::is_copy_constructible_v<U>, int> = 0)
        : value_(other.value_) {}
};
```

### Constructor Enablement

```cpp
// Enable constructor based on variadic arguments
template<typename T>
class flexible_container {
public:
    // Single argument constructor
    template<typename U,
             std::enable_if_t<std::is_convertible_v<U, T> &&
                            !std::is_same_v<std::decay_t<U>, flexible_container>, int> = 0>
    flexible_container(U&& value) : data_{std::forward<U>(value)} {}

    // Multiple argument constructor
    template<typename... Args,
             std::enable_if_t<(sizeof...(Args) > 1) &&
                            (std::is_convertible_v<Args, T> && ...), int> = 0>
    flexible_container(Args&&... args) : data_{std::forward<Args>(args)...} {}

private:
    std::vector<T> data_;
};
```

## Common SFINAE Pitfalls and Solutions

### Hard Errors vs Substitution Failures

```cpp
// Problem: This causes a hard error, not SFINAE
template<typename T>
auto bad_sfinae(T t) -> decltype(T::nonexistent_member) {
    return T::nonexistent_member;
}

// Solution: Use dependent context
template<typename T>
auto good_sfinae(T t) -> decltype(t.nonexistent_member) {
    return t.nonexistent_member;
}

// Or use std::declval
template<typename T>
auto better_sfinae() -> decltype(std::declval<T>().nonexistent_member) {
    return std::declval<T>().nonexistent_member;
}
```

### SFINAE in Deduced Contexts

```cpp
// Problem: SFINAE doesn't work in deduced contexts
template<typename T>
void problematic(std::vector<T> vec,
                std::enable_if_t<std::is_integral_v<T>>* = nullptr);
// T cannot be deduced when SFINAE constraint fails

// Solution: Use non-deduced context
template<typename T>
void better(std::vector<T> vec)
    requires std::is_integral_v<T>;

// Or use template parameter
template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
void alternative(std::vector<T> vec);
```

### Ambiguous Overloads

```cpp
// Problem: Both overloads may be valid
template<typename T>
std::enable_if_t<std::is_integral_v<T>, T> process(T value);

template<typename T>
std::enable_if_t<std::is_arithmetic_v<T>, T> process(T value);
// Ambiguous for integral types

// Solution: Make conditions mutually exclusive
template<typename T>
std::enable_if_t<std::is_integral_v<T>, T> process(T value);

template<typename T>
std::enable_if_t<std::is_floating_point_v<T>, T> process(T value);
```

## Performance Considerations

### Compilation Time Impact

SFINAE patterns affect compilation time:

1. **Deep Instantiation**: Complex SFINAE increases template instantiation depth
2. **Overload Set Size**: Many SFINAE overloads slow down resolution
3. **Expression Complexity**: Complex expressions in decltype increase parse time

### Optimization Strategies

```cpp
// Cache trait results
template<typename T>
struct cached_traits {
    static constexpr bool has_begin = has_begin_v<T>;
    static constexpr bool has_end = has_end_v<T>;
    static constexpr bool has_size = has_size_v<T>;
    static constexpr bool is_container = has_begin && has_end && has_size;
};

// Use cached results
template<typename T>
    requires cached_traits<T>::is_container
auto process_container(T&& c);
```

## Best Practices

### 1. Prefer Concepts When Available

```cpp
// Good: Use concepts for cleaner syntax
template<typename T>
    requires std::integral<T>
T increment(T value) { return value + 1; }

// Acceptable: SFINAE for compatibility
template<typename T>
std::enable_if_t<std::is_integral_v<T>, T>
increment_legacy(T value) { return value + 1; }
```

### 2. Use Helper Aliases

```cpp
// Good: Define clear helper aliases
template<typename T>
using require_arithmetic = std::enable_if_t<std::is_arithmetic_v<T>>;

template<typename T, typename = require_arithmetic<T>>
T multiply(T a, T b) { return a * b; }
```

### 3. Provide Clear Error Messages

```cpp
// Good: Static assertion with message
template<typename T>
void process(T value) {
    if constexpr (has_process_method_v<T>) {
        value.process();
    } else {
        static_assert(always_false<T>, "Type T must have a process() method");
    }
}

template<typename> inline constexpr bool always_false = false;
```

### 4. Document SFINAE Requirements

```cpp
/**
 * @brief Process a range-like object
 * @tparam Range Type that must have begin() and end() methods
 * @note Uses SFINAE to disable for non-range types
 */
template<typename Range>
auto process_range(Range&& r)
    -> std::enable_if_t<has_begin_v<Range> && has_end_v<Range>, void>;
```

## Migration Path: SFINAE to Concepts

XIEITE provides patterns for gradual migration:

```cpp
// Step 1: Original SFINAE
template<typename T>
std::enable_if_t<std::is_integral_v<T>, T>
original_function(T value);

// Step 2: Hybrid approach
template<typename T>
    requires std::is_integral_v<T>
auto migrated_function(T value)
    -> std::enable_if_t<sizeof(T) <= 8, T>;

// Step 3: Pure concepts
template<typename T>
    requires std::integral<T> && (sizeof(T) <= 8)
T modern_function(T value);
```

---

*See also: [Concepts](concepts.md) | [Type Traits Architecture](type_traits_arch.md) | [Template Patterns](template_patterns.md)*
