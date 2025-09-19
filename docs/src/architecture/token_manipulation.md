# Token Manipulation Techniques

## Overview

Token manipulation represents the foundation of XIEITE's preprocessor metaprogramming capabilities. Through careful manipulation of preprocessor tokens, the library achieves complex compile-time computations, conditional expansions, and macro composition that would otherwise be impossible in the preprocessor phase.

## Core Token Operations

### Token Concatenation

The concatenation system provides multiple ways to combine tokens:

```cpp
// Basic concatenation (cat.hpp)
#define XIEITE_CAT(x, ...) XIEITE_PCAT(x, __VA_ARGS__)
#define XIEITE_PCAT(x, ...) x##__VA_ARGS__

// Reverse concatenation
#define XIEITE_CATR(x, ...) XIEITE_PCATR(x, __VA_ARGS__)
#define XIEITE_PCATR(x, ...) __VA_ARGS__##x

// Partial concatenation helpers
#define XIEITE_CAT_A(x) XIEITE_PCAT(x,    // Opens concatenation
#define XIEITE_CAT_B(x) XIEITE_PCATR(x,   // Reverse open
```

Usage patterns:
```cpp
XIEITE_CAT(foo, bar)        // Expands to: foobar
XIEITE_CATR(bar, foo)       // Expands to: foobar
XIEITE_CAT(TYPE_, int)      // Expands to: TYPE_int
```

### Token Wrapping

Parenthesis manipulation enables variadic argument handling:

```cpp
// wrap.hpp - Add parentheses
#define XIEITE_WRAP(...) (__VA_ARGS__)

// unwrap.hpp - Remove parentheses
#define XIEITE_UNWRAP(...) XIEITE_PUNWRAP __VA_ARGS__
#define XIEITE_PUNWRAP(...) __VA_ARGS__

// paren.hpp - Parenthesis operations
#define XIEITE_PAREN )(
```

### Token Deferral

Deferral mechanisms control expansion timing:

```cpp
// defer.hpp - Delay expansion
#define XIEITE_DEFER(...) __VA_ARGS__ XIEITE_EAT()

// eat.hpp - Consume tokens
#define XIEITE_EAT(...)

// obstruct.hpp - Prevent immediate expansion
#define XIEITE_OBSTRUCT(...) __VA_ARGS__ XIEITE_DEFER(XIEITE_EMPTY)()
#define XIEITE_EMPTY()
```

## Advanced Token Patterns

### Stringification

Converting tokens to string literals:

```cpp
// str.hpp - Token to string conversion
#define XIEITE_STR(...) XIEITE_PSTR(__VA_ARGS__)
#define XIEITE_PSTR(...) #__VA_ARGS__

// Usage
XIEITE_STR(hello world)     // "hello world"
XIEITE_STR(42)             // "42"
```

### Token Probing

Detection of specific token patterns:

```cpp
// probe.hpp - Token detection
#define XIEITE_PROBE(...) XIEITE_SECOND(__VA_ARGS__, 1)
#define XIEITE_SECOND(a, b, ...) b

// check.hpp - Boolean conversion
#define XIEITE_CHECK(...) XIEITE_CHECK_N(__VA_ARGS__, 0,)
#define XIEITE_CHECK_N(x, n, ...) n
```

### Comma Operations

Comma manipulation for variadic processing:

```cpp
// comma.hpp - Comma handling
#define XIEITE_COMMA ,
#define XIEITE_COMMA_IF(cond) XIEITE_IF(cond)(XIEITE_COMMA, XIEITE_EMPTY)()

// cm.hpp - Comma variants
#define XIEITE_CM() ,
#define XIEITE_CM_IF(cond) XIEITE_IF(cond)(XIEITE_CM, XIEITE_EMPTY)()
```

## Expansion Control

### Evaluation Layers

Multi-pass evaluation for complex expansions:

```cpp
// eval.hpp - Force evaluation
#define XIEITE_EVAL(...) XIEITE_EVAL1024(__VA_ARGS__)
#define XIEITE_EVAL1024(...) XIEITE_EVAL512(XIEITE_EVAL512(__VA_ARGS__))
#define XIEITE_EVAL512(...) XIEITE_EVAL256(XIEITE_EVAL256(__VA_ARGS__))
// ... continues with powers of 2
```

### Scanning

Recursive macro expansion:

```cpp
// scan.hpp - Recursive scanning
#define XIEITE_SCAN(...) XIEITE_EVAL(XIEITE_SCAN1(__VA_ARGS__))
#define XIEITE_SCAN1(...) __VA_ARGS__
```

## Token Counting

### Argument Counting

Counting variadic arguments:

```cpp
// count.hpp - Count arguments
#define XIEITE_COUNT(...) \
    XIEITE_COUNT_I(__VA_ARGS__, \
        64, 63, 62, 61, 60, /* ... */ 3, 2, 1, 0)

#define XIEITE_COUNT_I( \
    _1, _2, _3, /* ... */ _64, n, ...) n
```

### Sequence Generation

Creating token sequences:

```cpp
// seq.hpp - Generate sequences
#define XIEITE_SEQ_0
#define XIEITE_SEQ_1 0
#define XIEITE_SEQ_2 XIEITE_SEQ_1, 1
#define XIEITE_SEQ_3 XIEITE_SEQ_2, 2
// ... continues
```

## Conditional Token Operations

### Token Selection

Conditional token emission:

```cpp
// if.hpp - Conditional expansion
#define XIEITE_IF(cond) XIEITE_CAT(XIEITE_IF_, cond)
#define XIEITE_IF_0(t, f) f
#define XIEITE_IF_1(t, f) t

// Usage
XIEITE_IF(1)(true_case, false_case)  // Expands to: true_case
XIEITE_IF(0)(true_case, false_case)  // Expands to: false_case
```

### Optional Tokens

Conditional token inclusion:

```cpp
// opt.hpp - Optional tokens
#define XIEITE_OPT(...) __VA_OPT__(__VA_ARGS__)
#define XIEITE_OPT_COMMA(...) __VA_OPT__(,) __VA_ARGS__
```

## Iteration Patterns

### Token Repetition

Repeating token patterns:

```cpp
// repeat.hpp - Repeat tokens
#define XIEITE_REPEAT(n, macro, ...) \
    XIEITE_CAT(XIEITE_REPEAT_, n)(macro, __VA_ARGS__)

#define XIEITE_REPEAT_0(m, ...)
#define XIEITE_REPEAT_1(m, ...) m(0, __VA_ARGS__)
#define XIEITE_REPEAT_2(m, ...) XIEITE_REPEAT_1(m, __VA_ARGS__) m(1, __VA_ARGS__)
// ... continues
```

### For-Each Operations

Applying operations to token lists:

```cpp
// each.hpp - Apply to each
#define XIEITE_EACH(macro, ...) \
    XIEITE_EVAL(XIEITE_EACH_I(macro, __VA_ARGS__))

#define XIEITE_EACH_I(macro, x, ...) \
    macro(x) \
    __VA_OPT__(XIEITE_DEFER(XIEITE_EACH_I)(macro, __VA_ARGS__))
```

## Token Transformation

### Case Operations

Case conversion patterns:

```cpp
// cases.hpp - Case transformations
#define XIEITE_CASE_UPPER_A a
#define XIEITE_CASE_UPPER_B b
// ... for all letters

#define XIEITE_TO_UPPER(x) XIEITE_CAT(XIEITE_CASE_UPPER_, x)
```

### Word Operations

Word boundary detection:

```cpp
// word.hpp - Word operations
#define XIEITE_WORD_BOUNDARY(x, y) \
    XIEITE_IF(XIEITE_IS_UPPER(y))( \
        XIEITE_IF(XIEITE_IS_LOWER(x))(_, ), \
        XIEITE_EMPTY() \
    )
```

## Advanced Techniques

### Token Lifting

Lifting values to token level:

```cpp
// lift.hpp - Lift to token space
#define XIEITE_LIFT(x) XIEITE_DEFER(x)
#define XIEITE_LIFT2(x) XIEITE_LIFT(XIEITE_LIFT(x))
```

### Token Revival

Reviving consumed tokens:

```cpp
// revive.hpp - Revive tokens
#define XIEITE_REVIVE(...) __VA_ARGS__
#define XIEITE_REVIVE_I(...) XIEITE_REVIVE(__VA_ARGS__)
```

### Structure Return

Anonymous structure creation:

```cpp
// ret_struct.hpp - Return anonymous struct
#define XIEITE_RET_STRUCT(...) \
    struct { __VA_ARGS__ }
```

## Implementation Patterns

### Indirection Layers

Using indirection for expansion control:

```cpp
// Pattern: Two-level expansion
#define DIRECT(x) x
#define INDIRECT(x) DIRECT(x)

// XIEITE equivalent
#define XIEITE_EXPAND(x) x
#define XIEITE_EXPAND_I(x) XIEITE_EXPAND(x)
```

### Token Pasting Shields

Preventing unwanted concatenation:

```cpp
// Using DEFER to prevent pasting
#define SAFE_CAT(a, b) XIEITE_CAT(a, XIEITE_DEFER(b))

// Using OBSTRUCT for complex cases
#define COMPLEX_CAT(a, b, c) \
    XIEITE_CAT(a, XIEITE_OBSTRUCT(XIEITE_CAT)(b, c))
```

### Recursion Simulation

