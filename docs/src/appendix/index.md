# Index

Comprehensive alphabetical index of XIEITE features, functions, types, and concepts.

## A

**abs** - `xieite/math/abs.hpp`
- Mathematical absolute value function with overflow protection
- Supports all arithmetic types with optimized implementations
- Returns unsigned type for signed integer inputs

**after** - `xieite/data/after.hpp`
- String/container utility for extracting content after a delimiter
- Template-based for generic container support

**after_last** - `xieite/data/after_last.hpp`
- Extract content after the last occurrence of a delimiter
- Useful for file extension extraction and path manipulation

**and** - `xieite/pp/and.hpp`
- Preprocessor logical AND operation
- Enables complex conditional compilation expressions

**any** - `xieite/pp/any.hpp`
- Preprocessor utility for checking if any condition is true
- Variadic macro for multiple condition evaluation

**apply_until** - `xieite/fn/apply_until.hpp`
- Functional utility for repeated function application
- Stops when predicate condition is met

**arch** - `xieite/pp/arch.hpp`
- Architecture detection macros (x86, x64, ARM, etc.)
- Cross-platform architecture identification

**arithmetic operations** - Various headers in `xieite/math/`
- Comprehensive mathematical function library
- Compile-time and runtime optimized implementations

**arrow macros** - `xieite/pp/arrow.hpp`
- XIEITE_ARROW: Auto-deducing return type and noexcept
- XIEITE_ARROW_NOEX: Forces noexcept(true)
- XIEITE_ARROW_RET: Manual return type specification

**as** - `xieite/pp/as.hpp`
- Preprocessor type casting utility
- Template argument forwarding helper

**at** - `xieite/pp/at.hpp`
- Variadic argument access by index
- Compile-time argument selection

**attr** - `xieite/pp/attr.hpp`
- Cross-compiler attribute macros
- Standardized attribute application

## B

**before** - `xieite/data/before.hpp`
- Extract content before a delimiter
- String and container processing utility

**before_last** - `xieite/data/before_last.hpp`
- Extract content before the last occurrence of delimiter
- Path manipulation and string processing

**between** - `xieite/data/between.hpp`
- Extract content between two delimiters
- Substring extraction with boundary matching

**bool** - `xieite/pp/bool.hpp`
- Preprocessor boolean conversion utilities
- Macro-level boolean logic operations

**build configuration** - Advanced build system integration
- CMake support and cross-platform compilation
- Compiler detection and optimization flags

## C

**call** - `xieite/pp/call.hpp`
- Macro function invocation utility
- Delayed macro expansion control

**can_alias** - `xieite/trait/can_alias.hpp`
- Type trait for alias detection
- Template substitution checking

**cases** - `xieite/pp/cases.hpp`
- Switch-case generation macro
- Pattern matching utilities

**cat** - `xieite/pp/cat.hpp`
- Token concatenation macro
- Preprocessor string joining

**chars** - `xieite/data/chars.hpp`
- Character classification utilities
- Unicode and ASCII character handling

**check** - `xieite/pp/check.hpp`
- Conditional compilation checking
- Feature detection utilities

**cm** - `xieite/pp/cm.hpp`
- Comma insertion utility
- Variadic argument separation

**cmp_ignore_case** - `xieite/data/cmp_ignore_case.hpp`
- Case-insensitive string comparison
- Locale-aware string operations

**comma** - `xieite/pp/comma.hpp`
- Comma operator utilities
- Macro argument handling

**compiler** - `xieite/pp/compiler.hpp`
- Compiler detection macros (GCC, Clang, MSVC)
- Version checking and feature detection

**compile-time computation**
- Extensive constexpr utilities across all categories
- Template metaprogramming support

**compl** - `xieite/pp/compl.hpp`
- Bitwise complement operations
- Preprocessor bit manipulation

**concepts** - Throughout `xieite/trait/`
- C++20 concept definitions
- Type constraint utilities

**count** - `xieite/pp/count.hpp`
- Variadic argument counting
- Compile-time size determination

**cross-platform support**
- Platform detection and conditional compilation
- Unified interfaces for different operating systems

**curry** - `xieite/fn/curry.hpp`
- Function currying utilities
- Partial application support

## D

**data structures** - `xieite/data/` category
- 152 utilities for data manipulation
- Containers, strings, and algorithms

**debug** - `xieite/pp/debug.hpp`
- Debug macro utilities
- Conditional debug output

**defer** - `xieite/pp/defer.hpp`
- Macro expansion deferral
- Delayed evaluation control

**del** - `xieite/pp/del.hpp`
- Macro deletion/removal utility
- Preprocessor cleanup operations

**diagnostic** - `xieite/pp/diagnostic.hpp`
- Compiler diagnostic control
- Warning and error management

