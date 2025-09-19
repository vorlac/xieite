# Template Metaprogramming

## Introduction

This guide demonstrates advanced template metaprogramming techniques using XIEITE's powerful metaprogramming utilities. These examples showcase sophisticated compile-time computation patterns, type manipulation, and template-based code generation that push the boundaries of modern C++ capabilities.

## Type List Manipulation

### Advanced Type List Operations

XIEITE's `type_list` provides comprehensive type sequence manipulation:

```cpp
#include <xieite/meta/type_list.hpp>
#include <iostream>
#include <string>

// Demonstrate comprehensive type list operations
void type_list_showcase() {
    using NumberTypes = xieite::type_list<int, float, double, long>;
    using StringTypes = xieite::type_list<std::string, const char*, std::string_view>;

    // Basic properties
    constexpr auto num_count = NumberTypes::size;
    constexpr auto has_float = NumberTypes::template has<float>;
    constexpr auto has_char = NumberTypes::template has<char>;

    std::cout << "Number types count: " << num_count << '\n';
    std::cout << "Has float: " << std::boolalpha << has_float << '\n';
    std::cout << "Has char: " << has_char << '\n';

    // Type access and indexing
    using FirstType = NumberTypes::at<0>;  // int
    using LastType = NumberTypes::at<3>;   // long
    constexpr auto float_index = NumberTypes::template idx_of<float>;

    std::cout << "Float index: " << float_index << '\n';

    // Type list transformations
    using CombinedTypes = NumberTypes::append_range<StringTypes>;
    using ReversedNumbers = NumberTypes::reverse<>;
    using NumberSlice = NumberTypes::slice<1, 3>;  // float, double

    constexpr auto combined_size = CombinedTypes::size;
    constexpr auto slice_size = NumberSlice::size;

    std::cout << "Combined size: " << combined_size << '\n';
    std::cout << "Slice size: " << slice_size << '\n';
}
```

**Source Reference**: `include/xieite/meta/type_list.hpp:18-252`

### Conditional Type Selection

```cpp
#include <xieite/meta/type_list.hpp>
#include <xieite/trait/is_arith.hpp>
#include <type_traits>

// Advanced type filtering and selection
template<typename TypeList>
class TypeAnalyzer {
public:
    // Filter arithmetic types
    using ArithmeticTypes = TypeList::template filter<
        []<typename T> requires(xieite::is_arith<T>) {}
    >;

    // Filter pointer types
    using PointerTypes = TypeList::template filter<
        []<typename T> requires(std::is_pointer_v<T>) {}
    >;

    // Filter const types
    using ConstTypes = TypeList::template filter<
        []<typename T> requires(std::is_const_v<T>) {}
    >;

    // Find largest type by size
    template<typename T, typename U>
    static constexpr auto size_compare = []<typename A, typename B> {
        return std::bool_constant<(sizeof(A) > sizeof(B))>{};
    };

    // Complex type transformations
    template<typename T>
    static constexpr auto add_pointer_transform = []<typename U> {
        return xieite::type_id<U*>{};
    };

    using PointerVersions = TypeList::template transform<1, add_pointer_transform<void>>;

    // Remove duplicates with custom comparator
    using UniqueTypes = TypeList::template dedup<
        []<typename T, typename U> requires(std::same_as<T, U>) {}
    >;

    static void analyze() {
        std::cout << "Original types: " << TypeList::size << '\n';
        std::cout << "Arithmetic types: " << ArithmeticTypes::size << '\n';
        std::cout << "Pointer types: " << PointerTypes::size << '\n';
        std::cout << "Const types: " << ConstTypes::size << '\n';
        std::cout << "Unique types: " << UniqueTypes::size << '\n';
    }
};

void advanced_type_filtering() {
    using MixedTypes = xieite::type_list<
        int, float*, const double, char, void*, const int, float*, bool
    >;

    TypeAnalyzer<MixedTypes>::analyze();
}
```

### Type List Algorithms

