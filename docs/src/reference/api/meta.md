# Metaprogramming API Reference

## Overview

The meta category contains 80+ header files providing template metaprogramming utilities, including type list manipulation, compile-time sequences, template operations, and advanced SFINAE/substitution detection patterns.

## Organization

The meta headers are organized into functional groups:

- **Type Lists** (15+ headers): Type list operations and manipulation
- **Sequences** (10+ headers): Compile-time integer and value sequences
- **Template Operations** (15+ headers): Template manipulation utilities
- **Substitution Detection** (10+ headers): SFINAE and substitution patterns
- **Compile-Time Algorithms** (10+ headers): Meta-algorithms
- **Repetition & Generation** (10+ headers): Code generation patterns
- **Utilities** (10+ headers): General metaprogramming helpers

## Type Lists

### `type_list`
- **Header**: `meta/type_list.hpp`
- **Synopsis**: `template<typename... Ts> struct type_list`
- **Purpose**: Basic type list container
- **Example**:
    ```cpp
    using types = xieite::type_list<int, double, std::string>;
    static_assert(types::size == 3);
    ```

### `type_at`
- **Header**: `meta/type_at.hpp`
- **Synopsis**: `template<std::size_t I, typename List> using type_at_t`
- **Purpose**: Get type at index
- **Example**:
    ```cpp
    using list = xieite::type_list<int, double, char>;
    using second = xieite::type_at_t<1, list>;  // double
    ```

### `type_front`
- **Header**: `meta/type_front.hpp`
- **Synopsis**: `template<typename List> using type_front_t`
- **Purpose**: Get first type
- **Example**:
    ```cpp
    using list = xieite::type_list<int, double, char>;
    using first = xieite::type_front_t<list>;  // int
    ```

### `type_back`
- **Header**: `meta/type_back.hpp`
- **Synopsis**: `template<typename List> using type_back_t`
- **Purpose**: Get last type
- **Example**:
    ```cpp
    using list = xieite::type_list<int, double, char>;
    using last = xieite::type_back_t<list>;  // char
    ```

### `type_push_front`
- **Header**: `meta/type_push_front.hpp`
- **Synopsis**: `template<typename T, typename List> using type_push_front_t`
- **Purpose**: Add type to front
- **Example**:
    ```cpp
    using list = xieite::type_list<int, double>;
    using new_list = xieite::type_push_front_t<char, list>;
    // type_list<char, int, double>
    ```

### `type_push_back`
- **Header**: `meta/type_push_back.hpp`
- **Synopsis**: `template<typename List, typename T> using type_push_back_t`
- **Purpose**: Add type to back
- **Example**:
    ```cpp
    using list = xieite::type_list<int, double>;
    using new_list = xieite::type_push_back_t<list, char>;
    // type_list<int, double, char>
    ```

### `type_pop_front`
- **Header**: `meta/type_pop_front.hpp`
- **Synopsis**: `template<typename List> using type_pop_front_t`
- **Purpose**: Remove first type
- **Example**:
    ```cpp
    using list = xieite::type_list<int, double, char>;
    using new_list = xieite::type_pop_front_t<list>;
    // type_list<double, char>
    ```

### `type_pop_back`
- **Header**: `meta/type_pop_back.hpp`
- **Synopsis**: `template<typename List> using type_pop_back_t`
- **Purpose**: Remove last type
- **Example**:
    ```cpp
    using list = xieite::type_list<int, double, char>;
    using new_list = xieite::type_pop_back_t<list>;
    // type_list<int, double>
    ```

### `type_concat`
- **Header**: `meta/type_concat.hpp`
- **Synopsis**: `template<typename... Lists> using type_concat_t`
- **Purpose**: Concatenate type lists
- **Example**:
    ```cpp
    using list1 = xieite::type_list<int, double>;
    using list2 = xieite::type_list<char, float>;
    using combined = xieite::type_concat_t<list1, list2>;
    // type_list<int, double, char, float>
    ```

### `type_transform`
- **Header**: `meta/type_transform.hpp`
- **Synopsis**: `template<template<typename> class F, typename List> using type_transform_t`
- **Purpose**: Transform each type
- **Example**:
    ```cpp
    using list = xieite::type_list<int, double, char>;
    using ptrs = xieite::type_transform_t<std::add_pointer, list>;
    // type_list<int*, double*, char*>
    ```

