# Data Structures API Reference

## Overview

The data structures category contains 65 header files providing enhanced containers, string utilities, iterator helpers, and algorithms optimized for both compile-time and runtime use.

## Organization

The data headers are organized into functional groups:

- **Compile-Time Structures** (15+ headers): Fixed-size containers and compile-time data
- **String Utilities** (20+ headers): String manipulation and parsing
- **Iterator Utilities** (10+ headers): Iterator adapters and helpers
- **Container Algorithms** (10+ headers): Enhanced container operations
- **Memory Management** (5+ headers): Smart pointers and allocators
- **Range Utilities** (5+ headers): Range-based operations

## Compile-Time Data Structures

### Fixed Arrays

#### fixed_array
- **Header**: `data/fixed_array.hpp`
- **Synopsis**: `template<typename T, std::size_t N> class fixed_array`
- **Purpose**: Compile-time fixed array with constexpr operations
- **Example**:
    ```cpp
    constexpr xieite::fixed_array<int, 5> arr{1, 2, 3, 4, 5};
    constexpr auto sum = arr.apply([](auto... values) { return (values + ...); });  // 15
    ```

#### fixed_vector
- **Header**: `data/fixed_vector.hpp`
- **Synopsis**: `template<typename T, std::size_t Capacity> class fixed_vector`
- **Purpose**: Stack-allocated vector with fixed capacity
- **Example**:
    ```cpp
    xieite::fixed_vector<int, 100> vec;
    vec.push_back(42);  // No heap allocation
    ```

#### bit_array
- **Header**: `data/bit_array.hpp`
- **Synopsis**: `template<std::size_t N> class bit_array`
- **Purpose**: Space-efficient bit storage
- **Example**:
    ```cpp
    xieite::bit_array<64> bits;
    bits.set(10);
    bits.flip(20);
    ```

### Compile-Time Strings

#### static_string
- **Header**: `data/static_string.hpp`
- **Synopsis**: `template<std::size_t N> class static_string`
- **Purpose**: Compile-time string with constexpr operations
- **Example**:
    ```cpp
    constexpr xieite::static_string<20> str{"Hello"};
    constexpr auto len = str.length();  // 5
    ```

#### fixed_string
- **Header**: `data/fixed_string.hpp`
- **Synopsis**: `template<std::size_t N> struct fixed_string`
- **Purpose**: String literal wrapper for template parameters
- **Example**:
    ```cpp
    template<xieite::fixed_string Name>
    struct named_type {
        static constexpr auto name = Name;
    };
    ```

## String Utilities

### String Manipulation

#### split
- **Header**: `data/split.hpp`
- **Synopsis**: `auto split(std::string_view str, std::string_view delimiter)`
- **Purpose**: Split string by delimiter
- **Example**:
    ```cpp
    auto parts = xieite::split("a,b,c", ",");
    // parts = {"a", "b", "c"}
    ```

#### join
- **Header**: `data/join.hpp`
- **Synopsis**: `template<typename Range> std::string join(const Range& r, std::string_view sep)`
- **Purpose**: Join range elements with separator
- **Example**:
    ```cpp
    std::vector<std::string> v{"a", "b", "c"};
    auto result = xieite::join(v, ", ");  // "a, b, c"
    ```

#### trim
- **Header**: `data/trim.hpp`
- **Synopsis**: `std::string_view trim(std::string_view str)`
- **Purpose**: Remove leading/trailing whitespace
- **Example**:
    ```cpp
    auto trimmed = xieite::trim("  hello  ");  // "hello"
    ```

#### trim_left
- **Header**: `data/trim_left.hpp`
- **Synopsis**: `std::string_view trim_left(std::string_view str)`
- **Purpose**: Remove leading whitespace

#### trim_right
- **Header**: `data/trim_right.hpp`
- **Synopsis**: `std::string_view trim_right(std::string_view str)`
- **Purpose**: Remove trailing whitespace

#### replace
- **Header**: `data/replace.hpp`
- **Synopsis**: `std::string replace(std::string_view str, std::string_view from, std::string_view to)`
- **Purpose**: Replace all occurrences
- **Example**:
    ```cpp
    auto result = xieite::replace("hello world", "o", "0");  // "hell0 w0rld"
    ```

#### replace_first
- **Header**: `data/replace_first.hpp`
- **Synopsis**: Replace first occurrence only

#### replace_last
- **Header**: `data/replace_last.hpp`
- **Synopsis**: Replace last occurrence only

### String Queries

#### starts_with
- **Header**: `data/starts_with.hpp`
- **Synopsis**: `bool starts_with(std::string_view str, std::string_view prefix)`
- **Purpose**: Check string prefix
- **Example**:
    ```cpp
    xieite::starts_with("hello", "hel")  // true
    ```