```cpp
#include <xieite/meta/type_list.hpp>
#include <xieite/meta/fold.hpp>

// Complex type list algorithms using fold operations
template<typename TypeList>
class TypeListAlgorithms {
public:
    // Calculate total size of all types
    static constexpr auto total_size_lambda = []<typename Acc, typename T> {
        return std::integral_constant<std::size_t, Acc::value + sizeof(T)>{};
    };

    using TotalSize = xieite::fold<
        total_size_lambda,
        std::integral_constant<std::size_t, 0>,
        typename TypeList::template apply<std::tuple>::type
    >;

    // Find maximum alignment requirement
    static constexpr auto max_align_lambda = []<typename Acc, typename T> {
        constexpr auto current_align = Acc::value;
        constexpr auto type_align = alignof(T);
        return std::integral_constant<std::size_t, std::max(current_align, type_align)>{};
    };

    // Create aligned storage for all types
    template<typename... Types>
    struct AlignedStorage {
        alignas(TypeListAlgorithms<xieite::type_list<Types...>>::max_alignment)
        std::byte storage[TypeListAlgorithms<xieite::type_list<Types...>>::total_size];
    };

    static constexpr std::size_t total_size = TotalSize::value;
    static constexpr std::size_t max_alignment =
        xieite::fold<max_align_lambda, std::integral_constant<std::size_t, 1>,
                     typename TypeList::template apply<std::tuple>::type>::value;
};

void type_list_algorithms_example() {
    using TestTypes = xieite::type_list<char, int, double, std::string>;
    using Algorithms = TypeListAlgorithms<TestTypes>;

    std::cout << "Total size: " << Algorithms::total_size << " bytes\n";
    std::cout << "Max alignment: " << Algorithms::max_alignment << " bytes\n";

    // Create storage optimized for all types
    Algorithms::AlignedStorage<char, int, double, std::string> storage;
    std::cout << "Storage size: " << sizeof(storage) << " bytes\n";
}
```

## Sequence Generation and Manipulation

### Compile-Time Integer Sequences

```cpp
#include <xieite/meta/make_seq.hpp>
#include <xieite/meta/seq.hpp>
#include <xieite/fn/repeat.hpp>

// Advanced sequence manipulation patterns
template<auto N>
class SequenceGenerator {
public:
    // Generate sequences with custom transformations
    template<auto transform>
    static constexpr auto make_transformed_seq() {
        return []<auto... i>(xieite::seq<i...>) {
            return xieite::seq<transform(i)...>{};
        }(xieite::make_seq<N>);
    }

    // Generate Fibonacci sequence at compile time
    static constexpr auto fibonacci_seq() {
        return []<auto... i>(xieite::seq<i...>) {
            constexpr auto fib = [](auto n) consteval {
                if constexpr (n <= 1) return n;
                else {
                    // Use recursive template to compute Fibonacci
                    return [](auto n, auto a = 0, auto b = 1) consteval {
                        return [n, a, b]<auto... steps>(xieite::seq<steps...>) consteval {
                            return ((steps < n) ? (a = a + b, b = a - b, void()) : void(), ...);
                        }(xieite::make_seq<n>), b;
                    }(n);
                }
            };
            return xieite::seq<fib(i)...>{};
        }(xieite::make_seq<N>);
    }

    // Generate prime number sequence
    static constexpr auto prime_seq() {
        constexpr auto is_prime = [](auto n) consteval {
            if constexpr (n < 2) return false;
            else if constexpr (n == 2) return true;
            else if constexpr (n % 2 == 0) return false;
            else {
                return []<auto... divisors>(xieite::seq<divisors...>) consteval {
                    return ((divisors == 0 || n % (divisors * 2 + 3) != 0) && ...);
                }(xieite::make_seq<(n / 2)>);
            }
        };

        return []<auto... i>(xieite::seq<i...>) {
            return xieite::seq<(is_prime(i) ? i : 0)...>{};
        }(xieite::make_seq<N>);
    }
};

void sequence_generation_example() {
    // Generate squares sequence
    constexpr auto square_transform = [](auto x) { return x * x; };
    constexpr auto squares = SequenceGenerator<10>::make_transformed_seq<square_transform>();

    // Generate Fibonacci sequence
    constexpr auto fibonacci = SequenceGenerator<15>::fibonacci_seq();

    // Generate primes
    constexpr auto primes = SequenceGenerator<30>::prime_seq();

    std::cout << "Sequences generated at compile time\n";
    std::cout << "Squares sequence has " << decltype(squares)::size << " elements\n";
    std::cout << "Fibonacci sequence has " << decltype(fibonacci)::size << " elements\n";
    std::cout << "Prime sequence has " << decltype(primes)::size << " elements\n";
}
```