### `type_filter`
- **Header**: `meta/type_filter.hpp`
- **Synopsis**: `template<template<typename> class Pred, typename List> using type_filter_t`
- **Purpose**: Filter types by predicate
- **Example**:
    ```cpp
    using list = xieite::type_list<int, void, double, void*, char>;
    using non_void = xieite::type_filter_t<is_not_void, list>;
    // type_list<int, double, char>
    ```

### `type_unique`
- **Header**: `meta/type_unique.hpp`
- **Synopsis**: `template<typename List> using type_unique_t`
- **Purpose**: Remove duplicate types
- **Example**:
    ```cpp
    using list = xieite::type_list<int, double, int, char, double>;
    using unique = xieite::type_unique_t<list>;
    // type_list<int, double, char>
    ```

### `type_reverse`
- **Header**: `meta/type_reverse.hpp`
- **Synopsis**: `template<typename List> using type_reverse_t`
- **Purpose**: Reverse type order
- **Example**:
    ```cpp
    using list = xieite::type_list<int, double, char>;
    using reversed = xieite::type_reverse_t<list>;
    // type_list<char, double, int>
    ```

### `type_sort`
- **Header**: `meta/type_sort.hpp`
- **Synopsis**: `template<template<typename, typename> class Comp, typename List> using type_sort_t`
- **Purpose**: Sort types by comparator
- **Example**:
    ```cpp
    using list = xieite::type_list<int, char, double>;
    using sorted = xieite::type_sort_t<size_less, list>;
    // type_list<char, int, double> (by sizeof)
    ```

### `type_find`
- **Header**: `meta/type_find.hpp`
- **Synopsis**: `template<typename T, typename List> constexpr std::size_t type_find_v`
- **Purpose**: Find type index
- **Example**:
    ```cpp
    using list = xieite::type_list<int, double, char>;
    constexpr auto idx = xieite::type_find_v<double, list>;  // 1
    ```

### `type_contains`
- **Header**: `meta/type_contains.hpp`
- **Synopsis**: `template<typename T, typename List> constexpr bool type_contains_v`
- **Purpose**: Check if type is in list
- **Example**:
    ```cpp
    using list = xieite::type_list<int, double, char>;
    static_assert(xieite::type_contains_v<double, list>);
    ```

## Integer Sequences

### `int_seq`
- **Header**: `meta/int_seq.hpp`
- **Synopsis**: `template<int... Is> struct int_seq`
- **Purpose**: Integer sequence container
- **Example**:
    ```cpp
    using seq = xieite::int_seq<1, 2, 3, 4, 5>;
    static_assert(seq::size == 5);
    ```

### `make_int_seq`
- **Header**: `meta/make_int_seq.hpp`
- **Synopsis**: `template<std::size_t N> using make_int_seq_t`
- **Purpose**: Generate integer sequence 0..N-1
- **Example**:
    ```cpp
    using seq = xieite::make_int_seq_t<5>;
    // int_seq<0, 1, 2, 3, 4>
    ```

### `int_range`
- **Header**: `meta/int_range.hpp`
- **Synopsis**: `template<int Start, int End> using int_range_t`
- **Purpose**: Generate integer range
- **Example**:
    ```cpp
    using range = xieite::int_range_t<5, 10>;
    // int_seq<5, 6, 7, 8, 9>
    ```

### `int_repeat`
- **Header**: `meta/int_repeat.hpp`
- **Synopsis**: `template<int V, std::size_t N> using int_repeat_t`
- **Purpose**: Repeat integer N times
- **Example**:
    ```cpp
    using repeated = xieite::int_repeat_t<42, 3>;
    // int_seq<42, 42, 42>
    ```

### `int_concat`
- **Header**: `meta/int_concat.hpp`
- **Synopsis**: `template<typename... Seqs> using int_concat_t`
- **Purpose**: Concatenate sequences
- **Example**:
    ```cpp
    using seq1 = xieite::int_seq<1, 2>;
    using seq2 = xieite::int_seq<3, 4>;
    using combined = xieite::int_concat_t<seq1, seq2>;
    // int_seq<1, 2, 3, 4>
    ```

