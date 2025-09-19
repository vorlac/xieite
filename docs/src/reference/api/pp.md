# Preprocessor API Reference

## Overview

The preprocessor category contains 72 header files providing powerful macro-based utilities for compile-time code generation, conditional compilation, platform detection, and the unique ARROW macro system.

## Core Components

### Arrow Macro System

The ARROW macros provide concise syntax for function definitions with automatic type deduction and noexcept specification.

#### XIEITE_ARROW
**Header**: `pp/arrow.hpp`
**Synopsis**:
```cpp
#define XIEITE_ARROW(...) \
    noexcept(noexcept(__VA_ARGS__)) \
    -> decltype(auto) \
    requires(requires { __VA_ARGS__; }) \
    { return __VA_ARGS__; }
```
**Purpose**: Auto-deduces return type and noexcept specification
**Example**:
```cpp
auto add(int x, int y) XIEITE_ARROW(x + y)
// Expands to: noexcept(noexcept(x + y)) -> decltype(auto) requires(requires { x + y; }) { return x + y; }
```

#### XIEITE_ARROW_NOEX
**Header**: `pp/arrow.hpp`
**Synopsis**:
```cpp
#define XIEITE_ARROW_NOEX(...) \
    noexcept \
    -> decltype(auto) \
    requires(requires { __VA_ARGS__; }) \
    { return __VA_ARGS__; }
```
**Purpose**: Forces noexcept(true) regardless of expression
**Example**:
```cpp
auto safe_get(int x) XIEITE_ARROW_NOEX(x)
// Always noexcept, even if x's operations might throw
```

#### XIEITE_ARROW_RET
**Header**: `pp/arrow.hpp`
**Synopsis**:
```cpp
#define XIEITE_ARROW_RET(...) \
    { return __VA_ARGS__; }
```
**Purpose**: Simple return without type deduction
**Example**:
```cpp
void process() XIEITE_ARROW_RET()  // Returns void
int get_value() XIEITE_ARROW_RET(42)
```

#### XIEITE_ARROW_IF
**Header**: `pp/arrow.hpp`
**Synopsis**:
```cpp
#define XIEITE_ARROW_IF(cond, ...) \
    { if (cond) { return __VA_ARGS__; } }
```
**Purpose**: Conditional return
**Example**:
```cpp
std::optional<int> find(bool found, int value)
    XIEITE_ARROW_IF(found, value)
```

#### XIEITE_ARROW_CHOOSE
**Header**: `pp/arrow.hpp`
**Synopsis**:
```cpp
#define XIEITE_ARROW_CHOOSE(cond, true_val, false_val) \
    { return (cond) ? (true_val) : (false_val); }
```
**Purpose**: Ternary return
**Example**:
```cpp
int max(int a, int b) XIEITE_ARROW_CHOOSE(a > b, a, b)
```

#### XIEITE_ARROW_TRY
**Header**: `pp/arrow.hpp`
**Synopsis**:
```cpp
#define XIEITE_ARROW_TRY(...) \
    try { return __VA_ARGS__; } \
    catch(...) { throw; }
```
**Purpose**: Exception-aware return
**Example**:
```cpp
auto risky_op() XIEITE_ARROW_TRY(might_throw())
```

#### XIEITE_ARROW_DECL
**Header**: `pp/arrow.hpp`
**Synopsis**:
```cpp
#define XIEITE_ARROW_DECL(type, name, ...) \
    type name __VA_ARGS__
```
**Purpose**: Parameter declaration helper
**Example**:
```cpp
XIEITE_ARROW_DECL(int, value, = 0)  // int value = 0
```

#### XIEITE_ARROW_CTOR
**Header**: `pp/arrow.hpp`
**Synopsis**:
```cpp
#define XIEITE_ARROW_CTOR(class_name, ...) \
    class_name(__VA_ARGS__)
```
**Purpose**: Constructor definition helper
**Example**:
```cpp
struct Point {
    int x, y;
    XIEITE_ARROW_CTOR(Point, int a, int b) : x(a), y(b) {}
};
```

### Token Manipulation