**diff** - `xieite/math/diff.hpp`
- Mathematical difference calculation
- Absolute difference utilities

## E

**each** - `xieite/pp/each.hpp`
- Macro iteration over arguments
- Bulk operation application

**eat** - `xieite/pp/eat.hpp`
- Argument consumption utility
- Macro argument disposal

**encoding** - `xieite/pp/encoding.hpp`
- Character encoding detection
- Unicode support utilities

**endian** - `xieite/pp/endian.hpp`
- Endianness detection and conversion
- Byte order utilities

**error handling**
- Exception safety patterns
- RAII and scope guard utilities

**eval** - `xieite/pp/eval.hpp`
- Macro evaluation control
- Expression expansion utilities

## F

**feat** - `xieite/pp/feat.hpp`
- Feature detection macros
- Capability checking utilities

**find_most_consec** - `xieite/data/find_most_consec.hpp`
- Find longest consecutive sequence
- Pattern analysis utility

**find_most_consec_if** - `xieite/data/find_most_consec_if.hpp`
- Conditional consecutive sequence finding
- Predicate-based pattern matching

**find_occur** - `xieite/data/find_occur.hpp`
- Occurrence finding in containers
- Search utilities

**find_occur_if** - `xieite/data/find_occur_if.hpp`
- Conditional occurrence finding
- Predicate-based searching

**fixed_array** - `xieite/data/fixed_array.hpp`
- Compile-time sized array container
- Stack-allocated fixed storage

**fixed_map** - `xieite/data/fixed_map.hpp`
- Compile-time sized map container
- Associative array with fixed capacity

**fixed_set** - `xieite/data/fixed_set.hpp`
- Compile-time sized set container
- Unique element storage

**fixed_str** - `xieite/data/fixed_str.hpp`
- Compile-time string type
- Fixed-length string handling

**fn** - `xieite/pp/fn.hpp`
- Function-related preprocessor utilities
- Lambda and function manipulation

**for** - `xieite/pp/for.hpp`
- Preprocessor loop constructs
- Iteration macros

**from** - `xieite/pp/from.hpp`
- Value extraction utilities
- Type conversion helpers

**functional programming** - `xieite/fn/` category
- 48 utilities for functional programming
- Higher-order functions and composition

**fwd** - `xieite/pp/fwd.hpp`
- Perfect forwarding utilities
- Template argument forwarding

## G

**get_env** - `xieite/sys/get_env.hpp`
- Environment variable access
- System configuration retrieval

**glossary** - Technical term definitions
- Comprehensive terminology reference

## H

**has_attr** - `xieite/pp/has_attr.hpp`
- Attribute availability detection
- Compiler capability checking

**has_declspec** - `xieite/pp/has_declspec.hpp`
- Microsoft declspec detection
- MSVC-specific feature checking

**has_incl** - `xieite/pp/has_incl.hpp`
- Header inclusion checking
- Availability testing

**header-only design**
- No compilation required
- Template-based implementation

## I

**if** - `xieite/pp/if.hpp`
- Conditional compilation macro
- Boolean-based code inclusion

**implementation patterns**
- Design patterns and best practices
- Advanced usage examples

**is_arith** - `xieite/trait/is_arith.hpp`
- Arithmetic type concept
- Numeric type checking

**is_abstract** - `xieite/trait/is_abstract.hpp`
- Abstract class detection
- Type property checking

**isalnum, isalpha, isblank, iscntrl** - `xieite/data/`
- Character classification functions
- Extended character type checking

**is_cxpr** - `xieite/pp/is_cxpr.hpp`
- Constexpr expression detection
- Compile-time evaluation checking

## J-K

**keywords** - `xieite/pp/keywords.hpp`
- Language keyword utilities
- Reserved word handling

## L

**lang** - `xieite/pp/lang.hpp`
- Language feature detection
- C++ standard checking

**lift** - `xieite/pp/lift.hpp`
- Expression lifting utilities
- Macro abstraction helpers

## M

**make_str_view** - String view creation utility
- Efficient string handling
- Zero-copy string operations

**math** - `xieite/math/` category
- 114 mathematical utilities
- Arithmetic and algorithmic functions

**meta** - `xieite/meta/` category
- 61 metaprogramming utilities
- Template manipulation tools

**metaprogramming**
- Template-based compile-time programming
- Type manipulation and generation

## N

**no_unix** - `xieite/pp/no_unix.hpp`
- Unix exclusion macro
- Platform-specific compilation control

**no_windows** - `xieite/pp/no_windows.hpp`
- Windows exclusion macro
- Platform filtering utilities

**none** - `xieite/pp/none.hpp`
- Empty value representation
- Null macro utilities

**not** - `xieite/pp/not.hpp`
- Logical negation macro
- Boolean inversion

## O

**obj** - `xieite/pp/obj.hpp`
- Object manipulation utilities
- Instance management helpers

