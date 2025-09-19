# Utility Macros

## Overview

XIEITE's utility macros provide general-purpose preprocessor functionality including token generation, probing mechanisms, and macro composition helpers. These utilities form the foundation for more complex macro operations.

## Token Generation

### Comma Generation
Implementation: `include/xieite/pp/comma.hpp` (line 4)

```cpp
#define XIEITE_COMMA(...)  // Expands to comma: ,
```

### Parenthesis Generation
Implementation: `include/xieite/pp/paren.hpp` (lines 4-6)

```cpp
#define XIEITE_PAREN(...)        // Expands to: ()
#define XIEITE_PAREN_LEFT(...)   // Expands to: (
#define XIEITE_PAREN_RIGHT(...)  // Expands to: )
```

## Probing and Checking

### Probe Mechanism
Implementation: `include/xieite/pp/probe.hpp` (line 4)

```cpp
#define XIEITE_PROBE(x)  // Expands to: x, 1,
```

### Check Mechanism
Implementation: `include/xieite/pp/check.hpp` (line 6)

```cpp
#define XIEITE_CHECK(...)  // Returns second element or 0
```

## Struct Return Helper
Implementation: `include/xieite/pp/ret_struct.hpp` (lines 6-10)

```cpp
#define XIEITE_RET_STRUCT(...)  // Generate anonymous struct and return
```

## Macro Composition
Implementation: `include/xieite/pp/cm.hpp` (line 8)

```cpp
#define XIEITE_CM(...)  // Complex macro composition system
```

## Usage Examples

### Comma in Macro Arguments
```cpp
#include <xieite/pp/comma.hpp>

// Problem: Can't pass comma directly in macros
// MACRO(std::map<int, int>)  // Error: too many arguments

// Solution: Use XIEITE_COMMA
#define DECLARE_TYPE(type) using my_type = type;
DECLARE_TYPE(std::map<int XIEITE_COMMA() int>)
// Expands to: using my_type = std::map<int, int>;
```

### Conditional Parentheses
```cpp
#include <xieite/pp/paren.hpp>
#include <xieite/pp/if.hpp>

// Add parentheses conditionally
#define MAYBE_PAREN(cond, x) \
    XIEITE_IF(cond)(XIEITE_PAREN_LEFT() x XIEITE_PAREN_RIGHT())(x)

// Usage
MAYBE_PAREN(1, value)  // Expands to: (value)
MAYBE_PAREN(0, value)  // Expands to: value
```

### Probe-Based Detection
```cpp
#include <xieite/pp/probe.hpp>
#include <xieite/pp/check.hpp>

// Detect if macro is defined to specific value
#define IS_DEBUG_0 XIEITE_PROBE(~)
#define CHECK_DEBUG(x) XIEITE_CHECK(IS_DEBUG_##x)

#define DEBUG 0
int is_debug = CHECK_DEBUG(DEBUG);  // Returns 1

#define RELEASE 1
int is_release = CHECK_DEBUG(RELEASE);  // Returns 0
```

### Anonymous Struct Returns
```cpp
#include <xieite/pp/ret_struct.hpp>

// Return multiple values without naming struct
auto get_dimensions() {
    XIEITE_RET_STRUCT({
        int width;
        int height;
        int depth;
    }) { .width = 100, .height = 200, .depth = 50 };
}

// Usage
auto dims = get_dimensions();
std::cout << dims.width << "x" << dims.height << "x" << dims.depth;
```

## Advanced Patterns

### Variadic Comma Lists
```cpp
// Generate comma-separated lists
#define LIST_ITEM(x) x XIEITE_COMMA()
#define MAKE_LIST(...) __VA_ARGS__

int values[] = { MAKE_LIST(
    LIST_ITEM(1)
    LIST_ITEM(2)
    LIST_ITEM(3)
    4  // Last item without comma
)};
```

### Parenthesis Manipulation
```cpp
// Strip or add parentheses
#define STRIP_PARENS(...) __VA_ARGS__
#define ADD_PARENS(...) XIEITE_PAREN_LEFT() __VA_ARGS__ XIEITE_PAREN_RIGHT()

// Function-like macro calls
#define CALL(fn, ...) fn ADD_PARENS(__VA_ARGS__)
CALL(printf, "Hello %s", "World")
// Expands to: printf("Hello %s", "World")
```

### Probe-Based Overloading
```cpp
// Overload macros based on argument count
#define HAS_ARGS(...) XIEITE_CHECK(XIEITE_PROBE(__VA_ARGS__))

#define FUNC_0() "No arguments"
#define FUNC_1(a) "One argument"
#define FUNC(...) XIEITE_IF(HAS_ARGS(__VA_ARGS__))(FUNC_1(__VA_ARGS__))(FUNC_0())

FUNC()      // Expands to: "No arguments"
FUNC(42)    // Expands to: "One argument"
```

### Complex Return Values
```cpp
// Return computed struct
auto analyze_data(const std::vector<double>& data) {
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    double avg = sum / data.size();

    XIEITE_RET_STRUCT({
        double total;
        double average;
        size_t count;
        bool valid;
    }) {
        .total = sum,
        .average = avg,
        .count = data.size(),
        .valid = !data.empty()
    };
}
```

## Implementation Details

### Comma Generation
`XIEITE_COMMA` ignores all arguments and expands to a literal comma (comma.hpp:4). This allows passing commas in contexts where they would otherwise be interpreted as argument separators.

### Parenthesis Tokens
The parenthesis macros (paren.hpp:4-6) generate literal parenthesis tokens, enabling dynamic parenthesis insertion in macro expansions.

### Probe Mechanism
`XIEITE_PROBE` (probe.hpp:4) creates a detectable pattern by expanding to `x, 1,`. This pattern is used with `XIEITE_CHECK` to detect macro expansion results.

### Check Operation
`XIEITE_CHECK` (check.hpp:6) uses `XIEITE_AT_1` to extract the second element from its arguments, defaulting to 0 if not present. This enables boolean-like macro detection.

### Struct Generation
`XIEITE_RET_STRUCT` uses `__COUNTER__` (ret_struct.hpp:6) to generate unique struct names, preventing naming conflicts when used multiple times.

## Common Pitfalls

1. **Comma in templates** - Remember to use `XIEITE_COMMA()` for template arguments
2. **Parenthesis balance** - Ensure matching LEFT/RIGHT parentheses
3. **Probe patterns** - The probe pattern must match expected check format
4. **Struct lifetime** - Anonymous structs follow normal C++ lifetime rules

## Best Practices

1. **Use utilities for clarity** - Prefer named utilities over raw tokens
2. **Document probe patterns** - Complex probe usage needs clear documentation
3. **Test macro expansion** - Verify expansions with compiler preprocessing output
4. **Consistent naming** - Use clear names for generated structures

## Compatibility

- All utilities work with standard C/C++ preprocessors
- Anonymous structs require C++11 or later
- No compiler-specific extensions required
- Pure preprocessor operations (zero runtime cost)

## See Also

- [Token Operations](./tokens.md) - Token manipulation utilities
- [Boolean Operations](./boolean.md) - Logical operations
- [Conditional Compilation](./conditional.md) - Conditional macros
- [Preprocessor API Reference](../../reference/api/pp.md)