### `int_transform`
- **Header**: `meta/int_transform.hpp`
- **Synopsis**: `template<template<int> class F, typename Seq> using int_transform_t`
- **Purpose**: Transform sequence values
- **Example**:
    ```cpp
    template<int I> struct double_it { static constexpr int value = I * 2; };
    using seq = xieite::int_seq<1, 2, 3>;
    using doubled = xieite::int_transform_t<double_it, seq>;
    // int_seq<2, 4, 6>
    ```

### `int_sum`
- **Header**: `meta/int_sum.hpp`
- **Synopsis**: `template<typename Seq> constexpr int int_sum_v`
- **Purpose**: Sum sequence values
- **Example**:
    ```cpp
    using seq = xieite::int_seq<1, 2, 3, 4, 5>;
    constexpr int sum = xieite::int_sum_v<seq>;  // 15
    ```

### `int_product`
- **Header**: `meta/int_product.hpp`
- **Synopsis**: `template<typename Seq> constexpr int int_product_v`
- **Purpose**: Product of sequence values
- **Example**:
    ```cpp
    using seq = xieite::int_seq<2, 3, 4>;
    constexpr int prod = xieite::int_product_v<seq>;  // 24
    ```

## Value Sequences

### `value_seq`
- **Header**: `meta/value_seq.hpp`
- **Synopsis**: `template<auto... Vs> struct value_seq`
- **Purpose**: Non-type value sequence
- **Example**:
    ```cpp
    using seq = xieite::value_seq<1, 'a', 2.5>;
    static_assert(seq::size == 3);
    ```

### `value_at`
- **Header**: `meta/value_at.hpp`
- **Synopsis**: `template<std::size_t I, typename Seq> constexpr auto value_at_v`
- **Purpose**: Get value at index
- **Example**:
    ```cpp
    using seq = xieite::value_seq<10, 20, 30>;
    constexpr auto val = xieite::value_at_v<1, seq>;  // 20
    ```

### `value_transform`
- **Header**: `meta/value_transform.hpp`
- **Synopsis**: `template<auto F, typename Seq> using value_transform_t`
- **Purpose**: Transform sequence values
- **Example**:
    ```cpp
    constexpr auto double_it = [](auto x) { return x * 2; };
    using seq = xieite::value_seq<1, 2, 3>;
    using doubled = xieite::value_transform_t<double_it, seq>;
    // value_seq<2, 4, 6>
    ```

## Template Operations

### `apply`
- **Header**: `meta/apply.hpp`
- **Synopsis**: `template<template<typename...> class F, typename List> using apply_t`
- **Purpose**: Apply template to type list
- **Example**:
    ```cpp
    using list = xieite::type_list<int, double>;
    using tuple = xieite::apply_t<std::tuple, list>;
    // std::tuple<int, double>
    ```

### `bind_front`
- **Header**: `meta/bind_front.hpp`
- **Synopsis**: `template<template<typename...> class F, typename... Ts> struct bind_front`
- **Purpose**: Bind template arguments at front
- **Example**:
    ```cpp
    template<typename... Ts> using bound =
        xieite::bind_front<std::tuple, int, double>::template apply<Ts...>;
    using result = bound<char>;  // std::tuple<int, double, char>
    ```

### `bind_back`
- **Header**: `meta/bind_back.hpp`
- **Synopsis**: `template<template<typename...> class F, typename... Ts> struct bind_back`
- **Purpose**: Bind template arguments at back
- **Example**:
    ```cpp
    template<typename... Ts> using bound =
        xieite::bind_back<std::tuple, int, double>::template apply<Ts...>;
    using result = bound<char>;  // std::tuple<char, int, double>
    ```

### `curry_template`
- **Header**: `meta/curry_template.hpp`
- **Synopsis**: `template<template<typename...> class F> struct curry_template`
- **Purpose**: Curry variadic template
- **Example**:
    ```cpp
    using curried = xieite::curry_template<std::tuple>;
    using step1 = curried::apply<int>;
    using step2 = step1::apply<double>;
    using result = step2::type;  // std::tuple<int, double>
    ```

### `quote`
- **Header**: `meta/quote.hpp`
- **Synopsis**: `template<template<typename...> class F> struct quote`
- **Purpose**: Quote template as type
- **Example**:
    ```cpp
    using quoted = xieite::quote<std::vector>;
    using vec = quoted::template apply<int>;  // std::vector<int>
    ```

