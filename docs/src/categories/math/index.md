# XIEITE Math Module

## Overview

The XIEITE math module provides a comprehensive suite of mathematical utilities spanning arithmetic operations, geometric computations, bit manipulation, numerical algorithms, and physical unit conversions. With 110 headers, it forms one of the largest and most feature-rich components of the XIEITE library.

## Module Organization

### Core Arithmetic (20 headers)
- **[Arithmetic Operations](arithmetic_operations.md)** - Overflow-safe operations, absolute values, sign manipulation
- **[Division and Rounding](division_rounding.md)** - Comprehensive division modes and rounding strategies
- Basic operations: `abs`, `diff`, `avg`, `sign`, `neg`, `split_bool`
- Overflow detection: `add_overflow`, `sub_overflow`, `mul_overflow`, `div_overflow`
- Comparison: `almost_equal`, `between`, `closest`

### Geometric Types and Operations (15 headers)
- **[Geometric Types](geometric_types.md)** - 2D points, lines, rays, segments, polygons
- **[Transformations](search_utilities.md#2d-geometric-transformations)** - Rotation, scaling, translation, reflection
- Core types: `point2d`, `line2d`, `segment2d`, `ray2d`, `polygon2d`
- Color types: `color3`, `color4`
- Operations: `rotate2d`, `scale2d`, `translate2d`, `reflect2d`, `intersection2d`

### Advanced Types (10 headers)
- **[Advanced Mathematical Types](advanced_types.md)** - Arbitrary precision and specialized numeric types
- `big_int` - Arbitrary precision integers
- `number` - Unified arithmetic interface with extended operations
- `bit_field` - Type-safe bitfield wrapper
- `wide_uint` - Double-width unsigned integers
- `vec2` - Complete 2D vector implementation

### Bit Operations and Hashing (15 headers)
- **[Bit Operations](bit_operations.md)** - Comprehensive bit manipulation and hashing
- Bit manipulation: `reverse_bits`, `join_bits`, `mash_bits`, `unjoin_bits`, `unmash_bits`
- Endianness: `big_endify`, `little_endify`, `byte_fill`
- Hashing: `djb2`, `md5`, `hash_combine`, `hash_distribute`, `xor_shift`
- Safe shifting: `left_shift`, `right_shift`

### Mathematical Functions (20 headers)
- **[Mathematical Functions and Constants](mathematical_functions.md)** - Number theory and transcendental functions
- Constants: `pi`, `tau`
- Precomputed sequences: `factorial`, `fib`
- Number theory: `prime`, `digits`, `gcd` (implied)
- Trigonometry: `cot`, `csc`, `sec`
- Statistics: `mean`, `median`, `modes`
- Conversions: `to_roman`, `from_roman`, `parse_number`, `str_number`

### Division and Rounding (18 headers)
- **[Division and Rounding Operations](division_rounding.md)** - Precise control over division behavior
- Division modes: `div_ceil`, `div_floor`, `div_truncate`, `div_magnify`
- Half-point variants: `div_ceil_half`, `div_floor_half`, `div_truncate_half`, `div_magnify_half`
- Rounding functions: `ceil`, `floor`, `truncate`, `magnify` (with step parameter)
- Modulo operations: `mod`, `rem`

### Search and Utilities (12 headers)
- **[Search, Transformation, and Utilities](search_utilities.md)** - Advanced algorithms and utility types
- Search: `exp_search`, `find_number`
- Intervals: `interval`, `merge_intervals`, `minmax`, `minmax_magnitude`
- Random: `uniform_distribution`, `uniform_interruptable_distribution`
- Units: Comprehensive physical unit system with automatic conversions
- Utilities: `ver` (versioning), `duration_cast`, `wrap`, `reverse_number`

## Key Features

### Compile-Time Computation
Most functions are `constexpr`, enabling:
- Zero-runtime-cost constants and precomputed values
- Compile-time validation and optimization
- Use in template metaprogramming

### Type Safety
- Concepts constrain template parameters
- `std::type_identity_t` prevents implicit conversions
- Type-aware operations (e.g., different integer/floating-point implementations)

### Overflow Safety
- Dedicated overflow detection functions
- Safe arithmetic operations
- Careful handling of edge cases (e.g., `INT_MIN`)

### Cross-Platform Support
- Endianness detection and conversion
- Platform-specific optimizations
- Portable 128-bit integer support

## Usage Examples

### Basic Arithmetic
```cpp
// Overflow-safe operations
if (!xieite::add_overflow(a, b)) {
    auto sum = a + b;
}

// Safe averaging without overflow
auto average = xieite::avg(INT_MAX, INT_MAX - 2, INT_MAX - 4);
```

### Geometric Computations
```cpp
// Create and transform shapes
xieite::polygon2d<> square = xieite::polygon2d<>::rect({0, 0}, {10, 10});
auto rotated = xieite::rotate2d(square, xieite::pi<> / 4);
auto scaled = xieite::scale2d(rotated, 1.5);

// Check intersections
auto intersections = xieite::intersection2d(shape1, shape2);
```

### Advanced Types
```cpp
// Arbitrary precision arithmetic
xieite::big_int<> factorial_100 = calculate_factorial(100);

// Physical units with automatic conversion
xieite::unit::mi distance{26.2};  // Marathon distance
xieite::unit::km km_distance = distance;  // Converts to ~42.195 km
```

### Bit Operations
```cpp
// Safe bit manipulation
auto reversed = xieite::reverse_bits(0b11010010);
auto joined = xieite::join_bits(byte1, byte2, byte3);

// Cross-platform endianness
auto network_order = xieite::big_endify(host_value);
```

## Design Philosophy

The math module follows these principles:

1. **Correctness First**: Handle edge cases, prevent overflow, maintain precision
2. **Performance**: Compile-time evaluation, efficient algorithms, minimal overhead
3. **Flexibility**: Support multiple numeric types, configurable behavior
4. **Safety**: Type constraints, overflow detection, safe operations
5. **Comprehensiveness**: Cover common and advanced use cases

## Module Statistics

- **Total Headers**: 110
- **Lines of Code**: ~15,000+
- **Compile-Time Functions**: ~95%
- **Test Coverage**: Comprehensive static assertions
- **Documentation**: 100% documented

## Performance Considerations

- Most operations are branch-free for integers
- Floating-point operations maintain IEEE-754 compliance
- Compile-time precomputation eliminates runtime costs
- Template specialization optimizes for specific types
- No dynamic memory allocation in basic operations

## Integration with Other Modules

- **trait/**: Uses type traits for concept definitions
- **pp/**: Leverages preprocessor utilities for macro generation
- **meta/**: Template metaprogramming for compile-time computation
- **data/**: Geometric types integrate with data structures

## Future Enhancements

Potential additions to the math module:
- Matrix and linear algebra operations
- Complex number support
- Statistical distributions beyond uniform
- Numerical integration and differentiation
- Fast Fourier Transform (FFT)
- Arbitrary precision floating-point

---

*Return to [XIEITE Documentation Home](../../index.md)*