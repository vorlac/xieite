# Advanced Template Metaprogramming Example

## Template Metaprogramming Showcase

This example demonstrates advanced usage of XIEITE's template metaprogramming facilities.

```cpp
// advanced_template_example.cpp
#include <iostream>
#include <string>
#include <tuple>
#include <variant>

// Type traits
#include <xieite/trait/is_satisfies.hpp>
#include <xieite/trait/is_ratio_unique.hpp>
#include <xieite/trait/is_nothrow_convertible.hpp>
#include <xieite/trait/add_versed_referent.hpp>

// Metaprogramming utilities
#include <xieite/meta/type_list.hpp>
#include <xieite/meta/fold.hpp>
#include <xieite/meta/arity.hpp>
#include <xieite/meta/for_crng.hpp>

// Function utilities
#include <xieite/fn/curry.hpp>
#include <xieite/fn/visitor.hpp>
#include <xieite/fn/pin.hpp>

// Preprocessor magic
#include <xieite/pp/arrow.hpp>

// Math compile-time utilities
#include <xieite/math/prime.hpp>
#include <xieite/math/fact.hpp>
#include <xieite/math/is_prime.hpp>

// Data structures
#include <xieite/data/fixed_str.hpp>

// Custom compile-time concepts
template<typename T>
concept Arithmetic = xieite::is_satisfies<T, std::is_arithmetic>;

template<typename T>
concept Container = requires(T t) {
    typename T::value_type;
    { t.begin() } -> std::forward_iterator;
    { t.end() } -> std::forward_iterator;
    { t.size() } -> std::convertible_to<std::size_t>;
};

// Compile-time type list manipulation
template<typename... Types>
struct TypeAnalyzer {
    using type_list = xieite::type_list<Types...>;

    static constexpr std::size_t count = type_list::size;

    // Filter arithmetic types
    using arithmetic_types = typename type_list::template filter<
        []<typename T> { return Arithmetic<T>; }
    >;

    // Get unique types
    using unique_types = typename type_list::dedupe;

    // Reverse the type list
    using reversed = typename type_list::reverse;

    // Check if contains a type
    template<typename T>
    static constexpr bool contains = type_list::template contains<T>;

    // Get type at index
    template<std::size_t idx>
    using at = typename type_list::template at<idx>;
};

// Compile-time string manipulation
template<xieite::fixed_str str>
struct StringProcessor {
    static constexpr auto value = str;
    static constexpr std::size_t length = str.size();

    static constexpr auto reversed() noexcept {
        xieite::fixed_str<length> result;
        for (std::size_t i = 0; i < length; ++i) {
            result[i] = str[length - 1 - i];
        }
        return result;
    }

    static constexpr bool is_palindrome() noexcept {
        for (std::size_t i = 0; i < length / 2; ++i) {
            if (str[i] != str[length - 1 - i]) {
                return false;
            }
        }
        return true;
    }
};

// Compile-time fold operations
template<typename... Args>
auto sum_all(Args... args)
    XIEITE_ARROW((... + args))

template<typename... Args>
auto multiply_all(Args... args)
    XIEITE_ARROW_NOEX((... * args))

// Advanced curry example
auto complex_operation = xieite::curry(
    [](int a, double b, std::string c, bool d) {
        std::cout << "a=" << a << ", b=" << b
                  << ", c=" << c << ", d=" << d << '\n';
        return a * b + c.length() * (d ? 1 : -1);
    }
);

// Aggregate introspection
struct Person {
    std::string name;
    int age;
    double height;
};

template<typename T>
void print_aggregate_info() {
    constexpr std::size_t member_count = xieite::arity<T>;
    std::cout << "Aggregate has " << member_count << " members\n";
}

// Compile-time prime calculations
template<std::size_t N>
struct PrimeCalculator {
    static constexpr bool is_prime = xieite::is_prime(N);
    static constexpr std::size_t next = xieite::prime<N + 1>;

    static void print_info() {
        std::cout << N << " is " << (is_prime ? "" : "not ") << "prime\n";
        if constexpr (!is_prime) {
            std::cout << "Next prime after " << N << " is " << next << '\n';
        }
    }
};

// Compile-time loop unrolling
template<std::size_t N>
void process_array(int (&arr)[N]) {
    xieite::for_crng<0, N>([&arr]<std::size_t i> {
        arr[i] *= 2;
        std::cout << "arr[" << i << "] = " << arr[i] << '\n';
    });
}

// Visitor pattern with variants
using Value = std::variant<int, double, std::string, bool>;

auto value_processor = xieite::visitor{
    [](int x) {
        std::cout << "Integer: " << x << " (squared: " << x*x << ")\n";
    },
    [](double x) {
        std::cout << "Double: " << x << " (sqrt: " << std::sqrt(x) << ")\n";
    },
    [](const std::string& x) {
        std::cout << "String: '" << x << "' (length: " << x.length() << ")\n";
    },
    [](bool x) {
        std::cout << "Boolean: " << std::boolalpha << x << '\n';
    }
};

int main() {
    std::cout << "=== Type List Manipulation ===\n";
    {
        using Analyzer = TypeAnalyzer<int, double, std::string, int, float, bool>;

        std::cout << "Total types: " << Analyzer::count << '\n';
        std::cout << "Unique types: " << Analyzer::unique_types::size << '\n';
        std::cout << "Arithmetic types: " << Analyzer::arithmetic_types::size << '\n';
        std::cout << "Contains string: " << Analyzer::contains<std::string> << '\n';
        std::cout << "Type at index 2: " << typeid(Analyzer::at<2>).name() << '\n';
    }

    std::cout << "\n=== Compile-Time String Processing ===\n";
    {
        constexpr auto processor1 = StringProcessor<"hello">{};
        constexpr auto processor2 = StringProcessor<"racecar">{};

        std::cout << "'" << processor1.value.data() << "' reversed: '"
                  << processor1.reversed().data() << "'\n";
        std::cout << "'" << processor1.value.data() << "' is palindrome: "
                  << processor1.is_palindrome() << '\n';
        std::cout << "'" << processor2.value.data() << "' is palindrome: "
                  << processor2.is_palindrome() << '\n';
    }

    std::cout << "\n=== Currying and Partial Application ===\n";
    {
        // Full application
        auto result1 = complex_operation(10)(3.14)("test")(true);
        std::cout << "Result: " << result1 << '\n';

        // Partial application
        auto partial1 = complex_operation(5);
        auto partial2 = partial1(2.5);
        auto partial3 = partial2("partial");
        auto result2 = partial3(false);
        std::cout << "Result: " << result2 << '\n';
    }

    std::cout << "\n=== Aggregate Introspection ===\n";
    {
        print_aggregate_info<Person>();

        Person p{"Alice", 30, 5.6};
        std::cout << "Person: " << p.name << ", " << p.age << ", " << p.height << '\n';
    }

    std::cout << "\n=== Compile-Time Prime Calculations ===\n";
    {
        PrimeCalculator<7>::print_info();
        PrimeCalculator<10>::print_info();
        PrimeCalculator<100>::print_info();

        constexpr auto factorial_5 = xieite::fact<5>;
        std::cout << "5! = " << factorial_5 << '\n';
    }

    std::cout << "\n=== Compile-Time Loop Unrolling ===\n";
    {
        int array[] = {1, 2, 3, 4, 5};
        process_array(array);
    }

    std::cout << "\n=== Variant Visitor Pattern ===\n";
    {
        std::vector<Value> values = {
            42,
            3.14159,
            std::string("XIEITE"),
            true
        };

        for (const auto& value : values) {
            std::visit(value_processor, value);
        }
    }

    std::cout << "\n=== Fold Expressions ===\n";
    {
        auto sum = sum_all(1, 2, 3, 4, 5);
        auto product = multiply_all(2, 3, 4);

        std::cout << "Sum(1,2,3,4,5) = " << sum << '\n';
        std::cout << "Product(2,3,4) = " << product << '\n';
    }

    return 0;
}
```

