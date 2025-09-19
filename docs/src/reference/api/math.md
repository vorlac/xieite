# Mathematics API Reference

## Overview

The mathematics category contains 110 header files providing mathematical operations, from basic arithmetic to advanced numerical algorithms, designed for both compile-time and runtime use.

## Core Arithmetic Operations

### `abs`
- **Header**: `math/abs.hpp`
- **Synopsis**: `template<typename T> constexpr auto abs(T value) noexcept`
- **Purpose**: Absolute value without undefined behavior
- **Example**: `xieite::abs(-42)` → `42`

### `sign`
- **Header**: `math/sign.hpp`
- **Synopsis**: `template<typename T> constexpr int sign(T value) noexcept`
- **Purpose**: Extract sign (-1, 0, or 1)
- **Example**: `xieite::sign(-5)` → `-1`

### `diff`
- **Header**: `math/diff.hpp`
- **Synopsis**: `template<typename T> constexpr auto diff(T a, T b) noexcept`
- **Purpose**: Absolute difference
- **Example**: `xieite::diff(10, 3)` → `7`

## Division Operations

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

### `mod`
- **Header**: `math/mod.hpp`
- **Synopsis**: `template<typename T> constexpr T mod(T n, T d) noexcept`
- **Purpose**: Euclidean modulo (always positive)
- **Example**: `xieite::mod(-7, 3)` → `2`

## Comparison Operations

### `almost_equal`
- **Header**: `math/almost_equal.hpp`
- **Synopsis**: `template<typename T> constexpr bool almost_equal(T a, T b, T epsilon = default_epsilon<T>) noexcept`
- **Purpose**: Floating-point comparison with tolerance
- **Example**: `xieite::almost_equal(0.1 + 0.2, 0.3)` → `true`

### `minmax`
- **Header**: `math/minmax.hpp`
- **Synopsis**: `template<typename T, typename... Ts> constexpr auto minmax(T first, Ts... rest) noexcept`
- **Purpose**: Find minimum and maximum values
- **Returns**: `xieite::interval<T>` with `.start` (minimum) and `.end` (maximum)
- **Example**:
```cpp
auto result = xieite::minmax(5, 2, 8, 1);
// result.start == 1, result.end == 8
```

## Rounding Functions

### `ceil`
- **Header**: `math/ceil.hpp`
- **Synopsis**: `template<typename T> constexpr T ceil(T value) noexcept`
- **Purpose**: Round up to nearest integer

### `truncate`
- **Header**: `math/truncate.hpp`
- **Synopsis**: `template<is_arith Arith> constexpr Arith truncate(Arith x, type_identity_t<Arith> step = 1)`
- **Purpose**: Truncate value to multiples of step size
- **Description**: Truncates a value toward zero to the nearest multiple of the step size. With step=1, truncates to integer. With fractional steps, can truncate to specific decimal places.
- **Example**:
    ```cpp
    #include <xieite/math/truncate.hpp>

    auto result1 = xieite::truncate(3.7);      // 3.0 (truncate to integer)
    auto result2 = xieite::truncate(-3.7);     // -3.0 (toward zero)
    auto result3 = xieite::truncate(3.456, 0.1);  // 3.4 (truncate to tenths)
    auto result4 = xieite::truncate(17, 5);    // 15 (truncate to multiples of 5)
    ```

## Power Functions

### `pow`
- **Header**: `math/pow.hpp`
- **Synopsis**: `template<typename T> constexpr T pow(T base, int exp) noexcept`
- **Purpose**: Integer exponentiation
- **Example**: `xieite::pow(2, 10)` → `1024`

## Special Functions (Lookup Tables)

### `factorial`
- **Header**: `math/factorial.hpp`
- **Synopsis**: `template<typename T> constexpr std::array<T, N> factorial`
- **Purpose**: Precomputed factorial lookup table
- **Usage**: Access with array indexing
- **Example**: `xieite::factorial<int>[5]` → `120`

### `fib`
- **Header**: `math/fib.hpp`
- **Synopsis**: `template<typename T> constexpr std::array<T, N> fib`
- **Purpose**: Precomputed Fibonacci lookup table
- **Usage**: Access with array indexing
- **Example**: `xieite::fib<int>[10]` → `55`

