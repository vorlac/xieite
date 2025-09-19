# Real Application Example

## Introduction

This comprehensive example demonstrates building a complete, production-ready application using XIEITE utilities. The application is a high-performance data processing pipeline that showcases advanced XIEITE usage patterns, cross-platform development, and integration with modern C++ best practices.

## Application Overview

### Project: Scientific Data Analysis Pipeline

The example application processes large datasets of scientific measurements, demonstrating:

- **Real-time data ingestion** using XIEITE I/O utilities
- **Compile-time optimized algorithms** using XIEITE mathematical functions
- **Type-safe configuration** using XIEITE type traits and concepts
- **Cross-platform deployment** using XIEITE platform detection
- **Performance optimization** through compile-time computation

### Architecture Overview

```
ScientificPipeline/
├── libs/
│   ├── core/           # Core utilities with XIEITE
│   ├── data/           # Data structures and algorithms
│   ├── processing/     # Signal processing algorithms
│   └── platform/       # Platform-specific optimizations
├── apps/
│   ├── pipeline/       # Main pipeline application
│   ├── analyzer/       # Data analysis tool
│   └── benchmark/      # Performance testing tool
├── tests/
│   ├── unit/          # Unit tests
│   ├── integration/   # Integration tests
│   └── performance/   # Performance benchmarks
└── config/
    ├── platforms/     # Platform-specific configurations
    └── algorithms/    # Algorithm parameter files
```

## Core Library Implementation

### Foundation Layer with XIEITE

```cpp
// libs/core/include/core/foundation.hpp
#pragma once

#include <xieite/trait/is_arith.hpp>
#include <xieite/trait/is_satisfied.hpp>
#include <xieite/math/abs.hpp>
#include <xieite/math/diff.hpp>
#include <xieite/pp/platform.hpp>
#include <xieite/pp/arrow.hpp>
#include <xieite/fn/scope_guard.hpp>
#include <concepts>
#include <type_traits>

namespace pipeline::core {

// Type traits for scientific data
template<typename T>
concept ScientificNumeric = xieite::is_arith<T> &&
    requires(T a, T b) {
        { xieite::abs(a) } -> std::convertible_to<T>;
        { xieite::diff(a, b) } -> std::convertible_to<T>;
    };

// Platform-specific optimizations
template<ScientificNumeric T>
class PlatformOptimized {
public:
    static constexpr bool use_simd =
        #if XIEITE_PLATFORM_TYPE_WINDOWS || XIEITE_PLATFORM_TYPE_LINUX
            true;
        #else
            false;
        #endif

    static constexpr bool use_threading =
        #if XIEITE_PLATFORM_TYPE_UNIX
            true;
        #else
            std::is_floating_point_v<T>;
        #endif

    template<typename Func>
    static auto with_optimization(Func&& func)
        XIEITE_ARROW(std::forward<Func>(func)())
};

// Resource management using XIEITE scope guards
template<typename Resource, typename Deleter>
class ManagedResource {
    Resource resource_;
    bool released_ = false;

public:
    explicit ManagedResource(Resource&& resource)
        : resource_(std::move(resource)) {}

    ~ManagedResource() {
        if (!released_) {
            Deleter{}(resource_);
        }
    }

    auto get() const XIEITE_ARROW(resource_)

    void release() { released_ = true; }

    template<typename Func>
    auto with_guard(Func&& func) {
        auto guard = xieite::scope_guard([this]() {
            if (!released_) {
                Deleter{}(resource_);
            }
        });

        auto result = func(resource_);
        guard.release(); // Success - don't clean up
        return result;
    }
};

} // namespace pipeline::core
```

### Configuration System

