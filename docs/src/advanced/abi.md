# ABI Considerations

This document covers Application Binary Interface (ABI) considerations when using XIEITE, including binary compatibility, symbol management, and strategies for maintaining stable interfaces across library versions.

## Understanding ABI in Header-Only Libraries

### Template Instantiation and ABI

XIEITE's header-only nature affects ABI in unique ways:

```cpp
#include <xieite/trait/is_arith.hpp>
#include <xieite/pp/arrow.hpp>

// Template instantiations affect ABI
namespace abi_considerations {
    template<xieite::is_arith T>
    class versioned_container {
        static constexpr int version = 1; // ABI version marker

    public:
        // ABI-stable interface
        void insert(const T& value) {
            data_.push_back(value);
        }

        std::size_t size() const noexcept {
            return data_.size();
        }

        // ABI-breaking change would be adding virtual functions
        // or changing data member layout

    private:
        std::vector<T> data_;
        // Adding new data members here would break ABI
    };

    // Explicit instantiation for common types to ensure ABI stability
    extern template class versioned_container<int>;
    extern template class versioned_container<double>;
    extern template class versioned_container<float>;
}
```

### Symbol Visibility and Linkage

Managing symbol visibility in header-only libraries:

```cpp
#include <xieite/pp/platform.hpp>
#include <xieite/pp/if.hpp>
#include <xieite/pp/attr.hpp>

namespace symbol_management {
    // Platform-specific symbol visibility
    XIEITE_PP_IF(XIEITE_PLATFORM_WINDOWS)(
        #define XIEITE_API_EXPORT __declspec(dllexport)
        #define XIEITE_API_IMPORT __declspec(dllimport)
        #define XIEITE_API_HIDDEN
    )

    XIEITE_PP_IF(!XIEITE_PLATFORM_WINDOWS)(
        #define XIEITE_API_EXPORT __attribute__((visibility("default")))
        #define XIEITE_API_IMPORT __attribute__((visibility("default")))
        #define XIEITE_API_HIDDEN __attribute__((visibility("hidden")))
    )

    // Conditional symbol export
    #ifdef XIEITE_BUILDING_LIBRARY
        #define XIEITE_API XIEITE_API_EXPORT
    #else
        #define XIEITE_API XIEITE_API_IMPORT
    #endif

    // ABI-stable interface with controlled visibility
    class XIEITE_API stable_interface {
    public:
        // Public ABI - must remain stable
        virtual ~stable_interface() = default;
        virtual void process(int value) = 0;
        virtual int get_result() const = 0;

        // Non-virtual interface for performance
        void utility_function(int x) {
            // Inline implementation - no ABI impact
            process(x * 2);
        }

    protected:
        // Protected members don't affect ABI
        int internal_state_ = 0;

    private:
        // Private implementation details
        XIEITE_API_HIDDEN void hidden_implementation();
    };

    // Implementation class with hidden symbols
    class XIEITE_API_HIDDEN implementation_details {
    public:
        static void internal_helper() {
            // Hidden from ABI
        }
    };
}
```

## ABI Versioning Strategies

### Version-Based Namespaces

Using namespaces to maintain ABI compatibility:

```cpp
#include <xieite/pp/ver.hpp>

// Version-specific namespaces
namespace xieite::v1 {
    template<typename T>
    class container {
        std::vector<T> data_;
    public:
        void add(const T& item) { data_.push_back(item); }
        std::size_t count() const { return data_.size(); }
    };
}

namespace xieite::v2 {
    template<typename T>
    class container {
        std::vector<T> data_;
        std::string name_; // Added in v2 - breaks v1 ABI
    public:
        void add(const T& item) { data_.push_back(item); }
        std::size_t count() const { return data_.size(); }

        // New functionality in v2
        void set_name(const std::string& name) { name_ = name; }
        const std::string& get_name() const { return name_; }
    };
}

// Current version alias
namespace xieite {
    inline namespace current {
        using namespace v2; // Point to current version
    }
}

// Backward compatibility layer
namespace xieite::compat {
    template<typename T>
    using container_v1 = v1::container<T>;
}
```

### ABI-Safe Evolution Patterns

Patterns for evolving interfaces without breaking ABI:

