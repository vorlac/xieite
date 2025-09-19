# STL Integration

This document covers advanced integration patterns between XIEITE and the Standard Template Library (STL), demonstrating how to seamlessly combine XIEITE utilities with standard library components for maximum effectiveness.

## Container Integration

### Enhanced STL Containers

Augmenting STL containers with XIEITE utilities:

```cpp
#include <xieite/trait/is_arith.hpp>
#include <xieite/math/abs.hpp>
#include <xieite/fn/scope_guard.hpp>
#include <vector>
#include <algorithm>

template<xieite::is_arith T>
class enhanced_vector : private std::vector<T> {
    using base = std::vector<T>;

public:
    using typename base::value_type;
    using typename base::size_type;
    using typename base::iterator;
    using typename base::const_iterator;

    // Inherit constructors
    using base::base;

    // Expose standard interface
    using base::begin;
    using base::end;
    using base::size;
    using base::empty;
    using base::operator[];
    using base::at;
    using base::push_back;
    using base::pop_back;

    // XIEITE-enhanced operations
    void push_back_safe(const T& value) {
        auto guard = xieite::scope_guard([this] {
            if (!this->empty()) {
                this->pop_back();
            }
        });

        this->push_back(value);
        guard.dismiss();
    }

    // Arithmetic operations using XIEITE utilities
    T sum() const requires xieite::is_arith<T> {
        T result = T{};
        for (const auto& elem : *this) {
            result += elem;
        }
        return result;
    }

    T absolute_sum() const requires xieite::is_arith<T> {
        T result = T{};
        for (const auto& elem : *this) {
            result += xieite::abs(elem);
        }
        return result;
    }

    // Statistical operations
    std::optional<T> mean() const requires xieite::is_arith<T> {
        if (this->empty()) return std::nullopt;
        return sum() / static_cast<T>(this->size());
    }

    // Safe element access
    std::optional<T> safe_at(size_type index) const noexcept {
        if (index >= this->size()) {
            return std::nullopt;
        }
        return (*this)[index];
    }
};
```

### Custom Allocators with XIEITE

Integrating XIEITE patterns with STL allocators:

```cpp
#include <xieite/trait/is_arith.hpp>
#include <xieite/fn/scope_guard.hpp>
#include <memory>

template<typename T>
class tracking_allocator {
    static inline std::size_t total_allocated_ = 0;
    static inline std::size_t allocation_count_ = 0;

public:
    using value_type = T;

    tracking_allocator() = default;

    template<typename U>
    tracking_allocator(const tracking_allocator<U>&) noexcept {}

    T* allocate(std::size_t n) {
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T)) {
            throw std::bad_alloc{};
        }

        auto guard = xieite::scope_guard([this, n] {
            // Rollback on failure
            total_allocated_ -= n * sizeof(T);
            --allocation_count_;
        });

        total_allocated_ += n * sizeof(T);
        ++allocation_count_;

        T* ptr = static_cast<T*>(std::malloc(n * sizeof(T)));
        if (!ptr) {
            throw std::bad_alloc{};
        }

        guard.dismiss();
        return ptr;
    }

    void deallocate(T* ptr, std::size_t n) noexcept {
        total_allocated_ -= n * sizeof(T);
        --allocation_count_;
        std::free(ptr);
    }

    static std::size_t total_allocated() noexcept { return total_allocated_; }
    static std::size_t allocation_count() noexcept { return allocation_count_; }

    template<typename U>
    bool operator==(const tracking_allocator<U>&) const noexcept { return true; }

    template<typename U>
    bool operator!=(const tracking_allocator<U>&) const noexcept { return false; }
};

// Usage with STL containers
using tracked_vector = std::vector<int, tracking_allocator<int>>;
using tracked_string = std::basic_string<char, std::char_traits<char>, tracking_allocator<char>>;
```

## Algorithm Integration

### XIEITE-Enhanced Algorithms

Combining XIEITE utilities with STL algorithms:

