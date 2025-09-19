# Compile-Time Repetition

## Overview

XIEITE provides compile-time repetition utilities for template metaprogramming, enabling repeated application of operations over types and values. These utilities support both runtime function repetition and compile-time type list transformations.

## Runtime Function Repetition

### Template-Based Repetition
Implementation: `include/xieite/fn/repeat.hpp` (lines 11-21)

```cpp
template<std::integral auto count>
constexpr void repeat(auto&& fn, auto&&... args)
XIEITE_ARROW_RET((
    []<auto... i>(xieite::seq<i...>, auto&& fn, auto&&... args)
        XIEITE_ARROW((..., fn.template operator()<i>(args...)))
)(xieite::make_seq<count>, XIEITE_FWD(fn), XIEITE_FWD(args)...));

template<typename... Ts>
constexpr void repeat(auto&& fn, auto&&... args)
XIEITE_ARROW_RET(xieite::repeat<sizeof...(Ts)>(XIEITE_FWD(fn), XIEITE_FWD(args)...));
```

Repeats function execution with compile-time index parameters.

### Constexpr Value Conversion
Implementation: `include/xieite/meta/make_cxpr.hpp` (lines 10-16)

```cpp
constexpr void make_cxpr(auto&& fn, unsigned char x) {
    xieite::repeat<(1uz << xieite::bit_size<char>)>([&fn, x]<std::size_t i> -> void {
        if (x == static_cast<unsigned char>(i)) {
            XIEITE_FWD(fn).template operator()<static_cast<unsigned char>(i)>();
        }
    });
}
```

Converts runtime values to compile-time template parameters.

## Type List Repetition

### Type List Repetition
Implementation: `include/xieite/meta/type_list.hpp` (lines 193-199)

```cpp
private:
    static constexpr auto repeat_impl = []<typename List, auto> {
        return typename List::template append<Ts...>();
    };

public:
    template<std::size_t count>
    using repeat = xieite::fold_for<xieite::type_list<Ts...>::repeat_impl, xieite::type_list<>, count>;
```

Repeats a type list a specified number of times.

## Folding Operations

### Basic Fold Operation
Implementation: `include/xieite/meta/fold.hpp` (lines 17-18)

```cpp
template<auto fn, typename T, typename... Ts>
using fold = decltype((DETAIL_XIEITE::fold::impl<fn, T>()->*...->*xieite::type_id<Ts>()))::type;
```

Applies a binary operation recursively across a type pack.

### Indexed Fold Operation
Implementation: `include/xieite/meta/fold_for.hpp` (lines 22-23)

```cpp
template<auto fn, typename T, std::size_t count>
using fold_for = decltype(xieite::unroll<count>(DETAIL_XIEITE::fold_for::impl<fn, T>))::type;
```

Performs folding operations with indexed iteration over a compile-time range.

## Usage Examples

### Basic Function Repetition
```cpp
#include <xieite/fn/repeat.hpp>

// Repeat a function 5 times with compile-time indices
xieite::repeat<5>([](auto index) {
    std::cout << "Iteration: " << index << "\n";
    // Each call receives a different compile-time index: 0, 1, 2, 3, 4
});

// Repeat based on type pack size
using types = std::tuple<int, double, std::string>;
xieite::repeat<types>([](auto index) {
    std::cout << "Type index: " << index << "\n";
    // Calls function 3 times (sizeof...(tuple types))
});
```

### Template Parameter Generation
```cpp
#include <xieite/fn/repeat.hpp>

template<std::size_t N>
void generate_array() {
    std::array<int, N> arr;

    // Initialize array with compile-time indices
    xieite::repeat<N>([&arr]<std::size_t i> {
        arr[i] = i * i;  // arr[0] = 0, arr[1] = 1, arr[2] = 4, etc.
    });

    for (auto val : arr) {
        std::cout << val << " ";
    }
}

generate_array<5>();  // Output: 0 1 4 9 16
```

### Runtime to Compile-Time Conversion
```cpp
#include <xieite/meta/make_cxpr.hpp>

// Convert runtime value to compile-time template parameter
void process_char(unsigned char c) {
    xieite::make_cxpr([](auto compile_time_char) {
        constexpr auto ch = compile_time_char;
        std::cout << "Character '" << static_cast<char>(ch)
                  << "' has ASCII value " << static_cast<int>(ch) << "\n";

        // Can use ch as template parameter
        std::array<char, ch> buffer{};  // Size determined at compile time
    }, c);
}

process_char('A');  // Character 'A' has ASCII value 65
```

### Type List Repetition
```cpp
#include <xieite/meta/type_list.hpp>

// Repeat a type list multiple times
using base_types = xieite::type_list<int, double>;
using repeated = base_types::repeat<3>;
// Result: type_list<int, double, int, double, int, double>

// Use repeated types to create tuple
using repeated_tuple = repeated::to<std::tuple>;
// Result: std::tuple<int, double, int, double, int, double>

repeated_tuple data{1, 1.5, 2, 2.5, 3, 3.5};
```

## Advanced Patterns

