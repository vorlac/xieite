# Range Utilities

## Overview

XIEITE provides range manipulation utilities for string joining, partial reversal, and range-based operations. These utilities extend the C++20 ranges library with specialized operations for common use cases.

## String Range Operations

### Comprehensive String Joining
Implementation: `include/xieite/data/str_join.hpp` (lines 19-76)

```cpp
template<std::ranges::input_range Range, is_char Char, typename Traits, typename Alloc>
constexpr basic_string<Char, Traits, Alloc>
str_join(Range&& range,
         basic_string_view<Char, Traits> delimiter = "",
         basic_string_view<Char, Traits> prefix = "",
         basic_string_view<Char, Traits> suffix = "",
         const Alloc& allocator = {});
```

Multiple overloads support various delimiter, prefix, and suffix types including characters, strings, and string views.

## Range Transformation

### Partial Range Reversal
Implementation: `include/xieite/data/partial_reverse.hpp` (lines 14-28)

```cpp
template<std::ranges::bidirectional_range Range,
         is_invoc<bool(range_reference_t<Range>)> Fn>
constexpr void partial_reverse(Range& range, Fn&& condition);
```

Reverses only the elements that satisfy the given predicate, leaving others in their original positions.

## Usage Examples

### String Joining Operations
```cpp
#include <xieite/data/str_join.hpp>

// Basic joining
std::vector<std::string> words{"Hello", "beautiful", "world"};
auto sentence = xieite::str_join(words, " ");
std::cout << sentence << "\n";  // "Hello beautiful world"

// With prefix and suffix
std::vector<int> numbers{1, 2, 3, 4, 5};
auto formatted = xieite::str_join(numbers, ", ", "[", "]");
std::cout << formatted << "\n";  // "[1, 2, 3, 4, 5]"

// Character delimiters
std::vector<std::string> items{"apple", "banana", "cherry"};
auto csv = xieite::str_join(items, ',');
std::cout << csv << "\n";  // "apple,banana,cherry"
```

### Advanced String Formatting
```cpp
#include <xieite/data/str_join.hpp>

// HTML list generation
std::vector<std::string> list_items{"Item 1", "Item 2", "Item 3"};

// Join with HTML tags
auto html_items = xieite::str_join(list_items, "</li>\n<li>", "<li>", "</li>");
std::string html_list = "<ul>\n" + html_items + "\n</ul>";

std::cout << html_list << "\n";
/* Output:
<ul>
<li>Item 1</li>
<li>Item 2</li>
<li>Item 3</li>
</ul>
*/

// JSON array formatting
std::vector<std::string> json_values{"\"apple\"", "\"banana\"", "\"cherry\""};
auto json_array = xieite::str_join(json_values, ", ", "[", "]");
std::cout << json_array << "\n";  // ["apple", "banana", "cherry"]
```

### Partial Range Reversal
```cpp
#include <xieite/data/partial_reverse.hpp>

std::string mixed = "aAbBcCdDeEfF";
std::cout << "Original: " << mixed << "\n";

// Reverse only uppercase letters
xieite::partial_reverse(mixed, [](char c) {
    return std::isupper(c);
});

std::cout << "After reversing uppercase: " << mixed << "\n";
// Original: aAbBcCdDeEfF
// After:    aFbEcDdCeBfA (uppercase letters reversed)

// Reverse only digits
std::vector<char> alphanumeric{'a', '1', 'b', '2', 'c', '3', 'd', '4'};
xieite::partial_reverse(alphanumeric, [](char c) {
    return std::isdigit(c);
});

// Result: 'a', '4', 'b', '3', 'c', '2', 'd', '1' (digits reversed)
```

### Complex Partial Reversal
```cpp
#include <xieite/data/partial_reverse.hpp>

// Reverse negative numbers only
std::vector<int> numbers{5, -3, 2, -7, 1, -1, 8, -9, 3};
std::cout << "Original: ";
for (int n : numbers) std::cout << n << " ";

xieite::partial_reverse(numbers, [](int n) { return n < 0; });

std::cout << "\nAfter reversing negatives: ";
for (int n : numbers) std::cout << n << " ";
// Original: 5 -3 2 -7 1 -1 8 -9 3
// After:    5 -9 2 -1 1 -7 8 -3 3 (negatives reversed)
```

## Advanced Patterns

### Dynamic String Formatting
```cpp
class Formatter {
private:
    std::string delimiter_;
    std::string prefix_;
    std::string suffix_;

public:
    Formatter(std::string delim = "", std::string pre = "", std::string suf = "")
        : delimiter_(std::move(delim)), prefix_(std::move(pre)), suffix_(std::move(suf)) {}

    template<std::ranges::input_range Range>
    std::string format(Range&& range) const {
        return xieite::str_join(std::forward<Range>(range), delimiter_, prefix_, suffix_);
    }

    // Fluent interface
    Formatter& with_delimiter(std::string delim) { delimiter_ = std::move(delim); return *this; }
    Formatter& with_prefix(std::string pre) { prefix_ = std::move(pre); return *this; }
    Formatter& with_suffix(std::string suf) { suffix_ = std::move(suf); return *this; }
};

// Usage
std::vector<double> values{1.1, 2.2, 3.3};

auto csv_format = Formatter().with_delimiter(", ").format(values);
auto json_format = Formatter().with_delimiter(", ").with_prefix("[").with_suffix("]").format(values);
auto xml_format = Formatter().with_delimiter("</val><val>").with_prefix("<val>").with_suffix("</val>").format(values);

std::cout << "CSV: " << csv_format << "\n";
std::cout << "JSON: " << json_format << "\n";
std::cout << "XML: " << xml_format << "\n";
```