**Source Reference**: `include/xieite/meta/make_seq.hpp:8-11`, `include/xieite/meta/seq.hpp:7-9`

## Advanced Template Patterns

### SFINAE and Concept-Based Overloading

```cpp
#include <xieite/trait/is_satisfied.hpp>
#include <xieite/trait/is_satisfied_all.hpp>
#include <xieite/pp/arrow.hpp>
#include <concepts>

// Advanced SFINAE patterns using XIEITE utilities
template<typename T>
class AdvancedTraits {
public:
    // Complex concept composition
    template<typename U>
    static constexpr auto is_complete_type = []<typename V> requires(sizeof(V) > 0) {};

    template<typename U>
    static constexpr auto is_default_constructible = []<typename V> requires(std::default_initializable<V>) {};

    template<typename U>
    static constexpr auto is_copyable = []<typename V> requires(std::copyable<V>) {};

    // Combine multiple conditions
    template<typename U>
    static constexpr bool is_usable_type =
        xieite::is_satisfied_all<is_complete_type<void>, U> &&
        xieite::is_satisfied_all<is_default_constructible<void>, U> &&
        xieite::is_satisfied_all<is_copyable<void>, U>;

    // Advanced overload resolution
    template<typename U>
    requires(is_usable_type<U>)
    static constexpr auto process_usable(U&& value)
        XIEITE_ARROW(std::forward<U>(value))

    template<typename U>
    requires(!is_usable_type<U> && std::convertible_to<U, T>)
    static constexpr auto process_convertible(U&& value)
        XIEITE_ARROW(static_cast<T>(std::forward<U>(value)))

    template<typename U>
    requires(!is_usable_type<U> && !std::convertible_to<U, T>)
    static constexpr auto process_fallback(U&&)
        XIEITE_ARROW(T{})
};

// Advanced template specialization patterns
template<typename T, typename = void>
struct AdvancedProcessor;

// Specialization for arithmetic types
template<xieite::is_arith T>
struct AdvancedProcessor<T> {
    static constexpr auto process(T value)
        XIEITE_ARROW(value * value)
};

// Specialization for container-like types
template<typename T>
requires requires(T t) { t.begin(); t.end(); t.size(); }
struct AdvancedProcessor<T> {
    static constexpr auto process(const T& container)
        XIEITE_ARROW(container.size())
};

// Specialization for callable types
template<typename T>
requires std::invocable<T>
struct AdvancedProcessor<T> {
    static constexpr auto process(T&& callable)
        XIEITE_ARROW(std::forward<T>(callable)())
};
```

### Template Recursion and Unrolling