```cpp
#include <xieite/trait/is_arith.hpp>
#include <xieite/math/abs.hpp>
#include <xieite/pp/arrow.hpp>
#include <algorithm>
#include <numeric>
#include <ranges>

namespace xieite_algorithms {

    // Enhanced find operations
    template<std::ranges::input_range Range, typename T>
    requires xieite::is_arith<T>
    auto find_closest(Range&& range, T target) {
        auto it = std::ranges::min_element(range, [target](const auto& a, const auto& b) {
            return xieite::abs(a - target) < xieite::abs(b - target);
        });
        return it;
    }

    // Safe accumulate with overflow checking
    template<std::ranges::input_range Range>
    requires xieite::is_arith<std::ranges::range_value_t<Range>>
    auto safe_accumulate(Range&& range) -> std::optional<std::ranges::range_value_t<Range>> {
        using T = std::ranges::range_value_t<Range>;

        if (std::ranges::empty(range)) {
            return T{};
        }

        T result = T{};
        for (const auto& elem : range) {
            // Check for overflow before addition
            if constexpr (std::is_integral_v<T>) {
                if (elem > 0 && result > std::numeric_limits<T>::max() - elem) {
                    return std::nullopt; // Overflow would occur
                }
                if (elem < 0 && result < std::numeric_limits<T>::min() - elem) {
                    return std::nullopt; // Underflow would occur
                }
            }
            result += elem;
        }

        return result;
    }

    // Transform with XIEITE utilities
    template<std::ranges::input_range Range, typename Func>
    auto transform_safe(Range&& range, Func&& func) {
        std::vector<std::invoke_result_t<Func, std::ranges::range_value_t<Range>>> result;
        result.reserve(std::ranges::size(range));

        std::ranges::transform(range, std::back_inserter(result), std::forward<Func>(func));
        return result;
    }

    // Partition with arithmetic predicates
    template<std::ranges::forward_range Range>
    requires xieite::is_arith<std::ranges::range_value_t<Range>>
    auto partition_by_sign(Range&& range) {
        using T = std::ranges::range_value_t<Range>;

        return std::ranges::partition(range, [](const T& value) {
            return value >= T{};
        });
    }

} // namespace xieite_algorithms
```

### Custom Iterators

Creating XIEITE-aware iterators:

```cpp
#include <xieite/trait/is_arith.hpp>
#include <xieite/math/abs.hpp>
#include <iterator>

template<xieite::is_arith T>
class arithmetic_sequence_iterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

private:
    T current_;
    T step_;

public:
    constexpr arithmetic_sequence_iterator(T start, T step)
        : current_(start), step_(step) {}

    constexpr reference operator*() const { return current_; }
    constexpr pointer operator->() const { return &current_; }

    constexpr arithmetic_sequence_iterator& operator++() {
        current_ += step_;
        return *this;
    }

    constexpr arithmetic_sequence_iterator operator++(int) {
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    constexpr arithmetic_sequence_iterator& operator--() {
        current_ -= step_;
        return *this;
    }

    constexpr arithmetic_sequence_iterator operator--(int) {
        auto tmp = *this;
        --(*this);
        return tmp;
    }

    constexpr arithmetic_sequence_iterator& operator+=(difference_type n) {
        current_ += step_ * static_cast<T>(n);
        return *this;
    }

    constexpr arithmetic_sequence_iterator& operator-=(difference_type n) {
        current_ -= step_ * static_cast<T>(n);
        return *this;
    }

    constexpr arithmetic_sequence_iterator operator+(difference_type n) const {
        auto result = *this;
        result += n;
        return result;
    }

    constexpr arithmetic_sequence_iterator operator-(difference_type n) const {
        auto result = *this;
        result -= n;
        return result;
    }

    constexpr difference_type operator-(const arithmetic_sequence_iterator& other) const {
        return static_cast<difference_type>((current_ - other.current_) / step_);
    }

    constexpr T operator[](difference_type n) const {
        return current_ + step_ * static_cast<T>(n);
    }

    constexpr bool operator==(const arithmetic_sequence_iterator& other) const {
        return current_ == other.current_;
    }

    constexpr bool operator!=(const arithmetic_sequence_iterator& other) const {
        return !(*this == other);
    }

    constexpr bool operator<(const arithmetic_sequence_iterator& other) const {
        return (step_ > T{}) ? (current_ < other.current_) : (current_ > other.current_);
    }

    constexpr bool operator<=(const arithmetic_sequence_iterator& other) const {
        return !(other < *this);
    }

    constexpr bool operator>(const arithmetic_sequence_iterator& other) const {
        return other < *this;
    }

    constexpr bool operator>=(const arithmetic_sequence_iterator& other) const {
        return !(*this < other);
    }
};

// Range factory
template<xieite::is_arith T>
class arithmetic_sequence {
    T start_;
    T step_;
    std::size_t count_;

public:
    constexpr arithmetic_sequence(T start, T step, std::size_t count)
        : start_(start), step_(step), count_(count) {}

    constexpr auto begin() const {
        return arithmetic_sequence_iterator<T>(start_, step_);
    }

    constexpr auto end() const {
        return arithmetic_sequence_iterator<T>(start_ + step_ * static_cast<T>(count_), step_);
    }

    constexpr std::size_t size() const { return count_; }
};

// Factory function
template<xieite::is_arith T>
constexpr auto make_arithmetic_sequence(T start, T step, std::size_t count) {
    return arithmetic_sequence<T>(start, step, count);
}
```

