# Scanning and Parsing

## Overview

XIEITE provides comprehensive terminal input scanning and parsing capabilities through the `xieite::term` utility. This system enables real-time character and key sequence parsing, input mode control, and cross-platform terminal interaction. The implementation focuses on Unix-like systems with fallback support for other platforms.

## Core Terminal Interface

### Terminal Control Structure
Implementation: `include/xieite/io/term.hpp` (lines 29-776)

```cpp
struct term {
public:
    std::FILE* in;   // Input stream
    std::FILE* out;  // Output stream

    [[nodiscard]] term(std::FILE* in = stdin, std::FILE* out = stdout) noexcept;
    term(const xieite::term&) = delete;
    ~term();

    // Terminal mode control
    void block(bool x) noexcept;      // Blocking/non-blocking input
    void echo(bool x) noexcept;       // Echo input characters
    void canon(bool x) noexcept;      // Canonical/raw input mode
    void signal(bool x) noexcept;     // Signal processing
    void proc(bool x) noexcept;       // Output processing
};
```

Provides complete terminal control with automatic mode restoration on destruction.

## Input Scanning Methods

### Character Reading
Implementation: `include/xieite/io/term.hpp` (lines 384-394)

```cpp
[[nodiscard]] int read_char() noexcept {
#if XIEITE_PLATFORM_TYPE_UNIX
    const bool canon_prev = this->is_canon;
    this->canon(false);               // Disable canonical mode
    const int c = std::fgetc(this->in);
    this->canon(canon_prev);          // Restore previous mode
    return c;
#else
    return std::fgetc(this->in);     // Fallback for other platforms
#endif
}
```

Reads single characters with temporary mode switching for immediate input.

### String Reading
Implementation: `include/xieite/io/term.hpp` (lines 396-409)

```cpp
[[nodiscard]] std::string read_str() noexcept {
#if XIEITE_PLATFORM_TYPE_UNIX
    const bool block_prev = this->is_block;
    const bool canon_prev = this->is_canon;
    this->block(false);               // Non-blocking mode
    this->canon(false);               // Raw mode
    const std::string input = xieite::read(this->in);
    this->block(block_prev);          // Restore modes
    this->canon(canon_prev);
    return input;
#else
    return xieite::read(this->in);   // Fallback
#endif
}
```

Reads complete strings with automatic mode management.

### Key Sequence Parsing
Implementation: `include/xieite/io/term.hpp` (lines 411-748)

```cpp
[[nodiscard]] xieite::keys read_key() noexcept {
#if XIEITE_PLATFORM_TYPE_UNIX
    const xieite::scope_guard _ = [this, block_prev = this->is_block] {
        this->block(block_prev);
    };
#endif
    const int c0 = this->read_char();
    this->block(false);

    switch (c0) {
    case 0x00: /* Handle null sequences */
    case 0x01: return xieite::keys::ctrl_a;
    case 0x02: return xieite::keys::ctrl_b;
    // ... extensive key mapping ...
    case 0x1B: /* Handle escape sequences */
        switch (const int c1 = this->read_char()) {
        case 0x5B: /* Handle ANSI escape sequences */
            // Complex multi-character sequence parsing
        }
    }
}
```

Comprehensive key sequence parser supporting control keys, function keys, and special sequences.

## Terminal State Management

### Cursor Position Operations
Implementation: `include/xieite/io/term.hpp` (lines 211-267)

```cpp
[[nodiscard]] xieite::pos get_cursor() noexcept {
#if XIEITE_PLATFORM_TYPE_UNIX
    const bool canon_prev = this->is_canon;
    this->canon(false);
    std::fputs("\x1B[6n", this->out);          // Send cursor position query
    int row = 1;
    int col = 1;
    std::fscanf(this->in, "\x1B[%i;%iR", &row, &col);  // Parse response
    this->canon(canon_prev);
    return xieite::pos(static_cast<xieite::ssize_t>(row - 1),
                       static_cast<xieite::ssize_t>(col - 1));
#else
    return xieite::pos(0, 0);
#endif
}
```

