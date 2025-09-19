# Type Traits API Reference

## Overview

The type traits category is XIEITE's largest component with 276 header files, providing comprehensive type introspection, transformation, and concept-based constraints for modern C++ metaprogramming.

## Organization

The 276 trait headers are organized into logical groups:

- **Type Modifications** (90+ headers): Add, remove, copy, and transform type qualifiers
- **Type Queries** (150+ headers): Check type properties and capabilities
- **Type Relationships** (20+ headers): Examine type conversions and inheritance
- **Type Extraction** (15+ headers): Extract properties and nested types

## Naming Convention Reference

| Prefix | Meaning | Example |
|--------|---------|---------|
| `add_` | Add qualifier/property | `add_c`, `add_ptr` |
| `rm_` | Remove qualifier/property | `rm_cv`, `rm_ref` |
| `cp_` | Copy qualifier/property | `cp_cv`, `cp_ref` |
| `is_` | Query type property | `is_integral`, `is_const` |
| `has_` | Check for capability | `has_default_ctor` |
| `get_` | Extract property | `get_fn_ret` |
| `try_` | Safe operation | `try_signed` |
| `maybe_` | Conditional type | `maybe_ref` |

| Suffix | Meaning | Example |
|--------|---------|---------|
| `_c` | const | `add_c`, `is_c` |
| `_v` | volatile | `add_v`, `rm_v` |
| `_cv` | const volatile | `add_cv`, `rm_cv` |
| `_ref` | reference | `add_ref`, `is_ref` |
| `_lref` | lvalue reference | `add_lref`, `is_lref` |
| `_rref` | rvalue reference | `add_rref`, `is_rref` |
| `_ptr` | pointer | `add_ptr`, `rm_ptr` |
| `_referent` | operate on referred type | `add_c_referent` |

## Core Type Modification Traits

### Adding Qualifiers

### `add_c`
- **Header**: `trait/add_c.hpp`
- **Synopsis**: `template<typename T> using add_c = T const;`
- **Purpose**: Add const qualifier
- **Example**: `add_c<int>` → `const int`

### `add_v`
- **Header**: `trait/add_v.hpp`
- **Synopsis**: `template<typename T> using add_v = T volatile;`
- **Purpose**: Add volatile qualifier
- **Example**: `add_v<int>` → `volatile int`

### `add_cv`
- **Header**: `trait/add_cv.hpp`
- **Synopsis**: `template<typename T> using add_cv = T const volatile;`
- **Purpose**: Add const and volatile
- **Example**: `add_cv<int>` → `const volatile int`

### `add_lref`
- **Header**: `trait/add_lref.hpp`
- **Synopsis**: `template<typename T> using add_lref = T&;`
- **Purpose**: Add lvalue reference
- **Example**: `add_lref<int>` → `int&`

### `add_rref`
- **Header**: `trait/add_rref.hpp`
- **Synopsis**: `template<typename T> using add_rref = T&&;`
- **Purpose**: Add rvalue reference
- **Example**: `add_rref<int>` → `int&&`

### `add_ptr`
- **Header**: `trait/add_ptr.hpp`
- **Synopsis**: `template<typename T> using add_ptr = T*;`
- **Purpose**: Add pointer level
- **Example**: `add_ptr<int>` → `int*`

### Referent Operations

These unique operations modify the type that a reference refers to:

### `add_c_referent`
- **Header**: `trait/add_c_referent.hpp`
- **Synopsis**: Adds const to the referent of a reference type
- **Example**: `add_c_referent<int&>` → `const int&`

### `add_v_referent`
- **Header**: `trait/add_v_referent.hpp`
- **Synopsis**: Adds volatile to the referent
- **Example**: `add_v_referent<int&>` → `volatile int&`

### `add_noex_referent`
- **Header**: `trait/add_noex_referent.hpp`
- **Synopsis**: Adds noexcept to function referent
- **Example**: `add_noex_referent<void(&)()>` → `void(&)() noexcept`

### Removing Qualifiers

