# Memoization

## Overview

XIEITE provides function memoization utilities that automatically cache function results based on input parameters. The memoization system uses compile-time constraints to ensure optimal performance and only applies caching when beneficial and possible.

## Core Memoization Function

### Automatic Function Memoization
Implementation: `include/xieite/fn/memoize.hpp` (lines 52-74)

```cpp
template<typename Fn, typename... Args>
requires(std::regular_invocable<Fn, Args...>)
std::invoke_result_t<Fn, Args...> memoize(Fn fn, const Args&... args)
noexcept(std::is_nothrow_invocable_v<Fn, Args...>);
```

Automatically caches function results when conditions are met for efficient memoization.

## Memoization Infrastructure

### Memo Key Structure
Implementation: `include/xieite/fn/memoize.hpp` (lines 16-28)

```cpp
template<typename Fn, typename... Args>
struct memo {
    Fn fn;
    std::tuple<Args...> args;

    constexpr memo(const Fn& fn, const std::tuple<Args...>& args) noexcept;
    friend constexpr bool operator==(const memo&, const memo&) noexcept;
};
```

Encapsulates function and arguments as a composite key for memoization cache.

### Specialized Hash Function
Implementation: `include/xieite/fn/memoize.hpp` (lines 30-48)

```cpp
struct hash {
    using is_transparent = void;

    template<typename Fn, typename... Args>
    static std::size_t operator()(const memo<Fn, Args...>& memo) noexcept(false);
};
```

Provides efficient hashing for memo keys using `xieite::hash_combine` and `xieite::unroll`.

## Usage Examples

### Basic Function Memoization
```cpp
#include <xieite/fn/memoize.hpp>

// Expensive recursive function
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Memoized version
int memoized_fibonacci(int n) {
    if (n <= 1) return n;

    // Cache recursive calls automatically
    return xieite::memoize(memoized_fibonacci, n - 1) +
           xieite::memoize(memoized_fibonacci, n - 2);
}

// Usage
std::cout << "Fibonacci(40): " << memoized_fibonacci(40) << "\n";
// Much faster than direct recursive approach
```

### Complex Calculation Memoization
```cpp
#include <xieite/fn/memoize.hpp>

// Expensive mathematical operation
double complex_calculation(double x, double y, int iterations) {
    double result = x;
    for (int i = 0; i < iterations; ++i) {
        result = result * y + x / (i + 1);
    }
    return result;
}

void demonstrate_memoization() {
    // First call - computed and cached
    auto result1 = xieite::memoize(complex_calculation, 3.14, 2.71, 1000);
    std::cout << "Result 1: " << result1 << "\n";

    // Second call with same parameters - retrieved from cache
    auto result2 = xieite::memoize(complex_calculation, 3.14, 2.71, 1000);
    std::cout << "Result 2: " << result2 << " (cached)\n";

    // Different parameters - new computation
    auto result3 = xieite::memoize(complex_calculation, 1.41, 1.73, 500);
    std::cout << "Result 3: " << result3 << "\n";
}
```

### Lambda Function Memoization
```cpp
#include <xieite/fn/memoize.hpp>

void lambda_memoization() {
    // Memoizable lambda
    auto expensive_lambda = [](int base, int exponent) -> long long {
        long long result = 1;
        for (int i = 0; i < exponent; ++i) {
            result *= base;
        }
        return result;
    };

    // Cache lambda results
    std::cout << "2^20: " << xieite::memoize(expensive_lambda, 2, 20) << "\n";
    std::cout << "3^15: " << xieite::memoize(expensive_lambda, 3, 15) << "\n";
    std::cout << "2^20: " << xieite::memoize(expensive_lambda, 2, 20) << " (cached)\n";
}
```

## Advanced Patterns

### Conditional Memoization Wrapper
```cpp
template<typename Function>
class MemoizedFunction {
private:
    Function func_;

public:
    explicit MemoizedFunction(Function func) : func_(func) {}

    template<typename... Args>
    auto operator()(Args&&... args)
        -> decltype(xieite::memoize(func_, std::forward<Args>(args)...)) {
        return xieite::memoize(func_, std::forward<Args>(args)...);
    }

    // Access to original function for non-memoized calls
    Function& original() { return func_; }
    const Function& original() const { return func_; }
};

// Helper function for creating memoized functions
template<typename Function>
auto make_memoized(Function&& func) {
    return MemoizedFunction<std::decay_t<Function>>(std::forward<Function>(func));
}

// Usage
auto memoized_pow = make_memoized([](double base, int exp) -> double {
    double result = 1.0;
    for (int i = 0; i < exp; ++i) {
        result *= base;
    }
    return result;
});

double fast_power = memoized_pow(2.5, 10);  // Cached automatically
```

