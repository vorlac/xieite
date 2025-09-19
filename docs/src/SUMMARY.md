# Summary

[Introduction](README.md)

# Part I: Core Architecture & Design Philosophy

- [Architecture Overview](architecture/README.md)
  - [Library Architecture](architecture/overview.md)
  - [Header-Only Design](architecture/header_only.md)
  - [Namespace Organization](architecture/namespace.md)
  - [Build System Integration](architecture/build_system.md)

- [Macro System Deep Dive](architecture/macro_system.md)
  - [Arrow Macro Family](architecture/arrow_macros.md)
    - [XIEITE_ARROW](architecture/arrow/arrow.md)
    - [XIEITE_ARROW_NOEX](architecture/arrow/arrow_noex.md)
    - [XIEITE_ARROW_RET](architecture/arrow/arrow_ret.md)
    - [XIEITE_ARROW_IF](architecture/arrow/arrow_if.md)
    - [XIEITE_ARROW_CHOOSE](architecture/arrow/arrow_choose.md)
    - [XIEITE_ARROW_TRY](architecture/arrow/arrow_try.md)
    - [XIEITE_ARROW_DECL](architecture/arrow/arrow_decl.md)
    - [XIEITE_ARROW_CTOR](architecture/arrow/arrow_ctor.md)
  - [Preprocessor Patterns](architecture/preprocessor_patterns.md)
  - [Token Manipulation](architecture/token_manipulation.md)

- [Template Metaprogramming](architecture/template_patterns.md)
  - [Concept-Based Design](architecture/concepts.md)
  - [SFINAE Patterns](architecture/sfinae.md)
  - [Compile-Time Computation](architecture/compile_time.md)
  - [Type Traits Architecture](architecture/type_traits_arch.md)

# Part II: Category Deep Dives

- [Categories Overview](categories/README.md)

## Preprocessor Utilities (`pp`)

- [Preprocessor Overview](categories/pp/README.md)
  - [Core Arrow Macros](categories/pp/arrow.md)
  - [Conditional Compilation](categories/pp/conditional.md)
    - [Platform Detection](categories/pp/platform.md)
    - [Architecture Detection](categories/pp/arch.md)
    - [Compiler Detection](categories/pp/compiler.md)
  - [Boolean Operations](categories/pp/boolean.md)
  - [Token Operations](categories/pp/tokens.md)
  - [String Manipulation](categories/pp/strings.md)
  - [Utility Macros](categories/pp/utilities.md)
  - [Debug Macros](categories/pp/debug.md)
  - [Version Detection](categories/pp/version.md)

## Type Traits (`trait`)

- [Type Traits Overview](categories/trait/README.md)
  - [Concepts Library](categories/trait/concepts.md)
    - [Type Classification](categories/trait/classification.md)
    - [Type Properties](categories/trait/properties.md)
    - [Type Relationships](categories/trait/relationships.md)
  - [Type Modification](categories/trait/modification.md)
    - [Reference Modifiers](categories/trait/references.md)
    - [CV Qualifiers](categories/trait/cv_qualifiers.md)
    - [Pointer Operations](categories/trait/pointers.md)
  - [Advanced Traits](categories/trait/advanced.md)
    - [Function Traits](categories/trait/functions.md)
    - [Template Detection](categories/trait/templates.md)
    - [SFINAE Helpers](categories/trait/sfinae_helpers.md)
  - [Standard Extensions](categories/trait/std_extensions.md)

## Mathematics (`math`)

- [Mathematics Overview](categories/math/README.md)
  - [Arithmetic Operations](categories/math/arithmetic.md)
  - [Advanced Math](categories/math/advanced.md)
    - [Trigonometry](categories/math/trigonometry.md)
    - [Logarithms](categories/math/logarithms.md)
    - [Powers & Roots](categories/math/powers.md)
  - [Statistical Functions](categories/math/statistics.md)
  - [Numeric Algorithms](categories/math/algorithms.md)
  - [Precision & Rounding](categories/math/precision.md)
  - [Constants & Limits](categories/math/constants.md)
  - [Geometric Utilities](categories/math/geometry.md)
  - [Random Numbers](categories/math/random.md)

## Data Structures (`data`)

- [Data Structures Overview](categories/data/README.md)
  - [Fixed Containers](categories/data/fixed_containers.md)
  - [String Utilities](categories/data/strings.md)
  - [Compile-Time Structures](categories/data/compile_time.md)
  - [Iterator Utilities](categories/data/iterators.md)
  - [Container Algorithms](categories/data/algorithms.md)
  - [Memory Management](categories/data/memory.md)
  - [Range Operations](categories/data/ranges.md)