#### XIEITE_CAT
**Header**: `pp/cat.hpp`
**Synopsis**:
```cpp
#define XIEITE_CAT(x, ...) x##__VA_ARGS__
```
**Purpose**: Concatenate tokens
**Example**:
```cpp
XIEITE_CAT(foo, bar)  // foobar
XIEITE_CAT(TYPE_, int)  // TYPE_int
```

#### XIEITE_STR
**Header**: `pp/str.hpp`
**Synopsis**:
```cpp
#define XIEITE_STR(...) #__VA_ARGS__
```
**Purpose**: Stringify tokens
**Example**:
```cpp
XIEITE_STR(hello world)  // "hello world"
```

#### XIEITE_WRAP
**Header**: `pp/wrap.hpp`
**Synopsis**:
```cpp
#define XIEITE_WRAP(...) (__VA_ARGS__)
```
**Purpose**: Wrap in parentheses
**Example**:
```cpp
XIEITE_WRAP(1, 2, 3)  // (1, 2, 3)
```

#### XIEITE_UNWRAP
**Header**: `pp/unwrap.hpp`
**Synopsis**:
```cpp
#define XIEITE_UNWRAP(...) __VA_ARGS__
```
**Purpose**: Remove parentheses
**Example**:
```cpp
XIEITE_UNWRAP((1, 2, 3))  // 1, 2, 3
```

### Conditional Compilation

#### XIEITE_IF
**Header**: `pp/if.hpp`
**Synopsis**:
```cpp
#define XIEITE_IF(cond) XIEITE_CAT(XIEITE_IF_, cond)
#define XIEITE_IF_0(t, f) f
#define XIEITE_IF_1(t, f) t
```
**Purpose**: Compile-time conditional
**Example**:
```cpp
XIEITE_IF(1)(true_case, false_case)  // true_case
XIEITE_IF(0)(true_case, false_case)  // false_case
```

#### XIEITE_WHEN
**Header**: `pp/when.hpp`
**Synopsis**:
```cpp
#define XIEITE_WHEN(cond) XIEITE_IF(cond)(XIEITE_EXPAND, XIEITE_EAT)
```
**Purpose**: Conditional expansion
**Example**:
```cpp
XIEITE_WHEN(DEBUG_MODE)(expensive_check())
```

### Platform Detection

#### Operating Systems
**Header**: `pp/platform.hpp`

```cpp
// Platform type macros
#define XIEITE_PLATFORM_TYPE_LINUX 0/1
#define XIEITE_PLATFORM_TYPE_WINDOWS 0/1
#define XIEITE_PLATFORM_TYPE_MACOS 0/1
#define XIEITE_PLATFORM_TYPE_BSD 0/1
#define XIEITE_PLATFORM_TYPE_ANDROID 0/1
#define XIEITE_PLATFORM_TYPE_IOS 0/1
// ... 50+ platforms

// Version information
#define XIEITE_PLATFORM_MAJOR_<PLATFORM> n
#define XIEITE_PLATFORM_MINOR_<PLATFORM> n
#define XIEITE_PLATFORM_PATCH_<PLATFORM> n
```

**Example**:
```cpp
#if XIEITE_PLATFORM_TYPE_LINUX
    // Linux-specific code
#elif XIEITE_PLATFORM_TYPE_WINDOWS
    // Windows-specific code
#endif
```

#### Architecture Detection
**Header**: `pp/arch.hpp`

```cpp
// Architecture macros
#define XIEITE_ARCH_TYPE_X86_64 0/1
#define XIEITE_ARCH_TYPE_X86_32 0/1
#define XIEITE_ARCH_TYPE_AARCH64 0/1
#define XIEITE_ARCH_TYPE_AARCH32 0/1
// ... 55+ architectures

// Version comparison
#define XIEITE_ARCH_VER(type, cmp, major, ...)
```

**Example**:
```cpp
#if XIEITE_ARCH_TYPE_X86_64
    // x64 optimizations
#elif XIEITE_ARCH_TYPE_AARCH64
    // ARM64 optimizations
#endif
```

#### Compiler Detection
**Header**: `pp/compiler.hpp`