### Dynamic Programming with Memoization
```cpp
#include <xieite/fn/memoize.hpp>

class DynamicProgramming {
public:
    // Memoized longest common subsequence
    static int lcs(const std::string& str1, const std::string& str2,
                   size_t i = 0, size_t j = 0) {
        if (i >= str1.length() || j >= str2.length()) {
            return 0;
        }

        if (str1[i] == str2[j]) {
            return 1 + xieite::memoize(lcs, str1, str2, i + 1, j + 1);
        } else {
            return std::max(
                xieite::memoize(lcs, str1, str2, i + 1, j),
                xieite::memoize(lcs, str1, str2, i, j + 1)
            );
        }
    }

    // Memoized edit distance
    static int edit_distance(const std::string& str1, const std::string& str2,
                             size_t i = 0, size_t j = 0) {
        if (i >= str1.length()) return static_cast<int>(str2.length() - j);
        if (j >= str2.length()) return static_cast<int>(str1.length() - i);

        if (str1[i] == str2[j]) {
            return xieite::memoize(edit_distance, str1, str2, i + 1, j + 1);
        }

        return 1 + std::min({
            xieite::memoize(edit_distance, str1, str2, i + 1, j),     // Delete
            xieite::memoize(edit_distance, str1, str2, i, j + 1),     // Insert
            xieite::memoize(edit_distance, str1, str2, i + 1, j + 1)  // Replace
        });
    }
};

// Usage
std::string text1 = "kitten";
std::string text2 = "sitting";
int distance = DynamicProgramming::edit_distance(text1, text2);
std::cout << "Edit distance: " << distance << "\n";
```

### Cache-Aware Algorithm Design
```cpp
template<typename T>
class CacheAwareProcessor {
private:
    // Heavy computation that benefits from memoization
    static T heavy_transform(const T& input, int complexity_level) {
        T result = input;
        for (int level = 0; level < complexity_level; ++level) {
            // Simulate expensive transformation
            result = result * 2 + level;
        }
        return result;
    }

public:
    // Public interface always uses memoization
    static T transform(const T& input, int complexity_level) {
        return xieite::memoize(heavy_transform, input, complexity_level);
    }

    // Batch processing with automatic caching
    template<std::ranges::input_range Range>
    static std::vector<T> transform_batch(Range&& inputs, int complexity_level) {
        std::vector<T> results;
        results.reserve(std::ranges::size(inputs));

        for (const auto& input : inputs) {
            // Each unique input gets cached automatically
            results.push_back(transform(input, complexity_level));
        }

        return results;
    }
};

// Usage
CacheAwareProcessor<double> processor;
std::vector<double> data{1.0, 2.0, 1.0, 3.0, 2.0};  // Note duplicates
auto results = processor.transform_batch(data, 1000);
// Duplicates (1.0, 2.0) are computed only once due to memoization
```

## Implementation Details

### Compile-Time Constraints
The `memoize` function (memoize.hpp:56-61) applies caching only when:
- Return type is not `void` (line 57)
- Function type is hashable or empty (line 58)
- Function type is equality comparable (line 59)
- All argument types are hashable (line 60)

### Cache Storage Strategy
Implementation uses static storage (memoize.hpp:62):
```cpp
static std::unordered_map<memo<Fn, std::decay_t<Args>...>,
                         std::invoke_result_t<Fn&, Args...>,
                         hash, std::equal_to<>> map;
```

### Hash Combination Algorithm
The hash function (memoize.hpp:34-47) uses:
- `xieite::unroll` for template parameter pack iteration (line 35)
- `xieite::hash_combine` for combining function and argument hashes (line 36)
- Conditional hashing based on `xieite::is_hashable` trait (lines 38-42)

### Memory Management
- Cache persists for program lifetime (static storage)
- No explicit cache invalidation mechanism
- Automatic cleanup on program termination
- Hash collisions handled by `std::unordered_map`

## Performance Characteristics

- **Cache lookup**: O(1) average, O(n) worst case (hash map operations)
- **Memory overhead**: O(k) where k is number of unique function calls
- **Hash computation**: O(n) where n is number of arguments
- **Storage efficiency**: Minimal overhead for key-value pairs

## Constraints and Limitations

### Memoization Requirements
Functions are memoized only when:
1. **Hashable parameters**: All arguments must be hashable
2. **Equality comparable**: Function objects must support equality comparison
3. **Non-void return**: Functions must return a value
4. **Deterministic**: Functions should be pure (same inputs → same outputs)

### When Memoization is Bypassed
The system falls back to direct function calls (memoize.hpp:72) when:
- Return type is `void`
- Function type is not hashable and not empty
- Any argument type is not hashable
- Function is not equality comparable

## Best Practices

1. **Use for expensive pure functions** - Functions with costly computations and no side effects
2. **Consider memory usage** - Caches persist throughout program lifetime
3. **Ensure deterministic behavior** - Memoized functions should be pure
4. **Optimize hash performance** - Keep argument types efficiently hashable
5. **Profile before optimizing** - Verify memoization provides actual performance benefits

## Common Use Cases

### Mathematical Computations
```cpp
// Factorial with memoization
long long factorial(int n) {
    if (n <= 1) return 1;
    return n * xieite::memoize(factorial, n - 1);
}

// Prime checking with cache
bool is_prime_cached(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

// Usage automatically caches results
bool result = xieite::memoize(is_prime_cached, 97);
```

### String Processing
```cpp
// Expensive string transformation
std::string process_text(const std::string& input, const std::string& pattern) {
    std::string result = input;
    // Complex text processing...
    return result;
}

// Automatic caching for repeated patterns
auto processed = xieite::memoize(process_text, "document.txt", "pattern1");
```

## See Also

- [Function Composition](./composition.md) - Function combination patterns
- [Currying](./currying.md) - Partial function application
- [Combinator Patterns](./combinators.md) - Higher-order function utilities
- [Functional API Reference](../../reference/api/fn.md)