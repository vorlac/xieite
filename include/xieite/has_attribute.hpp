#pragma once

#include <xieite/compiler.hpp>
#include <xieite/language_standard.hpp>

#if XIEITE_LANGUAGE_STANDARD_CPP_2020
#	define XIEITE_HAS_ATTRIBUTE(...) __has_cpp_attribute(__VA_ARGS__)
#elif XIEITE_LANGUAGE_STANDARD_C_2023
#	define XIEITE_HAS_ATTRIBUTE(...) __has_c_attribute(__VA_ARGS__)
#elif XIEITE_COMPILER_TYPE_GCC || XIEITE_COMPILER_TYPE_CLANG
#	define XIEITE_HAS_ATTRIBUTE(...) __has_attribute(__VA_ARGS__)
#else
#	define XIEITE_HAS_ATTRIBUTE(...) 0
#endif

// Thanks to Ian Pike (https://github.com/Rinzii) for original code
