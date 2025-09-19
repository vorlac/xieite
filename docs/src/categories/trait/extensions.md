# STL Extensions

## Overview

XIEITE extends the standard library's type traits with additional utilities for type manipulation, offering more granular control over cv-qualifiers, references, and integral sign conversions. These extensions fill gaps in the standard library and provide composable type transformation utilities.

## Safe Sign Conversion

### Try Signed/Unsigned
Implementation: `include/xieite/trait/try_signed.hpp` (line 9), `include/xieite/trait/try_unsigned.hpp` (line 9)

```cpp
template<typename T>
using try_signed = /* converts to signed if unsigned, otherwise unchanged */;

template<typename T>
using try_unsigned = /* converts to unsigned if signed, otherwise unchanged */;
```

Unlike std::make_signed/make_unsigned, these only convert when safe to do so.

## CV-Qualifier Management

### Granular CV Addition
Implementation: `include/xieite/trait/add_c.hpp` (line 9), `include/xieite/trait/add_v.hpp`, `include/xieite/trait/add_cv.hpp` (line 9)

```cpp
template<typename T>
using add_c = /* add const qualifier */;

template<typename T>
using add_v = /* add volatile qualifier */;

template<typename T>
using add_cv = /* add const volatile qualifiers */;
```

### CV-Qualifier Copying
Implementation: `include/xieite/trait/cp_cv.hpp`, `include/xieite/trait/cp_c.hpp`

```cpp
template<typename T, typename U>
using cp_cv = /* copy cv-qualifiers from U to T */;

template<typename T, typename U>
using cp_c = /* copy const qualifier from U to T */;
```

## Reference Management

### Reference Addition
Multiple reference addition utilities extending std::add_lvalue_reference:

```cpp
template<typename T>
using add_lref = /* add lvalue reference */;

template<typename T>
using add_rref = /* add rvalue reference */;

template<typename T, typename U>
using add_ref = /* add reference type from U to T */;
```

### Reference Copying
Implementation: `include/xieite/trait/cp_ref.hpp`, `include/xieite/trait/cp_cvref.hpp` (line 9)

```cpp
template<typename T, typename U>
using cp_ref = /* copy reference type from U to T */;

template<typename T, typename U>
using cp_cvref = /* copy cv-qualifiers and reference from U to T */;
```

### Combined CV-Reference Operations
Implementation: `include/xieite/trait/add_cvref.hpp` (line 9)

```cpp
template<typename T, typename U>
using add_cvref = /* add cv-qualifiers and reference type from U to T */;
```

## Usage Examples

### Safe Integral Sign Conversion
```cpp
#include <xieite/trait/try_signed.hpp>
#include <xieite/trait/try_unsigned.hpp>

template<typename T>
void process_number(T value) {
    // Safe conversion to unsigned (only if signed)
    using unsigned_t = xieite::try_unsigned<T>;
    unsigned_t abs_value = static_cast<unsigned_t>(std::abs(value));

    // Safe conversion to signed (only if unsigned)
    using signed_t = xieite::try_signed<T>;
    signed_t signed_value = static_cast<signed_t>(value);
}

// Examples
static_assert(std::same_as<xieite::try_signed<unsigned int>, int>);
static_assert(std::same_as<xieite::try_signed<int>, int>);  // No change
static_assert(std::same_as<xieite::try_unsigned<int>, unsigned int>);
static_assert(std::same_as<xieite::try_unsigned<unsigned>, unsigned>);  // No change
```

### CV-Qualifier Management
```cpp
#include <xieite/trait/add_cv.hpp>
#include <xieite/trait/cp_cv.hpp>

template<typename T>
void demonstrate_cv() {
    // Add qualifiers
    using const_t = xieite::add_c<T>;           // T -> const T
    using volatile_t = xieite::add_v<T>;        // T -> volatile T
    using cv_t = xieite::add_cv<T>;             // T -> const volatile T

    // Copy qualifiers
    const volatile int source{};
    using copied = xieite::cp_cv<T, decltype(source)>; // Copy cv from source to T
}

// Examples
static_assert(std::same_as<xieite::add_c<int>, const int>);
static_assert(std::same_as<xieite::cp_cv<int, const double>, const int>);
```

