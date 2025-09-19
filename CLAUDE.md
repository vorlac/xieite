# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

XIEITE is a modern C++ utility library consisting of 616 header files organized into 8 categories:
- **data**: Data structures and containers
- **fn**: Functional programming utilities
- **io**: Input/output utilities
- **math**: Mathematical functions and constants
- **meta**: Template metaprogramming utilities
- **pp**: Preprocessor utilities
- **sys**: System-level utilities
- **trait**: Type traits and concepts

This is a header-only library designed for C++20 with emphasis on template metaprogramming, cross-platform compatibility, and modern C++ features.

## Build Commands

This is a header-only library, so no compilation is needed. To use XIEITE in your project:

### With CMake:
```bash
# Configure the project
cmake -B build

# Install headers (optional)
cmake --install build
```

### Manual Integration:
Simply add the include directory to your compiler's include path:
```bash
g++ -std=c++20 -I/path/to/xieite/include your_file.cpp
```

## Code Architecture

### Directory Structure
```
include/xieite/
├── data/    # Data structures (e.g., is_ordinal_numeric.hpp, is_spec.hpp)
├── fn/      # Functional utilities (e.g., apply_until.hpp, curry.hpp)
├── io/      # I/O utilities (e.g., scan.hpp, read.hpp)
├── math/    # Math functions (e.g., diff.hpp, round_toward.hpp)
├── meta/    # Metaprogramming (e.g., repeat_to_digs.hpp, try_subst.hpp)
├── pp/      # Preprocessor utilities (e.g., toggle.hpp, ver_guard.hpp)
├── sys/     # System utilities (e.g., get_env.hpp, os.hpp)
└── trait/   # Type traits (e.g., can_alias.hpp, is_stdmem_func_ptr.hpp)
```

### Key Design Patterns

1. **Arrow Macro System**: The library uses custom macros for concise function definitions:
   - `XIEITE_ARROW(expr)` - Auto-deduces return type and noexcept
   - `XIEITE_ARROW_NOEX(expr)` - Forces noexcept(true)
   - Located in `include/xieite/pp/arrow.hpp`

2. **Concept-Heavy Design**: Extensive use of C++20 concepts for compile-time validation
   - Most traits are implemented as concepts
   - Static assertions validate template parameters

3. **Cross-Platform Support**: Platform detection and conditional compilation
   - OS detection macros in `include/xieite/sys/os.hpp`
   - Architecture detection in `include/xieite/sys/arch.hpp`

4. **Version Detection**: Automatic version parsing from header files
   - Version info in `include/xieite/xieite.hpp`
   - Current version: 0.118.2

### Important Implementation Details

- **Header Guards**: All headers use `XIEITE_HEADER_<CATEGORY>_<NAME>` pattern
- **Namespace**: Everything is in the `xieite` namespace
- **No External Dependencies**: Library is self-contained
- **Template-Heavy**: Most utilities are template functions/classes
- **Compile-Time Focus**: Heavy use of constexpr and consteval

## Development Workflow

### Adding New Utilities
1. Place header in appropriate category directory
2. Use consistent header guard naming: `XIEITE_HEADER_<CATEGORY>_<NAME>`
3. Implement within `xieite` namespace
4. Use arrow macros for simple function definitions
5. Add appropriate concepts/constraints for template parameters

### Code Style
- Use trailing return types with arrow macros
- Prefer concepts over SFINAE
- Make functions constexpr/consteval when possible
- Use [[nodiscard]] for non-void returns
- Follow existing naming conventions (snake_case for functions/variables)

### Testing
No integrated test suite found. Testing approach:
- Rely on static_assert for compile-time validation
- Use concepts to catch errors at instantiation
- External testing in separate projects

## Common Tasks

### Finding Utilities
```bash
# Find all headers in a category
ls include/xieite/math/*.hpp

# Search for specific functionality
grep -r "concept" include/xieite/trait/
```

### Using the Library
```cpp
#include <xieite/math/diff.hpp>
#include <xieite/fn/curry.hpp>

// Use utilities from xieite namespace
auto result = xieite::diff(10, 5);
```