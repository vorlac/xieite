# Substitution Detection

## Overview

XIEITE provides substitution detection utilities based on C++20 concepts for template metaprogramming. These utilities enable SFINAE-like functionality through concept-based constraint satisfaction, allowing code to test whether template instantiations are valid without causing compilation errors.

## Core Substitution Detection

### Basic Satisfaction Testing
Implementation: `include/xieite/trait/is_satisfied.hpp` (lines 5-6)

```cpp
template<auto fn, typename... Ts>
concept is_satisfied = requires { fn.template operator()<Ts...>(); };
```

Tests whether a generic lambda or function object can be successfully instantiated with given types.

### Universal Satisfaction Testing
Implementation: `include/xieite/trait/is_satisfied_all.hpp` (lines 7-8)

```cpp
template<auto fn, typename... Ts>
concept is_satisfied_all = (... && xieite::is_satisfied<fn, Ts>);
```

Tests whether all types in a pack satisfy a given predicate.

### Existential Satisfaction Testing
Implementation: `include/xieite/trait/is_satisfied_any.hpp` (lines 7-8)

```cpp
template<auto fn, typename... Ts>
concept is_satisfied_any = (... || xieite::is_satisfied<fn, Ts>);
```

Tests whether any type in a pack satisfies a given predicate.

## Construction Detection Concepts

### Brace Construction Detection
Implementation: `include/xieite/trait/has_brace_ctor.hpp` (lines 7-9)

```cpp
template<typename T, typename... Args>
concept has_brace_ctor = requires(Args... args) { T { args... }; };
```

Detects whether a type can be brace-constructed from given arguments.

### Noexcept Brace Construction
Implementation: `include/xieite/trait/has_noex_brace_ctor.hpp` (lines 7-10)

```cpp
template<typename T, typename... Args>
concept has_noex_brace_ctor = requires(Args... args) {
    requires(noexcept(T { args... }));
};
```

Detects whether brace construction is guaranteed to be noexcept.

## Boolean Testability Detection

### Boolean Context Testing
Implementation: `include/xieite/trait/is_bool_testable.hpp` (lines 7-10)

```cpp
template<typename T>
concept is_bool_testable = requires(T&& x) {
    static_cast<bool>(XIEITE_FWD(x));
    static_cast<bool>(!XIEITE_FWD(x));
};
```

Detects whether a type can be used in boolean contexts.

## Array Bounds Detection

### Bounded Array Detection
Implementation: `include/xieite/trait/is_bounded_array.hpp` (lines 7-9)

```cpp
template<typename T, std::size_t length = -1uz>
concept is_bounded_array = ((length == -1uz) ? std::is_bounded_array_v<T>
    : requires { ([]<typename U>(xieite::type_id<U[length]>) {})(xieite::type_id<T>()); });
```

Detects bounded arrays with optional length specification.

## Usage Examples

### Basic Substitution Detection
```cpp
#include <xieite/trait/is_satisfied.hpp>

// Test if types have a specific member
auto has_size_member = []<typename T> requires(sizeof(std::declval<T>().size())) {};

static_assert(xieite::is_satisfied<has_size_member, std::vector<int>>);  // true
static_assert(!xieite::is_satisfied<has_size_member, int>);              // false

// Test if types can be added
auto can_add = []<typename T> requires(sizeof(std::declval<T>() + std::declval<T>())) {};

static_assert(xieite::is_satisfied<can_add, int>);         // true
static_assert(xieite::is_satisfied<can_add, double>);      // true
static_assert(!xieite::is_satisfied<can_add, std::mutex>); // false
```

### Universal and Existential Testing
```cpp
#include <xieite/trait/is_satisfied_all.hpp>
#include <xieite/trait/is_satisfied_any.hpp>

// Check if all types are arithmetic
auto is_arithmetic = []<typename T> requires(std::is_arithmetic_v<T>) {};

static_assert(xieite::is_satisfied_all<is_arithmetic, int, double, float>);    // true
static_assert(!xieite::is_satisfied_all<is_arithmetic, int, std::string>);     // false

// Check if any type is a pointer
auto is_pointer = []<typename T> requires(std::is_pointer_v<T>) {};

static_assert(xieite::is_satisfied_any<is_pointer, int, char*, double>);       // true
static_assert(!xieite::is_satisfied_any<is_pointer, int, char, double>);       // false
```