### `rm_c`
- **Header**: `trait/rm_c.hpp`
- **Synopsis**: Removes const qualifier
- **Example**: `rm_c<const int>` → `int`

### `rm_v`
- **Header**: `trait/rm_v.hpp`
- **Synopsis**: Removes volatile qualifier
- **Example**: `rm_v<volatile int>` → `int`

### `rm_cv`
- **Header**: `trait/rm_cv.hpp`
- **Synopsis**: Removes const and volatile
- **Example**: `rm_cv<const volatile int>` → `int`

### `rm_ref`
- **Header**: `trait/rm_ref.hpp`
- **Synopsis**: Removes reference
- **Example**: `rm_ref<int&>` → `int`

### `rm_ptr`
- **Header**: `trait/rm_ptr.hpp`
- **Synopsis**: Removes one pointer level
- **Example**: `rm_ptr<int*>` → `int`

### `rm_cvref`
- **Header**: `trait/rm_cvref.hpp`
- **Synopsis**: Removes cv-qualifiers and reference
- **Example**: `rm_cvref<const int&>` → `int`

### Copying Qualifiers

### `cp_c`
- **Header**: `trait/cp_c.hpp`
- **Synopsis**: `template<typename From, typename To> using cp_c`
- **Purpose**: Copy const from From to To
- **Example**: `cp_c<const int, float>` → `const float`

### `cp_v`
- **Header**: `trait/cp_v.hpp`
- **Synopsis**: Copy volatile qualifier
- **Example**: `cp_v<volatile int, float>` → `volatile float`

### `cp_cv`
- **Header**: `trait/cp_cv.hpp`
- **Synopsis**: Copy const and volatile
- **Example**: `cp_cv<const volatile int, float>` → `const volatile float`

### `cp_ref`
- **Header**: `trait/cp_ref.hpp`
- **Synopsis**: Copy reference type
- **Example**: `cp_ref<int&, float>` → `float&`

## Type Query Concepts

### Fundamental Type Checks

### `is_arith`
- **Header**: `trait/is_arith.hpp`
- **Synopsis**: `template<typename T> concept is_arith = std::integral<T> || std::floating_point<T>;`
- **Purpose**: Check if arithmetic type
- **Example**: `is_arith<int>` → `true`

### `is_int`
- **Header**: `trait/is_int.hpp`
- **Synopsis**: `template<typename T> concept is_int = std::integral<T>;`
- **Purpose**: Check if integral type
- **Example**: `is_int<char>` → `true`

### `is_float`
- **Header**: `trait/is_float.hpp`
- **Synopsis**: Check if floating-point type
- **Example**: `is_float<double>` → `true`

### `is_void`
- **Header**: `trait/is_void.hpp`
- **Synopsis**: Check if void type
- **Example**: `is_void<void>` → `true`

### Qualifier Checks

### `is_c`
- **Header**: `trait/is_c.hpp`
- **Synopsis**: Check if const-qualified
- **Example**: `is_c<const int>` → `true`

### `is_v`
- **Header**: `trait/is_v.hpp`
- **Synopsis**: Check if volatile-qualified
- **Example**: `is_v<volatile int>` → `true`

### `is_cv`
- **Header**: `trait/is_cv.hpp`
- **Synopsis**: Check if const volatile
- **Example**: `is_cv<const volatile int>` → `true`

### Reference Checks

### `is_lref`
- **Header**: `trait/is_lref.hpp`
- **Synopsis**: Check if lvalue reference
- **Example**: `is_lref<int&>` → `true`

### `is_rref`
- **Header**: `trait/is_rref.hpp`
- **Synopsis**: Check if rvalue reference
- **Example**: `is_rref<int&&>` → `true`

### `is_ref`
- **Header**: `trait/is_ref.hpp`
- **Synopsis**: Check if any reference
- **Example**: `is_ref<int&>` → `true`

### Composite Reference Checks

### `is_clref`
- **Header**: `trait/is_clref.hpp`
- **Synopsis**: Check if const lvalue reference
- **Example**: `is_clref<const int&>` → `true`

