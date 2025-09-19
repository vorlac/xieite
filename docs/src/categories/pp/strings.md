# String Manipulation

## Overview

XIEITE's preprocessor string manipulation provides utilities for stringification, character encoding detection, and struct literal generation. These macros enable compile-time string operations and encoding awareness.

## String Operations

### Basic Stringification
Implementation: `include/xieite/pp/str.hpp` (lines 4-5)

```cpp
#define XIEITE_STR(...)   // Stringification with macro expansion
#define XIEITE_PSTR(...)  // Direct stringification without expansion
```

### Return Struct Generation
Implementation: `include/xieite/pp/ret_struct.hpp` (lines 6-10)

```cpp
#define XIEITE_RET_STRUCT(...)  // Generate and return anonymous struct
```

## Character Encoding Detection

### Encoding Constants
Implementation: `include/xieite/pp/encoding.hpp` (lines 4-6, 8-21)

```cpp
#define XIEITE_ENCODING_ASCII   // 1 if ASCII, 0 otherwise
#define XIEITE_ENCODING_EBCDIC  // 1 if EBCDIC, 0 otherwise
#define XIEITE_ENCODING_CP1036  // 1 if Code Page 1036, 0 otherwise
```

## Usage Examples

### Stringification
```cpp
#include <xieite/pp/str.hpp>

// Basic stringification
#define VERSION 123
const char* version_str = XIEITE_STR(VERSION);  // "123"

// Direct stringification (no expansion)
const char* literal = XIEITE_PSTR(VERSION);     // "VERSION"

// Multi-token stringification
#define ERROR_CODE 404
#define ERROR_MSG File not found
const char* error = XIEITE_STR(ERROR_CODE: ERROR_MSG);
// Result: "404: File not found"
```

### Anonymous Struct Returns
```cpp
#include <xieite/pp/ret_struct.hpp>

// Return multiple values without named struct
auto get_point() {
    XIEITE_RET_STRUCT({
        int x;
        int y;
    }) { .x = 10, .y = 20 };
}

// Usage
auto point = get_point();
std::cout << point.x << ", " << point.y;  // 10, 20
```

### Encoding Detection
```cpp
#include <xieite/pp/encoding.hpp>

void handle_text() {
    #if XIEITE_ENCODING_ASCII
        // ASCII-specific handling
        process_ascii_text();
    #elif XIEITE_ENCODING_EBCDIC
        // EBCDIC-specific handling
        process_ebcdic_text();
    #elif XIEITE_ENCODING_CP1036
        // Code Page 1036 handling
        process_cp1036_text();
    #else
        // Unknown encoding
        #error "Unsupported character encoding"
    #endif
}
```

## Implementation Details

### Stringification Process
The stringification macros use two levels of indirection:
- `XIEITE_STR` calls `XIEITE_PSTR` after macro expansion (str.hpp:4)
- `XIEITE_PSTR` performs direct stringification with `#` operator (str.hpp:5)
- This ensures macros are expanded before conversion to strings

### Anonymous Struct Generation
XIEITE_RET_STRUCT creates unique struct names using:
- `__COUNTER__` for unique identifiers (ret_struct.hpp:6)
- `DETAIL_XIEITE_struct_` prefix to avoid collisions
- Immediate return of struct instance (ret_struct.hpp:10)

### Encoding Detection Method
The encoding detection uses character literal comparisons:
- ASCII: Checks standard ASCII values (encoding.hpp:8)
- EBCDIC: Checks EBCDIC character mappings (encoding.hpp:13)
- CP1036: Checks Code Page 1036 mappings (encoding.hpp:18)
- Detection happens at compile-time via preprocessor conditions

## Advanced Patterns

### Macro Name to String
```cpp
// Convert macro names to strings
#define MAKE_NAME_STR(name) XIEITE_STR(name)

#define MY_CONSTANT 42
const char* constant_name = MAKE_NAME_STR(MY_CONSTANT);  // "42"

// Get literal macro name
#define GET_MACRO_NAME(m) XIEITE_PSTR(m)
const char* name = GET_MACRO_NAME(MY_CONSTANT);  // "MY_CONSTANT"
```

### Multiple Return Values
```cpp
// Complex return structures
auto calculate_stats(const std::vector<int>& data) {
    XIEITE_RET_STRUCT({
        double mean;
        double median;
        double stddev;
        int min;
        int max;
    }) {
        .mean = calc_mean(data),
        .median = calc_median(data),
        .stddev = calc_stddev(data),
        .min = *std::min_element(data.begin(), data.end()),
        .max = *std::max_element(data.begin(), data.end())
    };
}
```

### Encoding-Safe String Literals
```cpp
#if XIEITE_ENCODING_ASCII
    #define STRING_LITERAL(s) u8##s
#elif XIEITE_ENCODING_EBCDIC
    #define STRING_LITERAL(s) convert_from_ebcdic(s)
#else
    #define STRING_LITERAL(s) s
#endif

const auto greeting = STRING_LITERAL("Hello, World!");
```

## Common Patterns

### Debug String Generation
```cpp
// Generate debug strings
#define DEBUG_VAR(var) \
    XIEITE_STR(var) " = " XIEITE_STR(var##_value)

int count_value = 42;
const char* debug = DEBUG_VAR(count);  // "count = count_value"
```

### Compile-Time String Tables
```cpp
// Generate string arrays
#define ENUM_TO_STRING(e) XIEITE_STR(e),

enum Color { RED, GREEN, BLUE };

const char* color_names[] = {
    ENUM_TO_STRING(RED)     // "RED",
    ENUM_TO_STRING(GREEN)   // "GREEN",
    ENUM_TO_STRING(BLUE)    // "BLUE"
};
```

## Best Practices

1. **Use XIEITE_STR for expansion** - When you want macro values
2. **Use XIEITE_PSTR for literals** - When you want macro names
3. **Check encoding when needed** - For portable text handling
4. **Document struct returns** - Anonymous structs need clear documentation

## Limitations

1. **No string concatenation** - Preprocessor can't manipulate string contents
2. **No substring operations** - Can't extract parts of strings
3. **Limited encoding support** - Only three encodings detected
4. **Anonymous struct limitations** - No type deduction in some contexts

## Compatibility

- String operations work with all C/C++ standards
- Anonymous struct returns require C++14 or later
- Encoding detection works at compile-time
- Platform-independent (encoding-dependent)

## See Also

- [Token Operations](./tokens.md) - General token manipulation
- [Boolean Operations](./boolean.md) - Conditional string generation
- [Utilities](./utilities.md) - General preprocessor utilities
- [Preprocessor API Reference](../../reference/api/pp.md)