```cpp
#include <xieite/fn/unroll.hpp>
#include <xieite/meta/make_seq.hpp>

// Advanced recursive template patterns
template<std::size_t Depth>
class RecursiveComputation {
public:
    // Recursive template for computing nested operations
    template<auto operation, typename T>
    static constexpr auto deep_apply(T value) {
        if constexpr (Depth == 0) {
            return value;
        } else {
            return RecursiveComputation<Depth - 1>::template deep_apply<operation>(
                operation(value)
            );
        }
    }

    // Template unrolling for performance
    template<typename T, auto operation>
    static constexpr auto unrolled_apply(T value) {
        return [value]<std::size_t... i>(xieite::seq<i...>) {
            return ((i < Depth ? (value = operation(value)) : value), ...);
        }(xieite::make_seq<Depth>);
    }

    // Compile-time loop unrolling with accumulation
    template<typename T, auto binary_op, auto unary_op>
    static constexpr auto accumulating_unroll(T initial) {
        return xieite::unroll<Depth>([initial, binary_op, unary_op]<std::size_t... i> {
            T acc = initial;
            ((acc = binary_op(acc, unary_op(static_cast<T>(i)))), ...);
            return acc;
        });
    }
};

void recursive_template_example() {
    // Define operations
    constexpr auto square = [](auto x) { return x * x; };
    constexpr auto increment = [](auto x) { return x + 1; };
    constexpr auto add = [](auto a, auto b) { return a + b; };

    // Deep recursive application
    constexpr auto result1 = RecursiveComputation<3>::deep_apply<square>(2.0);
    std::cout << "Deep square(3 times) of 2: " << result1 << '\n';

    // Unrolled application
    constexpr auto result2 = RecursiveComputation<5>::unrolled_apply<int, increment>(10);
    std::cout << "Increment 5 times from 10: " << result2 << '\n';

    // Accumulating unroll
    constexpr auto result3 = RecursiveComputation<10>::accumulating_unroll<int, add, square>(0);
    std::cout << "Sum of squares 0-9: " << result3 << '\n';
}
```

**Source Reference**: `include/xieite/fn/unroll.hpp` (referenced in type_list.hpp)

## Complex Metaprogramming Applications

### Compile-Time String Processing

```cpp
#include <xieite/meta/type_list.hpp>
#include <xieite/data/cxpr_str.hpp>
#include <array>

// Advanced compile-time string manipulation
template<std::size_t N>
struct CompileTimeString {
    std::array<char, N> data;

    constexpr CompileTimeString(const char (&str)[N]) {
        std::copy_n(str, N, data.begin());
    }

    constexpr std::size_t size() const { return N - 1; }  // Exclude null terminator
    constexpr const char* c_str() const { return data.data(); }

    // Advanced string operations using type lists
    template<char delimiter>
    constexpr auto split() const {
        // Count delimiters to determine number of parts
        constexpr auto delimiter_count = [this]() {
            std::size_t count = 0;
            for (std::size_t i = 0; i < size(); ++i) {
                if (data[i] == delimiter) ++count;
            }
            return count;
        }();

        // Split implementation using template metaprogramming
        return [this]<std::size_t... i>(xieite::seq<i...>) {
            // Complex splitting logic using compile-time computation
            return std::array<std::string_view, delimiter_count + 1>{/* split parts */};
        }(xieite::make_seq<delimiter_count + 1>);
    }

    // Template-based string transformation
    template<auto transform>
    constexpr auto transform_chars() const {
        return [this]<std::size_t... i>(xieite::seq<i...>) {
            return CompileTimeString<N>{{transform(data[i])...}};
        }(xieite::make_seq<N>);
    }
};

// Advanced template-based parser
template<typename Grammar>
class CompileTimeParser {
public:
    template<CompileTimeString input>
    static constexpr auto parse() {
        // Complex parsing logic using template metaprogramming
        return Grammar::template parse<input>();
    }
};

// Example grammar for simple expressions
struct SimpleExpressionGrammar {
    template<CompileTimeString input>
    static constexpr auto parse() {
        // Parsing implementation using type lists and sequences
        // This would implement a full recursive descent parser
        return /* parsed result */;
    }
};
```

### Template-Based State Machines

