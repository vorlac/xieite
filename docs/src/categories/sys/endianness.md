# Endianness Detection

## Overview

XIEITE provides comprehensive endianness detection through preprocessor macros, supporting detection of big-endian, little-endian, and rare word-endian architectures. The system automatically detects byte order from compiler definitions, architecture characteristics, and platform-specific headers.

## Core Endianness Detection

### Endianness Type Macros
Implementation: `include/xieite/pp/endian.hpp` (lines 4-7, 45-52, 55-57)

```cpp
// Endianness detection macros (initially all set to 0)
#define XIEITE_ENDIAN_BIG 0          // Standard big-endian
#define XIEITE_ENDIAN_LITTLE 0       // Standard little-endian
#define XIEITE_ENDIAN_BIG_WORD 0     // Big-endian words (Honeywell 316)
#define XIEITE_ENDIAN_LITTLE_WORD 0  // Little-endian words (PDP-11)

// Set to 1 when corresponding endianness is detected
#if defined(BIG_ENDIAN) || defined(_BIG_ENDIAN) || /* ... many conditions ... */
#    undef XIEITE_ENDIAN_BIG
#    define XIEITE_ENDIAN_BIG 1
#endif

#if defined(LITTLE_ENDIAN) || defined(_LITTLE_ENDIAN) || /* ... many conditions ... */
#    undef XIEITE_ENDIAN_LITTLE
#    define XIEITE_ENDIAN_LITTLE 1
#endif

#if defined(__BYTE_ORDER) && (__BYTE_ORDER == __PDP_ENDIAN)
#    undef XIEITE_ENDIAN_LITTLE_WORD
#    define XIEITE_ENDIAN_LITTLE_WORD 1
#endif
```

Each macro is set to `1` when the corresponding endianness is detected, providing compile-time endianness information.

## Detection Sources

### Compiler Intrinsics
Implementation: `include/xieite/pp/endian.hpp` (lines 44-52)

**Big-Endian Detection (line 44):**
- `BIG_ENDIAN`, `_BIG_ENDIAN` - Standard definitions
- `_MIPSEB`, `__MIPSEB`, `__MIPSEB__` - MIPS big-endian
- `__AARCH64EB__`, `__ARMEB__` - ARM big-endian variants
- `__BIG_ENDIAN__` - GCC big-endian marker
- `__BYTE_ORDER == __BIG_ENDIAN` - Byte order comparison
- `__THUMBEB__` - ARM Thumb big-endian
- `sel` - SEL4 microkernel indicator

**Little-Endian Detection (line 49):**
- `LITTLE_ENDIAN`, `_LITTLE_ENDIAN` - Standard definitions
- `_MIPSEL`, `__MIPSEL`, `__MIPSEL__` - MIPS little-endian
- `__AARCH64EL__`, `__ARMEL__` - ARM little-endian variants
- `__LITTLE_ENDIAN__` - GCC little-endian marker
- `__BYTE_ORDER == __LITTLE_ENDIAN` - Byte order comparison
- `__THUMBEL__` - ARM Thumb little-endian

### Architecture-Based Detection
Implementation: `include/xieite/pp/endian.hpp` (lines 44, 49)

**Big-Endian Architectures:**
- `XIEITE_ARCH_TYPE_ELBRUS_2000` - Elbrus 2000 processor
- `XIEITE_ARCH_TYPE_IBM_SYSTEM_370` - IBM System/370
- `XIEITE_ARCH_TYPE_IBM_SYSTEM_390` - IBM System/390
- `XIEITE_ARCH_TYPE_IBM_Z` - IBM Z series
- `XIEITE_ARCH_TYPE_MOTOROLA_68000` - Motorola 68000 family
- `XIEITE_ARCH_TYPE_PA_RISC` - HP PA-RISC
- `XIEITE_ARCH_TYPE_POWERPC` - PowerPC family
- `XIEITE_ARCH_TYPE_SPARC` - SPARC family

