module;

#include <cstdio>
#include <iostream>
#include <string>

#include <xieite/compiler.hpp>
#include <xieite/platform.hpp>

#if XIEITE_PLATFORM_TYPE_UNIX
  #include <fcntl.h>
  #include <unistd.h>
#elif !XIEITE_PLATFORM_TYPE_WINDOWS
  #warning "unsupported platform"
#endif

#if XIEITE_COMPILER_TYPE_GCC
  #include <ext/stdio_filebuf.h>
#endif

export module xieite:streams.File;

import :concepts.InputStream;
import :concepts.OutputStream;
import :concepts.Stream;

export namespace xieite::streams {
    struct File {
    public:
        File(std::FILE* const stream = nullptr) noexcept
            : stream(stream) {
        }

        File(const std::string& path, const std::string& mode) noexcept {
            this->open(path, mode);
        }

#if XIEITE_PLATFORM_TYPE_WINDOWS
        File(const std::wstring& path, const std::wstring& mode) noexcept {
            this->open(path, mode);
        }
#endif

        File(const int descriptor, const std::string& mode) noexcept {
            this->open(descriptor, mode);
        }

#if XIEITE_PLATFORM_TYPE_WINDOWS
        File(const int descriptor, const std::wstring& mode) noexcept {
            this->open(descriptor, mode);
        }
#endif

        template <xieite::concepts::Stream Stream>
        File(Stream& stream) noexcept {
            this->open(stream);
        }

        File(const std::string& path, const std::string& mode, const File other) noexcept {
            this->reopen(path, mode, other);
        }

#if XIEITE_PLATFORM_TYPE_WINDOWS
        File(const std::wstring& path, const std::wstring& mode, const File other) noexcept {
            this->reopen(path, mode, other);
        }
#endif

        ~File() {
            this->close();
        }

        void open(const std::string& path, const std::string& mode) noexcept {
            this->stream = std::fopen(path.c_str(), mode.c_str());
        }

#if XIEITE_PLATFORM_TYPE_WINDOWS
        void open(const std::wstring& path, const std::wstring& mode) noexcept {
            this->stream = ::_wfopen(path.c_str(), mode.c_str());
        }
#endif

        void open(const int descriptor, const std::string& mode) noexcept {
#if XIEITE_PLATFORM_TYPE_WINDOWS
            this->stream = ::_fdopen(descriptor, mode.c_str());
#else
            this->stream = ::fdopen(descriptor, mode.c_str());
#endif
        }

#if XIEITE_PLATFORM_TYPE_WINDOWS
        void open(const int descriptor, const std::wstring& mode) noexcept {
            this->stream = ::_wfdopen(descriptor, mode.c_str());
        }
#endif

        template <xieite::concepts::Stream Stream>
        void open(Stream& stream) noexcept {
            this->stream = ([&stream] {
                constexpr static bool isInput = xieite::concepts::InputStream<Stream>;
                constexpr static bool isOutput = xieite::concepts::OutputStream<Stream>;
                const Stream* address = std::addressof(stream);
                if constexpr (isInput) {
                    if (address == std::addressof(std::cin)) {
                        return stdin;
                    }
                }
                else if constexpr (isOutput) {
                    if (address == std::addressof(std::cout)) {
                        return stdout;
                    }
                    if ((address == std::addressof(std::cerr)) || (address == std::addressof(std::clog))) {
                        return stderr;
                    }
                }
                if constexpr (requires { stream.native_handle(); }) {
                    const typename Stream::native_handle_type descriptor = stream.native_handle();
                    std::string mode;
                    mode.reserve(3);
                    if constexpr (isInput) {
                        mode += 'r';
                    }
                    if constexpr (isOutput) {
                        mode += 'w';
                    }
#if XIEITE_PLATFORM_TYPE_UNIX
                    if (::fcntl(descriptor, F_GETFL) & O_APPEND) {
                        mode += 'a';
                    }
#endif
                    return File(descriptor, mode).release();
                }
                else {
#if XIEITE_COMPILER_TYPE_GCC
                    return static_cast<__gnu_cxx::stdio_filebuf<typename Stream::char_type, typename Stream::traits_type>*>(stream.rdbuf())->file();
#else
                    return nullptr;
#endif
                }
            })();
        }

        void reopen(const std::string& path, const std::string& mode, const File other) noexcept {
            this->stream = std::freopen(path.c_str(), mode.c_str(), other.file());
        }

#if XIEITE_PLATFORM_TYPE_WINDOWS
        void reopen(const std::wstring& path, const std::wstring& mode, const File other) noexcept {
            this->stream = ::_wfreopen(path.c_str(), mode.c_str(), other.file());
        }
#endif

        int close() noexcept {
            if (this->stream && (this->stream != stdin) && (this->stream != stdout) && (this->stream != stderr)) {
                return std::fclose(this->stream);
            }
            return EOF;  // Erroneous value of `std::fclose`
        }

        [[nodiscard]] std::FILE* file() const noexcept {
            return this->stream;
        }

        [[nodiscard]] int descriptor() const noexcept {
#if XIEITE_PLATFORM_TYPE_WINDOWS
            return ::_fileno(this->stream);
#else
            return ::fileno(this->stream);
#endif
        }

        [[nodiscard]] std::FILE* release() noexcept {
            std::FILE* const copy = this->stream;
            this->stream = nullptr;
            return copy;
        }

    private:
        std::FILE* stream;
    };
}