#### ends_with
- **Header**: `data/ends_with.hpp`
- **Synopsis**: `bool ends_with(std::string_view str, std::string_view suffix)`
- **Purpose**: Check string suffix

#### contains
- **Header**: `data/contains.hpp`
- **Synopsis**: `bool contains(std::string_view str, std::string_view substr)`
- **Purpose**: Check substring presence

#### count
- **Header**: `data/count.hpp`
- **Synopsis**: `std::size_t count(std::string_view str, std::string_view substr)`
- **Purpose**: Count substring occurrences

### Case Conversion

#### to_lower
- **Header**: `data/to_lower.hpp`
- **Synopsis**: `std::string to_lower(std::string_view str)`
- **Purpose**: Convert to lowercase
- **Example**:
    ```cpp
    xieite::to_lower("Hello")  // "hello"
    ```

#### to_upper
- **Header**: `data/to_upper.hpp`
- **Synopsis**: `std::string to_upper(std::string_view str)`
- **Purpose**: Convert to uppercase

#### to_title
- **Header**: `data/to_title.hpp`
- **Synopsis**: `std::string to_title(std::string_view str)`
- **Purpose**: Convert to title case

#### to_snake_case
- **Header**: `data/to_snake_case.hpp`
- **Synopsis**: Convert to snake_case

#### to_camel_case
- **Header**: `data/to_camel_case.hpp`
- **Synopsis**: Convert to camelCase

#### to_pascal_case
- **Header**: `data/to_pascal_case.hpp`
- **Synopsis**: Convert to PascalCase

## Iterator Utilities

### Iterator Adapters

#### enumerate
- **Header**: `data/enumerate.hpp`
- **Synopsis**: `auto enumerate(Range&& range)`
- **Purpose**: Add index to iteration
- **Example**:
    ```cpp
    std::vector<std::string> v{"a", "b", "c"};
    for (auto [i, val] : xieite::enumerate(v)) {
        std::cout << i << ": " << val << '\n';
    }
    ```

#### zip
- **Header**: `data/zip.hpp`
- **Synopsis**: `auto zip(Range1&& r1, Range2&& r2)`
- **Purpose**: Iterate multiple ranges together
- **Example**:
    ```cpp
    std::vector<int> nums{1, 2, 3};
    std::vector<char> chars{'a', 'b', 'c'};
    for (auto [n, c] : xieite::zip(nums, chars)) {
        // n=1,c='a'; n=2,c='b'; n=3,c='c'
    }
    ```

#### filter
- **Header**: `data/filter.hpp`
- **Synopsis**: `auto filter(Range&& range, Pred pred)`
- **Purpose**: Filter range elements
- **Example**:
    ```cpp
    std::vector<int> v{1, 2, 3, 4, 5};
    for (int n : xieite::filter(v, [](int x) { return x % 2 == 0; })) {
        // n = 2, 4
    }
    ```

#### transform
- **Header**: `data/transform.hpp`
- **Synopsis**: `auto transform(Range&& range, Func func)`
- **Purpose**: Transform range elements
- **Example**:
    ```cpp
    std::vector<int> v{1, 2, 3};
    for (int n : xieite::transform(v, [](int x) { return x * 2; })) {
        // n = 2, 4, 6
    }
    ```

#### take
- **Header**: `data/take.hpp`
- **Synopsis**: `auto take(Range&& range, std::size_t n)`
- **Purpose**: Take first n elements
- **Example**:
    ```cpp
    std::vector<int> v{1, 2, 3, 4, 5};
    for (int n : xieite::take(v, 3)) {
        // n = 1, 2, 3
    }
    ```

#### drop
- **Header**: `data/drop.hpp`
- **Synopsis**: `auto drop(Range&& range, std::size_t n)`
- **Purpose**: Skip first n elements

#### cycle
- **Header**: `data/cycle.hpp`
- **Synopsis**: `auto cycle(Range&& range)`
- **Purpose**: Infinitely repeat range

#### reverse
- **Header**: `data/reverse.hpp`
- **Synopsis**: `auto reverse(Range&& range)`
- **Purpose**: Reverse iteration order

## Container Algorithms

### Sorting and Searching

#### sort
- **Header**: `data/sort.hpp`
- **Synopsis**: `void sort(Container& c, Compare comp = {})`
- **Purpose**: In-place container sort
- **Example**:
    ```cpp
    std::vector<int> v{3, 1, 4, 1, 5};
    xieite::sort(v);  // {1, 1, 3, 4, 5}
    ```

#### stable_sort
- **Header**: `data/stable_sort.hpp`
- **Synopsis**: Stable sorting algorithm

