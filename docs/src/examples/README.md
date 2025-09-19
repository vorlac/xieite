# Examples Overview

## Introduction

This section provides comprehensive examples demonstrating how to effectively use XIEITE's utilities in real-world scenarios. The examples are organized by complexity and use case, progressing from simple utility usage to advanced template metaprogramming patterns and complete application integration.

## Example Categories

### [Basic Usage](./basic/README.md)

The basic examples introduce fundamental XIEITE utilities and common usage patterns:

- **[Getting Started](./basic/getting_started.md)** - Your first steps with XIEITE
- **[Simple Utilities](./basic/simple_utilities.md)** - Common utility functions and their applications
- **[Common Patterns](./basic/common_patterns.md)** - Frequently used programming patterns with XIEITE

### [Advanced Examples](./advanced/README.md)

Advanced examples showcase complex template metaprogramming and specialized techniques:

- **[Template Metaprogramming](./advanced/templates.md)** - Advanced template patterns and techniques
- **[Compile-Time Examples](./advanced/compile_time.md)** - Compile-time computation and optimization
- **[Custom Traits](./advanced/custom_traits.md)** - Building custom type traits and concepts

### [Integration Guide](./integration/README.md)

Integration examples demonstrate how to incorporate XIEITE into larger projects:

- **[CMake Integration](./integration/cmake.md)** - Build system integration patterns
- **[Real Application](./integration/application.md)** - Complete application example
- **[Performance Benchmarks](./integration/benchmarks.md)** - Performance analysis and optimization

## Learning Path

We recommend following this progression when learning XIEITE:

1. **Start with [Getting Started](./basic/getting_started.md)** to understand the basic concepts and setup
2. **Explore [Simple Utilities](./basic/simple_utilities.md)** to see common use cases
3. **Learn [Common Patterns](./basic/common_patterns.md)** for practical programming techniques
4. **Advance to [Template Metaprogramming](./advanced/templates.md)** for sophisticated techniques
5. **Study [Compile-Time Examples](./advanced/compile_time.md)** for performance optimization
6. **Review [Integration Guide](./integration/README.md)** for production usage

## Code Examples Philosophy

All examples in this documentation follow these principles:

### Forensic Accuracy
- Every example is verified against actual XIEITE implementations
- Code samples include specific file and line references where applicable
- No assumptions are made about functionality not directly verified

### Progressive Complexity
- Examples build on previously introduced concepts
- Each section increases in complexity and sophistication
- Advanced examples reference and extend basic patterns

### Real-World Applicability
- Examples demonstrate practical use cases, not just syntax
- Code samples solve actual programming problems
- Integration examples show production-ready patterns

### Modern C++ Best Practices
- All examples use C++20 features where appropriate
- Code follows modern C++ idioms and conventions
- Examples demonstrate both compile-time and runtime efficiency

## Example Code Structure

Each example follows a consistent structure:

```cpp
// 1. Required includes with specific XIEITE headers
#include <xieite/category/utility.hpp>

// 2. Clear problem statement or use case
void demonstrate_feature() {
    // 3. Step-by-step implementation with comments

    // 4. Expected output or behavior

    // 5. Variations and alternatives
}

// 6. Complete runnable example when possible
int main() {
    demonstrate_feature();
    return 0;
}
```

## Categories by XIEITE Module

### Preprocessor (pp) Examples
- Arrow macro usage patterns
- Conditional compilation techniques
- Platform detection and branching
- Custom macro development

### Type Traits (trait) Examples
- Concept definitions and usage
- Custom trait implementations
- SFINAE patterns with concepts
- Type classification and queries

### Mathematics (math) Examples
- Compile-time mathematical computations
- Numeric algorithms and optimizations
- Statistical and geometric calculations
- Precision and overflow handling

### Data Structures (data) Examples
- Fixed-size container usage
- Compile-time string manipulation
- Iterator patterns and algorithms
- Memory management techniques

### Functional Programming (fn) Examples
- Function composition and currying
- Memoization and optimization
- Combinator patterns
- Scope guards and RAII

### Metaprogramming (meta) Examples
- Template manipulation techniques
- Compile-time sequence generation
- Type list operations
- Substitution failure detection

### System Utilities (sys) Examples
- Cross-platform development patterns
- System information queries
- Architecture and platform detection
- Performance monitoring

### Input/Output (io) Examples
- Advanced formatting techniques
- Terminal control and interaction
- File operation patterns
- Debug output strategies

## Running the Examples

### Prerequisites
- C++20 compatible compiler (GCC 10+, Clang 12+, MSVC 2022+)
- CMake 3.20 or later
- XIEITE library headers

### Building Examples
```bash
# Clone and build
git clone https://github.com/Eczbek/xieite.git
cd xieite/examples

# Configure with CMake
cmake -B build -S . -DCMAKE_CXX_STANDARD=20

# Build all examples
cmake --build build

# Run specific example
./build/basic_example
```

### Individual Example Compilation
```bash
# Compile individual examples
g++ -std=c++20 -I../include example.cpp -o example

# With optimizations
g++ -std=c++20 -O3 -I../include example.cpp -o example
```

## Example Categories Deep Dive

### Performance-Focused Examples
Many examples emphasize compile-time computation and zero-runtime-cost abstractions:
- Compile-time string processing
- Template-based algorithm unrolling
- Constexpr mathematical computations
- Zero-overhead type manipulations

### Cross-Platform Examples
Platform compatibility examples demonstrate:
- Conditional compilation patterns
- Architecture-specific optimizations
- Endianness handling
- Platform detection usage

### Integration Examples
Real-world integration patterns cover:
- Library integration with existing codebases
- Build system configuration
- Header organization strategies
- Namespace management

## Contributing Examples

When contributing new examples:

1. **Verify functionality** against current XIEITE implementation
2. **Include source references** to specific header files and line numbers
3. **Test on multiple compilers** to ensure portability
4. **Document expected behavior** clearly
5. **Follow established code style** and organization

## Troubleshooting Common Issues

### Compilation Errors
- Ensure C++20 standard is enabled
- Verify XIEITE headers are in include path
- Check compiler support for used features

### Template Instantiation Issues
- Review concept requirements for type constraints
- Verify template argument deduction patterns
- Check for SFINAE-related substitution failures

### Performance Concerns
- Profile compile-time vs runtime characteristics
- Review template instantiation depth
- Consider explicit instantiation for frequently used patterns

## See Also

- [Architecture Overview](../architecture/README.md) - Understanding XIEITE's design
- [Category Documentation](../categories/README.md) - Detailed utility reference
- [API Reference](../reference/README.md) - Complete API documentation