```cpp
#include <xieite/trait/is_arith.hpp>
#include <xieite/pp/arrow.hpp>

namespace abi_evolution {
    // Base interface that never changes
    template<typename T>
    class stable_base {
    public:
        virtual ~stable_base() = default;
        virtual void process(const T& value) = 0;
        virtual T get_result() const = 0;

        // ABI-safe way to add functionality
        virtual void process_v2(const T& value, int flags) {
            // Default implementation for backward compatibility
            if (flags == 0) {
                process(value);
            } else {
                // Extended functionality
                process_with_flags(value, flags);
            }
        }

    protected:
        virtual void process_with_flags(const T& value, int flags) {
            // Default implementation
            process(value);
        }
    };

    // Implementation that can evolve
    template<xieite::is_arith T>
    class evolving_implementation : public stable_base<T> {
        T result_ = T{};

        // Private data can be added at the end without ABI breakage
        // (as long as the class isn't used in arrays or as value types)

    public:
        void process(const T& value) override {
            result_ = value * value;
        }

        T get_result() const override {
            return result_;
        }

        // Override v2 functionality
        void process_v2(const T& value, int flags) override {
            if (flags & 1) {
                result_ = value * value * value; // Cubic instead of square
            } else {
                process(value);
            }
        }
    };

    // Factory function for ABI stability
    template<typename T>
    std::unique_ptr<stable_base<T>> create_processor() {
        return std::make_unique<evolving_implementation<T>>();
    }
}
```

## Memory Layout and Alignment

### Controlling Data Layout

Ensuring consistent memory layout across compilers:

```cpp
#include <xieite/pp/compiler.hpp>
#include <xieite/pp/if.hpp>
#include <xieite/trait/is_arith.hpp>

namespace layout_control {
    // Portable alignment specification
    XIEITE_PP_IF(XIEITE_COMPILER_MSVC)(
        #define XIEITE_ALIGNAS(n) __declspec(align(n))
    )
    XIEITE_PP_IF(!XIEITE_COMPILER_MSVC)(
        #define XIEITE_ALIGNAS(n) __attribute__((aligned(n)))
    )

    // Pack structures for ABI consistency
    XIEITE_PP_IF(XIEITE_COMPILER_MSVC)(
        #pragma pack(push, 1)
    )

    struct XIEITE_PP_IF(!XIEITE_COMPILER_MSVC)(__attribute__((packed)))
    abi_stable_header {
        uint32_t version;    // 4 bytes
        uint32_t size;       // 4 bytes
        uint64_t timestamp;  // 8 bytes
        // Total: 16 bytes, consistent across platforms
    };

    XIEITE_PP_IF(XIEITE_COMPILER_MSVC)(
        #pragma pack(pop)
    )

    // Cache-line aligned structure
    struct XIEITE_ALIGNAS(64) cache_aligned_data {
        std::atomic<int> counter;
        char padding[60]; // Ensure 64-byte total size
    };

    // Portable size assertions
    static_assert(sizeof(abi_stable_header) == 16, "Header size must be 16 bytes");
    static_assert(sizeof(cache_aligned_data) == 64, "Data size must be 64 bytes");
    static_assert(alignof(cache_aligned_data) == 64, "Data must be 64-byte aligned");
}
```

### Template Specialization ABI

Managing ABI across template specializations:

```cpp
#include <xieite/trait/is_arith.hpp>

namespace specialization_abi {
    // Primary template with stable ABI
    template<typename T>
    class processor {
        T data_;
        static constexpr std::size_t padding_size = 64 - sizeof(T);
        char padding[padding_size > 0 ? padding_size : 1];

    public:
        void process(const T& value) {
            data_ = value;
        }

        const T& get_data() const {
            return data_;
        }
    };

    // Specializations must maintain same memory layout
    template<>
    class processor<double> {
        double data_;
        char padding[56]; // 64 - sizeof(double) = 56

    public:
        void process(const double& value) {
            data_ = value * 2.0; // Different behavior, same interface
        }

        const double& get_data() const {
            return data_;
        }
    };

    // Verify consistent sizing
    static_assert(sizeof(processor<int>) == 64);
    static_assert(sizeof(processor<double>) == 64);
    static_assert(sizeof(processor<float>) == 64);
}
```

## Cross-Platform ABI Considerations

### Calling Conventions

Handling different calling conventions:

```cpp
#include <xieite/pp/platform.hpp>
#include <xieite/pp/if.hpp>

namespace calling_conventions {
    // Platform-specific calling conventions
    XIEITE_PP_IF(XIEITE_PLATFORM_WINDOWS)(
        #define XIEITE_STDCALL __stdcall
        #define XIEITE_CDECL __cdecl
        #define XIEITE_FASTCALL __fastcall
    )
    XIEITE_PP_IF(!XIEITE_PLATFORM_WINDOWS)(
        #define XIEITE_STDCALL
        #define XIEITE_CDECL
        #define XIEITE_FASTCALL
    )

    // C interface for ABI stability
    extern "C" {
        // Stable C ABI for critical functions
        XIEITE_CDECL int xieite_process_int(int value);
        XIEITE_CDECL double xieite_process_double(double value);
        XIEITE_CDECL void xieite_cleanup();
    }

    // C++ wrapper with exception safety
    namespace cpp_interface {
        template<xieite::is_arith T>
        T safe_process(T value) {
            if constexpr (std::is_same_v<T, int>) {
                return xieite_process_int(value);
            } else if constexpr (std::is_same_v<T, double>) {
                return xieite_process_double(value);
            } else {
                // Generic implementation for other types
                return value * T{2};
            }
        }

        class RAII_cleanup {
        public:
            ~RAII_cleanup() {
                xieite_cleanup();
            }
        };
    }
}
```