## Functional Programming (`fn`)

- [Functional Overview](categories/fn/README.md)
  - [Function Composition](categories/fn/composition.md)
  - [Currying & Partial Application](categories/fn/currying.md)
  - [Combinators](categories/fn/combinators.md)
  - [Memoization](categories/fn/memoization.md)
  - [Scope Guards](categories/fn/scope_guards.md)
  - [Process Management](categories/fn/process.md)
  - [User-Defined Literals](categories/fn/literals.md)

## Metaprogramming (`meta`)

- [Metaprogramming Overview](categories/meta/README.md)
  - [Template Manipulation](categories/meta/templates.md)
  - [Type Lists](categories/meta/type_lists.md)
  - [Compile-Time Sequences](categories/meta/sequences.md)
  - [Substitution Detection](categories/meta/substitution.md)
  - [Repetition & Generation](categories/meta/generation.md)
  - [Pack Operations](categories/meta/packs.md)

## System Utilities (`sys`)

- [System Overview](categories/sys/README.md)
  - [Platform Detection](categories/sys/platform.md)
  - [Environment Variables](categories/sys/environment.md)
  - [OS-Specific Features](categories/sys/os_specific.md)
  - [Architecture Info](categories/sys/architecture.md)
  - [Endianness](categories/sys/endianness.md)
  - [System Information](categories/sys/info.md)

## Input/Output (`io`)

- [I/O Overview](categories/io/README.md)
  - [Stream Utilities](categories/io/streams.md)
  - [Formatting](categories/io/formatting.md)
  - [Debug Output](categories/io/debug.md)
  - [File Operations](categories/io/files.md)
  - [Scanning & Parsing](categories/io/parsing.md)

# Part III: Advanced Patterns & Best Practices

- [Advanced Usage](advanced/README.md)
  - [Complex Patterns](advanced/complex_patterns.md)
  - [Performance Optimization](advanced/performance.md)
  - [Compile-Time vs Runtime](advanced/compile_runtime.md)
  - [Error Handling](advanced/error_handling.md)
  - [STL Integration](advanced/stl_integration.md)

- [Cross-Platform Development](advanced/cross_platform.md)
  - [Platform Branching](advanced/platform_branching.md)
  - [Compiler Workarounds](advanced/compiler_workarounds.md)
  - [ABI Compatibility](advanced/abi.md)
  - [Build Configuration](advanced/build_config.md)

# Examples

- [Examples Overview](examples/README.md)
  - [Basic Usage](examples/basic/README.md)
    - [Getting Started](examples/basic/getting_started.md)
    - [Simple Utilities](examples/basic/simple_utilities.md)
    - [Common Patterns](examples/basic/common_patterns.md)
  - [Advanced Examples](examples/advanced/README.md)
    - [Template Metaprogramming](examples/advanced/templates.md)
    - [Compile-Time Computation](examples/advanced/compile_time.md)
    - [Custom Type Traits](examples/advanced/custom_traits.md)
  - [Integration Examples](examples/integration/README.md)
    - [CMake Integration](examples/integration/cmake.md)
    - [Real-World Application](examples/integration/application.md)
    - [Performance Benchmarks](examples/integration/benchmarks.md)

# Complete Example Projects

- [Complete Projects Overview](projects/README.md)
  - [Basic Usage Example](examples/basic_usage.md)
  - [Advanced Template Metaprogramming](examples/advanced_templates.md)
  - [Real-World Integration](examples/integration_example.md)

# API Reference

- [Complete API Reference](reference/README.md)
  - [Preprocessor API](reference/api/pp.md)
  - [Type Traits API](reference/api/trait.md)
  - [Mathematics API](reference/api/math.md)
  - [Data Structures API](reference/api/data.md)
  - [Functional API](reference/api/fn.md)
  - [Metaprogramming API](reference/api/meta.md)
  - [System API](reference/api/sys.md)
  - [I/O API](reference/api/io.md)

# Appendices

- [Appendices](appendix/README.md)
  - [Error Reference](appendix/errors.md)
  - [Compiler Support](appendix/compilers.md)
  - [Performance Notes](appendix/performance.md)
  - [Glossary](appendix/glossary.md)
  - [Index](appendix/index.md)