### Compile-Time Loop Unrolling
```cpp
template<std::size_t N>
class UnrolledProcessor {
public:
    template<typename Array>
    static constexpr auto process(Array& arr) {
        auto sum = typename Array::value_type{};

        // Unroll the loop at compile time
        xieite::repeat<N>([&sum, &arr]<std::size_t i> {
            if constexpr (i < std::size(arr)) {
                sum += arr[i] * (i + 1);  // Weighted sum
            }
        });

        return sum;
    }
};

// Usage
std::array<int, 4> data{1, 2, 3, 4};
auto result = UnrolledProcessor<4>::process(data);
// Compiles to: sum = 1*1 + 2*2 + 3*3 + 4*4 = 30
```

### Template Instantiation Patterns
```cpp
template<typename... Ts>
class MultiTypeProcessor {
private:
    std::tuple<Ts...> data_;

public:
    MultiTypeProcessor(Ts... values) : data_(values...) {}

    void process_all() {
        // Process each type with its index
        xieite::repeat<Ts...>([this]<std::size_t i> {
            auto& element = std::get<i>(data_);

            std::cout << "Processing element " << i
                      << " of type " << typeid(element).name()
                      << " with value " << element << "\n";
        });
    }
};

// Usage
MultiTypeProcessor processor{42, 3.14, std::string("hello")};
processor.process_all();
```

### Recursive Type Construction
```cpp
#include <xieite/meta/fold.hpp>
#include <xieite/meta/type_list.hpp>

// Build nested types using folding
template<std::size_t depth>
struct NestedVectorBuilder {
    using type = xieite::fold_for<
        []<typename Prev, auto> {
            return xieite::type_id<std::vector<typename Prev::type>>();
        },
        xieite::type_id<int>,
        depth
    >::type;
};

// Usage
using nested_1 = NestedVectorBuilder<1>::type;  // std::vector<int>
using nested_3 = NestedVectorBuilder<3>::type;  // std::vector<std::vector<std::vector<int>>>

nested_3 data{{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
```

### Compile-Time String Processing
```cpp
template<std::size_t N>
constexpr auto process_string(const char (&str)[N]) {
    std::array<char, N> result{};

    xieite::repeat<N - 1>([&str, &result]<std::size_t i> {
        // Transform each character at compile time
        result[i] = (str[i] >= 'a' && str[i] <= 'z')
                   ? str[i] - 'a' + 'A'  // Convert to uppercase
                   : str[i];
    });

    return result;
}

// Usage
constexpr auto upper = process_string("hello");
// Result: array containing "HELLO"
```

## Implementation Details

### Sequence Generation Strategy
The repetition utilities use `xieite::make_seq` and `xieite::seq` for:
- Compile-time index sequence generation (repeat.hpp:14)
- Parameter pack expansion over integer sequences
- Template argument deduction for index parameters

### Fold Implementation
The fold operations (fold.hpp:7-13) employ:
- Operator overloading with `->*` for chaining operations
- Type identity wrappers for template argument preservation
- Recursive template instantiation for accumulation

### Type List Repetition Algorithm
The type list repetition (type_list.hpp:193-199) uses:
- `fold_for` for indexed iteration over compile-time ranges
- Lambda expressions with capture for type accumulation
- Template template parameters for generic container support

## Performance Characteristics

- **Compile-time overhead**: Linear with repetition count and template instantiation depth
- **Runtime overhead**: Zero - all repetition happens at compile time
- **Memory usage**: Dependent on generated template instantiations
- **Optimization**: Modern compilers can fully optimize away the repetition machinery

## Best Practices

1. **Use compile-time repetition for performance-critical code** - Unrolls loops and eliminates runtime overhead
2. **Limit repetition count for reasonable compile times** - Large counts can slow compilation
3. **Prefer type-based repetition for template metaprogramming** - More flexible than index-based approaches
4. **Consider template instantiation limits** - Very large repetitions may hit compiler limits

## Common Use Cases

### SIMD Instruction Generation
```cpp
template<std::size_t width>
void vectorized_add(const float* a, const float* b, float* result) {
    xieite::repeat<width>([=]<std::size_t i> {
        result[i] = a[i] + b[i];  // May vectorize automatically
    });
}
```

### Template Parameter Pack Processing
```cpp
template<typename... Types>
void print_type_info() {
    xieite::repeat<Types...>([]<std::size_t i> {
        using CurrentType = xieite::type_list<Types...>::template at<i>;
        std::cout << "Type " << i << ": " << typeid(CurrentType).name() << "\n";
    });
}
```

### Compile-Time Data Structure Generation
```cpp
template<std::size_t size>
using repeated_int_tuple =
    xieite::type_list<int>::repeat<size>::template to<std::tuple>;

repeated_int_tuple<5> data{1, 2, 3, 4, 5};
// Type: std::tuple<int, int, int, int, int>
```

## See Also

- [Sequences](./sequences.md) - Compile-time sequence generation
- [Type Lists](./type_lists.md) - Type manipulation utilities
- [Operations](./operations.md) - Type list operations
- [Metaprogramming API Reference](../../reference/api/meta.md)