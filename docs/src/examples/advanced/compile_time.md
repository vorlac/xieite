# Compile-Time Examples

## Introduction

This guide demonstrates advanced compile-time computation techniques using XIEITE utilities. These examples showcase how to move complex calculations, data structure generation, and algorithm execution entirely to compile time, resulting in zero-runtime-cost abstractions and highly optimized code.

## Compile-Time Data Structures

### Fixed-Size Compile-Time Containers

```cpp
#include <xieite/meta/make_seq.hpp>
#include <xieite/fn/repeat.hpp>
#include <array>

// Compile-time vector with advanced operations
template<typename T, std::size_t MaxSize>
class constexpr_vector {
    std::array<T, MaxSize> data_{};
    std::size_t size_ = 0;

public:
    constexpr constexpr_vector() = default;

    constexpr constexpr_vector(std::initializer_list<T> init) {
        for (const auto& item : init) {
            if (size_ < MaxSize) {
                data_[size_++] = item;
            }
        }
    }

    constexpr void push_back(const T& value) {
        if (size_ < MaxSize) {
            data_[size_++] = value;
        }
    }

    constexpr T& operator[](std::size_t index) { return data_[index]; }
    constexpr const T& operator[](std::size_t index) const { return data_[index]; }

    constexpr std::size_t size() const { return size_; }
    constexpr bool empty() const { return size_ == 0; }

    // Compile-time algorithms using XIEITE utilities
    template<auto predicate>
    constexpr auto filter() const {
        constexpr_vector<T, MaxSize> result;
        for (std::size_t i = 0; i < size_; ++i) {
            if (predicate(data_[i])) {
                result.push_back(data_[i]);
            }
        }
        return result;
    }

    template<auto transform>
    constexpr auto map() const {
        using ReturnType = decltype(transform(std::declval<T>()));
        constexpr_vector<ReturnType, MaxSize> result;
        for (std::size_t i = 0; i < size_; ++i) {
            result.push_back(transform(data_[i]));
        }
        return result;
    }

    template<auto binary_op>
    constexpr T reduce(T initial) const {
        T result = initial;
        for (std::size_t i = 0; i < size_; ++i) {
            result = binary_op(result, data_[i]);
        }
        return result;
    }
};

// Compile-time map implementation
template<typename Key, typename Value, std::size_t MaxSize>
class constexpr_map {
    struct pair {
        Key key;
        Value value;
    };

    std::array<pair, MaxSize> data_{};
    std::size_t size_ = 0;

public:
    constexpr constexpr_map() = default;

    constexpr void insert(const Key& key, const Value& value) {
        // Check if key already exists
        for (std::size_t i = 0; i < size_; ++i) {
            if (data_[i].key == key) {
                data_[i].value = value;
                return;
            }
        }

        // Insert new pair
        if (size_ < MaxSize) {
            data_[size_++] = {key, value};
        }
    }

    constexpr const Value* find(const Key& key) const {
        for (std::size_t i = 0; i < size_; ++i) {
            if (data_[i].key == key) {
                return &data_[i].value;
            }
        }
        return nullptr;
    }

    constexpr std::size_t size() const { return size_; }
};

void compile_time_containers_example() {
    // Compile-time vector operations
    constexpr auto numbers = constexpr_vector<int, 20>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    constexpr auto evens = numbers.filter([](int x) { return x % 2 == 0; });
    constexpr auto squares = numbers.map([](int x) { return x * x; });
    constexpr auto sum = numbers.reduce([](int a, int b) { return a + b; }, 0);

    std::cout << "Original size: " << numbers.size() << '\n';
    std::cout << "Even numbers: " << evens.size() << '\n';
    std::cout << "Sum: " << sum << '\n';

    // Compile-time map operations
    constexpr auto config_map = []() {
        constexpr_map<const char*, int, 10> map;
        map.insert("width", 800);
        map.insert("height", 600);
        map.insert("depth", 32);
        return map;
    }();

    constexpr auto width = config_map.find("width");
    if constexpr (width != nullptr) {
        std::cout << "Width: " << *width << '\n';
    }
}
```