**Little-Endian Architectures:**
- `XIEITE_ARCH_TYPE_ALPHA` - DEC Alpha
- `XIEITE_ARCH_TYPE_ARM` - ARM family
- `XIEITE_ARCH_TYPE_BLACKFIN` - Analog Devices Blackfin
- `XIEITE_ARCH_TYPE_IA64` - Intel Itanium
- `XIEITE_ARCH_TYPE_X86_32` - x86 32-bit
- `XIEITE_ARCH_TYPE_X86_64` - x86-64

### Platform-Based Detection
Implementation: `include/xieite/pp/endian.hpp` (lines 44, 49)

**Platforms with Big-Endian Tendencies:**
- `XIEITE_PLATFORM_TYPE_AIX` - IBM AIX
- `XIEITE_PLATFORM_TYPE_HP_UX` - HP-UX
- `XIEITE_PLATFORM_TYPE_IRIX` - SGI IRIX
- `XIEITE_PLATFORM_TYPE_SOLARIS` - Oracle Solaris

**Platforms with Little-Endian Tendencies:**
- `XIEITE_PLATFORM_TYPE_CYGWIN` - Cygwin environment
- `XIEITE_PLATFORM_TYPE_WINDOWS` - Microsoft Windows

### System Headers
Implementation: `include/xieite/pp/endian.hpp` (lines 12-42)

The system automatically includes available endianness headers:

```cpp
#if __has_include(<endian.h>)
#    include <endian.h>          // Standard endian.h
#endif

#if __has_include(<libkern/OSByteOrder.h>)
#    include <libkern/OSByteOrder.h>  // macOS byte order
#endif

#if __has_include(<machine/endian.h>)
#    include <machine/endian.h>  // BSD machine endian
#endif

#if __has_include(<sys/endian.h>)
#    include <sys/endian.h>      // System endian definitions
#endif

#if __has_include(<sys/_endian.h>)
#    include <sys/_endian.h>     // FreeBSD internal endian
#endif

#if __has_include(<sys/param.h>)
#    include <sys/param.h>       // System parameters
#endif

#if __has_include(<sys/types.h>)
#    include <sys/types.h>       // System type definitions
#endif

#if __has_include(<winsock2.h>)
#    include <winsock2.h>        // Windows socket definitions
#endif
```

## Usage Examples

### Basic Endianness Testing
```cpp
#include <xieite/pp/endian.hpp>
#include <iostream>

void print_endianness() {
    std::cout << "System Endianness:\n";

#if XIEITE_ENDIAN_LITTLE
    std::cout << "  Little-endian detected\n";
#elif XIEITE_ENDIAN_BIG
    std::cout << "  Big-endian detected\n";
#elif XIEITE_ENDIAN_LITTLE_WORD
    std::cout << "  Little-endian word (PDP-11 style) detected\n";
#elif XIEITE_ENDIAN_BIG_WORD
    std::cout << "  Big-endian word (Honeywell 316 style) detected\n";
#else
    std::cout << "  Unknown endianness\n";
#endif

    // Runtime verification
    constexpr uint32_t test_value = 0x12345678;
    const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&test_value);

    std::cout << "  Runtime verification: ";
    if (bytes[0] == 0x12) {
        std::cout << "Big-endian\n";
    } else if (bytes[0] == 0x78) {
        std::cout << "Little-endian\n";
    } else {
        std::cout << "Mixed endianness\n";
    }
}
```

