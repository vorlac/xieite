# Mathematics API Reference

## Overview

The mathematics category contains 110 header files providing comprehensive mathematical operations, from basic arithmetic to advanced numerical algorithms, all designed for both compile-time and runtime use.

## Organization

The math headers are organized into functional groups:

- **Basic Arithmetic** (20+ headers): Fundamental operations with enhanced safety
- **Numeric Algorithms** (25+ headers): Comparisons, rounding, conversions
- **Statistical Functions** (15+ headers): Mean, median, standard deviation
- **Geometric Operations** (10+ headers): Distance, angles, transformations
- **Number Theory** (15+ headers): Primes, factors, modular arithmetic
- **Bit Manipulation** (10+ headers): Bitwise operations and utilities
- **Special Functions** (15+ headers): Factorial, combinations, special math

### Core Arithmetic Operations

### Basic Operations

### `abs`
- **Header**: `math/abs.hpp`
- **Synopsis**: `template<typename T> constexpr auto abs(T value) noexcept`
- **Purpose**: Absolute value without undefined behavior
- **Example**: `xieite::abs(-42)` → `42`
- **Note**: Safe for `INT_MIN` unlike `std::abs`

### `sign`
- **Header**: `math/sign.hpp`
- **Synopsis**: `template<typename T> constexpr int sign(T value) noexcept`
- **Purpose**: Extract sign (-1, 0, or 1)
- **Example**: `xieite::sign(-5.5)` → `-1`

### `diff`
- **Header**: `math/diff.hpp`
- **Synopsis**: `template<typename T> constexpr auto diff(T a, T b) noexcept`
- **Purpose**: Absolute difference
- **Example**: `xieite::diff(10, 3)` → `7`

### `add_sat`
- **Header**: `math/add_sat.hpp`
- **Synopsis**: `template<typename T> constexpr T add_sat(T a, T b) noexcept`
- **Purpose**: Saturating addition
- **Example**: `xieite::add_sat(INT_MAX, 1)` → `INT_MAX`

### `sub_sat`
- **Header**: `math/sub_sat.hpp`
- **Synopsis**: `template<typename T> constexpr T sub_sat(T a, T b) noexcept`
- **Purpose**: Saturating subtraction
- **Example**: `xieite::sub_sat(INT_MIN, 1)` → `INT_MIN`

### `mul_sat`
- **Header**: `math/mul_sat.hpp`
- **Synopsis**: `template<typename T> constexpr T mul_sat(T a, T b) noexcept`
- **Purpose**: Saturating multiplication
- **Example**: `xieite::mul_sat(INT_MAX, 2)` → `INT_MAX`

### Division Operations

### `div_ceil`
- **Header**: `math/div_ceil.hpp`
- **Synopsis**: `template<typename T> constexpr T div_ceil(T n, T d) noexcept`
- **Purpose**: Division rounding up
- **Example**: `xieite::div_ceil(7, 3)` → `3`

### `div_floor`
- **Header**: `math/div_floor.hpp`
- **Synopsis**: `template<typename T> constexpr T div_floor(T n, T d) noexcept`
- **Purpose**: Division rounding down
- **Example**: `xieite::div_floor(-7, 3)` → `-3`

### `div_round`
- **Header**: `math/div_round.hpp`
- **Synopsis**: `template<typename T> constexpr T div_round(T n, T d) noexcept`
- **Purpose**: Division with rounding to nearest
- **Example**: `xieite::div_round(7, 3)` → `2`

### `mod`
- **Header**: `math/mod.hpp`
- **Synopsis**: `template<typename T> constexpr T mod(T n, T d) noexcept`
- **Purpose**: Euclidean modulo (always positive)
- **Example**: `xieite::mod(-7, 3)` → `2`

## Comparison Operations

