# Migration Guide

This guide provides step-by-step instructions for migrating between XIEITE versions, handling breaking changes, and updating existing codebases.

## Version Migration Matrix

### From Pre-1.0 to 1.0+

#### Major Breaking Changes

1. **Namespace Reorganization**
2. **Arrow Macro Syntax Changes**
3. **Concept Naming Standardization**
4. **Header File Restructuring**

#### Migration Steps

**Step 1: Update Include Paths**

```cpp
// Old (Pre-1.0)
#include <xieite/arithmetic.hpp>
#include <xieite/traits.hpp>

// New (1.0+)
#include <xieite/trait/is_arith.hpp>
#include <xieite/math/abs.hpp>
```

**Step 2: Update Namespace Usage**

```cpp
// Old
using namespace xieite::traits;
using namespace xieite::math;

// New
using namespace xieite; // All utilities in main namespace

// Or use specific includes
namespace tr = xieite::trait;  // If needed for disambiguation
```

**Step 3: Update Arrow Macro Syntax**

```cpp
// Old syntax
auto func(int x) -> int XIEITE_ARROW(x * 2)

// New syntax
auto func(int x)
XIEITE_ARROW(x * 2)

// Or explicit return type
template<typename T>
auto typed_func(T x) -> T
XIEITE_ARROW(x * 2)
```

### Version 0.x to 1.0 Migration

#### Automated Migration Script

```bash
#!/bin/bash
# migrate_to_1_0.sh - Automated migration helper

# Update include paths
find . -name "*.cpp" -o -name "*.hpp" | xargs sed -i \
    -e 's/#include <xieite\/arithmetic\.hpp>/#include <xieite\/math\/abs.hpp>/g' \
    -e 's/#include <xieite\/traits\.hpp>/#include <xieite\/trait\/is_arith.hpp>/g' \
    -e 's/xieite::traits::/xieite::/g' \
    -e 's/xieite::math::/xieite::/g'

# Update arrow macro syntax
find . -name "*.cpp" -o -name "*.hpp" | xargs sed -i \
    's/-> [^{]*XIEITE_ARROW(/XIEITE_ARROW(/g'

echo "Migration complete. Please review changes and test thoroughly."
```

#### Manual Migration Checklist

- [ ] Update all include paths to new header structure
- [ ] Remove redundant namespace qualifiers
- [ ] Update arrow macro syntax
- [ ] Replace deprecated concepts with new names
- [ ] Update CMake files to reference new header paths
- [ ] Run comprehensive tests after migration

## Version-Specific Migration Guides

### 0.118.x to 1.0.0

#### Header Reorganization

**Math Headers**:
```cpp
// Old
#include <xieite/abs.hpp>
#include <xieite/min_max.hpp>

// New
#include <xieite/math/abs.hpp>
#include <xieite/math/min.hpp>
#include <xieite/math/max.hpp>
```

**Trait Headers**:
```cpp
// Old
#include <xieite/is_arithmetic.hpp>
#include <xieite/type_traits.hpp>

// New
#include <xieite/trait/is_arith.hpp>
#include <xieite/trait/can_alias.hpp>
```

**Preprocessor Headers**:
```cpp
// Old
#include <xieite/platform_detection.hpp>
#include <xieite/conditional.hpp>

// New
#include <xieite/pp/platform.hpp>
#include <xieite/pp/if.hpp>
```

#### Concept Renaming

```cpp
// Old concept names
template<xieite::Arithmetic T>          // PascalCase
template<xieite::IsContainer T>

// New concept names
template<xieite::is_arith T>           // snake_case
template<xieite::is_container T>
```

#### Function Signature Changes

```cpp
// Old
template<typename T>
requires xieite::ArithmeticType<T>
auto square(T value) -> T;

// New
template<xieite::is_arith T>
auto square(T value) -> T;

// Or using arrow macro
template<xieite::is_arith T>
auto square(T value)
XIEITE_ARROW(value * value)
```

### 1.0.x to 1.1.0

#### New Features Integration

**Enhanced Error Handling**:
```cpp
// New scope guard syntax (if applicable)
#include <xieite/fn/scope_guard.hpp>

// Old pattern
{
    resource_type* res = acquire_resource();
    // ... use resource
    release_resource(res);
}

// New pattern
{
    auto res = acquire_resource();
    auto guard = xieite::scope_guard([res] { release_resource(res); });
    // ... use resource - automatic cleanup
}
```

