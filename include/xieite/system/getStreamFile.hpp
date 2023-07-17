#ifndef XIEITE_HEADER_SYSTEM_GETSTREAMFILE
#	define XIEITE_HEADER_SYSTEM_GETSTREAMFILE

#	include <xieite/macros/COMPILER_TYPE.hpp>

#	if XIEITE_COMPILER_TYPE_GCC
#		include <cstdio>
#		include <ext/stdio_filebuf.h>
#		include <fstream>
#		include <iostream>
#		include <istream>
#		include <ostream>
#		include <xieite/concepts/SameAsOrDerivedFrom.hpp>

namespace xieite::system {
	template<typename Character = char, xieite::concepts::SameAsOrDerivedFrom<std::basic_istream<Character>, std::basic_ostream<Character>> Stream>
	[[nodiscard]]
	inline std::FILE* getStreamFile(const Stream& stream) noexcept {
		if constexpr (xieite::concepts::SameAsOrDerivedFrom<Stream, std::basic_istream<Character>>) {
			if (&stream == &std::cin) {
				return stdin;
			}
		}
		if constexpr (xieite::concepts::SameAsOrDerivedFrom<Stream, std::basic_ostream<Character>>) {
			if (&stream == &std::cout) {
				return stdout;
			}
			if ((&stream == &std::cerr) || (&stream == &std::clog)) {
				return stderr;
			}
		}
		return static_cast<__gnu_cxx::stdio_filebuf<Character>* const>(static_cast<std::basic_ofstream<Character>::__filebuf_type* const>(stream.rdbuf()))->file();
	}
}

#	else
#		error "Compiler not supported"
#	endif

#endif