### Compile-Time String Processing

```cpp
#include <xieite/meta/make_seq.hpp>
#include <string_view>
#include <array>

// Advanced compile-time string utilities
template<std::size_t N>
struct compile_time_string {
    std::array<char, N> data;

    constexpr compile_time_string(const char (&str)[N]) {
        std::copy_n(str, N, data.begin());
    }

    constexpr std::size_t size() const { return N - 1; }  // Exclude null terminator
    constexpr std::string_view view() const { return {data.data(), size()}; }

    // Compile-time string concatenation
    template<std::size_t M>
    constexpr auto operator+(const compile_time_string<M>& other) const {
        constexpr auto new_size = N + M - 1;  // -1 for overlapping null terminators

        return [this, &other]<std::size_t... i, std::size_t... j>(
            xieite::seq<i...>, xieite::seq<j...>) {
            return compile_time_string<new_size>{{
                (i < N - 1 ? data[i] : other.data[j - (N - 1)])...
            }};
        }(xieite::make_seq<N - 1>, xieite::make_seq<new_size>);
    }

    // Compile-time character transformation
    template<auto transform>
    constexpr auto transform_chars() const {
        return [this]<std::size_t... i>(xieite::seq<i...>) {
            return compile_time_string<N>{{
                (i < N - 1 ? transform(data[i]) : '\0')...
            }};
        }(xieite::make_seq<N>);
    }

    // Compile-time substring
    template<std::size_t start, std::size_t length>
    constexpr auto substring() const {
        static_assert(start + length <= size(), "Substring out of bounds");

        return [this]<std::size_t... i>(xieite::seq<i...>) {
            return compile_time_string<length + 1>{{
                data[start + i]..., '\0'
            }};
        }(xieite::make_seq<length>);
    }

    // Compile-time character count
    constexpr std::size_t count(char ch) const {
        std::size_t result = 0;
        for (std::size_t i = 0; i < size(); ++i) {
            if (data[i] == ch) ++result;
        }
        return result;
    }
};

// Template deduction guide
template<std::size_t N>
compile_time_string(const char (&)[N]) -> compile_time_string<N>;

// Compile-time string processing functions
constexpr auto to_upper = [](char c) {
    return (c >= 'a' && c <= 'z') ? c - 'a' + 'A' : c;
};

constexpr auto to_lower = [](char c) {
    return (c >= 'A' && c <= 'Z') ? c - 'A' + 'a' : c;
};

void compile_time_string_example() {
    // All string operations happen at compile time
    constexpr auto hello = compile_time_string{"Hello"};
    constexpr auto world = compile_time_string{" World!"};
    constexpr auto greeting = hello + world;

    constexpr auto upper_greeting = greeting.template transform_chars<to_upper>();
    constexpr auto lower_greeting = greeting.template transform_chars<to_lower>();

    constexpr auto sub = greeting.template substring<0, 5>();  // "Hello"
    constexpr auto l_count = greeting.count('l');

    std::cout << "Greeting: " << greeting.view() << '\n';
    std::cout << "Upper: " << upper_greeting.view() << '\n';
    std::cout << "Lower: " << lower_greeting.view() << '\n';
    std::cout << "Substring: " << sub.view() << '\n';
    std::cout << "L count: " << l_count << '\n';
}
```

**Source Reference**: `include/xieite/meta/make_seq.hpp:8-11`

## Mathematical Computations

### Compile-Time Mathematical Constants and Functions

