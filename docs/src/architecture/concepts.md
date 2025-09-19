# Concept-Based Design

## C++20 Concepts in XIEITE

XIEITE extensively leverages C++20 concepts to provide clear, expressive constraints and better error messages. With over 150 concept definitions across 276 type trait headers, concepts form the foundation of XIEITE's type system.

## What Are Concepts?

Concepts are compile-time predicates that specify requirements on template arguments. They provide:
- **Clear Intent**: Express what types are valid
- **Better Errors**: Readable constraint failure messages
- **Overload Resolution**: Participate in SFINAE
- **Subsumption**: Automatic ordering of constraints

## XIEITE's Concept Architecture

### Concept Naming Convention

XIEITE follows a consistent naming pattern:
```cpp
// Type query concepts start with "is_"
template<typename T>
concept is_arithmetic = std::is_arithmetic_v<T>;

// Capability concepts start with "can_"
template<typename T>
concept can_compare = requires(T a, T b) {
    { a == b } -> std::convertible_to<bool>;
    { a != b } -> std::convertible_to<bool>;
};

// Requirement concepts start with "has_"
template<typename T>
concept has_value_type = requires {
    typename T::value_type;
};
```

## Core Concept Categories

### 1. Fundamental Type Concepts

```cpp
// Arithmetic types
template<typename T>
concept is_arithmetic = std::is_arithmetic_v<T>;

// Integral types
template<typename T>
concept is_integral = std::is_integral_v<T>;

// Floating-point types
template<typename T>
concept is_floating_point = std::is_floating_point_v<T>;

// Character types
template<typename T>
concept is_char = std::is_same_v<std::remove_cv_t<T>, char> ||
                  std::is_same_v<std::remove_cv_t<T>, wchar_t> ||
                  std::is_same_v<std::remove_cv_t<T>, char8_t> ||
                  std::is_same_v<std::remove_cv_t<T>, char16_t> ||
                  std::is_same_v<std::remove_cv_t<T>, char32_t>;
```

### 2. Container Concepts

```cpp
// Basic container
template<typename T>
concept is_container = requires(T t) {
    typename T::value_type;
    typename T::size_type;
    typename T::iterator;
    { t.begin() } -> std::input_or_output_iterator;
    { t.end() } -> std::sentinel_for<decltype(t.begin())>;
    { t.size() } -> std::convertible_to<typename T::size_type>;
};

// Sequence container
template<typename T>
concept is_sequence_container = is_container<T> && requires(T t) {
    { t.front() } -> std::convertible_to<typename T::value_type>;
    { t.back() } -> std::convertible_to<typename T::value_type>;
};

// Associative container
template<typename T>
concept is_associative_container = is_container<T> && requires {
    typename T::key_type;
    typename T::mapped_type;
};
```

### 3. Function Concepts

```cpp
// Callable with specific signature
template<typename F, typename... Args>
concept is_invocable = std::invocable<F, Args...>;

// Callable with specific return type
template<typename F, typename R, typename... Args>
concept is_invocable_r = std::invocable<F, Args...> &&
    std::convertible_to<std::invoke_result_t<F, Args...>, R>;

// Predicate concept
template<typename F, typename... Args>
concept is_predicate = is_invocable_r<F, bool, Args...>;

// Comparison function
template<typename F, typename T>
concept is_comparator = requires(F f, T a, T b) {
    { f(a, b) } -> std::convertible_to<bool>;
    { f(b, a) } -> std::convertible_to<bool>;
};
```

### 4. Iterator Concepts

```cpp
// Input iterator
template<typename T>
concept is_input_iterator = std::input_iterator<T>;

// Output iterator
template<typename T, typename V>
concept is_output_iterator = std::output_iterator<T, V>;

// Random access iterator
template<typename T>
concept is_random_access_iterator = std::random_access_iterator<T>;

// Contiguous iterator
template<typename T>
concept is_contiguous_iterator = std::contiguous_iterator<T>;
```

## Advanced Concept Techniques

### Concept Composition

```cpp
// Combining multiple concepts
template<typename T>
concept is_numeric_container = is_container<T> &&
                               is_arithmetic<typename T::value_type>;

// Building complex requirements
template<typename T>
concept is_sortable_container = is_container<T> &&
    std::sortable<typename T::iterator> &&
    std::totally_ordered<typename T::value_type>;

// Nested requirements
template<typename T>
concept is_matrix = is_container<T> && requires {
    typename T::value_type;
    requires is_container<typename T::value_type>;
    requires is_arithmetic<typename T::value_type::value_type>;
};
```

### Concept Subsumption

Concepts are automatically ordered by subsumption:

```cpp
// Base concept
template<typename T>
concept Copyable = std::is_copy_constructible_v<T>;

// More constrained concept subsumes the base
template<typename T>
concept CopyableAndMovable = Copyable<T> &&
                             std::is_move_constructible_v<T>;

// Function overloading with subsumption
template<Copyable T>
void process(T value) {
    // Called for types that are only copyable
}

template<CopyableAndMovable T>
void process(T value) {
    // Preferred for types that are both copyable and movable
}
```

### Requires Expressions

