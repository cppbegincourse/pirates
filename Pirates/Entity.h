#pragma once
#include <cstdio>
#include <unordered_map>

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

    Entity() : x(0), y(0){}
    Entity (size_t x, size_t y) : x(x), y(y){}
    //bool operator==(const Entity &e) { return (x == e.x && y == e.y); }
    //bool operator!=(const Entity &e) { return !(*this == e);}
};
