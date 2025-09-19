# Template Metaprogramming

## Foundation of XIEITE's Design

Template metaprogramming forms the backbone of XIEITE's architecture, enabling compile-time computation, type manipulation, and zero-overhead abstractions. This comprehensive guide explores the patterns, techniques, and innovations that power the library's 616 headers.

## Core Principles

### Compile-Time Computation

XIEITE prioritizes moving computation from runtime to compile-time:

```cpp
// Traditional runtime approach
int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i)
        result *= i;
    return result;
}

// XIEITE compile-time approach
template<std::size_t N>
constexpr auto factorial = xieite::fact<N>;

// Usage
constexpr auto val = xieite::fact<10>;  // Computed at compile time
static_assert(val == 3628800);
```

### Type as Data

Types carry information through the compilation process:

```cpp
// Type list as compile-time container
using types = xieite::type_list<int, double, std::string>;

// Operations on types
using filtered = types::filter<std::is_arithmetic>;  // int, double
using reversed = types::reverse;                      // string, double, int
using unique = types::dedupe;                        // Removes duplicates

static_assert(filtered::size == 2);
static_assert(types::contains<double>);
```

### SFINAE (Substitution Failure Is Not An Error)

XIEITE leverages SFINAE for conditional template instantiation:

```cpp
// Enable function only for arithmetic types
template<typename T>
    requires xieite::is_arithmetic<T>
auto process(T value) -> decltype(value * 2) {
    return value * 2;
}

// Alternative SFINAE approach
template<typename T>
auto process(T value)
    -> std::enable_if_t<xieite::is_arithmetic<T>, T> {
    return value * 2;
}
```

## Template Patterns in XIEITE

### 1. Recursive Template Instantiation

Used extensively for compile-time algorithms:

```cpp
// Compile-time fibonacci
template<std::size_t N>
struct fibonacci {
    static constexpr std::size_t value =
        fibonacci<N-1>::value + fibonacci<N-2>::value;
};

template<>
struct fibonacci<0> {
    static constexpr std::size_t value = 0;
};

template<>
struct fibonacci<1> {
    static constexpr std::size_t value = 1;
};
```

### 2. Template Specialization Hierarchies

XIEITE uses specialization for type trait implementation:

```cpp
// Primary template - default case
template<typename T, typename = void>
struct is_container : std::false_type {};

// Specialization for types with begin/end
template<typename T>
struct is_container<T, std::void_t<
    decltype(std::declval<T>().begin()),
    decltype(std::declval<T>().end()),
    typename T::value_type
>> : std::true_type {};
```

### 3. Variadic Template Patterns

Handling arbitrary numbers of template parameters:

```cpp
// Type list implementation
template<typename... Types>
struct type_list {
    static constexpr std::size_t size = sizeof...(Types);

    // Get type at index
    template<std::size_t I>
    using at = typename detail::at_impl<I, Types...>::type;

    // Append types
    template<typename... Others>
    using append = type_list<Types..., Others...>;

    // Apply transformation
    template<template<typename> class F>
    using transform = type_list<F<Types>...>;
};
```

### 4. Expression Templates

Building computation trees at compile-time:

```cpp
// Expression template for lazy evaluation
template<typename L, typename Op, typename R>
struct expression {
    L left;
    Op op;
    R right;

    auto operator()() const {
        return op(left(), right());
    }
};

// Operator overloading builds expression tree
template<typename L, typename R>
auto operator+(const L& l, const R& r) {
    return expression<L, std::plus<>, R>{l, {}, r};
}
```

### 5. CRTP (Curiously Recurring Template Pattern)

Static polymorphism without virtual functions:

```cpp
template<typename Derived>
struct comparable {
    auto operator!=(const Derived& other) const
        XIEITE_ARROW(!(static_cast<const Derived&>(*this) == other))

    auto operator>(const Derived& other) const
        XIEITE_ARROW(other < static_cast<const Derived&>(*this))

    auto operator<=(const Derived& other) const
        XIEITE_ARROW(!(static_cast<const Derived&>(*this) > other))

    auto operator>=(const Derived& other) const
        XIEITE_ARROW(!(static_cast<const Derived&>(*this) < other))
};

struct Point : comparable<Point> {
    int x, y;
    auto operator==(const Point& p) const XIEITE_ARROW(x == p.x && y == p.y)
    auto operator<(const Point& p) const XIEITE_ARROW(x < p.x || (x == p.x && y < p.y))
};
```

