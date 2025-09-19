# Container Algorithms

## Overview

XIEITE provides specialized algorithms for container operations, focusing on consecutive sequence finding, tuple-based data structures, and range-aware searching. These algorithms extend standard library capabilities with more specific use cases and better performance characteristics.

## Consecutive Sequence Algorithms

### Find Most Consecutive Elements
Implementation: `include/xieite/data/find_most_consec_if.hpp` (lines 15-39)

```cpp
template<is_fwd_sized_range Range, is_invoc<bool(range_reference_t<Range>)> Fn>
constexpr subrange<iterator_t<Range>>
find_most_consec_if(Range& range, Fn&& condition);
```

Finds the longest consecutive subsequence of elements satisfying a condition.

### Find Most Consecutive Values
Implementation: `include/xieite/data/find_most_consec.hpp` (lines 15-18)

```cpp
template<is_fwd_sized_range Range, is_invoc<bool(T, T)> Fn = std::equal_to<>>
constexpr subrange<iterator_t<Range>>
find_most_consec(Range& range, const T& value, Fn&& comparator = {});
```

Finds the longest consecutive sequence of elements equal to a specific value.

## Advanced Data Structures

### Multi-Dimensional Map
Implementation: `include/xieite/data/tuple_map.hpp` (lines 17-53)

```cpp
template<template<typename, typename> typename Container,
         typename KeyTuple, typename Value>
struct tuple_map;
```

A recursive map structure using tuples as multi-dimensional keys.

## Usage Examples

### Finding Consecutive Sequences
```cpp
#include <xieite/data/find_most_consec_if.hpp>
#include <xieite/data/find_most_consec.hpp>

std::vector<int> numbers{1, 2, 2, 2, 3, 3, 1, 1, 1, 1, 5};

// Find longest sequence of even numbers
auto even_seq = xieite::find_most_consec_if(numbers, [](int x) {
    return x % 2 == 0;
});

std::cout << "Longest even sequence: ";
for (auto it = even_seq.begin(); it != even_seq.end(); ++it) {
    std::cout << *it << " ";
}
// Output: "2 2 2 "

// Find longest sequence of specific value
auto ones_seq = xieite::find_most_consec(numbers, 1);
std::cout << "\nLongest sequence of 1s: ";
for (auto it = ones_seq.begin(); it != ones_seq.end(); ++it) {
    std::cout << *it << " ";
}
// Output: "1 1 1 1 "
```

### Custom Predicate Sequences
```cpp
#include <xieite/data/find_most_consec_if.hpp>

std::string text = "AAAbbCCCCCddEE";

// Find longest sequence of uppercase letters
auto upper_seq = xieite::find_most_consec_if(text, [](char c) {
    return std::isupper(c);
});

std::string longest_upper(upper_seq.begin(), upper_seq.end());
std::cout << "Longest uppercase sequence: " << longest_upper << "\n";
// Output: "CCCCC"

// Find longest sequence with custom comparison
std::vector<double> values{1.0, 1.1, 1.05, 2.0, 2.1, 2.05, 2.01, 3.0};
auto close_seq = xieite::find_most_consec_if(values, [prev = 0.0](double x) mutable {
    bool close = std::abs(x - prev) < 0.2;
    prev = x;
    return close;
});
```

### Multi-Dimensional Mapping
```cpp
#include <xieite/data/tuple_map.hpp>

// 3D coordinate system map
using Point3D = std::tuple<int, int, int>;
xieite::tuple_map<std::map, Point3D, std::string> space_map;

// Insert values
space_map.insert(std::make_tuple(0, 0, 0), "Origin");
space_map.insert(std::make_tuple(1, 1, 1), "Corner");
space_map.insert(std::make_tuple(5, 3, 2), "Random Point");

// Access values
auto origin_key = std::make_tuple(0, 0, 0);
if (space_map.has(origin_key)) {
    std::cout << "At origin: " << space_map[origin_key] << "\n";
}

// 2D example - simpler usage
using Coordinate = std::tuple<int, int>;
xieite::tuple_map<std::unordered_map, Coordinate, char> grid;

grid.insert(std::make_tuple(10, 20), 'X');
grid.insert(std::make_tuple(5, 15), 'O');

auto pos = std::make_tuple(10, 20);
std::cout << "At (10,20): " << grid[pos] << "\n";  // 'X'
```

### Game Board Implementation
```cpp
// Chess-like board using tuple coordinates
class GameBoard {
private:
    using Position = std::tuple<int, int>;
    using Piece = std::string;
    xieite::tuple_map<std::map, Position, Piece> board_;

public:
    void place_piece(int row, int col, const Piece& piece) {
        board_.insert(std::make_tuple(row, col), piece);
    }

    bool has_piece_at(int row, int col) const {
        return board_.has(std::make_tuple(row, col));
    }

    Piece get_piece(int row, int col) const {
        auto pos = std::make_tuple(row, col);
        return board_.has(pos) ? board_[pos] : "Empty";
    }
};

// Usage
GameBoard chess;
chess.place_piece(0, 0, "White Rook");
chess.place_piece(7, 7, "Black Rook");

std::cout << "Piece at (0,0): " << chess.get_piece(0, 0) << "\n";
```

