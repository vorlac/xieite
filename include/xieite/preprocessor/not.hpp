#pragma once

#include "../preprocessor/check.hpp"
#include "../preprocessor/concatenate.hpp"
#include "../preprocessor/probe.hpp"

#define XIEITE_NOT(value_) XIEITE_CHECK(XIEITE_CONCATENATE_PRIMITIVE(XIEITE_DETAIL_NOT_, value_))

#define XIEITE_DETAIL_NOT_0 XIEITE_PROBE(~)
