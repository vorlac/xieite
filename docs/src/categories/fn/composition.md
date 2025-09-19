# Function Composition Patterns

## Overview

**Note: XIEITE does not provide built-in function composition utilities.** This document explains function composition patterns and how they can be implemented in C++ using modern language features.

Function composition is a fundamental functional programming concept that enables building complex operations from simple, reusable functions through mathematical composition, piping, and chaining mechanisms.

## Composition Fundamentals

### Mathematical Composition
Function composition follows mathematical principles where `(f ∘ g)(x) = f(g(x))`:

```cpp
auto add_one = [](int x) { return x + 1; };
auto double_it = [](int x) { return x * 2; };

// Manual composition: first apply g, then f
auto f = [=](int x) { return double_it(add_one(x)); };
auto result = f(5);  // double_it(add_one(5)) = 12
```

### Pipeline Composition
Pipeline composition provides intuitive left-to-right data flow:

```cpp
auto add_one = [](int x) { return x + 1; };
auto double_it = [](int x) { return x * 2; };

// Pipeline approach: left to right
auto f = [=](int x) {
    auto temp = add_one(x);
    return double_it(temp);
};
auto result = f(5);  // 12
```

## Example Composition Implementations

**Note: The following implementations are examples of how composition could be implemented - they are not provided by XIEITE.**

### Binary Composition
```cpp
// Example implementation (not provided by XIEITE)
template<typename F, typename G>
auto compose(F&& f, G&& g) {
    return [f = std::forward<F>(f), g = std::forward<G>(g)]
           <typename... Args>(Args&&... args) {
               return f(g(std::forward<Args>(args)...));
           };
}

// Example usage
auto sqrt_abs = compose(std::sqrt, std::abs);
auto result = sqrt_abs(-16.0);  // 4.0
```

### Pipeline Composition
```cpp
// Example implementation (not provided by XIEITE)
template<typename F, typename G>
auto pipe(F&& f, G&& g) {
    return [f = std::forward<F>(f), g = std::forward<G>(g)]
           <typename... Args>(Args&&... args) {
               return g(f(std::forward<Args>(args)...));
           };
}

// Example usage
auto process = pipe(add_one, double_it);
auto result = process(5);  // 12
```

### Variadic Composition
```cpp
// Example implementation (not provided by XIEITE)
template<typename F, typename... Fs>
auto compose_all(F&& f, Fs&&... fs) {
    if constexpr (sizeof...(fs) == 0) {
        return std::forward<F>(f);
    } else {
        return compose(std::forward<F>(f),
                      compose_all(std::forward<Fs>(fs)...));
    }
}

// Example usage
auto process = compose_all(
    [](int x) { return x * x; },      // Last
    [](int x) { return x + 10; },     // Middle
    [](int x) { return x * 2; }       // First
);
auto result = process(5);  // ((5 * 2) + 10)² = 400
```

## Advanced Composition Patterns

### Conditional Composition
```cpp
// Example implementation (not provided by XIEITE)
template<typename Pred, typename F, typename G>
auto compose_if(Pred&& pred, F&& f, G&& g) {
    return [=]<typename T>(T&& x) -> decltype(auto) {
        if (pred(x)) {
            return f(g(std::forward<T>(x)));
        } else {
            return std::forward<T>(x);
        }
    };
}

// Example usage
auto safe_sqrt = compose_if(
    [](double x) { return x >= 0; },
    std::sqrt,
    std::abs
);
```

### Parallel Composition
```cpp
// Example implementation (not provided by XIEITE)
template<typename... Fs>
auto parallel(Fs&&... fs) {
    return [=]<typename T>(T&& x) {
        return std::make_tuple(fs(x)...);
    };
}

// Example usage
auto analyze = parallel(
    [](const auto& data) { return data.size(); },
    [](const auto& data) { return data.empty(); },
    [](const auto& data) { return data.front(); }
);

auto [size, empty, first] = analyze(container);
```

## Manual Composition Techniques

### Using Operator Overloading
```cpp
// Custom operator for composition (not provided by XIEITE)
template<typename F, typename G>
    requires std::is_invocable_v<F, std::invoke_result_t<G, int>>
auto operator|(G&& g, F&& f) {
    return [f = std::forward<F>(f), g = std::forward<G>(g)](auto&& x) {
        return f(g(std::forward<decltype(x)>(x)));
    };
}

// Usage example
auto process = add_one | double_it | negate;
```

### Chaining with Method Calls
```cpp
// Fluent interface approach
template<typename T>
class composable {
    T value_;
public:
    explicit composable(T val) : value_(std::move(val)) {}

    template<typename F>
    auto then(F&& f) && {
        return composable{f(std::move(value_))};
    }

    const T& get() const { return value_; }
};

// Usage
auto result = composable{5}
    .then(add_one)
    .then(double_it)
    .get();  // 12
```

## Practical Application Patterns

**Note: These examples show conceptual usage patterns. XIEITE does not provide these utilities.**

### Data Processing Pipeline
```cpp
// Manual pipeline approach
auto process_data = [](const std::string& input) {
    auto trimmed = trim(input);
    auto lowered = to_lower(trimmed);
    auto words = split(lowered, ' ');
    return filter(words, [](const auto& w) {
        return w.length() > 3;
    });
};

auto result = process_data("  Hello WORLD from C++  ");
```

### Error Handling Pipeline
```cpp
template<typename T>
using maybe = std::optional<T>;

auto safe_divide = [](double x, double y) -> maybe<double> {
    return y != 0 ? maybe{x / y} : std::nullopt;
};

auto safe_sqrt = [](double x) -> maybe<double> {
    return x >= 0 ? maybe{std::sqrt(x)} : std::nullopt;
};

// Manual monadic composition
auto safe_computation = [](double x, double y) -> maybe<double> {
    if (auto div = safe_divide(x, y)) {
        return safe_sqrt(*div);
    }
    return std::nullopt;
};
```

## Implementation Considerations

**Since XIEITE does not provide composition utilities, consider these approaches:**

1. **Manual composition** using nested function calls
2. **Lambda chaining** for simple pipelines
3. **Custom operator overloading** for syntactic sugar
4. **Fluent interfaces** for method chaining
5. **Third-party libraries** like range-v3 or functional-plus

## Performance Considerations

1. **Inlining** - Modern compilers often optimize function composition
2. **Template instantiation** - Can lead to code bloat with complex chains
3. **Reference forwarding** - Use perfect forwarding to avoid copies
4. **Compile-time composition** - Consider constexpr for static chains

## Standard Library Approaches

### Using std::invoke
```cpp
#include <functional>

template<typename F, typename G>
auto compose_invoke(F&& f, G&& g) {
    return [f, g](auto&&... args) {
        return std::invoke(f, std::invoke(g, std::forward<decltype(args)>(args)...));
    };
}
```

### Using std::function for Type Erasure
```cpp
#include <functional>

std::function<int(int)> create_pipeline() {
    return [](int x) {
        return double_it(add_one(x));
    };
}
```

## See Also

- [Currying Patterns](./currying.md)
- C++ Standard Library `<functional>` header
- Range-v3 library for advanced composition
- Functional programming techniques in C++