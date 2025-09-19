# Build Configurations

This document covers advanced build configuration strategies for XIEITE-based projects, including CMake integration, compiler flags, optimization settings, and cross-platform build management.

## CMake Integration

### Basic XIEITE Setup

Setting up XIEITE in a CMake project:

```cmake
# CMakeLists.txt for XIEITE-based project
cmake_minimum_required(VERSION 3.20)
project(xieite_project VERSION 1.0.0 LANGUAGES CXX)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find XIEITE
find_package(xieite REQUIRED)

# Create target
add_executable(myapp main.cpp)

# Link XIEITE (header-only)
target_link_libraries(myapp PRIVATE xieite::xieite)

# Alternative: Add include directory directly
# target_include_directories(myapp PRIVATE "${CMAKE_SOURCE_DIR}/third_party/xieite/include")
```

### Advanced CMake Configuration

Comprehensive build configuration with feature detection:

```cmake
# Advanced CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(advanced_xieite_project
    VERSION 1.0.0
    LANGUAGES CXX
    DESCRIPTION "Advanced XIEITE-based application"
)

# Build type configuration
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Platform detection
if(WIN32)
    set(XIEITE_PLATFORM_WINDOWS TRUE)
elseif(APPLE)
    set(XIEITE_PLATFORM_MACOS TRUE)
elseif(UNIX)
    set(XIEITE_PLATFORM_UNIX TRUE)
endif()

# Architecture detection
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
    set(XIEITE_ARCH_X86_64 TRUE)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64")
    set(XIEITE_ARCH_ARM64 TRUE)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
    set(XIEITE_ARCH_ARM32 TRUE)
endif()

# Compiler detection
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(XIEITE_COMPILER_GCC TRUE)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(XIEITE_COMPILER_CLANG TRUE)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(XIEITE_COMPILER_MSVC TRUE)
endif()

# Feature detection
include(CheckCXXFeature)
check_cxx_feature(cxx_concepts CONCEPTS_SUPPORT)
check_cxx_feature(cxx_modules MODULES_SUPPORT)

# Configuration options
option(XIEITE_ENABLE_SIMD "Enable SIMD optimizations" ON)
option(XIEITE_ENABLE_TESTING "Enable testing" ON)
option(XIEITE_ENABLE_BENCHMARKS "Enable benchmarks" OFF)
option(XIEITE_STRICT_WARNINGS "Enable strict warnings" ON)

# Create configuration header
configure_file(
    "${CMAKE_SOURCE_DIR}/config.h.in"
    "${CMAKE_BINARY_DIR}/include/config.h"
    @ONLY
)

# XIEITE library target
add_library(xieite INTERFACE)

target_include_directories(xieite INTERFACE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(xieite INTERFACE cxx_std_20)

# Platform-specific compile definitions
if(XIEITE_PLATFORM_WINDOWS)
    target_compile_definitions(xieite INTERFACE XIEITE_PLATFORM_WINDOWS=1)
elseif(XIEITE_PLATFORM_MACOS)
    target_compile_definitions(xieite INTERFACE XIEITE_PLATFORM_MACOS=1)
elseif(XIEITE_PLATFORM_UNIX)
    target_compile_definitions(xieite INTERFACE XIEITE_PLATFORM_UNIX=1)
endif()

# Architecture-specific definitions
if(XIEITE_ARCH_X86_64)
    target_compile_definitions(xieite INTERFACE XIEITE_ARCH_X86_64=1)
elseif(XIEITE_ARCH_ARM64)
    target_compile_definitions(xieite INTERFACE XIEITE_ARCH_ARM64=1)
elseif(XIEITE_ARCH_ARM32)
    target_compile_definitions(xieite INTERFACE XIEITE_ARCH_ARM32=1)
endif()

# Compiler-specific definitions
if(XIEITE_COMPILER_GCC)
    target_compile_definitions(xieite INTERFACE XIEITE_COMPILER_GCC=1)
elseif(XIEITE_COMPILER_CLANG)
    target_compile_definitions(xieite INTERFACE XIEITE_COMPILER_CLANG=1)
elseif(XIEITE_COMPILER_MSVC)
    target_compile_definitions(xieite INTERFACE XIEITE_COMPILER_MSVC=1)
endif()

# SIMD support
if(XIEITE_ENABLE_SIMD)
    if(XIEITE_ARCH_X86_64)
        target_compile_definitions(xieite INTERFACE XIEITE_ENABLE_SSE=1)
        if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
            target_compile_options(xieite INTERFACE /arch:AVX2)
        else()
            target_compile_options(xieite INTERFACE -mavx2 -mfma)
        endif()
    elseif(XIEITE_ARCH_ARM64)
        target_compile_definitions(xieite INTERFACE XIEITE_ENABLE_NEON=1)
    endif()
endif()
```