```cpp
// Compiler detection
#define XIEITE_COMPILER_TYPE_GCC 0/1
#define XIEITE_COMPILER_TYPE_CLANG 0/1
#define XIEITE_COMPILER_TYPE_MSVC 0/1
// ... 100+ compilers

// Version information
#define XIEITE_COMPILER_VER(type, cmp, major, ...)
```

**Example**:
```cpp
#if XIEITE_COMPILER_TYPE_GCC && XIEITE_COMPILER_VER(GCC, >=, 11, 0, 0)
    // GCC 11+ features
#endif
```

### Iteration and Repetition

#### XIEITE_REPEAT
**Header**: `pp/repeat.hpp`
**Synopsis**:
```cpp
#define XIEITE_REPEAT(n, macro, ...) \
    XIEITE_CAT(XIEITE_REPEAT_, n)(macro, __VA_ARGS__)
```
**Purpose**: Repeat macro n times
**Example**:
```cpp
#define PRINT(i, x) std::cout << x << i << '\n';
XIEITE_REPEAT(3, PRINT, "Item ")
// Expands to:
// std::cout << "Item " << 0 << '\n';
// std::cout << "Item " << 1 << '\n';
// std::cout << "Item " << 2 << '\n';
```

#### XIEITE_FOR
**Header**: `pp/for.hpp`
**Synopsis**:
```cpp
#define XIEITE_FOR(macro, ...) \
    XIEITE_FOR_I(macro, __VA_ARGS__)
```
**Purpose**: Apply macro to each argument
**Example**:
```cpp
#define DECLARE(x) int x;
XIEITE_FOR(DECLARE, a, b, c)
// Expands to: int a; int b; int c;
```

### Boolean Operations

#### XIEITE_AND
**Header**: `pp/and.hpp`
**Synopsis**:
```cpp
#define XIEITE_AND(a, b) XIEITE_CAT(XIEITE_AND_, a)(b)
```
**Purpose**: Logical AND
**Example**:
```cpp
XIEITE_AND(1, 1)  // 1
XIEITE_AND(1, 0)  // 0
```

#### XIEITE_OR
**Header**: `pp/or.hpp`
**Synopsis**:
```cpp
#define XIEITE_OR(a, b) XIEITE_CAT(XIEITE_OR_, a)(b)
```
**Purpose**: Logical OR
**Example**:
```cpp
XIEITE_OR(0, 1)  // 1
XIEITE_OR(0, 0)  // 0
```

#### XIEITE_NOT
**Header**: `pp/not.hpp`
**Synopsis**:
```cpp
#define XIEITE_NOT(x) XIEITE_CAT(XIEITE_NOT_, x)
```
**Purpose**: Logical NOT
**Example**:
```cpp
XIEITE_NOT(1)  // 0
XIEITE_NOT(0)  // 1
```

### Utility Macros

#### XIEITE_COUNT
**Header**: `pp/count.hpp`
**Synopsis**:
```cpp
#define XIEITE_COUNT(...) \
    XIEITE_COUNT_I(__VA_ARGS__, 64, 63, 62, /* ... */ 1, 0)
```
**Purpose**: Count variadic arguments
**Example**:
```cpp
XIEITE_COUNT(a, b, c)  // 3
XIEITE_COUNT()  // 0
```

#### XIEITE_DEFER
**Header**: `pp/defer.hpp`
**Synopsis**:
```cpp
#define XIEITE_DEFER(...) __VA_ARGS__ XIEITE_EAT()
```
**Purpose**: Defer expansion
**Example**:
```cpp
XIEITE_DEFER(MACRO)(args)  // Delays MACRO expansion
```

#### XIEITE_EVAL
**Header**: `pp/eval.hpp`
**Synopsis**:
```cpp
#define XIEITE_EVAL(...) XIEITE_EVAL1024(__VA_ARGS__)
```
**Purpose**: Force recursive evaluation
**Example**:
```cpp
XIEITE_EVAL(RECURSIVE_MACRO(x))  // Fully expands recursion
```

### Debug and Diagnostics