### Construction Detection
```cpp
#include <xieite/trait/has_brace_ctor.hpp>
#include <xieite/trait/has_noex_brace_ctor.hpp>

struct Constructible {
    Constructible(int, double) {}
};

struct NonConstructible {
    NonConstructible(int, double) = delete;
};

static_assert(xieite::has_brace_ctor<Constructible, int, double>);     // true
static_assert(!xieite::has_brace_ctor<NonConstructible, int, double>); // false

// Test noexcept construction
struct NoexceptConstructible {
    NoexceptConstructible(int) noexcept {}
};

static_assert(xieite::has_noex_brace_ctor<NoexceptConstructible, int>); // true
static_assert(!xieite::has_noex_brace_ctor<Constructible, int, double>); // false (not noexcept)
```

### Boolean Testability
```cpp
#include <xieite/trait/is_bool_testable.hpp>

struct BoolTestable {
    explicit operator bool() const { return true; }
    bool operator!() const { return false; }
};

struct NotBoolTestable {
    explicit operator bool() const = delete;
};

static_assert(xieite::is_bool_testable<bool>);           // true
static_assert(xieite::is_bool_testable<int>);            // true
static_assert(xieite::is_bool_testable<BoolTestable>);   // true
static_assert(!xieite::is_bool_testable<NotBoolTestable>); // false
```

## Advanced Patterns

### Template Constraint Factory
```cpp
template<typename ConstraintLambda>
class ConstraintFactory {
private:
    static constexpr auto constraint_ = ConstraintLambda{};

public:
    template<typename... Types>
    static constexpr bool test_all() {
        return xieite::is_satisfied_all<constraint_, Types...>;
    }

    template<typename... Types>
    static constexpr bool test_any() {
        return xieite::is_satisfied_any<constraint_, Types...>;
    }

    template<typename Type>
    static constexpr bool test() {
        return xieite::is_satisfied<constraint_, Type>;
    }
};

// Usage
constexpr auto has_reserve = []<typename T> requires(sizeof(std::declval<T>().reserve(0))) {};
using ReserveFactory = ConstraintFactory<decltype(has_reserve)>;

static_assert(ReserveFactory::test<std::vector<int>>());     // true
static_assert(!ReserveFactory::test<std::array<int, 5>>());  // false
```

### Concept-Based Type Filtering
```cpp
#include <xieite/meta/type_list.hpp>

// Filter types based on constraints
template<typename TypeList>
struct ConceptFilter {
    template<auto constraint>
    using where = TypeList::template filter<constraint>;

    template<auto constraint>
    static constexpr bool all_satisfy = TypeList::template all<constraint>;

    template<auto constraint>
    static constexpr bool any_satisfy = TypeList::template any<constraint>;
};

// Usage
using mixed_types = xieite::type_list<int, std::string, double, std::vector<int>>;
using filter = ConceptFilter<mixed_types>;

constexpr auto is_arithmetic = []<typename T> requires(std::is_arithmetic_v<T>) {};
constexpr auto has_size = []<typename T> requires(sizeof(std::declval<T>().size())) {};

using arithmetic_types = filter::where<is_arithmetic>;
// Result: type_list<int, double>

using container_types = filter::where<has_size>;
// Result: type_list<std::string, std::vector<int>>

static_assert(filter::any_satisfy<has_size>);      // true
static_assert(!filter::all_satisfy<is_arithmetic>); // false
```

### SFINAE-Style Function Overloading
```cpp
// Modern concept-based overloading replacing SFINAE
template<typename T>
void process(T&& value) requires xieite::is_satisfied<
    []<typename U> requires(sizeof(std::declval<U>().begin())) {},
    std::remove_cvref_t<T>
> {
    std::cout << "Processing container with " << value.size() << " elements\n";
    for (const auto& elem : value) {
        std::cout << elem << " ";
    }
}

template<typename T>
void process(T&& value) requires xieite::is_satisfied<
    []<typename U> requires(std::is_arithmetic_v<U>) {},
    std::remove_cvref_t<T>
> {
    std::cout << "Processing arithmetic value: " << value << "\n";
}

template<typename T>
void process(T&& value) requires (!xieite::is_satisfied<
    []<typename U> requires(sizeof(std::declval<U>().begin())) {},
    std::remove_cvref_t<T>
> && !std::is_arithmetic_v<std::remove_cvref_t<T>>) {
    std::cout << "Processing other type\n";
}

// Usage
process(std::vector{1, 2, 3});  // Container overload
process(42);                    // Arithmetic overload
process(std::make_unique<int>()); // Other overload
```

