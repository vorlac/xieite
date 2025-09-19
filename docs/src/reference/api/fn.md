# Functional API Reference

## Overview

The functional category contains 35 header files providing utility functions, guards, combinators, and helper utilities optimized for both compile-time and runtime use.

## Organization

The fn headers are organized into functional groups:

- **Function Utilities** (10+ headers): Basic function manipulation utilities
- **Guards & RAII** (5+ headers): Scope guards and resource management
- **Type Utilities** (8+ headers): Type casting and manipulation
- **Argument Manipulation** (5+ headers): Argument processing and distribution
- **Combinators** (7+ headers): Function combinators and utilities

## Function Utilities

### `fn`
- **Header**: `fn/fn.hpp`
- **Synopsis**: Function wrapper utilities
- **Purpose**: Basic function wrapper and utilities

### `memoize`
- **Header**: `fn/memoize.hpp`
- **Synopsis**: `auto memoize(F&& f)`
- **Purpose**: Cache function results
- **Example**:
```cpp
auto expensive = xieite::memoize([](int x) {
    // expensive computation
    return x * x * x;
});

auto result = expensive(10);  // Computed once
auto cached = expensive(10);  // Retrieved from cache
```

### `y_combinator`
- **Header**: `fn/y_combinator.hpp`
- **Synopsis**: `auto y_combinator(F&& f)`
- **Purpose**: Fixed-point combinator for recursion
- **Example**:
    ```cpp
    auto factorial = xieite::y_combinator(
        [](auto self, int n) -> int {
            return n <= 1 ? 1 : n * self(n - 1);
        }
    );

    auto result = factorial(5);  // 120
    ```

### `noex`
- **Header**: `fn/noex.hpp`
- **Synopsis**: Noexcept function utilities
- **Purpose**: Handle noexcept function specifications

### `discardable`
- **Header**: `fn/discardable.hpp`
- **Synopsis**: Mark results as safely discardable
- **Purpose**: Indicate functions whose return values can be ignored

## Guards & RAII

### `scope_guard`
- **Header**: `fn/scope_guard.hpp`
- **Synopsis**: `class scope_guard<F>`
- **Purpose**: Execute function on scope exit
- **Example**:
    ```cpp
    {
        auto guard = xieite::scope_guard([]{
            std::cout << "Cleanup\n";
        });
        // ... code ...
    }  // Cleanup executed here
    ```

### `process_guard`
- **Header**: `fn/process_guard.hpp`
- **Synopsis**: Process-level guard utilities
- **Purpose**: Guard resources at process level

## Type Utilities

### `as`
- **Header**: `fn/as.hpp`
- **Synopsis**: `auto as<T>(auto&& value)`
- **Purpose**: Type conversion utility
- **Example**:
```cpp
auto x = xieite::as<double>(42);  // Convert to double
```

### `cast`
- **Header**: `fn/cast.hpp`
- **Synopsis**: Safe casting utilities
- **Purpose**: Enhanced casting operations

### `try_opt`
- **Header**: `fn/try_opt.hpp`
- **Synopsis**: `auto try_opt(auto&& fn, auto&&... args)`
- **Purpose**: Execute function safely, returning optional with result or nullopt on exception
- **Description**: Wraps function calls in try-catch and returns std::optional. Returns nullopt if the function throws an exception, otherwise returns the result wrapped in optional.
- **Example**:
    ```cpp
    #include <xieite/fn/try_opt.hpp>
    #include <optional>
    #include <string>

    auto divide = [](int a, int b) -> int {
        if (b == 0) throw std::runtime_error("Division by zero");
        return a / b;
    };

    auto result1 = xieite::try_opt(divide, 10, 2);  // optional{5}
    auto result2 = xieite::try_opt(divide, 10, 0);  // nullopt

    if (result1) {
        std::cout << "Result: " << *result1 << std::endl;  // "Result: 5"
    }
    ```

