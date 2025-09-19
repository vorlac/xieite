# Macro System Deep Dive

## Overview

XIEITE's macro system represents one of the most sophisticated preprocessor implementations in modern C++. At its core are the ARROW macros - a family of 8 specialized macros that enable concise, expressive function definitions while maintaining full type safety and noexcept correctness.

## The Arrow Macro Philosophy

Traditional C++ function definitions are verbose:

```cpp
// Traditional approach - verbose and error-prone
template<typename T>
auto process(T&& value) noexcept(noexcept(transform(std::forward<T>(value))))
    -> decltype(transform(std::forward<T>(value)))
    requires requires { transform(std::forward<T>(value)); }
{
    return transform(std::forward<T>(value));
}

// XIEITE approach - concise and correct
template<typename T>
auto process(T&& value) XIEITE_ARROW(transform(std::forward<T>(value)))
```

## Core Arrow Macros

### XIEITE_ARROW - The Foundation

The most fundamental macro, providing automatic deduction of return type and noexcept specification:

```cpp
#define XIEITE_ARROW(...) \
    noexcept __VA_OPT__( \
        (noexcept(__VA_ARGS__)) \
        -> decltype(auto) \
        requires(requires { __VA_ARGS__; }) \
    ) { return __VA_ARGS__; }
```

**Features:**
- Deduces return type via `decltype(auto)`
- Automatically determines `noexcept` specification
- Adds concept constraint to ensure expression validity
- Perfect for single-expression functions

**Usage Examples:**

```cpp
// Simple computation
auto double_value(int x) XIEITE_ARROW(x * 2)

// With templates
template<typename T, typename U>
auto add(T&& a, U&& b) XIEITE_ARROW(std::forward<T>(a) + std::forward<U>(b))

// Member functions
struct Container {
    auto size() const XIEITE_ARROW(data_.size())
    auto empty() const XIEITE_ARROW(data_.empty())
private:
    std::vector<int> data_;
};
```

### XIEITE_ARROW_NOEX - Forced Noexcept

Forces `noexcept(true)` while maintaining return type deduction:

```cpp
#define XIEITE_ARROW_NOEX(...) \
    noexcept __VA_OPT__( \
        -> decltype(auto) \
        requires(requires { __VA_ARGS__; }) \
    ) { return __VA_ARGS__; }
```

**Use Cases:**
- Performance-critical code where exceptions must be avoided
- Interface contracts that guarantee no-throw
- Optimization hints for the compiler

```cpp
// Guarantee no exceptions
auto safe_access(const std::vector<int>& v, std::size_t i)
    XIEITE_ARROW_NOEX(v[std::min(i, v.size() - 1)])

// Critical path optimization
auto fast_hash(std::uint64_t x) XIEITE_ARROW_NOEX(x ^ (x >> 32))
```

### XIEITE_ARROW_RET - No Return Type Deduction

Omits return type deduction, useful when the return type is already specified:

```cpp
#define XIEITE_ARROW_RET(...) \
    noexcept __VA_OPT__( \
        (noexcept(__VA_ARGS__)) \
        requires(requires { __VA_ARGS__; }) \
    ) { return __VA_ARGS__; }
```

**When to Use:**
- Return type is explicitly declared
- Avoiding potential deduction issues
- Interface consistency requirements

```cpp
// Explicit return type
auto compute() -> int XIEITE_ARROW_RET(42)

// Template with specified return
template<typename T>
auto convert(T value) -> double XIEITE_ARROW_RET(static_cast<double>(value))
```

## Conditional Arrow Macros

### XIEITE_ARROW_IF - Conditional Execution

Executes code conditionally before returning:

```cpp
#define XIEITE_ARROW_IF(_cond, _then, ...) \
    noexcept((!static_cast<bool>(_cond) || noexcept(_then)) \
        __VA_OPT__(&& noexcept(__VA_ARGS__))) \
    -> decltype(auto) \
    requires((!static_cast<bool>(_cond) || requires { _then; }) \
        __VA_OPT__(&& requires { __VA_ARGS__; })) \
    { if constexpr (static_cast<bool>(_cond)) { _then; } \
      return __VA_ARGS__; }
```

**Use Cases:**
- Debug assertions
- Logging before return
- Conditional side effects

```cpp
// Debug logging
auto process(int x)
    XIEITE_ARROW_IF(DEBUG_MODE,
        std::cout << "Processing: " << x << '\n',
        x * 2)

// Validation
auto safe_divide(double a, double b)
    XIEITE_ARROW_IF(b == 0,
        throw std::domain_error("Division by zero"),
        a / b)
```

### XIEITE_ARROW_CHOOSE - Conditional Selection