### Endian-Safe Binary I/O
```cpp
#include <xieite/pp/endian.hpp>
#include <cstdint>
#include <iostream>
#include <fstream>

// Endian-safe serialization
class BinaryWriter {
private:
    std::ostream& stream_;

    template<typename T>
    void write_little_endian(T value) {
        const uint8_t* bytes = reinterpret_cast<const uint8_t*>(&value);

#if XIEITE_ENDIAN_LITTLE
        // Native little-endian: write directly
        stream_.write(reinterpret_cast<const char*>(bytes), sizeof(T));
#elif XIEITE_ENDIAN_BIG
        // Big-endian: reverse byte order
        for (int i = sizeof(T) - 1; i >= 0; --i) {
            stream_.write(reinterpret_cast<const char*>(&bytes[i]), 1);
        }
#else
        // Unknown endianness: detect at runtime
        uint16_t test = 0x0102;
        const uint8_t* test_bytes = reinterpret_cast<const uint8_t*>(&test);

        if (test_bytes[0] == 0x02) {
            // Runtime little-endian
            stream_.write(reinterpret_cast<const char*>(bytes), sizeof(T));
        } else {
            // Runtime big-endian
            for (int i = sizeof(T) - 1; i >= 0; --i) {
                stream_.write(reinterpret_cast<const char*>(&bytes[i]), 1);
            }
        }
#endif
    }

public:
    BinaryWriter(std::ostream& stream) : stream_(stream) {}

    void write_uint32(uint32_t value) {
        write_little_endian(value);
    }

    void write_uint16(uint16_t value) {
        write_little_endian(value);
    }

    void write_double(double value) {
        write_little_endian(value);
    }
};

// Endian-safe deserialization
class BinaryReader {
private:
    std::istream& stream_;

    template<typename T>
    T read_little_endian() {
        uint8_t bytes[sizeof(T)];
        stream_.read(reinterpret_cast<char*>(bytes), sizeof(T));

#if XIEITE_ENDIAN_LITTLE
        // Native little-endian: use directly
        return *reinterpret_cast<T*>(bytes);
#elif XIEITE_ENDIAN_BIG
        // Big-endian: reverse byte order
        uint8_t reversed[sizeof(T)];
        for (std::size_t i = 0; i < sizeof(T); ++i) {
            reversed[i] = bytes[sizeof(T) - 1 - i];
        }
        return *reinterpret_cast<T*>(reversed);
#else
        // Unknown endianness: detect at runtime
        uint16_t test = 0x0102;
        const uint8_t* test_bytes = reinterpret_cast<const uint8_t*>(&test);

        if (test_bytes[0] == 0x02) {
            // Runtime little-endian
            return *reinterpret_cast<T*>(bytes);
        } else {
            // Runtime big-endian
            uint8_t reversed[sizeof(T)];
            for (std::size_t i = 0; i < sizeof(T); ++i) {
                reversed[i] = bytes[sizeof(T) - 1 - i];
            }
            return *reinterpret_cast<T*>(reversed);
        }
#endif
    }

public:
    BinaryReader(std::istream& stream) : stream_(stream) {}

    uint32_t read_uint32() {
        return read_little_endian<uint32_t>();
    }

    uint16_t read_uint16() {
        return read_little_endian<uint16_t>();
    }

    double read_double() {
        return read_little_endian<double>();
    }
};

// Usage
void serialize_data() {
    std::ofstream file("data.bin", std::ios::binary);
    BinaryWriter writer(file);

    writer.write_uint32(0x12345678);
    writer.write_uint16(0xABCD);
    writer.write_double(3.14159);
}

void deserialize_data() {
    std::ifstream file("data.bin", std::ios::binary);
    BinaryReader reader(file);

    uint32_t value1 = reader.read_uint32();
    uint16_t value2 = reader.read_uint16();
    double value3 = reader.read_double();

    std::cout << std::hex << "Value1: 0x" << value1 << "\n";
    std::cout << std::hex << "Value2: 0x" << value2 << "\n";
    std::cout << std::fixed << "Value3: " << value3 << "\n";
}
```

