# System API Reference

## Overview

The sys category contains 40+ header files providing system-level utilities, including platform detection, architecture identification, environment queries, endianness handling, and OS-specific feature detection.

## Organization

The sys headers are organized into functional groups:

- **Platform Detection** (10+ headers): OS and platform identification
- **Architecture Detection** (8+ headers): CPU architecture identification
- **Compiler Detection** (8+ headers): Compiler and version detection
- **Environment** (5+ headers): Environment variables and system queries
- **Endianness** (3+ headers): Byte order detection and conversion
- **Feature Detection** (6+ headers): OS and hardware feature detection

## Platform Detection

### os
**Header**: `sys/os.hpp`
**Synopsis**: Platform detection macros
**Purpose**: Identify operating system at compile time
**Macros**:
```cpp
// OS Type Detection
XIEITE_OS_TYPE_WINDOWS   // Windows family
XIEITE_OS_TYPE_LINUX     // Linux
XIEITE_OS_TYPE_MACOS     // macOS
XIEITE_OS_TYPE_ANDROID   // Android
XIEITE_OS_TYPE_IOS       // iOS
XIEITE_OS_TYPE_BSD       // BSD variants
XIEITE_OS_TYPE_UNIX      // Unix-like systems

// OS Family Detection
XIEITE_OS_FAMILY_WINDOWS
XIEITE_OS_FAMILY_POSIX
XIEITE_OS_FAMILY_UNIX
```

**Example**:
```cpp
#if XIEITE_OS_TYPE_WINDOWS
    // Windows-specific code
#elif XIEITE_OS_TYPE_LINUX
    // Linux-specific code
#elif XIEITE_OS_TYPE_MACOS
    // macOS-specific code
#endif
```

### arch
**Header**: `sys/arch.hpp`
**Synopsis**: Architecture detection macros
**Purpose**: Identify CPU architecture
**Macros**:
```cpp
// Architecture Detection
XIEITE_ARCH_TYPE_X86      // 32-bit x86
XIEITE_ARCH_TYPE_X86_64   // 64-bit x86
XIEITE_ARCH_TYPE_ARM      // 32-bit ARM
XIEITE_ARCH_TYPE_AARCH64  // 64-bit ARM
XIEITE_ARCH_TYPE_MIPS     // MIPS
XIEITE_ARCH_TYPE_PPC      // PowerPC
XIEITE_ARCH_TYPE_RISCV    // RISC-V
XIEITE_ARCH_TYPE_WASM     // WebAssembly

// Architecture Properties
XIEITE_ARCH_BITS          // 32 or 64
XIEITE_ARCH_LITTLE_ENDIAN
XIEITE_ARCH_BIG_ENDIAN
```

### compiler
**Header**: `sys/compiler.hpp`
**Synopsis**: Compiler detection and version
**Purpose**: Identify compiler and version
**Macros**:
```cpp
// Compiler Detection
XIEITE_COMPILER_TYPE_GCC
XIEITE_COMPILER_TYPE_CLANG
XIEITE_COMPILER_TYPE_MSVC
XIEITE_COMPILER_TYPE_ICC
XIEITE_COMPILER_TYPE_MINGW

// Version Macros
XIEITE_COMPILER_VER(GCC, >=, 11, 0, 0)
XIEITE_COMPILER_VER(CLANG, >=, 14, 0, 0)
XIEITE_COMPILER_VER(MSVC, >=, 19, 29, 0)
```

### platform_string
**Header**: `sys/platform_string.hpp`
**Synopsis**: `constexpr std::string_view platform_string()`
**Purpose**: Get platform name as string
**Example**:
```cpp
constexpr auto platform = xieite::platform_string();
// Returns "windows", "linux", "macos", etc.
```

### arch_string
**Header**: `sys/arch_string.hpp`
**Synopsis**: `constexpr std::string_view arch_string()`
**Purpose**: Get architecture name as string
**Example**:
```cpp
constexpr auto arch = xieite::arch_string();
// Returns "x86_64", "aarch64", "x86", etc.
```

### compiler_string
**Header**: `sys/compiler_string.hpp`
**Synopsis**: `constexpr std::string_view compiler_string()`
**Purpose**: Get compiler name as string
**Example**:
```cpp
constexpr auto compiler = xieite::compiler_string();
// Returns "gcc", "clang", "msvc", etc.
```