## Number Theory

### `prime`
- **Header**: `math/prime.hpp`
- **Synopsis**: `template<std::integral Int> constexpr bool prime(Int x) noexcept`
- **Purpose**: Primality test
- **Example**: `xieite::prime(17)` → `true`

## Statistical Functions

### `mean`
- **Header**: `math/mean.hpp`
- **Synopsis**: `template<is_fwd_sized_range Range, typename Result> constexpr Result mean(Range&& range)`
- **Purpose**: Calculate arithmetic mean (average) of values in a range
- **Description**: Computes the arithmetic mean of all values in a range. Uses precise arithmetic to avoid overflow and precision loss. Template parameter Result defaults to common_type of range value and double.
- **Example**:
    ```cpp
    #include <xieite/math/mean.hpp>
    #include <vector>

    std::vector<int> values = {1, 2, 3, 4, 5};
    auto avg = xieite::mean(values);  // 3.0

    std::vector<double> decimals = {1.5, 2.5, 3.5};
    auto avg2 = xieite::mean(decimals);  // 2.5
    ```

### `median`
- **Header**: `math/median.hpp`
- **Synopsis**: `template<forward_range Range, typename Result> constexpr Result median(Range&& range)`
- **Purpose**: Find median (middle value) of a sequence when sorted
- **Description**: Sorts the range and returns the middle value. For even-sized ranges, returns the average of the two middle values. The function creates iterator vector for sorting without modifying the original range.
- **Example**:
    ```cpp
    #include <xieite/math/median.hpp>
    #include <vector>

    std::vector<int> values = {3, 1, 4, 1, 5};
    auto med = xieite::median(values);  // 3 (middle of sorted: 1,1,3,4,5)

    std::vector<int> even_values = {1, 2, 3, 4};
    auto med2 = xieite::median(even_values);  // 2.5 (average of 2 and 3)
    ```

### `modes`
- **Header**: `math/modes.hpp`
- **Synopsis**: Various overloads for finding most frequent values
- **Purpose**: Find the most frequently occurring values in a sequence
- **Description**: Returns the mode(s) - the value(s) that appear most frequently in the dataset. Can return multiple values if there's a tie for most frequent.
- **Example**:
    ```cpp
    #include <xieite/math/modes.hpp>
    #include <vector>

    std::vector<int> values = {1, 2, 2, 3, 2, 4};
    auto result = xieite::modes(values);
    // result contains {2} since 2 appears 3 times (most frequent)
    ```

## Bit Operations

### `reverse_bits`
- **Header**: `math/reverse_bits.hpp`
- **Synopsis**: `template<typename T> constexpr T reverse_bits(T value) noexcept`
- **Purpose**: Reverse bit order

## Usage Examples

### Basic Arithmetic
```cpp
#include <xieite/math/abs.hpp>
#include <xieite/math/div_ceil.hpp>
#include <xieite/math/mod.hpp>

constexpr auto a = xieite::abs(-42);        // 42
constexpr auto d = xieite::div_ceil(7, 3);  // 3
constexpr auto m = xieite::mod(-7, 3);      // 2
```

### MinMax with Interval
```cpp
#include <xieite/math/minmax.hpp>

auto result = xieite::minmax(5, 2, 8, 1, 9);
std::cout << "min: " << result.start << ", max: " << result.end << std::endl;
```

### Lookup Tables
```cpp
#include <xieite/math/factorial.hpp>
#include <xieite/math/fib.hpp>

constexpr auto fact = xieite::factorial<int>[5];  // 120
constexpr auto fibo = xieite::fib<int>[10];       // 55
```

### Number Theory
```cpp
#include <xieite/math/prime.hpp>

static_assert(xieite::prime(17));
```

## Compiler Requirements

- C++23 or later required (uses pack indexing)
- Recommended: clang++ with `-std=c++23`

## See Also

- [Mathematics Category Overview](../../categories/math/)
- [Compile-Time Computation](../../architecture/compile_time.md)