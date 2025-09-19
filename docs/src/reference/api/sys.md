# System API Reference

## Overview

The sys category contains 20 header files providing system-level utilities, including memory management, process execution, threading utilities, and system information queries.

## Organization

The sys headers are organized into functional groups:
- **Memory Management** (5+ headers): Aligned memory operations
- **Process Management** (5+ headers): Process execution and monitoring
- **Threading Utilities** (7+ headers): Thread management and synchronization
- **System Information** (3+ headers): System metrics and detection

## Memory Management

### `aligned_memcpy`
- **Header**: `sys/aligned_memcpy.hpp`
- **Synopsis**: `void* aligned_memcpy(void* dest, const void* src, std::size_t n)`
- **Purpose**: Memory copy with alignment optimization
- **Example**:
    ```cpp
    alignas(32) char dest[256];
    alignas(32) char src[256];
    xieite::aligned_memcpy(dest, src, 256);
    ```

### `aligned_memmove`
- **Header**: `sys/aligned_memmove.hpp`
- **Synopsis**: `void* aligned_memmove(void* dest, const void* src, std::size_t n)`
- **Purpose**: Memory move with alignment optimization
- **Example**:
    ```cpp
    alignas(16) char buffer[512];
    xieite::aligned_memmove(buffer + 128, buffer, 128);
    ```

### `aligned_memset`
- **Header**: `sys/aligned_memset.hpp`
- **Synopsis**: `void* aligned_memset(void* ptr, int value, std::size_t n)`
- **Purpose**: Memory set with alignment optimization
- **Example**:
    ```cpp
    alignas(32) char buffer[1024];
    xieite::aligned_memset(buffer, 0, 1024);
    ```

### `aligned_bzero`
- **Header**: `sys/aligned_bzero.hpp`
- **Synopsis**: `void aligned_bzero(void* ptr, std::size_t n)`
- **Purpose**: Zero memory with alignment optimization
- **Example**:
    ```cpp
    alignas(64) char buffer[2048];
    xieite::aligned_bzero(buffer, 2048);
    ```

## Process Management

### `exec`
- **Header**: `sys/exec.hpp`
- **Synopsis**: Process execution utilities
- **Purpose**: Execute external processes
- **Example**:
    ```cpp
    auto result = xieite::exec("ls -la");
    if (result.success()) {
        std::cout << result.output();
    }
    ```

### `exit`
- **Header**: `sys/exit.hpp`
- **Synopsis**: `[[noreturn]] void exit(int code)`
- **Purpose**: Exit process with code
- **Example**:
    ```cpp
    if (fatal_error) {
        xieite::exit(1);
    }
    ```

### `process_result`
- **Header**: `sys/process_result.hpp`
- **Synopsis**: `class process_result`
- **Purpose**: Result of process execution
- **Example**:
    ```cpp
    auto result = execute_process("command");
    if (result.success()) {
        auto output = result.stdout_output();
        auto code = result.exit_code();
    }
    ```

### `process_status`
- **Header**: `sys/process_status.hpp`
- **Synopsis**: Process status tracking
- **Purpose**: Monitor process execution status

### `shredder`
- **Header**: `sys/shredder.hpp`
- **Synopsis**: Secure data destruction
- **Purpose**: Securely overwrite sensitive data
- **Example**:
```cpp
char sensitive_data[256];
// ... use data ...
xieite::shredder::destroy(sensitive_data, sizeof(sensitive_data));
```

## Threading Utilities

### `thread_pool`
- **Header**: `sys/thread_pool.hpp`
- **Synopsis**: `class thread_pool`
- **Purpose**: Thread pool for concurrent execution
- **Example**:
    ```cpp
    xieite::thread_pool pool(4);  // 4 worker threads
    auto future = pool.submit([]() { return expensive_computation(); });
    auto result = future.get();
    ```

### `thread_id`
- **Header**: `sys/thread_id.hpp`
- **Synopsis**: Thread identification utilities
- **Purpose**: Get and manage thread IDs
- **Example**:
    ```cpp
    auto tid = xieite::thread_id::current();
    std::cout << "Thread ID: " << tid << '\n';
    ```

### `thread_loop`
- **Header**: `sys/thread_loop.hpp`
- **Synopsis**: Thread-based loop utilities
- **Purpose**: Run loops in separate threads
- **Example**:
    ```cpp
    xieite::thread_loop loop([]{
        // Background work
        process_queue();
    });
    loop.start();
    // ... later ...
    loop.stop();
    ```

### `thread_interval`
- **Header**: `sys/thread_interval.hpp`
- **Synopsis**: Interval-based threading
- **Purpose**: Execute functions at regular intervals
- **Example**:
```cpp
using namespace std::chrono_literals;
xieite::thread_interval timer(1s, []{
    std::cout << "Heartbeat\n";
});
timer.start();
```

### `thread_timeout`
- **Header**: `sys/thread_timeout.hpp`
- **Synopsis**: Thread timeout utilities
- **Purpose**: Execute functions with timeouts
- **Example**:
    ```cpp
    using namespace std::chrono_literals;
    auto result = xieite::thread_timeout::execute(5s, [](){
        return long_running_computation();
    });
    if (result.has_value()) {
        // Completed within timeout
    }
    ```