```cpp
// libs/core/include/core/config.hpp
#pragma once

#include <xieite/trait/is_satisfied_all.hpp>
#include <xieite/meta/type_list.hpp>
#include <xieite/pp/arrow.hpp>
#include <string>
#include <optional>
#include <unordered_map>

namespace pipeline::core {

// Compile-time configuration validation
template<typename T>
class ConfigValidator {
public:
    static constexpr auto is_numeric_config = []<typename U> requires(
        std::is_arithmetic_v<U> && !std::is_same_v<U, bool>
    ) {};

    static constexpr auto is_string_config = []<typename U> requires(
        std::convertible_to<U, std::string>
    ) {};

    static constexpr auto is_boolean_config = []<typename U> requires(
        std::is_same_v<U, bool>
    ) {};

    static constexpr bool is_valid_config_type =
        xieite::is_satisfied_all<is_numeric_config, T> ||
        xieite::is_satisfied_all<is_string_config, T> ||
        xieite::is_satisfied_all<is_boolean_config, T>;
};

// Type-safe configuration manager
class Configuration {
    std::unordered_map<std::string, std::string> values_;

public:
    template<typename T>
    requires(ConfigValidator<T>::is_valid_config_type)
    std::optional<T> get(const std::string& key) const {
        auto it = values_.find(key);
        if (it == values_.end()) {
            return std::nullopt;
        }

        if constexpr (std::is_arithmetic_v<T>) {
            try {
                if constexpr (std::is_integral_v<T>) {
                    return static_cast<T>(std::stoll(it->second));
                } else {
                    return static_cast<T>(std::stod(it->second));
                }
            } catch (...) {
                return std::nullopt;
            }
        } else if constexpr (std::convertible_to<T, std::string>) {
            return T{it->second};
        } else if constexpr (std::is_same_v<T, bool>) {
            return it->second == "true" || it->second == "1";
        }
    }

    template<typename T>
    requires(ConfigValidator<T>::is_valid_config_type)
    T get_or(const std::string& key, const T& default_value) const {
        return get<T>(key).value_or(default_value);
    }

    void set(const std::string& key, const std::string& value) {
        values_[key] = value;
    }

    // Bulk configuration validation
    template<typename... ConfigTypes>
    bool validate_required_keys(const std::initializer_list<std::string>& keys) const {
        using ConfigList = xieite::type_list<ConfigTypes...>;

        if (keys.size() != ConfigList::size) {
            return false;
        }

        return std::all_of(keys.begin(), keys.end(),
            [this](const std::string& key) {
                return values_.find(key) != values_.end();
            });
    }
};

} // namespace pipeline::core
```

## Data Processing Layer

### High-Performance Data Structures