### `unquote`
- **Header**: `meta/unquote.hpp`
- **Synopsis**: `template<typename Q> using unquote_t`
- **Purpose**: Extract quoted template
- **Example**:
    ```cpp
    using quoted = xieite::quote<std::vector>;
    using tmpl = xieite::unquote_t<quoted>;
    using vec = tmpl<int>;  // std::vector<int>
    ```

### `lift`
- **Header**: `meta/lift.hpp`
- **Synopsis**: `template<template<auto...> class F> struct lift`
- **Purpose**: Lift value template to type level
- **Example**:
    ```cpp
    template<int N> struct int_constant { static constexpr int value = N; };
    using lifted = xieite::lift<int_constant>;
    using result = lifted::template apply<42>;
    ```

## Substitution Detection

### `is_valid`
- **Header**: `meta/is_valid.hpp`
- **Synopsis**: `template<template<typename> class F, typename T> concept is_valid`
- **Purpose**: Check if substitution is valid
- **Example**:
    ```cpp
    template<typename T> using has_value_type = typename T::value_type;
    static_assert(xieite::is_valid<has_value_type, std::vector<int>>);
    ```

### `is_detected`
- **Header**: `meta/is_detected.hpp`
- **Synopsis**: `template<template<typename...> class Op, typename... Args> constexpr bool is_detected_v`
- **Purpose**: Detection idiom
- **Example**:
    ```cpp
    template<typename T> using has_size = decltype(std::declval<T>().size());
    static_assert(xieite::is_detected_v<has_size, std::vector<int>>);
    ```

### `detected_or`
- **Header**: `meta/detected_or.hpp`
- **Synopsis**: `template<typename Default, template<typename...> class Op, typename... Args> using detected_or_t`
- **Purpose**: Detection with default
- **Example**:
    ```cpp
    template<typename T> using get_value_type = typename T::value_type;
    using type = xieite::detected_or_t<void, get_value_type, int>;  // void
    ```

### `detected_t`
- **Header**: `meta/detected_t.hpp`
- **Synopsis**: `template<template<typename...> class Op, typename... Args> using detected_t`
- **Purpose**: Get detected type
- **Example**:
    ```cpp
    template<typename T> using get_iterator = typename T::iterator;
    using iter = xieite::detected_t<get_iterator, std::vector<int>>;
    ```

### `is_complete`
- **Header**: `meta/is_complete.hpp`
- **Synopsis**: `template<typename T> concept is_complete`
- **Purpose**: Check if type is complete
- **Example**:
    ```cpp
    struct Forward;  // Forward declaration
    static_assert(!xieite::is_complete<Forward>);
    struct Forward {};  // Definition
    static_assert(xieite::is_complete<Forward>);
    ```

### `void_t`
- **Header**: `meta/void_t.hpp`
- **Synopsis**: `template<typename...> using void_t = void`
- **Purpose**: SFINAE helper
- **Example**:
    ```cpp
    template<typename T, typename = void>
    struct has_iterator : std::false_type {};

    template<typename T>
    struct has_iterator<T, xieite::void_t<typename T::iterator>>
        : std::true_type {};
    ```

### `try_subst`
- **Header**: `meta/try_subst.hpp`
- **Synopsis**: `template<template<typename> class F, typename T, typename Default> using try_subst_t`
- **Purpose**: Try substitution with fallback
- **Example**:
    ```cpp
    template<typename T> using get_value = typename T::value_type;
    using type = xieite::try_subst_t<get_value, int, void>;  // void
    ```

### `require`
- **Header**: `meta/require.hpp`
- **Synopsis**: `template<bool B> using require = std::enable_if_t<B>`
- **Purpose**: Enable if helper
- **Example**:
    ```cpp
    template<typename T, xieite::require<std::is_integral_v<T>>* = nullptr>
    void process(T value) { /* integer processing */ }
    ```

### `require_t`
- **Header**: `meta/require_t.hpp`
- **Synopsis**: `template<typename T, template<typename> class Trait> using require_t`
- **Purpose**: Require trait to be true
- **Example**:
    ```cpp
    template<typename T, typename = xieite::require_t<T, std::is_integral>>
    void process(T value) { /* integer only */ }
    ```

## Compile-Time Repetition

