#pragma once

#include "../preprocessor/defer.hpp"
#include "../preprocessor/scan.hpp"

#define XIEITE_OBSTRUCT(...) __VA_ARGS__ XIEITE_DEFER(XIEITE_SCAN)()
