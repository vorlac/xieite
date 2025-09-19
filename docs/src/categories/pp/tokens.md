# Token Operations

## Overview

XIEITE's token operation macros provide fundamental building blocks for preprocessor metaprogramming. These utilities enable token concatenation, stringification, expansion control, and other essential token manipulations.

## Token Concatenation

### Basic Concatenation
Implementation: `include/xieite/pp/cat.hpp` (lines 4-7)

```cpp
#define XIEITE_CAT(x, ...)   // Concatenate tokens with indirection
#define XIEITE_PCAT(x, ...)  // Direct token pasting: x##__VA_ARGS__
#define XIEITE_CATR(x, ...)  // Reverse concatenation with indirection
#define XIEITE_PCATR(x, ...) // Direct reverse pasting: __VA_ARGS__##x
```

### Partial Concatenation
Implementation: `include/xieite/pp/cat.hpp` (lines 8-9)

```cpp
#define XIEITE_CAT_A(x)  // Start concatenation: x##
#define XIEITE_CAT_B(x)  // Start reverse concat: ##x
```

## String Conversion

### Stringification
Implementation: `include/xieite/pp/str.hpp` (lines 4-5)

```cpp
#define XIEITE_STR(...)   // Convert to string with indirection
#define XIEITE_PSTR(...)  // Direct stringification: #__VA_ARGS__
```

## Token Control

### Token Consumption
Implementation: `include/xieite/pp/eat.hpp` (line 4)

```cpp
#define XIEITE_EAT(...)  // Discard all arguments
```

### Token Expansion
Implementation: `include/xieite/pp/scan.hpp` (line 4)

```cpp
#define XIEITE_SCAN(...)  // Force expansion: __VA_ARGS__
```

### Deferred Expansion
Implementation: `include/xieite/pp/defer.hpp` (line 6)

```cpp
#define XIEITE_DEFER(...)  // Delay expansion by one scan
```

### Obstructed Expansion
Implementation: `include/xieite/pp/obstruct.hpp` (line 7)

```cpp
#define XIEITE_OBSTRUCT(...)  // Prevent immediate expansion
```

## Usage Examples

### Token Concatenation
```cpp
#include <xieite/pp/cat.hpp>

// Basic concatenation
#define PREFIX my_
#define MAKE_NAME(suffix) XIEITE_CAT(PREFIX, suffix)

MAKE_NAME(function)  // Expands to: my_function

// Direct concatenation
#define VERSION 2
#define API_V XIEITE_PCAT(api_v, VERSION)
// API_V expands to: api_v2

// Reverse concatenation
#define SUFFIX _impl
#define IMPL(name) XIEITE_CATR(SUFFIX, name)
IMPL(process)  // Expands to: process_impl
```

### String Conversion
```cpp
#include <xieite/pp/str.hpp>

// Convert macro to string
#define VERSION_NUM 1.2.3
const char* version = XIEITE_STR(VERSION_NUM);
// version = "1.2.3"

// Direct stringification
#define ERROR_MSG(code) XIEITE_PSTR(Error: code)
const char* msg = ERROR_MSG(404);
// msg = "Error: code" (not expanded)

// With expansion
#define CODE 404
const char* expanded = XIEITE_STR(CODE);
// expanded = "404"
```

### Token Manipulation
```cpp
#include <xieite/pp/eat.hpp>
#include <xieite/pp/scan.hpp>

// Conditional inclusion
#define DEBUG 1
#define LOG(msg) XIEITE_IF(DEBUG)(printf(msg))(XIEITE_EAT(msg))

// Force expansion
#define EXPAND_TWICE(x) XIEITE_SCAN(XIEITE_SCAN(x))

// Selective consumption
#define FIRST(a, ...) a
#define REST(a, ...) __VA_ARGS__
#define SKIP_FIRST(...) XIEITE_EAT(FIRST(__VA_ARGS__)) REST(__VA_ARGS__)
```

