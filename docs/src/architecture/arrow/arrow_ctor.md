# XIEITE_ARROW_CTOR

The `XIEITE_ARROW_CTOR` macro is a specialized constructor definition variant of the XIEITE Arrow macro family that enables concise constructor implementations with member initialization lists and optional constructor body execution. This macro combines arrow function syntax with constructor-specific features, providing a powerful tool for streamlined class construction patterns.

## Implementation

Located in `include/xieite/pp/arrow.hpp` at lines 52-58:

```cpp
#define XIEITE_ARROW_CTOR(_body, ...) \
    XIEITE_EVAL( \
        noexcept(XIEITE_OPT(_body)(noexcept(XIEITE_UNWRAP(_body)) &&)() DETAIL_XIEITE_ARROW_NOEX(&&, __VA_ARGS__)) \
        requires(requires { XIEITE_OPT(_body)(XIEITE_UNWRAP(_body);)() DETAIL_XIEITE_ARROW_NOEX(;, __VA_ARGS__); }) \
        : DETAIL_XIEITE_ARROW_INIT(__VA_ARGS__) \
        { XIEITE_UNWRAP(_body); } \
    )
```

## Architecture Analysis

### Macro Parameter Structure

The `XIEITE_ARROW_CTOR` macro handles constructor-specific patterns:

1. **`_body`**: Optional constructor body code (processed with `XIEITE_UNWRAP`)
2. **`__VA_ARGS__`**: Member initialization specifications

### Helper Macro Integration

The macro relies on specialized constructor helper macros:

- **`XIEITE_OPT`**: Handles optional body execution
- **`DETAIL_XIEITE_ARROW_INIT`**: Processes member initialization lists
- **`DETAIL_XIEITE_ARROW_NOEX`**: Calculates noexcept specifications for member initialization

### Member Initialization Processing

Located at line 68 in the same file:

```cpp
#define DETAIL_XIEITE_ARROW_INIT(_var, _value, ...) XIEITE_UNWRAP(XIEITE_UNWRAP(_var)) XIEITE_UNWRAP(_value)XIEITE_IF(XIEITE_WRAPPED(XIEITE_UNWRAP(_var)))(...)()__VA_OPT__(, DETAIL_XIEITE_ARROW_INIT_NEXT XIEITE_PAREN() (__VA_ARGS__))
```

This creates sophisticated member initialization handling that supports:
- Multiple member initialization
- Variadic constructor arguments
- Conditional initialization patterns

## Template Instantiation Mechanics

```cpp
// Usage example:
class Example {
    int value_;
    std::string name_;
    std::vector<int> data_;

public:
    // Constructor with initialization list and body
    template<typename T>
    Example(T&& initial_value) XIEITE_ARROW_CTOR(
        validate_input(initial_value),        // Optional body
        (value_, static_cast<int>(initial_value)),
        (name_, "default"),
        (data_, {1, 2, 3})
    )
};

// Expands approximately to:
template<typename T>
Example(T&& initial_value)
    noexcept(noexcept(validate_input(initial_value)) &&
             noexcept(static_cast<int>(initial_value)) &&
             noexcept(std::string("default")) &&
             noexcept(std::vector<int>({1, 2, 3})))
    requires(requires { validate_input(initial_value); static_cast<int>(initial_value); /* ... */ })
    : value_(static_cast<int>(initial_value)), name_("default"), data_({1, 2, 3})
{
    validate_input(initial_value);
}
```

## Constructor Definition Patterns

### Simple Member Initialization

```cpp
class Point {
    double x_, y_;
public:
    // Basic member initialization without body
    Point(double x, double y) XIEITE_ARROW_CTOR(
        ,                                     // Empty body
        (x_, x), (y_, y)
    )
};
```

### Constructor with Validation Body

```cpp
class SafeContainer {
    std::vector<int> data_;
    std::size_t max_size_;

public:
    template<typename Container>
    SafeContainer(Container&& input, std::size_t max_size) XIEITE_ARROW_CTOR(
        (validate_size(input.size(), max_size)),  // Validation in body
        (data_, std::forward<Container>(input)),
        (max_size_, max_size)
    )

private:
    void validate_size(std::size_t size, std::size_t max) {
        if (size > max) throw std::invalid_argument("Container too large");
    }
};
```

### Variadic Constructor Patterns

