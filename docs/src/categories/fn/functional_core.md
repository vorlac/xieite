# Core Functional Programming Utilities

## Overview

XIEITE provides functional programming utilities that leverage modern C++20 features. This document covers the available utilities in the functional module.

## Available Utilities

### Type-Erased Function Wrapper

#### fn
**`xieite::fn<Signature>`** - Enhanced std::function with noexcept support:

Key advantages over std::function:
- **Noexcept support**: Can wrap and guarantee noexcept functions
- **Optimized implementation**: Designed for efficiency

```cpp
// Regular function
xieite::fn<int(int, int)> add = [](int a, int b) { return a + b; };
int result = add(5, 3);  // 8

// Noexcept function
xieite::fn<int(int) noexcept> safe_abs = [](int x) noexcept {
    return x < 0 ? -x : x;
};
static_assert(noexcept(safe_abs(-5)));  // Guaranteed noexcept

// Stateful lambda
int counter = 0;
xieite::fn<void()> increment = [&counter]() { ++counter; };
increment();  // counter = 1
```

### Memoization

#### memoize
**`xieite::memoize(func)`** - Automatic result caching:

Features:
- **Transparent caching**: No code changes needed
- **Perfect forwarding**: Efficient argument passing

```cpp
// Example with Y combinator for recursion
auto fib = xieite::memoize(
    xieite::y_combinator([](auto self, int n) -> int {
        if (n <= 1) return n;
        return self(n-1) + self(n-2);
    })
);

int result = fib(40);  // Fast due to caching
```

### Y Combinator

#### y_combinator
**`xieite::y_combinator`** - Enable lambda recursion:

Allows recursive lambdas without std::function overhead:

```cpp
// Factorial with Y combinator
auto factorial = xieite::y_combinator(
    [](auto self, int n) -> int {
        return (n <= 1) ? 1 : n * self(n - 1);
    }
);

int fact5 = factorial(5);  // 120

// Tree traversal
struct Node {
    int value;
    std::vector<Node> children;
};

auto sum_tree = xieite::y_combinator(
    [](auto self, const Node& node) -> int {
        int sum = node.value;
        for (const auto& child : node.children) {
            sum += self(child);
        }
        return sum;
    }
);
```

### Argument Distribution

#### distribute_args
**`xieite::distribute_args(funcs...)`** - Distribute args to multiple functions:

```cpp
// Apply multiple operations to the same input
auto analyze = xieite::distribute_args(
    [](int x) { return x * 2; },      // Double
    [](int x) { return x + 10; },     // Add 10
    [](int x) { return x % 2 == 0; }  // Is even?
);

auto [doubled, plus10, is_even] = analyze(5);
// doubled = 10, plus10 = 15, is_even = false
```

## Performance Considerations

- **Type Erasure**: Small overhead for virtual dispatch in `fn`
- **Memoization**: O(1) lookup after first call, memory usage grows with unique inputs
- **Y Combinator**: Zero overhead, purely compile-time
- **Argument distribution**: Minimal overhead for tuple creation

## Best Practices

1. **Use Y combinator for recursive lambdas**:
   ```cpp
   // Cleaner than std::function self-reference
   auto recursive = xieite::y_combinator([](auto self, int n) {
       return n <= 0 ? 0 : n + self(n - 1);
   });
   ```

2. **Memoize expensive pure functions**:
   ```cpp
   // Cache results automatically
   auto expensive = xieite::memoize(compute_heavy_result);
   ```

3. **Use distribute_args for parallel analysis**:
   ```cpp
   // Apply multiple functions to same input
   auto multi_analyze = xieite::distribute_args(func1, func2, func3);
   ```

## Functional Programming Patterns Not Provided

XIEITE does not provide built-in utilities for some common functional programming patterns. For guidance on implementing these patterns manually, see:

- [Currying Patterns](./currying.md) - Manual currying implementation techniques
- [Function Composition Patterns](./composition.md) - Composition implementation techniques

These patterns can be implemented using standard C++ features and the techniques shown in those guides.

---

*Next: [Guards and Wrappers](guards_and_wrappers.md)*