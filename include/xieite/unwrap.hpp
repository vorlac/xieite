#pragma once

#include <xieite/concatenate.hpp>

#define XIEITE_UNWRAP(value_) XIEITE_CONCATENATE(XIEITE_DETAIL_UNWRAP_, XIEITE_DETAIL_UNWRAP value_)

#define XIEITE_DETAIL_UNWRAP(...) XIEITE_DETAIL_UNWRAP __VA_ARGS__
#define XIEITE_DETAIL_UNWRAP_XIEITE_DETAIL_UNWRAP