## Advanced Patterns

### Consecutive Analysis
```cpp
template<typename Range, typename Predicate>
struct ConsecutiveAnalyzer {
    Range& data_;
    Predicate pred_;

public:
    ConsecutiveAnalyzer(Range& data, Predicate pred)
        : data_(data), pred_(pred) {}

    auto find_all_sequences() {
        std::vector<std::ranges::subrange<std::ranges::iterator_t<Range>>> sequences;

        auto current_begin = std::ranges::begin(data_);
        auto end = std::ranges::end(data_);

        while (current_begin != end) {
            // Find start of next sequence
            current_begin = std::ranges::find_if(current_begin, end, pred_);
            if (current_begin == end) break;

            // Find end of current sequence
            auto current_end = std::ranges::find_if_not(current_begin, end, pred_);

            sequences.emplace_back(current_begin, current_end);
            current_begin = current_end;
        }

        return sequences;
    }

    auto find_longest_sequence() {
        return xieite::find_most_consec_if(data_, pred_);
    }
};

// Usage
std::string text = "AAAbbbCCCCddEEE";
ConsecutiveAnalyzer analyzer(text, [](char c) { return std::isupper(c); });

auto all_upper = analyzer.find_all_sequences();
std::cout << "Found " << all_upper.size() << " uppercase sequences\n";

auto longest = analyzer.find_longest_sequence();
std::cout << "Longest: " << std::string(longest.begin(), longest.end()) << "\n";
```

### Multi-Level Indexing
```cpp
// Document indexing system
class DocumentIndex {
private:
    using IndexKey = std::tuple<std::string, std::string, int>; // category, subcategory, page
    using DocInfo = std::string;
    xieite::tuple_map<std::map, IndexKey, DocInfo> index_;

public:
    void add_document(const std::string& category,
                      const std::string& subcategory,
                      int page,
                      const std::string& content) {
        index_.insert(std::make_tuple(category, subcategory, page), content);
    }

    std::string find_document(const std::string& category,
                              const std::string& subcategory,
                              int page) const {
        auto key = std::make_tuple(category, subcategory, page);
        return index_.has(key) ? index_[key] : "Not found";
    }

    bool document_exists(const std::string& category,
                         const std::string& subcategory,
                         int page) const {
        return index_.has(std::make_tuple(category, subcategory, page));
    }
};

// Usage
DocumentIndex docs;
docs.add_document("Programming", "C++", 1, "Introduction to C++");
docs.add_document("Programming", "C++", 2, "Advanced Templates");
docs.add_document("Math", "Calculus", 1, "Derivatives");

auto content = docs.find_document("Programming", "C++", 1);
std::cout << "Found: " << content << "\n";
```

## Implementation Details

### Consecutive Finding Algorithm
The `find_most_consec_if` implementation (find_most_consec_if.hpp:17-39) uses:
- Iterator meta-programming with `xieite::iters` (line 22)
- State tracking with previous/current flags (lines 21, 34)
- Distance calculation for length comparison (lines 30, 36)
- Subrange construction for result (lines 37-38)

### Tuple Map Structure
The `tuple_map` implementation (tuple_map.hpp:17-53) provides:
- Recursive template specialization for multi-dimensional keys
- Base case specialization for single-key tuples (lines 36-53)
- Perfect forwarding for key and value access (lines 26, 45)
- Container-agnostic design through template template parameters

### Performance Characteristics
- **find_most_consec_if**: O(n) time, O(1) space
- **tuple_map access**: O(log n) per dimension for std::map
- **Memory overhead**: Minimal for consecutive algorithms, recursive storage for tuple_map

## Algorithm Complexity

| Algorithm | Time Complexity | Space Complexity | Notes |
|-----------|----------------|------------------|-------|
| `find_most_consec_if` | O(n) | O(1) | Single pass with state tracking |
| `find_most_consec` | O(n) | O(1) | Delegates to predicate version |
| `tuple_map::operator[]` | O(log n × D) | O(1) | D = dimensions, log n per level |
| `tuple_map::insert` | O(log n × D) | O(1) | Creates intermediate maps as needed |

## Best Practices

1. **Use appropriate range types** - Forward iterators minimum for consecutive algorithms
2. **Consider noexcept specifications** - Algorithms preserve noexcept properties when possible
3. **Choose suitable containers** - std::map vs std::unordered_map for tuple_map based on key types
4. **Optimize predicates** - Keep predicate functions simple for consecutive finding

## Common Pitfalls

1. **Empty ranges** - Always check for empty input ranges
2. **Iterator invalidation** - Consecutive algorithms use iterators, be aware of container modifications
3. **Key tuple consistency** - Ensure tuple key types match across all tuple_map operations
4. **Memory usage** - tuple_map can create deep recursive structures

## See Also

- [Iterator Utilities](./iterators.md) - Iterator manipulation tools
- [Range Utilities](./ranges.md) - Range-based operations
- [String Utilities](./strings.md) - String processing algorithms
- [Data Structures API Reference](../../reference/api/data.md)