### `almost_eq`
- **Header**: `math/almost_eq.hpp`
- **Synopsis**: `template<typename T> constexpr bool almost_eq(T a, T b, T epsilon = default_epsilon<T>) noexcept`
- **Purpose**: Floating-point comparison with tolerance
- **Example**: `xieite::almost_eq(0.1 + 0.2, 0.3)` → `true`

### `min`
- **Header**: `math/min.hpp`
- **Synopsis**: `template<typename T, typename... Ts> constexpr auto min(T first, Ts... rest) noexcept`
- **Purpose**: Variadic minimum
- **Example**: `xieite::min(5, 2, 8, 1)` → `1`

### `max`
- **Header**: `math/max.hpp`
- **Synopsis**: `template<typename T, typename... Ts> constexpr auto max(T first, Ts... rest) noexcept`
- **Purpose**: Variadic maximum
- **Example**: `xieite::max(5, 2, 8, 1)` → `8`

### `clamp`
- **Header**: `math/clamp.hpp`
- **Synopsis**: `template<typename T> constexpr T clamp(T value, T low, T high) noexcept`
- **Purpose**: Constrain value to range
- **Example**: `xieite::clamp(10, 0, 5)` → `5`

### `in_range`
- **Header**: `math/in_range.hpp`
- **Synopsis**: `template<typename T> constexpr bool in_range(T value, T low, T high) noexcept`
- **Purpose**: Check if value in range
- **Example**: `xieite::in_range(3, 1, 5)` → `true`

## Rounding Functions

### `ceil`
- **Header**: `math/ceil.hpp`
- **Synopsis**: `template<typename T> constexpr T ceil(T value) noexcept`
- **Purpose**: Round up to nearest integer
- **Example**: `xieite::ceil(2.7)` → `3`

### `round_half_up`
- **Header**: `math/round_half_up.hpp`
- **Synopsis**: `template<typename T> constexpr T round_half_up(T value) noexcept`
- **Purpose**: Round half values up
- **Example**: `xieite::round_half_up(2.5)` → `3`

### `round_half_down`
- **Header**: `math/round_half_down.hpp`
- **Synopsis**: `template<typename T> constexpr T round_half_down(T value) noexcept`
- **Purpose**: Round half values down
- **Example**: `xieite::round_half_down(2.5)` → `2`

### `round_half_even`
- **Header**: `math/round_half_even.hpp`
- **Synopsis**: `template<typename T> constexpr T round_half_even(T value) noexcept`
- **Purpose**: Banker's rounding
- **Example**: `xieite::round_half_even(2.5)` → `2`

### `round_half_odd`
- **Header**: `math/round_half_odd.hpp`
- **Synopsis**: `template<typename T> constexpr T round_half_odd(T value) noexcept`
- **Purpose**: Round half to odd
- **Example**: `xieite::round_half_odd(2.5)` → `3`

### `truncate`
- **Header**: `math/truncate.hpp`
- **Synopsis**: `template<typename T> constexpr T truncate(T value, int digits) noexcept`
- **Purpose**: Truncate to n decimal places
- **Example**: `xieite::truncate(3.14159, 2)` → `3.14`

## Power and Root Functions

### `pow`
- **Header**: `math/pow.hpp`
- **Synopsis**: `template<typename T> constexpr T pow(T base, int exp) noexcept`
- **Purpose**: Integer exponentiation
- **Example**: `xieite::pow(2, 10)` → `1024`
- **Note**: Compile-time capable

### `sqrt_int`
- **Header**: `math/sqrt_int.hpp`
- **Synopsis**: `template<typename T> constexpr T sqrt_int(T value) noexcept`
- **Purpose**: Integer square root
- **Example**: `xieite::sqrt_int(16)` → `4`

### `cbrt_int`
- **Header**: `math/cbrt_int.hpp`
- **Synopsis**: `template<typename T> constexpr T cbrt_int(T value) noexcept`
- **Purpose**: Integer cube root
- **Example**: `xieite::cbrt_int(27)` → `3`