## System Information

### `total_mem`
- **Header**: `sys/total_mem.hpp`
- **Synopsis**: `std::size_t total_mem()`
- **Purpose**: Get total system memory
- **Example**:
    ```cpp
    auto total = xieite::total_mem();
    std::cout << "Total RAM: " << total / (1024*1024*1024) << " GB\n";
    ```

### `available_mem`
- **Header**: `sys/available_mem.hpp`
- **Synopsis**: `std::size_t available_mem()`
- **Purpose**: Get available system memory
- **Example**:
    ```cpp
    auto available = xieite::available_mem();
    std::cout << "Available RAM: " << available / (1024*1024) << " MB\n";
    ```

### `page_mem`
- **Header**: `sys/page_mem.hpp`
- **Synopsis**: `std::size_t page_mem()`
- **Purpose**: Get system memory page size
- **Example**:
    ```cpp
    auto page_size = xieite::page_mem();  // Typically 4096
    ```

### `nproc`
- **Header**: `sys/nproc.hpp`
- **Synopsis**: `std::size_t nproc()`
- **Purpose**: Get number of processor cores
- **Example**:
    ```cpp
    auto cores = xieite::nproc();
    std::cout << "CPU cores: " << cores << '\n';
    ```

## Utilities

### `stopwatch`
- **Header**: `sys/stopwatch.hpp`
- **Synopsis**: `class stopwatch`
- **Purpose**: High-resolution timing
- **Example**:
    ```cpp
    xieite::stopwatch timer;
    timer.start();
    // ... operation ...
    timer.stop();
    auto elapsed = timer.elapsed_ms();
    ```

### `segfault`
- **Header**: `sys/segfault.hpp`
- **Synopsis**: Segmentation fault utilities
- **Purpose**: Handle and debug segmentation faults
- **Example**:
    ```cpp
    xieite::segfault::install_handler([](int sig) {
        std::cerr << "Segmentation fault detected\n";
        std::abort();
    });
    ```

### `detect_cosmic_ray`
- **Header**: `sys/detect_cosmic_ray.hpp`
- **Synopsis**: Cosmic ray detection utilities
- **Purpose**: Detect potential cosmic ray induced bit flips
- **Example**:
    ```cpp
    if (xieite::detect_cosmic_ray::check_memory_integrity()) {
        // Memory appears intact
    } else {
        // Potential bit flip detected
        std::cerr << "Memory corruption detected!\n";
    }
    ```

## Usage Examples

### `Memory Operations`
```cpp
#include <xieite/sys/aligned_memcpy.hpp>
#include <xieite/sys/aligned_memset.hpp>

// Efficient aligned memory operations
alignas(32) char buffer1[1024];
alignas(32) char buffer2[1024];

xieite::aligned_memset(buffer1, 0xFF, 1024);
xieite::aligned_memcpy(buffer2, buffer1, 1024);
```

### `Process Execution`
```cpp
#include <xieite/sys/exec.hpp>
#include <xieite/sys/process_result.hpp>

auto result = xieite::exec("git status --porcelain");
if (result.success()) {
    if (result.output().empty()) {
        std::cout << "Working directory is clean\n";
    } else {
        std::cout << "Uncommitted changes:\n" << result.output();
    }
}
```

### `Threading`
```cpp
#include <xieite/sys/thread_pool.hpp>
#include <xieite/sys/thread_interval.hpp>

// Thread pool for parallel work
xieite::thread_pool pool(std::thread::hardware_concurrency());

std::vector<std::future<int>> futures;
for (int i = 0; i < 10; ++i) {
    futures.push_back(pool.submit([i]() {
        return expensive_computation(i);
    }));
}

for (auto& future : futures) {
    auto result = future.get();
    process_result(result);
}
```

### `System Monitoring`
```cpp
#include <xieite/sys/total_mem.hpp>
#include <xieite/sys/available_mem.hpp>
#include <xieite/sys/nproc.hpp>

void print_system_stats() {
    auto total = xieite::total_mem();
    auto available = xieite::available_mem();
    auto cores = xieite::nproc();

    std::cout << "Cores: " << cores << '\n';
    std::cout << "Memory: " << available / (1024*1024)
              << " / " << total / (1024*1024) << " MB\n";
    std::cout << "Usage: " << (100.0 * (total - available) / total)
              << "%\n";
}
```

## Performance Notes

- Aligned memory operations provide significant performance benefits on modern CPUs
- Thread pools reduce thread creation overhead
- Memory queries may have OS call overhead
- Stopwatch provides high-resolution timing with minimal overhead
- Process execution utilities handle cross-platform differences

## See Also

- [System Utilities Overview](../../categories/sys/README.md)
- [Platform Detection](../pp/platform.md) - Located in `pp/` category
- [Architecture Detection](../pp/arch.md) - Located in `pp/` category
- [Meta Programming API](./meta.md)
