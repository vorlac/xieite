# Data Structures API Reference

## Overview

The data structures category contains enhanced containers, string utilities, iterator helpers, and algorithms optimized for both compile-time and runtime use.

## Fixed Containers

### `fixed_array`
- **Header**: `data/fixed_array.hpp`
- **Synopsis**: `template<typename T, std::size_t N> class fixed_array`
- **Purpose**: Compile-time fixed array with constexpr operations
- **Example**:
    ```cpp
    xieite::fixed_array<int, 5> arr{1, 2, 3, 4, 5};
    assert(arr[0] == 1);
    assert(arr.size() == 5);
    ```

### `fixed_str`
- **Header**: `data/fixed_str.hpp`
- **Synopsis**: `template<xieite::is_char Char, std::size_t N> struct fixed_str`
- **Purpose**: Fixed-size string container
- **Example**:
    ```cpp
    xieite::fixed_str<char, 10> str("Hello");
    auto view = str.view();  // Get string_view
    assert(str.size() == 10);
    ```

### `fixed_map`
- **Header**: `data/fixed_map.hpp`
- **Purpose**: Fixed-capacity map container

### `fixed_set`
- **Header**: `data/fixed_set.hpp`
- **Purpose**: Fixed-capacity set container

## String Utilities

### `str_split`
- **Header**: `data/str_split.hpp`
- **Synopsis**: `template<is_char Char, typename Traits, typename VecAlloc> vector<string_view<Char, Traits>, VecAlloc> str_split(string_view<Char, Traits> strv, string_view<Char, Traits> delim, bool discard_empty = false, const VecAlloc& vec_alloc = {})`
- **Purpose**: Split strings by delimiter returning vector of string views
- **Description**: Splits a string into parts based on a delimiter. Can optionally discard empty segments. The function returns a vector of string_view objects pointing into the original string.
- **Example**:
    ```cpp
    #include <xieite/data/str_split.hpp>
    #include <vector>
    #include <string_view>

    std::string text = "apple,banana,cherry";
    auto parts = xieite::str_split(text, ",");
    // parts contains: ["apple", "banana", "cherry"]

    // With empty segments
    std::string text2 = "a,,b";
    auto parts2 = xieite::str_split(text2, ",", false);  // Keep empty
    // parts2 contains: ["a", "", "b"]

    auto parts3 = xieite::str_split(text2, ",", true);   // Discard empty
    // parts3 contains: ["a", "b"]
    ```

### `str_join`
- **Header**: `data/str_join.hpp`
- **Synopsis**: `template<input_range Range, is_char Char, typename Traits, typename Alloc> string<Char, Traits, Alloc> str_join(Range&& range, string_view<Char, Traits> delim = "", string_view<Char, Traits> pfx = "", string_view<Char, Traits> sfx = "", const Alloc& alloc = {})`
- **Purpose**: Join elements from a range into a string with optional delimiter, prefix, and suffix
- **Description**: Takes a range of string-like objects and joins them together with a delimiter. Optionally adds prefix and suffix to the entire result.
- **Example**:
    ```cpp
    #include <xieite/data/str_join.hpp>
    #include <vector>
    #include <string>

    std::vector<std::string> words = {"apple", "banana", "cherry"};
    auto result = xieite::str_join(words, ", ");
    // result is "apple, banana, cherry"

    // With prefix and suffix
    auto result2 = xieite::str_join(words, ", ", "[", "]");
    // result2 is "[apple, banana, cherry]"

    // Join with no delimiter
    auto result3 = xieite::str_join(words);
    // result3 is "applebananacherry"
    ```

