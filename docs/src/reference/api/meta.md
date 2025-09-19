# Metaprogramming API Reference

## Overview

The meta category contains template metaprogramming utilities, including type manipulation, compile-time sequences, template operations, and advanced metaprogramming patterns.

## Core Utilities

### `any`
- **Header**: `meta/any.hpp`
- **Purpose**: Any-related metaprogramming utilities

### `arity`
- **Header**: `meta/arity.hpp`
- **Purpose**: Function arity detection utilities

### `type_list`
- **Header**: `meta/type_list.hpp`
- **Synopsis**: `template<typename... Ts> struct type_list`
- **Purpose**: Comprehensive type list container with extensive operations
- **Features**:
  - Indexing: `at<idx>` for type access
  - Searching: `find<cond>`, `find_idx<cond>`, `idx_of<T>`
  - Manipulation: `append<...>`, `prepend<...>`, `slice<start, end>`
  - Modification: `insert<idx, ...>`, `erase<start, end>`, `replace<start, end, ...>`
  - Algorithms: `filter<cond>`, `dedup<cmp>`, `transform<arity, fn>`
  - Utilities: `reverse`, `repeat<count>`, `zip<...>`
- **Example**:
    ```cpp
    using types = xieite::type_list<int, double, std::string>;
    static_assert(types::size == 3);
    using second = types::at<1>;  // double
    using filtered = types::filter<[]<typename T> requires std::integral<T> {}>;
    ```

## Template Operations

### `make_seq`
- **Header**: `meta/make_seq.hpp`
- **Synopsis**: `template<auto count> constexpr auto make_seq`
- **Purpose**: Create compile-time integer sequences for template metaprogramming
- **Description**: Creates a sequence of integers from 0 to count-1. Used for unpacking parameter packs and generating compile-time index sequences. Returns a xieite::seq object.
- **Example**:
    ```cpp
    #include <xieite/meta/make_seq.hpp>
    #include <xieite/meta/seq.hpp>

    // Create sequence 0, 1, 2, 3, 4
    constexpr auto seq = xieite::make_seq<5>;
    // Use in template parameter pack expansion
    ```

### `seq`
- **Header**: `meta/seq.hpp`
- **Synopsis**: `template<auto... values> struct seq`
- **Purpose**: Integer sequence container for template metaprogramming
- **Description**: Holds a sequence of compile-time integer values. Used with make_seq and other metaprogramming utilities for parameter pack manipulation and compile-time loops.
- **Example**:
    ```cpp
    #include <xieite/meta/seq.hpp>

    using my_seq = xieite::seq<0, 1, 2, 3>;
    // Used in template specializations and pack expansion
    ```

### `seq_for`
- **Header**: `meta/seq_for.hpp`
- **Purpose**: Sequence iteration utilities

### `fold`
- **Header**: `meta/fold.hpp`
- **Purpose**: Fold (reduce) operations over type packs

### `fold_for`
- **Header**: `meta/fold_for.hpp`
- **Purpose**: Fold operations with iteration

### Tuple Utilities

### `make_tuple`
- **Header**: `meta/make_tuple.hpp`
- **Purpose**: Tuple construction utilities

### `fwd_tuple`
- **Header**: `meta/fwd_tuple.hpp`
- **Purpose**: Tuple forwarding utilities

### `reverse_tuple`
- **Header**: `meta/reverse_tuple.hpp`
- **Synopsis**: `constexpr auto reverse_tuple(is_tuple_like auto&& tuple)`
- **Purpose**: Reverse the order of elements in tuple-like objects
- **Description**: Creates a new tuple with elements in reverse order. Works with std::tuple, std::pair, and other tuple-like types. Uses perfect forwarding to preserve value categories.
- **Example**:
    ```cpp
    #include <xieite/meta/reverse_tuple.hpp>
    #include <tuple>
    #include <string>

    auto original = std::make_tuple(1, 2.5, "hello");
    auto reversed = xieite::reverse_tuple(original);
    // reversed is std::tuple<std::string, double, int>{"hello", 2.5, 1}

    static_assert(std::get<0>(reversed) == "hello");
    static_assert(std::get<1>(reversed) == 2.5);
    static_assert(std::get<2>(reversed) == 1);
    ```

### `splice_tuple`
- **Header**: `meta/splice_tuple.hpp`
- **Purpose**: Splice tuple operations

