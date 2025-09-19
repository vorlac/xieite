# CMake Integration

## Overview

XIEITE provides a minimal CMake configuration as a header-only library. The actual CMake setup is documented based on the project's CMakeLists.txt.

## XIEITE's CMake Configuration

### Version Detection System
XIEITE's CMakeLists.txt (lines 4-10) automatically extracts version information from the header file:

```cmake
# CMakeLists.txt:4-10 - Version extraction from pp/ver.hpp
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/pp/ver.hpp" PROJECT_VER_SRC)
string(REGEX MATCH "define [A-Z_]+_MAJOR ([0-9]+)" _ ${PROJECT_VER_SRC})
set(PROJECT_VERSION_MAJOR ${CMAKE_MATCH_1})
string(REGEX MATCH "define [A-Z_]+_MINOR ([0-9]+)" _ ${PROJECT_VER_SRC})
set(PROJECT_VERSION_MINOR ${CMAKE_MATCH_1})
string(REGEX MATCH "define [A-Z_]+_PATCH ([0-9]+)" _ ${PROJECT_VER_SRC})
set(PROJECT_VERSION_PATCH ${CMAKE_MATCH_1})
```

This reads from `include/xieite/pp/ver.hpp:4-6`:
```cpp
#define XIEITE_VER_MAJOR 0
#define XIEITE_VER_MINOR 118
#define XIEITE_VER_PATCH 2
```

### Interface Library Definition
XIEITE is defined as an INTERFACE library (CMakeLists.txt:17-21):

```cmake
# CMakeLists.txt:17 - Interface library (header-only)
add_library(${PROJECT_NAME} INTERFACE)

# CMakeLists.txt:18-21 - Include directory configuration
target_include_directories(
    ${PROJECT_NAME} INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
```

## Integration Methods

### Method 1: Add as Subdirectory
Based on XIEITE's CMakeLists.txt structure:

```cmake
cmake_minimum_required(VERSION 3.25)  # Matches XIEITE requirement (line 1)
project(MyProject CXX)

# Add XIEITE
add_subdirectory(path/to/xieite)

# Link to your target
add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE xieite)
```

### Method 2: Direct Include Path
Since XIEITE only needs its include directory:

```cmake
# Based on CMakeLists.txt:19-20 include directory structure
target_include_directories(my_app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/external/xieite/include
)
```

## Version Compatibility

### Version Checking with XIEITE Macros
Using the version macros from `pp/ver.hpp:7-9`:

```cpp
// pp/ver.hpp:7 - Version comparison macro
#define XIEITE_VER(_cmp, _major, ...) DETAIL_XIEITE_VER(_cmp, _major, __VA_ARGS__ __VA_OPT__(,) 0, 0)

// Example usage in code
#if XIEITE_VER(>=, 0, 118, 0)
    // Code for version 0.118.0 or later
#endif
```

## Minimum Requirements

Based on CMakeLists.txt:1:
- CMake 3.25 or later
- C++ compiler (project uses CXX language at line 14)

## Project Structure

The expected structure based on CMakeLists.txt paths:
```
xieite/
├── CMakeLists.txt
└── include/
    └── xieite/
        ├── pp/
        │   └── ver.hpp    # Version definitions (lines 4-6)
        └── [other headers]
```

## Using XIEITE Headers

After linking with CMake, include XIEITE headers directly:

```cpp
// Headers are available from include/xieite/ directory
#include <xieite/pp/arrow.hpp>
#include <xieite/trait/is_all.hpp>
// etc.
```

## Important Notes

1. **Header-Only**: XIEITE is an INTERFACE library (CMakeLists.txt:17), meaning no compilation is needed
2. **Version Source**: Version is read directly from `pp/ver.hpp` (CMakeLists.txt:4)
3. **Include Path**: The include directory is `${CMAKE_CURRENT_SOURCE_DIR}/include` (CMakeLists.txt:20)
4. **CMake 3.25**: Minimum required version (CMakeLists.txt:1)

## See Also

- CMakeLists.txt (root directory)
- include/xieite/pp/ver.hpp (version macros)