### Network Byte Order Conversion
```cpp
#include <xieite/pp/endian.hpp>
#include <cstdint>

// Network byte order utilities (big-endian)
namespace network_order {

template<typename T>
T host_to_network(T value) {
#if XIEITE_ENDIAN_BIG
    // Already big-endian
    return value;
#elif XIEITE_ENDIAN_LITTLE
    // Convert little-endian to big-endian
    T result;
    const uint8_t* src = reinterpret_cast<const uint8_t*>(&value);
    uint8_t* dst = reinterpret_cast<uint8_t*>(&result);

    for (std::size_t i = 0; i < sizeof(T); ++i) {
        dst[i] = src[sizeof(T) - 1 - i];
    }

    return result;
#else
    // Runtime detection
    uint16_t test = 0x0102;
    const uint8_t* test_bytes = reinterpret_cast<const uint8_t*>(&test);

    if (test_bytes[0] == 0x01) {
        // Runtime big-endian
        return value;
    } else {
        // Runtime little-endian
        T result;
        const uint8_t* src = reinterpret_cast<const uint8_t*>(&value);
        uint8_t* dst = reinterpret_cast<uint8_t*>(&result);

        for (std::size_t i = 0; i < sizeof(T); ++i) {
            dst[i] = src[sizeof(T) - 1 - i];
        }

        return result;
    }
#endif
}

template<typename T>
T network_to_host(T value) {
    // Network to host is the same operation as host to network
    return host_to_network(value);
}

// Specialized functions for common types
uint16_t htons(uint16_t value) { return host_to_network(value); }
uint32_t htonl(uint32_t value) { return host_to_network(value); }
uint64_t htonll(uint64_t value) { return host_to_network(value); }

uint16_t ntohs(uint16_t value) { return network_to_host(value); }
uint32_t ntohl(uint32_t value) { return network_to_host(value); }
uint64_t ntohll(uint64_t value) { return network_to_host(value); }

} // namespace network_order
```

## Advanced Patterns

### Compile-Time Endian-Aware Data Structures
```cpp
#include <xieite/pp/endian.hpp>
#include <array>
#include <cstdint>

// Endian-aware integer storage
template<typename T>
struct LittleEndianInteger {
private:
    std::array<uint8_t, sizeof(T)> bytes_;

public:
    LittleEndianInteger() = default;

    LittleEndianInteger(T value) {
        set(value);
    }

    void set(T value) {
#if XIEITE_ENDIAN_LITTLE
        // Native little-endian: direct copy
        std::memcpy(bytes_.data(), &value, sizeof(T));
#elif XIEITE_ENDIAN_BIG
        // Big-endian: reverse bytes
        const uint8_t* src = reinterpret_cast<const uint8_t*>(&value);
        for (std::size_t i = 0; i < sizeof(T); ++i) {
            bytes_[i] = src[sizeof(T) - 1 - i];
        }
#else
        // Runtime detection
        uint16_t test = 0x0102;
        const uint8_t* test_bytes = reinterpret_cast<const uint8_t*>(&test);

        if (test_bytes[0] == 0x02) {
            // Runtime little-endian
            std::memcpy(bytes_.data(), &value, sizeof(T));
        } else {
            // Runtime big-endian
            const uint8_t* src = reinterpret_cast<const uint8_t*>(&value);
            for (std::size_t i = 0; i < sizeof(T); ++i) {
                bytes_[i] = src[sizeof(T) - 1 - i];
            }
        }
#endif
    }

    T get() const {
#if XIEITE_ENDIAN_LITTLE
        // Native little-endian: direct copy
        T result;
        std::memcpy(&result, bytes_.data(), sizeof(T));
        return result;
#elif XIEITE_ENDIAN_BIG
        // Big-endian: reverse bytes
        T result;
        uint8_t* dst = reinterpret_cast<uint8_t*>(&result);
        for (std::size_t i = 0; i < sizeof(T); ++i) {
            dst[i] = bytes_[sizeof(T) - 1 - i];
        }
        return result;
#else
        // Runtime detection
        uint16_t test = 0x0102;
        const uint8_t* test_bytes = reinterpret_cast<const uint8_t*>(&test);

        T result;
        if (test_bytes[0] == 0x02) {
            // Runtime little-endian
            std::memcpy(&result, bytes_.data(), sizeof(T));
        } else {
            // Runtime big-endian
            uint8_t* dst = reinterpret_cast<uint8_t*>(&result);
            for (std::size_t i = 0; i < sizeof(T); ++i) {
                dst[i] = bytes_[sizeof(T) - 1 - i];
            }
        }
        return result;
#endif
    }

    operator T() const {
        return get();
    }

    LittleEndianInteger& operator=(T value) {
        set(value);
        return *this;
    }
};

// Type aliases for common uses
using le_uint16_t = LittleEndianInteger<uint16_t>;
using le_uint32_t = LittleEndianInteger<uint32_t>;
using le_uint64_t = LittleEndianInteger<uint64_t>;

// Usage
struct NetworkPacket {
    le_uint32_t packet_id;
    le_uint16_t data_length;
    le_uint32_t checksum;

    // Data is always stored in little-endian format regardless of host endianness
};
```

