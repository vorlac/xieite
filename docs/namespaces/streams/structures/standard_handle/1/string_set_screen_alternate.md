# [xieite](../../../../../xieite.md)\:\:[streams](../../../../../streams.md)\:\:[StandardHandle](../../../standard_handle.md)\:\:stringSetScreenAlternate\(\)
Defined in fragment [xieite:streams.StandardHandle](../../../../../../src/streams/standard_handle.cpp)

&nbsp;

## Description
Returns a string which enables or disables the alternate screen when printed.

&nbsp;

## Synopsis
#### 1)
```cpp
[[nodiscard]] static constexpr std::string stringSetScreenAlternate(bool value) noexcept;
```

&nbsp;

## Example
```cpp
import std;
import xieite;

int main() {
    std::string on = xieite::streams::StandardHandle::stringSetScreenAlternate(true);
    std::string off = xieite::streams::StandardHandle::stringSetScreenAlternate(false);

    std::string message = on + "Hello, " + off + "world!";

    std::println("{}", message);
}
```
Possible output:
```
world!
```