Returns different expressions based on a compile-time condition:

```cpp
#define XIEITE_ARROW_CHOOSE(_cond, _then, ...) \
    noexcept((static_cast<bool>(_cond) && noexcept(_then)) \
        __VA_OPT__(|| (!static_cast<bool>(_cond) && noexcept(__VA_ARGS__)))) \
    -> decltype(auto) \
    requires((static_cast<bool>(_cond) && requires { _then; }) \
        __VA_OPT__(|| (!static_cast<bool>(_cond) && requires { __VA_ARGS__; }))) \
    { if constexpr (static_cast<bool>(_cond)) { \
        return XIEITE_UNWRAP(_then); \
      } else { \
        return __VA_ARGS__; \
      } }
```

**Applications:**
- Platform-specific implementations
- Compile-time feature selection
- Optimization branches

```cpp
// Platform-specific code
auto get_path_separator()
    XIEITE_ARROW_CHOOSE(
        std::is_same_v<OS, Windows>,
        '\\',
        '/')

// Type-based selection
template<typename T>
auto default_value()
    XIEITE_ARROW_CHOOSE(
        std::is_arithmetic_v<T>,
        T{0},
        T{})
```

## Advanced Arrow Macros

### XIEITE_ARROW_TRY - Exception Handling

Provides try-catch blocks with automatic return:

```cpp
#define XIEITE_ARROW_TRY(_body, ...) \
    XIEITE_EVAL( \
        noexcept __VA_OPT__((DETAIL_XIEITE_ARROW_TRY(requires noexcept, __VA_ARGS__))) \
        -> decltype(auto) \
        requires(DETAIL_XIEITE_ARROW_TRY(,, _body, __VA_ARGS__)) \
        try { return XIEITE_UNWRAP(_body); } \
        DETAIL_XIEITE_ARROW_CATCH(__VA_ARGS__) \
    )
```

**Exception Safety:**
- Automatic noexcept deduction
- Multiple catch handlers
- Default fallback values

```cpp
// Safe conversion with fallback
auto safe_stoi(const std::string& s)
    XIEITE_ARROW_TRY(
        std::stoi(s),
        (std::invalid_argument), 0,
        (std::out_of_range), INT_MAX)

// Resource management
auto read_file(const std::string& path)
    XIEITE_ARROW_TRY(
        read_contents(path),
        (std::runtime_error), std::string{})
```

### XIEITE_ARROW_DECL - Parameter Declaration

Enables parameter pack expansion with automatic forwarding:

```cpp
#define XIEITE_ARROW_DECL(_params, ...) \
    XIEITE_EVAL( \
        noexcept(requires DETAIL_XIEITE_ARROW_PARAMS(XIEITE_UNWRAP(_params)) \
            { requires(noexcept(__VA_ARGS__)); }) \
        -> decltype(auto) \
        requires(requires DETAIL_XIEITE_ARROW_PARAMS(XIEITE_UNWRAP(_params)) \
            { __VA_ARGS__; }) \
        { return __VA_ARGS__; } \
    )
```

**Advanced Features:**
- Perfect forwarding of parameters
- Variadic template support
- Automatic type deduction

```cpp
// Variadic forwarding
template<typename... Args>
auto forward_to_impl XIEITE_ARROW_DECL(
    (Args),
    impl(std::forward<Args>(Args)...))

// Multiple parameter packs
template<typename... Ts, typename... Us>
auto combine XIEITE_ARROW_DECL(
    ((Ts), (Us)),
    make_tuple(std::forward<Ts>(Ts)..., std::forward<Us>(Us)...))
```

### XIEITE_ARROW_CTOR - Constructor Helper

Simplifies constructor initialization lists:

```cpp
#define XIEITE_ARROW_CTOR(_body, ...) \
    XIEITE_EVAL( \
        noexcept(XIEITE_OPT(_body)(noexcept(XIEITE_UNWRAP(_body)) &&)() \
            DETAIL_XIEITE_ARROW_NOEX(&&, __VA_ARGS__)) \
        requires(requires { XIEITE_OPT(_body)(XIEITE_UNWRAP(_body);)() \
            DETAIL_XIEITE_ARROW_NOEX(;, __VA_ARGS__); }) \
        : DETAIL_XIEITE_ARROW_INIT(__VA_ARGS__) \
        { XIEITE_UNWRAP(_body); } \
    )
```

**Constructor Patterns:**
- Member initialization
- Delegating constructors
- Conditional initialization

