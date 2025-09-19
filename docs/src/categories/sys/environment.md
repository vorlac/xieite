# Environment Variables

## Overview

Environment variable utilities provide cross-platform access to system environment variables and configuration settings. This category would include functions for reading, writing, and managing environment variables in a type-safe, cross-platform manner.

## Current Status

**Note**: Environment variable utilities are not currently implemented in XIEITE. This documentation serves as a specification for future implementation and describes the planned functionality.

## Planned Utilities

### Environment Variable Access

The planned environment variable utilities would provide:

```cpp
// Proposed interface - not yet implemented
namespace xieite::sys {
    // Get environment variable with optional default
    std::optional<std::string> get_env(const std::string& name);
    std::string get_env(const std::string& name, const std::string& default_value);

    // Set environment variable (platform-specific behavior)
    bool set_env(const std::string& name, const std::string& value);

    // Check if environment variable exists
    bool has_env(const std::string& name);

    // Remove environment variable
    bool unset_env(const std::string& name);

    // Get all environment variables
    std::map<std::string, std::string> get_all_env();
}
```

### Type-Safe Environment Access

Type-safe utilities for common environment variable patterns:

```cpp
// Proposed interface - not yet implemented
namespace xieite::sys {
    // Template for type-safe environment variable access
    template<typename T>
    std::optional<T> get_env_as(const std::string& name);

    template<typename T>
    T get_env_as(const std::string& name, const T& default_value);

    // Specialized versions for common types
    std::optional<int> get_env_int(const std::string& name);
    std::optional<bool> get_env_bool(const std::string& name);
    std::optional<double> get_env_double(const std::string& name);
    std::optional<std::filesystem::path> get_env_path(const std::string& name);
}
```

### Platform-Specific Considerations

Environment variable handling varies across platforms:

#### Windows Implementation Considerations
```cpp
// Windows-specific considerations (not implemented)
// - Use GetEnvironmentVariable() and SetEnvironmentVariable()
// - Handle Unicode strings properly
// - Consider process vs user vs system environment scopes
```

#### Unix/Linux Implementation Considerations
```cpp
// Unix/Linux-specific considerations (not implemented)
// - Use std::getenv() for reading
// - Use setenv()/putenv() for writing
// - Handle shell expansion and variable substitution
// - Consider security implications of environment modification
```

## Integration with Existing XIEITE Utilities

When implemented, environment utilities would integrate with existing XIEITE components:

### Platform Detection Integration

```cpp
// Proposed integration with platform detection
#include <xieite/pp/platform.hpp>

// Platform-specific environment variable patterns
#if XIEITE_PLATFORM_TYPE_WINDOWS
    // Windows environment variable patterns
    auto user_profile = xieite::sys::get_env("USERPROFILE");
    auto program_files = xieite::sys::get_env("PROGRAMFILES");
#elif XIEITE_PLATFORM_TYPE_UNIX || XIEITE_PLATFORM_TYPE_LINUX
    // Unix/Linux environment variable patterns
    auto home_dir = xieite::sys::get_env("HOME");
    auto path_var = xieite::sys::get_env("PATH");
#endif
```

### String Utility Integration

```cpp
// Proposed integration with string utilities
#include <xieite/data/str_join.hpp>

// Path manipulation using environment variables
auto create_search_path() {
    auto path_env = xieite::sys::get_env("PATH", "");

    // Split PATH and add custom directories
    std::vector<std::string> paths = /* split path_env by delimiter */;
    paths.push_back("/usr/local/bin");

    return xieite::str_join(paths, ":");
}
```

## Workarounds and Alternatives

Until environment variable utilities are implemented in XIEITE, you can use standard library alternatives:

### Standard Library Approach

```cpp
#include <cstdlib>
#include <string>
#include <optional>

// Manual implementation using std::getenv
std::optional<std::string> get_environment_variable(const char* name) {
    const char* value = std::getenv(name);
    return value ? std::make_optional(std::string(value)) : std::nullopt;
}

// Usage example
if (auto home = get_environment_variable("HOME")) {
    std::cout << "Home directory: " << *home << '\n';
} else {
    std::cout << "HOME not set\n";
}
```

### Cross-Platform Implementation

```cpp
#include <xieite/pp/platform.hpp>
#include <string>
#include <optional>

std::optional<std::string> get_env_cross_platform(const std::string& name) {
#if XIEITE_PLATFORM_TYPE_WINDOWS
    // Windows implementation
    char* buffer;
    size_t size;

    if (_dupenv_s(&buffer, &size, name.c_str()) == 0 && buffer) {
        std::string result(buffer);
        free(buffer);
        return result;
    }
    return std::nullopt;
#else
    // Unix/Linux implementation
    const char* value = std::getenv(name.c_str());
    return value ? std::make_optional(std::string(value)) : std::nullopt;
#endif
}
```

## Implementation Roadmap

When environment variable utilities are added to XIEITE, they should include:

### Core Functionality
1. **Basic access functions** - get/set/unset environment variables
2. **Type conversion** - automatic conversion to common types
3. **Cross-platform support** - unified interface across operating systems
4. **Error handling** - proper error reporting for failed operations

### Advanced Features
1. **Environment scoping** - support for different environment variable scopes
2. **Variable expansion** - shell-style variable expansion and substitution
3. **Secure handling** - protection against environment variable injection
4. **Caching** - optional caching of frequently accessed variables

### Integration Points
1. **Platform detection** - leverage existing platform detection utilities
2. **String utilities** - integrate with XIEITE string manipulation functions
3. **File system** - coordinate with file system path utilities
4. **Error reporting** - consistent error handling patterns

## Security Considerations

Environment variable handling involves several security considerations:

### Input Validation
- Validate environment variable names and values
- Prevent injection attacks through environment manipulation
- Handle special characters and encoding properly

### Platform Security
- Respect platform-specific security models
- Consider implications of modifying process environment
- Handle sensitive information appropriately

### Best Practices
- Minimize environment variable modification
- Use secure defaults when variables are unset
- Log environment access for security auditing

## Related Categories

Environment variable utilities would complement these existing XIEITE categories:

- **[Platform Detection](../pp/platform.md)** - Platform-specific conditional compilation
- **[System Queries](./queries.md)** - System information and resource queries
- **[String Utilities](../data/strings.md)** - String manipulation and formatting
- **[File Operations](../io/files.md)** - File system and path utilities

## Future Extensions

Potential future extensions for environment variable utilities:

1. **Configuration Management** - Higher-level configuration file integration
2. **Service Discovery** - Environment-based service configuration
3. **Container Integration** - Docker/Kubernetes environment variable patterns
4. **Shell Integration** - Shell script generation and environment export
5. **Validation Framework** - Schema-based environment variable validation

This documentation will be updated once environment variable utilities are implemented in XIEITE.