### Configuration Header Template

config.h.in template for compile-time configuration:

```c
// config.h.in - Configuration header template
#ifndef XIEITE_CONFIG_H
#define XIEITE_CONFIG_H

// Version information
#define XIEITE_VERSION_MAJOR @PROJECT_VERSION_MAJOR@
#define XIEITE_VERSION_MINOR @PROJECT_VERSION_MINOR@
#define XIEITE_VERSION_PATCH @PROJECT_VERSION_PATCH@
#define XIEITE_VERSION_STRING "@PROJECT_VERSION@"

// Platform detection
#cmakedefine XIEITE_PLATFORM_WINDOWS
#cmakedefine XIEITE_PLATFORM_MACOS
#cmakedefine XIEITE_PLATFORM_UNIX

// Architecture detection
#cmakedefine XIEITE_ARCH_X86_64
#cmakedefine XIEITE_ARCH_ARM64
#cmakedefine XIEITE_ARCH_ARM32

// Compiler detection
#cmakedefine XIEITE_COMPILER_GCC
#cmakedefine XIEITE_COMPILER_CLANG
#cmakedefine XIEITE_COMPILER_MSVC

// Feature support
#cmakedefine CONCEPTS_SUPPORT
#cmakedefine MODULES_SUPPORT

// Build options
#cmakedefine XIEITE_ENABLE_SIMD
#cmakedefine XIEITE_ENABLE_SSE
#cmakedefine XIEITE_ENABLE_NEON

// Debug/Release configuration
#ifdef CMAKE_BUILD_TYPE
    #if "${CMAKE_BUILD_TYPE}" STREQUAL "Debug"
        #define XIEITE_DEBUG_BUILD 1
    #else
        #define XIEITE_RELEASE_BUILD 1
    #endif
#endif

#endif // XIEITE_CONFIG_H
```

## Compiler-Specific Build Configurations

### GCC Configuration

Optimized GCC build settings:

```cmake
# GCC-specific configuration
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Version-specific flags
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "11.0")
        target_compile_options(xieite INTERFACE
            $<$<CONFIG:Debug>:-O0 -g3 -fno-omit-frame-pointer>
            $<$<CONFIG:Release>:-O3 -DNDEBUG -march=native>
            $<$<CONFIG:RelWithDebInfo>:-O2 -g -DNDEBUG>
            $<$<CONFIG:MinSizeRel>:-Os -DNDEBUG>
        )
    endif()

    # Warning flags
    if(XIEITE_STRICT_WARNINGS)
        target_compile_options(xieite INTERFACE
            -Wall -Wextra -Wpedantic
            -Wcast-align -Wcast-qual
            -Wconversion -Wsign-conversion
            -Wduplicated-cond -Wduplicated-branches
            -Wlogical-op -Wrestrict
            -Wnull-dereference -Wuseless-cast
            -Wdouble-promotion -Wformat=2
        )
    endif()

    # LTO support
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        set_property(TARGET xieite PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
    endif()

    # Sanitizer support
    option(XIEITE_ENABLE_ASAN "Enable AddressSanitizer" OFF)
    option(XIEITE_ENABLE_UBSAN "Enable UndefinedBehaviorSanitizer" OFF)
    option(XIEITE_ENABLE_TSAN "Enable ThreadSanitizer" OFF)

    if(XIEITE_ENABLE_ASAN)
        target_compile_options(xieite INTERFACE -fsanitize=address)
        target_link_options(xieite INTERFACE -fsanitize=address)
    endif()

    if(XIEITE_ENABLE_UBSAN)
        target_compile_options(xieite INTERFACE -fsanitize=undefined)
        target_link_options(xieite INTERFACE -fsanitize=undefined)
    endif()

    if(XIEITE_ENABLE_TSAN)
        target_compile_options(xieite INTERFACE -fsanitize=thread)
        target_link_options(xieite INTERFACE -fsanitize=thread)
    endif()
endif()
```

### Clang Configuration

Clang-specific optimization settings:

```cmake
# Clang-specific configuration
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # Optimization flags
    target_compile_options(xieite INTERFACE
        $<$<CONFIG:Debug>:-O0 -g -fno-omit-frame-pointer>
        $<$<CONFIG:Release>:-O3 -DNDEBUG -march=native>
        $<$<CONFIG:RelWithDebInfo>:-O2 -g -DNDEBUG>
        $<$<CONFIG:MinSizeRel>:-Oz -DNDEBUG>
    )

    # Clang-specific warnings
    if(XIEITE_STRICT_WARNINGS)
        target_compile_options(xieite INTERFACE
            -Wall -Wextra -Wpedantic
            -Wcast-align -Wcast-qual
            -Wconversion -Wsign-conversion
            -Wloop-analysis -Wshift-overflow
            -Wstring-conversion -Wtautological-overlap-compare
            -Wunused-exception-parameter -Wvla
        )
    endif()

    # Profile-guided optimization
    option(XIEITE_ENABLE_PGO "Enable Profile-Guided Optimization" OFF)
    if(XIEITE_ENABLE_PGO)
        target_compile_options(xieite INTERFACE -fprofile-generate)
        target_link_options(xieite INTERFACE -fprofile-generate)
    endif()

    # Code coverage
    option(XIEITE_ENABLE_COVERAGE "Enable code coverage" OFF)
    if(XIEITE_ENABLE_COVERAGE)
        target_compile_options(xieite INTERFACE --coverage)
        target_link_options(xieite INTERFACE --coverage)
    endif()
endif()
```