### `is_pow_of`
- **Header**: `math/is_pow_of.hpp`
- **Synopsis**: `template<typename T> constexpr bool is_pow_of(T value, T base) noexcept`
- **Purpose**: Check if power of base
- **Example**: `xieite::is_pow_of(32, 2)` → `true`

### `next_pow_of_2`
- **Header**: `math/next_pow_of_2.hpp`
- **Synopsis**: `template<typename T> constexpr T next_pow_of_2(T value) noexcept`
- **Purpose**: Next power of 2
- **Example**: `xieite::next_pow_of_2(5)` → `8`

## Number Theory

### `factorial`
- **Header**: `math/factorial.hpp`
- **Synopsis**: `template<typename T> constexpr T factorial(T n) noexcept`
- **Purpose**: Factorial computation
- **Example**: `xieite::factorial(5)` → `120`
- **Note**: Compile-time capable

### `gcd`
- **Header**: `math/gcd.hpp`
- **Synopsis**: `template<typename T> constexpr T gcd(T a, T b) noexcept`
- **Purpose**: Greatest common divisor
- **Example**: `xieite::gcd(24, 36)` → `12`

### `lcm`
- **Header**: `math/lcm.hpp`
- **Synopsis**: `template<typename T> constexpr T lcm(T a, T b) noexcept`
- **Purpose**: Least common multiple
- **Example**: `xieite::lcm(12, 18)` → `36`

### `is_prime`
- **Header**: `math/is_prime.hpp`
- **Synopsis**: `template<typename T> constexpr bool is_prime(T n) noexcept`
- **Purpose**: Primality test
- **Example**: `xieite::is_prime(17)` → `true`

### `next_prime`
- **Header**: `math/next_prime.hpp`
- **Synopsis**: `template<typename T> constexpr T next_prime(T n) noexcept`
- **Purpose**: Find next prime
- **Example**: `xieite::next_prime(14)` → `17`

### `prime_factors`
- **Header**: `math/prime_factors.hpp`
- **Synopsis**: `template<typename T> constexpr auto prime_factors(T n)`
- **Purpose**: Prime factorization
- **Example**: `xieite::prime_factors(12)` → `{2, 2, 3}`

### `fibonacci`
- **Header**: `math/fibonacci.hpp`
- **Synopsis**: `template<typename T> constexpr T fibonacci(T n) noexcept`
- **Purpose**: Nth Fibonacci number
- **Example**: `xieite::fibonacci(10)` → `55`

## Combinatorics

### `nCr`
- **Header**: `math/nCr.hpp`
- **Synopsis**: `template<typename T> constexpr T nCr(T n, T r) noexcept`
- **Purpose**: Combinations
- **Example**: `xieite::nCr(5, 2)` → `10`
---
### `nPr`
- **Header**: `math/nPr.hpp`
- **Synopsis**: `template<typename T> constexpr T nPr(T n, T r) noexcept`
- **Purpose**: Permutations
- **Example**: `xieite::nPr(5, 2)` → `20`
---
### `catalan`
- **Header**: `math/catalan.hpp`
- **Synopsis**: `template<typename T> constexpr T catalan(T n) noexcept`
- **Purpose**: Nth Catalan number
- **Example**: `xieite::catalan(4)` → `14`

## Bit Operations

### `popcount`
- **Header**: `math/popcount.hpp`
- **Synopsis**: `template<typename T> constexpr int popcount(T value) noexcept`
- **Purpose**: Count set bits
- **Example**: `xieite::popcount(0b1011)` → `3`

### `leading_zeros`
- **Header**: `math/leading_zeros.hpp`
- **Synopsis**: `template<typename T> constexpr int leading_zeros(T value) noexcept`
- **Purpose**: Count leading zero bits
- **Example**: `xieite::leading_zeros(0b00001000)` → `4` (for 8-bit)

### `trailing_zeros`
- **Header**: `math/trailing_zeros.hpp`
- **Synopsis**: `template<typename T> constexpr int trailing_zeros(T value) noexcept`
- **Purpose**: Count trailing zero bits
- **Example**: `xieite::trailing_zeros(0b1000)` → `3`

