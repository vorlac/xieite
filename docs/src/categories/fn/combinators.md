# Combinator Patterns

## Overview

XIEITE provides functional combinators for advanced function composition, argument manipulation, and recursive patterns. These utilities enable functional programming techniques including the Y combinator for recursion, argument transformation combinators, and generic visitor patterns.

## Fixed-Point Combinators

### Y Combinator
Implementation: `include/xieite/fn/y_combinator.hpp` (lines 9-10)

```cpp
constexpr auto y_combinator(auto&& fn)
XIEITE_ARROW([fn = XIEITE_FWD(fn)](auto&&... args) mutable
    XIEITE_ARROW(std::invoke(fn, fn, XIEITE_FWD(args)...)));
```

Enables anonymous recursion by providing the function itself as the first argument.

## Argument Manipulation Combinators

### Argument Reversal
Implementation: `include/xieite/fn/reverse_args.hpp` (lines 11-16)

```cpp
constexpr auto reverse_args(auto&& fn, auto&&... args)
XIEITE_ARROW(std::apply(XIEITE_FWD(fn),
    xieite::reverse_tuple(std::forward_as_tuple(XIEITE_FWD(args)...))));

template<typename T>
constexpr T reverse_args(auto&&... args)
XIEITE_ARROW_RET(xieite::reverse_args(XIEITE_LIFT(T), XIEITE_FWD(args)...));
```

Reverses the order of arguments before applying them to a function.

### Argument Rotation
Implementation: `include/xieite/fn/rotate_args.hpp` (lines 12-23)

```cpp
template<std::size_t distance>
constexpr auto rotate_args(auto&& fn, auto&&... args)
XIEITE_ARROW(xieite::unroll<sizeof...(args)>(
    []<std::size_t... i>(auto&& fn, auto&&... args)
        XIEITE_ARROW(std::invoke(XIEITE_FWD(fn),
            XIEITE_FWD(args...[(i + distance % sizeof...(args)) % sizeof...(args)])...)),
    XIEITE_FWD(fn), XIEITE_FWD(args)...));
```

Rotates function arguments by a specified distance before application.

### Argument Distribution
Implementation: `include/xieite/fn/distribute_args.hpp` (lines 15-25)

```cpp
template<std::size_t arity>
constexpr void distribute_args(auto&& fn, auto&&... args)
XIEITE_ARROW_RET(xieite::unroll<(sizeof...(args) / arity)>(
    []<std::size_t... i>(const auto& fn, const auto& args_tuple)
        XIEITE_ARROW((..., (void)std::apply(fn,
            xieite::subtuple<(i * arity), ((i + 1) * arity)>(std::move(args_tuple))))),
    fn, std::forward_as_tuple(XIEITE_FWD(args)...)));
```

Distributes arguments across multiple function calls with specified arity.

## Visitor Combinator

### Generic Visitor Pattern
Implementation: `include/xieite/fn/visitor.hpp` (lines 5-11)

```cpp
template<typename... Fns>
struct visitor : Fns... {
    using Fns::operator()...;
};

template<typename... Fns>
visitor(Fns...) -> visitor<Fns...>;
```

Combines multiple callable objects into a single overload set.

## Side-Effect Combinators

### Also Combinator
Implementation: `include/xieite/fn/also.hpp` (lines 13-25)

```cpp
template<xieite::has_cp_ctor T, std::invocable<T&&> Fn>
constexpr T also(T&& x, Fn&& fn = {})
noexcept(xieite::has_noex_cp_ctor<T> && xieite::is_noex_invoc<Fn, void(T&&)>);

template<xieite::has_cp_ctor T, std::invocable<> Fn>
constexpr T also(T&& x, Fn&& fn = {})
noexcept(xieite::has_noex_cp_ctor<T> && xieite::is_noex_invoc<Fn>);
```

Performs a side effect and returns the original value.

## Function Wrapper

### Type-Erased Function
Implementation: `include/xieite/fn/fn.hpp` (lines 17-69)

```cpp
template<typename Ret, typename... Args, bool noex>
struct fn<Ret(Args...) noexcept(noex)> {
    constexpr fn(const xieite::fn<Ret(Args...)>& fn) noexcept;

    template<xieite::is_invoc<Ret(Args...)> Fn>
    constexpr fn(Fn&& fn) noexcept;

    constexpr Ret operator()(Args... args) const noexcept(noex);
};
```