## Functional Programming Integration

### XIEITE with STL Functional

Combining XIEITE utilities with functional programming patterns:

```cpp
#include <xieite/trait/is_arith.hpp>
#include <xieite/fn/curry.hpp>
#include <xieite/pp/arrow.hpp>
#include <functional>
#include <ranges>

namespace xieite_functional {

    // Compose XIEITE operations with STL algorithms
    template<xieite::is_arith T>
    auto create_arithmetic_pipeline() {
        return [](auto&& range) {
            return range
                | std::views::filter([](T x) { return x != T{}; })  // Remove zeros
                | std::views::transform([](T x) { return xieite::abs(x); })  // Absolute values
                | std::views::take(100);  // Limit to first 100 elements
        };
    }

    // Curried functions with XIEITE utilities
    template<xieite::is_arith T>
    auto curried_safe_divide = xieite::curry([](T a, T b) -> std::optional<T> {
        if (b == T{}) return std::nullopt;
        return a / b;
    });

    // Function composition with error handling
    template<typename F, typename G>
    auto compose_with_optional(F&& f, G&& g) {
        return [f = std::forward<F>(f), g = std::forward<G>(g)](auto&& arg) {
            auto result1 = g(std::forward<decltype(arg)>(arg));
            if (!result1) return result1;
            return f(*result1);
        };
    }

    // Monadic operations
    template<typename T>
    class maybe {
        std::optional<T> value_;

    public:
        constexpr maybe() = default;
        constexpr maybe(T value) : value_(std::move(value)) {}
        constexpr maybe(std::nullopt_t) : value_(std::nullopt) {}

        constexpr bool has_value() const noexcept { return value_.has_value(); }
        constexpr const T& value() const { return value_.value(); }

        template<typename F>
        constexpr auto and_then(F&& func) const {
            using result_type = std::invoke_result_t<F, T>;
            if constexpr (std::is_same_v<result_type, void>) {
                if (has_value()) {
                    func(value());
                }
                return maybe<void>{};
            } else {
                if (has_value()) {
                    return maybe<typename result_type::value_type>{func(value())};
                } else {
                    return maybe<typename result_type::value_type>{};
                }
            }
        }

        template<typename F>
        constexpr auto transform(F&& func) const {
            using result_type = std::invoke_result_t<F, T>;
            if (has_value()) {
                return maybe<result_type>{func(value())};
            } else {
                return maybe<result_type>{};
            }
        }

        constexpr T value_or(const T& default_value) const {
            return has_value() ? value() : default_value;
        }
    };

} // namespace xieite_functional
```

