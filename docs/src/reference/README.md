# Complete API Reference

## Overview

This comprehensive API reference documents all 616 header files in the XIEITE library, organized by category. Each entry provides detailed information about functionality, parameters, return values, complexity guarantees, and usage examples.

## Organization

The API reference is structured to mirror the library's category organization:

- **[Preprocessor Utilities (`pp`)](./api/pp.md)** - 72 headers
  - Macro systems, conditional compilation, platform detection
- **[Type Traits (`trait`)](./api/trait.md)** - 276 headers
  - Concepts, type queries, SFINAE helpers, type transformations
- **[Mathematics (`math`)](./api/math.md)** - 110 headers
  - Arithmetic operations, statistics, geometry, number theory
- **[Data Structures (`data`)](./api/data.md)** - 65 headers
  - Containers, strings, iterators, algorithms
- **[Functional Programming (`fn`)](./api/fn.md)** - 35 headers
  - Function composition, currying, combinators
- **[Metaprogramming (`meta`)](./api/meta.md)** - 28 headers
  - Template manipulation, compile-time sequences
- **[System Utilities (`sys`)](./api/sys.md)** - 21 headers
  - Platform detection, environment, OS features
- **[Input/Output (`io`)](./api/io.md)** - 9 headers
  - Stream utilities, formatting, debug output

## API Documentation Format

Each API entry follows a consistent format:

### Header Information
```
Header: <category>/<name>.hpp
Since: Version X.Y.Z
Dependencies: List of required headers
```

### Synopsis
```cpp
namespace xieite {
    // Primary template/function/macro declaration
}
```

### Description
Detailed explanation of functionality and purpose.

### Template Parameters / Parameters
- `T` - Description and requirements
- `Args...` - Variadic parameter description

### Return Value
Description of return type and meaning.

### Complexity
Time and space complexity guarantees.

### Example
```cpp
// Practical usage example
```

### Notes
Additional information, caveats, or implementation details.

### See Also
Related utilities and cross-references.

## Navigation Guide

### Quick Reference by Functionality

#### Type Manipulation
- [Type Traits](./api/trait.md) - Concepts and type queries
- [Metaprogramming](./api/meta.md) - Template manipulation

