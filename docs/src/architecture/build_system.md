# Build System Integration

## Overview

As a header-only library, XIEITE requires no compilation or linking, making integration straightforward across all major build systems. This document covers integration methods for CMake, manual compilation, package managers, and other build systems.

## CMake Integration

### Basic Setup

The simplest CMake integration defines an interface library:

```cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 3.14)
project(my_project)

# Define XIEITE as an interface library
add_library(xieite INTERFACE)
target_include_directories(xieite INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/xieite/include
)
target_compile_features(xieite INTERFACE cxx_std_23)

# Your target
add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE xieite)
```

### FetchContent Integration

For automatic download and setup:

```cmake
include(FetchContent)

FetchContent_Declare(
    xieite
    GIT_REPOSITORY https://github.com/xieite/xieite.git
    GIT_TAG        main  # or specific version tag
)

FetchContent_MakeAvailable(xieite)

# Use in your targets
target_link_libraries(my_app PRIVATE xieite)
```