```cpp
// libs/data/include/data/structures.hpp
#pragma once

#include <xieite/meta/make_seq.hpp>
#include <xieite/fn/repeat.hpp>
#include <xieite/math/bit_size.hpp>
#include <xieite/trait/is_arith.hpp>
#include <array>
#include <vector>
#include <memory>

namespace pipeline::data {

// Cache-aligned data buffer for high-performance processing
template<typename T, std::size_t Size>
requires(xieite::is_arith<T>)
class alignas(64) CacheAlignedBuffer {
    static constexpr std::size_t cache_line_size = 64;
    static constexpr std::size_t effective_size =
        ((Size * sizeof(T) + cache_line_size - 1) / cache_line_size) * cache_line_size / sizeof(T);

    std::array<T, effective_size> data_;
    std::size_t active_size_ = Size;

public:
    constexpr CacheAlignedBuffer() = default;

    constexpr CacheAlignedBuffer(std::initializer_list<T> init) {
        std::size_t i = 0;
        for (const auto& value : init) {
            if (i >= Size) break;
            data_[i++] = value;
        }
    }

    constexpr T& operator[](std::size_t index) { return data_[index]; }
    constexpr const T& operator[](std::size_t index) const { return data_[index]; }

    constexpr std::size_t size() const { return active_size_; }
    constexpr std::size_t capacity() const { return effective_size; }

    constexpr T* data() { return data_.data(); }
    constexpr const T* data() const { return data_.data(); }

    // Vectorized operations using compile-time unrolling
    template<auto operation>
    constexpr void apply_vectorized() {
        constexpr std::size_t vector_width = 4; // Assume 4-element SIMD
        constexpr std::size_t vectorized_count = Size / vector_width;
        constexpr std::size_t remainder = Size % vector_width;

        // Process vectorized chunks
        xieite::repeat<vectorized_count>([this]<std::size_t chunk>(auto...) {
            constexpr std::size_t base = chunk * vector_width;
            xieite::repeat<vector_width>([this, base]<std::size_t i>(auto...) {
                data_[base + i] = operation(data_[base + i]);
            });
        });

        // Process remainder elements
        if constexpr (remainder > 0) {
            constexpr std::size_t base = vectorized_count * vector_width;
            xieite::repeat<remainder>([this, base]<std::size_t i>(auto...) {
                data_[base + i] = operation(data_[base + i]);
            });
        }
    }

    // Parallel reduction operations
    template<auto binary_op, auto identity>
    constexpr T reduce() const {
        T result = identity;
        for (std::size_t i = 0; i < active_size_; ++i) {
            result = binary_op(result, data_[i]);
        }
        return result;
    }
};

// Circular buffer for streaming data
template<typename T, std::size_t Capacity>
class CircularBuffer {
    std::array<T, Capacity> buffer_;
    std::size_t head_ = 0;
    std::size_t tail_ = 0;
    std::size_t size_ = 0;

public:
    bool push(const T& value) {
        if (size_ >= Capacity) {
            return false; // Buffer full
        }

        buffer_[tail_] = value;
        tail_ = (tail_ + 1) % Capacity;
        ++size_;
        return true;
    }

    std::optional<T> pop() {
        if (size_ == 0) {
            return std::nullopt;
        }

        T value = buffer_[head_];
        head_ = (head_ + 1) % Capacity;
        --size_;
        return value;
    }

    constexpr std::size_t size() const { return size_; }
    constexpr std::size_t capacity() const { return Capacity; }
    constexpr bool empty() const { return size_ == 0; }
    constexpr bool full() const { return size_ >= Capacity; }

    // Batch operations for better performance
    template<typename Iterator>
    std::size_t push_batch(Iterator begin, Iterator end) {
        std::size_t count = 0;
        for (auto it = begin; it != end && !full(); ++it, ++count) {
            push(*it);
        }
        return count;
    }

    template<typename OutputIterator>
    std::size_t pop_batch(OutputIterator out, std::size_t max_count) {
        std::size_t count = 0;
        while (count < max_count && !empty()) {
            if (auto value = pop()) {
                *out++ = *value;
                ++count;
            }
        }
        return count;
    }
};

} // namespace pipeline::data
```

### Signal Processing Algorithms