#### Compile-Time Programming
- [Preprocessor](./api/pp.md) - Macro utilities
- [Data Structures](./api/data.md#compile-time) - Compile-time containers

#### Numerical Computing
- [Mathematics](./api/math.md) - Mathematical functions
- [Statistics](./api/math.md#statistics) - Statistical operations

#### Functional Programming
- [Function Utilities](./api/fn.md) - Composition and currying
- [Combinators](./api/fn.md#combinators) - Functional patterns

#### System Programming
- [System](./api/sys.md) - Platform and OS utilities
- [I/O](./api/io.md) - Input/output helpers

### Index by Header Count

| Category | Headers | Primary Focus |
|----------|---------|---------------|
| `trait` | 276 | Type traits and concepts |
| `math` | 110 | Mathematical operations |
| `pp` | 72 | Preprocessor utilities |
| `data` | 65 | Data structures |
| `fn` | 35 | Functional programming |
| `meta` | 28 | Metaprogramming |
| `sys` | 21 | System utilities |
| `io` | 9 | Input/output |
| **Total** | **616** | |

## Naming Conventions

### Abbreviations Used

| Abbreviation | Meaning | Example |
|--------------|---------|---------|
| `c` | const | `add_c`, `rm_c` |
| `v` | volatile | `add_v`, `rm_v` |
| `cv` | const volatile | `add_cv`, `rm_cv` |
| `ref` | reference | `add_ref`, `rm_ref` |
| `lref` | lvalue reference | `add_lref` |
| `rref` | rvalue reference | `add_rref` |
| `ptr` | pointer | `add_ptr`, `rm_ptr` |
| `cp` | copy | `cp_ctor`, `cp_assign` |
| `mv` | move | `mv_ctor`, `mv_assign` |
| `ctor` | constructor | `has_ctor` |
| `dtor` | destructor | `has_dtor` |
| `noex` | noexcept | `add_noex_referent` |
| `arith` | arithmetic | `is_arith` |
| `int` | integral | `is_int` |
| `fn` | function | `is_fn` |

### Prefixes

| Prefix | Purpose | Example |
|--------|---------|---------|
| `is_` | Type property query | `is_integral` |
| `has_` | Feature detection | `has_default_ctor` |
| `add_` | Add qualifier/property | `add_const` |
| `rm_` | Remove qualifier/property | `rm_reference` |
| `cp_` | Copy qualifier/property | `cp_cv` |
| `get_` | Extract property | `get_fn_ret` |
| `try_` | Safe operation with fallback | `try_signed` |
| `maybe_` | Conditional type | `maybe_ref` |

## Version History

### Version Compatibility

All APIs maintain backward compatibility within major versions:

- **Major version changes** (X.0.0): May break compatibility
- **Minor version changes** (0.X.0): Add new features, maintain compatibility
- **Patch version changes** (0.0.X): Bug fixes only

### Deprecation Policy

Deprecated APIs are marked with:
```cpp
[[deprecated("Use new_api instead")]]
```

Deprecated features are maintained for at least one minor version.

## Compiler Support

### Minimum Requirements

| Compiler | Minimum Version | Full Support |
|----------|-----------------|--------------|
| GCC | 10.1 | 11.0+ |
| Clang | 12.0 | 14.0+ |
| MSVC | 19.28 | 19.29+ |
| ICC | 2021.1 | 2021.3+ |

### Feature Requirements

| Feature | C++ Standard | Required For |
|---------|--------------|--------------|
| Concepts | C++20 | Type traits |
| Constexpr | C++20 | Compile-time evaluation |
| Ranges | C++20 | Range utilities |
| Three-way comparison | C++20 | Comparison utilities |
| Modules | C++20 | Optional module support |

## Usage Patterns

### Including Headers

```cpp
// Individual headers
#include <xieite/trait/is_integral.hpp>
#include <xieite/math/abs.hpp>

// Note: No category-level or library-wide include files exist
// Include only the specific headers you need
```

### Namespace Usage

All utilities are in the `xieite` namespace:

```cpp
using namespace xieite;  // Not recommended

// Prefer explicit namespace
xieite::is_integral<int>
xieite::abs(-42)

// Or namespace alias
namespace xe = xieite;
xe::is_integral<int>
```

### Compile-Time vs Runtime

Many utilities work at both compile-time and runtime:

```cpp
// Compile-time
constexpr auto result = xieite::abs(-42);
static_assert(result == 42);

// Runtime
auto runtime_result = xieite::abs(get_value());
```

## Performance Guarantees

### Compile-Time Performance

- **Concepts**: Cached after first evaluation
- **Type traits**: No runtime overhead
- **Constexpr functions**: Evaluated at compile-time when possible
- **Template instantiation**: Minimized through careful design

### Runtime Performance

- **Zero-overhead abstractions**: No performance penalty vs hand-written code
- **Inline functions**: Aggressive inlining for small utilities
- **Branch prediction hints**: Used where beneficial
- **SIMD**: Utilized where available and beneficial

## Error Handling

### Compile-Time Errors

Most errors are caught at compile-time through:
- Concept constraints
- Static assertions
- SFINAE
- Template instantiation failures

### Runtime Errors

Runtime errors follow these patterns:
- **Exceptions**: Thrown for recoverable errors (when exceptions enabled)
- **Optional returns**: For operations that may fail
- **Error codes**: For system operations
- **Assertions**: For debug-mode checking

## Thread Safety

### General Guidelines

- **Const operations**: Thread-safe
- **Non-const operations**: Not thread-safe unless documented
- **Global state**: Avoided where possible
- **Static initialization**: Thread-safe (C++11 guarantee)

## Best Practices

### 1. Use Concepts for Constraints

```cpp
// Good
template<xieite::is_integral T>
void process(T value);

// Avoid
template<typename T>
void process(T value) {
    static_assert(std::is_integral_v<T>);
}
```

### 2. Prefer Compile-Time Evaluation

```cpp
// Good - compile-time when possible
constexpr auto result = xieite::factorial<int>[5];

// Less optimal - always runtime
auto result = compute_factorial(5);
```

### 3. Use Appropriate Abstractions

```cpp
// Use high-level utilities when available
auto sorted = xieite::sort(container);

// Instead of reimplementing
std::sort(container.begin(), container.end());
```

## Finding Information

### Search Strategies

1. **By functionality**: Use category pages
2. **By name**: Use alphabetical index
3. **By header**: Navigate directly to file
4. **By concept**: Check trait/ category
5. **By pattern**: See examples section

### Cross-References

Each API entry includes:
- Related utilities in same category
- Utilities in other categories
- Standard library equivalents
- Alternative approaches

## Contributing

For API additions or modifications:
1. Follow existing naming conventions
2. Provide comprehensive documentation
3. Include usage examples
4. Add appropriate tests
5. Update cross-references

## Support

- **Documentation issues**: Report in GitHub issues
- **API questions**: Check examples first
- **Performance concerns**: See performance section
- **Compatibility**: Check compiler support matrix

---

*Select a category above to browse the complete API reference for that section.*
