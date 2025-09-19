# Boolean Operations

## Overview

XIEITE's preprocessor boolean operations provide compile-time logical operations for macro metaprogramming. These macros enable conditional compilation and decision-making within the preprocessor.

## Core Boolean Macros

### Boolean Conversion
Implementation: `include/xieite/pp/bool.hpp` (line 7)

```cpp
#define XIEITE_BOOL(x)
// Converts any value to 0 or 1
// Returns 1 for non-zero values, 0 for zero
```

### Logical NOT
Implementation: `include/xieite/pp/not.hpp` (line 8)

```cpp
#define XIEITE_NOT(x)
// Returns 1 if x is 0, otherwise returns 0
```

### Complement Operation
Implementation: `include/xieite/pp/compl.hpp` (line 6)

```cpp
#define XIEITE_COMPL(b)
// Flips boolean value: 0 -> 1, 1 -> 0
```

## Logical Operations

### AND Operation
Implementation: `include/xieite/pp/and.hpp` (line 7)

```cpp
#define XIEITE_AND(...)
// Returns 1 if all arguments are non-zero, 0 otherwise
```

### OR Operation
Implementation: `include/xieite/pp/or.hpp` (line 7)

```cpp
#define XIEITE_OR(...)
// Returns 1 if any argument is non-zero, 0 otherwise
```

## Conditional Execution

### IF Statement
Implementation: `include/xieite/pp/if.hpp` (line 9)

```cpp
#define XIEITE_IF(x)
// If x is non-zero, expands the first argument after invocation
// If x is zero, expands the second argument after invocation
```

### IIF (Immediate IF)
Implementation: `include/xieite/pp/if.hpp` (line 10)

```cpp
#define XIEITE_IIF(b)
// Direct boolean branching without conversion
// b must be exactly 0 or 1
```

## Usage Examples

### Basic Boolean Operations
```cpp
#include <xieite/pp/bool.hpp>
#include <xieite/pp/not.hpp>

// Convert to boolean
#define VALUE 42
#define IS_TRUE XIEITE_BOOL(VALUE)  // Expands to 1

#define ZERO 0
#define IS_FALSE XIEITE_BOOL(ZERO)   // Expands to 0

// Logical NOT
#define INVERTED XIEITE_NOT(0)        // Expands to 1
#define NEGATED XIEITE_NOT(1)         // Expands to 0
```

### Logical Combinations
```cpp
#include <xieite/pp/and.hpp>
#include <xieite/pp/or.hpp>

// AND operation
#define BOTH XIEITE_AND(1, 1)         // Expands to 1
#define MIXED XIEITE_AND(1, 0)        // Expands to 0

// OR operation
#define EITHER XIEITE_OR(0, 1)        // Expands to 1
#define NEITHER XIEITE_OR(0, 0)       // Expands to 0
```

### Conditional Compilation
```cpp
#include <xieite/pp/if.hpp>

// Define debug mode
#define DEBUG_MODE 1

// Conditional macro expansion
#define LOG(msg) XIEITE_IF(DEBUG_MODE)(printf(msg))(/* nothing */)

// Usage
LOG("Debug message");  // Expands to printf("Debug message") if DEBUG_MODE is 1
```

### Feature Flags
```cpp
#include <xieite/pp/if.hpp>
#include <xieite/pp/and.hpp>

#define HAS_FEATURE_A 1
#define HAS_FEATURE_B 0
#define HAS_FEATURE_C 1

// Check multiple features
#define ALL_FEATURES XIEITE_AND(HAS_FEATURE_A, HAS_FEATURE_B, HAS_FEATURE_C)

// Conditional compilation based on features
#define INIT_FEATURES() \
    XIEITE_IF(HAS_FEATURE_A)(init_feature_a())() \
    XIEITE_IF(HAS_FEATURE_B)(init_feature_b())() \
    XIEITE_IF(HAS_FEATURE_C)(init_feature_c())()
```

## Implementation Details

### Boolean Normalization
The XIEITE_BOOL macro uses double negation through COMPL and NOT:
- `XIEITE_NOT(x)` converts non-zero to 0, and 0 to 1 (not.hpp:8)
- `XIEITE_COMPL` then flips the result (compl.hpp:6)
- This ensures any non-zero value becomes 1

### Token Pasting Strategy
All boolean operations use token pasting (XIEITE_PCAT) to select appropriate expansions:
- `DETAIL_XIEITE_COMPL_0` expands to 1 (compl.hpp:8)
- `DETAIL_XIEITE_COMPL_1` expands to 0 (compl.hpp:9)
- `DETAIL_XIEITE_IF_0` selects second branch (if.hpp:12)
- `DETAIL_XIEITE_IF_1` selects first branch (if.hpp:13)

## Advanced Patterns

### Nested Conditions
```cpp
#define PLATFORM_CHECK \
    XIEITE_IF(XIEITE_AND(IS_WINDOWS, IS_64BIT))( \
        use_windows_64() \
    )( \
        XIEITE_IF(IS_WINDOWS)( \
            use_windows_32() \
        )( \
            use_other_platform() \
        ) \
    )
```

### Boolean Predicates
```cpp
// Check if value is in range
#define IN_RANGE(x, min, max) \
    XIEITE_AND( \
        XIEITE_BOOL(x >= min), \
        XIEITE_BOOL(x <= max) \
    )

// Usage
#if IN_RANGE(VERSION, 1, 3)
    // Version 1-3 specific code
#endif
```

### Lazy Evaluation
```cpp
// Short-circuit evaluation
#define SAFE_DIVIDE(a, b) \
    XIEITE_IF(XIEITE_BOOL(b))( \
        ((a) / (b)) \
    )( \
        0 \
    )
```

## Common Pitfalls

1. **Non-boolean values in IIF** - XIEITE_IIF requires exactly 0 or 1
2. **Missing parentheses** - Always parenthesize macro arguments
3. **Order of operations** - Boolean macros evaluate left-to-right
4. **Token expansion** - Some contexts may require extra indirection

## Best Practices

1. **Use XIEITE_BOOL for normalization** - Ensures consistent 0/1 values
2. **Prefer IF over IIF** - IF includes automatic boolean conversion
3. **Document boolean flags** - Clear naming for feature flags
4. **Test edge cases** - Verify with 0, 1, and other values

## Compatibility Notes

These macros work with:
- C++98 and later
- C99 and later (when used in C code)
- All major compilers (GCC, Clang, MSVC)
- Preprocessor-only evaluation (no runtime cost)

## See Also

- [Conditional Compilation](./conditional.md) - Platform-specific compilation
- [Token Operations](./tokens.md) - Token manipulation
- [Preprocessor Utilities](./utilities.md) - General preprocessor tools
- [Preprocessor API Reference](../../reference/api/pp.md)