```cpp
// Simple requires expression
template<typename T>
concept has_reset = requires(T t) {
    t.reset();
};

// Compound requirements
template<typename T>
concept is_resizable = requires(T t, std::size_t n) {
    { t.size() } -> std::convertible_to<std::size_t>;
    { t.resize(n) } noexcept;
    { t.capacity() } -> std::same_as<std::size_t>;
};

// Nested requirements
template<typename T>
concept is_smart_pointer = requires(T t) {
    typename T::element_type;
    { *t } -> std::convertible_to<typename T::element_type&>;
    { t.get() } -> std::same_as<typename T::element_type*>;
    { t.reset() } noexcept;
    requires std::destructible<typename T::element_type>;
};
```

## XIEITE-Specific Concepts

### Arrow Macro Compatibility

```cpp
// Can be used with XIEITE_ARROW
template<typename F, typename... Args>
concept arrow_compatible = requires(F f, Args... args) {
    { f(args...) };  // Expression must be valid
    requires !std::is_void_v<decltype(f(args...))>;  // Must return something
};
```

### Type List Concepts

```cpp
// Is a type list
template<typename T>
concept is_type_list = requires {
    typename T::template at<0>;
    { T::size } -> std::convertible_to<std::size_t>;
};

// Can be filtered
template<typename T>
concept is_filterable_list = is_type_list<T> && requires {
    typename T::template filter<std::is_integral>;
};
```

### Mathematical Concepts

```cpp
// Supports arithmetic operations
template<typename T>
concept math_compatible = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
    { a - b } -> std::convertible_to<T>;
    { a * b } -> std::convertible_to<T>;
    { a / b } -> std::convertible_to<T>;
};

// Can be used in algorithms
template<typename T>
concept algorithm_compatible = std::regular<T> &&
                               std::totally_ordered<T>;
```

## Concept-Based Function Design

### Single Concept Constraint

```cpp
template<is_container C>
auto get_size(const C& container) {
    return container.size();
}
```

### Multiple Constraints

```cpp
template<typename T>
    requires is_container<T> &&
             is_arithmetic<typename T::value_type>
auto sum_elements(const T& container) {
    using value_type = typename T::value_type;
    return std::accumulate(container.begin(), container.end(),
                          value_type{0});
}
```

### Constrained Auto

```cpp
// C++20 constrained auto
is_arithmetic auto compute() {
    return 42;
}

// In templates
template<typename T>
void process(T container) {
    is_arithmetic auto sum = 0;
    for (is_arithmetic auto& value : container) {
        sum += value;
    }
}
```

## Concept Error Messages

### Clear Constraint Failures

```cpp
template<is_container C>
void process_container(C& c);

// Attempting to call with non-container
int x = 42;
process_container(x);
// Error: constraint 'is_container<int>' not satisfied
// Note: 'int' does not have member 'begin()'
```

### Custom Error Messages

```cpp
template<typename T>
concept ValidInput = is_container<T> ||
    static_assert_v<false, "Type must be a container">;
```

## Best Practices

### 1. Use Semantic Names

```cpp
// Good: Clear intent
template<typename T>
concept is_serializable = /* ... */;

// Bad: Unclear purpose
template<typename T>
concept C1 = /* ... */;
```

### 2. Compose Simple Concepts

```cpp
// Build complex from simple
template<typename T>
concept is_copyable = std::is_copy_constructible_v<T>;

template<typename T>
concept is_movable = std::is_move_constructible_v<T>;

template<typename T>
concept is_relocatable = is_copyable<T> || is_movable<T>;
```

### 3. Document Requirements

```cpp
// Document what the concept checks
template<typename T>
concept is_range = requires(T t) {
    // Must have begin/end that return iterators
    { t.begin() } -> std::input_or_output_iterator;
    { t.end() } -> std::sentinel_for<decltype(t.begin())>;
};
```

### 4. Avoid Over-Constraining

```cpp
// Too restrictive
template<typename T>
    requires std::same_as<T, std::vector<int>>
void process(T& v);

// Better: More flexible
template<is_container T>
    requires is_integral<typename T::value_type>
void process(T& v);
```

## Performance Implications

### Compile-Time Cost

- Concept checking happens at compile time
- No runtime overhead
- May increase compilation time with complex constraints
- Compilers cache concept evaluations

### Binary Size

- Concepts don't affect binary size
- Better than SFINAE (less template instantiation)
- Enables better optimization through constraints

## Migration from SFINAE

### Before (SFINAE)

```cpp
template<typename T,
         typename = std::enable_if_t<std::is_integral_v<T>>>
T increment(T value) {
    return value + 1;
}
```

### After (Concepts)

```cpp
template<std::integral T>
T increment(T value) {
    return value + 1;
}
```

## Concept Testing

### Static Assertions

```cpp
// Test concept satisfaction
static_assert(is_container<std::vector<int>>);
static_assert(!is_container<int>);

// Test subsumption
static_assert(CopyableAndMovable<std::string>);
```

### Compile-Time Queries

```cpp
if constexpr (is_container<T>) {
    // Container-specific code
} else {
    // Non-container code
}
```

## Future Directions

### C++23 Enhancements

- Deducing this
- Expanded standard concepts
- Better subsumption rules

### XIEITE Evolution

- More domain-specific concepts
- Concept-based optimizations
- Enhanced error reporting

---

*Next: [SFINAE Patterns](sfinae.md) | [Compile-Time Computation](compile_time.md) | [Type Traits Architecture](type_traits_arch.md)*