## Implementation Details

### Detection Strategy
The endianness detection employs a multi-layered approach:

1. **Compiler Definitions** - Standard and compiler-specific endianness macros
2. **Architecture Inference** - Known endianness of specific processor architectures
3. **Platform Defaults** - Platform-typical endianness assumptions
4. **System Headers** - Automatic inclusion of available endianness headers

### Macro Redefinition Pattern
The implementation uses `#undef` followed by `#define` to handle potential conflicts:
```cpp
#undef XIEITE_ENDIAN_BIG
#define XIEITE_ENDIAN_BIG 1
```

This ensures clean macro state regardless of prior definitions.

### Word Endianness Support
The library includes support for historical word-endian architectures:
- **PDP-11 style** (`XIEITE_ENDIAN_LITTLE_WORD`) - Little-endian words in big-endian bytes
- **Honeywell 316 style** (`XIEITE_ENDIAN_BIG_WORD`) - Big-endian words

## Performance Considerations

- **Compile-time detection**: All endianness checks happen at compile time
- **Zero runtime overhead**: Optimized away by modern compilers
- **Conditional compilation**: Dead code elimination removes unused branches
- **Template specialization**: Can enable type-specific optimizations

## Best Practices

1. **Always provide runtime fallback** - Some systems may not be detected at compile time
2. **Use fixed-width types** - Ensure consistent behavior across platforms
3. **Test on target hardware** - Verify endianness assumptions on actual deployment targets
4. **Document format assumptions** - Clearly specify endianness in file formats and protocols

## Common Use Cases

### Network Protocol Implementation
```cpp
#include <xieite/pp/endian.hpp>

struct ProtocolHeader {
#if XIEITE_ENDIAN_BIG
    // Network byte order matches host
    uint32_t message_id;
    uint16_t length;
    uint16_t flags;
#else
    // Need conversion for network byte order
    uint32_t message_id;
    uint16_t length;
    uint16_t flags;

    void to_network_order() {
        message_id = __builtin_bswap32(message_id);
        length = __builtin_bswap16(length);
        flags = __builtin_bswap16(flags);
    }

    void from_network_order() {
        to_network_order(); // Same operation
    }
#endif
};
```

### Cross-Platform Configuration Files
```cpp
// Configuration file with endianness metadata
struct Config {
    static constexpr uint32_t ENDIAN_CHECK = 0x12345678;

    uint32_t endian_marker = ENDIAN_CHECK;
    // ... configuration data ...

    bool validate_endianness() const {
        return endian_marker == ENDIAN_CHECK;
    }
};
```

## See Also

- [Architecture Detection](./architecture.md) - Processor architecture identification
- [Platform Detection](./platform.md) - Operating system detection
- [Compiler Detection](../pp/compiler.md) - Compiler identification
- [System API Reference](../../reference/api/sys.md)