Queries and parses terminal cursor position using ANSI escape sequences.

### Screen Size Detection
Implementation: `include/xieite/io/term.hpp` (lines 326-334)

```cpp
[[nodiscard]] xieite::pos screen_size() noexcept {
#if XIEITE_PLATFORM_TYPE_UNIX
    ::winsize size;
    ::ioctl(::fileno(this->in), TIOCGWINSZ, &size);
    return xieite::pos(size.ws_row, size.ws_col);
#else
    return xieite::pos(0, 0);
#endif
}
```

Retrieves terminal dimensions using system ioctl calls.

## Usage Examples

### Basic Input Scanning
```cpp
#include <xieite/io/term.hpp>
#include <iostream>

void basic_input_example() {
    xieite::term terminal;

    std::cout << "Press any key (ESC to exit): ";

    while (true) {
        xieite::keys key = terminal.read_key();

        switch (key) {
            case xieite::keys::escape:
                std::cout << "\nExiting...\n";
                return;

            case xieite::keys::up:
                std::cout << "\nUp arrow pressed\n";
                break;

            case xieite::keys::down:
                std::cout << "\nDown arrow pressed\n";
                break;

            case xieite::keys::enter:
                std::cout << "\nEnter pressed\n";
                break;

            case xieite::keys::ctrl_c:
                std::cout << "\nCtrl+C pressed\n";
                return;

            default:
                if (key >= xieite::keys::a && key <= xieite::keys::z) {
                    char ch = 'a' + static_cast<int>(key) - static_cast<int>(xieite::keys::a);
                    std::cout << "\nLetter: " << ch << "\n";
                } else if (key >= xieite::keys::_0 && key <= xieite::keys::_9) {
                    char ch = '0' + static_cast<int>(key) - static_cast<int>(xieite::keys::_0);
                    std::cout << "\nDigit: " << ch << "\n";
                } else {
                    std::cout << "\nUnknown key\n";
                }
                break;
        }

        std::cout << "Press another key (ESC to exit): ";
    }
}
```

### Interactive Menu System
```cpp
#include <xieite/io/term.hpp>
#include <iostream>
#include <vector>
#include <string>

class InteractiveMenu {
private:
    xieite::term terminal_;
    std::vector<std::string> options_;
    std::size_t selected_index_;

public:
    InteractiveMenu(const std::vector<std::string>& options)
        : options_(options), selected_index_(0) {}

    void display_menu() {
        terminal_.clear_screen();
        terminal_.set_cursor(0, 0);

        std::cout << "Use arrow keys to navigate, Enter to select, ESC to exit:\n\n";

        for (std::size_t i = 0; i < options_.size(); ++i) {
            if (i == selected_index_) {
                terminal_.bg(50, 50, 150);     // Highlight background
                terminal_.fg(255, 255, 255);   // White text
                std::cout << "> " << options_[i];
                terminal_.reset_style();
            } else {
                std::cout << "  " << options_[i];
            }
            std::cout << "\n";
        }

        std::cout << "\nSelected: " << selected_index_ << "\n";
    }

    int run() {
        while (true) {
            display_menu();

            xieite::keys key = terminal_.read_key();

            switch (key) {
                case xieite::keys::up:
                    if (selected_index_ > 0) {
                        selected_index_--;
                    }
                    break;

                case xieite::keys::down:
                    if (selected_index_ < options_.size() - 1) {
                        selected_index_++;
                    }
                    break;

                case xieite::keys::enter:
                    terminal_.clear_screen();
                    terminal_.set_cursor(0, 0);
                    std::cout << "Selected: " << options_[selected_index_] << "\n";
                    return static_cast<int>(selected_index_);

                case xieite::keys::escape:
                    terminal_.clear_screen();
                    terminal_.set_cursor(0, 0);
                    std::cout << "Menu cancelled\n";
                    return -1;

                default:
                    break;
            }
        }
    }
};

void menu_example() {
    std::vector<std::string> options = {
        "New File",
        "Open File",
        "Save File",
        "Settings",
        "Exit"
    };

    InteractiveMenu menu(options);
    int selection = menu.run();

    if (selection >= 0) {
        std::cout << "You selected option " << selection << ": "
                  << options[selection] << "\n";
    }
}
```