**Platform Detection Enhancements**:
```cpp
// New architecture detection
#include <xieite/pp/arch.hpp>

XIEITE_PP_IF(XIEITE_ARCH_ARM64)(
    // ARM64-specific optimizations
)
```

## Breaking Changes by Category

### Preprocessor Utilities

#### Arrow Macros (v0.x → 1.0)

```cpp
// Old - required explicit return type
auto func(int x) -> int XIEITE_ARROW(x + 1)

// New - return type deduction
auto func(int x)
XIEITE_ARROW(x + 1)

// Migration pattern
#define OLD_STYLE_ARROW(ret_type, expr) \
    XIEITE_ARROW(expr)

// Usage during transition
auto func(int x) OLD_STYLE_ARROW(int, x + 1)
```

#### Platform Detection (v0.x → 1.0)

```cpp
// Old
#ifdef XIEITE_WINDOWS
    // Windows code
#endif

// New
#include <xieite/pp/platform.hpp>
XIEITE_PP_IF(XIEITE_PLATFORM_WINDOWS)(
    // Windows code
)
```

### Type Traits and Concepts

#### Concept Naming (v0.x → 1.0)

```cpp
// Create compatibility aliases during migration
namespace xieite {
    // Compatibility aliases for old names
    template<typename T>
    concept Arithmetic = is_arith<T>;

    template<typename T>
    concept Container = is_container<T>;
}

// Gradually replace with new names
template<xieite::is_arith T>  // Preferred
// template<xieite::Arithmetic T>  // Deprecated but works
auto process(T value) { /* implementation */ }
```

#### SFINAE to Concepts (v0.x → 1.0)

```cpp
// Old SFINAE approach
template<typename T>
auto process(T value)
    -> std::enable_if_t<std::is_arithmetic_v<T>, T> {
    return value * 2;
}

// New concept approach
template<xieite::is_arith T>
auto process(T value) -> T {
    return value * 2;
}

// Or with arrow macro
template<xieite::is_arith T>
auto process(T value)
XIEITE_ARROW(value * 2)
```

### Mathematical Utilities

#### Function Signatures (v0.x → 1.0)

```cpp
// Old - separate headers and functions
#include <xieite/absolute.hpp>
#include <xieite/minimum.hpp>

auto a = xieite::absolute(-5);
auto m = xieite::minimum(a, b);

// New - unified naming and headers
#include <xieite/math/abs.hpp>
#include <xieite/math/min.hpp>

auto a = xieite::abs(-5);
auto m = xieite::min(a, b);
```


## Migration Strategies

### Gradual Migration Approach

**Phase 1: Compatibility Layer**
```cpp
// Create compatibility header
// compat/xieite_compat.hpp
#pragma once

#include <xieite/trait/is_arith.hpp>
#include <xieite/math/abs.hpp>

namespace xieite {
    // Old naming compatibility
    template<typename T>
    concept Arithmetic = is_arith<T>;

    template<typename T>
    auto absolute(T value) { return abs(value); }
}
```

**Phase 2: Update Incrementally**
```cpp
// Update one module at a time
// Module A - updated to new syntax
#include <xieite/trait/is_arith.hpp>
template<xieite::is_arith T>
auto func_a(T value) { return value; }

// Module B - still using compatibility
#include "compat/xieite_compat.hpp"
template<xieite::Arithmetic T>
auto func_b(T value) { return value; }
```

**Phase 3: Remove Compatibility**
```cpp
// Remove compatibility layer after full migration
// All modules now use new syntax
#include <xieite/trait/is_arith.hpp>
template<xieite::is_arith T>
auto unified_func(T value) { return value; }
```

### Automated Migration Tools

#### CMake Migration Helper

```cmake
# migrate_headers.cmake
function(migrate_xieite_headers target_dir)
    file(GLOB_RECURSE source_files
         "${target_dir}/*.cpp"
         "${target_dir}/*.hpp")

    foreach(file ${source_files})
        # Read file content
        file(READ ${file} content)

        # Apply transformations
        string(REGEX REPLACE
               "#include <xieite/arithmetic\\.hpp>"
               "#include <xieite/math/abs.hpp>\n#include <xieite/trait/is_arith.hpp>"
               content "${content}")

        string(REGEX REPLACE
               "xieite::Arithmetic"
               "xieite::is_arith"
               content "${content}")

        # Write back
        file(WRITE ${file} "${content}")
    endforeach()
endfunction()

# Usage: migrate_xieite_headers(${CMAKE_SOURCE_DIR}/src)
```