```cpp
#include <xieite/math/bit_size.hpp>
#include <xieite/meta/make_cxpr.hpp>
#include <xieite/fn/repeat.hpp>
#include <numbers>

// Advanced compile-time mathematical computations
template<typename T>
class compile_time_math {
public:
    // High-precision mathematical constants
    static constexpr T pi = static_cast<T>(3.1415926535897932384626433832795);
    static constexpr T e = static_cast<T>(2.7182818284590452353602874713527);
    static constexpr T golden_ratio = static_cast<T>(1.6180339887498948482045868343656);

    // Compile-time power function with integer exponent
    static constexpr T power(T base, int exponent) {
        if (exponent == 0) return T{1};
        if (exponent < 0) return T{1} / power(base, -exponent);

        T result = T{1};
        for (int i = 0; i < exponent; ++i) {
            result *= base;
        }
        return result;
    }

    // Compile-time factorial
    static constexpr T factorial(int n) {
        if (n <= 1) return T{1};
        T result = T{1};
        for (int i = 2; i <= n; ++i) {
            result *= static_cast<T>(i);
        }
        return result;
    }

    // Compile-time sine approximation using Taylor series
    static constexpr T sine(T x, int terms = 20) {
        T result = x;
        T term = x;

        for (int n = 1; n < terms; ++n) {
            term *= -x * x / ((2 * n) * (2 * n + 1));
            result += term;
        }
        return result;
    }

    // Compile-time cosine approximation
    static constexpr T cosine(T x, int terms = 20) {
        T result = T{1};
        T term = T{1};

        for (int n = 1; n < terms; ++n) {
            term *= -x * x / ((2 * n - 1) * (2 * n));
            result += term;
        }
        return result;
    }

    // Compile-time exponential function
    static constexpr T exp(T x, int terms = 30) {
        T result = T{1};
        T term = T{1};

        for (int n = 1; n < terms; ++n) {
            term *= x / n;
            result += term;
        }
        return result;
    }

    // Compile-time natural logarithm (for x near 1)
    static constexpr T ln(T x, int terms = 50) {
        if (x <= 0) return std::numeric_limits<T>::quiet_NaN();
        if (x == 1) return T{0};

        T y = (x - 1) / (x + 1);
        T y_squared = y * y;
        T result = y;
        T term = y;

        for (int n = 1; n < terms; ++n) {
            term *= y_squared;
            result += term / (2 * n + 1);
        }
        return 2 * result;
    }
};

// Compile-time numerical integration
template<typename T, auto function, T start, T end, int subdivisions = 1000>
constexpr T integrate() {
    constexpr T step = (end - start) / subdivisions;
    T result = T{0};

    // Simpson's rule implementation
    for (int i = 0; i <= subdivisions; ++i) {
        T x = start + i * step;
        T weight = (i == 0 || i == subdivisions) ? T{1} :
                   (i % 2 == 1) ? T{4} : T{2};
        result += weight * function(x);
    }

    return result * step / 3;
}

void compile_time_math_example() {
    using Math = compile_time_math<double>;

    // All computations happen at compile time
    constexpr auto pi_approx = Math::pi;
    constexpr auto e_approx = Math::e;
    constexpr auto sine_pi_half = Math::sine(Math::pi / 2);
    constexpr auto cosine_pi = Math::cosine(Math::pi);
    constexpr auto exp_one = Math::exp(1.0);
    constexpr auto ln_e = Math::ln(Math::e);
    constexpr auto factorial_10 = Math::factorial(10);

    std::cout << "π ≈ " << pi_approx << '\n';
    std::cout << "e ≈ " << e_approx << '\n';
    std::cout << "sin(π/2) ≈ " << sine_pi_half << '\n';
    std::cout << "cos(π) ≈ " << cosine_pi << '\n';
    std::cout << "e^1 ≈ " << exp_one << '\n';
    std::cout << "ln(e) ≈ " << ln_e << '\n';
    std::cout << "10! = " << factorial_10 << '\n';

    // Compile-time numerical integration
    constexpr auto quadratic = [](double x) { return x * x; };
    constexpr auto integral_result = integrate<double, quadratic, 0.0, 2.0>();
    std::cout << "∫₀² x² dx ≈ " << integral_result << '\n';
}
```

**Source Reference**: `include/xieite/math/bit_size.hpp:9-13`, `include/xieite/meta/make_cxpr.hpp:10-16`

## Compile-Time Algorithms

### Advanced Sorting and Searching

