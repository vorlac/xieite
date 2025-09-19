# Custom Traits

## Overview

XIEITE demonstrates advanced patterns for creating custom type traits and concepts. These implementations show how to build complex type introspection utilities, function signature analysis, and concept-based constraints that extend beyond the standard library.

## Concept-Based Traits

### Constructor Detection
Implementation: `include/xieite/trait/has_ctor.hpp` (line 8), `include/xieite/trait/has_noex_ctor.hpp` (line 8)

```cpp
template<typename T, typename... Args>
concept has_ctor = std::is_constructible_v<T, Args...>;

template<typename T, typename... Args>
concept has_noex_ctor = std::is_nothrow_constructible_v<T, Args...>;
```

XIEITE provides concept wrappers for standard traits, offering cleaner syntax and better error messages.

## Function Signature Analysis

### Return Type Extraction
Implementation: `include/xieite/trait/get_fn_ret.hpp` (lines 8-164)

```cpp
template<typename T>
using get_fn_ret = /* extract return type from function signature */;
```

This trait handles all function types:
- Function pointers: `Ret(*)(Args...)`
- Member functions: `Ret(S::*)(Args...)`
- Function references with all cv-qualifiers
- Variadic functions
- Noexcept specifications

### Complex Function Analysis
The implementation uses extensive template specialization (get_fn_ret.hpp:11-159) to handle:
- All cv-qualifier combinations (const, volatile, const volatile)
- All reference qualifiers (&, &&)
- Both regular and variadic functions
- Member function pointers
- Noexcept specifications

## Custom Trait Patterns

### SFINAE-Based Detection
```cpp
namespace detail {
    template<typename T, typename = void>
    struct has_custom_method : std::false_type {};

    template<typename T>
    struct has_custom_method<T, std::void_t<
        decltype(std::declval<T>().custom_method())
    >> : std::true_type {};
}

template<typename T>
concept has_custom_method = detail::has_custom_method<T>::value;
```

### Concept Composition
```cpp
template<typename T>
concept complete_type = requires {
    // Type must be complete and constructible
    typename T;
    requires sizeof(T) > 0;
    requires std::constructible_from<T>;
};

template<typename T>
concept container_like = requires(T t) {
    // Container-like interface
    t.begin();
    t.end();
    t.size();
    typename T::value_type;
};
```

## Usage Examples

### Advanced Constructor Checking
```cpp
#include <xieite/trait/has_ctor.hpp>
#include <xieite/trait/has_noex_ctor.hpp>

template<typename T, typename... Args>
    requires xieite::has_ctor<T, Args...>
auto safe_construct(Args&&... args) {
    if constexpr (xieite::has_noex_ctor<T, Args...>) {
        return T{std::forward<Args>(args)...};
    } else {
        try {
            return T{std::forward<Args>(args)...};
        } catch (...) {
            return T{};  // Fallback to default construction
        }
    }
}

// Usage
auto obj1 = safe_construct<std::string>("Hello");     // noexcept
auto obj2 = safe_construct<std::vector<int>>(1000);   // may throw
```

### Function Return Type Analysis
```cpp
#include <xieite/trait/get_fn_ret.hpp>

template<typename Func>
void analyze_function() {
    using return_t = xieite::get_fn_ret<Func>;

    std::cout << "Return type: " << typeid(return_t).name() << "\n";

    if constexpr (std::is_void_v<return_t>) {
        std::cout << "Function returns void\n";
    } else {
        std::cout << "Function returns value\n";
    }
}

// Examples
void func1();
int func2(double);
auto lambda = [](int x) -> std::string { return std::to_string(x); };

analyze_function<decltype(func1)>();   // void
analyze_function<decltype(func2)>();   // int
analyze_function<decltype(lambda)>();  // std::string
```

### Custom Trait Implementation
```cpp
// Detect if type has specific member
template<typename T>
concept has_serialize = requires(T t, std::ostream& os) {
    t.serialize(os);
};

// Detect if type supports comparison
template<typename T>
concept totally_ordered = requires(const T& a, const T& b) {
    { a < b } -> std::convertible_to<bool>;
    { a <= b } -> std::convertible_to<bool>;
    { a > b } -> std::convertible_to<bool>;
    { a >= b } -> std::convertible_to<bool>;
    { a == b } -> std::convertible_to<bool>;
    { a != b } -> std::convertible_to<bool>;
};

// Use in templates
template<typename T>
    requires has_serialize<T> && totally_ordered<T>
void process_data(const std::vector<T>& data) {
    std::sort(data.begin(), data.end());
    for (const auto& item : data) {
        item.serialize(std::cout);
    }
}
```

## Advanced Trait Techniques

### Recursive Trait Detection
```cpp
// Detect nested containers
template<typename T>
concept nested_container = container_like<T> &&
    container_like<typename T::value_type>;

// Recursive depth calculation
template<typename T>
constexpr std::size_t container_depth() {
    if constexpr (container_like<T>) {
        return 1 + container_depth<typename T::value_type>();
    } else {
        return 0;
    }
}

// Usage
static_assert(container_depth<std::vector<int>>() == 1);
static_assert(container_depth<std::vector<std::vector<int>>>() == 2);
```