```cpp
template<typename... Types>
class VariadicHolder {
    std::tuple<Types...> data_;
    std::size_t count_;

public:
    // Variadic constructor with perfect forwarding
    template<typename... Args>
    VariadicHolder(Args&&... args) XIEITE_ARROW_CTOR(
        static_assert(sizeof...(Args) == sizeof...(Types)),  // Compile-time validation
        (data_, std::forward<Args>(args)...),
        (count_, sizeof...(Args))
    )
};
```

### Complex Initialization Patterns

```cpp
class ResourceManager {
    std::unique_ptr<Resource> primary_;
    std::vector<std::unique_ptr<Resource>> backups_;
    std::mutex mutex_;

public:
    template<typename... BackupArgs>
    ResourceManager(std::unique_ptr<Resource> primary, BackupArgs&&... backup_args) XIEITE_ARROW_CTOR(
        (initialize_logging(),               // Setup body
         register_cleanup_handler()),
        (primary_, std::move(primary)),
        (backups_, create_backups(std::forward<BackupArgs>(backup_args)...)),
        (mutex_)                             // Default initialization
    )

private:
    void initialize_logging() { /* logging setup */ }
    void register_cleanup_handler() { /* cleanup registration */ }

    template<typename... Args>
    std::vector<std::unique_ptr<Resource>> create_backups(Args&&... args) {
        return {std::make_unique<Resource>(std::forward<Args>(args))...};
    }
};
```

## Advanced Constructor Patterns

### SFINAE-Friendly Constructors

```cpp
template<typename T>
class ConditionalContainer {
    T data_;
    bool is_valid_;

public:
    // Enable different constructors based on type properties
    template<typename U = T>
        requires std::is_default_constructible_v<U>
    ConditionalContainer() XIEITE_ARROW_CTOR(
        ,                                     // No body needed
        (data_), (is_valid_, true)
    )

    template<typename U>
        requires std::is_convertible_v<U, T>
    ConditionalContainer(U&& value) XIEITE_ARROW_CTOR(
        (validate_input(value)),              // Input validation
        (data_, std::forward<U>(value)),
        (is_valid_, true)
    )

private:
    template<typename U>
    void validate_input(const U& value) {
        if constexpr (requires { value.validate(); }) {
            if (!value.validate()) is_valid_ = false;
        }
    }
};
```

### Perfect Forwarding Constructor

```cpp
template<typename T>
class UniversalWrapper {
    T wrapped_;
    std::string type_name_;

public:
    // Perfect forwarding with type deduction
    template<typename U>
        requires std::is_constructible_v<T, U>
    UniversalWrapper(U&& value) XIEITE_ARROW_CTOR(
        (record_construction_type<U>()),      // Type recording
        (wrapped_, std::forward<U>(value)),
        (type_name_, typeid(U).name())
    )

private:
    template<typename U>
    void record_construction_type() {
        // Log construction details
    }
};
```

### Delegating Constructor Patterns

```cpp
class ComplexClass {
    int value_;
    std::string description_;
    std::vector<double> coefficients_;

public:
    // Primary constructor
    ComplexClass(int value, std::string description, std::vector<double> coefficients) XIEITE_ARROW_CTOR(
        (validate_parameters(value, description, coefficients)),
        (value_, value),
        (description_, std::move(description)),
        (coefficients_, std::move(coefficients))
    )

    // Delegating constructor with defaults
    ComplexClass(int value) XIEITE_ARROW_CTOR(
        ,                                     // No additional body
        (value_, value),
        (description_, "default"),
        (coefficients_, {1.0, 0.0, 0.0})
    )

private:
    void validate_parameters(int value, const std::string& desc, const std::vector<double>& coeffs) {
        if (value < 0) throw std::invalid_argument("Value must be non-negative");
        if (desc.empty()) throw std::invalid_argument("Description cannot be empty");
        if (coeffs.empty()) throw std::invalid_argument("Coefficients cannot be empty");
    }
};
```

## Integration with XIEITE Systems

### With Type Traits

```cpp
#include <xieite/trait/is_container.hpp>
#include <xieite/pp/arrow.hpp>

template<typename Container>
class ContainerAdapter {
    Container data_;
    std::size_t cached_size_;

public:
    template<typename C>
        requires xieite::is_container<C>
    ContainerAdapter(C&& container) XIEITE_ARROW_CTOR(
        (cache_container_info()),
        (data_, std::forward<C>(container)),
        (cached_size_, data_.size())
    )

private:
    void cache_container_info() {
        // Cache additional container metadata
    }
};
```

### With Mathematical Utilities

