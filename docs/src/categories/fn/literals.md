# User-Defined Literals

## Overview

XIEITE provides extensive user-defined literals for type casting, unit conversions, range creation, and specialized numeric operations. These literals enable expressive syntax for compile-time conversions and mathematical unit handling across metric, imperial, and specialized measurement systems.

## Numeric Type Literals

### Integer Type Literals
Implementation: `include/xieite/fn/number_udl.hpp` (lines 18-418)

```cpp
// Basic integer types
consteval auto operator""_i(unsigned long long int x) noexcept;    // int
consteval auto operator""_u(unsigned long long int x) noexcept;    // unsigned int
consteval auto operator""_il(unsigned long long int x) noexcept;   // long int
consteval auto operator""_ul(unsigned long long int x) noexcept;   // unsigned long
consteval auto operator""_ill(unsigned long long int x) noexcept;  // long long
consteval auto operator""_ull(unsigned long long int x) noexcept;  // unsigned long long

// Fixed-width integer types (when available)
consteval auto operator""_i8(unsigned long long int x) noexcept;   // int8_t
consteval auto operator""_u8(unsigned long long int x) noexcept;   // uint8_t
consteval auto operator""_i16(unsigned long long int x) noexcept;  // int16_t
consteval auto operator""_u16(unsigned long long int x) noexcept;  // uint16_t
// ... and more variants
```

Provides compile-time type casting literals for all standard integer types.

### Floating-Point Type Literals
Implementation: `include/xieite/fn/number_udl.hpp` (lines 420-492)

```cpp
consteval auto operator""_f(unsigned long long int x) noexcept;    // float
consteval auto operator""_d(unsigned long long int x) noexcept;    // double
consteval auto operator""_dl(unsigned long long int x) noexcept;   // long double

#if XIEITE_FEAT_F16
consteval auto operator""_f16(unsigned long long int x) noexcept;  // float16_t
#endif
```

Compile-time casting literals for floating-point types including modern C++23 extended precision types.

### Character Type Literals
Implementation: `include/xieite/fn/number_udl.hpp` (lines 90-144)

```cpp
consteval auto operator""_c(unsigned long long int x) noexcept;    // char
consteval auto operator""_uc(unsigned long long int x) noexcept;   // unsigned char
consteval auto operator""_ic(unsigned long long int x) noexcept;   // signed char
consteval auto operator""_cw(unsigned long long int x) noexcept;   // wchar_t
consteval auto operator""_c8(unsigned long long int x) noexcept;   // char8_t
consteval auto operator""_c16(unsigned long long int x) noexcept;  // char16_t
consteval auto operator""_c32(unsigned long long int x) noexcept;  // char32_t
```

Compile-time character type conversion literals.

## Physical Unit Literals

### Length Units
Implementation: `include/xieite/fn/unit_udl.hpp` (lines 7-357)

```cpp
// Metric lengths (all prefixes from quecto to quetta)
consteval auto operator""_qm(unsigned long long int x) noexcept;  // quectometers
consteval auto operator""_mm(unsigned long long int x) noexcept;  // millimeters
consteval auto operator""_cm(unsigned long long int x) noexcept;  // centimeters
consteval auto operator""_m(unsigned long long int x) noexcept;   // meters
consteval auto operator""_km(unsigned long long int x) noexcept;  // kilometers
consteval auto operator""_Mm(unsigned long long int x) noexcept;  // megameters
// ... complete SI prefix system

// Imperial lengths
consteval auto operator""_in(unsigned long long int x) noexcept;     // inches
consteval auto operator""_ft(unsigned long long int x) noexcept;     // feet
consteval auto operator""_yd(unsigned long long int x) noexcept;     // yards
consteval auto operator""_mi(unsigned long long int x) noexcept;     // miles
consteval auto operator""_fathoms(unsigned long long int x) noexcept; // fathoms
consteval auto operator""_chains(unsigned long long int x) noexcept; // chains
```

Comprehensive length unit literals covering metric, imperial, nautical, and specialized measurement systems.

### Area Units
Implementation: `include/xieite/fn/unit_udl.hpp` (lines 359-653)