### 6. Tag Dispatching

Compile-time function selection based on type properties:

```cpp
namespace detail {
    template<typename T>
    void destroy_impl(T* ptr, std::true_type) {
        // Trivially destructible - no-op
    }

    template<typename T>
    void destroy_impl(T* ptr, std::false_type) {
        ptr->~T();  // Call destructor
    }
}

template<typename T>
void destroy(T* ptr) {
    detail::destroy_impl(ptr, std::is_trivially_destructible<T>{});
}
```

### 7. Template Template Parameters

Templates that take other templates as parameters:

```cpp
template<template<typename...> class Container, typename T>
struct rebind {
    using type = Container<T>;
};

// Usage
using vec_int = rebind<std::vector, int>::type;  // std::vector<int>
using set_str = rebind<std::set, std::string>::type;  // std::set<std::string>
```

## Advanced Metaprogramming Techniques

### Compile-Time Type Manipulation

```cpp
// Remove qualifiers recursively
template<typename T>
struct deep_remove_cv {
    using type = T;
};

template<typename T>
struct deep_remove_cv<const T> {
    using type = typename deep_remove_cv<T>::type;
};

template<typename T>
struct deep_remove_cv<volatile T> {
    using type = typename deep_remove_cv<T>::type;
};

template<typename T>
struct deep_remove_cv<T*> {
    using type = typename deep_remove_cv<T>::type*;
};

template<typename T>
using deep_remove_cv_t = typename deep_remove_cv<T>::type;
```

### Fold Expressions (C++17)

XIEITE uses fold expressions for variadic operations:

```cpp
// Check if all types satisfy a predicate
template<typename... Types>
constexpr bool all_integral = (std::is_integral_v<Types> && ...);

// Sum all values
template<typename... Args>
auto sum(Args... args) XIEITE_ARROW((args + ...))

// Check if any type matches
template<typename T, typename... Types>
constexpr bool is_any_of = ((std::is_same_v<T, Types>) || ...);
```

### Compile-Time String Processing

```cpp
template<std::size_t N>
struct fixed_string {
    char data[N + 1] = {};

    constexpr fixed_string(const char (&str)[N + 1]) {
        std::copy_n(str, N + 1, data);
    }

    template<std::size_t M>
    constexpr auto operator+(const fixed_string<M>& other) const {
        fixed_string<N + M> result;
        std::copy_n(data, N, result.data);
        std::copy_n(other.data, M + 1, result.data + N);
        return result;
    }
};

template<fixed_string str>
struct string_constant {
    static constexpr auto value = str;
};
```

### Compile-Time Reflection (Aggregate Introspection)

```cpp
// Detect number of aggregate members
template<typename T>
constexpr std::size_t arity() {
    if constexpr (requires { T{any{}, any{}, any{}, any{}}; }) return 4;
    else if constexpr (requires { T{any{}, any{}, any{}}; }) return 3;
    else if constexpr (requires { T{any{}, any{}}; }) return 2;
    else if constexpr (requires { T{any{}}; }) return 1;
    else return 0;
}

// Usage
struct Point { int x, y; };
static_assert(arity<Point>() == 2);
```

## Type Traits Architecture

### Concept-Based Design

XIEITE extensively uses C++20 concepts:

```cpp
template<typename T>
concept arithmetic = std::is_arithmetic_v<T>;

template<typename T>
concept container = requires(T t) {
    typename T::value_type;
    { t.begin() } -> std::input_iterator;
    { t.end() } -> std::sentinel_for<decltype(t.begin())>;
    { t.size() } -> std::convertible_to<std::size_t>;
};

template<typename T>
concept hashable = requires(T t) {
    { std::hash<T>{}(t) } -> std::convertible_to<std::size_t>;
};
```

### Trait Composition

Building complex traits from simple ones:

```cpp
template<typename T>
concept signed_integral = std::integral<T> && std::is_signed_v<T>;

template<typename T>
concept trivial_container = container<T> &&
    std::is_trivially_copyable_v<typename T::value_type>;

template<typename T>
concept fast_comparable =
    std::is_trivially_copyable_v<T> &&
    sizeof(T) <= sizeof(void*);
```