```cpp
#include <xieite/meta/type_list.hpp>
#include <xieite/trait/is_satisfied.hpp>

// Advanced state machine using template metaprogramming
template<typename StateList, typename EventList, typename TransitionTable>
class CompileTimeStateMachine {
public:
    template<typename CurrentState, typename Event>
    using next_state = typename TransitionTable::template transition<CurrentState, Event>;

    template<typename InitialState>
    class Instance {
        using current_state_type = InitialState;

    public:
        template<typename Event>
        constexpr auto process_event() const {
            using new_state = next_state<current_state_type, Event>;
            return Instance<new_state>{};
        }

        template<typename ExpectedState>
        constexpr bool is_in_state() const {
            return std::same_as<current_state_type, ExpectedState>;
        }

        // Advanced state queries using type list operations
        template<auto predicate>
        constexpr bool satisfies_condition() const {
            return xieite::is_satisfied<predicate, current_state_type>;
        }
    };
};

// Example state machine definition
struct IdleState {};
struct ProcessingState {};
struct ErrorState {};

struct StartEvent {};
struct CompleteEvent {};
struct ErrorEvent {};

struct TransitionTable {
    template<typename State, typename Event>
    struct transition;

    template<>
    struct transition<IdleState, StartEvent> { using type = ProcessingState; };

    template<>
    struct transition<ProcessingState, CompleteEvent> { using type = IdleState; };

    template<>
    struct transition<ProcessingState, ErrorEvent> { using type = ErrorState; };

    // Default transition (stay in same state)
    template<typename State, typename Event>
    struct transition { using type = State; };
};

void compile_time_state_machine_example() {
    using States = xieite::type_list<IdleState, ProcessingState, ErrorState>;
    using Events = xieite::type_list<StartEvent, CompleteEvent, ErrorEvent>;
    using StateMachine = CompileTimeStateMachine<States, Events, TransitionTable>;

    // Create state machine instance
    constexpr auto initial = StateMachine::Instance<IdleState>{};

    // Process events at compile time
    constexpr auto processing = initial.process_event<StartEvent>();
    constexpr auto completed = processing.process_event<CompleteEvent>();

    // State verification at compile time
    static_assert(initial.template is_in_state<IdleState>());
    static_assert(processing.template is_in_state<ProcessingState>());
    static_assert(completed.template is_in_state<IdleState>());

    std::cout << "State machine transitions verified at compile time\n";
}
```

## Performance Optimization Patterns

### Template Instantiation Control

```cpp
#include <xieite/meta/type_list.hpp>

// Advanced template instantiation optimization
template<typename TypeList>
class OptimizedProcessor {
private:
    // Minimize template instantiations using type erasure
    static void process_impl(void* data, std::size_t type_index);

    // Type index mapping using type lists
    template<typename T>
    static constexpr std::size_t type_index = TypeList::template idx_of<T>;

public:
    template<typename T>
    static void process(T& value) {
        // Only instantiate the interface, not the implementation
        process_impl(&value, type_index<T>);
    }

    // Batch processing to reduce instantiation overhead
    template<typename... Args>
    static void process_batch(Args&... args) {
        // Process all arguments efficiently
        (process(args), ...);
    }
};

// Explicit instantiation control
template<typename TypeList>
class ExplicitInstantiator {
public:
    // Force instantiation of specific patterns
    template<template<typename> class Template>
    static void instantiate_all() {
        TypeList::apply([](auto... type_ids) {
            (Template<typename decltype(type_ids)::type>{}, ...);
        });
    }

    // Selective instantiation based on conditions
    template<template<typename> class Template, auto condition>
    static void instantiate_conditional() {
        using FilteredTypes = typename TypeList::template filter<condition>;
        FilteredTypes::apply([](auto... type_ids) {
            (Template<typename decltype(type_ids)::type>{}, ...);
        });
    }
};
```

### Compile-Time Optimization Techniques