### `rotate_left`
- **Header**: `math/rotate_left.hpp`
- **Synopsis**: `template<typename T> constexpr T rotate_left(T value, int n) noexcept`
- **Purpose**: Bitwise left rotation
- **Example**: `xieite::rotate_left(0b1011, 2)` → `0b101100`

### `rotate_right`
- **Header**: `math/rotate_right.hpp`
- **Synopsis**: `template<typename T> constexpr T rotate_right(T value, int n) noexcept`
- **Purpose**: Bitwise right rotation

### `reverse_bits`
- **Header**: `math/reverse_bits.hpp`
- **Synopsis**: `template<typename T> constexpr T reverse_bits(T value) noexcept`
- **Purpose**: Reverse bit order
- **Example**: `xieite::reverse_bits(0b1101)` → `0b1011`

## Statistical Functions

### `mean`
- **Header**: `math/mean.hpp`
- **Synopsis**: `template<typename... Ts> constexpr auto mean(Ts... values) noexcept`
- **Purpose**: Arithmetic mean
- **Example**: `xieite::mean(1, 2, 3, 4, 5)` → `3`

### `median`
- **Header**: `math/median.hpp`
- **Synopsis**: `template<typename... Ts> constexpr auto median(Ts... values) noexcept`
- **Purpose**: Middle value
- **Example**: `xieite::median(1, 3, 2)` → `2`

### `mode`
- **Header**: `math/mode.hpp`
- **Synopsis**: `template<typename Range> auto mode(const Range& values)`
- **Purpose**: Most frequent value
- **Example**: `xieite::mode({1, 2, 2, 3})` → `2`

### `variance`
- **Header**: `math/variance.hpp`
- **Synopsis**: `template<typename... Ts> constexpr auto variance(Ts... values) noexcept`
- **Purpose**: Statistical variance
- **Example**: `xieite::variance(1, 2, 3, 4, 5)` → `2`

### `std_dev`
- **Header**: `math/std_dev.hpp`
- **Synopsis**: `template<typename... Ts> constexpr auto std_dev(Ts... values) noexcept`
- **Purpose**: Standard deviation
- **Example**: `xieite::std_dev(1, 2, 3, 4, 5)` → `1.414...`

## Geometric Functions

### `distance`
- **Header**: `math/distance.hpp`
- **Synopsis**: `template<typename T> constexpr T distance(T x1, T y1, T x2, T y2) noexcept`
- **Purpose**: Euclidean distance
- **Example**: `xieite::distance(0, 0, 3, 4)` → `5`

### `manhattan_distance`
- **Header**: `math/manhattan_distance.hpp`
- **Synopsis**: `template<typename T> constexpr T manhattan_distance(T x1, T y1, T x2, T y2) noexcept`
- **Purpose**: Manhattan/taxi distance
- **Example**: `xieite::manhattan_distance(0, 0, 3, 4)` → `7`

### `angle`
- **Header**: `math/angle.hpp`
- **Synopsis**: `template<typename T> constexpr T angle(T x1, T y1, T x2, T y2) noexcept`
- **Purpose**: Angle between two points
- **Example**: `xieite::angle(0, 0, 1, 1)` → `45` (degrees)

### `dot_product`
- **Header**: `math/dot_product.hpp`
- **Synopsis**: `template<typename T> constexpr T dot_product(T x1, T y1, T x2, T y2) noexcept`
- **Purpose**: Vector dot product
- **Example**: `xieite::dot_product(1, 2, 3, 4)` → `11`

### `cross_product`
- **Header**: `math/cross_product.hpp`
- **Synopsis**: `template<typename T> constexpr auto cross_product(T x1, T y1, T z1, T x2, T y2, T z2) noexcept`
- **Purpose**: 3D vector cross product

## Interpolation