## Environment Variables

### get_env
**Header**: `sys/get_env.hpp`
**Synopsis**: `std::optional<std::string> get_env(const std::string& name)`
**Purpose**: Get environment variable value
**Example**:
```cpp
auto path = xieite::get_env("PATH");
if (path) {
    std::cout << "PATH: " << *path << '\n';
}
```

### set_env
**Header**: `sys/set_env.hpp`
**Synopsis**: `bool set_env(const std::string& name, const std::string& value)`
**Purpose**: Set environment variable
**Example**:
```cpp
xieite::set_env("MY_VAR", "value");
```

### unset_env
**Header**: `sys/unset_env.hpp`
**Synopsis**: `bool unset_env(const std::string& name)`
**Purpose**: Remove environment variable
**Example**:
```cpp
xieite::unset_env("MY_VAR");
```

### env_exists
**Header**: `sys/env_exists.hpp`
**Synopsis**: `bool env_exists(const std::string& name)`
**Purpose**: Check if environment variable exists
**Example**:
```cpp
if (xieite::env_exists("HOME")) {
    // HOME variable exists
}
```

### env_expand
**Header**: `sys/env_expand.hpp`
**Synopsis**: `std::string env_expand(const std::string& str)`
**Purpose**: Expand environment variables in string
**Example**:
```cpp
auto expanded = xieite::env_expand("$HOME/documents");
// Expands to actual home path
```

## Endianness

### endian
**Header**: `sys/endian.hpp`
**Synopsis**: Endianness detection and conversion
**Purpose**: Handle byte order
**Types**:
```cpp
enum class endian {
    little = 0,
    big = 1,
    native = /* implementation-defined */
};
```

**Example**:
```cpp
if constexpr (xieite::endian::native == xieite::endian::little) {
    // Little-endian system
}
```

### byteswap
**Header**: `sys/byteswap.hpp`
**Synopsis**: `T byteswap(T value)`
**Purpose**: Reverse byte order
**Example**:
```cpp
uint32_t val = 0x12345678;
auto swapped = xieite::byteswap(val);  // 0x78563412
```

### to_little_endian
**Header**: `sys/to_little_endian.hpp`
**Synopsis**: `T to_little_endian(T value)`
**Purpose**: Convert to little-endian
**Example**:
```cpp
uint32_t native = 0x12345678;
auto little = xieite::to_little_endian(native);
```

### to_big_endian
**Header**: `sys/to_big_endian.hpp`
**Synopsis**: `T to_big_endian(T value)`
**Purpose**: Convert to big-endian
**Example**:
```cpp
uint32_t native = 0x12345678;
auto big = xieite::to_big_endian(native);
```

### from_little_endian
**Header**: `sys/from_little_endian.hpp`
**Synopsis**: `T from_little_endian(T value)`
**Purpose**: Convert from little-endian
**Example**:
```cpp
uint32_t little_val = read_little_endian_data();
auto native = xieite::from_little_endian(little_val);
```

### from_big_endian
**Header**: `sys/from_big_endian.hpp`
**Synopsis**: `T from_big_endian(T value)`
**Purpose**: Convert from big-endian
**Example**:
```cpp
uint32_t big_val = read_big_endian_data();
auto native = xieite::from_big_endian(big_val);
```

## System Queries

### cpu_count
**Header**: `sys/cpu_count.hpp`
**Synopsis**: `std::size_t cpu_count()`
**Purpose**: Get number of CPU cores
**Example**:
```cpp
auto cores = xieite::cpu_count();
std::cout << "CPU cores: " << cores << '\n';
```

### page_size
**Header**: `sys/page_size.hpp`
**Synopsis**: `std::size_t page_size()`
**Purpose**: Get system memory page size
**Example**:
```cpp
auto size = xieite::page_size();  // Typically 4096
```

### cache_line_size
**Header**: `sys/cache_line_size.hpp`
**Synopsis**: `constexpr std::size_t cache_line_size`
**Purpose**: Get CPU cache line size
**Example**:
```cpp
alignas(xieite::cache_line_size) struct aligned_data {
    int value;
};
```

### total_memory
**Header**: `sys/total_memory.hpp`
**Synopsis**: `std::size_t total_memory()`
**Purpose**: Get total system memory
**Example**:
```cpp
auto total = xieite::total_memory();
std::cout << "Total RAM: " << total / (1024*1024*1024) << " GB\n";
```