Simulating recursion in preprocessor:

```cpp
// Recursive-like pattern
#define REC_0(x) x
#define REC_1(x) x, REC_0(x)
#define REC_2(x) x, REC_1(x)
#define REC_3(x) x, REC_2(x)

#define RECURSE(n, x) XIEITE_CAT(REC_, n)(x)
```

## Debugging Token Operations

### Token Inspection

Techniques for debugging token expansions:

```cpp
// Force visibility of expansion
#define DEBUG_EXPAND(...) #__VA_ARGS__

// Show intermediate expansion
#define DEBUG_STEP(x) DEBUG[x]

// Token counter for debugging
#define DEBUG_COUNT(...) [COUNT: XIEITE_COUNT(__VA_ARGS__)]
```

### Expansion Tracing

Tracing macro expansion:

```cpp
#ifdef DEBUG_MACROS
    #define TRACE(x) _Pragma(#x) x
#else
    #define TRACE(x) x
#endif
```

## Performance Considerations

### Expansion Depth

Managing preprocessor recursion limits:

```cpp
// Depth-limited evaluation
#define EVAL_16(...)  EVAL_8(EVAL_8(__VA_ARGS__))
#define EVAL_8(...)   EVAL_4(EVAL_4(__VA_ARGS__))
#define EVAL_4(...)   EVAL_2(EVAL_2(__VA_ARGS__))
#define EVAL_2(...)   EVAL_1(EVAL_1(__VA_ARGS__))
#define EVAL_1(...)   __VA_ARGS__
```

### Token Caching

Reusing computed token sequences:

```cpp
// Cache common sequences
#define NUMBERS_1_10 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
#define ALPHABET a, b, c, d, e, f, g, h, i, j, k, l, m, \
                n, o, p, q, r, s, t, u, v, w, x, y, z
```

## Integration with Other Systems

### Arrow Macro Support

Token manipulation in arrow macros:

```cpp
// Combining with arrow macros
#define MAKE_ARROW(name, body) \
    XIEITE_CAT(XIEITE_ARROW_, name)(body)

// Token-based arrow selection
#define SELECT_ARROW(type) \
    XIEITE_IF(XIEITE_IS_NOEX(type))( \
        XIEITE_ARROW_NOEX, \
        XIEITE_ARROW \
    )
```

### Concept Integration

Bridging tokens to concepts:

```cpp
// Generate concept from tokens
#define MAKE_CONCEPT(name, ...) \
    template<typename T> \
    concept name = __VA_ARGS__;

// Token-based constraint generation
#define ADD_CONSTRAINT(base, extra) \
    XIEITE_CAT(base, _and_) extra
```

## Best Practices

### 1. Use Indirection for Flexibility

```cpp
// Good: Allows macro arguments
#define FLEXIBLE(x) XIEITE_CAT(PREFIX_, x)

// Bad: Direct concatenation limits usage
#define INFLEXIBLE PREFIX_##x
```

### 2. Guard Against Empty Arguments

```cpp
// Safe handling of potentially empty args
#define SAFE_MACRO(...) \
    XIEITE_IF(XIEITE_COUNT(__VA_ARGS__))( \
        PROCESS(__VA_ARGS__), \
        DEFAULT_VALUE \
    )
```

### 3. Document Token Requirements

```cpp
// Document expected token format
// Expects: MACRO(token, token, ...)
// Not: MACRO("string", 123)
#define TOKEN_ONLY(...) XIEITE_EACH(PROCESS_TOKEN, __VA_ARGS__)
```

## Common Pitfalls

### Unwanted Token Pasting

```cpp
// Problem: Unintended concatenation
#define BAD(x, y) x##y##_suffix

// Solution: Use DEFER or spaces
#define GOOD(x, y) XIEITE_CAT(x, y) _suffix
```

### Expansion Order Issues

```cpp
// Problem: Order-dependent expansion
#define WRONG(x) EXPAND(x) THEN_THIS(x)

// Solution: Control evaluation order
#define RIGHT(x) XIEITE_EVAL(EXPAND(x) XIEITE_DEFER(THEN_THIS)(x))
```

### Recursion Limits

```cpp
// Problem: Exceeds recursion depth
#define DEEP_RECURSION(n) /* complex recursion */

// Solution: Use bounded iteration
#define BOUNDED(n) XIEITE_CAT(BOUNDED_, n)
```

## Summary

Token manipulation forms the backbone of XIEITE's preprocessor capabilities, enabling sophisticated compile-time computations and code generation. Through careful use of concatenation, wrapping, deferral, and evaluation control, the library achieves functionality that pushes the boundaries of what's possible in the C++ preprocessor. These techniques, while complex, provide the foundation for the library's arrow macros, conditional compilation, and metaprogramming features.