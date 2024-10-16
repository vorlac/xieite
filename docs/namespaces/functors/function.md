# [xieite](../../xieite.md)\:\:[functors](../../functors.md)\:\:Function\<\> \{\}
Defined in fragment [xieite:functors.Function](../../../src/functors/function.cpp)

&nbsp;

## Description
`std::function` but constexpr.

&nbsp;

## Synopsis
#### 1)
```cpp
template<typename>
struct Function;
```
#### 2)
```cpp
template<typename Return, typename... Arguments>
struct Function<Return(Arguments...)> {
    Function() = default;

    explicit(false) constexpr Function(const Function&) noexcept;

    template<xieite::concepts::Invocable<Return(Arguments...)> Functor>
    requires(!std::same_as<std::remove_cvref_t<Functor>, Function>)
    explicit(false) constexpr Function(Functor&&) noexcept;

    explicit constexpr operator bool() const noexcept;

    template<typename... ArgumentReferences>
    requires((... && std::convertible_to<ArgumentReferences, Arguments>))
    constexpr Return operator()(ArgumentReferences&&...) const noexcept(false);
};
```
- [Function\<\>\(\)](./structures/function/2/operators/constructor.md)
- [operator typename\(\)](./structures/function/2/operators/cast.md)
- [operator\(\)\<\>\(\)](./structures/function/2/operators/call.md)

&nbsp;

## Example
```cpp
import std;
import xieite;

int add(int a, int b) {
    return a + b;
}

int main() {
    xieite::functors::Function<int(int, int)> foo = &add;

    int x = 4;
    xieite::functors::Function<int(int)> bar = [&x](int a) {
        return a * x;
    };

    xieite::functors::Function<int()> baz = [i = 0] mutable {
        return i++;
    };

    xieite::functors::Function<int()> qux = baz;

    std::println("{}", foo(1, 2));
    std::println("{}", bar(3));
    std::println("{}", baz());
    std::println("{}", baz());
    std::println("{}", qux());
}
```
Output:
```
3
12
0
1
0
```
