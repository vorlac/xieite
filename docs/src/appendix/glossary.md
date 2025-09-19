# Glossary

Comprehensive definitions of technical terms, concepts, and acronyms used throughout XIEITE documentation and codebase.

## A

**ABI (Application Binary Interface)**
The interface between compiled code modules, defining calling conventions, data layout, and symbol naming. XIEITE's header-only design minimizes ABI concerns but template instantiation can still affect binary compatibility.

**Arrow Macros**
XIEITE's signature feature providing concise function definition syntax:
- `XIEITE_ARROW(expr)`: Auto-deduces return type and noexcept specification
- `XIEITE_ARROW_NOEX(expr)`: Forces noexcept(true)
- `XIEITE_ARROW_RET(type, expr)`: Manual return type specification

**Arithmetic Type**
In XIEITE context, types satisfying `xieite::is_arith` concept: integral types (int, long, etc.) and floating-point types (float, double, etc.), excluding bool.

## B

**Branch Prediction**
CPU optimization where the processor predicts which conditional branches will be taken. XIEITE provides `XIEITE_LIKELY` and `XIEITE_UNLIKELY` macros for optimization hints.

**Build Configuration**
The set of compiler flags, definitions, and settings used to compile a project. XIEITE provides extensive platform and compiler detection for optimal configuration.

## C

**Compile-Time Computation**
Evaluation of expressions during compilation rather than runtime, using constexpr, consteval, and template metaprogramming. XIEITE emphasizes compile-time evaluation for zero-cost abstractions.

**Concept**
C++20 feature for constraining template parameters with named requirements. XIEITE extensively uses concepts like `is_arith`, `is_container`, etc.

**Conditional Compilation**
Including or excluding code based on preprocessor conditions. XIEITE's `XIEITE_PP_IF` macro enables sophisticated conditional compilation patterns.

**Cross-Platform**
Code that works across different operating systems and architectures. XIEITE provides extensive platform detection and abstraction utilities.

## D

**Duck Typing**
Programming concept where object suitability is determined by presence of methods/properties rather than explicit type declarations. XIEITE uses this concept in template constraints.

## E

**Expression Template**
Template metaprogramming technique for building complex expressions at compile-time. XIEITE uses this in mathematical and data manipulation utilities.

## F

**Fixed-Size Container**
Containers with compile-time determined size, such as `xieite::fixed_array`. These provide stack allocation and compile-time bounds checking.

**Function Object (Functor)**
Object that can be called like a function, including lambdas, function pointers, and classes with operator(). XIEITE's functional utilities work with various function objects.

## H

**Header-Only Library**
Library implemented entirely in header files, requiring no separate compilation. XIEITE is header-only, simplifying integration and enabling template optimizations.

## I

**Inline Namespace**
C++ feature allowing namespace members to be available in parent namespace. XIEITE uses inline namespaces for version management and API evolution.

**Instantiation**
The process of creating concrete functions or classes from templates. XIEITE's template-heavy design relies on efficient instantiation.

## L

**Link-Time Optimization (LTO)**
Compiler optimization performed across translation units during linking. XIEITE's header-only design works well with LTO for maximum performance.

## M

**Macro Hygiene**
Writing macros that don't interfere with surrounding code through name collisions or unexpected expansions. XIEITE macros follow hygiene best practices.

**Metaprogramming**
Programming where programs manipulate programs, often at compile-time. XIEITE provides extensive metaprogramming utilities in the `meta` category.

**MSVC (Microsoft Visual C++)**
Microsoft's C++ compiler and development environment. XIEITE provides specific support and workarounds for MSVC.

## N

**Named Parameter Idiom**
Design pattern using method chaining for readable parameter specification. Some XIEITE utilities employ this pattern.

**NTTP (Non-Type Template Parameter)**
Template parameters that are values rather than types, such as `template<int N>`. XIEITE uses NTTPs for compile-time configuration.

## O

**ODR (One Definition Rule)**
C++ rule requiring entities to have exactly one definition across all translation units. Header-only libraries like XIEITE must carefully manage ODR compliance.

## P

**Platform Detection**
Determining the target operating system, architecture, and compiler at compile-time. XIEITE provides comprehensive platform detection in the `pp` category.

**Preprocessor**
Tool that processes source code before compilation, handling macros, includes, and conditional compilation. XIEITE's `pp` category provides 67 preprocessor utilities.

**Profile-Guided Optimization (PGO)**
Optimization technique using runtime profiling data to guide compiler optimizations. XIEITE supports PGO configuration in build systems.

## Q