```cpp
#include <xieite/meta/make_seq.hpp>
#include <xieite/fn/repeat.hpp>

// Advanced compile-time optimization patterns
template<std::size_t N>
class OptimizedAlgorithms {
public:
    // Loop unrolling for maximum performance
    template<typename T, auto operation>
    static constexpr T unrolled_operation(T value) {
        return [value]<std::size_t... i>(xieite::seq<i...>) constexpr {
            T result = value;
            ((result = operation(result, i)), ...);
            return result;
        }(xieite::make_seq<N>);
    }

    // Template specialization for power-of-2 optimizations
    template<typename T>
    static constexpr T optimized_power(T base, std::size_t exponent) {
        if constexpr ((N & (N - 1)) == 0) {  // Power of 2
            // Use bit shifting optimization
            return base << (exponent * (N / 2));
        } else {
            // Use regular multiplication
            return [base, exponent]<std::size_t... i>(xieite::seq<i...>) constexpr {
                T result = T{1};
                ((i < exponent ? result *= base : void()), ...);
                return result;
            }(xieite::make_seq<32>);  // Reasonable upper limit
        }
    }

    // Cache-friendly data structure generation
    template<typename T>
    struct alignas(64) CacheAlignedArray {  // 64-byte cache line
        static constexpr std::size_t effective_size =
            ((N * sizeof(T) + 63) / 64) * 64 / sizeof(T);

        std::array<T, effective_size> data;

        constexpr T& operator[](std::size_t index) { return data[index]; }
        constexpr const T& operator[](std::size_t index) const { return data[index]; }
    };
};

void optimization_patterns_example() {
    constexpr auto multiply_add = [](auto acc, auto i) { return acc * 2 + i; };

    // Unrolled operation
    constexpr auto result = OptimizedAlgorithms<8>::unrolled_operation<int, multiply_add>(1);
    std::cout << "Unrolled result: " << result << '\n';

    // Optimized power calculation
    constexpr auto power_result = OptimizedAlgorithms<16>::optimized_power(2, 4);
    std::cout << "Optimized power: " << power_result << '\n';

    // Cache-aligned storage
    OptimizedAlgorithms<100>::CacheAlignedArray<double> cache_aligned_data;
    std::cout << "Cache-aligned array size: " << cache_aligned_data.data.size() << '\n';
}
```

## Best Practices for Advanced Templates

### Error Handling and Diagnostics

```cpp
#include <xieite/meta/type_list.hpp>

// Advanced template error handling
template<typename... Args>
class SafeTemplateProcessor {
public:
    // Comprehensive constraint checking
    static_assert(sizeof...(Args) > 0, "At least one argument required");
    static_assert(sizeof...(Args) <= 64, "Too many arguments (max 64)");

    using arg_list = xieite::type_list<Args...>;

    // Detect problematic type combinations
    static constexpr bool has_void = arg_list::template has<void>;
    static constexpr bool has_function_types = arg_list::template any<
        []<typename T> requires(std::is_function_v<T>) {}
    >;

    static_assert(!has_void, "void types not supported");
    static_assert(!has_function_types, "function types not supported");

    // Provide helpful error messages
    template<typename T>
    static constexpr void validate_type() {
        static_assert(std::is_object_v<T>,
            "Type must be an object type (not reference, function, or void)");
        static_assert(!std::is_abstract_v<T>,
            "Abstract types are not supported");
        static_assert(std::is_destructible_v<T>,
            "Type must be destructible");
    }

    // Safe processing with comprehensive checks
    template<auto processor>
    static constexpr auto safe_process() {
        // Validate all types before processing
        (validate_type<Args>(), ...);

        // Process with guaranteed safety
        return arg_list::apply(processor);
    }
};

// Template debugging utilities
template<typename T>
void debug_type() {
    std::cout << "Type: " << typeid(T).name() << '\n';
    std::cout << "Size: " << sizeof(T) << " bytes\n";
    std::cout << "Alignment: " << alignof(T) << " bytes\n";
    std::cout << "Trivial: " << std::is_trivial_v<T> << '\n';
    std::cout << "Standard layout: " << std::is_standard_layout_v<T> << '\n';
}

template<typename TypeList>
void debug_type_list() {
    std::cout << "Type list size: " << TypeList::size << '\n';
    TypeList::apply([](auto... type_ids) {
        (debug_type<typename decltype(type_ids)::type>(), ...);
    });
}
```

These advanced template metaprogramming examples demonstrate the sophisticated capabilities available through XIEITE's metaprogramming utilities. They showcase patterns for type manipulation, compile-time computation, performance optimization, and safe template design that are essential for building high-quality, efficient C++ libraries and applications.

The combination of XIEITE's utilities with modern C++20 features enables developers to create powerful abstractions that operate entirely at compile time, resulting in zero-runtime-cost solutions for complex programming problems.