#### Python Migration Script

```python
#!/usr/bin/env python3
"""
XIEITE Migration Script
Automatically updates source files from old to new XIEITE syntax
"""

import re
import os
import argparse
from pathlib import Path

class XieiteMigrator:
    def __init__(self):
        self.transformations = [
            # Header updates
            (r'#include <xieite/arithmetic\.hpp>',
             r'#include <xieite/math/abs.hpp>\n#include <xieite/trait/is_arith.hpp>'),
            (r'#include <xieite/traits\.hpp>',
             r'#include <xieite/trait/is_arith.hpp>'),

            # Concept renames
            (r'xieite::Arithmetic', r'xieite::is_arith'),
            (r'xieite::Container', r'xieite::is_container'),

            # Function renames
            (r'xieite::absolute\(', r'xieite::abs('),
            (r'xieite::minimum\(', r'xieite::min('),
            (r'xieite::maximum\(', r'xieite::max('),

            # Arrow macro syntax
            (r'-> [^{]*XIEITE_ARROW\(', r'XIEITE_ARROW('),
        ]

    def migrate_file(self, filepath):
        """Migrate a single file"""
        with open(filepath, 'r') as f:
            content = f.read()

        original_content = content
        for pattern, replacement in self.transformations:
            content = re.sub(pattern, replacement, content)

        if content != original_content:
            with open(filepath, 'w') as f:
                f.write(content)
            return True
        return False

    def migrate_directory(self, directory):
        """Migrate all files in directory recursively"""
        changed_files = []
        for ext in ['*.cpp', '*.hpp', '*.cc', '*.h']:
            for filepath in Path(directory).rglob(ext):
                if self.migrate_file(filepath):
                    changed_files.append(filepath)
        return changed_files

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Migrate XIEITE code to new version')
    parser.add_argument('directory', help='Directory to migrate')
    args = parser.parse_args()

    migrator = XieiteMigrator()
    changed_files = migrator.migrate_directory(args.directory)

    print(f"Migration complete. Changed {len(changed_files)} files:")
    for file in changed_files:
        print(f"  {file}")
```

## Testing Migration

### Validation Checklist

After migration, ensure:

- [ ] All files compile without errors
- [ ] Unit tests pass
- [ ] No performance regressions
- [ ] Cross-platform compatibility maintained
- [ ] Documentation updated
- [ ] CI/CD pipelines updated

### Regression Testing

```cpp
// Create regression tests for migration
#include <xieite/trait/is_arith.hpp>
#include <xieite/math/abs.hpp>

namespace migration_tests {
    // Test old functionality still works with new syntax
    template<xieite::is_arith T>
    void test_arithmetic_concept() {
        static_assert(xieite::is_arith<int>);
        static_assert(xieite::is_arith<double>);
        static_assert(!xieite::is_arith<std::string>);
    }

    void test_abs_function() {
        assert(xieite::abs(-5) == 5);
        assert(xieite::abs(3.14) == 3.14);
        assert(xieite::abs(-3.14) == 3.14);
    }

    void run_all_migration_tests() {
        test_arithmetic_concept<int>();
        test_abs_function();
        // Add more tests as needed
    }
}
```

## Common Migration Issues

### Issue: Include Path Not Found

**Problem**: `fatal error: 'xieite/arithmetic.hpp' file not found`

**Solution**: Update include paths and check header reorganization map.

### Issue: Concept Not Recognized

**Problem**: `error: 'Arithmetic' is not a member of 'xieite'`

**Solution**: Update concept names to snake_case and ensure proper headers are included.

### Issue: Arrow Macro Syntax Error

**Problem**: `error: expected ';' after expression`

**Solution**: Update arrow macro syntax to remove explicit return type.

### Issue: Compilation Performance

**Problem**: Significantly slower compilation after migration

**Solution**: Check for unnecessary header includes and use forward declarations where possible.

## Best Practices for Future Migrations

1. **Version Pinning**: Pin XIEITE version in build systems
2. **Automated Testing**: Maintain comprehensive test coverage
3. **Gradual Updates**: Update one module at a time
4. **Documentation**: Keep migration notes for team reference
5. **Backup**: Always backup code before major migrations

This migration guide ensures smooth transitions between XIEITE versions while maintaining code quality and functionality.