## Compile-Time Algorithms

### Type List Operations

```cpp
// Filter types based on predicate
template<typename List, template<typename> class Pred>
struct filter;

template<template<typename...> class List, typename... Types,
         template<typename> class Pred>
struct filter<List<Types...>, Pred> {
    template<typename T>
    using filtered = std::conditional_t<Pred<T>::value,
                                       type_list<T>,
                                       type_list<>>;

    using type = decltype((filtered<Types>{} + ...));
};

// Sort types by size
template<typename... Types>
using sort_by_size = /* implementation using compile-time quicksort */;
```

### Compile-Time State Machines

```cpp
template<typename State, typename Event>
struct transition;

// Define transitions
template<>
struct transition<Idle, StartEvent> {
    using next = Running;
};

template<>
struct transition<Running, StopEvent> {
    using next = Idle;
};

// State machine
template<typename InitialState>
class state_machine {
    using state = InitialState;

    template<typename Event>
    using process = typename transition<state, Event>::next;
};
```

## Performance Implications

### Compilation Time vs Runtime

```cpp
// Compile-time computation - slower compilation, zero runtime cost
template<std::size_t N>
constexpr auto compile_time_prime = xieite::prime<N>;

// Runtime computation - fast compilation, runtime cost
auto runtime_prime(std::size_t n) {
    return xieite::nth_prime(n);
}
```

### Template Instantiation Costs

- **Linear Growth**: Simple templates scale linearly
- **Exponential Growth**: Recursive templates can explode
- **Memoization**: Compilers cache instantiations
- **Explicit Instantiation**: Control where templates are instantiated

### Binary Size Considerations

```cpp
// Minimize template instantiations
template<typename T>
void process_impl(void* data) {
    // Implementation
}

template<typename T>
void process(T& value) {
    process_impl<T>(&value);  // Single instantiation point
}
```

## Best Practices

### 1. Constrain Templates Early

```cpp
template<typename T>
    requires std::integral<T>  // Constraint at declaration
auto function(T value) {
    // Clear error messages if constraint fails
}
```

### 2. Use Concepts Over SFINAE

```cpp
// Prefer concepts (clear)
template<container C>
void process(C& c);

// Over SFINAE (cryptic)
template<typename C>
std::enable_if_t<is_container_v<C>> process(C& c);
```

### 3. Minimize Template Depth

```cpp
// Iterative instead of recursive when possible
template<std::size_t N>
constexpr auto factorial() {
    std::size_t result = 1;
    for (std::size_t i = 2; i <= N; ++i)
        result *= i;
    return result;
}
```

### 4. Explicit Instantiation Control

```cpp
// In header
template<typename T>
void heavy_template(T value);

// In source file
template void heavy_template<int>(int);
template void heavy_template<double>(double);
// Limits instantiation to specific types
```

## Common Pitfalls and Solutions

### Pitfall: Infinite Template Recursion

```cpp
// Problem
template<typename T>
struct infinite : infinite<infinite<T>> {};  // Error!

// Solution
template<typename T, std::size_t Depth = 0>
struct bounded {
    static_assert(Depth < 100, "Recursion limit");
    using type = bounded<T, Depth + 1>;
};
```

### Pitfall: Dependent Name Lookup

```cpp
// Problem
template<typename T>
void function() {
    T::type value;  // Error if type is not a type

// Solution
template<typename T>
void function() {
    typename T::type value;  // Correct
}
```

### Pitfall: Template Bloat

```cpp
// Problem: Each T creates new instantiation
template<typename T>
class heavy_class { /* lots of code */ };

// Solution: Type erasure
class heavy_class_impl { /* implementation */ };

template<typename T>
class light_wrapper {
    heavy_class_impl impl;  // Shared implementation
};
```

## Future Directions

### C++23 and Beyond

- **Static Reflection**: Introspect types at compile-time
- **Pattern Matching**: Advanced compile-time dispatch
- **Compile-Time Allocation**: Dynamic memory at compile-time
- **Metaclasses**: Generate classes from templates

### XIEITE Evolution

- Enhanced concept definitions
- More compile-time algorithms
- Better error messages
- Reduced compilation times

---

*Next: [Concept-Based Design](concepts.md) | [SFINAE Patterns](sfinae.md) | [Compile-Time Computation](compile_time.md)*