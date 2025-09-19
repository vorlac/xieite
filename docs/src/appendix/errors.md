# Error Reference

This document provides a comprehensive reference for errors, warnings, and diagnostic messages that may be encountered when using XIEITE, along with their causes and solutions.

## Compilation Errors

### Template and Concept Errors

#### Error: Concept requirement not satisfied
```
error: the concept 'xieite::is_arith<T>' is not satisfied
```

**Cause**: Attempting to use an arithmetic-constrained template with a non-arithmetic type.

**Example**:
```cpp
#include <xieite/trait/is_arith.hpp>
#include <xieite/math/abs.hpp>

template<xieite::is_arith T>
auto square(T value) { return value * value; }

int main() {
    std::string str = "hello";
    auto result = square(str); // Error: std::string is not arithmetic
}
```

**Solution**:
```cpp
// Use appropriate type
auto result = square(42);     // OK: int is arithmetic
auto result = square(3.14);   // OK: double is arithmetic

// Or check type before calling
if constexpr (xieite::is_arith<decltype(value)>) {
    auto result = square(value);
}
```

#### Error: Template recursion depth exceeded
```
error: template instantiation depth exceeds maximum of 1024
```

**Cause**: Recursive template instantiation without proper termination condition.

**Example**:
```cpp
template<std::size_t N>
struct factorial {
    static constexpr std::size_t value = N * factorial<N-1>::value; // Missing base case
};
```

**Solution**:
```cpp
template<std::size_t N>
struct factorial {
    static constexpr std::size_t value = N <= 1 ? 1 : N * factorial<N-1>::value;
};

// Or use XIEITE's safer alternatives
#include <xieite/fn/repeat.hpp>
```

#### Error: No matching function for call
```
error: no matching function for call to 'xieite::abs(bool)'
```

**Cause**: Calling XIEITE functions with unsupported types.

**Solution**:
```cpp
#include <xieite/trait/is_arith.hpp>

// Check type constraints
template<typename T>
auto safe_abs(T value) {
    if constexpr (xieite::is_arith<T>) {
        return xieite::abs(value);
    } else {
        static_assert(xieite::is_arith<T>, "Type must be arithmetic");
    }
}
```

### Preprocessor Errors

#### Error: Macro redefinition
```
warning: 'XIEITE_PLATFORM_WINDOWS' macro redefined
```

**Cause**: Multiple definitions of the same macro, often from mixing manual definitions with XIEITE's automatic detection.

**Solution**:
```cpp
// Don't manually define platform macros
// #define XIEITE_PLATFORM_WINDOWS 1  // Remove this

// Let XIEITE handle detection
#include <xieite/pp/platform.hpp>
#include <xieite/pp/if.hpp>

XIEITE_PP_IF(XIEITE_PLATFORM_WINDOWS)(
    // Windows-specific code
)
```

#### Error: Invalid preprocessor directive
```
error: invalid preprocessing directive #XIEITE_PP_IF
```

**Cause**: Incorrect macro usage or missing includes.

**Solution**:
```cpp
// Include required headers
#include <xieite/pp/if.hpp>

// Correct usage
XIEITE_PP_IF(condition)(
    // code when condition is true
)

// Not this:
// #XIEITE_PP_IF(condition)  // Invalid syntax
```

#### Error: Variadic macro issues
```
error: expected expression before ')' token
```

**Cause**: Empty variadic macro arguments, especially on older compilers.

**Solution**:
```cpp
// Use XIEITE's variadic helpers
#include <xieite/pp/each.hpp>

// Avoid empty arguments
XIEITE_PP_EACH(MACRO, arg1, arg2)  // Good
// XIEITE_PP_EACH(MACRO,)          // Problematic
```

### Arrow Macro Errors

#### Error: Arrow macro syntax issues
```
error: expected ';' after expression
```

**Cause**: Incorrect arrow macro usage or missing includes.

**Example**:
```cpp
// Missing include
auto func(int x) XIEITE_ARROW(x * 2)  // Error
```

**Solution**:
```cpp
#include <xieite/pp/arrow.hpp>

// Correct usage
auto func(int x)
XIEITE_ARROW(x * 2)

// For complex expressions, use braces
auto complex_func(int x)
XIEITE_ARROW({
    int temp = x * 2;
    return temp + 1;
})
```

#### Error: Arrow macro with void return
```
error: inconsistent deduction for auto return type
```

**Cause**: Using XIEITE_ARROW with statements instead of expressions.

**Solution**:
```cpp
// For void functions, use regular syntax
void print_value(int x) {
    std::cout << x << std::endl;
}

// Or use arrow macro with void expression
auto print_value(int x)
XIEITE_ARROW((void)(std::cout << x << std::endl))
```

## Linker Errors

### Multiple Definition Errors
```
error: multiple definition of 'symbol_name'
```

**Cause**: XIEITE is header-only, but sometimes symbols can be duplicated.

**Solution**:
```cpp
// Ensure proper inline usage
inline auto global_function() {
    // implementation
}

// Or use anonymous namespace for internal linkage
namespace {
    auto internal_function() {
        // implementation
    }
}
```

### Template Instantiation Errors
```
undefined reference to 'template_function<specific_type>'
```

**Cause**: Missing template instantiation or header inclusion.

