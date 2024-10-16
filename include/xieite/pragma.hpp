#pragma once

#include <xieite/compiler.hpp>
#include <xieite/language_standard.hpp>
#include <xieite/stringify.hpp>

#if XIEITE_LANGUAGE_STANDARD_CPP_2011 || XIEITE_LANGUAGE_STANDARD_C_1999
#	define XIEITE_PRAGMA(...) _Pragma(XIEITE_STRINGIFY(__VA_ARGS__))
#elif XIEITE_COMPILER_TYPE_MSVC
#	define XIEITE_PRAGMA(...) __pragma(__VA_ARGS__)
#else
#	define XIEITE_PRAGMA(...)
#endif
