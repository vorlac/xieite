# XIEITE Data Module

## Overview

The XIEITE data module provides a comprehensive collection of data structures, string manipulation utilities, and range algorithms. With 65 headers, it offers both compile-time optimized containers and runtime-efficient utilities that extend and enhance the C++ standard library.

## Module Organization

### Fixed-Size Containers (12 headers)
- **[Fixed Containers](fixed_containers.md)** - Compile-time sized containers with STL compatibility
- Core types: `fixed_array`, `fixed_str`, `fixed_map`, `fixed_set`
- Multi-dimensional: `fixed_md_container`, `md_container`
- Tuple-based: `tuple_map`, `tuple_set`
- Smart pointers: `ptr`, `ref`

### String Manipulation (30 headers)
- **[String Utilities](string_utilities.md)** - Comprehensive string processing functions
- Splitting/Joining: `str_split`, `str_join`
- Extraction: `str_before`, `str_after`, `str_between`
- Transformation: `str_replace`, `tolower`, `toupper`, `str_repeat`
- Trimming/Padding: `trim`, `pad`, `str_truncate`
- Quoting: `quote`, `unquote`
- Character classification: `isalpha`, `isdigit`, `isspace`, etc.

### Iterator and Range Utilities (23 headers)
- **[Iterator Utilities](iterator_utilities.md)** - Advanced range algorithms and iterator wrappers
- Iterator wrapper: `iters`
- Search algorithms: `find_occur`, `find_occur_if`, `find_most_consec`
- Range manipulation: `partial_reverse`, `rotated`
- Range extraction: `before`, `after`, `between`
- Factory functions: `make_array`, `make_ptr`, `make_sparse_array`

## Key Features

### Compile-Time Optimization
The data module emphasizes compile-time operations where possible:
- Fixed containers use template parameters for size
- String operations are constexpr-enabled
- Dual-mode containers optimize differently for compile-time vs runtime

### Type Safety
Strong type constraints using C++20 concepts:
- `xieite::is_char` for character operations
- Range concepts for algorithm constraints
- SFINAE-friendly design throughout

### Memory Efficiency
- Fixed containers avoid heap allocation
- String views prevent unnecessary copying
- Sparse arrays optimize memory for large key spaces

### STL Compatibility
All containers provide standard interfaces:
- Iterator support (begin/end)
- Standard typedefs (value_type, size_type, etc.)
- Range-based for loop support
- Standard algorithm compatibility

## Container Comparison

| Container | Size | Allocation | Compile-Time | Use Case |
|-----------|------|------------|--------------|----------|
| `fixed_array<T,N>` | Fixed | Stack | Yes | Known size arrays |
| `fixed_str<C,N>` | Fixed | Stack | Yes | Compile-time strings |
| `fixed_map<K,V,N>` | Fixed | Stack/Static | Dual-mode | Small lookup tables |
| `fixed_set<T,N>` | Fixed | Stack/Static | Dual-mode | Small membership sets |
| `tuple_map<C,K,V>` | Dynamic | Heap | No | Multi-key associations |
| `ptr<T>` | Single | Heap | No | RAII resource management |

## String Processing Pipeline

```cpp
// Example: Process CSV data
std::string csv_line = "  John Doe , 42 , Engineer  ";

auto processed = xieite::str_split(
    xieite::trim(csv_line),    // Remove outer whitespace
    ","                         // Split on comma
);

// Trim each field
std::vector<std::string> fields;
for (auto field : processed) {
    fields.push_back(std::string(xieite::trim(field)));
}
// Result: {"John Doe", "42", "Engineer"}
```

## Advanced Usage Examples

### Compile-Time Configuration
```cpp
// Define compile-time configuration
constexpr xieite::fixed_map<int, const char*, 5> config{{
    {1, "Development"},
    {2, "Testing"},
    {3, "Staging"},
    {4, "Production"},
    {5, "Maintenance"}
}};

// Use at compile-time
constexpr auto env = config.get(3);  // "Staging"

// Runtime with optimization
auto user_env = config.get(user_input);  // Uses hash map
```

### Multi-Dimensional Access
```cpp
// 3D voxel grid using tuple_map
xieite::tuple_map<std::map, std::tuple<int, int, int>, VoxelData> world;

// Natural syntax for 3D coordinates
world[{10, 20, 30}] = VoxelData{...};

if (world.has({x, y, z})) {
    auto& voxel = world[{x, y, z}];
    render_voxel(voxel);
}
```

### Iterator Position Tracking
```cpp
// Find all occurrences with positions
std::vector<int> data{1, 2, 3, 2, 5, 2, 7};
std::vector<size_t> positions;

xieite::iters wrapper{data};
for (auto iter : wrapper) {
    if (*iter == 2) {
        positions.push_back(std::distance(data.begin(), iter));
    }
}
// positions: {1, 3, 5}
```

## Design Patterns

### Dual-Mode Optimization
Fixed containers use `if consteval` to optimize differently:
```cpp
if consteval {
    // Compile-time: Linear search
    for (const auto& [k, v] : array) {
        if (k == key) return v;
    }
} else {
    // Runtime: Hash map lookup
    return cached_map[key];
}
```

### Perfect Forwarding
Extensive use of `XIEITE_FWD` macro:
```cpp
template<typename T>
auto process(T&& value) {
    return internal_process(XIEITE_FWD(value));
}
```

### Range Composition
Functions compose naturally:
```cpp
auto result = xieite::trim(
    xieite::str_replace(
        xieite::str_between(input, "<", ">"),
        "&amp;", "&"
    )
);
```

## Performance Characteristics

### Compile-Time Performance
- Fixed containers: Zero runtime initialization
- Constexpr strings: Compile-time processing
- Template unrolling: Loop optimization

### Runtime Performance
- String views: O(1) substring operations
- Hash caching: One-time initialization cost
- Range algorithms: Single-pass where possible

### Memory Usage
- Fixed containers: Predictable stack usage
- String utilities: Minimal allocations
- Sparse arrays: O(2^bits) space for key type

## Integration with Other Modules

- **trait/**: Uses type traits for concept definitions
- **pp/**: Leverages arrow macros for concise implementations
- **meta/**: Template metaprogramming for container construction
- **math/**: Character utilities use mathematical operations

## Best Practices

1. **Choose the right container**:
   - Use fixed containers for compile-time known sizes
   - Use tuple containers for composite keys
   - Use standard containers when size is dynamic

2. **Leverage string views**:
   - Process without copying when possible
   - Chain operations efficiently
   - Be aware of lifetime issues

3. **Optimize with dual-mode**:
   - Fixed containers automatically optimize
   - No code changes needed
   - Best of both compile-time and runtime

4. **Use appropriate algorithms**:
   - `find_occur` for nth occurrence
   - `find_most_consec` for sequences
   - `partial_reverse` for selective operations

## Module Statistics

- **Total Headers**: 65
- **Container Types**: 10+
- **String Functions**: 30+
- **Range Algorithms**: 15+
- **Character Classification**: 13
- **Compile-Time Functions**: ~90%

## Future Enhancements

Potential additions to the data module:
- Additional fixed container types
- Unicode string support
- More range algorithms
- Concurrent containers
- Memory pool allocators

---

*Return to [XIEITE Documentation Home](../../index.md)*