```cpp
#include <xieite/meta/make_seq.hpp>
#include <array>
#include <algorithm>

// Compile-time sorting algorithms
template<typename T, std::size_t N>
class compile_time_algorithms {
public:
    // Compile-time bubble sort
    static constexpr std::array<T, N> bubble_sort(std::array<T, N> arr) {
        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t j = 0; j < N - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    T temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
        return arr;
    }

    // Compile-time quick sort
    static constexpr std::array<T, N> quick_sort(std::array<T, N> arr) {
        if constexpr (N <= 1) {
            return arr;
        } else {
            return quick_sort_impl(arr, 0, N - 1);
        }
    }

    // Compile-time binary search
    template<std::size_t M>
    static constexpr int binary_search(const std::array<T, M>& arr, T target) {
        int left = 0;
        int right = static_cast<int>(M) - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (arr[mid] == target) {
                return mid;
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;  // Not found
    }

    // Compile-time merge sort
    static constexpr std::array<T, N> merge_sort(std::array<T, N> arr) {
        if constexpr (N <= 1) {
            return arr;
        } else {
            constexpr std::size_t mid = N / 2;

            auto left = extract_subarray<0, mid>(arr);
            auto right = extract_subarray<mid, N - mid>(arr);

            auto sorted_left = compile_time_algorithms<T, mid>::merge_sort(left);
            auto sorted_right = compile_time_algorithms<T, N - mid>::merge_sort(right);

            return merge_arrays(sorted_left, sorted_right);
        }
    }

private:
    static constexpr std::array<T, N> quick_sort_impl(std::array<T, N> arr, int low, int high) {
        if (low < high) {
            int pivot = partition(arr, low, high);
            arr = quick_sort_impl(arr, low, pivot - 1);
            arr = quick_sort_impl(arr, pivot + 1, high);
        }
        return arr;
    }

    static constexpr int partition(std::array<T, N>& arr, int low, int high) {
        T pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; ++j) {
            if (arr[j] < pivot) {
                ++i;
                T temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        T temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        return i + 1;
    }

    template<std::size_t start, std::size_t count>
    static constexpr std::array<T, count> extract_subarray(const std::array<T, N>& arr) {
        return [&arr]<std::size_t... i>(xieite::seq<i...>) {
            return std::array<T, count>{arr[start + i]...};
        }(xieite::make_seq<count>);
    }

    template<std::size_t L, std::size_t R>
    static constexpr std::array<T, L + R> merge_arrays(
        const std::array<T, L>& left, const std::array<T, R>& right) {

        std::array<T, L + R> result{};
        std::size_t i = 0, j = 0, k = 0;

        while (i < L && j < R) {
            if (left[i] <= right[j]) {
                result[k++] = left[i++];
            } else {
                result[k++] = right[j++];
            }
        }

        while (i < L) result[k++] = left[i++];
        while (j < R) result[k++] = right[j++];

        return result;
    }
};

void compile_time_algorithms_example() {
    // All sorting happens at compile time
    constexpr std::array<int, 10> unsorted = {64, 34, 25, 12, 22, 11, 90, 88, 5, 77};

    constexpr auto bubble_sorted = compile_time_algorithms<int, 10>::bubble_sort(unsorted);
    constexpr auto quick_sorted = compile_time_algorithms<int, 10>::quick_sort(unsorted);
    constexpr auto merge_sorted = compile_time_algorithms<int, 10>::merge_sort(unsorted);

    // Binary search on sorted array
    constexpr auto search_result = compile_time_algorithms<int, 10>::binary_search(bubble_sorted, 25);

    std::cout << "Original: ";
    for (auto x : unsorted) std::cout << x << " ";
    std::cout << '\n';

    std::cout << "Bubble sorted: ";
    for (auto x : bubble_sorted) std::cout << x << " ";
    std::cout << '\n';

    std::cout << "Quick sorted: ";
    for (auto x : quick_sorted) std::cout << x << " ";
    std::cout << '\n';

    std::cout << "Merge sorted: ";
    for (auto x : merge_sorted) std::cout << x << " ";
    std::cout << '\n';

    std::cout << "Search for 25: index " << search_result << '\n';
}
```

### Compile-Time Graph Algorithms