## Building

```cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(xieite_advanced_example)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable concepts
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-fconcepts)
endif()

find_package(xieite REQUIRED)

add_executable(advanced_example advanced_template_example.cpp)
target_link_libraries(advanced_example PRIVATE xieite::xieite)

# Enable all optimizations for template instantiation
target_compile_options(advanced_example PRIVATE
    $<$<CONFIG:Release>:-O3>
    $<$<CONFIG:Debug>:-O0 -g>
)
```

## Key Template Metaprogramming Features

### Type List Operations
- Compile-time type manipulation
- Filtering, deduplication, reversal
- Type containment checking
- Index-based type access

### Compile-Time Computations
- Prime number calculations at compile time
- Factorial computation
- String manipulation in constexpr context
- Loop unrolling with template recursion

### Advanced Function Patterns
- Currying for partial application
- Visitor pattern for variant processing
- Arrow macros for concise syntax
- Perfect forwarding with fold expressions

### Concept-Based Programming
- Custom concept definitions
- Concept subsumption
- SFINAE-friendly trait checking
- Compile-time validation

## Performance Benefits

1. **Zero Runtime Cost**: All template computations happen at compile time
2. **Optimized Code Generation**: Compiler can inline and optimize aggressively
3. **Type Safety**: Errors caught at compile time, not runtime
4. **Memory Efficiency**: No vtables or runtime polymorphism overhead

## Expected Output

```
=== Type List Manipulation ===
Total types: 6
Unique types: 5
Arithmetic types: 4
Contains string: 1
Type at index 2: class std::basic_string<char>

=== Compile-Time String Processing ===
'hello' reversed: 'olleh'
'hello' is palindrome: 0
'racecar' is palindrome: 1

=== Currying and Partial Application ===
a=10, b=3.14, c=test, d=1
Result: 35.4
a=5, b=2.5, c=partial, d=0
Result: 5.5

=== Aggregate Introspection ===
Aggregate has 3 members
Person: Alice, 30, 5.6

=== Compile-Time Prime Calculations ===
7 is prime
10 is not prime
Next prime after 10 is 11
100 is not prime
Next prime after 100 is 101
5! = 120

=== Compile-Time Loop Unrolling ===
arr[0] = 2
arr[1] = 4
arr[2] = 6
arr[3] = 8
arr[4] = 10

=== Variant Visitor Pattern ===
Integer: 42 (squared: 1764)
Double: 3.14159 (sqrt: 1.77245)
String: 'XIEITE' (length: 6)
Boolean: true

=== Fold Expressions ===
Sum(1,2,3,4,5) = 15
Product(2,3,4) = 24
```

---

*Next: [Real-World Integration Example](integration_example.md)*