### `subtuple`
- **Header**: `meta/subtuple.hpp`
- **Purpose**: Extract sub-tuples

### `tuple_size`
- **Header**: `meta/tuple_size.hpp`
- **Purpose**: Tuple size utilities

### `decay_as_tuple`
- **Header**: `meta/decay_as_tuple.hpp`
- **Purpose**: Decay types as tuple

### `collapse_fwd`
- **Header**: `meta/collapse_fwd.hpp`
- **Purpose**: Collapse forwarding references

### `collapse_fwd_as_tuple`
- **Header**: `meta/collapse_fwd_as_tuple.hpp`
- **Purpose**: Collapse forwarding as tuple

### Type Identification

### `type_id`
- **Header**: `meta/type_id.hpp`
- **Purpose**: Type identification utilities

### `type_name`
- **Header**: `meta/type_name.hpp`
- **Purpose**: Type name utilities

### `type_counter`
- **Header**: `meta/type_counter.hpp`
- **Purpose**: Type counting utilities

### `value_id`
- **Header**: `meta/value_id.hpp`
- **Purpose**: Value identification utilities

### `value_name`
- **Header**: `meta/value_name.hpp`
- **Purpose**: Value name utilities

### Miscellaneous

### `demangle`
- **Header**: `meta/demangle.hpp`
- **Synopsis**: `std::string demangle(std::string_view name)`
- **Purpose**: Demangle C++ type names to human-readable form
- **Description**: Converts mangled type names (from typeid().name()) to human-readable strings. Uses platform-specific demangling (cxxabi on GCC/Clang). Falls back to original name if demangling is unavailable.
- **Example**:
    ```cpp
    #include <xieite/meta/demangle.hpp>
    #include <typeinfo>
    #include <iostream>

    // Get mangled name and demangle it
    auto mangled = typeid(std::vector<int>).name();
    auto readable = xieite::demangle(mangled);
    std::cout << readable << std::endl;  // "std::vector<int, std::allocator<int>>"

    // Works with any type
    auto name = xieite::demangle(typeid(void(*)(int, double)).name());
    // Produces readable function pointer type
    ```

### `end`
- **Header**: `meta/end.hpp`
- **Purpose**: End marker utilities

### `enum_size`
- **Header**: `meta/enum_size.hpp`
- **Purpose**: Enum size detection

### `make_cxpr`
- **Header**: `meta/make_cxpr.hpp`
- **Purpose**: Constexpr creation utilities

### `paren`
- **Header**: `meta/paren.hpp`
- **Purpose**: Parenthesis utilities

### `state`
- **Header**: `meta/state.hpp`
- **Purpose**: State management utilities

## Usage Examples

### Type List Operations
```cpp
#include <xieite/meta/type_list.hpp>

using types = xieite::type_list<int, double, std::string, char>;

// Basic properties
static_assert(types::size == 4);
static_assert(std::same_as<types::at<1>, double>);

// Manipulation
using without_first = types::slice<1>;
using with_float = types::append<float>;
using reversed = types::reverse<>;

// Filtering
using integral_only = types::filter<[]<typename T> requires std::integral<T> {}>;
```

### Tuple Utilities
```cpp
#include <xieite/meta/reverse_tuple.hpp>
#include <tuple>

auto original = std::make_tuple(1, 2.5, "hello");
auto reversed = xieite::reverse_tuple(original);
// reversed contains {"hello", 2.5, 1} in reverse order
```

### Sequences
```cpp
#include <xieite/meta/make_seq.hpp>
#include <xieite/meta/seq.hpp>

// Create compile-time sequence 0, 1, 2, 3, 4
constexpr auto seq = xieite::make_seq<5>;

// Use in template metaprogramming
template<std::size_t... I>
void process_indices(xieite::seq<I...>) {
    // Process each index I...
}
```

## Implementation Notes

1. **Type Lists**: The `type_list` class provides comprehensive type manipulation through member aliases and static members
2. **Constexpr**: Most operations are available at compile-time
3. **C++20/23**: Uses modern C++ features including concepts and pack indexing
4. **Performance**: Operations are typically zero-cost abstractions

## See Also

- [Metaprogramming Category Overview](../../categories/meta/)
- [Template Patterns](../../architecture/template_patterns.md)
- [Compile-Time Computation](../../architecture/compile_time.md)
