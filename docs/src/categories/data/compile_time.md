# Compile-Time Data Structures

## Overview

XIEITE's compile-time data structures enable zero-runtime-cost data manipulation through constexpr operations, template metaprogramming, and static storage. This module provides several fixed-size containers designed for compile-time use.

## Design Philosophy

### Zero Runtime Cost
All compile-time structures are designed to have no runtime overhead:
- Operations resolve at compile time
- No dynamic allocations
- Optimal code generation
- Static initialization

### Constexpr Everything
Every operation that can be constexpr is constexpr:
```cpp
constexpr xieite::fixed_array<int, 5> arr{1, 2, 3, 4, 5};
// Operations computed at compile time
```

### Template-Friendly
Designed for use in template metaprogramming:
```cpp
template<xieite::fixed_str Name>
struct named_type {
    static constexpr auto name = Name;
};

using my_type = named_type<"Configuration">;
```

## Available Structures

### Fixed Array
Fixed-size array with compile-time operations:
```cpp
constexpr xieite::fixed_array<int, 10> data{};
constexpr auto size = data.size();
constexpr auto ptr = data.data();
```

### Fixed String
Compile-time string for template parameters:
```cpp
template<xieite::fixed_str S>
constexpr auto make_label() {
    return "[" + S + "]";
}

constexpr auto label = make_label<"ERROR">();  // "[ERROR]"
```

### Fixed Map
Compile-time key-value mapping:
```cpp
constexpr xieite::fixed_map<int, const char*, 3> errors{{
    {404, "Not Found"},
    {500, "Internal Error"},
    {503, "Service Unavailable"}
}};

constexpr auto msg = errors.at(404);  // "Not Found"
```

### Fixed Set
Compile-time set operations:
```cpp
constexpr xieite::fixed_set<int, 5> valid_codes{200, 201, 204, 301, 302};
constexpr bool is_valid = valid_codes.contains(200);  // true
```

### Fixed Multidimensional Container
Multi-dimensional compile-time containers:
```cpp
constexpr xieite::fixed_md_container<int, 3, 3> matrix{
    1, 2, 3,
    4, 5, 6,
    7, 8, 9
};
constexpr auto element = matrix[1][2];  // 6
```

## Implementation Patterns

### Index Sequences
Leverage std::index_sequence for array operations:
```cpp
template<typename T, std::size_t N>
class fixed_array {
    template<std::size_t... Is>
    constexpr auto reverse_impl(std::index_sequence<Is...>) const {
        return fixed_array{array[N - 1 - Is]...};
    }

public:
    constexpr auto reverse() const {
        return reverse_impl(std::make_index_sequence<N>{});
    }
};
```

### Perfect Forwarding in Constexpr
```cpp
template<typename... Args>
constexpr auto make_array(Args&&... args) {
    return xieite::fixed_array<std::common_type_t<Args...>, sizeof...(Args)>{
        std::forward<Args>(args)...
    };
}
```

## Usage Patterns

### Configuration Tables
```cpp
constexpr xieite::fixed_map<int, const char*, 3> error_messages{{
    {404, "Not Found"},
    {500, "Internal Error"},
    {503, "Service Unavailable"}
}};

constexpr auto msg = error_messages.at(404);  // "Not Found"
```

### Compile-Time Validation
```cpp
template<int Min, int Max>
struct bounded_int {
    int value;

    constexpr bounded_int(int v) : value(v) {
        if (v < Min || v > Max) {
            throw "Value out of bounds";
        }
    }
};

constexpr bounded_int<0, 100> percentage{50};  // OK
// constexpr bounded_int<0, 100> invalid{150};  // Compile error
```

### Static Lookup Tables
```cpp
constexpr auto make_sqrt_table() {
    xieite::fixed_array<double, 100> table{};
    for (int i = 0; i < 100; ++i) {
        table[i] = std::sqrt(i);  // Computed at compile time
    }
    return table;
}

constexpr auto sqrt_table = make_sqrt_table();
```

## Performance Considerations

### Compilation Time
- Complex compile-time operations increase compilation time
- Balance between runtime performance and build time
- Use explicit instantiation to reduce template bloat

### Binary Size
- Compile-time data becomes part of the binary
- Large static arrays increase executable size
- Consider trade-offs between speed and size

### Optimization Opportunities
```cpp
// Compiler can optimize this completely
constexpr auto result = complex_computation();
int value = result;  // No runtime computation

// vs runtime computation
int value = complex_computation();  // Computed at runtime
```

## Advanced Techniques

### String as Template Parameter
```cpp
template<xieite::fixed_str Str>
struct tag {
    static constexpr auto value = Str;
};

using error_tag = tag<"ERROR">;
using warning_tag = tag<"WARNING">;
```

### Integration with Type Traits
```cpp
template<typename T>
constexpr auto type_properties() {
    xieite::fixed_array<bool, 5> props{
        std::is_integral_v<T>,
        std::is_floating_point_v<T>,
        std::is_pointer_v<T>,
        std::is_const_v<T>,
        std::is_volatile_v<T>
    };
    return props;
}
```

## Best Practices

1. **Prefer constexpr over templates** when possible for better error messages
2. **Use static_assert** for compile-time validation
3. **Consider compilation time** for complex operations
4. **Document compile-time requirements** clearly
5. **Test with multiple compilers** for portability

## See Also

- [Data Structures API](../../reference/api/data.md)
- [Template Patterns](../../architecture/template_patterns.md)
- [String Utilities](./strings.md)