# Preprocessor Utilities (pp/)

## Overview

The preprocessor utilities category contains 72 header files that provide powerful macro-based tools for compile-time code generation, conditional compilation, and syntactic sugar. This is the foundation of XIEITE's revolutionary Arrow Macro System and other advanced preprocessing capabilities.

## Directory Structure

```
include/xieite/pp/
├── Arrow Macros (8 headers)
│   ├── arrow.hpp          # Core arrow macro definitions
│   └── Supporting macros for arrow system
├── Conditional Compilation (15 headers)
│   ├── platform.hpp       # Platform detection
│   ├── arch.hpp          # Architecture detection
│   ├── compiler.hpp      # Compiler detection
│   └── Feature detection macros
├── Boolean Operations (8 headers)
│   ├── and.hpp           # Logical AND
│   ├── or.hpp            # Logical OR
│   ├── not.hpp           # Logical NOT
│   └── Boolean utility macros
├── Token Manipulation (20 headers)
│   ├── cat.hpp           # Token concatenation
│   ├── str.hpp           # Stringification
│   ├── paren.hpp         # Parenthesis manipulation
│   └── Token processing utilities
└── Utility Macros (21 headers)
    ├── eval.hpp          # Macro evaluation
    ├── repeat.hpp        # Repetition macros
    ├── debug.hpp         # Debug utilities
    └── General purpose macros
```

## Key Components

### 1. Arrow Macro System

The centerpiece of the preprocessor utilities, providing concise syntax for function definitions:

| Macro | Purpose | Source |
|-------|---------|---------|
| `XIEITE_ARROW` | Auto-deduced return type with noexcept detection | `pp/arrow.hpp:12-17` |
| `XIEITE_ARROW_NOEX` | Forced noexcept(true) with auto return | `pp/arrow.hpp:23-27` |
| `XIEITE_ARROW_RET` | Return without decltype | `pp/arrow.hpp:18-22` |
| `XIEITE_ARROW_IF` | Conditional execution | `pp/arrow.hpp:28-32` |
| `XIEITE_ARROW_CHOOSE` | Conditional return | `pp/arrow.hpp:33-37` |
| `XIEITE_ARROW_TRY` | Exception handling | `pp/arrow.hpp:38-44` |
| `XIEITE_ARROW_DECL` | Parameter declaration | `pp/arrow.hpp:45-51` |
| `XIEITE_ARROW_CTOR` | Constructor helper | `pp/arrow.hpp:52-58` |

### 2. Platform Detection

Comprehensive platform and architecture detection:

```cpp
// Platform macros
XIEITE_PLATFORM_TYPE    // windows, unix, embedded, unknown
XIEITE_PLATFORM_WINDOWS // 1 or 0
XIEITE_PLATFORM_UNIX    // 1 or 0
XIEITE_PLATFORM_LINUX   // 1 or 0
XIEITE_PLATFORM_MACOS   // 1 or 0
```

### 3. Compiler Detection

Identifies compiler and version:

```cpp
XIEITE_COMPILER_TYPE  // gcc, clang, msvc, icc, unknown
XIEITE_COMPILER_GCC   // 1 or 0
XIEITE_COMPILER_CLANG // 1 or 0
XIEITE_COMPILER_MSVC  // 1 or 0
```

## Design Philosophy

### Zero-Overhead Principle

All macros expand at preprocessing time with no runtime cost:
- Pure text substitution
- No function call overhead
- Compile-time constant expressions

### Composability

Macros are designed to compose with each other:
```cpp
// Macros can be nested and combined
XIEITE_IF(XIEITE_PLATFORM_WINDOWS)(
    XIEITE_CAT(win_, impl)
)(
    XIEITE_CAT(unix_, impl)
)
```

### Safety Through Concepts

Modern macros use requires-expressions for compile-time validation:
```cpp
#define XIEITE_ARROW(...) \
    noexcept(noexcept(__VA_ARGS__)) \
    -> decltype(auto) \
    requires(requires { __VA_ARGS__; }) \
    { return __VA_ARGS__; }
```

## Complete Header List

### Core Arrow System (8 headers)
1. `arrow.hpp` - Main arrow macro definitions
2. `unwrap.hpp` - Parenthesis unwrapping
3. `wrapped.hpp` - Parenthesis detection
4. `paren.hpp` - Parenthesis generation
5. `eval.hpp` - Macro evaluation
6. `each.hpp` - Variadic iteration
7. `opt.hpp` - Optional macro arguments
8. `if.hpp` - Conditional macro expansion

### Conditional Compilation (15 headers)
1. `platform.hpp` - Platform detection
2. `arch.hpp` - Architecture detection
3. `compiler.hpp` - Compiler detection
4. `endian.hpp` - Endianness detection
5. `lang.hpp` - Language version detection
6. `stdlib.hpp` - Standard library detection
7. `feat.hpp` - Feature detection
8. `has_attr.hpp` - Attribute detection
9. `has_declspec.hpp` - Declspec detection
10. `has_incl.hpp` - Include file detection
11. `unix.hpp` - Unix-specific macros
12. `no_unix.hpp` - Non-Unix macros
13. `no_windows.hpp` - Non-Windows macros
14. `check.hpp` - General checks
15. `ver.hpp` - Version detection

### Boolean Operations (8 headers)
1. `and.hpp` - Logical AND
2. `or.hpp` - Logical OR
3. `not.hpp` - Logical NOT
4. `bool.hpp` - Boolean conversion
5. `compl.hpp` - Complement operation
6. `any.hpp` - Any true check
7. `none.hpp` - None true check
8. `cm.hpp` - Conditional macro

