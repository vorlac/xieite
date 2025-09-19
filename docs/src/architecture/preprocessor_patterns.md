# Preprocessor Patterns

The XIEITE library employs sophisticated preprocessor patterns that push the boundaries of C++ macro metaprogramming. These patterns enable compile-time code generation, token manipulation, and advanced macro composition techniques that form the foundation of XIEITE's powerful utility system.

## Core Preprocessor Philosophy

XIEITE's preprocessor system follows several key principles:

1. **Zero Runtime Overhead**: All preprocessor operations resolve at compile time
2. **Composability**: Macros build upon each other to create complex behaviors
3. **Type Safety**: Despite being macros, patterns maintain type safety through careful design
4. **Diagnostic Quality**: Error messages are designed to be as clear as possible within macro constraints

## Fundamental Preprocessor Patterns

### Token Pasting and Stringification

XIEITE uses sophisticated token manipulation for macro composition:

```cpp
// From include/xieite/pp/cat.hpp
#define XIEITE_CAT(x, y) DETAIL_XIEITE_CAT(x, y)
#define DETAIL_XIEITE_CAT(x, y) x ## y

// From include/xieite/pp/str.hpp
#define XIEITE_STR(x) DETAIL_XIEITE_STR(x)
#define DETAIL_XIEITE_STR(x) #x
```

The double-layer pattern ensures proper macro expansion:

```cpp
#define VERSION 42
XIEITE_STR(VERSION)           // Expands to "42" not "VERSION"
XIEITE_CAT(prefix_, VERSION)  // Expands to prefix_42
```

### Conditional Expansion Patterns

XIEITE implements sophisticated conditional compilation:

```cpp
// From include/xieite/pp/if.hpp
#define XIEITE_IF(cond) DETAIL_XIEITE_IF_ ## cond
#define DETAIL_XIEITE_IF_0(then_)(else_) else_
#define DETAIL_XIEITE_IF_1(then_)(else_) then_

// Usage pattern
#define CONDITIONAL_CODE(flag) XIEITE_IF(flag)(complex_version)(simple_version)
```

### Variadic Macro Patterns

XIEITE extensively uses C++20's `__VA_OPT__` for sophisticated variadic handling:

```cpp
// Pattern for optional arguments
#define PROCESS(...) __VA_OPT__(DETAIL_PROCESS(__VA_ARGS__))

// Pattern for conditional comma insertion
#define LIST_ITEMS(first, ...) first __VA_OPT__(, __VA_ARGS__)

// Pattern for counting arguments
#define COUNT_ARGS(...) DETAIL_COUNT(__VA_ARGS__ __VA_OPT__(,) 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
```

## Advanced Token Manipulation

### Parenthesis Detection and Unwrapping

XIEITE implements sophisticated parenthesis handling:

```cpp
// From include/xieite/pp/wrapped.hpp
#define XIEITE_WRAPPED(...) DETAIL_XIEITE_WRAPPED(__VA_ARGS__)
#define DETAIL_XIEITE_WRAPPED(...) DETAIL_XIEITE_WRAPPED_CHECK(__VA_ARGS__)

// From include/xieite/pp/unwrap.hpp
#define XIEITE_UNWRAP(...) XIEITE_CAT(DETAIL_XIEITE_UNWRAP_, DETAIL_XIEITE_UNWRAP __VA_ARGS__)
#define DETAIL_XIEITE_UNWRAP(...) DETAIL_XIEITE_UNWRAP __VA_ARGS__
#define DETAIL_XIEITE_UNWRAP_DETAIL_XIEITE_UNWRAP
```

This enables:
```cpp
XIEITE_WRAPPED((x, y))    // Returns 1 (wrapped)
XIEITE_WRAPPED(x)         // Returns 0 (not wrapped)
XIEITE_UNWRAP((x, y))     // Returns x, y
XIEITE_UNWRAP(x)          // Returns x
```

### Optional Macro Expansion

XIEITE's optional expansion pattern:

```cpp
// From include/xieite/pp/opt.hpp
#define XIEITE_OPT(...) DETAIL_XIEITE_OPT(__VA_ARGS__)
#define DETAIL_XIEITE_OPT(...) __VA_OPT__(DETAIL_XIEITE_OPT_EXPAND(__VA_ARGS__))

// Usage: Execute macro only if arguments provided
XIEITE_OPT(value)(PROCESS(value))()  // Processes if value exists
XIEITE_OPT()(PROCESS())()             // No-op if empty
```