### `visitor`
- **Header**: `fn/visitor.hpp`
- **Synopsis**: `template<typename... Fns> struct visitor : Fns...`
- **Purpose**: Create visitors for std::variant and similar types using multiple lambdas
- **Description**: Combines multiple function objects into a single visitor that can handle different types. Uses using declarations to bring all operator() overloads into scope. Perfect for std::visit with variants.
- **Example**:
    ```cpp
    #include <xieite/fn/visitor.hpp>
    #include <variant>
    #include <string>
    #include <iostream>

    using Value = std::variant<int, std::string, double>;

    auto visitor = xieite::visitor{
        [](int x) {
            std::cout << "Integer: " << x << std::endl;
        },
        [](const std::string& s) {
            std::cout << "String: " << s << std::endl;
        },
        [](double d) {
            std::cout << "Double: " << d << std::endl;
        }
    };

    Value v1 = 42;
    Value v2 = std::string("hello");
    Value v3 = 3.14;

    std::visit(visitor, v1);  // "Integer: 42"
    std::visit(visitor, v2);  // "String: hello"
    std::visit(visitor, v3);  // "Double: 3.14"
    ```

## Argument Manipulation

### `reverse_args`
- **Header**: `fn/reverse_args.hpp`
- **Synopsis**: `auto reverse_args(F&& f)`
- **Purpose**: Reverse function arguments
- **Example**:
```cpp
auto divide = [](int a, int b) { return a / b; };
auto reversed = xieite::reverse_args(divide);
auto result = reversed(2, 10);  // 10/2 = 5
```

### `rotate_args`
- **Header**: `fn/rotate_args.hpp`
- **Synopsis**: `auto rotate_args(F&& f)`
- **Purpose**: Rotate function arguments
- **Example**:
```cpp
auto f = [](int a, int b, int c) {
    return std::vector{a, b, c};
};
auto rotated = xieite::rotate_args(f);
auto result = rotated(1, 2, 3);  // Rotated argument order
```

### `distribute_args`
- **Header**: `fn/distribute_args.hpp`
- **Synopsis**: Distribute arguments across multiple functions
- **Purpose**: Apply arguments to multiple functions

### `apply_array`
- **Header**: `fn/apply_array.hpp`
- **Synopsis**: Apply function to array elements
- **Purpose**: Array-based function application

### `apply_as_tuple`
- **Header**: `fn/apply_as_tuple.hpp`
- **Synopsis**: Apply function with tuple arguments
- **Purpose**: Tuple unpacking for function calls

### `min_args`
- **Header**: `fn/min_args.hpp`
- **Synopsis**: Minimum argument utilities
- **Purpose**: Handle functions with minimum argument requirements

## Combinators & Logic

### `all_true`
- **Header**: `fn/all_true.hpp`
- **Synopsis**: `template<typename Predicate, typename... Args> bool all_true(Predicate&& pred, Args&&... args)`
- **Purpose**: Check if predicate returns true for all arguments
- **Example**:
```cpp
auto is_positive = [](int x) { return x > 0; };
bool result = xieite::all_true(is_positive, 1, 2, 3);  // true
bool result2 = xieite::all_true(is_positive, 1, -2, 3);  // false
```

### `any_true`
- **Header**: `fn/any_true.hpp`
- **Synopsis**: `template<typename Predicate, typename... Args> bool any_true(Predicate&& pred, Args&&... args)`
- **Purpose**: Check if predicate returns true for any argument
- **Example**:
```cpp
auto is_positive = [](int x) { return x > 0; };
bool result = xieite::any_true(is_positive, -1, -2, 3);  // true
bool result2 = xieite::any_true(is_positive, -1, -2, -3);  // false
```

### `also`
- **Header**: `fn/also.hpp`
- **Synopsis**: Combinator for side effects
- **Purpose**: Perform side effects while passing through values

### `analog`
- **Header**: `fn/analog.hpp`
- **Synopsis**: Analog computation utilities
- **Purpose**: Analog-style computations and transformations

## User-Defined Literals

### `fstr_udl`
- **Header**: `fn/fstr_udl.hpp`
- **Synopsis**: Fixed string user-defined literals
- **Purpose**: Compile-time string literals

