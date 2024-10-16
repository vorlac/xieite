# [xieite](../../xieite.md)\:\:[functors](../../functors.md)\:\:counter\<\>\(\)
Defined in fragment [xieite:functors.counter](../../../src/functors/counter.cpp)

&nbsp;

## Description
A compile-time counter thingamabob. Technically not ill-formed ([yet](https://www.open-std.org/jtc1/sc22/wg21/docs/cwg_active.html#2118)) but causes wonky behavior if used in template constraints. In any case, this hack currently works on major compilers.

&nbsp;

## Synopsis
#### 1)
```cpp
template<auto tag = /* ... */, auto = [] {}>
[[nodiscard]] constexpr std::size_t counter() noexcept;
```

&nbsp;

## Example
```cpp
import std;
import xieite;

int main() {
    static constexpr std::size_t x = xieite::functors::counter();
    static constexpr std::size_t y = xieite::functors::counter();
    static constexpr std::size_t z = xieite::functors::counter();

    std::println("{} {} {}", x, y, z);
}
```
Output:
```
0 1 2
```
