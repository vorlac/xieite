# OS-Specific Features

## Overview

The OS-specific features category provides platform-dependent utilities and system resource access functions. These utilities leverage platform-specific APIs to provide information about system capabilities, hardware resources, and specialized functionality not available through standard library interfaces.

## System Resource Queries

### Processor Information

#### Number of Processors

```cpp
#include <xieite/sys/nproc.hpp>

std::size_t get_cpu_count() {
    return xieite::nproc();
}

void system_info_example() {
    auto cpu_count = xieite::nproc();
    std::cout << "Available processors: " << cpu_count << '\n';

    // Use for thread pool sizing
    auto thread_count = std::max(1UL, cpu_count - 1);
    std::cout << "Recommended thread count: " << thread_count << '\n';
}
```

**Source Reference**: `include/xieite/sys/nproc.hpp:16-26`

The function uses platform-specific APIs:
- **Unix/Linux**: `sysconf(_SC_NPROCESSORS_ONLN)` for online processors
- **Windows**: `GetSystemInfo()` to query `dwNumberOfProcessors`
- **Fallback**: Returns 0 for unsupported platforms

### Memory Information

#### Total System Memory

```cpp
#include <xieite/sys/total_mem.hpp>

void memory_analysis() {
    auto total = xieite::total_mem();

    std::cout << "Total system memory: "
              << (total / (1024 * 1024)) << " MB\n";

    // Calculate memory thresholds
    auto high_water = total * 0.8;  // 80% threshold
    auto low_water = total * 0.6;   // 60% threshold

    std::cout << "High water mark: " << (high_water / (1024 * 1024)) << " MB\n";
    std::cout << "Low water mark: " << (low_water / (1024 * 1024)) << " MB\n";
}
```

**Source Reference**: `include/xieite/sys/total_mem.hpp:17-28`

Platform implementations:
- **Unix/Linux**: `sysconf(_SC_PHYS_PAGES) * page_size`
- **Windows**: `GlobalMemoryStatusEx()` returning `ullTotalPhys`

#### Available Memory

```cpp
#include <xieite/sys/available_mem.hpp>
#include <xieite/sys/total_mem.hpp>

class MemoryMonitor {
    std::size_t total_memory;

public:
    MemoryMonitor() : total_memory(xieite::total_mem()) {}

    double memory_usage_percent() const {
        auto available = xieite::available_mem();
        auto used = total_memory - available;
        return (static_cast<double>(used) / total_memory) * 100.0;
    }

    bool is_memory_pressure() const {
        return memory_usage_percent() > 85.0;
    }

    std::size_t available_bytes() const {
        return xieite::available_mem();
    }
};

void memory_monitoring_example() {
    MemoryMonitor monitor;

    std::cout << "Memory usage: " << monitor.memory_usage_percent() << "%\n";
    std::cout << "Available memory: "
              << (monitor.available_bytes() / (1024 * 1024)) << " MB\n";

    if (monitor.is_memory_pressure()) {
        std::cout << "Warning: High memory usage detected!\n";
    }
}
```

**Source Reference**: `include/xieite/sys/available_mem.hpp:17-28`

#### Memory Page Size

```cpp
#include <xieite/sys/page_mem.hpp>

void page_aligned_allocation() {
    auto page_size = xieite::page_mem();

    std::cout << "System page size: " << page_size << " bytes\n";

    // Align allocation to page boundaries
    std::size_t buffer_size = 1024 * 1024;  // 1 MB
    std::size_t aligned_size = ((buffer_size + page_size - 1) / page_size) * page_size;

    std::cout << "Requested: " << buffer_size << " bytes\n";
    std::cout << "Page-aligned: " << aligned_size << " bytes\n";

    // Allocate page-aligned memory (platform-specific)
    // Implementation would use posix_memalign() or VirtualAlloc()
}
```

**Source Reference**: `include/xieite/sys/page_mem.hpp:16-26`

## Specialized System Features

### Cosmic Ray Detection

A unique utility for detecting potential cosmic ray-induced bit flips in memory:

```cpp
#include <xieite/sys/detect_cosmic_ray.hpp>

void cosmic_ray_detection_example() {
    std::size_t detection_buffer_size = 1024 * 1024;  // 1 MB

    std::cout << "Starting cosmic ray detection...\n";
    std::cout << "Buffer size: " << detection_buffer_size << " bytes\n";

    // This function will run indefinitely until a bit flip is detected
    // or the program is terminated
    xieite::detect_cosmic_ray(detection_buffer_size);

    // This line will only execute if a cosmic ray is detected
    std::cout << "Cosmic ray detected! Memory corruption found.\n";
}

// More practical usage for testing/debugging
void cosmic_ray_test_framework() {
    // Use in a separate thread for background monitoring
    std::thread detector([]{
        xieite::detect_cosmic_ray(512 * 1024);  // 512 KB buffer
    });

    // Detach thread to run in background
    detector.detach();

    // Continue with main application logic
    std::cout << "Cosmic ray detection running in background...\n";
}
```