Provides type erasure for callable objects with specific signatures.

## Usage Examples

### Y Combinator for Anonymous Recursion
```cpp
#include <xieite/fn/y_combinator.hpp>

// Factorial using Y combinator
auto factorial = xieite::y_combinator([](auto self, int n) -> int {
    return (n <= 1) ? 1 : n * self(self, n - 1);
});

std::cout << "Factorial(5): " << factorial(5) << "\n";  // 120

// Fibonacci with Y combinator
auto fibonacci = xieite::y_combinator([](auto self, int n) -> int {
    return (n <= 1) ? n : self(self, n - 1) + self(self, n - 2);
});

std::cout << "Fibonacci(10): " << fibonacci(10) << "\n";  // 55
```

### Tree Traversal with Y Combinator
```cpp
#include <xieite/fn/y_combinator.hpp>

struct TreeNode {
    int value;
    std::unique_ptr<TreeNode> left, right;
};

// Anonymous tree sum using Y combinator
auto tree_sum = xieite::y_combinator([](auto self, const TreeNode* node) -> int {
    if (!node) return 0;
    return node->value + self(self, node->left.get()) + self(self, node->right.get());
});

// Build example tree
auto root = std::make_unique<TreeNode>();
root->value = 10;
root->left = std::make_unique<TreeNode>();
root->left->value = 5;
root->right = std::make_unique<TreeNode>();
root->right->value = 15;

std::cout << "Tree sum: " << tree_sum(root.get()) << "\n";  // 30
```

### Argument Manipulation Combinators
```cpp
#include <xieite/fn/reverse_args.hpp>
#include <xieite/fn/rotate_args.hpp>

// Function expecting (a, b, c)
auto subtract = [](int a, int b, int c) { return a - b - c; };

// Original order: 10 - 5 - 2 = 3
std::cout << "Original: " << subtract(10, 5, 2) << "\n";

// Reversed order: 2 - 5 - 10 = -13
std::cout << "Reversed: " << xieite::reverse_args(subtract, 10, 5, 2) << "\n";

// Rotated by 1: 5 - 2 - 10 = -7
std::cout << "Rotated: " << xieite::rotate_args<1>(subtract, 10, 5, 2) << "\n";
```

### Visitor Pattern for Variant Handling
```cpp
#include <xieite/fn/visitor.hpp>
#include <variant>

using Value = std::variant<int, double, std::string>;

// Create visitor with multiple handlers
auto printer = xieite::visitor{
    [](int i) { std::cout << "Integer: " << i << "\n"; },
    [](double d) { std::cout << "Double: " << d << "\n"; },
    [](const std::string& s) { std::cout << "String: " << s << "\n"; }
};

// Use with std::visit
std::vector<Value> values{42, 3.14, std::string("hello")};

for (const auto& value : values) {
    std::visit(printer, value);
}
// Output:
// Integer: 42
// Double: 3.14
// String: hello
```

### Argument Distribution for Batch Operations
```cpp
#include <xieite/fn/distribute_args.hpp>

// Function that takes 2 arguments
auto add_pair = [](int a, int b) {
    std::cout << a << " + " << b << " = " << (a + b) << "\n";
};

// Distribute 6 arguments as 3 pairs of 2
xieite::distribute_args<2>(add_pair, 1, 2, 3, 4, 5, 6);
// Output:
// 1 + 2 = 3
// 3 + 4 = 7
// 5 + 6 = 11
```

## Advanced Patterns

### Combinator Composition
```cpp
template<typename Combinator>
class CombinatorBuilder {
private:
    Combinator combinator_;

public:
    explicit CombinatorBuilder(Combinator c) : combinator_(c) {}

    // Fluent interface for chaining combinators
    template<typename NextCombinator>
    auto then(NextCombinator next) && {
        return CombinatorBuilder{[c = std::move(combinator_), n = std::move(next)]
                                (auto&& fn, auto&&... args) {
            return n(c(std::forward<decltype(fn)>(fn)),
                    std::forward<decltype(args)>(args)...);
        }};
    }

    // Apply the composed combinator
    template<typename Fn, typename... Args>
    auto apply(Fn&& fn, Args&&... args) {
        return combinator_(std::forward<Fn>(fn), std::forward<Args>(args)...);
    }
};

// Helper function for creating combinator builder
template<typename Combinator>
auto make_combinator(Combinator c) {
    return CombinatorBuilder{std::move(c)};
}

// Usage - reverse then rotate arguments
auto composed = make_combinator(xieite::reverse_args)
                    .then([](auto fn) {
                        return [fn = std::move(fn)](auto&&... args) {
                            return xieite::rotate_args<1>(fn,
                                std::forward<decltype(args)>(args)...);
                        };
                    });

auto result = composed.apply(subtract, 10, 5, 2);
```

