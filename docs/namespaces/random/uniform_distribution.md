# [xieite](../../xieite.md)\:\:[random](../../random.md)\:\:UniformDistribution\<\>
Defined in fragment [xieite:random.UniformDistribution](../../../src/random/uniform_distribution.cpp)

&nbsp;

## Description
A type alias to a uniform distribution for an integer, boolean, or floating point.

&nbsp;

## Synopsis
#### 1)
```cpp
template<xieite::concepts::Arithmetic Arithmetic>
using UniformDistribution = std::conditional_t<std::integral<Arithmetic>, std::conditional_t<std::same_as<Arithmetic, bool>, std::bernoulli_distribution, std::uniform_int_distribution<Arithmetic>>, std::uniform_real_distribution<Arithmetic>>;
```

&nbsp;

## Example
```cpp
import std;
import xieite;

int main() {
    using Foo = xieite::random::UniformDistribution<int>;
    using Bar = xieite::random::UniformDistribution<bool>;
    using Baz = xieite::random::UniformDistribution<double>;

    std::println("{}", xieite::concepts::SpecializationOf<Foo, std::uniform_int_distribution>);
    std::println("{}", std::same_as<Bar, std::bernoulli_distribution>);
    std::println("{}", xieite::concepts::SpecializationOf<Baz, std::uniform_real_distribution>);
}
```
Output:
```
true
true
true
```