### Deferred Expansion
```cpp
#include <xieite/pp/defer.hpp>
#include <xieite/pp/obstruct.hpp>

// Defer macro expansion
#define LATER(x) XIEITE_DEFER(x)()

// Multiple levels of deferral
#define LEVEL_1() "immediate"
#define LEVEL_2() XIEITE_DEFER(LEVEL_1)()
#define LEVEL_3() XIEITE_OBSTRUCT(LEVEL_1)()

// Recursive macro helpers
#define RECURSE(...) XIEITE_OBSTRUCT(RECURSE_I)()(__VA_ARGS__)
#define RECURSE_I() RECURSE
```

## Advanced Patterns

### Token Pasting with Variable Arguments
```cpp
// Build identifier lists
#define MAKE_VARS(prefix, ...) \
    XIEITE_CAT(prefix, 1), \
    XIEITE_CAT(prefix, 2), \
    XIEITE_CAT(prefix, 3)

int MAKE_VARS(var_);  // int var_1, var_2, var_3;

// Dynamic prefixing
#define NAMESPACE(ns, name) XIEITE_CAT(ns, XIEITE_CAT(_, name))
#define MY_NS foo
void NAMESPACE(MY_NS, func)();  // void foo_func();
```

### Stringification with Formatting
```cpp
// Create formatted strings
#define MAKE_ERROR(code, msg) \
    "[" XIEITE_STR(code) "] " msg

const char* error = MAKE_ERROR(E001, "File not found");
// error = "[E001] File not found"

// Version string generation
#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define VERSION_STR \
    XIEITE_STR(VERSION_MAJOR) "." \
    XIEITE_STR(VERSION_MINOR)
// VERSION_STR = "1.0"
```

### Expansion Control in Recursion
```cpp
// Controlled recursive expansion
#define REPEAT_0(x)
#define REPEAT_1(x) x
#define REPEAT_2(x) x XIEITE_DEFER(REPEAT_1)(x)
#define REPEAT_3(x) x XIEITE_DEFER(REPEAT_2)(x)

#define REPEAT(n, x) XIEITE_CAT(REPEAT_, n)(x)

// Usage
REPEAT(3, A)  // Expands to: A A A
```

## Implementation Details

### Indirection Levels
- `XIEITE_CAT` uses `XIEITE_PCAT` for proper macro expansion (cat.hpp:4)
- `XIEITE_STR` uses `XIEITE_PSTR` to expand arguments first (str.hpp:4)
- This ensures macros are expanded before concatenation/stringification

### Expansion Timing
- `XIEITE_SCAN` forces immediate expansion (scan.hpp:4)
- `XIEITE_DEFER` delays by appending `XIEITE_EAT()` (defer.hpp:6)
- `XIEITE_OBSTRUCT` uses double deferral (obstruct.hpp:7)

### Token Consumption Strategy
- `XIEITE_EAT` expands to nothing, consuming all arguments (eat.hpp:4)
- Used in conditional compilation to discard unwanted branches

## Common Pitfalls

1. **Missing indirection** - Direct pasting may not expand macros
2. **Over-expansion** - Too many scan passes can cause errors
3. **Token validity** - Concatenation must produce valid tokens
4. **Stringification timing** - Arguments expanded before stringification with `XIEITE_STR`

## Best Practices

1. **Use indirection for expansion** - `XIEITE_CAT` over `XIEITE_PCAT` when macros involved
2. **Document expansion levels** - Clear comments for deferred expansions
3. **Test token validity** - Ensure concatenation produces valid identifiers
4. **Consistent naming** - Clear prefixes/suffixes for generated names

## Compatibility

- Works with all C/C++ preprocessors
- No compiler-specific extensions required
- Compatible with C++98 through C++23
- Pure preprocessor operations (no runtime cost)

## See Also

- [Boolean Operations](./boolean.md) - Logical operations on tokens
- [Conditional Compilation](./conditional.md) - Using tokens in conditionals
- [String Manipulation](./strings.md) - String-specific operations
- [Preprocessor API Reference](../../reference/api/pp.md)