### Reference Type Manipulation
```cpp
#include <xieite/trait/cp_ref.hpp>
#include <xieite/trait/add_cvref.hpp>

template<typename T, typename U>
void reference_operations() {
    // Copy reference type
    using same_ref = xieite::cp_ref<T, U>;      // Copy reference from U to T

    // Copy cv-qualifiers and reference
    using same_cvref = xieite::cp_cvref<T, U>;  // Copy cv + ref from U to T

    // Add cv and reference from another type
    using combined = xieite::add_cvref<T, U>;   // Add cv + ref from U to T
}

// Examples
static_assert(std::same_as<xieite::cp_ref<int, double&>, int&>);
static_assert(std::same_as<xieite::cp_cvref<int, const double&>, const int&>);
```

### Perfect Forwarding Helpers
```cpp
template<typename T, typename... Args>
auto make_like(Args&&... args) {
    // Preserve cv-qualifiers and reference category
    using result_t = xieite::cp_cvref<
        std::remove_reference_t<T>,
        T
    >;

    return result_t{std::forward<Args>(args)...};
}

// Usage
const int& source = 42;
auto result = make_like<decltype(source)>(100);  // Returns const int&
```

## Advanced Patterns

### Type Trait Composition
```cpp
// Combine multiple transformations
template<typename T, typename Model>
using transform_like = xieite::cp_cvref<
    xieite::try_unsigned<std::decay_t<T>>,
    Model
>;

// Apply model's qualifiers to unsigned version of T
using result = transform_like<int, const volatile double&>;
// Result: const volatile unsigned int&
```

### Conditional Qualifiers
```cpp
template<typename T, bool add_const>
using maybe_const = std::conditional_t<
    add_const,
    xieite::add_c<T>,
    T
>;

// Template specialization helper
template<typename T>
struct qualified_variant {
    using mutable_t = T;
    using const_t = xieite::add_c<T>;
    using volatile_t = xieite::add_v<T>;
    using cv_t = xieite::add_cv<T>;
};
```

### Reference Category Preservation
```cpp
template<typename T>
class wrapper {
    T value_;

public:
    template<typename U>
    auto get_as() -> xieite::cp_ref<U, T> {
        if constexpr (std::is_lvalue_reference_v<T>) {
            return static_cast<U&>(value_);
        } else {
            return static_cast<U&&>(value_);
        }
    }
};
```

## Implementation Details

### Safe Conversion Strategy
- `try_signed` (try_signed.hpp:9): Uses `std::conditional_t` with `xieite::is_unsigned` check
- `try_unsigned` (try_unsigned.hpp:9): Uses `std::signed_integral` concept for safety
- Only applies conversion when the source type matches the expected category

### CV-Qualifier Operations
- `add_c` (add_c.hpp:9): Uses `cp_ref` with `const rm_ref<T>` to preserve references
- `add_cv` (add_cv.hpp:9): Composes `add_c` and `add_v` for combined effect
- `cp_cv` (cp_cv.hpp:9): Copies qualifiers while preserving target's reference category

### Reference Preservation
- `cp_ref` preserves cv-qualifiers while copying reference type
- `cp_cvref` (cp_cvref.hpp:9): Combines `cp_cv` and `cp_ref` operations
- All operations maintain type safety and avoid invalid combinations

## Relationship to Standard Library

### Extensions vs Standard Traits
| Standard Library | XIEITE Extension | Key Difference |
|------------------|------------------|----------------|
| `std::make_signed` | `xieite::try_signed` | Safe conversion (no-op if already signed) |
| `std::make_unsigned` | `xieite::try_unsigned` | Safe conversion (no-op if already unsigned) |
| `std::add_cv` | `xieite::add_cv` | Reference-aware implementation |
| None | `xieite::cp_cvref` | Copy qualifiers between types |

### Composition Benefits
XIEITE traits compose naturally:
```cpp
// Standard library requires multiple steps
using step1 = std::remove_reference_t<T>;
using step2 = std::add_const_t<step1>;
using result = std::add_lvalue_reference_t<step2>;

// XIEITE allows direct composition
using result = xieite::add_cvref<std::remove_reference_t<T>, const U&>;
```

## Performance Considerations

- All operations are compile-time only (zero runtime cost)
- Template instantiation depth kept minimal through careful composition
- Optimized for common use cases (cv-ref copying, safe conversions)
- No recursive template patterns that could cause compilation slowdown

## Best Practices

1. **Prefer safe conversions** - Use `try_*` variants over `std::make_*`
2. **Compose operations** - Combine traits for complex transformations
3. **Preserve reference categories** - Use cv-ref copying to maintain semantics
4. **Document type transformations** - Complex compositions need clear documentation

## See Also

- [Type Classification](./classification.md) - Type category detection
- [Type Queries](./queries.md) - Type property inspection
- [Custom Traits](./custom.md) - Creating new type traits
- [Type Traits API Reference](../../reference/api/trait.md)