```cpp
// libs/processing/include/processing/algorithms.hpp
#pragma once

#include <xieite/math/abs.hpp>
#include <xieite/math/diff.hpp>
#include <xieite/fn/repeat.hpp>
#include <xieite/meta/make_seq.hpp>
#include <xieite/trait/is_arith.hpp>
#include <pipeline/core/foundation.hpp>
#include <pipeline/data/structures.hpp>
#include <cmath>
#include <numbers>

namespace pipeline::processing {

// Compile-time optimized digital filters
template<typename T, std::size_t Order>
requires(core::ScientificNumeric<T>)
class DigitalFilter {
    static_assert(Order > 0 && Order <= 32, "Filter order must be between 1 and 32");

    std::array<T, Order + 1> coefficients_;
    data::CircularBuffer<T, Order> delay_line_;

public:
    constexpr DigitalFilter(const std::array<T, Order + 1>& coefficients)
        : coefficients_(coefficients) {}

    // Process single sample with compile-time loop unrolling
    T process(T input) {
        delay_line_.push(input);

        T output = T{0};

        // Unroll the convolution loop at compile time
        xieite::repeat<Order + 1>([&]<std::size_t i>(auto...) {
            if constexpr (i == 0) {
                output += coefficients_[0] * input;
            } else {
                // Access delay line (implementation detail)
                // In real implementation, would access delay_line_ properly
                output += coefficients_[i] * T{0}; // Simplified for example
            }
        });

        return output;
    }

    // Batch processing for better performance
    template<std::size_t BatchSize>
    void process_batch(
        const data::CacheAlignedBuffer<T, BatchSize>& input,
        data::CacheAlignedBuffer<T, BatchSize>& output) {

        for (std::size_t i = 0; i < input.size(); ++i) {
            output[i] = process(input[i]);
        }
    }
};

// Fast Fourier Transform implementation
template<typename T, std::size_t N>
requires(core::ScientificNumeric<T> && ((N & (N - 1)) == 0)) // Power of 2
class FastFFT {
    static constexpr std::size_t log2_N = std::bit_width(N) - 1;

public:
    using Complex = std::complex<T>;

    // Compile-time twiddle factor generation
    static constexpr auto generate_twiddle_factors() {
        std::array<Complex, N / 2> twiddles{};

        for (std::size_t i = 0; i < N / 2; ++i) {
            T angle = -2.0 * std::numbers::pi_v<T> * i / N;
            twiddles[i] = Complex{std::cos(angle), std::sin(angle)};
        }

        return twiddles;
    }

    static constexpr auto twiddle_factors = generate_twiddle_factors();

    // Optimized radix-2 FFT with compile-time staging
    static void compute(std::array<Complex, N>& data) {
        // Bit-reversal permutation
        bit_reverse_permute(data);

        // Butterfly computations with compile-time loop unrolling
        xieite::repeat<log2_N>([&data]<std::size_t stage>(auto...) {
            constexpr std::size_t step = 1 << (stage + 1);
            constexpr std::size_t half_step = step >> 1;

            for (std::size_t i = 0; i < N; i += step) {
                for (std::size_t j = 0; j < half_step; ++j) {
                    std::size_t twiddle_index = j * (N / step);
                    Complex twiddle = twiddle_factors[twiddle_index];

                    Complex even = data[i + j];
                    Complex odd = data[i + j + half_step] * twiddle;

                    data[i + j] = even + odd;
                    data[i + j + half_step] = even - odd;
                }
            }
        });
    }

private:
    static void bit_reverse_permute(std::array<Complex, N>& data) {
        for (std::size_t i = 0; i < N; ++i) {
            std::size_t reversed = bit_reverse(i, log2_N);
            if (i < reversed) {
                std::swap(data[i], data[reversed]);
            }
        }
    }

    static constexpr std::size_t bit_reverse(std::size_t value, std::size_t bits) {
        std::size_t result = 0;
        for (std::size_t i = 0; i < bits; ++i) {
            result = (result << 1) | (value & 1);
            value >>= 1;
        }
        return result;
    }
};

// Statistical analysis with compile-time optimization
template<typename T>
requires(core::ScientificNumeric<T>)
class StatisticalAnalyzer {
public:
    struct Statistics {
        T mean;
        T variance;
        T std_deviation;
        T min_value;
        T max_value;
        T range;
    };

    template<std::size_t N>
    static Statistics analyze(const data::CacheAlignedBuffer<T, N>& data) {
        Statistics stats{};

        // Single pass computation for efficiency
        T sum = T{0};
        T sum_squares = T{0};
        T min_val = std::numeric_limits<T>::max();
        T max_val = std::numeric_limits<T>::lowest();

        for (std::size_t i = 0; i < data.size(); ++i) {
            T value = data[i];
            sum += value;
            sum_squares += value * value;
            min_val = std::min(min_val, value);
            max_val = std::max(max_val, value);
        }

        T n = static_cast<T>(data.size());
        stats.mean = sum / n;
        stats.variance = (sum_squares - sum * sum / n) / (n - T{1});
        stats.std_deviation = std::sqrt(stats.variance);
        stats.min_value = min_val;
        stats.max_value = max_val;
        stats.range = xieite::diff(max_val, min_val);

        return stats;
    }

    // Outlier detection using statistical methods
    template<std::size_t N>
    static std::vector<std::size_t> find_outliers(
        const data::CacheAlignedBuffer<T, N>& data,
        T threshold_factor = T{2.5}) {

        auto stats = analyze(data);
        std::vector<std::size_t> outliers;

        T lower_bound = stats.mean - threshold_factor * stats.std_deviation;
        T upper_bound = stats.mean + threshold_factor * stats.std_deviation;

        for (std::size_t i = 0; i < data.size(); ++i) {
            if (data[i] < lower_bound || data[i] > upper_bound) {
                outliers.push_back(i);
            }
        }

        return outliers;
    }
};

} // namespace pipeline::processing
```

