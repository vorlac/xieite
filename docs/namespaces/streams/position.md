# [xieite](../../xieite.md)\:\:[streams](../../streams.md)\:\:Position \{\}
Defined in fragment [xieite:streams.Position](../../../src/streams/position.cpp)

&nbsp;

## Description
A class for storing a position in the terminal output buffer.

&nbsp;

## Synopsis
#### 1)
```cpp
struct Position {
    int row = 0;
    int column = 0;

    friend bool operator==(xieite::streams::Position, xieite::streams::Position) = default;
};
```
- row
- column

&nbsp;

## [Example](./structures/standard_handle/1/get_cursor_position.md)