### available_memory
**Header**: `sys/available_memory.hpp`
**Synopsis**: `std::size_t available_memory()`
**Purpose**: Get available system memory
**Example**:
```cpp
auto available = xieite::available_memory();
```

### process_id
**Header**: `sys/process_id.hpp`
**Synopsis**: `int process_id()`
**Purpose**: Get current process ID
**Example**:
```cpp
auto pid = xieite::process_id();
std::cout << "Process ID: " << pid << '\n';
```

### thread_id
**Header**: `sys/thread_id.hpp`
**Synopsis**: `std::thread::id thread_id()`
**Purpose**: Get current thread ID
**Example**:
```cpp
auto tid = xieite::thread_id();
```

### username
**Header**: `sys/username.hpp`
**Synopsis**: `std::string username()`
**Purpose**: Get current username
**Example**:
```cpp
auto user = xieite::username();
std::cout << "User: " << user << '\n';
```

### hostname
**Header**: `sys/hostname.hpp`
**Synopsis**: `std::string hostname()`
**Purpose**: Get system hostname
**Example**:
```cpp
auto host = xieite::hostname();
std::cout << "Hostname: " << host << '\n';
```

### home_directory
**Header**: `sys/home_directory.hpp`
**Synopsis**: `std::filesystem::path home_directory()`
**Purpose**: Get user home directory
**Example**:
```cpp
auto home = xieite::home_directory();
auto config = home / ".config" / "myapp";
```

### temp_directory
**Header**: `sys/temp_directory.hpp`
**Synopsis**: `std::filesystem::path temp_directory()`
**Purpose**: Get temporary directory
**Example**:
```cpp
auto temp = xieite::temp_directory();
auto temp_file = temp / "myapp_temp.txt";
```

## Feature Detection

### has_sse
**Header**: `sys/has_sse.hpp`
**Synopsis**: `constexpr bool has_sse()`
**Purpose**: Check SSE support
**Example**:
```cpp
if constexpr (xieite::has_sse()) {
    // Use SSE instructions
}
```

### has_avx
**Header**: `sys/has_avx.hpp`
**Synopsis**: `constexpr bool has_avx()`
**Purpose**: Check AVX support
**Example**:
```cpp
if constexpr (xieite::has_avx()) {
    // Use AVX instructions
}
```

### has_avx2
**Header**: `sys/has_avx2.hpp`
**Synopsis**: `constexpr bool has_avx2()`
**Purpose**: Check AVX2 support
**Example**:
```cpp
if constexpr (xieite::has_avx2()) {
    // Use AVX2 instructions
}
```

### has_neon
**Header**: `sys/has_neon.hpp`
**Synopsis**: `constexpr bool has_neon()`
**Purpose**: Check ARM NEON support
**Example**:
```cpp
if constexpr (xieite::has_neon()) {
    // Use NEON instructions
}
```

### has_fma
**Header**: `sys/has_fma.hpp`
**Synopsis**: `constexpr bool has_fma()`
**Purpose**: Check FMA instruction support
**Example**:
```cpp
if constexpr (xieite::has_fma()) {
    // Use fused multiply-add
}
```

### simd_width
**Header**: `sys/simd_width.hpp`
**Synopsis**: `constexpr std::size_t simd_width()`
**Purpose**: Get SIMD register width
**Example**:
```cpp
constexpr auto width = xieite::simd_width();  // e.g., 256 for AVX
```

## Time Utilities

### high_resolution_clock
**Header**: `sys/high_resolution_clock.hpp`
**Synopsis**: High-resolution timing
**Purpose**: Precise time measurements
**Example**:
```cpp
auto start = xieite::high_resolution_clock::now();
// ... operation ...
auto end = xieite::high_resolution_clock::now();
auto duration = end - start;
```

### cpu_time
**Header**: `sys/cpu_time.hpp`
**Synopsis**: `double cpu_time()`
**Purpose**: Get CPU time used
**Example**:
```cpp
auto cpu_usage = xieite::cpu_time();
```

### wall_time
**Header**: `sys/wall_time.hpp`
**Synopsis**: `double wall_time()`
**Purpose**: Get wall clock time
**Example**:
```cpp
auto elapsed = xieite::wall_time();
```