### `make_str_view`
- **Header**: `data/make_str_view.hpp`
- **Synopsis**: Various overloads for creating string_view from different sources
- **Purpose**: String view creation utilities with automatic type deduction
- **Description**: Creates string_view objects from various string sources including C-style strings, std::string, character literals, and fixed arrays. Handles null-terminated strings correctly.
- **Example**:
    ```cpp
    #include <xieite/data/make_str_view.hpp>
    #include <string>

    // From string literal
    auto sv1 = xieite::make_str_view("hello");

    // From std::string
    std::string str = "world";
    auto sv2 = xieite::make_str_view(str);

    // From single character
    auto sv3 = xieite::make_str_view('x');

    // From existing string_view
    std::string_view existing = "test";
    auto sv4 = xieite::make_str_view(existing);
    ```

## Character Utilities

### `isalnum`
- **Header**: `data/isalnum.hpp`
- **Synopsis**: `bool isalnum(is_char auto c)` and overloads for strings
- **Purpose**: Check if character or all characters in string are alphanumeric
- **Description**: Checks if a character is alphanumeric (letters or digits) or if all characters in a string are alphanumeric. Returns true for characters a-z, A-Z, 0-9.
- **Example**:
    ```cpp
    #include <xieite/data/isalnum.hpp>

    // Single character
    assert(xieite::isalnum('a') == true);
    assert(xieite::isalnum('5') == true);
    assert(xieite::isalnum('!') == false);

    // String
    assert(xieite::isalnum("abc123") == true);
    assert(xieite::isalnum("abc-123") == false);  // Contains hyphen
    ```

### `isalpha`
- **Header**: `data/isalpha.hpp`
- **Synopsis**: `bool isalpha(is_char auto c)` and overloads for strings
- **Purpose**: Check if character or all characters in string are alphabetic
- **Description**: Checks if a character is alphabetic (letters only) or if all characters in a string are alphabetic. Returns true for characters a-z, A-Z.
- **Example**:
    ```cpp
    #include <xieite/data/isalpha.hpp>

    assert(xieite::isalpha('a') == true);
    assert(xieite::isalpha('Z') == true);
    assert(xieite::isalpha('5') == false);
    assert(xieite::isalpha("hello") == true);
    assert(xieite::isalpha("hello5") == false);
    ```

### `isdigit`
- **Header**: `data/isdigit.hpp`
- **Synopsis**: `bool isdigit(is_char auto c)` and overloads for strings
- **Purpose**: Check if character or all characters in string are digits
- **Description**: Checks if a character is a digit (0-9) or if all characters in a string are digits.
- **Example**:
    ```cpp
    #include <xieite/data/isdigit.hpp>

    assert(xieite::isdigit('5') == true);
    assert(xieite::isdigit('a') == false);
    assert(xieite::isdigit("12345") == true);
    assert(xieite::isdigit("123a") == false);
    ```

### `islower`
- **Header**: `data/islower.hpp`
- **Synopsis**: `bool islower(is_char auto c)` and overloads for strings
- **Purpose**: Check if character or all characters in string are lowercase
- **Description**: Checks if a character is lowercase or if all alphabetic characters in a string are lowercase.
- **Example**:
    ```cpp
    #include <xieite/data/islower.hpp>

    assert(xieite::islower('a') == true);
    assert(xieite::islower('A') == false);
    assert(xieite::islower("hello") == true);
    assert(xieite::islower("Hello") == false);
    ```

### `isupper`
- **Header**: `data/isupper.hpp`
- **Synopsis**: `bool isupper(is_char auto c)` and overloads for strings
- **Purpose**: Check if character or all characters in string are uppercase
- **Description**: Checks if a character is uppercase or if all alphabetic characters in a string are uppercase.
- **Example**:
    ```cpp
    #include <xieite/data/isupper.hpp>

    assert(xieite::isupper('A') == true);
    assert(xieite::isupper('a') == false);
    assert(xieite::isupper("HELLO") == true);
    assert(xieite::isupper("Hello") == false);
    ```

### `isspace`
- **Header**: `data/isspace.hpp`
- **Synopsis**: `bool isspace(is_char auto c)` and overloads for strings
- **Purpose**: Check if character or all characters in string are whitespace
- **Description**: Checks if a character is whitespace (space, tab, newline, etc.) or if all characters in a string are whitespace.
- **Example**:
    ```cpp
    #include <xieite/data/isspace.hpp>

    assert(xieite::isspace(' ') == true);
    assert(xieite::isspace('\t') == true);
    assert(xieite::isspace('a') == false);
    assert(xieite::isspace("   ") == true);
    assert(xieite::isspace(" a ") == false);
    ```