```cpp
#include <xieite/meta/make_seq.hpp>
#include <array>
#include <limits>

// Compile-time graph representation and algorithms
template<std::size_t N>
class compile_time_graph {
    std::array<std::array<int, N>, N> adjacency_matrix_{};

public:
    constexpr compile_time_graph() {
        // Initialize with "infinity" (large value)
        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t j = 0; j < N; ++j) {
                adjacency_matrix_[i][j] = (i == j) ? 0 : 99999;
            }
        }
    }

    constexpr void add_edge(std::size_t from, std::size_t to, int weight) {
        adjacency_matrix_[from][to] = weight;
    }

    // Floyd-Warshall algorithm for all-pairs shortest paths
    constexpr auto all_pairs_shortest_paths() const {
        auto distances = adjacency_matrix_;

        for (std::size_t k = 0; k < N; ++k) {
            for (std::size_t i = 0; i < N; ++i) {
                for (std::size_t j = 0; j < N; ++j) {
                    int through_k = distances[i][k] + distances[k][j];
                    if (through_k < distances[i][j]) {
                        distances[i][j] = through_k;
                    }
                }
            }
        }

        return distances;
    }

    // Dijkstra's algorithm for single-source shortest paths
    constexpr std::array<int, N> dijkstra(std::size_t source) const {
        std::array<int, N> distances;
        std::array<bool, N> visited{};

        // Initialize distances
        for (std::size_t i = 0; i < N; ++i) {
            distances[i] = adjacency_matrix_[source][i];
        }
        distances[source] = 0;
        visited[source] = true;

        for (std::size_t count = 1; count < N; ++count) {
            // Find minimum distance vertex
            std::size_t min_vertex = 0;
            int min_distance = 99999;

            for (std::size_t v = 0; v < N; ++v) {
                if (!visited[v] && distances[v] < min_distance) {
                    min_distance = distances[v];
                    min_vertex = v;
                }
            }

            visited[min_vertex] = true;

            // Update distances
            for (std::size_t v = 0; v < N; ++v) {
                if (!visited[v] && adjacency_matrix_[min_vertex][v] != 99999) {
                    int new_distance = distances[min_vertex] + adjacency_matrix_[min_vertex][v];
                    if (new_distance < distances[v]) {
                        distances[v] = new_distance;
                    }
                }
            }
        }

        return distances;
    }

    // Check if graph is connected
    constexpr bool is_connected() const {
        auto distances = all_pairs_shortest_paths();

        for (std::size_t i = 0; i < N; ++i) {
            for (std::size_t j = 0; j < N; ++j) {
                if (distances[i][j] == 99999) {
                    return false;
                }
            }
        }
        return true;
    }
};

void compile_time_graph_example() {
    // Create and analyze graph at compile time
    constexpr auto graph = []() {
        compile_time_graph<5> g;
        g.add_edge(0, 1, 4);
        g.add_edge(0, 2, 2);
        g.add_edge(1, 2, 1);
        g.add_edge(1, 3, 5);
        g.add_edge(2, 3, 8);
        g.add_edge(2, 4, 10);
        g.add_edge(3, 4, 2);
        return g;
    }();

    constexpr auto shortest_from_0 = graph.dijkstra(0);
    constexpr auto all_pairs = graph.all_pairs_shortest_paths();
    constexpr auto connected = graph.is_connected();

    std::cout << "Shortest distances from vertex 0:\n";
    for (std::size_t i = 0; i < 5; ++i) {
        std::cout << "To " << i << ": " << shortest_from_0[i] << '\n';
    }

    std::cout << "Graph is connected: " << std::boolalpha << connected << '\n';
}
```

## Code Generation and Optimization

### Compile-Time Code Generation