```cpp
#include <xieite/math/abs.hpp>
#include <xieite/pp/arrow.hpp>

template<typename T>
class MathematicalVector {
    std::vector<T> components_;
    T magnitude_;

public:
    template<typename... Components>
        requires (std::is_convertible_v<Components, T> && ...)
    MathematicalVector(Components... components) XIEITE_ARROW_CTOR(
        ,                                     // No body needed
        (components_, {static_cast<T>(components)...}),
        (magnitude_, calculate_magnitude())
    )

private:
    T calculate_magnitude() {
        T sum{};
        for (const auto& component : components_) {
            sum += component * component;
        }
        return xieite::abs(sum);  // Use XIEITE's abs function
    }
};
```

### With System Utilities

```cpp
#include <xieite/sys/os.hpp>
#include <xieite/pp/arrow.hpp>

class PlatformAwareClass {
    std::string platform_info_;
    std::unique_ptr<PlatformSpecificData> data_;

public:
    PlatformAwareClass() XIEITE_ARROW_CTOR(
        (initialize_platform_specific()),
        (platform_info_, get_platform_string()),
        (data_, create_platform_data())
    )

private:
    void initialize_platform_specific() {
        // Platform-specific initialization
    }

    std::string get_platform_string() {
        // Use XIEITE platform detection
        return "Platform detected";
    }

    std::unique_ptr<PlatformSpecificData> create_platform_data() {
        // Create platform-appropriate data
        return std::make_unique<PlatformSpecificData>();
    }
};
```

## Exception Safety and Noexcept Specification

### Sophisticated Noexcept Calculation

The macro's noexcept specification considers both body and initialization:

```cpp
noexcept(XIEITE_OPT(_body)(noexcept(XIEITE_UNWRAP(_body)) &&)() DETAIL_XIEITE_ARROW_NOEX(&&, __VA_ARGS__))
```

This ensures the constructor is noexcept only when:
1. **Constructor body is noexcept** (if present)
2. **All member initializations are noexcept**

### Exception Safety Examples

```cpp
class SafeConstruction {
    int value_;
    std::string name_;

public:
    // Noexcept when all operations are noexcept
    SafeConstruction(int value) XIEITE_ARROW_CTOR(
        ,                                     // No throwing body
        (value_, value),                      // Arithmetic assignment (noexcept)
        (name_, "default")                    // String construction (may throw)
    ) // noexcept(false) due to string construction

    // Conditionally noexcept based on input
    template<typename T>
    SafeConstruction(T&& input) XIEITE_ARROW_CTOR(
        (process_input(input)),               // May or may not throw
        (value_, convert_safely(input)),
        (name_, "converted")
    ) // noexcept depends on process_input and convert_safely
};
```

## Performance Characteristics

### Zero-Cost Constructor Abstraction

The macro generates efficient constructor code without overhead:

```cpp
class EfficientClass {
    int a_, b_, c_;

public:
    EfficientClass(int a, int b, int c) XIEITE_ARROW_CTOR(
        ,                                     // No body overhead
        (a_, a), (b_, b), (c_, c)
    ) // Generates optimal initialization code
};
```

### Compile-Time Constructor Selection

```cpp
template<typename T>
class OptimizedConstruction {
    T data_;

public:
    template<typename U>
    OptimizedConstruction(U&& value) XIEITE_ARROW_CTOR(
        std::conditional_t<sizeof(U) <= sizeof(void*),
            small_type_optimization(),
            large_type_optimization()
        >(),
        (data_, std::forward<U>(value))
    )

private:
    void small_type_optimization() { /* optimized for small types */ }
    void large_type_optimization() { /* optimized for large types */ }
};
```

## Best Practices

### 1. Clear Member Initialization Order

```cpp
// Good: Clear initialization order
class WellOrdered {
    int first_;
    std::string second_;
    std::vector<int> third_;

public:
    WellOrdered(int f, std::string s, std::vector<int> t) XIEITE_ARROW_CTOR(
        ,
        (first_, f),                          // Initialize in declaration order
        (second_, std::move(s)),
        (third_, std::move(t))
    )
};
```

### 2. Meaningful Constructor Bodies

```cpp
// Good: Use body for validation and setup
class ValidatedClass {
    int value_;

public:
    ValidatedClass(int value) XIEITE_ARROW_CTOR(
        (validate_and_setup(value)),          // Clear purpose
        (value_, value)
    )

private:
    void validate_and_setup(int value) {
        if (value < 0) throw std::invalid_argument("Value must be non-negative");
        // Additional setup...
    }
};
```