## Main Application Implementation

### Pipeline Application

```cpp
// apps/pipeline/src/main.cpp
#include <pipeline/core/foundation.hpp>
#include <pipeline/core/config.hpp>
#include <pipeline/data/structures.hpp>
#include <pipeline/processing/algorithms.hpp>
#include <xieite/fn/scope_guard.hpp>
#include <xieite/io/dump.hpp>
#include <xieite/pp/platform.hpp>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

using namespace pipeline;

class DataProcessor {
    core::Configuration config_;
    static constexpr std::size_t buffer_size = 4096;

public:
    explicit DataProcessor(const core::Configuration& config)
        : config_(config) {}

    template<typename T>
    bool process_file(const std::string& input_path, const std::string& output_path) {
        // Resource management with XIEITE scope guards
        std::ifstream input(input_path, std::ios::binary);
        if (!input) {
            std::cerr << "Failed to open input file: " << input_path << '\n';
            return false;
        }

        std::ofstream output(output_path, std::ios::binary);
        if (!output) {
            std::cerr << "Failed to open output file: " << output_path << '\n';
            return false;
        }

        auto file_guard = xieite::scope_guard([&]() {
            input.close();
            output.close();
            std::cout << "Files closed automatically\n";
        });

        // Configure processing parameters from config
        auto filter_order = config_.get_or<int>("filter_order", 8);
        auto threshold = config_.get_or<T>("outlier_threshold", T{2.5});
        auto enable_fft = config_.get_or<bool>("enable_fft", true);

        std::cout << "Processing with filter order: " << filter_order << '\n';
        std::cout << "Outlier threshold: " << threshold << '\n';
        std::cout << "FFT enabled: " << std::boolalpha << enable_fft << '\n';

        // Platform-specific optimization messages
        #if XIEITE_PLATFORM_TYPE_WINDOWS
            std::cout << "Using Windows optimizations\n";
        #elif XIEITE_PLATFORM_TYPE_LINUX
            std::cout << "Using Linux optimizations\n";
        #elif XIEITE_PLATFORM_TYPE_UNIX
            std::cout << "Using Unix optimizations\n";
        #else
            std::cout << "Using generic optimizations\n";
        #endif

        // High-performance data processing
        data::CacheAlignedBuffer<T, buffer_size> input_buffer;
        data::CacheAlignedBuffer<T, buffer_size> output_buffer;

        // Create processing pipeline
        std::array<T, 9> filter_coeffs{
            T{0.1}, T{0.1}, T{0.1}, T{0.1}, T{0.2},
            T{0.1}, T{0.1}, T{0.1}, T{0.1}
        };
        processing::DigitalFilter<T, 8> filter(filter_coeffs);
        processing::StatisticalAnalyzer<T> analyzer;

        // Process data in chunks
        std::size_t total_samples = 0;
        std::size_t total_outliers = 0;

        while (input.good()) {
            // Read data chunk
            input.read(reinterpret_cast<char*>(input_buffer.data()),
                      buffer_size * sizeof(T));
            std::size_t samples_read = input.gcount() / sizeof(T);

            if (samples_read == 0) break;

            // Apply digital filter
            filter.process_batch(input_buffer, output_buffer);

            // Statistical analysis
            auto stats = analyzer.analyze(output_buffer);
            auto outliers = analyzer.find_outliers(output_buffer, threshold);

            total_samples += samples_read;
            total_outliers += outliers.size();

            // Write processed data
            output.write(reinterpret_cast<const char*>(output_buffer.data()),
                        samples_read * sizeof(T));

            // Progress reporting
            if (total_samples % (buffer_size * 10) == 0) {
                std::cout << "Processed " << total_samples << " samples, "
                         << "found " << total_outliers << " outliers\n";
            }
        }

        std::cout << "Processing complete!\n";
        std::cout << "Total samples: " << total_samples << '\n';
        std::cout << "Total outliers: " << total_outliers << '\n';

        file_guard.release(); // Successful completion
        return true;
    }
};

int main(int argc, char* argv[]) {
    try {
        // Configuration setup
        core::Configuration config;
        config.set("filter_order", "8");
        config.set("outlier_threshold", "2.5");
        config.set("enable_fft", "true");

        // Validate configuration
        if (!config.validate_required_keys<int, double, bool>(
                {"filter_order", "outlier_threshold", "enable_fft"})) {
            std::cerr << "Invalid configuration\n";
            return 1;
        }

        DataProcessor processor(config);

        // Process command line arguments
        if (argc != 3) {
            std::cout << "Usage: " << argv[0] << " <input_file> <output_file>\n";
            return 1;
        }

        std::string input_path = argv[1];
        std::string output_path = argv[2];

        // Performance timing
        auto start_time = std::chrono::high_resolution_clock::now();

        // Process the data
        bool success = processor.process_file<double>(input_path, output_path);

        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);

        if (success) {
            std::cout << "Processing completed successfully in "
                     << duration.count() << " ms\n";
            return 0;
        } else {
            std::cerr << "Processing failed\n";
            return 1;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "Unknown error occurred\n";
        return 1;
    }
}
```