### `exp_udl`
- **Header**: `fn/exp_udl.hpp`
- **Synopsis**: Exponent user-defined literals
- **Purpose**: Scientific notation literals

### `number_udl`
- **Header**: `fn/number_udl.hpp`
- **Synopsis**: Number user-defined literals
- **Purpose**: Enhanced numeric literals

### `radix_udl`
- **Header**: `fn/radix_udl.hpp`
- **Synopsis**: Radix user-defined literals
- **Purpose**: Different base number literals

### `range_udl`
- **Header**: `fn/range_udl.hpp`
- **Synopsis**: Range user-defined literals
- **Purpose**: Range creation literals

### `unit_udl`
- **Header**: `fn/unit_udl.hpp`
- **Synopsis**: Unit user-defined literals
- **Purpose**: Physical unit literals

## Utility Functions

### `repeat`
- **Header**: `fn/repeat.hpp`
- **Synopsis**: `auto repeat(F&& f, std::size_t n)`
- **Purpose**: Repeat function execution
- **Example**:
```cpp
int counter = 0;
xieite::repeat([&]{ ++counter; }, 5);
// counter == 5
```

### `unroll`
- **Header**: `fn/unroll.hpp`
- **Synopsis**: Loop unrolling utilities
- **Purpose**: Compile-time loop unrolling

### `rotate_swap`
- **Header**: `fn/rotate_swap.hpp`
- **Synopsis**: Rotate and swap operations
- **Purpose**: Rotating swap algorithms

### `range_cmp`
- **Header**: `fn/range_cmp.hpp`
- **Synopsis**: Range comparison utilities
- **Purpose**: Compare ranges with custom logic

### `time`
- **Header**: `fn/time.hpp`
- **Synopsis**: Timing utilities
- **Purpose**: Function timing and profiling

### `tmp`
- **Header**: `fn/tmp.hpp`
- **Synopsis**: Template utilities
- **Purpose**: Template metaprogramming helpers

### `mixfix`
- **Header**: `fn/mixfix.hpp`
- **Synopsis**: Mixfix notation utilities
- **Purpose**: Custom operator syntax

### `synth_three_way`
- **Header**: `fn/synth_three_way.hpp`
- **Synopsis**: Synthesized three-way comparison
- **Purpose**: Generate three-way comparison operators

## Usage Examples

### Basic Function Utilities
```cpp
#include <xieite/fn/memoize.hpp>
#include <xieite/fn/reverse_args.hpp>

// Memoization
auto expensive = xieite::memoize([](int x) { return x * x; });

// Argument reversal
auto divide = [](int a, int b) { return a / b; };
auto rev_divide = xieite::reverse_args(divide);
```

### Scope Management
```cpp
#include <xieite/fn/scope_guard.hpp>

void process_file(const std::string& path) {
    auto* file = fopen(path.c_str(), "r");
    auto guard = xieite::scope_guard([file]{
        if (file) fclose(file);
    });
    // Process file...
    // File automatically closed
}
```

### Logic Combinators
```cpp
#include <xieite/fn/all_true.hpp>
#include <xieite/fn/any_true.hpp>

auto is_valid = [](const auto& item) { return item.isValid(); };
bool all_valid = xieite::all_true(is_valid, item1, item2, item3);
bool any_valid = xieite::any_true(is_valid, item1, item2, item3);
```

### `Recursion`
```cpp
#include <xieite/fn/y_combinator.hpp>

auto gcd = xieite::y_combinator([](auto self, int a, int b) -> int {
    return b == 0 ? a : self(b, a % b);
});
auto result = gcd(24, 36);  // 12
```

## Performance Notes

- Memoization trades memory for speed
- Scope guards have minimal overhead
- Y-combinator enables efficient tail recursion
- User-defined literals are compile-time constructs
- Most utilities are header-only with inline optimizations

## See Also

- [Functional Overview](../../categories/fn/)
- [Meta Programming API](./meta.md)
- [Data Structures API](./data.md)