```cpp
#include <xieite/meta/make_cxpr.hpp>
#include <xieite/fn/repeat.hpp>
#include <xieite/meta/make_seq.hpp>

// Automatic lookup table generation
template<auto function, typename T, T start, T end, T step = T{1}>
class compile_time_lookup_table {
    static constexpr std::size_t size = static_cast<std::size_t>((end - start) / step + 1);

    static constexpr auto generate_table() {
        std::array<decltype(function(start)), size> table{};

        T current = start;
        for (std::size_t i = 0; i < size; ++i) {
            table[i] = function(current);
            current += step;
        }

        return table;
    }

    static constexpr auto lookup_table = generate_table();

public:
    static constexpr auto lookup(T value) {
        if (value < start || value > end) {
            return function(value);  // Fallback to computation
        }

        std::size_t index = static_cast<std::size_t>((value - start) / step);
        return lookup_table[index];
    }

    static constexpr std::size_t table_size() { return size; }
};

// Automatic switch statement generation
template<auto handler, std::size_t N>
constexpr auto make_jump_table() {
    return [](unsigned char value) {
        xieite::make_cxpr([handler](auto constant_value) {
            handler.template operator()<constant_value>();
        }, value);
    };
}

// Compile-time finite state machine generation
template<typename StateEnum, auto transition_table, StateEnum initial_state>
class compile_time_fsm {
    StateEnum current_state = initial_state;

public:
    template<auto event>
    constexpr void process_event() {
        constexpr auto new_state = transition_table.template get_transition<current_state, event>();
        current_state = new_state;
    }

    constexpr StateEnum get_state() const { return current_state; }

    // Generate optimized state machine code
    template<auto event_sequence>
    static constexpr StateEnum process_sequence() {
        StateEnum state = initial_state;

        return [&state]<auto... events>(xieite::seq<events...>) {
            ((state = transition_table.template get_transition<state, events>()), ...);
            return state;
        }(event_sequence);
    }
};

void compile_time_code_generation_example() {
    // Sine lookup table generated at compile time
    constexpr auto sine_func = [](double x) { return std::sin(x); };
    using SineLookup = compile_time_lookup_table<sine_func, double, 0.0, 6.28, 0.01>;

    constexpr auto sine_pi_half = SineLookup::lookup(1.57);
    std::cout << "sin(π/2) from lookup: " << sine_pi_half << '\n';
    std::cout << "Lookup table size: " << SineLookup::table_size() << '\n';

    // Square lookup table
    constexpr auto square_func = [](int x) { return x * x; };
    using SquareLookup = compile_time_lookup_table<square_func, int, 0, 100>;

    constexpr auto square_42 = SquareLookup::lookup(42);
    std::cout << "42² from lookup: " << square_42 << '\n';

    // Jump table example
    constexpr auto handler = []<unsigned char value>() {
        std::cout << "Handling value: " << static_cast<int>(value) << '\n';
    };

    constexpr auto jump_table = make_jump_table<handler, 256>();
    jump_table(65);  // Will call handler<65>()
}
```

**Source Reference**: `include/xieite/meta/make_cxpr.hpp:10-16`

## Performance Analysis

### Compile-Time vs Runtime Comparison

```cpp
#include <chrono>
#include <iostream>

// Runtime version for comparison
double runtime_fibonacci(int n) {
    if (n <= 1) return n;
    return runtime_fibonacci(n - 1) + runtime_fibonacci(n - 2);
}

// Compile-time version
constexpr double compile_time_fibonacci(int n) {
    if (n <= 1) return n;

    double a = 0, b = 1;
    for (int i = 2; i <= n; ++i) {
        double temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

void performance_comparison() {
    constexpr int n = 40;

    // Compile-time computation (zero runtime cost)
    constexpr auto compile_time_result = compile_time_fibonacci(n);

    // Runtime computation (measured)
    auto start = std::chrono::high_resolution_clock::now();
    auto runtime_result = runtime_fibonacci(n);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Fibonacci(" << n << "):\n";
    std::cout << "Compile-time result: " << compile_time_result << " (0μs)\n";
    std::cout << "Runtime result: " << runtime_result << " (" << duration.count() << "μs)\n";
    std::cout << "Speedup: ∞ (computed at compile time)\n";
}
```

These compile-time examples demonstrate how XIEITE utilities enable moving complex computations entirely to compile time, resulting in optimized code with zero runtime overhead. The techniques shown here are essential for building high-performance libraries and applications that leverage the full power of modern C++ template metaprogramming.