### `repeat`
- **Header**: `meta/repeat.hpp`
- **Synopsis**: `template<std::size_t N, typename T> using repeat_t`
- **Purpose**: Repeat type N times
- **Example**:
    ```cpp
    using repeated = xieite::repeat_t<3, int>;
    // type_list<int, int, int>
    ```

### `repeat_to_digs`
- **Header**: `meta/repeat_to_digs.hpp`
- **Synopsis**: `template<typename T, typename Digit> using repeat_to_digs_t`
- **Purpose**: Repeat to digit count
- **Example**:
    ```cpp
    // Repeats type based on number of digits
    using result = xieite::repeat_to_digs_t<char, std::integral_constant<int, 123>>;
    // type_list<char, char, char>  (3 digits)
    ```

### `generate_n`
- **Header**: `meta/generate_n.hpp`
- **Synopsis**: `template<std::size_t N, template<std::size_t> class Gen> using generate_n_t`
- **Purpose**: Generate N types
- **Example**:
    ```cpp
    template<std::size_t I> using make_array = std::array<int, I>;
    using arrays = xieite::generate_n_t<3, make_array>;
    // type_list<std::array<int, 0>, std::array<int, 1>, std::array<int, 2>>
    ```

### `for_each`
- **Header**: `meta/for_each.hpp`
- **Synopsis**: `template<typename List, template<typename> class F> struct for_each`
- **Purpose**: Apply operation to each type
- **Example**:
    ```cpp
    using list = xieite::type_list<int, double, char>;
    template<typename T> struct print_size {
        static constexpr std::size_t value = sizeof(T);
    };
    xieite::for_each<list, print_size>::apply();
    ```

### `cartesian_product`
- **Header**: `meta/cartesian_product.hpp`
- **Synopsis**: `template<typename List1, typename List2> using cartesian_product_t`
- **Purpose**: Cartesian product of type lists
- **Example**:
    ```cpp
    using list1 = xieite::type_list<int, double>;
    using list2 = xieite::type_list<const, volatile>;
    using product = xieite::cartesian_product_t<list1, list2>;
    // type_list<pair<int,const>, pair<int,volatile>,
    //           pair<double,const>, pair<double,volatile>>
    ```

## Algorithm Utilities

### `fold`
- **Header**: `meta/fold.hpp`
- **Synopsis**: `template<typename List, typename Init, template<typename, typename> class F> using fold_t`
- **Purpose**: Fold over type list
- **Example**:
    ```cpp
    using list = xieite::type_list<int, double, char>;
    template<typename Acc, typename T>
    using sum_size = std::integral_constant<std::size_t, Acc::value + sizeof(T)>;
    using total = xieite::fold_t<list, std::integral_constant<std::size_t, 0>, sum_size>;
    ```

### `scan`
- **Header**: `meta/scan.hpp`
- **Synopsis**: `template<typename List, typename Init, template<typename, typename> class F> using scan_t`
- **Purpose**: Cumulative fold
- **Example**:
    ```cpp
    using list = xieite::type_list<int, double, char>;
    using scanned = xieite::scan_t<list, void, make_pair>;
    // Produces intermediate results
    ```

### `partition`
- **Header**: `meta/partition.hpp`
- **Synopsis**: `template<template<typename> class Pred, typename List> struct partition`
- **Purpose**: Split list by predicate
- **Example**:
    ```cpp
    using list = xieite::type_list<int, void, double, void*, char>;
    using parts = xieite::partition<std::is_void, list>;
    using voids = parts::true_types;   // type_list<void>
    using non_voids = parts::false_types;  // type_list<int, double, void*, char>
    ```

### `zip`
- **Header**: `meta/zip.hpp`
- **Synopsis**: `template<typename... Lists> using zip_t`
- **Purpose**: Zip type lists together
- **Example**:
    ```cpp
    using list1 = xieite::type_list<int, double>;
    using list2 = xieite::type_list<char, float>;
    using zipped = xieite::zip_t<list1, list2>;
    // type_list<pair<int, char>, pair<double, float>>
    ```

### `rotate`
- **Header**: `meta/rotate.hpp`
- **Synopsis**: `template<std::size_t N, typename List> using rotate_t`
- **Purpose**: Rotate type list
- **Example**:
    ```cpp
    using list = xieite::type_list<int, double, char, float>;
    using rotated = xieite::rotate_t<2, list>;
    // type_list<char, float, int, double>
    ```

## Conditional Operations