**Source Reference**: `include/xieite/sys/detect_cosmic_ray.hpp:9-13`

The implementation creates a buffer of volatile memory and continuously checks for unexpected bit flips that could indicate cosmic ray interference.

## Platform-Specific Integration

### Cross-Platform Resource Management

```cpp
#include <xieite/sys/nproc.hpp>
#include <xieite/sys/total_mem.hpp>
#include <xieite/sys/available_mem.hpp>
#include <xieite/pp/platform.hpp>

class SystemResourceManager {
public:
    struct SystemInfo {
        std::size_t processor_count;
        std::size_t total_memory;
        std::size_t available_memory;
        std::size_t page_size;
        std::string platform_name;
    };

    static SystemInfo gather_system_info() {
        SystemInfo info;

        info.processor_count = xieite::nproc();
        info.total_memory = xieite::total_mem();
        info.available_memory = xieite::available_mem();
        info.page_size = xieite::page_mem();

        // Platform identification
        #if XIEITE_PLATFORM_TYPE_WINDOWS
            info.platform_name = "Windows";
        #elif XIEITE_PLATFORM_TYPE_LINUX
            info.platform_name = "Linux";
        #elif XIEITE_PLATFORM_TYPE_UNIX
            info.platform_name = "Unix";
        #elif XIEITE_PLATFORM_TYPE_MACOS
            info.platform_name = "macOS";
        #else
            info.platform_name = "Unknown";
        #endif

        return info;
    }

    static void print_system_summary(const SystemInfo& info) {
        std::cout << "=== System Information ===\n";
        std::cout << "Platform: " << info.platform_name << '\n';
        std::cout << "Processors: " << info.processor_count << '\n';
        std::cout << "Total Memory: " << (info.total_memory / (1024 * 1024)) << " MB\n";
        std::cout << "Available Memory: " << (info.available_memory / (1024 * 1024)) << " MB\n";
        std::cout << "Page Size: " << info.page_size << " bytes\n";

        double memory_usage = ((double)(info.total_memory - info.available_memory) / info.total_memory) * 100.0;
        std::cout << "Memory Usage: " << std::fixed << std::setprecision(1) << memory_usage << "%\n";
    }
};
```

### Adaptive Application Configuration

```cpp
#include <xieite/sys/nproc.hpp>
#include <xieite/sys/available_mem.hpp>

class AdaptiveConfiguration {
public:
    static auto configure_for_system() {
        struct Config {
            std::size_t thread_pool_size;
            std::size_t cache_size_mb;
            std::size_t buffer_size_kb;
            bool enable_parallel_processing;
        } config;

        auto cpu_count = xieite::nproc();
        auto available_memory = xieite::available_mem();
        auto memory_mb = available_memory / (1024 * 1024);

        // Adaptive thread pool sizing
        if (cpu_count <= 2) {
            config.thread_pool_size = 1;
            config.enable_parallel_processing = false;
        } else {
            config.thread_pool_size = std::min(cpu_count - 1, 8UL);
            config.enable_parallel_processing = true;
        }

        // Memory-based cache configuration
        if (memory_mb < 512) {
            config.cache_size_mb = 32;
            config.buffer_size_kb = 64;
        } else if (memory_mb < 2048) {
            config.cache_size_mb = 128;
            config.buffer_size_kb = 256;
        } else {
            config.cache_size_mb = 512;
            config.buffer_size_kb = 1024;
        }

        return config;
    }
};
```

## Memory Management Patterns

### Page-Aligned Operations

```cpp
#include <xieite/sys/page_mem.hpp>

class PageAlignedBuffer {
    void* buffer = nullptr;
    std::size_t size = 0;
    std::size_t aligned_size = 0;

public:
    explicit PageAlignedBuffer(std::size_t requested_size) {
        auto page_size = xieite::page_mem();

        // Round up to next page boundary
        aligned_size = ((requested_size + page_size - 1) / page_size) * page_size;

        #if XIEITE_PLATFORM_TYPE_WINDOWS
            buffer = VirtualAlloc(nullptr, aligned_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        #elif XIEITE_PLATFORM_TYPE_UNIX
            if (posix_memalign(&buffer, page_size, aligned_size) != 0) {
                buffer = nullptr;
            }
        #else
            buffer = std::aligned_alloc(page_size, aligned_size);
        #endif

        size = buffer ? aligned_size : 0;
    }

    ~PageAlignedBuffer() {
        if (buffer) {
            #if XIEITE_PLATFORM_TYPE_WINDOWS
                VirtualFree(buffer, 0, MEM_RELEASE);
            #else
                std::free(buffer);
            #endif
        }
    }

    void* data() const { return buffer; }
    std::size_t capacity() const { return size; }
    bool valid() const { return buffer != nullptr; }
};
```