### MSVC Configuration

MSVC-specific build settings:

```cmake
# MSVC-specific configuration
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # Optimization flags
    target_compile_options(xieite INTERFACE
        $<$<CONFIG:Debug>:/Od /Zi /RTC1>
        $<$<CONFIG:Release>:/O2 /Oi /DNDEBUG>
        $<$<CONFIG:RelWithDebInfo>:/O2 /Zi /DNDEBUG>
        $<$<CONFIG:MinSizeRel>:/O1 /DNDEBUG>
    )

    # Warning configuration
    if(XIEITE_STRICT_WARNINGS)
        target_compile_options(xieite INTERFACE
            /W4
            /w14242 /w14254 /w14263 /w14265 /w14287
            /w14296 /w14311 /w14545 /w14546 /w14547
            /w14549 /w14555 /w14619 /w14640 /w14826
            /w14905 /w14906 /w14928
        )
    endif()

    # Disable specific warnings
    target_compile_options(xieite INTERFACE
        /wd4068  # Unknown pragma
        /wd4996  # Deprecated functions
    )

    # Runtime library configuration
    set_property(TARGET xieite PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

    # Enable parallel compilation
    target_compile_options(xieite INTERFACE /MP)

    # Enhanced security features
    target_compile_definitions(xieite INTERFACE
        _CRT_SECURE_NO_WARNINGS
        _SCL_SECURE_NO_WARNINGS
    )
endif()
```

## Advanced Build Features

### Profile-Guided Optimization (PGO)

Setting up PGO builds:

```cmake
# PGO configuration
function(setup_pgo target)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        # Two-stage PGO build
        add_custom_target(${target}_pgo_generate
            COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Release
                    -DXIEITE_PGO_GENERATE=ON
                    -B ${CMAKE_BINARY_DIR}/pgo_generate
                    -S ${CMAKE_SOURCE_DIR}
            COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/pgo_generate
            COMMENT "Building PGO instrumented version"
        )

        add_custom_target(${target}_pgo_use
            COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Release
                    -DXIEITE_PGO_USE=ON
                    -B ${CMAKE_BINARY_DIR}/pgo_use
                    -S ${CMAKE_SOURCE_DIR}
            COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}/pgo_use
            DEPENDS ${target}_pgo_generate
            COMMENT "Building PGO optimized version"
        )
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        # MSVC PGO configuration
        target_link_options(${target} PRIVATE
            $<$<BOOL:${XIEITE_PGO_GENERATE}>:/GENPROFILE>
            $<$<BOOL:${XIEITE_PGO_USE}>:/USEPROFILE>
        )
    endif()
endfunction()
```

### Link-Time Optimization (LTO)

Advanced LTO configuration:

```cmake
# LTO configuration
function(setup_lto target)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT lto_supported OUTPUT lto_error)

    if(lto_supported)
        set_property(TARGET ${target} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)

        if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            target_compile_options(${target} PRIVATE -flto=auto)
            target_link_options(${target} PRIVATE -flto=auto)
        elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
            target_compile_options(${target} PRIVATE -flto=thin)
            target_link_options(${target} PRIVATE -flto=thin)
        endif()
    else()
        message(WARNING "LTO not supported: ${lto_error}")
    endif()
endfunction()
```

### Build Caching

Setting up build caching with ccache:

```cmake
# ccache configuration
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    option(XIEITE_USE_CCACHE "Use ccache for compilation" ON)
    if(XIEITE_USE_CCACHE)
        set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
        set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
        message(STATUS "Using ccache: ${CCACHE_PROGRAM}")
    endif()
endif()

# Ninja build configuration
if(CMAKE_GENERATOR STREQUAL "Ninja")
    set_property(GLOBAL PROPERTY JOB_POOLS compile=4 link=2)
    set(CMAKE_JOB_POOL_COMPILE compile)
    set(CMAKE_JOB_POOL_LINK link)
endif()
```

## Testing and Validation

### Test Configuration

Comprehensive test setup:

```cmake
# Testing configuration
if(XIEITE_ENABLE_TESTING)
    enable_testing()
    find_package(Catch2 REQUIRED)

    # Test executable
    add_executable(xieite_tests
        tests/main.cpp
        tests/test_arithmetic.cpp
        tests/test_traits.cpp
        tests/test_meta.cpp
    )

    target_link_libraries(xieite_tests PRIVATE
        xieite
        Catch2::Catch2WithMain
    )

    # Test discovery
    include(CTest)
    include(Catch)
    catch_discover_tests(xieite_tests)

    # Coverage reporting
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        option(XIEITE_ENABLE_COVERAGE "Enable coverage reporting" OFF)
        if(XIEITE_ENABLE_COVERAGE)
            target_compile_options(xieite_tests PRIVATE --coverage)
            target_link_options(xieite_tests PRIVATE --coverage)

            find_program(GCOVR_PROGRAM gcovr)
            if(GCOVR_PROGRAM)
                add_custom_target(coverage
                    COMMAND ${GCOVR_PROGRAM} --root=${CMAKE_SOURCE_DIR}
                            --exclude=${CMAKE_SOURCE_DIR}/tests
                            --html --html-details
                            --output=${CMAKE_BINARY_DIR}/coverage.html
                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                    COMMENT "Generating coverage report"
                )
            endif()
        endif()
    endif()
endif()
```

### Benchmark Configuration

Performance testing setup:

```cmake
# Benchmark configuration
if(XIEITE_ENABLE_BENCHMARKS)
    find_package(benchmark REQUIRED)

    add_executable(xieite_benchmarks
        benchmarks/main.cpp
        benchmarks/bench_arithmetic.cpp
        benchmarks/bench_meta.cpp
    )

    target_link_libraries(xieite_benchmarks PRIVATE
        xieite
        benchmark::benchmark
    )

    # Optimization for benchmarks
    target_compile_options(xieite_benchmarks PRIVATE
        $<$<CXX_COMPILER_ID:GNU>:-O3 -march=native -DNDEBUG>
        $<$<CXX_COMPILER_ID:Clang>:-O3 -march=native -DNDEBUG>
        $<$<CXX_COMPILER_ID:MSVC>:/O2 /DNDEBUG>
    )
endif()
```

## Continuous Integration

### GitHub Actions Configuration

CI pipeline configuration:

```yaml
# .github/workflows/ci.yml
name: CI

on:
  push:
    branches: [ main, develop ]
  pull_request:
    branches: [ main ]

jobs:
  test:
    strategy:
      matrix:
        os: [ubuntu-latest, windows-latest, macos-latest]
        compiler: [gcc, clang, msvc]
        config: [Debug, Release]
        exclude:
          - os: windows-latest
            compiler: gcc
          - os: windows-latest
            compiler: clang
          - os: ubuntu-latest
            compiler: msvc
          - os: macos-latest
            compiler: msvc

    runs-on: ${{ matrix.os }}

    steps:
    - uses: actions/checkout@v3

    - name: Setup compiler
      if: matrix.compiler == 'gcc'
      run: |
        sudo apt-get update
        sudo apt-get install -y gcc-11 g++-11
        echo "CC=gcc-11" >> $GITHUB_ENV
        echo "CXX=g++-11" >> $GITHUB_ENV

    - name: Configure CMake
      run: |
        cmake -B build \
              -DCMAKE_BUILD_TYPE=${{ matrix.config }} \
              -DXIEITE_ENABLE_TESTING=ON \
              -DXIEITE_STRICT_WARNINGS=ON

    - name: Build
      run: cmake --build build --config ${{ matrix.config }}

    - name: Test
      run: ctest --test-dir build --config ${{ matrix.config }} --output-on-failure
```

## Installation and Packaging

### CMake Package Configuration

Setting up XIEITE for distribution:

```cmake
# Installation configuration
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Install headers
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hpp"
)

# Generate package configuration
configure_package_config_file(
    "${CMAKE_SOURCE_DIR}/cmake/xieiteConfig.cmake.in"
    "${CMAKE_BINARY_DIR}/xieiteConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/xieite
)

write_basic_package_version_file(
    "${CMAKE_BINARY_DIR}/xieiteConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Install CMake files
install(FILES
    "${CMAKE_BINARY_DIR}/xieiteConfig.cmake"
    "${CMAKE_BINARY_DIR}/xieiteConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/xieite
)

# Export targets
install(TARGETS xieite
    EXPORT xieiteTargets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT xieiteTargets
    FILE xieiteTargets.cmake
    NAMESPACE xieite::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/xieite
)

# CPack configuration
set(CPACK_PACKAGE_VENDOR "XIEITE Project")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Modern C++ utility library")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")

include(CPack)
```

This comprehensive build configuration approach ensures XIEITE-based projects are built efficiently across different platforms and toolchains while maintaining high code quality and performance.