```cpp
// Metric areas with complete SI prefix system
consteval auto operator""_qA(unsigned long long int x) noexcept;  // quecto-ares
consteval auto operator""_a(unsigned long long int x) noexcept;   // ares
consteval auto operator""_ha(unsigned long long int x) noexcept;  // hectares

// Imperial areas
consteval auto operator""_sq_in(unsigned long long int x) noexcept; // square inches
consteval auto operator""_sq_ft(unsigned long long int x) noexcept; // square feet
consteval auto operator""_sq_yd(unsigned long long int x) noexcept; // square yards
consteval auto operator""_sq_mi(unsigned long long int x) noexcept; // square miles
consteval auto operator""_ac(unsigned long long int x) noexcept;    // acres
```

Area measurement literals for both metric and imperial systems.

### Volume Units
Implementation: `include/xieite/fn/unit_udl.hpp` (lines 655-1133)

```cpp
// Metric volumes (complete SI prefix system for liters)
consteval auto operator""_qL(unsigned long long int x) noexcept;  // quectoliters
consteval auto operator""_mL(unsigned long long int x) noexcept;  // milliliters
consteval auto operator""_L(unsigned long long int x) noexcept;   // liters
consteval auto operator""_kL(unsigned long long int x) noexcept;  // kiloliters

// Imperial/US volumes
consteval auto operator""_cu_in(unsigned long long int x) noexcept; // cubic inches
consteval auto operator""_cu_ft(unsigned long long int x) noexcept; // cubic feet
consteval auto operator""_fl_oz(unsigned long long int x) noexcept; // fluid ounces
consteval auto operator""_cups(unsigned long long int x) noexcept;  // cups
consteval auto operator""_pt(unsigned long long int x) noexcept;    // pints
consteval auto operator""_qt(unsigned long long int x) noexcept;    // quarts
consteval auto operator""_gal(unsigned long long int x) noexcept;   // gallons
```

Volume unit literals supporting both metric and imperial measurement systems.

### Temperature Units
Implementation: `include/xieite/fn/unit_udl.hpp` (lines 1151-1181)

```cpp
consteval auto operator""_K(unsigned long long int x) noexcept;  // Kelvin
consteval auto operator""_C(unsigned long long int x) noexcept;  // Celsius
consteval auto operator""_F(unsigned long long int x) noexcept;  // Fahrenheit
consteval auto operator""_R(unsigned long long int x) noexcept;  // Rankine
```

Temperature scale conversion literals.

### Angular Units
Implementation: `include/xieite/fn/unit_udl.hpp` (lines 1135-1149)

```cpp
consteval auto operator""_rad(unsigned long long int x) noexcept; // radians
consteval auto operator""_deg(unsigned long long int x) noexcept; // degrees
```

Angular measurement literals for radians and degrees.

### Time Units
Implementation: `include/xieite/fn/unit_udl.hpp` (lines 1183-1201)

```cpp
consteval auto operator""_decades(unsigned long long int x) noexcept;    // decades
consteval auto operator""_centuries(unsigned long long int x) noexcept;  // centuries
consteval auto operator""_millenniums(unsigned long long int x) noexcept; // millenniums
consteval auto operator""_epochs(unsigned long long int x) noexcept;     // geological epochs
consteval auto operator""_eons(unsigned long long int x) noexcept;       // geological eons
```

Extended time period literals for geological and historical timescales.

## Range Creation Literals

### Range Syntax
Implementation: `include/xieite/fn/range_udl.hpp` (lines 49-62)

```cpp
template<char... digits>
constexpr auto operator""_range() noexcept;
```

Creates compile-time ranges from string literals using syntax: `start.end[estep]`.

### Range Iterator
Implementation: `include/xieite/fn/range_udl.hpp` (lines 14-45)

```cpp
template<auto one_past, decltype(one_past) step>
struct iter {
    decltype(one_past) value;

    constexpr auto operator*() const noexcept;
    constexpr auto& operator++() noexcept;
    friend bool operator==(const iter&, const iter&) = default;
};
```

Iterator implementation for range literals with compile-time step calculation.

## Usage Examples

### Numeric Type Conversion
```cpp
#include <xieite/fn/number_udl.hpp>

// Explicit type casting at compile time
auto small_int = 42_i8;          // int8_t
auto big_int = 1000000_i64;      // int64_t
auto precise = 3.14159_f32;      // float32_t (if available)
auto boolean = 1_b;              // bool

// Character types
auto ascii_char = 65_c;          // char ('A')
auto wide_char = 65_cw;          // wchar_t
auto unicode = 0x1F600_c32;      // char32_t (emoji codepoint)

// Platform-specific sizes
auto ptr_sized = 0x12345678_up;  // uintptr_t
auto size_val = 1024_uz;         // size_t
```

