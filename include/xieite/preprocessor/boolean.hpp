#pragma once

#include "../preprocessor/complement.hpp"
#include "../preprocessor/not.hpp"

#define XIEITE_BOOLEAN(value_) XIEITE_COMPLEMENT(XIEITE_NOT(value_))