**obstruct** - `xieite/pp/obstruct.hpp`
- Macro expansion obstruction
- Evaluation control mechanisms

**opt** - `xieite/pp/opt.hpp`
- Optional value handling
- Conditional operation utilities

**optimization**
- Performance optimization techniques
- Compile-time and runtime efficiency

**or** - `xieite/pp/or.hpp`
- Logical OR operation
- Boolean combination macro

**os** - `xieite/sys/os.hpp`
- Operating system detection
- Platform identification

**out** - `xieite/pp/out.hpp`
- Output parameter utilities
- Reference parameter handling

## P

**paren** - `xieite/pp/paren.hpp`
- Parentheses manipulation
- Expression grouping utilities

**performance**
- Optimization strategies and benchmarks
- Efficiency guidelines and measurements

**platform** - `xieite/pp/platform.hpp`
- Platform detection macros
- Operating system identification

**pp** - `xieite/pp/` category
- 67 preprocessor utilities
- Macro programming tools

**pragma** - `xieite/pp/pragma.hpp`
- Pragma directive utilities
- Compiler directive management

**probe** - `xieite/pp/probe.hpp`
- Template probe utilities
- SFINAE detection helpers

## Q-R

**repeat** - `xieite/pp/repeat.hpp`
- Repetition macros
- Loop unrolling utilities

**repeat** - `xieite/fn/repeat.hpp`
- Digit-based repetition
- Numeric iteration utilities

**restrict** - `xieite/pp/restrict.hpp`
- Restrict keyword utilities
- Memory access optimization

**ret_struct** - `xieite/pp/ret_struct.hpp`
- Return structure utilities
- Multiple return value handling

**reverse** - `xieite/pp/reverse.hpp`
- Argument order reversal
- Sequence manipulation

**revive** - `xieite/pp/revive.hpp`
- Macro revival utilities
- Definition restoration

**ceil** - `xieite/math/ceil.hpp`
- Directional rounding functions
- Precision control utilities

## S

**scan** - `xieite/pp/scan.hpp`
- Input scanning utilities
- Pattern matching and parsing

**scope_guard** - `xieite/fn/scope_guard.hpp`
- RAII scope management
- Automatic cleanup utilities

**seq** - `xieite/pp/seq.hpp`
- Sequence generation
- Range creation utilities

**signature** - `xieite/pp/signature.hpp`
- Function signature utilities
- Type signature manipulation

**static_assert** - `xieite/pp/static_assert.hpp`
- Enhanced static assertions
- Compile-time validation

**stdlib** - `xieite/pp/stdlib.hpp`
- Standard library detection
- Feature availability checking

**str** - `xieite/pp/str.hpp`
- String manipulation macros
- Text processing utilities

**string utilities** - Throughout `xieite/data/`
- Comprehensive string processing
- Text manipulation and analysis

**sys** - `xieite/sys/` category
- 42 system utilities
- OS and hardware interaction

## T

**template metaprogramming**
- Advanced template techniques
- Compile-time programming patterns

**trait** - `xieite/trait/` category
- 89 type traits and concepts
- Template constraint utilities

**try_subst** - `xieite/meta/try_subst.hpp`
- Substitution failure detection
- SFINAE utility for template matching

**try_unsigned** - `xieite/trait/try_unsigned.hpp`
- Unsigned type conversion
- Safe integer type transformation

**typeof** - `xieite/pp/typeof.hpp`
- Type extraction utilities
- Dynamic type determination

## U

**unix** - `xieite/pp/unix.hpp`
- Unix-specific utilities
- POSIX system support

**unreach** - `xieite/pp/unreach.hpp`
- Unreachable code markers
- Control flow optimization

**until** - `xieite/pp/until.hpp`
- Loop termination utilities
- Conditional iteration

**unwrap** - `xieite/pp/unwrap.hpp`
- Wrapper removal utilities
- Container value extraction

## V

**ver** - `xieite/pp/ver.hpp`
- Version detection utilities
- Software version management

**ver_guard** - Header guard generation
- Include protection utilities

## W

**word** - `xieite/pp/word.hpp`
- Word processing utilities
- Text tokenization

**wrap** - `xieite/pp/wrap.hpp`
- Value wrapping utilities
- Container encapsulation

**wrapped** - `xieite/pp/wrapped.hpp`
- Wrapper detection utilities
- Encapsulation checking

## X-Z

**XIEITE_ARROW** - Primary arrow macro
- Auto-deducing function definition
- Concise syntax for simple functions

**XIEITE_ARROW_NOEX** - No-except arrow macro
- Forces noexcept(true) specification
- Exception-safe function definition

See also: [Glossary](glossary.md) for term definitions, [Error Reference](errors.md) for troubleshooting, and [Compiler Support](compilers.md) for compatibility information.