## I/O Stream Integration

### Enhanced Stream Operations

Integrating XIEITE with STL streams:

```cpp
#include <xieite/trait/is_arith.hpp>
#include <xieite/math/abs.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>

namespace xieite_io {

    // Safe input operations
    template<xieite::is_arith T>
    class safe_input {
        std::istream& stream_;

    public:
        explicit safe_input(std::istream& stream) : stream_(stream) {}

        std::optional<T> read() {
            T value;
            if (stream_ >> value) {
                // Additional validation for arithmetic types
                if constexpr (std::is_floating_point_v<T>) {
                    if (std::isnan(value) || std::isinf(value)) {
                        return std::nullopt;
                    }
                }
                return value;
            }
            return std::nullopt;
        }

        std::vector<T> read_all() {
            std::vector<T> result;
            T value;
            while (stream_ >> value) {
                if constexpr (std::is_floating_point_v<T>) {
                    if (std::isnan(value) || std::isinf(value)) {
                        continue; // Skip invalid values
                    }
                }
                result.push_back(value);
            }
            return result;
        }
    };

    // Enhanced output formatting
    template<xieite::is_arith T>
    class formatted_output {
        std::ostream& stream_;
        int precision_;
        int width_;

    public:
        explicit formatted_output(std::ostream& stream, int precision = 6, int width = 0)
            : stream_(stream), precision_(precision), width_(width) {}

        formatted_output& write(const T& value) {
            auto saved_precision = stream_.precision();
            auto saved_width = stream_.width();
            auto saved_flags = stream_.flags();

            auto guard = xieite::scope_guard([&] {
                stream_.precision(saved_precision);
                stream_.width(saved_width);
                stream_.flags(saved_flags);
            });

            if constexpr (std::is_floating_point_v<T>) {
                stream_ << std::fixed << std::setprecision(precision_);
            }

            if (width_ > 0) {
                stream_ << std::setw(width_);
            }

            stream_ << value;
            return *this;
        }

        formatted_output& write_scientific(const T& value) requires std::is_floating_point_v<T> {
            auto saved_precision = stream_.precision();
            auto saved_flags = stream_.flags();

            auto guard = xieite::scope_guard([&] {
                stream_.precision(saved_precision);
                stream_.flags(saved_flags);
            });

            stream_ << std::scientific << std::setprecision(precision_) << value;
            return *this;
        }

        template<std::ranges::range Range>
        formatted_output& write_range(const Range& range, const std::string& separator = " ") {
            bool first = true;
            for (const auto& elem : range) {
                if (!first) {
                    stream_ << separator;
                }
                write(elem);
                first = false;
            }
            return *this;
        }
    };

    // Stream manipulators for XIEITE types
    template<xieite::is_arith T>
    struct absolute_manip {
        const T& value;
        explicit absolute_manip(const T& v) : value(v) {}
    };

    template<xieite::is_arith T>
    auto absolute(const T& value) {
        return absolute_manip<T>{value};
    }

    template<xieite::is_arith T>
    std::ostream& operator<<(std::ostream& os, const absolute_manip<T>& manip) {
        return os << xieite::abs(manip.value);
    }

} // namespace xieite_io
```

## Memory Management Integration

### Smart Pointers with XIEITE

Enhanced smart pointer usage:

```cpp
#include <xieite/trait/is_arith.hpp>
#include <xieite/fn/scope_guard.hpp>
#include <memory>

namespace xieite_memory {

    // Factory functions with XIEITE safety
    template<typename T, typename... Args>
    auto make_unique_safe(Args&&... args) -> std::unique_ptr<T> {
        try {
            return std::make_unique<T>(std::forward<Args>(args)...);
        } catch (...) {
            // Log error or perform cleanup if needed
            throw;
        }
    }

    template<typename T, typename... Args>
    auto make_shared_safe(Args&&... args) -> std::shared_ptr<T> {
        try {
            return std::make_shared<T>(std::forward<Args>(args)...);
        } catch (...) {
            // Log error or perform cleanup if needed
            throw;
        }
    }

    // RAII wrapper for C-style resources
    template<typename T, auto Deleter>
    class unique_resource {
        T resource_;
        bool owns_;

    public:
        explicit unique_resource(T resource) : resource_(resource), owns_(true) {}

        ~unique_resource() {
            if (owns_ && resource_) {
                Deleter(resource_);
            }
        }

        // Non-copyable
        unique_resource(const unique_resource&) = delete;
        unique_resource& operator=(const unique_resource&) = delete;

        // Movable
        unique_resource(unique_resource&& other) noexcept
            : resource_(other.resource_), owns_(other.owns_) {
            other.owns_ = false;
        }

        unique_resource& operator=(unique_resource&& other) noexcept {
            if (this != &other) {
                if (owns_ && resource_) {
                    Deleter(resource_);
                }
                resource_ = other.resource_;
                owns_ = other.owns_;
                other.owns_ = false;
            }
            return *this;
        }

        T get() const noexcept { return resource_; }
        T release() noexcept {
            owns_ = false;
            return resource_;
        }

        void reset(T new_resource = T{}) {
            if (owns_ && resource_) {
                Deleter(resource_);
            }
            resource_ = new_resource;
            owns_ = (new_resource != T{});
        }

        explicit operator bool() const noexcept {
            return resource_ != T{};
        }
    };

    // Convenience aliases
    using unique_file = unique_resource<FILE*, [](FILE* f) { if (f) fclose(f); }>;
    using unique_malloc = unique_resource<void*, [](void* p) { if (p) free(p); }>;

} // namespace xieite_memory
```

## Exception Safety with STL

### Strong Exception Safety Patterns

Ensuring exception safety in STL integration:

```cpp
#include <xieite/fn/scope_guard.hpp>
#include <vector>
#include <stdexcept>

template<typename T>
class exception_safe_container {
    std::vector<T> data_;

public:
    void transactional_operation(std::function<void(std::vector<T>&)> operation) {
        // Create a copy for rollback
        auto backup = data_;
        auto rollback_guard = xieite::scope_guard([&] {
            data_ = std::move(backup);
        });

        try {
            operation(data_);
            // Success - commit changes
            rollback_guard.dismiss();
        } catch (...) {
            // Exception thrown - rollback_guard will restore state
            throw;
        }
    }

    void safe_resize(std::size_t new_size, const T& value = T{}) {
        transactional_operation([new_size, &value](std::vector<T>& vec) {
            vec.resize(new_size, value);
        });
    }

    void safe_insert(std::size_t index, const T& value) {
        if (index > data_.size()) {
            throw std::out_of_range("Index out of bounds");
        }

        transactional_operation([index, &value](std::vector<T>& vec) {
            vec.insert(vec.begin() + index, value);
        });
    }
};
```

## Best Practices for STL Integration

### Guidelines

1. **Leverage Concepts**: Use XIEITE concepts to constrain STL template parameters
2. **Exception Safety**: Combine XIEITE scope guards with STL operations
3. **Performance**: Use XIEITE's compile-time features to optimize STL usage
4. **Type Safety**: Apply XIEITE type traits for safer STL operations
5. **Interoperability**: Design XIEITE extensions to work seamlessly with STL algorithms

### Common Integration Patterns

1. **Enhanced Containers**: Wrap STL containers with XIEITE-powered safety features
2. **Safe Algorithms**: Create XIEITE-aware versions of STL algorithms
3. **Custom Allocators**: Use XIEITE utilities in custom allocator implementations
4. **Stream Integration**: Enhance STL streams with XIEITE formatting and safety
5. **Iterator Design**: Create XIEITE-compatible iterators for specialized ranges

This comprehensive integration approach maximizes the synergy between XIEITE and the STL, creating robust and efficient C++ applications.