### `select`
- **Header**: `meta/select.hpp`
- **Synopsis**: `template<bool B, typename T, typename F> using select_t`
- **Purpose**: Conditional type selection
- **Example**:
    ```cpp
    using type = xieite::select_t<sizeof(int) == 4, int32_t, int64_t>;
    ```

### `conditional_apply`
- **Header**: `meta/conditional_apply.hpp`
- **Synopsis**: `template<bool B, template<typename> class F, typename T> using conditional_apply_t`
- **Purpose**: Conditionally apply template
- **Example**:
    ```cpp
    using type = xieite::conditional_apply_t<true, std::add_pointer, int>;
    // int*
    ```

### `when`
- **Header**: `meta/when.hpp`
- **Synopsis**: `template<bool B> struct when`
- **Purpose**: Enable when condition true
- **Example**:
    ```cpp
    template<typename T, typename = void>
    struct trait : std::false_type {};

    template<typename T>
    struct trait<T, xieite::when<std::is_integral_v<T>>> : std::true_type {};
    ```

## Type Inspection

### `type_name`
- **Header**: `meta/type_name.hpp`
- **Synopsis**: `template<typename T> constexpr std::string_view type_name()`
- **Purpose**: Get type name as string
- **Example**:
    ```cpp
    constexpr auto name = xieite::type_name<int>();  // "int"
    ```

### `sizeof_pack`
- **Header**: `meta/sizeof_pack.hpp`
- **Synopsis**: `template<typename... Ts> constexpr std::size_t sizeof_pack`
- **Purpose**: Size of parameter pack
- **Example**:
    ```cpp
    constexpr auto size = xieite::sizeof_pack<int, double, char>;  // 3
    ```

### `type_identity`
- **Header**: `meta/type_identity.hpp`
- **Synopsis**: `template<typename T> struct type_identity`
- **Purpose**: Identity metafunction
- **Example**:
    ```cpp
    using type = xieite::type_identity<int>::type;  // int
    ```

## Usage Examples

### Type List Manipulation

```cpp
#include <xieite/meta/type_list.hpp>
#include <xieite/meta/type_transform.hpp>
#include <xieite/meta/type_filter.hpp>

using types = xieite::type_list<int, double, char, void>;
using pointers = xieite::type_transform_t<std::add_pointer, types>;
// type_list<int*, double*, char*, void*>

template<typename T> using is_not_void = std::negation<std::is_void<T>>;
using non_void = xieite::type_filter_t<is_not_void, types>;
// type_list<int, double, char>
```

### Compile-Time Sequences
```cpp
#include <xieite/meta/int_seq.hpp>
#include <xieite/meta/int_transform.hpp>

template<int I> struct factorial {
    static constexpr int value = I * factorial<I-1>::value;
};
template<> struct factorial<0> { static constexpr int value = 1; };

using indices = xieite::int_seq<1, 2, 3, 4, 5>;
using factorials = xieite::int_transform_t<factorial, indices>;
// int_seq<1, 2, 6, 24, 120>
```

### Detection Idiom
```cpp
#include <xieite/meta/is_detected.hpp>
#include <xieite/meta/detected_or.hpp>

template<typename T> using has_value_type = typename T::value_type;
template<typename T> using has_size = decltype(std::declval<T>().size());

template<typename T>
constexpr bool is_container =
    xieite::is_detected_v<has_value_type, T> &&
    xieite::is_detected_v<has_size, T>;

static_assert(is_container<std::vector<int>>);
static_assert(!is_container<int>);
```

### Template Currying
```cpp
#include <xieite/meta/curry_template.hpp>

using curried_tuple = xieite::curry_template<std::tuple>;
using step1 = curried_tuple::apply<int>;
using step2 = step1::apply<double>;
using step3 = step2::apply<char>;
using result = step3::type;  // std::tuple<int, double, char>
```

## Performance Notes

- All operations are compile-time with zero runtime cost
- Type lists are purely compile-time constructs
- Template instantiation depth may be a concern for large lists
- Consider chunking operations for very large type lists
- Use lazy instantiation patterns when possible

## See Also

- [Metaprogramming Overview](../../categories/meta/README.md)
- [Template Manipulation](../../categories/meta/templates.md)
- [Compile-Time Sequences](../../categories/meta/sequences.md)
- [Type Traits API](./trait.md)