#### binary_search
- **Header**: `data/binary_search.hpp`
- **Synopsis**: `auto binary_search(const Container& c, const T& value)`
- **Purpose**: Binary search in sorted container

#### lower_bound
- **Header**: `data/lower_bound.hpp`
- **Synopsis**: Find first not less than value

#### upper_bound
- **Header**: `data/upper_bound.hpp`
- **Synopsis**: Find first greater than value

### Set Operations

#### unique
- **Header**: `data/unique.hpp`
- **Synopsis**: `void unique(Container& c)`
- **Purpose**: Remove consecutive duplicates
- **Example**:
    ```cpp
    std::vector<int> v{1, 1, 2, 2, 3};
    xieite::unique(v);  // {1, 2, 3}
    ```

#### intersection
- **Header**: `data/intersection.hpp`
- **Synopsis**: `auto intersection(const Container1& c1, const Container2& c2)`
- **Purpose**: Set intersection

#### union_set
- **Header**: `data/union_set.hpp`
- **Synopsis**: `auto union_set(const Container1& c1, const Container2& c2)`
- **Purpose**: Set union

#### difference
- **Header**: `data/difference.hpp`
- **Synopsis**: `auto difference(const Container1& c1, const Container2& c2)`
- **Purpose**: Set difference

### Container Queries

#### all_of
- **Header**: `data/all_of.hpp`
- **Synopsis**: `bool all_of(const Container& c, Pred pred)`
- **Purpose**: Check if all elements satisfy predicate

#### any_of
- **Header**: `data/any_of.hpp`
- **Synopsis**: `bool any_of(const Container& c, Pred pred)`
- **Purpose**: Check if any element satisfies predicate

#### none_of
- **Header**: `data/none_of.hpp`
- **Synopsis**: `bool none_of(const Container& c, Pred pred)`
- **Purpose**: Check if no elements satisfy predicate

#### find
- **Header**: `data/find.hpp`
- **Synopsis**: `auto find(const Container& c, const T& value)`
- **Purpose**: Find element in container

#### find_if
- **Header**: `data/find_if.hpp`
- **Synopsis**: `auto find_if(const Container& c, Pred pred)`
- **Purpose**: Find element by predicate

## Specialized Containers

### Ring Buffer

#### ring_buffer
- **Header**: `data/ring_buffer.hpp`
- **Synopsis**: `template<typename T, std::size_t N> class ring_buffer`
- **Purpose**: Fixed-size circular buffer
- **Example**:
    ```cpp
    xieite::ring_buffer<int, 3> buf;
    buf.push(1);
    buf.push(2);
    buf.push(3);
    buf.push(4);  // Overwrites 1
    ```

### Flat Containers

#### flat_map
- **Header**: `data/flat_map.hpp`
- **Synopsis**: `template<typename K, typename V> class flat_map`
- **Purpose**: Cache-friendly sorted map
- **Example**:
    ```cpp
    xieite::flat_map<int, std::string> map;
    map[1] = "one";
    map[2] = "two";
    ```

#### flat_set
- **Header**: `data/flat_set.hpp`
- **Synopsis**: `template<typename T> class flat_set`
- **Purpose**: Cache-friendly sorted set

### Small Containers

#### small_vector
- **Header**: `data/small_vector.hpp`
- **Synopsis**: `template<typename T, std::size_t N> class small_vector`
- **Purpose**: Vector with small buffer optimization
- **Example**:
    ```cpp
    xieite::small_vector<int, 5> vec;  // Stack storage for 5 elements
    vec.push_back(1);  // No allocation
    ```

#### small_string
- **Header**: `data/small_string.hpp`
- **Synopsis**: String with small buffer optimization

## Memory Utilities

### Smart Pointers

#### observer_ptr
- **Header**: `data/observer_ptr.hpp`
- **Synopsis**: `template<typename T> class observer_ptr`
- **Purpose**: Non-owning pointer wrapper
- **Example**:
    ```cpp
    int x = 42;
    xieite::observer_ptr<int> p{&x};
    ```

#### clone_ptr
- **Header**: `data/clone_ptr.hpp`
- **Synopsis**: `template<typename T> class clone_ptr`
- **Purpose**: Deep-copying smart pointer

### Memory Operations

#### uninitialized_array
- **Header**: `data/uninitialized_array.hpp`
- **Synopsis**: Array without default construction

#### aligned_storage
- **Header**: `data/aligned_storage.hpp`
- **Synopsis**: Aligned memory storage

## Parsing Utilities

#### parse
- **Header**: `data/parse.hpp`
- **Synopsis**: `template<typename T> std::optional<T> parse(std::string_view str)`
- **Purpose**: Parse string to type
- **Example**:
    ```cpp
    auto n = xieite::parse<int>("42");     // std::optional(42)
    auto f = xieite::parse<float>("3.14"); // std::optional(3.14f)
    ```

