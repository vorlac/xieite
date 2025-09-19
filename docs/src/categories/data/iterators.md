# Iterator Utilities

## Overview

XIEITE provides iterator utilities for advanced range manipulation and iterator wrapping. These utilities offer meta-iteration capabilities and enhanced string view creation with automatic null-termination handling.

## Iterator Meta-Programming

### Iterator Wrapper
Implementation: `include/xieite/data/iters.hpp` (lines 10-93)

```cpp
template<std::ranges::range Range>
struct iters {
    Range& value;

    // Iterator access methods
    constexpr auto begin();    // Returns wrapped iterator
    constexpr auto cbegin();   // Const iterator
    constexpr auto rbegin();   // Reverse iterator
    constexpr auto end();      // End iterator
    // ... all standard iterator methods
};
```

The `iters` wrapper allows iteration over iterators themselves rather than their values.

### Wrapped Iterator Interface
Implementation: `include/xieite/data/iters.hpp` (lines 14-58)

```cpp
template<typename Iter>
struct iter {
    Iter value;  // The actual iterator

    auto& operator*();           // Returns the iterator itself
    auto operator+(difference_t); // Iterator arithmetic
    auto operator++();           // Increment operations
    bool operator==(const iter&); // Comparison operations
    // ... full iterator interface
};
```

## String View Creation

### Enhanced String View Construction
Implementation: `include/xieite/data/make_str_view.hpp` (lines 12-31)

```cpp
template<is_char Char>
constexpr auto make_str_view(basic_string_view<Char>);     // Pass-through

template<is_char Char, typename Traits>
constexpr auto make_str_view(const basic_string<Char>&);  // From string

template<is_char Char, typename Traits>
constexpr auto make_str_view(const Char*, size_t);        // From C-string with length

template<is_char Char, typename Traits, size_t N>
constexpr auto make_str_view(const Char(&)[N]);           // From array

template<is_char Char, typename Traits>
constexpr auto make_str_view(Char&&);                     // From single character
```

## Usage Examples

### Iterator Meta-Iteration
```cpp
#include <xieite/data/iters.hpp>

std::vector<int> data{1, 2, 3, 4, 5};
xieite::iters iter_wrapper{data};

// Iterate over iterators themselves
for (auto it : iter_wrapper) {
    std::cout << "Iterator points to: " << *it << "\n";
    std::cout << "Iterator address: " << &it << "\n";

    // Can manipulate the iterator
    if (it != data.end()) {
        ++it;  // Move to next position
        if (it != data.end()) {
            std::cout << "Next value: " << *it << "\n";
        }
    }
}
```

### Iterator Arithmetic on Meta-Iterators
```cpp
#include <xieite/data/iters.hpp>

std::array<double, 10> values{};
std::iota(values.begin(), values.end(), 1.0);

xieite::iters iter_range{values};

auto meta_iter = iter_range.begin();
auto end_iter = iter_range.end();

// Arithmetic on wrapped iterators
while (meta_iter != end_iter) {
    auto current_pos = *meta_iter;  // Get the actual iterator

    std::cout << "Value: " << *current_pos << "\n";

    // Skip every other element
    meta_iter += 2;
}
```

### Enhanced String View Creation
```cpp
#include <xieite/data/make_str_view.hpp>

// From various sources
std::string str = "Hello, World!";
auto view1 = xieite::make_str_view(str);

// From C-string with automatic null handling
const char* cstr = "C-style string";
auto view2 = xieite::make_str_view(cstr, strlen(cstr));

// From single character
auto view3 = xieite::make_str_view('X');

// From array with size deduction
char array[] = "Array string";
auto view4 = xieite::make_str_view(array);

// All views are std::string_view compatible
void process_text(std::string_view text) {
    std::cout << "Processing: " << text << "\n";
}

process_text(view1);
process_text(view2);
process_text(view3);  // Single character as string_view
process_text(view4);
```

### Null-Termination Handling
```cpp
// The make_str_view function handles null-termination automatically
const char buffer[10] = "Hello";  // Null-terminated
auto safe_view = xieite::make_str_view(buffer, 10);

// Length is adjusted to exclude trailing nulls (make_str_view.hpp:22)
std::cout << "Length: " << safe_view.length() << "\n";  // 5, not 10
std::cout << "Content: '" << safe_view << "'\n";        // "Hello"
```

## Advanced Patterns

