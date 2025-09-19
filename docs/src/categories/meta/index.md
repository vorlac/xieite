# XIEITE Metaprogramming Module

## Overview

The XIEITE metaprogramming module provides advanced template metaprogramming utilities for C++20 and beyond. With 28 headers, it offers comprehensive type manipulation, compile-time computation, and metaprogramming patterns that form the foundation for sophisticated template-based designs.

## Module Organization

### Type Manipulation (12 headers)
- **[Type Manipulation](type_manipulation.md)** - Type lists and transformations
- Core type list: `type_list` with 30+ operations
- Type identification: `type_id`, `type_name`, `value_name`
- Folding operations: `fold`, `fold_for`
- Tuple utilities: `tuple_size`, `subtuple`, `reverse_tuple`

### Compile-Time Utilities (16 headers)
- **[Compile-Time Utilities](compile_time_utilities.md)** - Computation and introspection
- Aggregate inspection: `arity`, `any`
- Sequence generation: `seq`, `make_seq`, `seq_for`
- Type utilities: `type_counter`, `enum_size`
- Name utilities: `demangle`
- Helpers: `make_cxpr`, `paren`, `state`

## Key Features

### Comprehensive Type Lists
The `type_list` provides over 30 operations:
```cpp
using types = xieite::type_list<int, double, char>;

// Queries
static_assert(types::has<double>);
static_assert(types::all<std::is_arithmetic>);

// Transformations
using reversed = types::reverse<>;
using filtered = types::filter<std::is_integral>;
using unique = types::dedup<>;

// Advanced operations
using transformed = types::transform<1, transformer>;
using zipped = types::zip<float, long, short>;
```

### Aggregate Introspection
Determine aggregate structure at compile-time:
```cpp
struct Widget {
    int id;
    std::string name;
    double value;
};

static_assert(xieite::arity<Widget> == 3);

// Works with nested aggregates
struct Nested {
    Widget widget;
    std::vector<int> data;
};
static_assert(xieite::arity<Nested> == 2);
```

### Compile-Time Folding
Powerful fold operations over types:
```cpp
// Sum sizes of types
using total = xieite::fold<
    []<typename Acc, typename T> {
        return std::integral_constant<size_t, 
            Acc::value + sizeof(T)>{};
    },
    std::integral_constant<size_t, 0>,
    int, double, char
>;  // integral_constant<size_t, 13>

// Apply N times
using triple_ptr = xieite::fold_for<
    []<typename T, auto> { return xieite::type_id<T*>{}; },
    int,
    3
>;  // int***
```

### Sequence Generation
Create compile-time sequences:
```cpp
// Index sequences
using indices = xieite::seq_for<5>;  // seq<0,1,2,3,4>
using range = xieite::make_seq<10, 20>;  // seq<10,11,...,19>

// Use in parameter pack expansion
template<auto... i>
void expand(xieite::seq<i...>) {
    ((process<i>()), ...);
}

expand(xieite::make_seq<0, 10>{});
```

## Design Patterns

### Type List Programming
```cpp
// Define supported types
using supported = xieite::type_list<int, float, double, long>;

// Check if type is supported
template<typename T>
constexpr bool is_supported = supported::has<T>;

// Get nth supported type
using third_type = supported::at<2>;  // double

// Filter numeric types
using numerics = supported::filter<std::is_arithmetic>;
```

### Compile-Time State
```cpp
// Stateful metaprogramming
using counter = xieite::type_counter<>;

template<typename T>
struct Register {
    inline static const auto id = counter::next();
};

// Each type gets unique ID
static_assert(Register<int>::id == 0);
static_assert(Register<double>::id == 1);
static_assert(Register<char>::id == 2);
```

### Tuple Manipulation
```cpp
// Tuple operations
auto t = std::make_tuple(1, 2.0, 'a', true);

// Extract subset
auto sub = xieite::subtuple<1, 3>(t);  // tuple<double, char>

// Reverse elements
auto rev = xieite::reverse_tuple(t);  // tuple<bool, char, double, int>

// Splice multiple tuples
auto spliced = xieite::splice_tuple(
    std::make_tuple(1, 2),
    std::make_tuple('a', 'b'),
    std::make_tuple(3.14)
);  // tuple<int, int, char, char, double>
```