### Token Manipulation (20 headers)
1. `cat.hpp` - Token concatenation
2. `str.hpp` - Stringification
3. `paren.hpp` - Parenthesis manipulation
4. `eat.hpp` - Token consumption
5. `del.hpp` - Token deletion
6. `unwrap.hpp` - Parenthesis removal
7. `wrapped.hpp` - Parenthesis detection
8. `wrap.hpp` - Parenthesis addition
9. `word.hpp` - Word extraction
10. `from.hpp` - Extract from position
11. `at.hpp` - Extract at position
12. `scan.hpp` - Token scanning
13. `seq.hpp` - Sequence manipulation
14. `reverse.hpp` - Reverse tokens
15. `repeat.hpp` - Token repetition
16. `until.hpp` - Repeat until condition
17. `for.hpp` - For-loop macro
18. `call.hpp` - Function-like call
19. `cases.hpp` - Case generation
20. `comma.hpp` - Comma manipulation

### Utility Macros (21 headers)
1. `debug.hpp` - Debug utilities
2. `diagnostic.hpp` - Diagnostic control
3. `pragma.hpp` - Pragma directives
4. `static_assert.hpp` - Static assertions
5. `attr.hpp` - Attribute macros
6. `keywords.hpp` - Keyword detection
7. `typeof.hpp` - Type extraction
8. `is_cxpr.hpp` - Constexpr detection
9. `signature.hpp` - Function signature
10. `fn.hpp` - Function utilities
11. `obj.hpp` - Object macros
12. `as.hpp` - Type casting
13. `defer.hpp` - Deferred execution
14. `probe.hpp` - Probing macros
15. `obstruct.hpp` - Macro obstruction
16. `revive.hpp` - Macro revival
17. `lift.hpp` - Lifting operations
18. `out.hpp` - Output macros
19. `ret_struct.hpp` - Return struct
20. `restrict.hpp` - Restrict keyword
21. `unreach.hpp` - Unreachable code

## Usage Patterns

### Basic Arrow Macro Usage

```cpp
// Simple function with auto-deduced return and noexcept
auto double_value(int x) XIEITE_ARROW(x * 2)
// Expands to:
// auto double_value(int x)
//     noexcept(noexcept(x * 2))
//     -> decltype(auto)
//     requires(requires { x * 2; })
//     { return x * 2; }
```

### Conditional Compilation

```cpp
XIEITE_IF(XIEITE_PLATFORM_WINDOWS)(
    // Windows-specific code
    using handle = HANDLE;
)(
    // Unix-specific code
    using handle = int;
)
```

### Token Manipulation

```cpp
#define MY_CLASS(name) \
    class XIEITE_CAT(My, name) { \
        static constexpr auto type = XIEITE_STR(name); \
    };

MY_CLASS(Widget)  // Creates class MyWidget
```

## Performance Characteristics

| Operation | Cost | Notes |
|-----------|------|-------|
| Macro expansion | Compile-time only | Zero runtime overhead |
| Token manipulation | Preprocessing only | No code generation |
| Conditional compilation | Branch elimination | Dead code removed |
| Arrow macros | Inline expansion | Same as manual code |

## Platform Support

| Platform | Detection Macro | Support Level |
|----------|----------------|---------------|
| Windows | `XIEITE_PLATFORM_WINDOWS` | Full |
| Linux | `XIEITE_PLATFORM_LINUX` | Full |
| macOS | `XIEITE_PLATFORM_MACOS` | Full |
| FreeBSD | `XIEITE_PLATFORM_UNIX` | Full |
| Embedded | Platform-specific | Partial |

## Compiler Compatibility

| Compiler | Minimum Version | Detection Macro |
|----------|----------------|-----------------|
| GCC | 10.0 | `XIEITE_COMPILER_GCC` |
| Clang | 12.0 | `XIEITE_COMPILER_CLANG` |
| MSVC | 19.29 | `XIEITE_COMPILER_MSVC` |
| ICC | 2021.1 | `XIEITE_COMPILER_ICC` |

## Advanced Features

### Variadic Macro Iteration

The `XIEITE_EACH` macro enables iteration over variadic arguments:

```cpp
#define PRINT(x) std::cout << x << " ";
XIEITE_EACH(PRINT, 1, 2, 3, 4)
// Expands to: PRINT(1) PRINT(2) PRINT(3) PRINT(4)
```

### Compile-Time Validation

Arrow macros include requires-expressions for compile-time validation:

```cpp
auto safe_divide(int a, int b)
    XIEITE_ARROW_IF(b != 0, , a / b)
// Only compiles if division is valid
```

### Exception Handling in Macros

The `XIEITE_ARROW_TRY` macro provides exception handling:

```cpp
auto safe_parse(const std::string& s)
    XIEITE_ARROW_TRY(
        std::stoi(s),
        (std::invalid_argument, -1),
        (std::out_of_range, 0)
    )
```

## Best Practices

1. **Use Arrow Macros for Simple Functions**: Ideal for getters, simple transformations
2. **Prefer Compile-Time Checks**: Use requires-expressions for validation
3. **Compose Macros Carefully**: Test macro expansion with complex nesting
4. **Document Macro Behavior**: Complex macros should have clear documentation
5. **Avoid Side Effects**: Macros should not modify global state

## Common Pitfalls

1. **Multiple Evaluation**: Arguments may be evaluated multiple times
2. **Precedence Issues**: Always parenthesize macro arguments
3. **Namespace Pollution**: Use DETAIL_ prefix for internal macros
4. **Debugging Difficulty**: Complex macros can be hard to debug

## Implementation Notes

- All macros use `DETAIL_XIEITE_` prefix for internal helpers
- Header guards follow pattern `DETAIL_XIEITE_HEADER_PP_NAME`
- Macros compose through careful token manipulation
- Recursive macro expansion is avoided for portability

---

*Next: [Arrow Macro System Deep Dive](arrow.md)*