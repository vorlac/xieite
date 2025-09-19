# I/O API Reference

## Overview

The io category contains 30+ header files providing input/output utilities, including enhanced stream operations, formatting helpers, file I/O, scanning/parsing, and debug output utilities.

## Organization

The io headers are organized into functional groups:

- **Stream Operations** (8+ headers): Enhanced stream manipulation
- **Formatting** (6+ headers): Output formatting utilities
- **File Operations** (5+ headers): File I/O helpers
- **Scanning/Parsing** (5+ headers): Input parsing utilities
- **Debug Output** (4+ headers): Debug and logging helpers
- **Console I/O** (2+ headers): Terminal/console operations

## Stream Operations

### print
**Header**: `io/print.hpp`
**Synopsis**: `void print(Args&&... args)`
**Purpose**: Print values to stdout
**Example**:
```cpp
xieite::print("Hello", " ", "World", '\n');
xieite::print("Value: ", 42, ", Pi: ", 3.14159);
```

### println
**Header**: `io/println.hpp`
**Synopsis**: `void println(Args&&... args)`
**Purpose**: Print values with newline
**Example**:
```cpp
xieite::println("Hello World");
xieite::println("Count:", 10);
```

### eprint
**Header**: `io/eprint.hpp`
**Synopsis**: `void eprint(Args&&... args)`
**Purpose**: Print to stderr
**Example**:
```cpp
xieite::eprint("Error: ", error_message);
```

### eprintln
**Header**: `io/eprintln.hpp`
**Synopsis**: `void eprintln(Args&&... args)`
**Purpose**: Print to stderr with newline
**Example**:
```cpp
xieite::eprintln("Error occurred!");
```

### stream_guard
**Header**: `io/stream_guard.hpp`
**Synopsis**: `class stream_guard`
**Purpose**: RAII stream state restoration
**Example**:
```cpp
{
    xieite::stream_guard guard(std::cout);
    std::cout << std::hex << std::uppercase;
    std::cout << 255;  // Prints "FF"
}  // Stream state restored
```

### stream_separator
**Header**: `io/stream_separator.hpp`
**Synopsis**: `class stream_separator`
**Purpose**: Auto-insert separators
**Example**:
```cpp
xieite::stream_separator sep(std::cout, ", ");
sep << 1 << 2 << 3;  // Prints: "1, 2, 3"
```

### stream_indent
**Header**: `io/stream_indent.hpp`
**Synopsis**: `class stream_indent`
**Purpose**: Manage indentation
**Example**:
```cpp
xieite::stream_indent indent(std::cout);
indent.push(4);
indent << "Indented line\n";
indent.push(4);
indent << "More indented\n";
indent.pop();
indent << "Less indented\n";
```

### tee_stream
**Header**: `io/tee_stream.hpp`
**Synopsis**: `class tee_stream`
**Purpose**: Write to multiple streams
**Example**:
```cpp
std::ofstream file("log.txt");
xieite::tee_stream tee(std::cout, file);
tee << "This goes to both console and file\n";
```

## Input Operations

### scan
**Header**: `io/scan.hpp`
**Synopsis**: `bool scan(T& value)`
**Purpose**: Read from stdin
**Example**:
```cpp
int n;
if (xieite::scan(n)) {
    std::cout << "Read: " << n << '\n';
}
```

### scan_line
**Header**: `io/scan_line.hpp`
**Synopsis**: `std::string scan_line()`
**Purpose**: Read entire line
**Example**:
```cpp
std::cout << "Enter name: ";
auto name = xieite::scan_line();
```

### scan_all
**Header**: `io/scan_all.hpp`
**Synopsis**: `std::string scan_all()`
**Purpose**: Read all input
**Example**:
```cpp
auto content = xieite::scan_all();
```

### scan_until
**Header**: `io/scan_until.hpp`
**Synopsis**: `std::string scan_until(char delimiter)`
**Purpose**: Read until delimiter
**Example**:
```cpp
auto word = xieite::scan_until(' ');
```

### scan_n
**Header**: `io/scan_n.hpp`
**Synopsis**: `std::string scan_n(std::size_t n)`
**Purpose**: Read n characters
**Example**:
```cpp
auto chunk = xieite::scan_n(10);  // Read 10 chars
```

## Formatting Utilities

### format
**Header**: `io/format.hpp`
**Synopsis**: `std::string format(const std::string& fmt, Args&&... args)`
**Purpose**: Format string (printf-style)
**Example**:
```cpp
auto str = xieite::format("Value: %d, Pi: %.2f", 42, 3.14159);
// "Value: 42, Pi: 3.14"
```

### pad_left
**Header**: `io/pad_left.hpp`
**Synopsis**: `std::string pad_left(const std::string& str, std::size_t width, char fill = ' ')`
**Purpose**: Left-pad string
**Example**:
```cpp
auto padded = xieite::pad_left("42", 5, '0');  // "00042"
```

