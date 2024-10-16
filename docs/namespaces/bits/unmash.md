# [xieite](../../xieite.md)\:\:[bits](../../bits.md)\:\:unmash\<\>\(\)
Defined in fragment [xieite:bits.unmash](../../../src/bits/unmash.cpp)

&nbsp;

## Description
"Unmashes" one `std::bitset` apart into multiple integers of specified sizes (I couldn't think of a better function name)

&nbsp;

## Synopsis
#### 1)
```cpp
template<std::size_t... sizes, std::size_t bits>
requires(bits >= (... + sizes))
[[nodiscard]] constexpr std::tuple<xieite::types::LeastInteger<sizes>...> unmash(std::bitset<bits> value) noexcept;
```
#### 2)
```cpp
template<std::integral Integral, std::size_t... sizes, std::size_t bits>
requires(bits >= (... + sizes))
[[nodiscard]] constexpr std::array<Integral, sizeof...(sizes)> unmash(std::bitset<bits> value) noexcept;
```

&nbsp;

## Example
```cpp
import std;
import xieite;

int main() {
    std::bitset<12> foo = 0b011000111101;
    auto bar = xieite::bits::unmash<3, 9>(foo);

    std::println("{}", std::get<0>(bar));
    std::println("{}", std::get<1>(bar));
}
```
Output:
```
5
199
```