## Macro Composition Patterns

### Recursive Macro Expansion

XIEITE uses controlled recursion for complex operations:

```cpp
// Pattern for list processing
#define PROCESS_LIST(macro, ...) __VA_OPT__(DETAIL_PROCESS_LIST(macro, __VA_ARGS__))
#define DETAIL_PROCESS_LIST(macro, head, ...) \
    macro(head) __VA_OPT__(, DETAIL_PROCESS_LIST_NEXT()(macro, __VA_ARGS__))
#define DETAIL_PROCESS_LIST_NEXT() DETAIL_PROCESS_LIST

// Example: Apply transformation to each element
#define STRINGIFY(x) #x
PROCESS_LIST(STRINGIFY, a, b, c)  // "a", "b", "c"
```

### Deferred Expansion

XIEITE employs deferred expansion for complex macro interactions:

```cpp
// From include/xieite/pp/eval.hpp
#define XIEITE_EVAL(...) DETAIL_XIEITE_EVAL1(__VA_ARGS__)
#define DETAIL_XIEITE_EVAL1(...) DETAIL_XIEITE_EVAL2(__VA_ARGS__)
#define DETAIL_XIEITE_EVAL2(...) DETAIL_XIEITE_EVAL3(__VA_ARGS__)
// ... continues for sufficient expansion depth

// Ensures complete macro expansion before final evaluation
#define COMPLEX_MACRO(...) XIEITE_EVAL(NESTED_EXPANSION(__VA_ARGS__))
```

### Parenthesis Generation

Pattern for generating parentheses on demand:

```cpp
// From include/xieite/pp/paren.hpp
#define XIEITE_PAREN() ()
#define XIEITE_LPAREN() (
#define XIEITE_RPAREN() )

// Enables dynamic function-like macro invocation
#define INVOKE_LATER(macro) macro XIEITE_PAREN()
```

## Compile-Time Selection Patterns

### Boolean Logic in Preprocessor

XIEITE implements boolean operations entirely in preprocessor:

```cpp
// From include/xieite/pp/bool_*.hpp
#define XIEITE_BOOL_AND(a, b) DETAIL_XIEITE_BOOL_AND_ ## a ## _ ## b
#define DETAIL_XIEITE_BOOL_AND_0_0 0
#define DETAIL_XIEITE_BOOL_AND_0_1 0
#define DETAIL_XIEITE_BOOL_AND_1_0 0
#define DETAIL_XIEITE_BOOL_AND_1_1 1

#define XIEITE_BOOL_OR(a, b) DETAIL_XIEITE_BOOL_OR_ ## a ## _ ## b
#define DETAIL_XIEITE_BOOL_OR_0_0 0
#define DETAIL_XIEITE_BOOL_OR_0_1 1
#define DETAIL_XIEITE_BOOL_OR_1_0 1
#define DETAIL_XIEITE_BOOL_OR_1_1 1
```

### Compile-Time Branching

Advanced branching based on multiple conditions:

```cpp
// Multi-condition selection
#define SELECT_IMPLEMENTATION(feature1, feature2) \
    XIEITE_CAT(IMPL_, XIEITE_CAT(feature1, XIEITE_CAT(_, feature2)))

#define IMPL_0_0() basic_implementation
#define IMPL_0_1() feature2_implementation
#define IMPL_1_0() feature1_implementation
#define IMPL_1_1() combined_implementation

// Usage
SELECT_IMPLEMENTATION(HAS_AVX, HAS_SSE)()
```

## Error Handling and Diagnostics

### Static Assertion Patterns

XIEITE uses preprocessor patterns for compile-time assertions:

```cpp
// Pattern for preprocessor static assertions
#define XIEITE_PP_ASSERT(cond, msg) \
    XIEITE_IF(cond)(/* valid */)(DETAIL_PP_ERROR(msg))

#define DETAIL_PP_ERROR(msg) \
    static_assert(false, "Preprocessor assertion failed: " msg)

// Usage
#define SAFE_MACRO(x) \
    XIEITE_PP_ASSERT(XIEITE_WRAPPED(x), "Argument must be wrapped") \
    PROCESS(XIEITE_UNWRAP(x))
```

### Diagnostic Message Generation

Pattern for generating helpful error messages:

```cpp
// Generate contextual error messages
#define XIEITE_CONTEXT_ERROR(context, error) \
    XIEITE_CAT(ERROR_IN_, context) XIEITE_CAT(__, error)

// Produces readable error tokens
XIEITE_CONTEXT_ERROR(TEMPLATE_EXPANSION, INVALID_TYPE)
// Expands to: ERROR_IN_TEMPLATE_EXPANSION__INVALID_TYPE
```

## Platform-Specific Patterns

### Conditional Platform Code

XIEITE uses preprocessor patterns for platform branching:

```cpp
// Pattern for platform-specific implementations
#define PLATFORM_IMPL(name) \
    XIEITE_IF(XIEITE_PLATFORM_TYPE_WINDOWS)( \
        name ## _windows \
    )( \
        XIEITE_IF(XIEITE_PLATFORM_TYPE_LINUX)( \
            name ## _linux \
        )( \
            name ## _generic \
        ) \
    )

// Selects appropriate implementation
#define OPTIMIZED_FUNC PLATFORM_IMPL(fast_func)
```

### Compiler-Specific Extensions

Pattern for using compiler-specific features safely:

```cpp
// Compiler feature detection pattern
#ifdef __has_builtin
    #define XIEITE_HAS_BUILTIN(x) __has_builtin(x)
#else
    #define XIEITE_HAS_BUILTIN(x) 0
#endif

// Conditional builtin usage
#define SAFE_POPCOUNT(x) \
    XIEITE_IF(XIEITE_HAS_BUILTIN(__builtin_popcount))( \
        __builtin_popcount(x) \
    )( \
        generic_popcount(x) \
    )
```

## Macro Hygiene Patterns

### Namespace Pollution Prevention

XIEITE uses prefixing and undefining patterns:

```cpp
// Internal detail macros use DETAIL_ prefix
#define DETAIL_XIEITE_INTERNAL_HELPER(x) implementation

// Public macros use XIEITE_ prefix
#define XIEITE_PUBLIC_MACRO(x) DETAIL_XIEITE_INTERNAL_HELPER(x)

// Cleanup pattern for temporary macros
#define TEMP_MACRO helper_implementation
// ... use TEMP_MACRO ...
#undef TEMP_MACRO
```

### Argument Protection

Pattern for protecting macro arguments:

```cpp
// Parenthesize to protect against operator precedence
#define SAFE_MULTIPLY(a, b) ((a) * (b))

// Use do-while for statement-like macros
#define SAFE_STATEMENT(code) do { code } while(0)

// Protect against multiple evaluation
#define SAFE_SWAP(a, b) do { \
    auto XIEITE_UNIQUE(temp) = (a); \
    (a) = (b); \
    (b) = XIEITE_UNIQUE(temp); \
} while(0)
```

## Advanced Composition Examples

### The Arrow Macro Pattern

The arrow macros demonstrate advanced composition:

```cpp
// Combines multiple patterns
#define XIEITE_ARROW(...) \
    noexcept __VA_OPT__((noexcept(__VA_ARGS__))) \
    -> decltype(auto) \
    requires __VA_OPT__((requires { __VA_ARGS__; })) \
    { return __VA_ARGS__; }

// Uses:
// - __VA_OPT__ for optional content
// - Token pasting for composition
// - Deferred evaluation for complex expressions
```

### Recursive Type List Processing

Pattern for compile-time type manipulation:

```cpp
// Process type lists recursively
#define PROCESS_TYPES(macro, ...) \
    __VA_OPT__(DETAIL_PROCESS_TYPES(macro, __VA_ARGS__))

#define DETAIL_PROCESS_TYPES(macro, head, ...) \
    macro(head) __VA_OPT__(, DETAIL_PROCESS_TYPES_NEXT()(macro, __VA_ARGS__))

#define DETAIL_PROCESS_TYPES_NEXT() DETAIL_PROCESS_TYPES

// Generate template parameters
#define TEMPLATE_PARAM(type) typename type
template<PROCESS_TYPES(TEMPLATE_PARAM, T1, T2, T3)>
// Expands to: template<typename T1, typename T2, typename T3>
```

## Integration with Template Metaprogramming

### Bridging Preprocessor and Templates

XIEITE seamlessly bridges preprocessor and template systems:

```cpp
// Generate template specializations
#define GENERATE_SPECIALIZATION(type) \
    template<> \
    struct processor<type> { \
        static constexpr auto process(type value) { \
            return specialized_process_ ## type(value); \
        } \
    };

// Apply to multiple types
PROCESS_LIST(GENERATE_SPECIALIZATION, int, float, double)
```

### Concept Generation

Pattern for generating concepts from macros:

```cpp
// Generate concept from requirements
#define DEFINE_CONCEPT(name, ...) \
    template<typename T> \
    concept name = requires(T t) { \
        __VA_ARGS__ \
    };

DEFINE_CONCEPT(Incrementable,
    ++t;
    t++;
    { t + 1 } -> std::same_as<T>;
)
```

## Performance Considerations

### Compilation Time Impact

Preprocessor patterns affect compilation time:

1. **Macro Expansion Depth**: Deep recursion increases compilation time
2. **Token Count**: Large macro expansions consume memory
3. **Include Dependencies**: Minimal includes reduce preprocessing time

### Optimization Patterns

```cpp
// Minimize expansion by deferring to templates when possible
#define OPTIMIZE_CHOICE(cond, true_path, false_path) \
    std::conditional_t<cond, \
        std::integral_constant<decltype(true_path), true_path>, \
        std::integral_constant<decltype(false_path), false_path> \
    >::value

// Combines preprocessor selection with template optimization
```

## Best Practices

### 1. Use Meaningful Prefixes

```cpp
// Good: Clear namespace separation
#define XIEITE_PUBLIC_API(x) implementation
#define DETAIL_XIEITE_INTERNAL(x) helper

// Avoid: Generic names that may conflict
#define HELPER(x) implementation  // Risk of collision
```

### 2. Document Macro Behavior

```cpp
/**
 * @brief Applies macro to each argument
 * @param macro Function-like macro to apply
 * @param ... Arguments to process
 * @note Generates comma-separated list
 */
#define XIEITE_FOR_EACH(macro, ...) implementation
```

### 3. Protect Against Reevaluation

```cpp
// Good: Single evaluation
#define SAFE_MAX(a, b) \
    ([](auto&& x, auto&& y) { return x > y ? x : y; }(a, b))

// Risky: Multiple evaluation
#define UNSAFE_MAX(a, b) ((a) > (b) ? (a) : (b))
```

### 4. Provide Escape Hatches

```cpp
// Allow disabling macros when needed
#ifndef XIEITE_NO_MACROS
    #define XIEITE_MACRO implementation
#endif

// Or provide alternative implementations
#ifdef XIEITE_USE_TEMPLATE_VERSION
    template<typename T> constexpr auto func(T t) { return t; }
#else
    #define func(x) (x)
#endif
```

## Common Pitfalls and Solutions

### Comma Interpretation

Problem: Commas in template arguments break macro parsing

```cpp
// Problem
MACRO(std::pair<int, double>)  // Sees two arguments

// Solution: Wrap in parentheses
MACRO((std::pair<int, double>))  // One argument

// Or use typedef
using pair_type = std::pair<int, double>;
MACRO(pair_type)
```

### Recursive Expansion Limits

Problem: Preprocessors have expansion depth limits

```cpp
// Solution: Use bounded recursion with explicit termination
#define RECURSE_256 RECURSE_128 RECURSE_128
#define RECURSE_128 RECURSE_64 RECURSE_64
#define RECURSE_64 RECURSE_32 RECURSE_32
// ... continue pattern
```

### Token Pasting with Operators

Problem: Can't paste to create operators

```cpp
// Doesn't work: XIEITE_CAT(+, =)  // Can't create +=

// Solution: Use conditional selection
#define SELECT_OP(op) DETAIL_SELECT_OP_ ## op
#define DETAIL_SELECT_OP_PLUS +=
#define DETAIL_SELECT_OP_MINUS -=
```

## Advanced Techniques

### Self-Modifying Macros

Pattern for macros that change behavior based on invocation count:

```cpp
#define COUNTER_MACRO() DETAIL_COUNTER_0
#define DETAIL_COUNTER_0 1 DETAIL_COUNTER_REDEF_0
#define DETAIL_COUNTER_REDEF_0 \
    #undef COUNTER_MACRO \
    #define COUNTER_MACRO() DETAIL_COUNTER_1

// Each invocation returns different value
```

### Compile-Time String Processing

Pattern for preprocessor string manipulation:

```cpp
// Extract first character
#define FIRST_CHAR(str) DETAIL_FIRST_CHAR_ ## str
#define DETAIL_FIRST_CHAR_hello 'h'
#define DETAIL_FIRST_CHAR_world 'w'

// Limited but useful for specific cases
```

---

*See also: [Macro System](macro_system.md) | [Arrow Macros](arrow_macros.md) | [Token Manipulation](token_manipulation.md)*