### pad_right
**Header**: `io/pad_right.hpp`
**Synopsis**: `std::string pad_right(const std::string& str, std::size_t width, char fill = ' ')`
**Purpose**: Right-pad string
**Example**:
```cpp
auto padded = xieite::pad_right("Hello", 10, '.');  // "Hello....."
```

### pad_center
**Header**: `io/pad_center.hpp`
**Synopsis**: `std::string pad_center(const std::string& str, std::size_t width, char fill = ' ')`
**Purpose**: Center string with padding
**Example**:
```cpp
auto centered = xieite::pad_center("Hi", 7, '-');  // "--Hi---"
```

### align_columns
**Header**: `io/align_columns.hpp`
**Synopsis**: `std::string align_columns(const std::vector<std::vector<std::string>>& data)`
**Purpose**: Align data in columns
**Example**:
```cpp
std::vector<std::vector<std::string>> data = {
    {"Name", "Age", "City"},
    {"Alice", "30", "New York"},
    {"Bob", "25", "LA"}
};
auto table = xieite::align_columns(data);
```

### hex_dump
**Header**: `io/hex_dump.hpp`
**Synopsis**: `std::string hex_dump(const void* data, std::size_t size)`
**Purpose**: Generate hex dump
**Example**:
```cpp
char buffer[] = "Hello World";
auto dump = xieite::hex_dump(buffer, sizeof(buffer));
```

## File Operations

### read_file
**Header**: `io/read_file.hpp`
**Synopsis**: `std::string read_file(const std::string& path)`
**Purpose**: Read entire file
**Example**:
```cpp
auto content = xieite::read_file("config.txt");
```

### write_file
**Header**: `io/write_file.hpp`
**Synopsis**: `void write_file(const std::string& path, const std::string& content)`
**Purpose**: Write to file
**Example**:
```cpp
xieite::write_file("output.txt", "Hello World");
```

### append_file
**Header**: `io/append_file.hpp`
**Synopsis**: `void append_file(const std::string& path, const std::string& content)`
**Purpose**: Append to file
**Example**:
```cpp
xieite::append_file("log.txt", "New log entry\n");
```

### read_lines
**Header**: `io/read_lines.hpp`
**Synopsis**: `std::vector<std::string> read_lines(const std::string& path)`
**Purpose**: Read file as lines
**Example**:
```cpp
auto lines = xieite::read_lines("data.txt");
for (const auto& line : lines) {
    process_line(line);
}
```

### write_lines
**Header**: `io/write_lines.hpp`
**Synopsis**: `void write_lines(const std::string& path, const std::vector<std::string>& lines)`
**Purpose**: Write lines to file
**Example**:
```cpp
std::vector<std::string> lines = {"Line 1", "Line 2", "Line 3"};
xieite::write_lines("output.txt", lines);
```

### file_size
**Header**: `io/file_size.hpp`
**Synopsis**: `std::size_t file_size(const std::string& path)`
**Purpose**: Get file size
**Example**:
```cpp
auto size = xieite::file_size("large_file.dat");
std::cout << "File size: " << size << " bytes\n";
```

### file_exists
**Header**: `io/file_exists.hpp`
**Synopsis**: `bool file_exists(const std::string& path)`
**Purpose**: Check if file exists
**Example**:
```cpp
if (xieite::file_exists("config.ini")) {
    load_config("config.ini");
}
```

## Debug Output

### debug_print
**Header**: `io/debug_print.hpp`
**Synopsis**: `void debug_print(const T& value)`
**Purpose**: Print debug representation
**Example**:
```cpp
std::vector<int> v{1, 2, 3};
xieite::debug_print(v);  // Prints: [1, 2, 3]
```

### dump
**Header**: `io/dump.hpp`
**Synopsis**: `void dump(const T& value, const std::string& name = "")`
**Purpose**: Dump variable with name
**Example**:
```cpp
int x = 42;
xieite::dump(x, "x");  // Prints: "x = 42"
```

### trace
**Header**: `io/trace.hpp`
**Synopsis**: `void trace(const std::string& msg)`
**Purpose**: Trace execution with file/line
**Example**:
```cpp
xieite::trace("Checkpoint reached");
// Prints: "[file.cpp:123] Checkpoint reached"
```

### log
**Header**: `io/log.hpp`
**Synopsis**: `void log(LogLevel level, const std::string& msg)`
**Purpose**: Leveled logging
**Example**:
```cpp
xieite::log(xieite::LogLevel::INFO, "Starting process");
xieite::log(xieite::LogLevel::ERROR, "Connection failed");
```

## Console/Terminal

### clear_screen
**Header**: `io/clear_screen.hpp`
**Synopsis**: `void clear_screen()`
**Purpose**: Clear terminal screen
**Example**:
```cpp
xieite::clear_screen();
```

