# XIEITE System Module

## Overview

The XIEITE system module provides comprehensive system-level utilities for C++20 and beyond. With 21 headers, it offers process management, memory operations, threading utilities, timing, and platform-specific functionality with consistent cross-platform interfaces.

## Module Organization

### System and Process Utilities (11 headers)
- **[System Utilities](system_utilities.md)** - Process and memory management
- Process execution: `exec`, `exit`, `segfault`
- Memory operations: `aligned_memcpy`, `aligned_memset`, `shredder`
- System info: `nproc`, `total_mem`, `available_mem`, `page_mem`
- Timing: `stopwatch`
- Special: `detect_cosmic_ray`

### Threading and Concurrency (10 headers)
- **[Threading Utilities](threading_utilities.md)** - Advanced concurrent programming
- Thread pool: `thread_pool` with dynamic scaling
- Timed execution: `thread_timeout`, `thread_interval`, `thread_loop`
- Thread management: `thread_id`

## Key Features

### Process Management
Execute and control system processes:
```cpp
// Execute command and capture output
auto result = xieite::exec("ls -la");
if (result.status.success()) {
    std::cout << result.output;
}

// Controlled exit
if (critical_error) {
    xieite::exit(1);
}

// Test crash handlers
if (test_mode) {
    xieite::segfault();  // Intentional crash
}
```

### High-Performance Memory
Aligned operations for optimal performance:
```cpp
// Aligned memory operations
alignof(64) float src[1024];
alignof(64) float dst[1024];

xieite::aligned_memcpy<64>(dst, src, sizeof(src));
xieite::aligned_bzero<32>(buffer, size);

// Secure erasure
{
    xieite::shredder<std::string> password;
    password.value = get_password();
    authenticate(password.value);
}  // Automatically shredded
```

### Advanced Threading
Scalable thread pool with work queue:
```cpp
// Create thread pool
xieite::thread_pool pool;

// Parallel processing
std::vector<std::future<void>> futures;
for (auto& item : items) {
    futures.push_back(
        pool.enqueue([&item] { process(item); })
    );
}

// Wait for completion
for (auto& f : futures) {
    f.wait();
}

// Dynamic scaling
pool.set_threads(heavy_load ? xieite::nproc() * 2 : 2);
```

### Precision Timing
High-resolution time measurement:
```cpp
xieite::stopwatch<> timer;

timer.start();
for (int i = 0; i < iterations; ++i) {
    process_batch(i);
    auto lap = timer.lap<std::chrono::microseconds>();
    log_timing(i, lap.count());
}

auto total = timer.total<std::chrono::milliseconds>();
std::cout << "Total: " << total.count() << " ms\n";
```

## System Information

### Hardware Queries
```cpp
// CPU information
auto cpu_count = xieite::nproc();
std::cout << "CPUs: " << cpu_count << '\n';

// Memory information
auto total = xieite::total_mem();
auto available = xieite::available_mem();
auto page_size = xieite::page_mem();

std::cout << "Memory:\n"
          << "  Total: " << (total / (1024*1024)) << " MB\n"
          << "  Available: " << (available / (1024*1024)) << " MB\n"
          << "  Page size: " << page_size << " bytes\n";
```

### Adaptive Resource Management
```cpp
// Adjust buffer based on available memory
std::size_t buffer_size = std::min(
    xieite::available_mem() / 4,  // Use 25% max
    1024 * 1024 * 1024  // Cap at 1GB
);

// Align to page boundaries
buffer_size = (buffer_size / xieite::page_mem()) * xieite::page_mem();

// Configure thread pool based on CPU count
thread_pool workers(xieite::nproc());
```

## Threading Patterns

### Timed Execution
```cpp
// Execute with timeout
xieite::thread_timeout task(
    [] { long_operation(); },
    std::chrono::seconds(30)
);

if (!task.completed()) {
    std::cerr << "Operation timed out\n";
    task.cancel();
}

// Periodic execution
xieite::thread_interval monitor(
    [] { check_system_health(); },
    std::chrono::seconds(5)
);
monitor.start();

// Continuous processing
xieite::thread_loop processor(
    [] {
        if (auto task = get_next_task()) {
            process(*task);
        }
    }
);
processor.start();
```