### Recursive Combinator Patterns
```cpp
// Mutual recursion with Y combinator
auto even_odd = xieite::y_combinator([](auto self, int n, bool check_even) -> bool {
    if (n == 0) return check_even;
    if (n == 1) return !check_even;
    return self(self, n - 2, check_even);
});

bool result_even = even_odd(10, true);   // true
bool result_odd = even_odd(9, false);    // true

// Tail-recursive factorial
auto tail_factorial = xieite::y_combinator([](auto self, int n, int acc = 1) -> int {
    return (n <= 1) ? acc : self(self, n - 1, acc * n);
});

int result = tail_factorial(5);  // 120
```

### Side-Effect Combinator Chains
```cpp
#include <xieite/fn/also.hpp>

// Chain side effects while maintaining value flow
auto process_value = [](int x) {
    return xieite::also(x * 2, [](int val) {
        std::cout << "Doubled to: " << val << "\n";
    });
};

// Chain multiple side effects
auto complex_processing = [](int x) {
    return xieite::also(
        xieite::also(x, [](int v) { std::cout << "Input: " << v << "\n"; }) * 3,
        [](int v) { std::cout << "Tripled to: " << v << "\n"; }
    );
};

int result = complex_processing(5);
// Output:
// Input: 5
// Tripled to: 15
// result = 15
```

## Implementation Details

### Y Combinator Strategy
The Y combinator (y_combinator.hpp:9-10) uses:
- Capture by move to preserve the function object
- Self-application pattern where the function receives itself as first parameter
- Perfect forwarding for argument preservation

### Argument Manipulation Architecture
The argument transformation combinators employ:
- `xieite::unroll` for compile-time parameter pack iteration (rotate_args.hpp:14)
- Tuple manipulation through `xieite::reverse_tuple` (reverse_args.hpp:12)
- Template parameter pack indexing with modular arithmetic (rotate_args.hpp:16)

### Visitor Pattern Implementation
The visitor combinator (visitor.hpp:5-7) provides:
- Multiple inheritance from all function types
- Using declarations to bring all operator() overloads into scope
- Deduction guide for automatic template parameter inference

### Type Erasure Design
The `fn` wrapper (fn.hpp:17-69) implements:
- Virtual base class for type erasure (lines 44-50)
- CRTP-style derived template for concrete types (lines 52-66)
- Clone pattern for copy semantics (line 49)

## Performance Considerations

- **Y Combinator**: Zero overhead abstraction - compiles to direct recursion
- **Argument manipulation**: Compile-time transformations with no runtime cost
- **Visitor pattern**: Virtual dispatch overhead for polymorphic calls
- **Type erasure**: Heap allocation and virtual dispatch costs

## Best Practices

1. **Use Y combinator for complex anonymous recursion** - Cleaner than named recursive lambdas
2. **Prefer argument combinators for reusable transformations** - Compose functions rather than rewrite
3. **Leverage visitor pattern for variant handling** - Cleaner than manual visitation
4. **Consider performance implications of type erasure** - Use only when polymorphism is needed

## Common Use Cases

### Algorithm Composition
```cpp
// Compose sorting with transformation
auto sort_and_transform = [](auto container, auto transform) {
    std::sort(container.begin(), container.end());
    return xieite::also(std::move(container), [&transform](const auto& c) {
        std::transform(c.begin(), c.end(), c.begin(), transform);
    });
};
```

### Recursive Data Processing
```cpp
// Process nested data structures
auto process_nested = xieite::y_combinator([](auto self, const auto& data) {
    if constexpr (/* is leaf type */) {
        return process_leaf(data);
    } else {
        return transform(data, [&self](const auto& child) { return self(self, child); });
    }
});
```

## See Also

- [Function Composition](./composition.md) - Function combination utilities
- [Memoization](./memoization.md) - Function result caching
- [Currying](./currying.md) - Partial function application
- [Functional API Reference](../../reference/api/fn.md)