### Physical Unit Conversions
```cpp
#include <xieite/fn/unit_udl.hpp>
using namespace xieite::unit_udl;

// Length measurements
auto distance_m = 5_km;          // 5 kilometers in meters
auto height_m = 6_ft;            // 6 feet converted to meters
auto precision_m = 250_mm;       // 250 millimeters in meters

// Area calculations
auto room_area = 20_sq_ft;       // 20 square feet in square meters
auto land_area = 2.5_ac;         // 2.5 acres in square meters

// Volume measurements
auto tank_vol = 50_gal;          // 50 gallons in liters
auto medicine_vol = 250_mL;      // 250 milliliters

// Temperature conversions
auto temp_k = 25_C;              // 25°C in Kelvin
auto fever_k = 101_F;            // 101°F in Kelvin

// Time periods
auto historical = 2_millenniums; // 2000 years
auto geological = 3_epochs;      // 3 geological epochs
```

### Range Creation and Iteration
```cpp
#include <xieite/fn/range_udl.hpp>
using namespace xieite::range_udl;

// Basic ranges
auto simple = "0.10"_range;      // 0 to 10, step 1
auto stepped = "0.10e2"_range;   // 0 to 10, step 2
auto reversed = "10.0"_range;    // 10 to 0 (descending)

// Range iteration
for (auto i : "1.5"_range) {
    std::cout << i << " ";       // Prints: 1 2 3 4 5
}

// Negative ranges
auto neg_range = "0.-5"_range;   // 0 to -5
for (auto val : neg_range) {
    std::cout << val << " ";     // Prints: 0 -1 -2 -3 -4 -5
}

// Custom step ranges
for (auto even : "0.10e2"_range) {
    std::cout << even << " ";    // Prints: 0 2 4 6 8 10
}
```

## Advanced Patterns

### Unit System Integration
```cpp
#include <xieite/fn/unit_udl.hpp>

class PhysicsCalculator {
public:
    static constexpr double kinetic_energy(double mass_kg, double velocity_ms) {
        return 0.5 * mass_kg * velocity_ms * velocity_ms;
    }

    static constexpr double gravitational_force(double mass1_kg, double mass2_kg, double distance_m) {
        constexpr double G = 6.67430e-11; // m³/kg/s²
        return G * mass1_kg * mass2_kg / (distance_m * distance_m);
    }
};

// Usage with unit literals
using namespace xieite::unit_udl;

auto car_mass = 1500.0;          // kg (base unit)
auto car_speed = (60_mi) / 3600.0; // Convert 60 mph to m/s approximation

auto ke = PhysicsCalculator::kinetic_energy(car_mass, car_speed);

// Distance calculations with unit mixing
auto earth_radius = 6371_km;     // Earth radius in meters
auto moon_distance = 384400_km;  // Moon distance in meters
auto grav_force = PhysicsCalculator::gravitational_force(
    5.972e24,    // Earth mass (kg)
    7.342e22,    // Moon mass (kg)
    moon_distance // Distance in meters
);
```

### Compile-Time Range Processing
```cpp
#include <xieite/fn/range_udl.hpp>

template<typename Range>
constexpr auto sum_range(Range&& range) {
    auto total = 0;
    for (auto val : range) {
        total += val;
    }
    return total;
}

template<typename Range>
constexpr auto count_range(Range&& range) {
    auto count = 0;
    for (auto val : range) {
        (void)val;  // Suppress unused variable warning
        ++count;
    }
    return count;
}

// Compile-time range calculations
using namespace xieite::range_udl;

constexpr auto sum = sum_range("1.10"_range);    // Sum of 1+2+3+...+10 = 55
constexpr auto count = count_range("0.5e2"_range); // Count of even numbers 0,2,4 = 3

static_assert(sum == 55);
static_assert(count == 3);
```

### Type-Safe Numeric Literals
```cpp
#include <xieite/fn/number_udl.hpp>

template<typename T>
class TypedValue {
private:
    T value_;

public:
    constexpr TypedValue(T value) : value_(value) {}
    constexpr T get() const { return value_; }
    constexpr explicit operator T() const { return value_; }
};

// Factory functions using literals
constexpr auto make_byte(unsigned long long val) {
    return TypedValue<std::uint8_t>(val);
}

constexpr auto make_word(unsigned long long val) {
    return TypedValue<std::uint16_t>(val);
}

// Usage
using namespace xieite::number_udl;

auto byte_val = make_byte(255_u8);     // TypedValue<uint8_t>
auto word_val = make_word(65535_u16);  // TypedValue<uint16_t>

// Compile-time validation
static_assert(byte_val.get() == 255);
static_assert(word_val.get() == 65535);
```