### `is_crref`
- **Header**: `trait/is_crref.hpp`
- **Synopsis**: Check if const rvalue reference
- **Example**: `is_crref<const int&&>` → `true`

### `is_cvlref`
- **Header**: `trait/is_cvlref.hpp`
- **Synopsis**: Check if const volatile lvalue reference
- **Example**: `is_cvlref<const volatile int&>` → `true`

## Constructor and Assignment Detection

### Constructor Traits

### `has_default_ctor`
- **Header**: `trait/has_default_ctor.hpp`
- **Synopsis**: Check for default constructor
- **Example**: `has_default_ctor<std::vector<int>>` → `true`

### `has_cp_ctor`
- **Header**: `trait/has_cp_ctor.hpp`
- **Synopsis**: Check for copy constructor
- **Example**: `has_cp_ctor<std::string>` → `true`

### `has_mv_ctor`
- **Header**: `trait/has_mv_ctor.hpp`
- **Synopsis**: Check for move constructor
- **Example**: `has_mv_ctor<std::unique_ptr<int>>` → `true`

### `has_ctor`
- **Header**: `trait/has_ctor.hpp`
- **Synopsis**: `template<typename T, typename... Args> concept has_ctor`
- **Purpose**: Check for specific constructor
- **Example**: `has_ctor<std::string, const char*>` → `true`

### `has_brace_ctor`
- **Header**: `trait/has_brace_ctor.hpp`
- **Synopsis**: Check for brace initialization
- **Example**: `has_brace_ctor<Point, int, int>` → `true`

### Assignment Traits

### `has_cp_assign`
- **Header**: `trait/has_cp_assign.hpp`
- **Synopsis**: Check for copy assignment
- **Example**: `has_cp_assign<std::string>` → `true`

### `has_mv_assign`
- **Header**: `trait/has_mv_assign.hpp`
- **Synopsis**: Check for move assignment
- **Example**: `has_mv_assign<std::vector<int>>` → `true`

### Noexcept Variants

### `has_noex_default_ctor`
- **Header**: `trait/has_noex_default_ctor.hpp`
- **Synopsis**: Check for noexcept default constructor
- **Example**: `has_noex_default_ctor<int>` → `true`

### `has_noex_cp_ctor`
- **Header**: `trait/has_noex_cp_ctor.hpp`
- **Synopsis**: Check for noexcept copy constructor

### `has_noex_mv_ctor`
- **Header**: `trait/has_noex_mv_ctor.hpp`
- **Synopsis**: Check for noexcept move constructor

### `has_noex_cp_assign`
- **Header**: `trait/has_noex_cp_assign.hpp`
- **Synopsis**: Check for noexcept copy assignment

### `has_noex_mv_assign`
- **Header**: `trait/has_noex_mv_assign.hpp`
- **Synopsis**: Check for noexcept move assignment

### Destructor Properties

### `has_dtor`
- **Header**: `trait/has_dtor.hpp`
- **Synopsis**: Check if has destructor
- **Example**: `has_dtor<std::string>` → `true`

### `has_virtual_dtor`
- **Header**: `trait/has_virtual_dtor.hpp`
- **Synopsis**: Check for virtual destructor
- **Example**: `has_virtual_dtor<std::exception>` → `true`

### `has_noex_dtor`
- **Header**: `trait/has_noex_dtor.hpp`
- **Synopsis**: Check for noexcept destructor

### `has_trivial_dtor`
- **Header**: `trait/has_trivial_dtor.hpp`
- **Synopsis**: Check for trivial destructor
- **Example**: `has_trivial_dtor<int>` → `true`

## Triviality Checks

### `has_trivial_default_ctor`
- **Header**: `trait/has_trivial_default_ctor.hpp`
- **Synopsis**: Check for trivial default constructor

### `has_trivial_cp_ctor`
- **Header**: `trait/has_trivial_cp_ctor.hpp`
- **Synopsis**: Check for trivial copy constructor

### `has_trivial_mv_ctor`
- **Header**: `trait/has_trivial_mv_ctor.hpp`
- **Synopsis**: Check for trivial move constructor

