#pragma once

#include "../preprocessor/eat.hpp"
#include "../preprocessor/if.hpp"
#include "../preprocessor/scan.hpp"

#define XIEITE_WHEN(value_) XIEITE_IF(value_)(XIEITE_SCAN, XIEITE_EAT)
