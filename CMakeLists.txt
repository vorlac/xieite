cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(compiler_is_msvc "$<CXX_COMPILER_ID:MSVC>")
set(compiler_is_gnu "$<CXX_COMPILER_ID:GNU>")
set(compiler_is_clang "$<OR:$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:Clang>>")

file(GLOB_RECURSE xieite_sources
  CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/xieite.cpp"
)

add_library(xieite)

#set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
set(CMAKE_CXX_MODULE_STD ON)

target_compile_features(xieite
  PRIVATE
    cxx_std_23
  INTERFACE
    cxx_std_20
)

target_compile_definitions(xieite
  INTERFACE
    NOMINMAX
	UNICODE

    $<${compiler_is_msvc}:
        LEAN_AND_MEAN
    >
)

target_compile_options(xieite
  INTERFACE
    $<${compiler_is_msvc}:
        /experimental:module
        /EHsc
        /c
        /std:c++latest
        /utf-8

        #"/reference std=src/std.ifc"
        #/headerUnit
        #/ifcMap
    >

    $<${compiler_is_clang}:
        -march=native
        -fmodules
        -fbuiltin-module-map
        #--precompile

        -Wno-deprecated-declarations
    >

    $<${compiler_is_gnu}:
        -fmodules-ts
        -march=native
    >
)

target_link_options(xieite
  INTERFACE
    $<${compiler_is_clang}:
        #-stdlib=libc++
        #-static-libgcc
        #-static-libc++
    >

    $<${compiler_is_gnu}:
        #-static-libgcc
        #-static-libc++
    >
)

target_include_directories(xieite PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_sources(xieite
  PUBLIC FILE_SET
    CXX_MODULES FILES
      ${xieite_sources}
)