## Process Control

### sleep_for
**Header**: `sys/sleep_for.hpp`
**Synopsis**: `void sleep_for(Duration d)`
**Purpose**: Sleep for duration
**Example**:
```cpp
using namespace std::chrono_literals;
xieite::sleep_for(100ms);
```

### yield
**Header**: `sys/yield.hpp`
**Synopsis**: `void yield()`
**Purpose**: Yield CPU to other threads
**Example**:
```cpp
while (!ready) {
    xieite::yield();
}
```

### exit
**Header**: `sys/exit.hpp`
**Synopsis**: `[[noreturn]] void exit(int code)`
**Purpose**: Exit process
**Example**:
```cpp
if (fatal_error) {
    xieite::exit(1);
}
```

### abort
**Header**: `sys/abort.hpp`
**Synopsis**: `[[noreturn]] void abort()`
**Purpose**: Abort process
**Example**:
```cpp
if (assertion_failed) {
    xieite::abort();
}
```

## Signal Handling

### signal_handler
**Header**: `sys/signal_handler.hpp`
**Synopsis**: `void signal_handler(int sig, void(*handler)(int))`
**Purpose**: Set signal handler
**Example**:
```cpp
xieite::signal_handler(SIGINT, [](int) {
    std::cout << "Interrupted\n";
    std::exit(0);
});
```

### ignore_signal
**Header**: `sys/ignore_signal.hpp`
**Synopsis**: `void ignore_signal(int sig)`
**Purpose**: Ignore signal
**Example**:
```cpp
xieite::ignore_signal(SIGPIPE);
```

## Memory Mapping

### memory_map
**Header**: `sys/memory_map.hpp`
**Synopsis**: `class memory_map`
**Purpose**: Memory-mapped file access
**Example**:
```cpp
xieite::memory_map map("large_file.dat");
auto* data = map.data();
auto size = map.size();
```

### shared_memory
**Header**: `sys/shared_memory.hpp`
**Synopsis**: `class shared_memory`
**Purpose**: Inter-process shared memory
**Example**:
```cpp
xieite::shared_memory shm("my_shm", 1024);
auto* ptr = shm.get<int>();
*ptr = 42;
```

## Usage Examples

### Platform-Specific Code
```cpp
#include <xieite/sys/os.hpp>
#include <xieite/sys/arch.hpp>

void optimize_for_platform() {
    #if XIEITE_OS_TYPE_WINDOWS && XIEITE_ARCH_TYPE_X86_64
        // Windows x64 optimizations
    #elif XIEITE_OS_TYPE_LINUX && XIEITE_ARCH_TYPE_AARCH64
        // Linux ARM64 optimizations
    #endif
}
```

### System Information
```cpp
#include <xieite/sys/cpu_count.hpp>
#include <xieite/sys/total_memory.hpp>
#include <xieite/sys/platform_string.hpp>

void print_system_info() {
    std::cout << "Platform: " << xieite::platform_string() << '\n';
    std::cout << "CPU cores: " << xieite::cpu_count() << '\n';
    std::cout << "Total memory: " << xieite::total_memory() / (1024*1024*1024) << " GB\n";
}
```

### Environment Variables
```cpp
#include <xieite/sys/get_env.hpp>
#include <xieite/sys/env_expand.hpp>

std::string get_config_path() {
    auto config = xieite::get_env("MY_APP_CONFIG");
    if (config) {
        return xieite::env_expand(*config);
    }
    return xieite::env_expand("$HOME/.config/myapp");
}
```

### Endianness Handling
```cpp
#include <xieite/sys/endian.hpp>
#include <xieite/sys/to_big_endian.hpp>

void write_network_data(uint32_t value) {
    // Network byte order is big-endian
    auto network_value = xieite::to_big_endian(value);
    write_to_socket(&network_value, sizeof(network_value));
}
```

## Performance Notes

- Platform detection is compile-time with zero cost
- Environment queries may have OS call overhead
- Memory mapping provides efficient file access
- SIMD detection enables optimal code paths
- Cache line alignment improves performance

## See Also

- [System Utilities Overview](../../categories/sys/README.md)
- [Platform Detection](../../categories/sys/platform.md)
- [Architecture Detection](../../categories/sys/architecture.md)
- [I/O API](./io.md)