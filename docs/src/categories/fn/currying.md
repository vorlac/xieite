# Currying & Partial Application Patterns

## Overview

**Note: XIEITE does not provide built-in currying or partial application utilities.** This document explains these functional programming patterns and how they can be implemented in C++ using modern language features.

Currying and partial application are powerful functional programming techniques that transform multi-parameter functions into sequences of single-parameter functions, enabling flexible argument binding and function composition.

## Currying Fundamentals

### What is Currying?
Currying transforms a function that takes multiple arguments into a sequence of functions that each take a single argument:

```cpp
// Original function: (a, b, c) -> result
auto add3 = [](int a, int b, int c) { return a + b + c; };

// Manual currying example:
auto add3_curried = [](int a) {
    return [a](int b) {
        return [a, b](int c) {
            return a + b + c;
        };
    };
};
auto result = add3_curried(10)(20)(30);  // 60
```

### Mathematical Foundation
Currying is based on the isomorphism between multi-argument functions and higher-order functions:
- `(A × B) → C` is isomorphic to `A → (B → C)`
- Named after Haskell Curry, though introduced by Moses Schönfinkel

## Example Currying Implementation

**Note: The following implementations are examples of how currying could be implemented - they are not provided by XIEITE.**

### Basic Curry Implementation
```cpp
// Example implementation (not provided by XIEITE)
template<typename F>
class curry_wrapper {
    F func_;

public:
    explicit curry_wrapper(F f) : func_(std::move(f)) {}

    template<typename... Args>
    auto operator()(Args&&... args) const {
        if constexpr (std::is_invocable_v<F, Args...>) {
            return func_(std::forward<Args>(args)...);
        } else {
            return curry_wrapper{
                [f = func_, ...bound = std::forward<Args>(args)]
                <typename... Rest>(Rest&&... rest) {
                    return f(bound..., std::forward<Rest>(rest)...);
                }
            };
        }
    }
};

// Example usage function (not provided by XIEITE)
template<typename F>
auto curry(F&& f) {
    return curry_wrapper{std::forward<F>(f)};
}
```

## Partial Application Examples

### Left Partial Application
```cpp
// Example implementation (not provided by XIEITE)
template<typename F, typename... BoundArgs>
auto partial(F&& f, BoundArgs&&... bound) {
    return [f = std::forward<F>(f),
            ...bound = std::forward<BoundArgs>(bound)]
           <typename... FreeArgs>(FreeArgs&&... free) {
               return f(bound..., std::forward<FreeArgs>(free)...);
           };
}

// Example usage (using custom implementation)
auto multiply = [](int a, int b, int c) { return a * b * c; };
auto times_10 = partial(multiply, 10);  // Custom implementation
auto result = times_10(2, 3);  // 60
```

### Right Partial Application
```cpp
// Example implementation (not provided by XIEITE)
template<typename F, typename... BoundArgs>
auto partial_right(F&& f, BoundArgs&&... bound) {
    return [f = std::forward<F>(f),
            ...bound = std::forward<BoundArgs>(bound)]
           <typename... FreeArgs>(FreeArgs&&... free) {
               return f(std::forward<FreeArgs>(free)..., bound...);
           };
}

// Example usage (using custom implementation)
auto divide = [](double a, double b) { return a / b; };
auto divide_by_2 = partial_right(divide, 2.0);  // Custom implementation
auto result = divide_by_2(10.0);  // 5.0
```

## Practical Application Patterns

**Note: These examples show conceptual usage patterns. XIEITE does not provide these utilities.**

### Manual Function Factories
```cpp
// Manual currying approach (no XIEITE utility needed)
auto make_multiplier = [](int factor) {
    return [factor](int value) {
        return factor * value;
    };
};

auto double_it = make_multiplier(2);
auto triple_it = make_multiplier(3);
```

### Using std::bind for Partial Application
```cpp
#include <functional>

auto multiply = [](int a, int b, int c) { return a * b * c; };

// Using standard library for partial application
auto times_10 = std::bind(multiply, 10, std::placeholders::_1, std::placeholders::_2);
auto result = times_10(2, 3);  // 60
```

## Implementation Considerations

**Since XIEITE does not provide currying utilities, consider these approaches:**

1. **Manual currying** using nested lambdas for simple cases
2. **std::bind** for basic partial application needs
3. **Custom implementations** for complex currying requirements
4. **Third-party libraries** like functional-plus or range-v3
5. **Template metaprogramming** for compile-time currying

## Common Pitfalls

1. **Reference lifetime** - Be careful with reference parameters in closures
2. **Evaluation order** - Curried functions may capture by value
3. **Template instantiation** - Can lead to code bloat
4. **Type deduction** - May need explicit types for complex functions

## Standard Library Alternatives

- `std::bind` and `std::placeholders` for partial application
- `std::function` for type erasure
- Lambda expressions for manual currying
- Template metaprogramming for compile-time solutions

## See Also

- [Function Composition Patterns](./composition.md)
- C++ Standard Library `<functional>` header
- Template metaprogramming techniques