### set_color
**Header**: `io/set_color.hpp`
**Synopsis**: `void set_color(Color fg, Color bg = Color::DEFAULT)`
**Purpose**: Set terminal colors
**Example**:
```cpp
xieite::set_color(xieite::Color::RED);
std::cout << "Error!" << std::endl;
xieite::set_color(xieite::Color::DEFAULT);
```

### cursor_position
**Header**: `io/cursor_position.hpp`
**Synopsis**: `void cursor_position(int row, int col)`
**Purpose**: Move cursor position
**Example**:
```cpp
xieite::cursor_position(10, 20);
std::cout << "Text at position (10, 20)";
```

### get_terminal_size
**Header**: `io/get_terminal_size.hpp`
**Synopsis**: `std::pair<int, int> get_terminal_size()`
**Purpose**: Get terminal dimensions
**Example**:
```cpp
auto [rows, cols] = xieite::get_terminal_size();
std::cout << "Terminal: " << rows << "x" << cols << '\n';
```

## Progress Indicators

### progress_bar
**Header**: `io/progress_bar.hpp`
**Synopsis**: `class progress_bar`
**Purpose**: Display progress bar
**Example**:
```cpp
xieite::progress_bar bar(100);
for (int i = 0; i <= 100; ++i) {
    bar.update(i);
    // Do work...
}
```

### spinner
**Header**: `io/spinner.hpp`
**Synopsis**: `class spinner`
**Purpose**: Display spinning indicator
**Example**:
```cpp
xieite::spinner spin;
while (processing) {
    spin.update();
    // Do work...
}
```

## Binary I/O

### read_binary
**Header**: `io/read_binary.hpp`
**Synopsis**: `std::vector<uint8_t> read_binary(const std::string& path)`
**Purpose**: Read binary file
**Example**:
```cpp
auto data = xieite::read_binary("image.png");
```

### write_binary
**Header**: `io/write_binary.hpp`
**Synopsis**: `void write_binary(const std::string& path, const std::vector<uint8_t>& data)`
**Purpose**: Write binary file
**Example**:
```cpp
std::vector<uint8_t> data = generate_data();
xieite::write_binary("output.bin", data);
```

### binary_reader
**Header**: `io/binary_reader.hpp`
**Synopsis**: `class binary_reader`
**Purpose**: Read binary data with endianness
**Example**:
```cpp
xieite::binary_reader reader("data.bin");
auto magic = reader.read<uint32_t>();
auto version = reader.read<uint16_t>();
```

### binary_writer
**Header**: `io/binary_writer.hpp`
**Synopsis**: `class binary_writer`
**Purpose**: Write binary data with endianness
**Example**:
```cpp
xieite::binary_writer writer("output.bin");
writer.write<uint32_t>(0x12345678);
writer.write<uint16_t>(42);
```

## String Streams

### string_reader
**Header**: `io/string_reader.hpp`
**Synopsis**: `class string_reader`
**Purpose**: Read from string
**Example**:
```cpp
xieite::string_reader reader("42 3.14 hello");
int n;
double d;
std::string s;
reader >> n >> d >> s;
```

### string_writer
**Header**: `io/string_writer.hpp`
**Synopsis**: `class string_writer`
**Purpose**: Write to string
**Example**:
```cpp
xieite::string_writer writer;
writer << "Value: " << 42 << ", Pi: " << 3.14;
std::string result = writer.str();
```

## Usage Examples

### Basic I/O
```cpp
#include <xieite/io/println.hpp>
#include <xieite/io/scan_line.hpp>

int main() {
    xieite::println("Enter your name:");
    auto name = xieite::scan_line();
    xieite::println("Hello,", name, "!");
}
```

### File Operations
```cpp
#include <xieite/io/read_lines.hpp>
#include <xieite/io/write_file.hpp>

void process_config() {
    auto lines = xieite::read_lines("config.txt");
    std::string output;
    for (const auto& line : lines) {
        output += process_line(line) + "\n";
    }
    xieite::write_file("processed.txt", output);
}
```

### Debug Output
```cpp
#include <xieite/io/debug_print.hpp>
#include <xieite/io/dump.hpp>

void debug_data() {
    std::map<std::string, int> data = {
        {"apple", 5},
        {"banana", 3}
    };
    xieite::debug_print(data);

    int count = 42;
    xieite::dump(count, "count");
}
```

### Progress Display
```cpp
#include <xieite/io/progress_bar.hpp>

void process_items(const std::vector<Item>& items) {
    xieite::progress_bar bar(items.size());
    for (std::size_t i = 0; i < items.size(); ++i) {
        process_item(items[i]);
        bar.update(i + 1);
    }
}
```

## Performance Notes

- Stream guards have minimal overhead
- File operations buffer for efficiency
- Binary I/O uses memory mapping when available
- Progress indicators use minimal terminal updates
- Debug output is optimized out in release builds

## See Also

- [I/O Utilities Overview](../../categories/io/README.md)
- [Stream Operations](../../categories/io/streams.md)
- [File Operations](../../categories/io/files.md)
- [System API](./sys.md)