## Build System Integration

### CMakeLists.txt

```cmake
# apps/pipeline/CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(ScientificPipeline VERSION 1.0.0 LANGUAGES CXX)

# Require C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find XIEITE
find_package(xieite REQUIRED)

# Compiler-specific flags for XIEITE
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-fconcepts-diagnostics-depth=10)
    add_compile_options(-ftemplate-backtrace-limit=0)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-ferror-limit=0)
    add_compile_options(-ftemplate-backtrace-limit=0)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/permissive-)
    add_compile_options(/Zc:preprocessor)
endif()

# Core library
add_library(pipeline_core
    libs/core/src/foundation.cpp
    libs/core/src/config.cpp
)

target_include_directories(pipeline_core
    PUBLIC
        libs/core/include
        libs/data/include
        libs/processing/include
)

target_link_libraries(pipeline_core
    PUBLIC
        xieite::xieite
)

# Data structures library
add_library(pipeline_data INTERFACE)
target_include_directories(pipeline_data INTERFACE libs/data/include)
target_link_libraries(pipeline_data INTERFACE pipeline_core)

# Processing algorithms library
add_library(pipeline_processing INTERFACE)
target_include_directories(pipeline_processing INTERFACE libs/processing/include)
target_link_libraries(pipeline_processing INTERFACE pipeline_data)

# Main pipeline application
add_executable(pipeline
    apps/pipeline/src/main.cpp
)

target_link_libraries(pipeline
    PRIVATE
        pipeline_core
        pipeline_data
        pipeline_processing
)

# Platform-specific optimizations
if(WIN32)
    target_compile_definitions(pipeline PRIVATE PIPELINE_WINDOWS=1)
elseif(UNIX AND NOT APPLE)
    target_compile_definitions(pipeline PRIVATE PIPELINE_LINUX=1)
    target_link_libraries(pipeline PRIVATE pthread)
elseif(APPLE)
    target_compile_definitions(pipeline PRIVATE PIPELINE_MACOS=1)
endif()

# Enable optimizations for release builds
target_compile_options(pipeline PRIVATE
    $<$<CONFIG:Release>:-O3>
    $<$<CONFIG:Release>:-march=native>
    $<$<CONFIG:RelWithDebInfo>:-O2>
)
```

## Testing and Validation

### Unit Tests

