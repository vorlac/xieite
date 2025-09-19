# System Queries

## Overview

XIEITE provides cross-platform system query utilities for retrieving system information such as memory statistics, processor count, and other hardware characteristics. These utilities abstract platform differences and provide a unified interface for system resource queries.

## Memory Information

### Available Physical Memory
Implementation: `include/xieite/sys/available_mem.hpp` (lines 17-28)

```cpp
[[nodiscard]] inline std::size_t available_mem() noexcept {
#if XIEITE_PLATFORM_TYPE_UNIX
    return static_cast<std::size_t>(::sysconf(_SC_AVPHYS_PAGES)) * xieite::page_mem();
#elif XIEITE_PLATFORM_TYPE_WINDOWS
    ::MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    ::GlobalMemoryStatusEx(&status);
    return static_cast<std::size_t>(status.ullAvailPhys);
#else
    return 0;
#endif
}
```

Returns the amount of available physical memory in bytes.

### Total Physical Memory
Implementation: `include/xieite/sys/total_mem.hpp` (lines 17-28)

```cpp
[[nodiscard]] inline std::size_t total_mem() noexcept {
#if XIEITE_PLATFORM_TYPE_UNIX
    return static_cast<std::size_t>(::sysconf(_SC_PHYS_PAGES)) * xieite::page_mem();
#elif XIEITE_PLATFORM_TYPE_WINDOWS
    ::MEMORYSTATUSEX status;
    status.dwLength = sizeof(status);
    ::GlobalMemoryStatusEx(&status);
    return static_cast<std::size_t>(status.ullTotalPhys);
#else
    return 0;
#endif
}
```

Returns the total amount of physical memory in bytes.

## Processor Information

### Processor Count
Implementation: `include/xieite/sys/nproc.hpp` (lines 16-26)

```cpp
inline std::size_t nproc() noexcept {
#if XIEITE_PLATFORM_TYPE_UNIX
    return static_cast<std::size_t>(::sysconf(_SC_NPROCESSORS_ONLN));
#elif XIEITE_PLATFORM_TYPE_WINDOWS
    ::SYSTEM_INFO info;
    ::GetSystemInfo(&info);
    return static_cast<std::size_t>(info.dwNumberOfProcessors);
#else
    return 0;
#endif
}
```

Returns the number of logical processors (cores) available to the system.

## Usage Examples

### Basic System Information
```cpp
#include <xieite/sys/available_mem.hpp>
#include <xieite/sys/total_mem.hpp>
#include <xieite/sys/nproc.hpp>
#include <iostream>
#include <iomanip>

void print_system_info() {
    const auto total = xieite::total_mem();
    const auto available = xieite::available_mem();
    const auto used = total - available;
    const auto processors = xieite::nproc();

    std::cout << "System Information:\n";
    std::cout << "  Processors: " << processors << "\n";
    std::cout << "  Total Memory: " << std::fixed << std::setprecision(2)
              << static_cast<double>(total) / (1024 * 1024 * 1024) << " GB\n";
    std::cout << "  Available Memory: " << std::fixed << std::setprecision(2)
              << static_cast<double>(available) / (1024 * 1024 * 1024) << " GB\n";
    std::cout << "  Used Memory: " << std::fixed << std::setprecision(2)
              << static_cast<double>(used) / (1024 * 1024 * 1024) << " GB\n";
    std::cout << "  Memory Usage: " << std::fixed << std::setprecision(1)
              << (static_cast<double>(used) / total) * 100 << "%\n";
}
```

### Memory Monitoring
```cpp
#include <xieite/sys/available_mem.hpp>
#include <xieite/sys/total_mem.hpp>
#include <chrono>
#include <thread>

class MemoryMonitor {
private:
    std::size_t total_memory_;
    double high_usage_threshold_;
    double low_memory_threshold_;

public:
    MemoryMonitor(double high_threshold = 0.8, double low_threshold = 0.1)
        : total_memory_(xieite::total_mem())
        , high_usage_threshold_(high_threshold)
        , low_memory_threshold_(low_threshold) {}

    enum class MemoryStatus {
        Normal,
        HighUsage,
        LowMemory,
        Critical
    };

    MemoryStatus check_status() const {
        const auto available = xieite::available_mem();
        const double usage_ratio = 1.0 - (static_cast<double>(available) / total_memory_);
        const double available_ratio = static_cast<double>(available) / total_memory_;

        if (available_ratio < 0.05) {  // Less than 5% available
            return MemoryStatus::Critical;
        } else if (available_ratio < low_memory_threshold_) {
            return MemoryStatus::LowMemory;
        } else if (usage_ratio > high_usage_threshold_) {
            return MemoryStatus::HighUsage;
        } else {
            return MemoryStatus::Normal;
        }
    }

    void continuous_monitor(std::chrono::milliseconds interval) {
        while (true) {
            auto status = check_status();
            auto available = xieite::available_mem();
            auto usage_percent = (1.0 - static_cast<double>(available) / total_memory_) * 100;

            switch (status) {
                case MemoryStatus::Critical:
                    std::cout << "[CRITICAL] Memory usage: " << std::fixed << std::setprecision(1)
                              << usage_percent << "% - System may become unstable\n";
                    break;
                case MemoryStatus::LowMemory:
                    std::cout << "[WARNING] Low memory: " << std::fixed << std::setprecision(1)
                              << usage_percent << "% - Consider freeing resources\n";
                    break;
                case MemoryStatus::HighUsage:
                    std::cout << "[INFO] High memory usage: " << std::fixed << std::setprecision(1)
                              << usage_percent << "%\n";
                    break;
                case MemoryStatus::Normal:
                    // Only log periodically for normal status
                    break;
            }

            std::this_thread::sleep_for(interval);
        }
    }
};

// Usage
MemoryMonitor monitor(0.75, 0.2);  // Alert at 75% usage, warn at 20% available
auto status = monitor.check_status();
```