### `lerp`
- **Header**: `math/lerp.hpp`
- **Synopsis**: `template<typename T> constexpr T lerp(T a, T b, T t) noexcept`
- **Purpose**: Linear interpolation
- **Example**: `xieite::lerp(0, 10, 0.5)` → `5`

### `inverse_lerp`
- **Header**: `math/inverse_lerp.hpp`
- **Synopsis**: `template<typename T> constexpr T inverse_lerp(T a, T b, T value) noexcept`
- **Purpose**: Inverse linear interpolation
- **Example**: `xieite::inverse_lerp(0, 10, 5)` → `0.5`

### `smoothstep`
- **Header**: `math/smoothstep.hpp`
- **Synopsis**: `template<typename T> constexpr T smoothstep(T edge0, T edge1, T x) noexcept`
- **Purpose**: Smooth Hermite interpolation
- **Example**: `xieite::smoothstep(0, 1, 0.5)` → `0.5`

## Range and Sequence Operations

### `sum`
- **Header**: `math/sum.hpp`
- **Synopsis**: `template<typename... Ts> constexpr auto sum(Ts... values) noexcept`
- **Purpose**: Sum of values
- **Example**: `xieite::sum(1, 2, 3, 4, 5)` → `15`

### `product`
- **Header**: `math/product.hpp`
- **Synopsis**: `template<typename... Ts> constexpr auto product(Ts... values) noexcept`
- **Purpose**: Product of values
- **Example**: `xieite::product(2, 3, 4)` → `24`

### `accumulate`
- **Header**: `math/accumulate.hpp`
- **Synopsis**: `template<typename Op, typename Init, typename... Ts> constexpr auto accumulate(Op op, Init init, Ts... values) noexcept`
- **Purpose**: General accumulation
- **Example**: `xieite::accumulate(std::plus{}, 0, 1, 2, 3)` → `6`

## Conversion Functions

### `to_degrees`
- **Header**: `math/to_degrees.hpp`
- **Synopsis**: `template<typename T> constexpr T to_degrees(T radians) noexcept`
- **Purpose**: Radians to degrees
- **Example**: `xieite::to_degrees(M_PI)` → `180`

### `to_radians`
- **Header**: `math/to_radians.hpp`
- **Synopsis**: `template<typename T> constexpr T to_radians(T degrees) noexcept`
- **Purpose**: Degrees to radians
- **Example**: `xieite::to_radians(180)` → `3.14159...`

### `to_base`
- **Header**: `math/to_base.hpp`
- **Synopsis**: `template<typename T> std::string to_base(T value, int base)`
- **Purpose**: Convert to arbitrary base
- **Example**: `xieite::to_base(42, 16)` → `"2A"`

### `from_base`
- **Header**: `math/from_base.hpp`
- **Synopsis**: `template<typename T> T from_base(std::string_view str, int base)`
- **Purpose**: Parse from arbitrary base
- **Example**: `xieite::from_base<int>("2A", 16)` → `42`

## Numeric Properties

### `is_even`
- **Header**: `math/is_even.hpp`
- **Synopsis**: `template<typename T> constexpr bool is_even(T value) noexcept`
- **Purpose**: Check if even
- **Example**: `xieite::is_even(4)` → `true`

### `is_odd`
- **Header**: `math/is_odd.hpp`
- **Synopsis**: `template<typename T> constexpr bool is_odd(T value) noexcept`
- **Purpose**: Check if odd
- **Example**: `xieite::is_odd(5)` → `true`

### `is_perfect_square`
- **Header**: `math/is_perfect_square.hpp`
- **Synopsis**: `template<typename T> constexpr bool is_perfect_square(T value) noexcept`
- **Purpose**: Check if perfect square
- **Example**: `xieite::is_perfect_square(16)` → `true`

### `is_palindrome`
- **Header**: `math/is_palindrome.hpp`
- **Synopsis**: `template<typename T> constexpr bool is_palindrome(T value) noexcept`
- **Purpose**: Check if numeric palindrome
- **Example**: `xieite::is_palindrome(12321)` → `true`

