# XIEITE Functional Module

## Overview

The XIEITE functional module provides advanced functional programming utilities for C++20 and beyond. With 35 headers, it offers type-erased functions, memoization, recursion combinators, RAII guards, and user-defined literals that enhance code expressiveness and safety.

## Module Organization

### Core Functional Utilities (15 headers)
- **[Functional Core](functional_core.md)** - Type erasure, memoization, and combinators
- Type-erased wrapper: `fn` with noexcept support
- Memoization: `memoize` for automatic caching
- Recursion: `y_combinator` for lambda recursion
- Argument manipulation: `curry`, `bind_front`, `bind_back`
- Function composition: `compose`, `distribute_args`

### Guards and Wrappers (10 headers)
- **[Guards and Wrappers](guards_and_wrappers.md)** - RAII patterns and resource management
- Scope guards: `scope_guard`, `scope_exit`, `scope_fail`, `scope_success`
- Process management: `process_guard`
- Utility wrappers: `finally`, `no_op`, `visitor`

### User-Defined Literals (10 headers)
- **[User-Defined Literals](user_defined_literals.md)** - Type-safe literal syntax
- Numeric: `_number`, `_exp`
- String: `_fstr`, `_str`, `_hash`
- Units: `_unit` for type-safe measurements
- Memory: `_kb`, `_mb`, `_gb`, `_tb`
- Binary: `_bin` for bit patterns

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

### RAII Resource Management
Automatic cleanup with scope guards:
```cpp
void process_file(const char* path) {
    FILE* file = fopen(path, "r");
    xieite::scope_guard cleanup([file] { 
        if (file) fclose(file);
    });
    
    // File automatically closed on any exit path
    if (error) throw std::runtime_error("Failed");
}
```

### Expressive Literals
Type-safe and readable literals:
```cpp
// Memory sizes
auto buffer_size = 256_mb;
auto cache_limit = 4_gb;

// Numeric parsing
constexpr auto port = "8080"_number<uint16_t>;

// Type-safe units
auto distance = 100.0_unit<"meters">;
auto time = 5.0_unit<"seconds">;
// auto invalid = distance + time;  // Compile error
```

## Functional Patterns

### Currying and Partial Application
```cpp
auto add = xieite::curry([](int a, int b, int c) { 
    return a + b + c; 
});

auto add5 = add(5);        // Partial application
auto add5_10 = add5(10);   // More partial application
int result = add5_10(20);  // 35
```

### Function Composition
```cpp
auto process = xieite::compose(
    [](std::string s) { return "[" + s + "]"; },  // Add brackets
    [](std::string s) { return xieite::toupper(s); },  // Uppercase
    [](int n) { return std::to_string(n); }  // Convert to string
);

std::string result = process(42);  // "[42]"
```

### Visitor Pattern
```cpp
using Value = std::variant<int, double, std::string>;

void handle(const Value& v) {
    std::visit(xieite::visitor{
        [](int i) { std::cout << "Integer: " << i; },
        [](double d) { std::cout << "Double: " << d; },
        [](const std::string& s) { std::cout << "String: " << s; }
    }, v);
}
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

### Composability
- Functions combine naturally
- Consistent interfaces
- Building blocks for larger abstractions

## Module Comparison

| Feature | std:: Alternative | XIEITE Advantage |
|---------|------------------|------------------|
| `fn<T>` | `std::function` | Noexcept support, lighter weight |
| `memoize` | Manual caching | Automatic, transparent |
| `y_combinator` | `std::function` recursion | Zero overhead |
| `scope_guard` | Custom RAII classes | Generic, reusable |
| `visitor` | Separate lambdas | Overload set syntax |
| UDLs | None/Basic | Comprehensive set |

## Performance Characteristics

### Compile-Time
- User-defined literals: Zero runtime cost
- Template instantiation: Optimized by compiler
- Concept checking: Early error detection

### Runtime
- Type erasure: Single indirection for `fn`
- Memoization: O(1) after first call
- Guards: Single branch on destruction
- Composition: Inlined by optimizer

## Integration Examples

### Error Handling Pattern
```cpp
auto safe_operation() {
    xieite::scope_fail on_error([] {
        log_error("Operation failed");
        rollback();
    });
    
    xieite::scope_success on_success([] {
        commit();
        log_info("Operation succeeded");
    });
    
    // Complex operation...
    perform_step1();
    perform_step2();
    // Guards handle both paths automatically
}
```

### Configuration DSL
```cpp
struct Config {
    std::string name = "server"_str;
    uint16_t port = "8080"_number<uint16_t>;
    std::size_t buffer = 64_mb;
    auto timeout = 30.0_unit<"seconds">;
    
    bool validate() const {
        return port > 0 && buffer >= 1_mb;
    }
};
```

### Functional Pipeline
```cpp
auto pipeline = xieite::compose(
    xieite::memoize(expensive_transform),
    xieite::curry(parameterized_filter)(config),
    xieite::bind_back(format_output, "\n")
);

for (const auto& input : data) {
    auto result = pipeline(input);
    process(result);
}
```

## Best Practices

1. **Use appropriate guards**:
   - `scope_guard` for general cleanup
   - `scope_fail` for error handling
   - `scope_success` for commit operations

2. **Leverage memoization**:
   - Cache expensive pure functions
   - Combine with Y combinator for recursion
   - Consider thread safety needs

3. **Compose functions**:
   - Build pipelines from simple functions
   - Use curry for configuration
   - Combine with bind for adaptation

4. **Type-safe literals**:
   - Use for configuration values
   - Prevent unit mixing errors
   - Improve code readability

## Module Statistics

- **Total Headers**: 35
- **Type Erasure**: 1 (`fn`)
- **Combinators**: 5 (Y, compose, curry, etc.)
- **Guards**: 6 types
- **User-Defined Literals**: 10+
- **Compile-Time Functions**: ~60%

## Future Enhancements

Potential additions to the functional module:
- Monadic operations (map, flatmap, filter)
- Lazy evaluation utilities
- More functional data structures
- Parallel execution combinators
- Coroutine integration

---

*Return to [XIEITE Documentation Home](../../index.md)*