### Unit Conversion Pipeline
```cpp
#include <xieite/fn/unit_udl.hpp>

class UnitConverter {
public:
    template<typename From, typename To>
    static constexpr double convert(double value) {
        // This would be implemented with proper conversion factors
        // Simplified for demonstration
        return value; // Actual implementation would do proper conversion
    }

    template<typename Unit>
    static constexpr auto to_si(double value) {
        return value; // Convert to SI base unit
    }
};

// Conversion pipeline using unit literals
using namespace xieite::unit_udl;

auto process_measurements() {
    // Collect measurements in various units
    auto length_imperial = 10_ft;    // feet to meters
    auto area_metric = 100_sq_m;     // Already in square meters
    auto volume_us = 5_gal;          // gallons to liters
    auto temp_fahrenheit = 70_F;     // Fahrenheit to Kelvin

    // All converted to SI base units internally
    return std::make_tuple(length_imperial, area_metric, volume_us, temp_fahrenheit);
}
```

## Implementation Details

### Numeric Literal Strategy
The numeric literals (number_udl.hpp:18-492) employ:
- `consteval` for compile-time evaluation
- `static_cast` for explicit type conversion (lines 19, 23, etc.)
- Platform feature detection using `XIEITE_FEAT_*` macros (lines 146, 196, etc.)
- Support for both integer and floating-point input forms

### Unit System Architecture
The unit literals (unit_udl.hpp:7-1201) implement:
- Consistent naming pattern with SI prefixes
- Complete metric prefix coverage (quecto to quetta)
- Imperial and nautical unit integration
- Temperature scale conversions with proper offset handling
- All literals return values in SI base units

### Range Literal Parsing
The range literal system (range_udl.hpp:49-62) uses:
- Template parameter pack char expansion for compile-time string parsing
- `std::string_view` for substring processing (line 52)
- Delimiter detection for end point (`.`) and step (`e`) specification
- Automatic type deduction with signed/unsigned handling

### Iterator Implementation
The range iterator (range_udl.hpp:14-28) provides:
- Bidirectional iteration with automatic direction detection
- Step-aware increment using `xieite::closest` for boundary handling
- Compile-time range bounds checking
- STL-compatible iterator interface

## Performance Considerations

- **Compile-time evaluation**: All literal conversions happen at compile time
- **Zero runtime overhead**: Literals resolve to constant values
- **Template instantiation**: Range literals generate specialized iterator types
- **Unit conversions**: Mathematical operations performed at compile time

## Best Practices

1. **Use appropriate literal suffixes** - Choose the most specific type for your use case
2. **Leverage unit literals for clarity** - Express measurements in natural units
3. **Combine with constexpr functions** - Enable compile-time calculations
4. **Consider range literals for iteration** - More expressive than traditional loops

## Common Use Cases

### Scientific Computing
```cpp
using namespace xieite::unit_udl;

constexpr auto light_speed = 299792458.0; // m/s
constexpr auto planck_constant = 6.62607015e-34; // J⋅s

auto photon_energy(double wavelength_nm) {
    auto wavelength_m = wavelength_nm * 1e-9;
    return planck_constant * light_speed / wavelength_m;
}

// Red light photon energy
auto red_photon = photon_energy(650_nm); // Using nanometer literal
```

### Data Processing
```cpp
using namespace xieite::number_udl;
using namespace xieite::range_udl;

// Process data with explicit types
std::array<std::uint8_t, 256> lookup_table;

// Initialize with range literal
auto index = 0_uz;
for (auto i : "0.255"_range) {
    lookup_table[index++] = static_cast<std::uint8_t>(i);
}
```

### Configuration Systems
```cpp
struct SystemConfig {
    std::size_t buffer_size = 4_kB;        // Using hypothetical kB literal
    std::uint16_t port = 8080_u16;         // Explicit port type
    std::chrono::seconds timeout{30_i64};  // Duration with explicit type
};
```

## See Also

- [Function Composition](./composition.md) - Function combination utilities
- [Memoization](./memoization.md) - Function result caching
- [Combinator Patterns](./combinators.md) - Higher-order function utilities
- [Functional API Reference](../../reference/api/fn.md)