### Load-Balanced Processing
```cpp
#include <xieite/sys/nproc.hpp>
#include <vector>
#include <thread>
#include <future>
#include <algorithm>

template<typename Iterator, typename Function>
void parallel_for_each(Iterator first, Iterator last, Function func) {
    const auto processor_count = xieite::nproc();
    const auto element_count = std::distance(first, last);

    if (element_count == 0 || processor_count == 0) {
        return;
    }

    // Determine optimal number of threads
    const auto thread_count = std::min(
        static_cast<std::size_t>(element_count),
        processor_count
    );

    // Calculate work per thread
    const auto work_per_thread = element_count / thread_count;
    const auto remainder = element_count % thread_count;

    std::vector<std::future<void>> futures;
    futures.reserve(thread_count);

    auto current = first;
    for (std::size_t i = 0; i < thread_count; ++i) {
        // Calculate range for this thread
        auto chunk_size = work_per_thread + (i < remainder ? 1 : 0);
        auto chunk_end = std::next(current, chunk_size);

        // Launch thread for this chunk
        futures.emplace_back(std::async(std::launch::async, [current, chunk_end, func]() {
            std::for_each(current, chunk_end, func);
        }));

        current = chunk_end;
    }

    // Wait for all threads to complete
    for (auto& future : futures) {
        future.wait();
    }
}

// Usage
std::vector<int> data(1000000);
std::iota(data.begin(), data.end(), 1);

parallel_for_each(data.begin(), data.end(), [](int& value) {
    value = value * value;  // Square each element
});
```

## Advanced Patterns

### Resource-Aware Allocation
```cpp
#include <xieite/sys/available_mem.hpp>
#include <xieite/sys/total_mem.hpp>
#include <memory>
#include <stdexcept>

template<typename T>
class MemoryAwareAllocator {
private:
    static constexpr double max_allocation_ratio = 0.5;  // Use max 50% of available memory

public:
    using value_type = T;

    template<typename U>
    constexpr MemoryAwareAllocator(const MemoryAwareAllocator<U>&) noexcept {}
    constexpr MemoryAwareAllocator() = default;

    [[nodiscard]] T* allocate(std::size_t n) {
        const auto requested_bytes = n * sizeof(T);
        const auto available = xieite::available_mem();
        const auto max_allowed = static_cast<std::size_t>(available * max_allocation_ratio);

        if (requested_bytes > max_allowed) {
            throw std::bad_alloc();
        }

        return std::allocator<T>{}.allocate(n);
    }

    void deallocate(T* p, std::size_t n) noexcept {
        std::allocator<T>{}.deallocate(p, n);
    }

    template<typename U>
    bool operator==(const MemoryAwareAllocator<U>&) const noexcept {
        return true;
    }
};

// Usage
using SafeVector = std::vector<int, MemoryAwareAllocator<int>>;

try {
    SafeVector large_vector(1000000000);  // May throw if insufficient memory
} catch (const std::bad_alloc&) {
    std::cout << "Insufficient memory for allocation\n";
}
```