#### parse_csv
- **Header**: `data/parse_csv.hpp`
- **Synopsis**: Parse CSV data

#### parse_json
- **Header**: `data/parse_json.hpp`
- **Synopsis**: Basic JSON parsing

## Numeric Strings

#### is_numeric
- **Header**: `data/is_numeric.hpp`
- **Synopsis**: `bool is_numeric(std::string_view str)`
- **Purpose**: Check if string is numeric

#### is_integer
- **Header**: `data/is_integer.hpp`
- **Synopsis**: Check if string represents integer

#### is_float
- **Header**: `data/is_float.hpp`
- **Synopsis**: Check if string represents float

## String Builders

#### string_builder
- **Header**: `data/string_builder.hpp`
- **Synopsis**: `class string_builder`
- **Purpose**: Efficient string concatenation
- **Example**:
    ```cpp
    xieite::string_builder sb;
    sb << "Hello" << ' ' << "World" << '!';
    std::string result = sb.str();  // "Hello World!"
    ```

## Hashing Utilities

#### hash_combine
- **Header**: `data/hash_combine.hpp`
- **Synopsis**: `void hash_combine(std::size_t& seed, const T& value)`
- **Purpose**: Combine hash values
- **Example**:
    ```cpp
    std::size_t h = 0;
    xieite::hash_combine(h, "hello");
    xieite::hash_combine(h, 42);
    ```

#### fnv1a_hash
- **Header**: `data/fnv1a_hash.hpp`
- **Synopsis**: FNV-1a hash algorithm

## Encoding Utilities

#### base64_encode
- **Header**: `data/base64_encode.hpp`
- **Synopsis**: Base64 encoding

#### base64_decode
- **Header**: `data/base64_decode.hpp`
- **Synopsis**: Base64 decoding

#### url_encode
- **Header**: `data/url_encode.hpp`
- **Synopsis**: URL encoding

#### url_decode
- **Header**: `data/url_decode.hpp`
- **Synopsis**: URL decoding

## Validation

#### is_palindrome
- **Header**: `data/is_palindrome.hpp`
- **Synopsis**: `bool is_palindrome(std::string_view str)`
- **Purpose**: Check if palindrome

#### is_anagram
- **Header**: `data/is_anagram.hpp`
- **Synopsis**: `bool is_anagram(std::string_view s1, std::string_view s2)`
- **Purpose**: Check if anagrams

## Range Utilities

#### chunk
- **Header**: `data/chunk.hpp`
- **Synopsis**: `auto chunk(Range&& r, std::size_t size)`
- **Purpose**: Split range into chunks
- **Example**:
    ```cpp
    std::vector<int> v{1,2,3,4,5,6};
    for (auto chunk : xieite::chunk(v, 2)) {
        // chunk = {1,2}, {3,4}, {5,6}
    }
    ```

#### slide
- **Header**: `data/slide.hpp`
- **Synopsis**: `auto slide(Range&& r, std::size_t window)`
- **Purpose**: Sliding window over range

#### adjacent
- **Header**: `data/adjacent.hpp`
- **Synopsis**: `auto adjacent<N>(Range&& r)`
- **Purpose**: Adjacent elements

## Usage Examples

### String Processing
```cpp
#include <xieite/data/split.hpp>
#include <xieite/data/trim.hpp>
#include <xieite/data/join.hpp>

std::string input = "  hello, world  ";
auto trimmed = xieite::trim(input);
auto parts = xieite::split(trimmed, ", ");
auto result = xieite::join(parts, " | ");  // "hello | world"
```

### Container Operations
```cpp
#include <xieite/data/enumerate.hpp>
#include <xieite/data/filter.hpp>

std::vector<int> numbers{1, 2, 3, 4, 5};
for (auto [i, val] : xieite::enumerate(numbers)) {
    if (val % 2 == 0) {
        std::cout << "Even at " << i << ": " << val << '\n';
    }
}
```

### Compile-Time Data
```cpp
#include <xieite/data/fixed_array.hpp>

constexpr xieite::fixed_array<int, 5> data{1, 2, 3, 4, 5};
constexpr auto sum = data.apply([](auto... values) { return (values + ...); });
static_assert(sum == 15);
```

## Performance Notes

- Small buffer optimization reduces allocations
- Flat containers improve cache locality
- String views avoid unnecessary copies
- Compile-time structures enable optimization
- Iterator adapters have minimal overhead

## See Also

- [Data Structures Overview](../../categories/data/README.md)
- [Iterator Patterns](../../categories/data/iterators.md)
- [String Utilities](../../categories/data/strings.md)
- [Functional API](./fn.md)