## Matrix Operations

### `matrix_multiply`
- **Header**: `math/matrix_multiply.hpp`
- **Synopsis**: Matrix multiplication utilities
- **Purpose**: 2D matrix operations

### `matrix_transpose`
- **Header**: `math/matrix_transpose.hpp`
- **Synopsis**: Matrix transposition
- **Purpose**: Transpose 2D matrices

### `determinant`
- **Header**: `math/determinant.hpp`
- **Synopsis**: Calculate matrix determinant
- **Purpose**: Matrix determinant

## Special Constants

### `constants`
- **Header**: `math/constants.hpp`
- **Synopsis**: Mathematical constants
- **Contents**:
  * `pi` - Pi constant
  * `e` - Euler's number
  * `phi` - Golden ratio
  * `sqrt2` - Square root of 2
  * `sqrt3` - Square root of 3
  * `ln2` - Natural log of 2
  * `ln10` - Natural log of 10

## Error Handling

### `safe_div`
- **Header**: `math/safe_div.hpp`
- **Synopsis**: `template<typename T> std::optional<T> safe_div(T n, T d) noexcept`
- **Purpose**: Division with zero check
- **Example**: `xieite::safe_div(10, 0)` → `std::nullopt`

### `checked_add`
- **Header**: `math/checked_add.hpp`
- **Synopsis**: `template<typename T> std::optional<T> checked_add(T a, T b) noexcept`
- **Purpose**: Addition with overflow check

### `checked_sub`
- **Header**: `math/checked_sub.hpp`
- **Synopsis**: `template<typename T> std::optional<T> checked_sub(T a, T b) noexcept`
- **Purpose**: Subtraction with underflow check

### `checked_mul`
- **Header**: `math/checked_mul.hpp`
- **Synopsis**: `template<typename T> std::optional<T> checked_mul(T a, T b) noexcept`
- **Purpose**: Multiplication with overflow check

## Random Number Utilities

### `random`
- **Header**: `math/random.hpp`
- **Synopsis**: Random number generation utilities
- **Purpose**: Simplified random number generation

### `random_int`
- **Header**: `math/random_int.hpp`
- **Synopsis**: `template<typename T> T random_int(T min, T max)`
- **Purpose**: Random integer in range

### `random_real`
- **Header**: `math/random_real.hpp`
- **Synopsis**: `template<typename T> T random_real(T min, T max)`
- **Purpose**: Random real number in range

## Usage Examples

### Basic Arithmetic
```cpp
#include <xieite/math/abs.hpp>
#include <xieite/math/div_ceil.hpp>

constexpr auto a = xieite::abs(-42);        // 42
constexpr auto d = xieite::div_ceil(7, 3);  // 3
```

### Number Theory
```cpp
#include <xieite/math/is_prime.hpp>
#include <xieite/math/gcd.hpp>

static_assert(xieite::is_prime(17));
constexpr auto g = xieite::gcd(24, 36);  // 12
```

### Statistics
```cpp
#include <xieite/math/mean.hpp>
#include <xieite/math/std_dev.hpp>

auto avg = xieite::mean(1, 2, 3, 4, 5);
auto sd = xieite::std_dev(1, 2, 3, 4, 5);
```

### Compile-Time Computation
```cpp
#include <xieite/math/factorial.hpp>
#include <xieite/math/fibonacci.hpp>

constexpr auto fact = xieite::factorial(10);
constexpr auto fib = xieite::fibonacci(20);
```

## Performance Notes

- Most functions are `constexpr` for compile-time evaluation
- Integer operations avoid floating-point when possible
- Bit operations use compiler intrinsics when available
- Statistical functions optimize for small datasets
- Safe operations have minimal overhead over unsafe versions

## See Also

- [Mathematics Overview](../../categories/math/README.md)
- [Compile-Time Computation](../../architecture/compile_time.md)
- [Data Structures API](./data.md)