### Conditional Member Access
```cpp
template<typename T>
class ConditionalAccess {
private:
    T data_;

    static constexpr auto has_size = []<typename U> requires(sizeof(std::declval<U>().size())) {};
    static constexpr auto has_capacity = []<typename U> requires(sizeof(std::declval<U>().capacity())) {};

public:
    ConditionalAccess(T data) : data_(std::move(data)) {}

    // Only available if T has size() method
    auto size() const requires xieite::is_satisfied<has_size, T> {
        return data_.size();
    }

    // Only available if T has capacity() method
    auto capacity() const requires xieite::is_satisfied<has_capacity, T> {
        return data_.capacity();
    }

    // Always available
    const T& get() const { return data_; }
};

// Usage
ConditionalAccess vec_access{std::vector{1, 2, 3}};
std::cout << vec_access.size() << "\n";      // OK
std::cout << vec_access.capacity() << "\n";  // OK

ConditionalAccess array_access{std::array{1, 2, 3}};
// array_access.size();      // Compilation error - array doesn't have size()
// array_access.capacity();  // Compilation error - array doesn't have capacity()
std::cout << array_access.get().size() << "\n"; // OK - using std::array::size()
```

## Implementation Details

### Concept-Based Detection Strategy
The substitution detection utilities (is_satisfied.hpp:5-6) employ:
- C++20 `requires` expressions for constraint testing
- Generic lambda expressions as constraint predicates
- Template argument deduction for flexible type testing

### Fold Expression Integration
The universal/existential tests (is_satisfied_all.hpp, is_satisfied_any.hpp) use:
- C++17 fold expressions with logical operators (`&&`, `||`)
- Variadic template expansion over type packs
- Short-circuit evaluation for efficiency

### Construction Detection Implementation
The construction concepts (has_brace_ctor.hpp) utilize:
- Brace-initialization expressions within `requires` clauses
- Perfect forwarding for argument preservation
- Noexcept testing through nested `requires` expressions

### Boolean Testability Testing
The boolean concept (is_bool_testable.hpp) tests:
- Explicit conversion to `bool` type
- Logical negation operator availability
- Perfect forwarding for universal reference handling

## Performance Considerations

- **Compile-time evaluation**: All substitution detection happens at compile time
- **Template instantiation depth**: Complex constraints may increase compilation time
- **Concept caching**: Modern compilers cache concept evaluation results
- **SFINAE replacement**: Concepts provide cleaner error messages than traditional SFINAE

## Best Practices

1. **Use concept-based constraints over SFINAE** - Cleaner syntax and better error messages
2. **Keep constraint predicates simple** - Complex constraints slow compilation
3. **Leverage fold expressions for type pack testing** - More efficient than recursive templates
4. **Design composable constraints** - Build complex tests from simple building blocks

## Common Use Cases

### Generic Container Operations
```cpp
template<typename Container>
void safe_reserve(Container& c, std::size_t capacity)
requires xieite::is_satisfied<
    []<typename T> requires(sizeof(std::declval<T>().reserve(0))) {},
    Container
> {
    c.reserve(capacity);
}

// Only compiles for containers with reserve() method
std::vector<int> vec;
safe_reserve(vec, 100);  // OK

std::array<int, 5> arr;
// safe_reserve(arr, 100);  // Compilation error
```

### Type-Safe Serialization
```cpp
template<typename T>
void serialize(const T& obj)
requires xieite::is_satisfied<
    []<typename U> requires(sizeof(std::declval<U>().serialize())) {},
    T
> {
    obj.serialize();
}

template<typename T>
void serialize(const T& obj)
requires (!xieite::is_satisfied<
    []<typename U> requires(sizeof(std::declval<U>().serialize())) {},
    T
> && std::is_trivially_copyable_v<T>) {
    // Generic serialization for trivial types
    std::cout << "Serializing trivial type of size " << sizeof(T) << "\n";
}
```

## See Also

- [Concepts](../trait/concepts.md) - Concept-based design patterns
- [SFINAE Helpers](../trait/sfinae_helpers.md) - SFINAE utility patterns
- [Type Traits](../trait/classification.md) - Type classification utilities
- [Metaprogramming API Reference](../../reference/api/meta.md)