## Iterator Utilities

### `iters`
- **Header**: `data/iters.hpp`
- **Purpose**: Iterator helper utilities

### Array Utilities

### `make_array`
- **Header**: `data/make_array.hpp`
- **Synopsis**: `template<typename Value, std::size_t length> array<Value, length> make_array(Range&& range, Fn&& conv = {})`
- **Purpose**: Create arrays from ranges with optional conversion function

## Search Utilities

### `find_most_consec`
- **Header**: `data/find_most_consec.hpp`
- **Synopsis**: `subrange<iterator_t<Range>> find_most_consec(Range& range, range_common_reference_t<const Range> value, Fn&& cmp = {})`
- **Purpose**: Find the longest consecutive sequence of a specific value in a range
- **Description**: Searches through a range to find the longest consecutive sequence of elements equal to the given value. Returns a subrange pointing to the longest sequence found.
- **Example**:
    ```cpp
    #include <xieite/data/find_most_consec.hpp>
    #include <vector>

    std::vector<int> data = {1, 2, 2, 2, 3, 2, 2, 4};
    auto longest = xieite::find_most_consec(data, 2);
    // longest points to the sequence of three 2's at indices 1-3
    assert(std::distance(longest.begin(), longest.end()) == 3);
    ```

### `find_most_consec_if`
- **Header**: `data/find_most_consec_if.hpp`
- **Synopsis**: `subrange<iterator_t<Range>> find_most_consec_if(Range& range, Fn&& predicate)`
- **Purpose**: Find the longest consecutive sequence of elements matching a predicate
- **Description**: Similar to find_most_consec but uses a predicate function to determine matching elements instead of equality comparison.
- **Example**:
    ```cpp
    #include <xieite/data/find_most_consec_if.hpp>
    #include <vector>

    std::vector<int> data = {1, 4, 6, 8, 3, 2, 4, 6};
    auto longest = xieite::find_most_consec_if(data, [](int x) { return x % 2 == 0; });
    // longest points to the sequence of even numbers 4, 6, 8
    assert(std::distance(longest.begin(), longest.end()) == 3);
    ```

### `find_occur`
- **Header**: `data/find_occur.hpp`
- **Synopsis**: Various overloads for finding occurrences in sequences
- **Purpose**: Find occurrences of elements or subsequences in a range
- **Description**: Searches for occurrences of specific values or patterns within a range and returns information about their positions.
- **Example**:
    ```cpp
    #include <xieite/data/find_occur.hpp>
    #include <vector>

    std::vector<int> data = {1, 2, 3, 2, 5, 2};
    auto occurrences = xieite::find_occur(data, 2);
    // Returns information about where value 2 occurs in the sequence
    ```

### `find_occur_if`
- **Header**: `data/find_occur_if.hpp`
- **Synopsis**: Various overloads for finding occurrences with predicate
- **Purpose**: Find occurrences of elements matching a predicate in a range
- **Description**: Similar to find_occur but uses a predicate function to determine matching elements.
- **Example**:
    ```cpp
    #include <xieite/data/find_occur_if.hpp>
    #include <vector>

    std::vector<int> data = {1, 4, 3, 6, 5, 8};
    auto occurrences = xieite::find_occur_if(data, [](int x) { return x % 2 == 0; });
    // Returns information about where even numbers occur
    ```

## String Position Utilities