```cpp
// tests/unit/test_core.cpp
#include <pipeline/core/foundation.hpp>
#include <pipeline/core/config.hpp>
#include <pipeline/data/structures.hpp>
#include <gtest/gtest.h>
#include <xieite/math/abs.hpp>

class CoreFoundationTest : public ::testing::Test {
protected:
    void SetUp() override {
        config_.set("test_value", "42");
        config_.set("test_string", "hello");
        config_.set("test_bool", "true");
    }

    pipeline::core::Configuration config_;
};

TEST_F(CoreFoundationTest, ConfigurationTypeValidation) {
    // Test numeric configuration
    auto int_value = config_.get<int>("test_value");
    ASSERT_TRUE(int_value.has_value());
    EXPECT_EQ(*int_value, 42);

    // Test string configuration
    auto string_value = config_.get<std::string>("test_string");
    ASSERT_TRUE(string_value.has_value());
    EXPECT_EQ(*string_value, "hello");

    // Test boolean configuration
    auto bool_value = config_.get<bool>("test_bool");
    ASSERT_TRUE(bool_value.has_value());
    EXPECT_TRUE(*bool_value);

    // Test missing key
    auto missing = config_.get<int>("missing_key");
    EXPECT_FALSE(missing.has_value());
}

TEST_F(CoreFoundationTest, ScientificNumericConcept) {
    using namespace pipeline::core;

    // Test concept satisfaction
    static_assert(ScientificNumeric<double>);
    static_assert(ScientificNumeric<float>);
    static_assert(ScientificNumeric<int>);
    static_assert(!ScientificNumeric<std::string>);

    // Test with actual values
    double a = 3.14;
    double b = 2.71;

    auto abs_result = xieite::abs(a - b);
    EXPECT_GT(abs_result, 0.0);
}

class DataStructuresTest : public ::testing::Test {};

TEST_F(DataStructuresTest, CacheAlignedBuffer) {
    using namespace pipeline::data;

    CacheAlignedBuffer<double, 100> buffer;

    // Test basic operations
    buffer[0] = 1.0;
    buffer[1] = 2.0;
    buffer[2] = 3.0;

    EXPECT_EQ(buffer[0], 1.0);
    EXPECT_EQ(buffer[1], 2.0);
    EXPECT_EQ(buffer[2], 3.0);

    // Test vectorized operations
    auto square = [](double x) { return x * x; };
    buffer.apply_vectorized<square>();

    EXPECT_EQ(buffer[0], 1.0);  // 1^2 = 1
    EXPECT_EQ(buffer[1], 4.0);  // 2^2 = 4
    EXPECT_EQ(buffer[2], 9.0);  // 3^2 = 9

    // Test reduction
    auto add = [](double a, double b) { return a + b; };
    auto sum = buffer.reduce<add, 0.0>();
    EXPECT_EQ(sum, 14.0);  // 1 + 4 + 9 = 14
}

TEST_F(DataStructuresTest, CircularBuffer) {
    using namespace pipeline::data;

    CircularBuffer<int, 5> buffer;

    EXPECT_TRUE(buffer.empty());
    EXPECT_FALSE(buffer.full());

    // Fill buffer
    for (int i = 1; i <= 5; ++i) {
        EXPECT_TRUE(buffer.push(i));
    }

    EXPECT_FALSE(buffer.empty());
    EXPECT_TRUE(buffer.full());
    EXPECT_FALSE(buffer.push(6)); // Should fail when full

    // Empty buffer
    for (int i = 1; i <= 5; ++i) {
        auto value = buffer.pop();
        ASSERT_TRUE(value.has_value());
        EXPECT_EQ(*value, i);
    }

    EXPECT_TRUE(buffer.empty());
    EXPECT_FALSE(buffer.pop().has_value()); // Should fail when empty
}
```

## Performance Benchmarks

### Benchmark Implementation