### Real-Time Input Parser
```cpp
#include <xieite/io/term.hpp>
#include <iostream>
#include <string>
#include <chrono>

class RealTimeParser {
private:
    xieite::term terminal_;
    std::string input_buffer_;
    std::chrono::steady_clock::time_point last_input_;

public:
    RealTimeParser() {
        // Configure terminal for real-time input
        terminal_.echo(false);    // Don't echo characters
        terminal_.canon(false);   // Raw mode
        terminal_.block(false);   // Non-blocking
    }

    void process_input() {
        std::cout << "Real-time input parser (Ctrl+C to exit)\n";
        std::cout << "Type characters and see them processed immediately:\n\n";

        while (true) {
            xieite::keys key = terminal_.read_key();
            auto now = std::chrono::steady_clock::now();

            if (key == xieite::keys::ctrl_c) {
                std::cout << "\nExiting...\n";
                break;
            }

            if (key == xieite::keys::unknown) {
                // No input available in non-blocking mode
                // Check for timeout-based processing
                if (!input_buffer_.empty()) {
                    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
                        now - last_input_);

                    if (elapsed.count() > 1000) {  // 1 second timeout
                        process_complete_input();
                    }
                }
                continue;
            }

            last_input_ = now;

            // Convert key to character if possible
            char ch = key_to_char(key);
            if (ch != '\0') {
                input_buffer_ += ch;
                std::cout << ch << std::flush;  // Show character immediately

                // Process special patterns
                analyze_input_pattern();
            } else {
                // Handle special keys
                handle_special_key(key);
            }
        }
    }

private:
    char key_to_char(xieite::keys key) {
        if (key >= xieite::keys::a && key <= xieite::keys::z) {
            return 'a' + static_cast<int>(key) - static_cast<int>(xieite::keys::a);
        } else if (key >= xieite::keys::A && key <= xieite::keys::Z) {
            return 'A' + static_cast<int>(key) - static_cast<int>(xieite::keys::A);
        } else if (key >= xieite::keys::_0 && key <= xieite::keys::_9) {
            return '0' + static_cast<int>(key) - static_cast<int>(xieite::keys::_0);
        } else if (key == xieite::keys::space) {
            return ' ';
        }
        return '\0';
    }

    void handle_special_key(xieite::keys key) {
        switch (key) {
            case xieite::keys::backspace:
                if (!input_buffer_.empty()) {
                    input_buffer_.pop_back();
                    std::cout << "\b \b" << std::flush;  // Erase character visually
                }
                break;

            case xieite::keys::enter:
                std::cout << "\n";
                process_complete_input();
                break;

            case xieite::keys::tab:
                input_buffer_ += "\t";
                std::cout << "\t" << std::flush;
                break;

            default:
                break;
        }
    }

    void analyze_input_pattern() {
        // Real-time pattern analysis
        if (input_buffer_.length() >= 3) {
            std::string last_three = input_buffer_.substr(input_buffer_.length() - 3);

            if (last_three == "123") {
                std::cout << " [SEQUENCE DETECTED]" << std::flush;
            } else if (last_three == "abc") {
                std::cout << " [ALPHABET SEQUENCE]" << std::flush;
            }
        }
    }

    void process_complete_input() {
        if (!input_buffer_.empty()) {
            std::cout << "\nProcessed: \"" << input_buffer_ << "\"\n";
            std::cout << "Length: " << input_buffer_.length() << " characters\n";

            // Analysis
            std::size_t vowel_count = 0;
            for (char c : input_buffer_) {
                if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
                    c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
                    vowel_count++;
                }
            }

            std::cout << "Vowels: " << vowel_count << "\n";
            std::cout << "Consonants: " << (input_buffer_.length() - vowel_count) << "\n\n";

            input_buffer_.clear();
        }
    }
};

void real_time_parser_example() {
    RealTimeParser parser;
    parser.process_input();
}
```

