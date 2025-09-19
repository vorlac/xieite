# XIEITE Functional Module

## Overview

The XIEITE functional module provides functional programming utilities for C++20 and beyond. The module includes type-erased functions, memoization, recursion combinators, RAII guards, and user-defined literals.

## Available Utilities

### Type-Erased Functions
- **`fn`** - Enhanced function wrapper with noexcept support

### Memoization
- **`memoize`** - Automatic result caching for functions

### Recursion
- **`y_combinator`** - Enables lambda recursion without std::function overhead

### Argument Manipulation
- **`distribute_args`** - Apply multiple functions to the same arguments

### Guards and Resource Management
- **`process_guard`** - RAII for process management
- **Scope guards** - Automatic cleanup patterns

### User-Defined Literals
- **Numeric literals** - Type-safe numeric parsing
- **String literals** - Enhanced string handling
- **Memory size literals** - Unit-safe memory sizes

## Key Features

### Enhanced Type Erasure
The `fn` wrapper improves on std::function:
```cpp
// Noexcept guarantee
xieite::fn<int(int) noexcept> safe_func = [](int x) noexcept {
    return x * 2;
};
static_assert(noexcept(safe_func(5)));

// Lighter weight than std::function
xieite::fn<void()> callback = []{ process(); };
```

### Automatic Memoization
Cache expensive computations transparently:
```cpp
auto fibonacci = xieite::memoize(
    xieite::y_combinator([](auto self, int n) -> int {
        if (n <= 1) return n;
        return self(n-1) + self(n-2);
    })
);

int result = fibonacci(40);  // Fast with caching
```

### Lambda Recursion
```cpp
auto factorial = xieite::y_combinator(
    [](auto self, int n) -> int {
        return (n <= 1) ? 1 : n * self(n - 1);
    }
);

int fact5 = factorial(5);  // 120
```

## Design Philosophy

### Zero-Overhead Abstractions
- Compile-time optimizations where possible
- Minimal runtime overhead for type erasure
- Efficient memory usage

### Type Safety
- Strong typing with user-defined literals
- Compile-time validation
- Concept-constrained templates

### RAII Everywhere
- Automatic resource management
- Exception safety guarantees
- Deterministic cleanup

## Note on Functional Programming Patterns

While XIEITE does not provide built-in utilities for all functional programming patterns (such as currying or function composition), the documentation includes guides on how to implement these patterns using modern C++ features. See:

- [Currying Patterns](./currying.md) - How to implement currying manually
- [Function Composition Patterns](./composition.md) - Composition techniques

---

*Return to [XIEITE Documentation Home](../../index.md)*