### Name Mangling and Linkage

Managing symbol names across compilers:

```cpp
#include <xieite/pp/compiler.hpp>
#include <xieite/pp/if.hpp>

namespace symbol_naming {
    // Prevent name mangling for critical symbols
    extern "C" {
        // Stable symbol names
        int xieite_get_version();
        const char* xieite_get_build_info();
    }

    // Compiler-specific name mangling control
    XIEITE_PP_IF(XIEITE_COMPILER_MSVC)(
        #pragma comment(linker, "/EXPORT:xieite_get_version")
        #pragma comment(linker, "/EXPORT:xieite_get_build_info")
    )

    // Inline namespace for ABI versioning
    inline namespace v1_0 {
        template<typename T>
        class versioned_api {
        public:
            static constexpr int abi_version = 1;

            void method_v1(const T& value) {
                // Version 1 implementation
            }
        };
    }

    // Future version would use different inline namespace
    namespace v2_0 {
        template<typename T>
        class versioned_api {
        public:
            static constexpr int abi_version = 2;

            void method_v1(const T& value) {
                // Backward compatible implementation
            }

            void method_v2(const T& value, int flags) {
                // New functionality
            }
        };
    }
}
```

## ABI Testing and Validation

### Binary Compatibility Testing

Tools and techniques for ABI validation:

```cpp
#include <xieite/trait/is_arith.hpp>

namespace abi_testing {
    // ABI test structure with known layout
    struct abi_test_struct {
        int32_t version;
        int64_t timestamp;
        double value;
        char name[32];
    };

    // Compile-time ABI validation
    static_assert(sizeof(abi_test_struct) == 48, "ABI test struct size changed");
    static_assert(offsetof(abi_test_struct, version) == 0, "Version offset changed");
    static_assert(offsetof(abi_test_struct, timestamp) == 8, "Timestamp offset changed");
    static_assert(offsetof(abi_test_struct, value) == 16, "Value offset changed");
    static_assert(offsetof(abi_test_struct, name) == 24, "Name offset changed");

    // Runtime ABI validation
    class abi_validator {
    public:
        static bool validate_layout() {
            abi_test_struct test{};

            // Check pointer arithmetic
            auto* base = reinterpret_cast<char*>(&test);
            auto* version_ptr = reinterpret_cast<char*>(&test.version);
            auto* timestamp_ptr = reinterpret_cast<char*>(&test.timestamp);
            auto* value_ptr = reinterpret_cast<char*>(&test.value);
            auto* name_ptr = reinterpret_cast<char*>(&test.name);

            return (version_ptr - base) == 0 &&
                   (timestamp_ptr - base) == 8 &&
                   (value_ptr - base) == 16 &&
                   (name_ptr - base) == 24;
        }

        template<typename T>
        static bool validate_template_abi() {
            // Validate template instantiation produces expected layout
            specialization_abi::processor<T> proc;
            return sizeof(proc) == 64;
        }
    };

    // ABI signature generation for comparison
    template<typename T>
    constexpr auto generate_abi_signature() {
        struct signature {
            std::size_t size;
            std::size_t alignment;
            int version;
        };

        return signature{
            sizeof(T),
            alignof(T),
            1 // ABI version
        };
    }
}
```

## Best Practices for ABI Stability

### Design Guidelines

1. **Minimize Public Data Members**: Use private data with public accessors
2. **Avoid Virtual Function Changes**: Don't add, remove, or reorder virtual functions
3. **Use Opaque Pointers**: Hide implementation details behind pointers
4. **Version Interfaces**: Use versioned namespaces or function names
5. **Prefer Non-Virtual Interfaces**: Virtual functions complicate ABI evolution
6. **Control Symbol Visibility**: Export only necessary symbols
7. **Test ABI Changes**: Validate binary compatibility between versions

### ABI Breakage Patterns to Avoid

1. **Changing Data Member Order**: Reordering breaks layout
2. **Adding Virtual Functions**: Changes vtable layout
3. **Changing Function Signatures**: Breaks symbol matching
4. **Template Parameter Changes**: Creates different instantiations
5. **Exception Specification Changes**: Affects calling convention
6. **Alignment Changes**: Breaks memory layout assumptions

### Migration Strategies

1. **Deprecation Warnings**: Mark old interfaces as deprecated
2. **Compatibility Layers**: Provide wrappers for old interfaces
3. **Version Coexistence**: Allow multiple versions to coexist
4. **Gradual Migration**: Phase out old interfaces over multiple releases
5. **Documentation**: Clearly document ABI compatibility guarantees

This comprehensive approach to ABI management ensures XIEITE-based libraries can evolve while maintaining binary compatibility with existing applications.