## Advanced Patterns

### Command Line Interface Builder
```cpp
#include <xieite/io/term.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <map>

class CLIBuilder {
private:
    xieite::term terminal_;
    std::map<std::string, std::function<void()>> commands_;
    std::vector<std::string> history_;
    std::size_t history_index_;
    std::string current_line_;
    std::size_t cursor_pos_;

public:
    CLIBuilder() : history_index_(0), cursor_pos_(0) {
        terminal_.echo(false);
        terminal_.canon(false);

        // Register built-in commands
        commands_["help"] = [this] { show_help(); };
        commands_["clear"] = [this] { terminal_.clear_screen(); };
        commands_["history"] = [this] { show_history(); };
        commands_["exit"] = [this] { exit_cli(); };
    }

    void add_command(const std::string& name, std::function<void()> handler) {
        commands_[name] = handler;
    }

    void run() {
        terminal_.clear_screen();
        std::cout << "XIEITE CLI - Type 'help' for commands\n\n";

        while (true) {
            display_prompt();
            if (!read_command()) {
                break;  // Exit requested
            }
        }
    }

private:
    void display_prompt() {
        std::cout << "> " << current_line_;

        // Position cursor correctly
        std::size_t prompt_len = 2;  // "> "
        terminal_.set_cursor(terminal_.get_cursor().row,
                           prompt_len + static_cast<xieite::ssize_t>(cursor_pos_));
    }

    bool read_command() {
        xieite::keys key = terminal_.read_key();

        switch (key) {
            case xieite::keys::enter:
                std::cout << "\n";
                if (!current_line_.empty()) {
                    execute_command(current_line_);
                    history_.push_back(current_line_);
                    history_index_ = history_.size();
                }
                current_line_.clear();
                cursor_pos_ = 0;
                break;

            case xieite::keys::backspace:
                if (cursor_pos_ > 0) {
                    current_line_.erase(cursor_pos_ - 1, 1);
                    cursor_pos_--;
                    redraw_line();
                }
                break;

            case xieite::keys::left:
                if (cursor_pos_ > 0) {
                    cursor_pos_--;
                    terminal_.mv_cursor(0, -1);
                }
                break;

            case xieite::keys::right:
                if (cursor_pos_ < current_line_.length()) {
                    cursor_pos_++;
                    terminal_.mv_cursor(0, 1);
                }
                break;

            case xieite::keys::up:
                navigate_history(-1);
                break;

            case xieite::keys::down:
                navigate_history(1);
                break;

            case xieite::keys::ctrl_c:
                std::cout << "\n";
                current_line_.clear();
                cursor_pos_ = 0;
                break;

            case xieite::keys::ctrl_d:
                if (current_line_.empty()) {
                    std::cout << "\nExiting...\n";
                    return false;
                }
                break;

            default:
                char ch = key_to_char(key);
                if (ch != '\0') {
                    current_line_.insert(cursor_pos_, 1, ch);
                    cursor_pos_++;
                    redraw_line();
                }
                break;
        }

        return true;
    }

    void redraw_line() {
        // Clear current line and redraw
        terminal_.set_cursor(terminal_.get_cursor().row, 0);
        terminal_.clear_line();
        std::cout << "> " << current_line_;

        // Position cursor
        terminal_.set_cursor(terminal_.get_cursor().row,
                           2 + static_cast<xieite::ssize_t>(cursor_pos_));
    }

    void navigate_history(int direction) {
        if (history_.empty()) return;

        if (direction < 0 && history_index_ > 0) {
            history_index_--;
        } else if (direction > 0 && history_index_ < history_.size()) {
            history_index_++;
        } else {
            return;
        }

        if (history_index_ < history_.size()) {
            current_line_ = history_[history_index_];
        } else {
            current_line_.clear();
        }

        cursor_pos_ = current_line_.length();
        redraw_line();
    }

    void execute_command(const std::string& command) {
        auto it = commands_.find(command);
        if (it != commands_.end()) {
            it->second();
        } else {
            std::cout << "Unknown command: " << command << "\n";
            std::cout << "Type 'help' for available commands.\n";
        }
    }

    char key_to_char(xieite::keys key) {
        // Same implementation as previous example
        if (key >= xieite::keys::a && key <= xieite::keys::z) {
            return 'a' + static_cast<int>(key) - static_cast<int>(xieite::keys::a);
        }
        // ... etc
        return '\0';
    }

    void show_help() {
        std::cout << "Available commands:\n";
        for (const auto& [name, _] : commands_) {
            std::cout << "  " << name << "\n";
        }
    }

    void show_history() {
        std::cout << "Command history:\n";
        for (std::size_t i = 0; i < history_.size(); ++i) {
            std::cout << "  " << i + 1 << ": " << history_[i] << "\n";
        }
    }

    void exit_cli() {
        std::cout << "Goodbye!\n";
        std::exit(0);
    }
};
```