## Performance Monitoring

### System Resource Tracking

```cpp
#include <xieite/sys/available_mem.hpp>
#include <xieite/sys/nproc.hpp>
#include <chrono>
#include <vector>

class ResourceTracker {
    struct Measurement {
        std::chrono::steady_clock::time_point timestamp;
        std::size_t available_memory;
        double cpu_load_estimate;
    };

    std::vector<Measurement> measurements;
    std::chrono::steady_clock::time_point start_time;

public:
    ResourceTracker() : start_time(std::chrono::steady_clock::now()) {}

    void record_measurement() {
        Measurement m;
        m.timestamp = std::chrono::steady_clock::now();
        m.available_memory = xieite::available_mem();
        m.cpu_load_estimate = estimate_cpu_load();

        measurements.push_back(m);

        // Keep only last 100 measurements
        if (measurements.size() > 100) {
            measurements.erase(measurements.begin());
        }
    }

    double average_memory_usage() const {
        if (measurements.empty()) return 0.0;

        std::size_t total = 0;
        for (const auto& m : measurements) {
            total += m.available_memory;
        }

        return static_cast<double>(total) / measurements.size();
    }

private:
    double estimate_cpu_load() {
        // Simple CPU load estimation based on timing
        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - start_time);

        // This is a simplified estimation - real implementation would
        // use platform-specific CPU usage APIs
        return std::min(100.0, duration.count() / 10000.0);
    }
};
```

## Best Practices

### Error Handling for System Queries

```cpp
#include <xieite/sys/nproc.hpp>
#include <xieite/sys/total_mem.hpp>

class SafeSystemQuery {
public:
    static std::optional<std::size_t> safe_nproc() {
        auto result = xieite::nproc();
        return (result > 0) ? std::make_optional(result) : std::nullopt;
    }

    static std::optional<std::size_t> safe_total_mem() {
        auto result = xieite::total_mem();
        return (result > 0) ? std::make_optional(result) : std::nullopt;
    }

    static bool validate_system_resources() {
        auto cpu_count = safe_nproc();
        auto total_memory = safe_total_mem();

        if (!cpu_count || !total_memory) {
            std::cerr << "Failed to query system resources\n";
            return false;
        }

        if (*cpu_count == 0 || *total_memory < 1024 * 1024) {  // Less than 1MB
            std::cerr << "System resources appear invalid\n";
            return false;
        }

        return true;
    }
};
```

### Resource-Aware Application Design

```cpp
#include <xieite/sys/available_mem.hpp>
#include <xieite/sys/nproc.hpp>

template<typename T>
class AdaptiveContainer {
    std::vector<T> data;
    std::size_t max_capacity;

public:
    AdaptiveContainer() {
        // Calculate capacity based on available memory
        auto available = xieite::available_mem();
        auto safe_usage = available / 4;  // Use at most 25% of available memory

        max_capacity = safe_usage / sizeof(T);

        // Reserve initial capacity
        auto initial_capacity = std::min(max_capacity / 10, 1000UL);
        data.reserve(initial_capacity);
    }

    bool can_add_elements(std::size_t count = 1) const {
        return (data.size() + count) <= max_capacity;
    }

    bool add_element(const T& element) {
        if (!can_add_elements()) {
            return false;  // Would exceed memory limits
        }

        data.push_back(element);
        return true;
    }

    std::size_t capacity_remaining() const {
        return max_capacity - data.size();
    }
};
```

## Related System Utilities

These OS-specific features complement other system utilities:

- **[Platform Detection](../pp/platform.md)** - Compile-time platform identification
- **[Architecture Detection](./architecture.md)** - CPU architecture information
- **[Endianness Handling](./endianness.md)** - Byte order detection and conversion
- **[System Queries](./queries.md)** - Additional system information functions

## Platform Support Matrix

| Feature | Windows | Linux | Unix | macOS | Notes |
|---------|---------|-------|------|-------|-------|
| `nproc()` | ✅ | ✅ | ✅ | ✅ | Returns 0 on unsupported platforms |
| `total_mem()` | ✅ | ✅ | ✅ | ✅ | Uses platform-specific memory APIs |
| `available_mem()` | ✅ | ✅ | ✅ | ✅ | Real-time available memory |
| `page_mem()` | ✅ | ✅ | ✅ | ✅ | System memory page size |
| `detect_cosmic_ray()` | ✅ | ✅ | ✅ | ✅ | Platform-independent implementation |

All functions gracefully handle unsupported platforms by returning appropriate default values and issuing compiler warnings where applicable.