```cpp
struct Widget {
    int value;
    std::string name;

    // Clean constructor syntax
    Widget(int v, std::string n)
        XIEITE_ARROW_CTOR(
            validate(),
            value, v,
            name, std::move(n))

    // Variadic constructor
    template<typename... Args>
    Widget(Args&&... args)
        XIEITE_ARROW_CTOR(,
            value, 0,
            name, concat(std::forward<Args>(args)...))
};
```

## Supporting Macro Infrastructure

### Token Manipulation

```cpp
// Unwrap parenthesized expressions
#define XIEITE_UNWRAP(...) __VA_ARGS__

// Check if wrapped in parentheses
#define XIEITE_WRAPPED(...) /* implementation */

// Optional expansion
#define XIEITE_OPT(...) /* implementation */
```

### Preprocessor Helpers

```cpp
// Evaluate after expansion
#define XIEITE_EVAL(...) __VA_ARGS__

// Conditional expansion
#define XIEITE_IF(cond) /* implementation */

// For-each iteration
#define XIEITE_EACH(...) /* implementation */
```

## Macro Expansion Examples

Let's trace through a complete expansion:

```cpp
// Original code
auto add(int a, int b) XIEITE_ARROW(a + b)

// Stage 1: Macro substitution
auto add(int a, int b)
    noexcept __VA_OPT__(
        (noexcept(a + b))
        -> decltype(auto)
        requires(requires { a + b; })
    ) { return a + b; }

// Stage 2: __VA_OPT__ expansion
auto add(int a, int b)
    noexcept(noexcept(a + b))
    -> decltype(auto)
    requires(requires { a + b; })
    { return a + b; }

// Final expanded code
auto add(int a, int b)
    noexcept(true)  // a + b is noexcept for int
    -> decltype(auto)  // deduces to int
    requires(requires { a + b; })  // validates expression
    { return a + b; }
```

## Best Practices

### When to Use Arrow Macros

**Good Uses:**
- Single-expression functions
- Simple forwarding functions
- Getter/setter methods
- Mathematical operations
- Type conversions

**Avoid For:**
- Complex multi-statement logic
- Functions with local variables
- Loop-based algorithms
- Resource management (RAII)

### Performance Considerations

Arrow macros have **zero runtime overhead**:
- Expand at preprocessing time
- Generate optimal code
- Enable better inlining
- Preserve noexcept correctness

### Debugging Tips

To see macro expansion:
```bash
# GCC/Clang
g++ -E -P file.cpp

# MSVC
cl /P /EP file.cpp
```

## Integration with Other Systems

### Concepts Integration

Arrow macros work seamlessly with C++20 concepts:

```cpp
template<typename T>
    requires std::integral<T>
auto increment(T value) XIEITE_ARROW(value + 1)
```

### Template Metaprogramming

Perfect for SFINAE and template specialization:

```cpp
template<typename T, typename = void>
struct has_size : std::false_type {};

template<typename T>
struct has_size<T, std::void_t<
    decltype(std::declval<T>() XIEITE_ARROW(size()))
>> : std::true_type {};
```

### Coroutines

Compatible with C++20 coroutines:

```cpp
auto async_compute(int x) -> Task<int>
    XIEITE_ARROW(co_return x * 2)
```

## Common Patterns

### Property Access

```cpp
class Property {
    int value_;
public:
    auto get() const XIEITE_ARROW(value_)
    auto set(int v) XIEITE_ARROW_NOEX(value_ = v)
};
```

### Operator Overloading

```cpp
struct Point {
    double x, y;

    auto operator+(const Point& p) const
        XIEITE_ARROW(Point{x + p.x, y + p.y})

    auto operator==(const Point& p) const
        XIEITE_ARROW(x == p.x && y == p.y)
};
```

### Factory Functions

```cpp
template<typename T, typename... Args>
auto make_unique_ptr(Args&&... args)
    XIEITE_ARROW(std::make_unique<T>(std::forward<Args>(args)...))
```

## Limitations and Workarounds

### Multiple Statements

Arrow macros don't support multiple statements directly:

```cpp
// Won't work
auto process(int x) XIEITE_ARROW(
    log(x);  // Error: multiple statements
    return x * 2;
)

// Workaround: Use lambda
auto process(int x) XIEITE_ARROW(
    [&] { log(x); return x * 2; }()
)
```

### Local Variables

Cannot declare local variables:

```cpp
// Won't work
auto compute(int x) XIEITE_ARROW(
    int temp = x * 2;  // Error: declaration
    return temp + 1;
)

// Workaround: Helper function
auto compute_impl(int x) {
    int temp = x * 2;
    return temp + 1;
}
auto compute(int x) XIEITE_ARROW(compute_impl(x))
```

---

*Next: [Arrow Macros Detail](arrow_macros.md) | [Preprocessor Patterns](preprocessor_patterns.md)*