### 3. Exception Safety Considerations

```cpp
// Good: Consider exception safety in member order
class ExceptionSafe {
    std::unique_ptr<Resource> resource_;     // Initialize first (can't throw after construction)
    std::string name_;                       // May throw, but safe if resource_ already initialized

public:
    ExceptionSafe(std::string name) XIEITE_ARROW_CTOR(
        ,
        (resource_, std::make_unique<Resource>()),  // Safe initialization order
        (name_, std::move(name))
    )
};
```

### 4. Template Constructor Documentation

```cpp
/**
 * @brief Constructs container adapter with perfect forwarding
 * @tparam Container Container type (must satisfy container concept)
 * @param container Source container to adapt
 * @note Uses perfect forwarding to preserve value category
 */
template<typename Container>
class DocumentedAdapter {
    Container data_;

public:
    template<typename C>
    DocumentedAdapter(C&& container) XIEITE_ARROW_CTOR(
        ,
        (data_, std::forward<C>(container))
    )
};
```

## Limitations and Considerations

### 1. Constructor Body Complexity

The macro is designed for simple constructor bodies:

```cpp
// Good: Simple validation
class Simple {
public:
    Simple(int value) XIEITE_ARROW_CTOR(
        (validate_simple(value)),             // Single function call
        (value_, value)
    )
};

// Consider traditional constructor for complex logic
class Complex {
public:
    Complex(int value) {                      // Traditional constructor preferred
        if (value < 0) {
            log_error("Negative value");
            value = 0;
        }
        initialize_subsystems();
        value_ = value;
        register_with_manager();
    }
};
```

### 2. Member Initialization Syntax

Complex member types may require careful handling:

```cpp
// Risk: Complex template types
class TemplateContainer {
    std::map<std::string, std::vector<int>> data_;

public:
    TemplateContainer() XIEITE_ARROW_CTOR(
        ,
        (data_, std::map<std::string, std::vector<int>>{})  // Complex type may cause parsing issues
    )
};

// Solution: Use type aliases
using MapType = std::map<std::string, std::vector<int>>;
class SafeContainer {
    MapType data_;

public:
    SafeContainer() XIEITE_ARROW_CTOR(
        ,
        (data_, MapType{})                    // Cleaner syntax
    )
};
```

### 3. Debugging Constructor Issues

Macro-generated constructors can complicate debugging:

```cpp
// Error messages may reference macro internals
class DebugDifficult {
public:
    DebugDifficult(int value) XIEITE_ARROW_CTOR(
        (problematic_validation(value)),      // Errors may be cryptic
        (member_, invalid_initialization(value))
    )
};
```

### 4. Template Instantiation Impact

Complex constructor patterns may affect compilation time:

```cpp
// Many template parameters increase compilation cost
template<typename T, typename U, typename V, typename W>
class ManyTemplates {
public:
    template<typename A, typename B, typename C, typename D>
    ManyTemplates(A&& a, B&& b, C&& c, D&& d) XIEITE_ARROW_CTOR(
        (complex_validation(a, b, c, d)),
        (member1_, std::forward<A>(a)),
        (member2_, std::forward<B>(b)),
        (member3_, std::forward<C>(c)),
        (member4_, std::forward<D>(d))
    ) // Complex template instantiation
};
```

## Comparison with Traditional Constructors

| Approach | Syntax Conciseness | Feature Support | Debugging Ease |
|----------|-------------------|-----------------|-----------------|
| Traditional Constructor | Verbose | Full C++ features | Excellent |
| `XIEITE_ARROW_CTOR` | **Concise** | **Arrow macro features** | Moderate |

### Selection Guidelines

```cpp
// Use XIEITE_ARROW_CTOR when:
// 1. Simple constructor logic
// 2. Want concise syntax
// 3. Benefit from automatic noexcept calculation
// 4. Using other arrow macros in codebase

// Example: Simple initialization (use ARROW_CTOR)
class Point {
public:
    Point(double x, double y) XIEITE_ARROW_CTOR(, (x_, x), (y_, y))
};

// Example: Complex logic (use traditional)
class ComplexClass {
public:
    ComplexClass(const Config& config) {
        // Multi-step initialization
        parse_config(config);
        initialize_subsystems();
        validate_state();
        x_ = processed_x;
        y_ = processed_y;
    }
};
```

---

*See also: [Constructor Patterns](../template_patterns.md) | [Member Initialization](../concepts.md) | [Arrow Macro Family](../arrow_macros.md)*