## Module Architecture

### Type System Foundation
- `type_id`: Basic type wrapper
- `type_list`: Type container with operations
- `fold`/`fold_for`: Type transformation primitives

### Compile-Time Infrastructure
- `seq`/`make_seq`: Value sequences
- `arity`: Aggregate inspection
- `type_counter`: Unique ID generation
- `state`: Compile-time mutable state

### Utility Layer
- `demangle`: Human-readable names
- `make_cxpr`: Force compile-time evaluation
- `paren`: Macro safety wrapper
- `any`: Universal initializer

## Performance Characteristics

### Compile-Time
- All operations execute at compile-time
- Deep recursion may increase compilation time
- Template instantiation grows with type list size
- Modern compilers optimize well

### Runtime
- Zero runtime overhead
- No code generation for pure metaprograms
- Folded results are compile-time constants
- Type operations leave no runtime trace

## Integration Examples

### Variant Visitor Generation
```cpp
using variant_types = xieite::type_list<int, double, std::string>;

template<typename... Handlers>
auto make_visitor(Handlers... handlers) {
    return variant_types::apply([handlers...]
        <typename... Ts>() {
            return std::overloaded{handlers...};
        }
    );
}
```

### Compile-Time Factory
```cpp
template<typename Base>
class Factory {
    using types = xieite::type_list</* derived types */>;
    
    template<std::size_t I>
    static auto create() {
        using T = types::at<I>;
        return std::make_unique<T>();
    }
    
public:
    static auto create(std::size_t index) {
        return types::apply([index]<typename... Ts>() {
            using fn_ptr = std::unique_ptr<Base>(*)();
            fn_ptr factories[] = {create<Ts>...};
            return factories[index]();
        });
    }
};
```

### Reflection System
```cpp
template<typename T>
struct Reflectable {
    static constexpr auto name = xieite::type_name<T>();
    static constexpr auto id = xieite::type_counter<>::next();
    static constexpr auto size = xieite::arity<T>;
    
    static void print_info() {
        std::cout << "Type: " << name << '\n'
                  << "ID: " << id << '\n'
                  << "Members: " << size << '\n';
    }
};
```

## Best Practices

1. **Use type_list for type collections**:
   - Centralize type management
   - Apply operations uniformly
   - Maintain type safety

2. **Leverage fold for transformations**:
   - Build complex types incrementally
   - Avoid deep recursion
   - Compose operations

3. **Generate sequences efficiently**:
   - Use seq_for for indices
   - make_seq for ranges
   - Apply in pack expansion

4. **Introspect carefully**:
   - arity for aggregate analysis
   - type_name for debugging
   - demangle for readable output

## Module Statistics

- **Total Headers**: 28
- **Type Operations**: 30+ in type_list
- **Fold Variants**: 2 (fold, fold_for)
- **Sequence Types**: 3 (seq, make_seq, seq_for)
- **Tuple Operations**: 5+
- **Compile-Time Functions**: 100%

## Common Patterns

### Type Filtering
```cpp
using all_types = xieite::type_list</* many types */>;
using integers = all_types::filter<std::is_integral>;
using pointers = all_types::filter<std::is_pointer>;
```

### Type Registration
```cpp
template<typename T>
struct AutoRegister {
    inline static const bool registered = [] {
        Registry::add<T>();
        return true;
    }();
};
```

### Compile-Time Dispatch
```cpp
template<std::size_t I>
auto dispatch() {
    return handlers::at<I>{}();
}
```

## Future Enhancements

Potential additions to the meta module:
- Compile-time sorting algorithms
- Type tree structures
- Advanced SFINAE helpers
- Compile-time parsers
- More fold variations

---

*Return to [XIEITE Documentation Home](../../index.md)*