#### XIEITE_DEBUG
**Header**: `pp/debug.hpp`
**Synopsis**:
```cpp
#ifdef DEBUG
    #define XIEITE_DEBUG(...) __VA_ARGS__
#else
    #define XIEITE_DEBUG(...)
#endif
```
**Purpose**: Conditional debug code
**Example**:
```cpp
XIEITE_DEBUG(std::cout << "Debug: " << value << '\n';)
```

#### XIEITE_STATIC_ASSERT
**Header**: `pp/static_assert.hpp`
**Synopsis**:
```cpp
#define XIEITE_STATIC_ASSERT(cond, msg) \
    static_assert(cond, msg)
```
**Purpose**: Compile-time assertion
**Example**:
```cpp
XIEITE_STATIC_ASSERT(sizeof(int) == 4, "Requires 32-bit int")
```

### Language Features

#### XIEITE_LANG
**Header**: `pp/lang.hpp`
**Synopsis**:
```cpp
#define XIEITE_LANG_CPP __cplusplus
#define XIEITE_LANG_CPP98 199711L
#define XIEITE_LANG_CPP11 201103L
#define XIEITE_LANG_CPP14 201402L
#define XIEITE_LANG_CPP17 201703L
#define XIEITE_LANG_CPP20 202002L
#define XIEITE_LANG_CPP23 202302L
```
**Purpose**: Language version detection
**Example**:
```cpp
#if XIEITE_LANG_CPP >= XIEITE_LANG_CPP20
    // C++20 features
#endif
```

#### XIEITE_FEAT
**Header**: `pp/feat.hpp`
**Synopsis**:
```cpp
#define XIEITE_FEAT(feature) __has_cpp_attribute(feature)
```
**Purpose**: Feature detection
**Example**:
```cpp
#if XIEITE_FEAT(nodiscard)
    [[nodiscard]]
#endif
```

### Version Management

#### XIEITE_VER
**Header**: `pp/ver.hpp`
**Synopsis**:
```cpp
#define XIEITE_VER_MAJOR 0
#define XIEITE_VER_MINOR 118
#define XIEITE_VER_PATCH 2
#define XIEITE_VER_STRING "0.118.2"
```
**Purpose**: Library version information
**Example**:
```cpp
#if XIEITE_VER_MAJOR >= 1
    // Version 1.x features
#endif
```

## Complete Header List

### Core Macros (8 files)
- `arrow.hpp` - Arrow macro family
- `cat.hpp` - Token concatenation
- `str.hpp` - Stringification
- `wrap.hpp` - Parenthesis wrapping
- `unwrap.hpp` - Parenthesis removal
- `defer.hpp` - Expansion deferral
- `eval.hpp` - Recursive evaluation
- `scan.hpp` - Token scanning

### Conditional Compilation (12 files)
- `if.hpp` - Conditional selection
- `when.hpp` - Conditional expansion
- `and.hpp` - Logical AND
- `or.hpp` - Logical OR
- `not.hpp` - Logical NOT
- `bool.hpp` - Boolean operations
- `check.hpp` - Condition checking
- `probe.hpp` - Token probing
- `any.hpp` - Any condition true
- `none.hpp` - No condition true
- `all.hpp` - All conditions true
- `opt.hpp` - Optional expansion

### Platform Detection (6 files)
- `platform.hpp` - OS detection
- `arch.hpp` - Architecture detection
- `compiler.hpp` - Compiler detection
- `endian.hpp` - Endianness detection
- `encoding.hpp` - Character encoding
- `stdlib.hpp` - Standard library detection

### Iteration (8 files)
- `repeat.hpp` - Repeat n times
- `for.hpp` - For each argument
- `each.hpp` - Apply to each
- `seq.hpp` - Generate sequences
- `reverse.hpp` - Reverse arguments
- `at.hpp` - Access nth argument
- `from.hpp` - Arguments from index
- `until.hpp` - Process until condition