**Solution**:
```cpp
// Ensure all required headers are included
#include <xieite/trait/is_arith.hpp>  // For concepts
#include <xieite/math/abs.hpp>        // For specific functions

// For explicit instantiation (if needed):
template auto specific_function<int>(int) -> int;
```

## Runtime Errors

### Assertion Failures
```
Assertion failed: condition, file: example.cpp, line: 42
```

**Cause**: XIEITE static assertions or runtime checks failing.

**Example**:
```cpp
#include <xieite/data/fixed_array.hpp>

xieite::fixed_array<int, 5> arr;
int value = arr[10]; // Runtime error: out of bounds
```

**Solution**:
```cpp
// Use safe access methods
auto safe_value = arr.at(index); // Throws on out of bounds

// Or check bounds
if (index < arr.size()) {
    auto value = arr[index];
}
```

### Memory Access Violations

**Cause**: Incorrect usage of XIEITE containers or utilities.

**Solution**:
```cpp
// Always initialize containers properly
xieite::fixed_array<int, 5> arr{1, 2, 3, 4, 5};

// Use RAII patterns
#include <xieite/fn/scope_guard.hpp>
auto guard = xieite::scope_guard([]() {
    // Cleanup code
});
```

## Warning Messages

### Unused Variable Warnings
```
warning: unused variable 'name'
```

**Cause**: Variables created by XIEITE macros but not used.

**Solution**:
```cpp
// Use [[maybe_unused]] attribute
[[maybe_unused]] auto result = xieite_function();

// Or explicitly use the variable
auto result = xieite_function();
(void)result; // Suppress warning
```

### Deprecation Warnings
```
warning: 'old_function' is deprecated
```

**Cause**: Using deprecated XIEITE features.

**Solution**: Check migration guide for replacement functions and update code accordingly.

### Performance Warnings
```
warning: large object passed by value
```

**Cause**: Inefficient parameter passing with XIEITE utilities.

**Solution**:
```cpp
// Use const references for large objects
template<typename T>
auto process_large_object(const T& obj) {
    // Process obj
}
```

## Platform-Specific Errors

### Windows-Specific Issues

#### MSVC Template Issues
```
error C2039: 'type': is not a member of 'std'
```

**Solution**:
```cpp
// Include proper headers for MSVC
#include <type_traits>
#include <concepts>

// Use XIEITE compatibility layers
#include <xieite/trait/is_arith.hpp>
```

#### Windows Header Conflicts
```
error: 'min' was not declared in this scope
```

**Solution**:
```cpp
// Define NOMINMAX before Windows headers
#define NOMINMAX
#include <windows.h>

// Or use XIEITE utilities
#include <xieite/math/min.hpp>
auto result = xieite::min(a, b);
```

### Unix/Linux-Specific Issues

#### GCC Version Compatibility
```
error: 'concepts' header not found
```

**Solution**:
```cpp
// Check GCC version and use appropriate headers
#if __GNUC__ >= 10
    #include <concepts>
#else
    // Use XIEITE fallbacks
    #include <xieite/trait/is_arith.hpp>
#endif
```

### macOS-Specific Issues

#### Clang Compatibility
```
error: no template named 'concept'
```

**Solution**: Update to newer Clang version or use XIEITE's compatibility shims.

## Debugging Techniques

### Compile-Time Debugging

```cpp
// Use static_assert for debugging
template<typename T>
void debug_type() {
    static_assert(false, "T is instantiated with this type");
}

// Inspect template instantiation
template<auto Value>
struct value_inspector {
    static_assert(Value != Value, "Value inspection");
};
```

### Runtime Debugging

```cpp
#include <xieite/pp/debug.hpp>

// Use XIEITE debug macros
XIEITE_DEBUG_PRINT("Variable value:", variable);

// Conditional debugging
#ifdef XIEITE_DEBUG_BUILD
    // Debug-only code
#endif
```

### Template Error Reduction

```cpp
// Use concepts to improve error messages
template<xieite::is_arith T>
auto better_error_function(T value) {
    return value * 2;
}

// Instead of complex SFINAE that produces cryptic errors
template<typename T>
auto complex_sfinae_function(T value)
    -> std::enable_if_t<std::is_arithmetic_v<T>, T> {
    return value * 2;
}
```

## Error Prevention

### Best Practices

1. **Include Guard**: Always use proper includes
```cpp
#include <xieite/trait/is_arith.hpp>  // Before using is_arith
#include <xieite/pp/arrow.hpp>        // Before using arrow macros
```

2. **Type Safety**: Use concepts and constraints
```cpp
template<xieite::is_arith T>
auto safe_function(T value) { /* implementation */ }
```

3. **Platform Detection**: Use XIEITE's platform macros
```cpp
#include <xieite/pp/platform.hpp>
XIEITE_PP_IF(XIEITE_PLATFORM_WINDOWS)(
    // Platform-specific code
)
```

4. **Error Handling**: Use scope guards and RAII
```cpp
#include <xieite/fn/scope_guard.hpp>
auto guard = xieite::scope_guard(cleanup_function);
```

### Common Pitfalls

1. **Mixing C++17 and C++20 features**: Ensure consistent C++20 usage
2. **Platform assumption**: Always use cross-platform XIEITE utilities
3. **Template complexity**: Keep templates simple and well-constrained
4. **Header dependencies**: Include all necessary XIEITE headers

This error reference should help diagnose and resolve most issues encountered when working with XIEITE. For additional help, consult the specific category documentation or file issues in the project repository.