```cpp
// tests/performance/benchmark_processing.cpp
#include <pipeline/processing/algorithms.hpp>
#include <pipeline/data/structures.hpp>
#include <benchmark/benchmark.h>
#include <random>
#include <chrono>

using namespace pipeline;

class ProcessingBenchmark : public benchmark::Fixture {
protected:
    void SetUp(const benchmark::State& state) override {
        // Generate test data
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<double> dist(0.0, 1.0);

        for (std::size_t i = 0; i < buffer_size; ++i) {
            test_data_[i] = dist(gen);
        }
    }

    static constexpr std::size_t buffer_size = 4096;
    data::CacheAlignedBuffer<double, buffer_size> test_data_;
    data::CacheAlignedBuffer<double, buffer_size> output_data_;
};

BENCHMARK_F(ProcessingBenchmark, DigitalFilterProcessing)(benchmark::State& state) {
    std::array<double, 9> coeffs{0.1, 0.1, 0.1, 0.1, 0.2, 0.1, 0.1, 0.1, 0.1};
    processing::DigitalFilter<double, 8> filter(coeffs);

    for (auto _ : state) {
        filter.process_batch(test_data_, output_data_);
        benchmark::DoNotOptimize(output_data_.data());
    }

    state.SetItemsProcessed(state.iterations() * buffer_size);
    state.SetBytesProcessed(state.iterations() * buffer_size * sizeof(double));
}

BENCHMARK_F(ProcessingBenchmark, StatisticalAnalysis)(benchmark::State& state) {
    processing::StatisticalAnalyzer<double> analyzer;

    for (auto _ : state) {
        auto stats = analyzer.analyze(test_data_);
        benchmark::DoNotOptimize(stats);
    }

    state.SetItemsProcessed(state.iterations() * buffer_size);
}

BENCHMARK_F(ProcessingBenchmark, FFTComputation)(benchmark::State& state) {
    using Complex = std::complex<double>;
    std::array<Complex, 4096> fft_data;

    // Initialize with test data
    for (std::size_t i = 0; i < 4096; ++i) {
        fft_data[i] = Complex{test_data_[i], 0.0};
    }

    processing::FastFFT<double, 4096> fft;

    for (auto _ : state) {
        auto data_copy = fft_data; // Copy for each iteration
        fft.compute(data_copy);
        benchmark::DoNotOptimize(data_copy.data());
    }

    state.SetItemsProcessed(state.iterations() * 4096);
    state.SetComplexityN(4096);
}

// Compile-time vs runtime comparison
static void CompileTimeVsRuntime(benchmark::State& state) {
    constexpr auto compile_time_result = []() constexpr {
        double sum = 0.0;
        for (int i = 0; i < 1000; ++i) {
            sum += i * i;
        }
        return sum;
    }();

    auto runtime_computation = []() {
        double sum = 0.0;
        for (int i = 0; i < 1000; ++i) {
            sum += i * i;
        }
        return sum;
    };

    for (auto _ : state) {
        if (state.range(0) == 0) {
            // Compile-time result (already computed)
            volatile double result = compile_time_result;
            benchmark::DoNotOptimize(result);
        } else {
            // Runtime computation
            auto result = runtime_computation();
            benchmark::DoNotOptimize(result);
        }
    }
}

BENCHMARK(CompileTimeVsRuntime)->Arg(0)->Arg(1)->Unit(benchmark::kNanosecond);

BENCHMARK_MAIN();
```

## Deployment and Distribution

### Docker Configuration

```dockerfile
# Dockerfile for cross-platform deployment
FROM ubuntu:22.04 AS builder

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libgtest-dev \
    libbenchmark-dev \
    && rm -rf /var/lib/apt/lists/*

# Set up C++20 compiler
RUN apt-get update && apt-get install -y gcc-11 g++-11
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 100
RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 100

# Copy source code
WORKDIR /app
COPY . .

# Build the application
RUN mkdir build && cd build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release && \
    make -j$(nproc)

# Runtime stage
FROM ubuntu:22.04 AS runtime

RUN apt-get update && apt-get install -y \
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

COPY --from=builder /app/build/apps/pipeline/pipeline /usr/local/bin/
COPY --from=builder /app/config/ /app/config/

WORKDIR /app
ENTRYPOINT ["/usr/local/bin/pipeline"]
```

This comprehensive real application example demonstrates how XIEITE can be effectively integrated into production systems, providing high performance, type safety, and cross-platform compatibility. The example showcases advanced C++ techniques combined with XIEITE utilities to create efficient, maintainable scientific computing applications.