### Utilities (14 files)
- `count.hpp` - Count arguments
- `comma.hpp` - Comma operations
- `paren.hpp` - Parenthesis utilities
- `eat.hpp` - Consume tokens
- `empty.hpp` - Empty expansion
- `obstruct.hpp` - Obstruct expansion
- `revive.hpp` - Revive tokens
- `lift.hpp` - Lift to token level
- `cases.hpp` - Case transformations
- `word.hpp` - Word operations
- `cm.hpp` - Comma variants
- `del.hpp` - Delete tokens
- `obj.hpp` - Object-like macros
- `ret_struct.hpp` - Return struct

### Language Features (10 files)
- `lang.hpp` - Language version
- `feat.hpp` - Feature detection
- `attr.hpp` - Attribute support
- `has_attr.hpp` - Attribute detection
- `has_incl.hpp` - Include detection
- `has_declspec.hpp` - Declspec detection
- `keywords.hpp` - Keyword definitions
- `typeof.hpp` - Type extraction
- `is_cxpr.hpp` - Constexpr detection
- `signature.hpp` - Function signatures

### Debug and Diagnostics (8 files)
- `debug.hpp` - Debug macros
- `static_assert.hpp` - Static assertions
- `diagnostic.hpp` - Diagnostic control
- `pragma.hpp` - Pragma directives
- `unreach.hpp` - Unreachable code
- `restrict.hpp` - Restrict qualifier
- `no_unix.hpp` - Unix exclusion
- `no_windows.hpp` - Windows exclusion

### Version and Configuration (6 files)
- `ver.hpp` - Version information
- `ver_guard.hpp` - Version guards
- `call.hpp` - Macro calling
- `fn.hpp` - Function macros
- `fwd.hpp` - Forward declarations
- `out.hpp` - Output control

## Usage Guidelines

### Best Practices

1. **Use Arrow Macros for Simple Functions**
```cpp
// Good: Clear and concise
auto double_it(int x) XIEITE_ARROW(x * 2)

// Avoid for complex logic
auto complex_func(int x) {
    // Multiple statements need traditional body
    validate(x);
    log(x);
    return process(x);
}
```

2. **Platform Detection Order**
```cpp
// Check most specific first
#if XIEITE_PLATFORM_TYPE_ANDROID
    // Android (Linux-based)
#elif XIEITE_PLATFORM_TYPE_LINUX
    // Generic Linux
#endif
```

3. **Compiler Feature Detection**
```cpp
// Combine compiler and version
#if XIEITE_COMPILER_TYPE_GCC && XIEITE_COMPILER_VER(GCC, >=, 10, 0, 0)
    // GCC 10+ specific code
#endif
```

### Common Patterns

#### Multi-Platform Support
```cpp
#if XIEITE_PLATFORM_TYPE_WINDOWS
    #include <windows.h>
    using handle_t = HANDLE;
#elif XIEITE_PLATFORM_TYPE_UNIX
    #include <unistd.h>
    using handle_t = int;
#else
    #error "Unsupported platform"
#endif
```

#### Conditional Compilation
```cpp
#define LOG_LEVEL 2

#if LOG_LEVEL >= 3
    #define LOG_DEBUG(...) log_impl("DEBUG", __VA_ARGS__)
#else
    #define LOG_DEBUG(...)
#endif
```

#### Version-Based Features
```cpp
#if XIEITE_LANG_CPP >= XIEITE_LANG_CPP20
    template<typename T>
    concept my_concept = true;
#else
    // Pre-C++20 fallback
#endif
```

## Performance Notes

- **Zero Runtime Cost**: All preprocessor operations happen at compile time
- **Compile-Time Impact**: Complex macro expansions may increase compilation time
- **Token Limit**: Be aware of preprocessor token limits in deeply nested macros
- **Debugging**: Macro-heavy code can be harder to debug - use `-E` flag to see expansion

## Compatibility

- **C++ Standard**: Requires C++20 or later
- **Preprocessor**: Standard-compliant preprocessor required
- **Variadic Macros**: Full C99/C++11 variadic macro support required
- **Token Pasting**: Standard ## and # operators must be supported

## See Also

- [Architecture Overview](../../architecture/macro_system.md)
- [Arrow Macros Deep Dive](../../architecture/arrow_macros.md)
- [Token Manipulation](../../architecture/token_manipulation.md)
- [Platform Detection Guide](../../categories/pp/platform.md)