### Parallel Algorithms
```cpp
template<typename Container, typename Fn>
void parallel_transform(Container& data, Fn transformer) {
    xieite::thread_pool pool;
    std::vector<std::future<void>> futures;
    
    for (auto& item : data) {
        futures.push_back(
            pool.enqueue([&item, transformer] {
                item = transformer(item);
            })
        );
    }
    
    for (auto& f : futures) {
        f.wait();
    }
}
```

## Special Features

### Cosmic Ray Detection
Detect memory bit flips:
```cpp
// Monitor for bit flips in separate thread
std::thread monitor([] {
    xieite::detect_cosmic_ray(1024 * 1024);  // 1MB
    // If returns, bit flip detected
    log_critical("Memory corruption detected!");
    xieite::exit(99);
});
monitor.detach();
```

### Secure Memory Handling
```cpp
template<typename T>
class SecureContainer {
    xieite::shredder<std::vector<T>> data;
    
public:
    void store(const T& value) {
        data.value.push_back(value);
    }
    
    // Automatically shredded on destruction
};
```

## Performance Characteristics

### Memory Operations
- Aligned operations: Up to 4x faster on aligned boundaries
- Shredder: Multiple overwrites for security
- Page-aligned allocation: Optimal OS interaction

### Threading
- Thread pool: Avoids creation/destruction overhead
- Work stealing: Automatic load balancing
- Lock-free queues: Minimal contention

### System Calls
- Process execution: Platform-optimized (fork/exec vs CreateProcess)
- Memory queries: Usually cached by OS
- Hardware info: One-time cost, cached results

## Cross-Platform Support

### Platform Detection
```cpp
// Automatic platform adaptation
auto result = xieite::exec(command);  // Works on all platforms

// Platform-specific optimization
#ifdef _WIN32
    // Windows-specific path
#else
    // Unix-specific path
#endif
```

### Consistent Interfaces
All utilities provide the same interface regardless of platform:
- Memory operations work identically
- Thread utilities abstract platform differences
- System queries return consistent types

## Module Statistics

- **Total Headers**: 21
- **Process Management**: 3 utilities
- **Memory Operations**: 5 functions
- **Threading**: 5 classes
- **System Info**: 4 queries
- **Timing**: 1 stopwatch class
- **Special**: 3 unique utilities

## Best Practices

1. **Check process results**:
   ```cpp
   auto result = xieite::exec(cmd);
   if (!result.status.success()) {
       handle_error(result.status.code);
   }
   ```

2. **Use aligned operations**:
   ```cpp
   alignof(64) char buffer[4096];
   xieite::aligned_memset<64>(buffer, 0, sizeof(buffer));
   ```

3. **Size thread pools appropriately**:
   ```cpp
   // CPU-bound: match core count
   xieite::thread_pool cpu_pool(xieite::nproc());
   
   // I/O-bound: oversubscribe
   xieite::thread_pool io_pool(xieite::nproc() * 2);
   ```

4. **Secure sensitive data**:
   ```cpp
   {
       xieite::shredder<PrivateKey> key;
       // Use key.value
   }  // Automatically erased
   ```

## Integration Examples

### System Monitor
```cpp
class SystemMonitor {
    xieite::thread_interval checker;
    xieite::stopwatch uptime;
    
public:
    SystemMonitor() : checker(
        [this] { check(); },
        std::chrono::seconds(10)
    ) {
        uptime.start();
        checker.start();
    }
    
    void check() {
        auto mem = xieite::available_mem();
        if (mem < threshold) {
            alert("Low memory: " + std::to_string(mem));
        }
        
        auto elapsed = uptime.total<std::chrono::hours>();
        log_uptime(elapsed.count());
    }
};
```

### Parallel Pipeline
```cpp
template<typename T>
class Pipeline {
    xieite::thread_pool pool;
    
public:
    void process(std::vector<T>& data) {
        // Stage 1: Parallel preprocessing
        parallel_transform(data, preprocess);
        
        // Stage 2: Parallel main processing
        parallel_transform(data, main_process);
        
        // Stage 3: Parallel postprocessing
        parallel_transform(data, postprocess);
    }
};
```

## Future Enhancements

Potential additions to the sys module:
- Process spawning and IPC
- Memory-mapped files
- Signal handling utilities
- Hardware topology detection
- Power management interfaces

---

*Return to [XIEITE Documentation Home](../../index.md)*