## Implementation Details

### Unix-Specific Terminal Control
The implementation (term.hpp:37-45, 766-775) uses:
- `fcntl()` for file descriptor control (blocking/non-blocking)
- `tcgetattr()`/`tcsetattr()` for terminal attribute management
- `ioctl()` with `TIOCGWINSZ` for screen size detection
- POSIX termios structures for mode configuration

### Escape Sequence Parsing
The key parsing system (term.hpp:452-747) handles:
- Single character keys (ASCII 0x20-0x7F)
- Control sequences (Ctrl+A through Ctrl+Z)
- Alt combinations with all printable characters
- Function keys (F1-F12) through ANSI escape sequences
- Arrow keys and navigation keys
- Complex multi-byte escape sequences

### Mode Management Strategy
The terminal state management employs:
- RAII pattern for automatic cleanup on destruction
- Scope guards for temporary mode changes
- Bitwise flag manipulation for efficient mode switching
- Original state preservation for restoration

## Performance Considerations

- **Non-blocking I/O**: Supports real-time input without blocking
- **Minimal system calls**: Efficient terminal attribute management
- **Escape sequence caching**: Optimized multi-character sequence parsing
- **Platform fallbacks**: Graceful degradation on unsupported systems

## Best Practices

1. **Always use RAII**: Let the destructor restore terminal state
2. **Handle platform differences**: Check `XIEITE_PLATFORM_TYPE_UNIX` for feature availability
3. **Use scope guards**: For temporary mode changes within functions
4. **Test key sequences**: Different terminals may send different escape sequences

## Common Use Cases

### Interactive Applications
```cpp
#include <xieite/io/term.hpp>

void interactive_app() {
    xieite::term terminal;
    terminal.echo(false);
    terminal.canon(false);

    // Real-time character processing
    while (true) {
        xieite::keys key = terminal.read_key();
        // Process immediately
    }
}
```

### Input Validation
```cpp
bool validate_numeric_input() {
    xieite::term terminal;

    while (true) {
        xieite::keys key = terminal.read_key();

        if (key >= xieite::keys::_0 && key <= xieite::keys::_9) {
            return true;  // Valid digit
        } else if (key == xieite::keys::escape) {
            return false; // Cancelled
        }
        // Ignore other keys
    }
}
```

### Terminal Games
```cpp
void simple_snake_game() {
    xieite::term terminal;
    terminal.cursor_invis(true);
    terminal.clear_screen();

    // Game loop with real-time input
    while (true) {
        xieite::keys key = terminal.read_key();

        switch (key) {
            case xieite::keys::up:
            case xieite::keys::down:
            case xieite::keys::left:
            case xieite::keys::right:
                // Update game state
                break;
            case xieite::keys::escape:
                return;
        }

        // Render game state
    }
}
```

## See Also

- [Format Helpers](./formatting.md) - Output formatting utilities
- [Debug Output](./debug.md) - Debug printing utilities
- [File Operations](./files.md) - File I/O utilities
- [I/O API Reference](../../reference/api/io.md)