### Iterator Range Analysis
```cpp
template<std::ranges::range Range>
void analyze_iterators(Range& range) {
    xieite::iters meta_range{range};

    auto begin_iter = meta_range.begin();
    auto end_iter = meta_range.end();

    std::cout << "Range analysis:\n";
    std::cout << "Begin iterator: " << &(*begin_iter) << "\n";
    std::cout << "End iterator: " << &(*end_iter) << "\n";

    // Calculate distance using meta-iterators
    auto distance = std::distance(begin_iter, end_iter);
    std::cout << "Iterator count: " << distance << "\n";
}

// Usage
std::list<std::string> words{"one", "two", "three"};
analyze_iterators(words);
```

### Custom Iterator Manipulation
```cpp
template<typename Container>
auto find_middle_iterators(Container& container) {
    xieite::iters meta{container};

    auto begin_meta = meta.begin();
    auto end_meta = meta.end();

    // Find middle using meta-iterators
    auto distance = std::distance(begin_meta, end_meta);
    auto middle_meta = begin_meta + distance / 2;

    // Return the actual iterator
    return *middle_meta;
}

// Usage
std::vector<int> numbers{10, 20, 30, 40, 50};
auto mid_iter = find_middle_iterators(numbers);
std::cout << "Middle element: " << *mid_iter << "\n";  // 30
```

### String View Factory Pattern
```cpp
class TextProcessor {
private:
    template<typename Source>
    static auto to_view(Source&& src) {
        return xieite::make_str_view(std::forward<Source>(src));
    }

public:
    template<typename... Sources>
    void process_all(Sources&&... sources) {
        (process_single(to_view(std::forward<Sources>(sources))), ...);
    }

private:
    void process_single(std::string_view text) {
        std::cout << "Processing: " << text << " (length: " << text.size() << ")\n";
    }
};

// Usage - all converted to string_view automatically
TextProcessor processor;
processor.process_all(
    std::string("String object"),
    "C-string literal",
    'X',  // Single char
    std::string_view("Existing view")
);
```

## Implementation Details

### Iterator Wrapper Design
The `iters` class (iters.hpp:10-93) provides:
- Range-based interface for meta-iteration
- Wrapped iterators that expose the iterator itself as the value
- Full iterator arithmetic operations (iters.hpp:35-57)
- Support for all iterator categories (forward, bidirectional, random access)

### Meta-Iterator Operations
The inner `iter` class (iters.hpp:14-58) implements:
- Dereference returns the wrapped iterator (iters.hpp:19-21)
- Comparison operations between wrapped iterators (iters.hpp:23-33)
- Arithmetic operations forwarded to the wrapped iterator (iters.hpp:35-57)
- Pre/post increment/decrement with proper return types (iters.hpp:41-57)

### String View Construction Strategy
The `make_str_view` function (make_str_view.hpp:21-22) handles:
- Automatic null-termination detection and length adjustment
- Template deduction for character types and traits
- Support for various string sources (string, C-string, array, single char)
- Compile-time optimization through constexpr

## Performance Considerations

- Meta-iteration has minimal overhead (wrapper around existing iterators)
- String view creation is compile-time optimized with constexpr
- No dynamic allocation or copying of underlying data
- Iterator arithmetic operations inline to wrapped iterator operations

## Best Practices

1. **Use meta-iteration for algorithm development** - When you need to work with iterator positions
2. **Prefer make_str_view for safe string handling** - Automatic null-termination handling
3. **Leverage template deduction** - Let the compiler deduce character types and traits
4. **Consider iterator categories** - Meta-iterators preserve underlying iterator properties

## Common Use Cases

### Algorithm Development
```cpp
// Find all local maxima positions
template<std::ranges::range Range>
auto find_peaks(Range& data) {
    std::vector<typename Range::iterator> peaks;
    xieite::iters meta{data};

    auto prev = meta.begin();
    auto curr = prev + 1;
    auto next = curr + 1;
    auto end = meta.end();

    while (next != end) {
        if (*(*curr) > *(*prev) && *(*curr) > *(*next)) {
            peaks.push_back(*curr);  // Store the iterator
        }
        ++prev; ++curr; ++next;
    }

    return peaks;
}
```

### Text Processing Pipeline
```cpp
class FlexibleTextProcessor {
public:
    template<typename Source>
    auto normalize(Source&& source) {
        auto view = xieite::make_str_view(std::forward<Source>(source));
        // Process the normalized string_view
        return std::string{view};  // Convert back if needed
    }
};
```

## See Also

- [Container Algorithms](./algorithms.md) - Algorithm utilities for containers
- [Range Utilities](./ranges.md) - Range manipulation tools
- [String Utilities](./strings.md) - String processing functions
- [Data Structures API Reference](../../reference/api/data.md)