### Trait Composition Patterns
```cpp
// Combine multiple constraints
template<typename T>
concept serializable_container = container_like<T> &&
    has_serialize<typename T::value_type>;

// Optional capability detection
template<typename T>
concept optionally_hashable = requires {
    // Either has hash specialization or custom hash method
    std::hash<T>{}(std::declval<T>());
} || requires(const T& t) {
    t.hash();
};

// Compile-time capability branching
template<typename T>
auto get_hash(const T& value) {
    if constexpr (requires { std::hash<T>{}(value); }) {
        return std::hash<T>{}(value);
    } else if constexpr (requires { value.hash(); }) {
        return value.hash();
    } else {
        return std::size_t{0};  // Fallback
    }
}
```

### Template Metaprogramming Integration
```cpp
// Use with type lists
template<typename TypeList>
concept all_constructible = TypeList::template all<std::is_default_constructible>;

template<typename TypeList>
concept any_trivial = TypeList::template any<std::is_trivial>;

// Factory pattern with constraints
template<typename T>
    requires std::default_initializable<T>
auto make_default() -> std::unique_ptr<T> {
    return std::make_unique<T>();
}

template<typename T, typename... Args>
    requires std::constructible_from<T, Args...>
auto make_with_args(Args&&... args) -> std::unique_ptr<T> {
    return std::make_unique<T>(std::forward<Args>(args)...);
}
```

## Implementation Strategies

### SFINAE vs Concepts
```cpp
// SFINAE approach (pre-C++20)
template<typename T>
struct has_size_sfinae {
private:
    template<typename U>
    static auto test(int) -> decltype(std::declval<U>().size(), std::true_type{});

    template<typename>
    static std::false_type test(...);

public:
    static constexpr bool value = decltype(test<T>(0))::value;
};

// Concepts approach (C++20+)
template<typename T>
concept has_size_concept = requires(T t) {
    t.size();
};

// Hybrid approach for compatibility
#ifdef __cpp_concepts
    template<typename T>
    concept has_size = has_size_concept<T>;
#else
    template<typename T>
    constexpr bool has_size = has_size_sfinae<T>::value;
#endif
```

### Specialization Hierarchies
Following XIEITE's pattern from get_fn_ret.hpp:

```cpp
// Base case
template<typename T>
struct function_analyzer : std::false_type {
    using return_type = void;
    static constexpr std::size_t arity = 0;
};

// Function pointer specialization
template<typename Ret, typename... Args>
struct function_analyzer<Ret(*)(Args...)> : std::true_type {
    using return_type = Ret;
    static constexpr std::size_t arity = sizeof...(Args);
};

// Member function specialization
template<typename Ret, typename Class, typename... Args>
struct function_analyzer<Ret(Class::*)(Args...)> : std::true_type {
    using return_type = Ret;
    using class_type = Class;
    static constexpr std::size_t arity = sizeof...(Args);
};

// Continue with cv-qualified variants...
```

## Best Practices for Custom Traits

### 1. Clear Naming Conventions
```cpp
// Predicates: is_*, has_*, can_*
template<typename T> concept is_numeric = /*...*/;
template<typename T> concept has_iterator = /*...*/;
template<typename T> concept can_serialize = /*...*/;

// Transformations: add_*, remove_*, get_*
template<typename T> using add_optional = std::optional<T>;
template<typename T> using remove_optional = /*...*/;
template<typename T> using get_value_type = typename T::value_type;
```

### 2. Comprehensive Specialization
Following XIEITE's approach, handle all relevant cases:
- All cv-qualifier combinations
- Reference types (&, &&)
- Const/volatile member functions
- Noexcept specifications
- Variadic templates

### 3. Error Message Optimization
```cpp
template<typename T>
concept printable = requires(std::ostream& os, const T& t) {
    os << t;
} || requires(const T& t) {
    t.print();
};

template<typename T>
    requires printable<T>
void debug_print(const T& value) {
    if constexpr (requires(std::ostream& os) { os << value; }) {
        std::cout << value;
    } else {
        value.print();
    }
}
```

### 4. Performance Considerations
- Prefer concepts over SFINAE for better compile times
- Use `std::void_t` for simple SFINAE checks
- Minimize template instantiation depth
- Cache complex trait results with `inline constexpr` variables

## Testing Custom Traits

```cpp
// Comprehensive trait testing
struct TestType {
    void serialize(std::ostream&) const;
    std::size_t size() const;
    auto begin() { return data_.begin(); }
    auto end() { return data_.end(); }

private:
    std::vector<int> data_;
};

// Static assertions for verification
static_assert(has_serialize<TestType>);
static_assert(container_like<TestType>);
static_assert(serializable_container<TestType>);
static_assert(!totally_ordered<TestType>);  // Intentionally missing operators

// Runtime verification
void test_traits() {
    std::cout << "TestType is serializable: " << has_serialize<TestType> << "\n";
    std::cout << "Container depth: " << container_depth<TestType>() << "\n";
}
```

## See Also

- [Concepts](./concepts.md) - Core concept definitions
- [Type Classification](./classification.md) - Standard type categories
- [STL Extensions](./extensions.md) - Extended standard traits
- [Type Traits API Reference](../../reference/api/trait.md)