### `has_trivial_cp_assign`
- **Header**: `trait/has_trivial_cp_assign.hpp`
- **Synopsis**: Check for trivial copy assignment

### `has_trivial_mv_assign`
- **Header**: `trait/has_trivial_mv_assign.hpp`
- **Synopsis**: Check for trivial move assignment

## Type Relationships

### Conversion Traits

### `is_conv_to`
- **Header**: `trait/is_conv_to.hpp`
- **Synopsis**: `template<typename From, typename To> concept is_conv_to`
- **Purpose**: Check convertibility
- **Example**: `is_conv_to<int, double>` → `true`

### `is_noex_conv_to`
- **Header**: `trait/is_noex_conv_to.hpp`
- **Synopsis**: Check noexcept convertibility

### `is_impl_conv_to`
- **Header**: `trait/is_impl_conv_to.hpp`
- **Synopsis**: Check implicit convertibility

### Inheritance Traits

### `is_base`
- **Header**: `trait/is_base.hpp`
- **Synopsis**: `template<typename Base, typename Derived> concept is_base`
- **Purpose**: Check if Base is base of Derived
- **Example**: `is_base<std::exception, std::runtime_error>` → `true`

### `is_derived_from`
- **Header**: `trait/is_derived_from.hpp`
- **Synopsis**: Check derivation relationship

### `is_base_any`
- **Header**: `trait/is_base_any.hpp`
- **Synopsis**: Check if base of any in list

## Container and Range Concepts

### `is_range`
- **Header**: `trait/is_range.hpp`
- **Synopsis**: Check if range type
- **Example**: `is_range<std::vector<int>>` → `true`

### `is_sized_range`
- **Header**: `trait/is_sized_range.hpp`
- **Synopsis**: Check if sized range

### `is_input_range`
- **Header**: `trait/is_input_range.hpp`
- **Synopsis**: Check if input range

### `is_fwd_range`
- **Header**: `trait/is_fwd_range.hpp`
- **Synopsis**: Check if forward range

### `is_bidirect_range`
- **Header**: `trait/is_bidirect_range.hpp`
- **Synopsis**: Check if bidirectional range

### `is_random_access_range`
- **Header**: `trait/is_random_access_range.hpp`
- **Synopsis**: Check if random access range

### `is_contig_range`
- **Header**: `trait/is_contig_range.hpp`
- **Synopsis**: Check if contiguous range

## Stream Concepts

### `is_streamable_out`
- **Header**: `trait/is_streamable_out.hpp`
- **Synopsis**: Check if output streamable
- **Example**: `is_streamable_out<int>` → `true`

### `is_streamable_in`
- **Header**: `trait/is_streamable_in.hpp`
- **Synopsis**: Check if input streamable

## Function Traits

### `is_fn`
- **Header**: `trait/is_fn.hpp`
- **Synopsis**: Check if function type

### `is_fn_ptr`
- **Header**: `trait/is_fn_ptr.hpp`
- **Synopsis**: Check if function pointer

### `is_mem_fn_ptr`
- **Header**: `trait/is_mem_fn_ptr.hpp`
- **Synopsis**: Check if member function pointer

### `is_stdmem_func_ptr`
- **Header**: `trait/is_stdmem_func_ptr.hpp`
- **Synopsis**: Check if standard member function pointer

### `get_fn_ret`
- **Header**: `trait/get_fn_ret.hpp`
- **Synopsis**: Extract function return type

### `get_fn_args`
- **Header**: `trait/get_fn_args.hpp`
- **Synopsis**: Extract function argument types

## Special Type Properties

### `is_complete`
- **Header**: `trait/is_complete.hpp`
- **Synopsis**: Check if type is complete

### `is_decayed`
- **Header**: `trait/is_decayed.hpp`
- **Synopsis**: Check if already decayed

### `is_empty`
- **Header**: `trait/is_empty.hpp`
- **Synopsis**: Check if empty class

