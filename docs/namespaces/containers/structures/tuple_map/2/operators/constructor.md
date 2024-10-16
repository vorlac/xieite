# [xieite](../../../../../../xieite.md)\:\:[containers](../../../../../../containers.md)\:\:[TupleMap<Container, std::tuple<FirstKey, RestKeys...>, Value>](../../../../tuple_map.md)\:\:TupleMap\(\)
Defined in fragment [xieite:containers.TupleMap](../../../../../../../src/containers/tuple_map.cpp)

&nbsp;

## Description
Constructs a `xieite::containers::TupleMap`.

&nbsp;

## Synopsis
#### 1)
```cpp
constexpr TupleMap(std::initializer_list<std::pair<FirstKey, xieite::containers::TupleMap<std::tuple<RestKeys...>, Value>>> list = {}) noexcept;
```

&nbsp;

## Example
```cpp
import std;
import xieite;

int main() {
    using TupleMap = xieite::containers::TupleMap<std::unordered_map, std::tuple<int, char>, double>;

    TupleMap map = {
        { 5, {
            { 'h', 3.14159 },
            { '4', 2.71828 }
        } },
        { -23, {
            { 'L', 6.28318 },
            { ' ', 0.33333 }
        } }
    };

    std::println("{}", map[std::make_tuple(-23, 'L')]);
}
```
Output:
```
6.28318
```