### `after`
- **Header**: `data/after.hpp`
- **Synopsis**: `auto after(Range0&& range, Range1&& subrange)` and `auto after(Range&& range, range_common_reference_t<Range> x)`
- **Purpose**: Get portion of range after a delimiter or subsequence
- **Description**: Returns a subrange containing everything after the first occurrence of the specified delimiter or subsequence. If the delimiter is not found, returns an empty range.
- **Example**:
    ```cpp
    #include <xieite/data/after.hpp>
    #include <string>

    std::string text = "hello-world-test";
    auto result = xieite::after(text, "-");
    // result contains "world-test"

    auto result2 = xieite::after(text, 'o');
    // result2 contains "llo-world-test" (after first 'o')
    ```

### `after_last`
- **Header**: `data/after_last.hpp`
- **Synopsis**: Similar to `after` but finds last occurrence
- **Purpose**: Get portion of range after the last occurrence of delimiter
- **Description**: Returns a subrange containing everything after the last occurrence of the specified delimiter. Useful for extracting file extensions or final path components.
- **Example**:
    ```cpp
    #include <xieite/data/after_last.hpp>
    #include <string>

    std::string path = "path/to/file.txt";
    auto extension = xieite::after_last(path, ".");
    // extension contains "txt"

    std::string text = "a-b-c-d";
    auto result = xieite::after_last(text, "-");
    // result contains "d"
    ```

### `before`
- **Header**: `data/before.hpp`
- **Synopsis**: `auto before(Range0&& range, Range1&& subrange)` and `auto before(Range&& range, range_common_reference_t<Range> x)`
- **Purpose**: Get portion of range before a delimiter or subsequence
- **Description**: Returns a subrange containing everything before the first occurrence of the specified delimiter or subsequence.
- **Example**:
    ```cpp
    #include <xieite/data/before.hpp>
    #include <string>

    std::string text = "hello-world-test";
    auto result = xieite::before(text, "-");
    // result contains "hello"

    std::string email = "user@domain.com";
    auto username = xieite::before(email, "@");
    // username contains "user"
    ```

### `before_last`
- **Header**: `data/before_last.hpp`
- **Synopsis**: Similar to `before` but finds last occurrence
- **Purpose**: Get portion of range before the last occurrence of delimiter
- **Description**: Returns a subrange containing everything before the last occurrence of the specified delimiter. Useful for extracting directory paths or base names.
- **Example**:
    ```cpp
    #include <xieite/data/before_last.hpp>
    #include <string>

    std::string path = "path/to/file.txt";
    auto basename = xieite::before_last(path, ".");
    // basename contains "path/to/file"

    std::string text = "a-b-c-d";
    auto result = xieite::before_last(text, "-");
    // result contains "a-b-c"
    ```

### `between`
- **Header**: `data/between.hpp`
- **Synopsis**: `auto between(auto&& range, auto&& a, auto&& b)`
- **Purpose**: Get portion of range between two delimiters
- **Description**: Returns a subrange containing everything between the first occurrence of delimiter `a` and the first occurrence of delimiter `b` after `a`. Combines `after` and `before` operations.
- **Example**:
    ```cpp
    #include <xieite/data/between.hpp>
    #include <string>

    std::string text = "start[content]end";
    auto result = xieite::between(text, "[", "]");
    // result contains "content"

    std::string xml = "<tag>value</tag>";
    auto value = xieite::between(xml, ">", "<");
    // value contains "value"
    ```

## Usage Examples

### Fixed Containers
```cpp
#include <xieite/data/fixed_array.hpp>
#include <xieite/data/fixed_str.hpp>

// Fixed array
xieite::fixed_array<int, 5> arr = {1, 2, 3, 4, 5};
assert(arr.size() == 5);

// Fixed string
xieite::fixed_str<char, 10> str("Hello");
auto view = str.view();
```

### String Operations
```cpp
#include <xieite/data/str_split.hpp>
#include <xieite/data/str_join.hpp>
#include <xieite/data/make_str_view.hpp>
```

## Implementation Notes
1. **Template parameter order**: `fixed_str` requires character type first, then size
2. **Method names**: Use `.view()` for accessing fixed_str content
3. **make_array**: Takes a range and optional conversion function

## See Also
- [Data Structures Category Overview](../../categories/data/README.md)