### `is_final`
- **Header**: `trait/is_final.hpp`
- **Synopsis**: Check if final class

### `is_abstract`
- **Header**: `trait/is_abstract.hpp`
- **Synopsis**: Check if abstract class

### `is_aggregate`
- **Header**: `trait/is_aggregate.hpp`
- **Synopsis**: Check if aggregate type

### `is_polymorphic`
- **Header**: `trait/is_polymorphic.hpp`
- **Synopsis**: Check if polymorphic class

### `is_standard_layout`
- **Header**: `trait/is_standard_layout.hpp`
- **Synopsis**: Check if standard layout

### `is_trivial`
- **Header**: `trait/is_trivial.hpp`
- **Synopsis**: Check if trivial type

### `is_trivially_copyable`
- **Header**: `trait/is_trivially_copyable.hpp`
- **Synopsis**: Check if trivially copyable

## Enum Traits

### `is_enum`
- **Header**: `trait/is_enum.hpp`
- **Synopsis**: Check if enumeration type

### `is_scoped_enum`
- **Header**: `trait/is_scoped_enum.hpp`
- **Synopsis**: Check if scoped enumeration

### `is_unscoped_enum`
- **Header**: `trait/is_unscoped_enum.hpp`
- **Synopsis**: Check if unscoped enumeration

## Numeric Type Properties

### `is_signed`
- **Header**: `trait/is_signed.hpp`
- **Synopsis**: Check if signed type

### `is_unsigned`
- **Header**: `trait/is_unsigned.hpp`
- **Synopsis**: Check if unsigned type

### `try_signed`
- **Header**: `trait/try_signed.hpp`
- **Synopsis**: Safely convert to signed

### `try_unsigned`
- **Header**: `trait/try_unsigned.hpp`
- **Synopsis**: Safely convert to unsigned

## Pointer and Reference Utilities

### `is_ptr`
- **Header**: `trait/is_ptr.hpp`
- **Synopsis**: Check if pointer type

### `is_null_ptr`
- **Header**: `trait/is_null_ptr.hpp`
- **Synopsis**: Check if nullptr_t

### `is_member_ptr`
- **Header**: `trait/is_member_ptr.hpp`
- **Synopsis**: Check if member pointer

### `get_ptr`
- **Header**: `trait/get_ptr.hpp`
- **Synopsis**: Extract pointed-to type

### `get_member_ptr_class`
- **Header**: `trait/get_member_ptr_class.hpp`
- **Synopsis**: Extract class from member pointer

## Conditional Types

### `maybe_ref`
- **Header**: `trait/maybe_ref.hpp`
- **Synopsis**: Conditionally wrap in reference_wrapper

### `maybe_base`
- **Header**: `trait/maybe_base.hpp`
- **Synopsis**: Extract base if derived

### `collapse_ref`
- **Header**: `trait/collapse_ref.hpp`
- **Synopsis**: Handle reference collapsing

## Array Traits

### `is_array`
- **Header**: `trait/is_array.hpp`
- **Synopsis**: Check if array type

### `is_bounded_array`
- **Header**: `trait/is_bounded_array.hpp`
- **Synopsis**: Check if bounded array

### `is_unbounded_array`
- **Header**: `trait/is_unbounded_array.hpp`
- **Synopsis**: Check if unbounded array

### `rm_extent`
- **Header**: `trait/rm_extent.hpp`
- **Synopsis**: Remove array extent

### `rm_all_extents`
- **Header**: `trait/rm_all_extents.hpp`
- **Synopsis**: Remove all array extents

## Clock and Time Traits

### `is_clock`
- **Header**: `trait/is_clock.hpp`
- **Synopsis**: Check if clock type

### `is_duration`
- **Header**: `trait/is_duration.hpp`
- **Synopsis**: Check if duration type

### `is_time_point`
- **Header**: `trait/is_time_point.hpp`
- **Synopsis**: Check if time_point type

## Ratio Traits

### `is_ratio`
- **Header**: `trait/is_ratio.hpp`
- **Synopsis**: Check if std::ratio type

## Specialization Detection