### Dynamic Thread Pool Sizing
```cpp
#include <xieite/sys/nproc.hpp>
#include <xieite/sys/available_mem.hpp>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

class AdaptiveThreadPool {
private:
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;
    std::mutex queue_mutex_;
    std::condition_variable condition_;
    bool stop_;

    std::size_t calculate_optimal_threads() const {
        const auto hardware_threads = xieite::nproc();
        const auto available_mem = xieite::available_mem();
        const auto total_mem = xieite::total_mem();

        // Reduce thread count if memory is low
        const double memory_ratio = static_cast<double>(available_mem) / total_mem;

        if (memory_ratio < 0.1) {
            // Very low memory: use minimal threads
            return std::max(1uz, hardware_threads / 4);
        } else if (memory_ratio < 0.3) {
            // Low memory: use half threads
            return std::max(1uz, hardware_threads / 2);
        } else {
            // Normal memory: use all available threads
            return hardware_threads;
        }
    }

public:
    AdaptiveThreadPool() : stop_(false) {
        const auto thread_count = calculate_optimal_threads();

        std::cout << "Starting thread pool with " << thread_count
                  << " threads (hardware: " << xieite::nproc() << ")\n";

        workers_.reserve(thread_count);
        for (std::size_t i = 0; i < thread_count; ++i) {
            workers_.emplace_back([this] {
                while (true) {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(queue_mutex_);
                        condition_.wait(lock, [this] { return stop_ || !tasks_.empty(); });

                        if (stop_ && tasks_.empty()) {
                            return;
                        }

                        task = std::move(tasks_.front());
                        tasks_.pop();
                    }

                    task();
                }
            });
        }
    }

    template<typename F>
    void enqueue(F&& f) {
        {
            std::lock_guard<std::mutex> lock(queue_mutex_);
            if (stop_) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }
            tasks_.emplace(std::forward<F>(f));
        }
        condition_.notify_one();
    }

    ~AdaptiveThreadPool() {
        {
            std::lock_guard<std::mutex> lock(queue_mutex_);
            stop_ = true;
        }

        condition_.notify_all();

        for (std::thread& worker : workers_) {
            worker.join();
        }
    }
};
```

## Implementation Details

### Platform-Specific APIs
The system query utilities use different APIs based on platform:

**Unix/Linux (available_mem.hpp:18-19, total_mem.hpp:18-19, nproc.hpp:17-18):**
- `sysconf(_SC_AVPHYS_PAGES)` - Available physical pages
- `sysconf(_SC_PHYS_PAGES)` - Total physical pages
- `sysconf(_SC_NPROCESSORS_ONLN)` - Online processors
- Requires multiplication by page size for memory queries

**Windows (available_mem.hpp:20-24, total_mem.hpp:20-24, nproc.hpp:19-22):**
- `GlobalMemoryStatusEx()` - Memory status information
- `GetSystemInfo()` - System information including processor count
- Direct byte values from memory status structure

### Error Handling Strategy
The utilities employ defensive programming:
- Return 0 for unsupported platforms (lines 26 in each file)
- `noexcept` specifications ensure exception safety
- Platform detection prevents compilation on unsupported systems

### Memory Calculation Details
Memory values are computed as:
- **Unix**: `pages * page_size` using `xieite::page_mem()`
- **Windows**: Direct byte values from `MEMORYSTATUSEX`
- Values represent physical RAM, not virtual memory

## Performance Characteristics

- **System calls**: Each query involves one system call
- **Caching considerations**: Values may change rapidly, especially available memory
- **Thread safety**: Functions are thread-safe but values are snapshots
- **Overhead**: Minimal - direct system API calls with no additional processing

## Best Practices

1. **Cache processor count** - Number of processors rarely changes during execution
2. **Poll memory periodically** - Available memory changes frequently
3. **Handle zero returns** - Always check for unsupported platform returns
4. **Consider virtual vs physical memory** - These utilities report physical memory only

## Common Use Cases

### Memory Pool Sizing
```cpp
#include <xieite/sys/available_mem.hpp>

class MemoryPool {
private:
    static constexpr double pool_ratio = 0.25;  // Use 25% of available memory

public:
    static std::size_t calculate_pool_size() {
        return static_cast<std::size_t>(xieite::available_mem() * pool_ratio);
    }
};
```

### Parallel Algorithm Configuration
```cpp
#include <xieite/sys/nproc.hpp>
#include <algorithm>
#include <execution>

template<typename Iterator, typename Function>
void adaptive_transform(Iterator first, Iterator last, Function func) {
    const auto size = std::distance(first, last);
    const auto cores = xieite::nproc();

    if (size > cores * 1000) {
        // Large dataset: use parallel execution
        std::transform(std::execution::par_unseq, first, last, first, func);
    } else {
        // Small dataset: use sequential execution
        std::transform(std::execution::seq, first, last, first, func);
    }
}
```

### System Resource Monitoring
```cpp
#include <xieite/sys/available_mem.hpp>
#include <xieite/sys/total_mem.hpp>
#include <xieite/sys/nproc.hpp>

struct SystemSnapshot {
    std::size_t total_memory;
    std::size_t available_memory;
    std::size_t processor_count;
    std::chrono::steady_clock::time_point timestamp;

    static SystemSnapshot capture() {
        return {
            xieite::total_mem(),
            xieite::available_mem(),
            xieite::nproc(),
            std::chrono::steady_clock::now()
        };
    }

    double memory_usage_percent() const {
        return (1.0 - static_cast<double>(available_memory) / total_memory) * 100.0;
    }
};
```

## See Also

- [Platform Detection](./platform.md) - Operating system detection utilities
- [Architecture Detection](./architecture.md) - Processor architecture detection
- [Environment Variables](./environment.md) - Environment variable access
- [System API Reference](../../reference/api/sys.md)