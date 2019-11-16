#pragma once
#include <cstdio>

enum class DirectionY {
    UP = -1,
    NONE = 0,
    DOWN = 1,
};

enum class DirectionX {
    LEFT = -1,
    NONE = 0,
    RIGHT = 1
};

struct Entity {
    size_t x = 0;
    size_t y = 0;
};
