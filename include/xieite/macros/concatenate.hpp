#ifndef XIEITE_HEADER_MACROS_CONCATENATE
#	define XIEITE_HEADER_MACROS_CONCATENATE

#	define XIEITE_CONCATENATE_DIRECT_FORWARD(first, second) first##second

#	define XIEITE_CONCATENATE_DIRECT_REVERSE(first, second) second##first

#	define XIEITE_CONCATENATE(first, second) XIEITE_CONCATENATE_DIRECT_FORWARD(first, second)

#	define XIEITE_CONCATENATE_FIRST(first) XIEITE_CONCATENATE_DIRECT_FORWARD(first,

#	define XIEITE_CONCATENATE_SECOND(second) XIEITE_CONCATENATE_DIRECT_REVERSE(second,

#endif