### `is_specialization`
- **Header**: `trait/is_specialization.hpp`
- **Synopsis**: Check if template specialization

## Character Type Traits

### `is_char`
- **Header**: `trait/is_char.hpp`
- **Synopsis**: Check if character type

### `is_char8`
- **Header**: `trait/is_char8.hpp`
- **Synopsis**: Check if char8_t

### `is_char16`
- **Header**: `trait/is_char16.hpp`
- **Synopsis**: Check if char16_t

### `is_char32`
- **Header**: `trait/is_char32.hpp`
- **Synopsis**: Check if char32_t

### `is_wchar`
- **Header**: `trait/is_wchar.hpp`
- **Synopsis**: Check if wchar_t

## Boolean and Logical Traits

### `is_bool`
- **Header**: `trait/is_bool.hpp`
- **Synopsis**: Check if bool type

### `is_bool_testable`
- **Header**: `trait/is_bool_testable.hpp`
- **Synopsis**: Check if contextually convertible to bool

## Union Detection

### `is_union`
- **Header**: `trait/is_union.hpp`
- **Synopsis**: Check if union type

## Class Traits

### `is_class`
- **Header**: `trait/is_class.hpp`
- **Synopsis**: Check if class type

## Same Type Checking

### `is_same`
- **Header**: `trait/is_same.hpp`
- **Synopsis**: Check if types are same

### `is_same_any`
- **Header**: `trait/is_same_any.hpp`
- **Synopsis**: Check if same as any in list

### `is_same_all`
- **Header**: `trait/is_same_all.hpp`
- **Synopsis**: Check if all are same type

## Decay and Transformation

### `decay`
- **Header**: `trait/decay.hpp`
- **Synopsis**: Apply decay transformation

### `is_decayed`
- **Header**: `trait/is_decayed.hpp`
- **Synopsis**: Check if already decayed

## Satisfaction Checking

### `is_satisfied`
- **Header**: `trait/is_satisfied.hpp`
- **Synopsis**: Check if constraint satisfied

### `is_satisfies`
- **Header**: `trait/is_satisfies.hpp`
- **Synopsis**: Check multiple constraints

## Layout Properties

### `is_unique_obj_repr`
- **Header**: `trait/has_unique_obj_repr.hpp`
- **Synopsis**: Check unique object representation

## Assignment Detection

### `is_assign_to`
- **Header**: `trait/is_assign_to.hpp`
- **Synopsis**: Check if assignable to type

## Type Size Properties

### `is_sizeof`
- **Header**: `trait/is_sizeof.hpp`
- **Synopsis**: Check size of type

## Usage Examples

### Basic Type Queries
```cpp
#include <xieite/trait/is_arith.hpp>
#include <xieite/trait/is_integral.hpp>

static_assert(xieite::is_arith<int>);
static_assert(!xieite::is_arith<std::string>);
```

### Type Transformations
```cpp
#include <xieite/trait/add_c_referent.hpp>
#include <xieite/trait/rm_cvref.hpp>

using T1 = xieite::add_c_referent<int&>;      // const int&
using T2 = xieite::rm_cvref<const int&>;      // int
```

### Constructor Detection
```cpp
#include <xieite/trait/has_noex_mv_ctor.hpp>

template<typename T>
    requires xieite::has_noex_mv_ctor<T>
class container {
    // Optimized for types with noexcept move
};
```

### Safe Type Operations
```cpp
#include <xieite/trait/try_signed.hpp>

template<typename T>
auto safe_negate(T value) {
    using signed_type = xieite::try_signed<T>;
    return -static_cast<signed_type>(value);
}
```

## Performance Notes

- All traits are evaluated at compile time with zero runtime cost
- Concepts are cached after first evaluation
- Template instantiation is minimized through careful design
- SFINAE-friendly for use in overload resolution

## See Also

- [Type Traits Overview](../../categories/trait/)
- [SFINAE Helpers](../../categories/trait/sfinae_helpers.md)
- [Architecture Documentation](../../architecture/type_traits_arch.md)