**QSFINAE (Quirky SFINAE)**
Subtle SFINAE patterns that behave differently across compilers. XIEITE prefers concepts over complex SFINAE for better portability.

## R

**RAII (Resource Acquisition Is Initialization)**
C++ idiom where resource lifetime is tied to object lifetime. XIEITE's scope guards and containers follow RAII principles.

**Range-Based For Loop**
C++11 feature for iterating over containers: `for (auto& item : container)`. XIEITE containers support range-based iteration.

## S

**SFINAE (Substitution Failure Is Not An Error)**
Template technique where failed substitutions don't cause compilation errors. XIEITE provides SFINAE helpers but prefers concepts for constraints.

**Scope Guard**
RAII utility that executes cleanup code when leaving scope. XIEITE provides `scope_guard` in the `fn` category.

**Static Assertion**
Compile-time assertion using `static_assert`. XIEITE utilities include comprehensive static assertions for type safety.

**STL (Standard Template Library)**
C++ standard library providing containers, algorithms, and utilities. XIEITE integrates well with STL and extends its functionality.

## T

**Template Metaprogramming**
Using templates to perform computations at compile-time. XIEITE's `meta` category provides utilities for template manipulation and type-level programming.

**Template Specialization**
Providing specific implementations for particular template arguments. XIEITE uses specialization for optimization and platform-specific behavior.

**Type Trait**
Template that provides information about types at compile-time. XIEITE's `trait` category includes 89 type traits and concepts.

**TMP (Template Metaprogramming)**
See Template Metaprogramming.

## U

**UB (Undefined Behavior)**
C++ behavior not specified by the standard, potentially causing unpredictable results. XIEITE utilities are designed to avoid UB through careful implementation.

**Universal Reference**
Template parameter using `T&&` that can bind to both lvalue and rvalue references. XIEITE utilities use universal references for perfect forwarding.

## V

**Variadic Template**
Template accepting variable number of arguments using `...` syntax. XIEITE extensively uses variadic templates for flexible interfaces.

**VTABLE**
Virtual function table used for dynamic dispatch. XIEITE prefers compile-time polymorphism but supports virtual interfaces where needed.

## X

**XIEITE**
Modern C++ utility library emphasizing template metaprogramming, cross-platform compatibility, and compile-time computation. Name pronunciation: "ZEE-eh-tay" or "SHEE-eh-tay".

**XIEITE_ARROW**
Primary arrow macro for concise function definitions with automatic return type deduction and noexcept specification.

## Z

**Zero-Cost Abstraction**
Abstraction that doesn't add runtime overhead compared to hand-written code. XIEITE achieves zero-cost abstractions through compile-time evaluation and template optimization.

## Common Abbreviations

**ADL**: Argument-Dependent Lookup
**CRTP**: Curiously Recurring Template Pattern
**CTAD**: Class Template Argument Deduction
**CV**: Const-Volatile (type qualifiers)
**CWRU**: Case-Western Reserve University (context-dependent)
**EBCO**: Empty Base Class Optimization
**EBO**: Empty Base Optimization
**IFNDR**: Ill-Formed No Diagnostic Required
**NRVO**: Named Return Value Optimization
**OBRM**: Owning-Based Resource Management
**POD**: Plain Old Data
**RVO**: Return Value Optimization
**TOCTTOU**: Time-Of-Check Time-Of-Use

## Symbol Conventions

**snake_case**: XIEITE naming convention for functions, variables, and concepts
**UPPER_CASE**: Macro and constant naming convention
**PascalCase**: Legacy concept names (deprecated in favor of snake_case)
**camelCase**: Generally avoided in XIEITE in favor of snake_case

## Compiler-Specific Terms

**Clang**: LLVM-based C++ compiler with excellent C++20 support
**GCC**: GNU Compiler Collection, traditional Unix C++ compiler
**MinGW**: Minimalist GNU for Windows, provides GCC on Windows
**MSVC**: Microsoft Visual C++, Windows-native compiler

## Build System Terms

**CMake**: Cross-platform build system generator used with XIEITE
**Ninja**: Fast build system often used as CMake backend
**MSBuild**: Microsoft's build system for Visual Studio projects
**Make**: Traditional Unix build system

## Performance Terms

**Cache Line**: Unit of cache coherency, typically 64 bytes
**SIMD**: Single Instruction, Multiple Data parallel processing
**Vectorization**: Converting scalar operations to vector operations
**IPC**: Instructions Per Cycle, measure of CPU efficiency
**CPI**: Cycles Per Instruction, inverse of IPC

This glossary provides essential terminology for understanding and effectively using XIEITE in C++ development projects.