### Selective Range Operations
```cpp
template<typename Range, typename Predicate>
class SelectiveReverser {
    Range& range_;
    Predicate pred_;

public:
    SelectiveReverser(Range& range, Predicate pred)
        : range_(range), pred_(pred) {}

    void reverse_matching() {
        xieite::partial_reverse(range_, pred_);
    }

    void reverse_non_matching() {
        xieite::partial_reverse(range_, [this](const auto& x) {
            return !pred_(x);
        });
    }

    auto count_matching() const {
        return std::ranges::count_if(range_, pred_);
    }
};

// Usage
std::string text = "Hello World 123";
SelectiveReverser letter_reverser(text, [](char c) { return std::isalpha(c); });

std::cout << "Original: " << text << "\n";
std::cout << "Letters to reverse: " << letter_reverser.count_matching() << "\n";

letter_reverser.reverse_matching();
std::cout << "After reversing letters: " << text << "\n";
```

### Range Pipeline Processing
```cpp
class TextProcessor {
public:
    template<std::ranges::input_range Range>
    static std::string to_sentence(Range&& words) {
        return xieite::str_join(std::forward<Range>(words), " ") + ".";
    }

    template<std::ranges::input_range Range>
    static std::string to_bullet_list(Range&& items) {
        return xieite::str_join(std::forward<Range>(items), "\n• ", "• ");
    }

    template<std::ranges::input_range Range>
    static std::string to_code_array(Range&& values) {
        return xieite::str_join(std::forward<Range>(values), ", ", "{", "}");
    }

    template<std::ranges::bidirectional_range Range, typename Predicate>
    static void reverse_conditional(Range& range, Predicate&& pred) {
        xieite::partial_reverse(range, std::forward<Predicate>(pred));
    }
};

// Usage
std::vector<std::string> words{"The", "quick", "brown", "fox"};
std::vector<int> numbers{1, 2, 3, 4, 5};

std::cout << TextProcessor::to_sentence(words) << "\n";
std::cout << TextProcessor::to_bullet_list(words) << "\n";
std::cout << TextProcessor::to_code_array(numbers) << "\n";

// Conditional reversal
TextProcessor::reverse_conditional(numbers, [](int n) { return n % 2 == 0; });
// Even numbers are now reversed: 1, 4, 3, 2, 5
```

## Implementation Details

### String Joining Strategy
The `str_join` function (str_join.hpp:19-32) implements:
- Empty range handling (lines 23-25)
- Efficient string concatenation avoiding repeated allocations
- Multiple overloads for different parameter combinations (lines 34-76)
- Character and string view parameter normalization through `make_str_view`

### Partial Reversal Algorithm
The `partial_reverse` function (partial_reverse.hpp:14-28) uses:
- Bidirectional iterator requirements for efficient reversal
- Find operations to locate elements matching the predicate (lines 19-20)
- Iterator swapping with proper bounds checking (lines 21-27)
- Noexcept specification preservation based on predicate and range properties

### Template Constraints
Both utilities employ comprehensive template constraints:
- Range concept requirements (`input_range`, `bidirectional_range`)
- Character type constraints (`is_char`)
- Invocable concept validation for predicates
- Constructibility requirements for string types

## Performance Considerations

- **str_join**: O(n) time complexity with minimal string reallocations
- **partial_reverse**: O(n log n) worst case due to find operations, O(n) best case
- **Memory usage**: str_join creates result string, partial_reverse operates in-place
- **Exception safety**: Both functions provide strong exception safety guarantees

## Algorithm Complexity

| Function | Time Complexity | Space Complexity | Notes |
|----------|----------------|------------------|-------|
| `str_join` | O(n × m) | O(n × m) | n = elements, m = avg element size |
| `partial_reverse` | O(n) to O(n log n) | O(1) | Depends on predicate selectivity |

## Best Practices

1. **Use appropriate allocators** - Custom allocators supported for str_join
2. **Consider string size** - str_join pre-allocates when possible
3. **Optimize predicates** - Keep partial_reverse predicates simple and fast
4. **Choose suitable containers** - bidirectional_range required for partial_reverse

## Common Use Cases

### Data Export Formatting
```cpp
// CSV export
std::vector<std::vector<std::string>> table_data;
for (const auto& row : table_data) {
    std::cout << xieite::str_join(row, ",") << "\n";
}

// SQL IN clause generation
std::vector<int> ids{1, 2, 3, 4, 5};
std::string sql = "SELECT * FROM users WHERE id IN (" +
                  xieite::str_join(ids, ", ") + ");";
```

### Text Processing
```cpp
// Reverse punctuation in text while keeping letters in order
std::string text = "Hello, World! How are you?";
xieite::partial_reverse(text, [](char c) { return std::ispunct(c); });
// Result: "Hello? World! How are you,"
```

## See Also

- [Iterator Utilities](./iterators.md) - Iterator manipulation tools
- [Container Algorithms](./algorithms.md) - Specialized container operations
- [String Utilities](./strings.md) - String processing functions
- [Data Structures API Reference](../../reference/api/data.md)