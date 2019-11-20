#pragma once
#include <cstdio>
#include <unordered_map>
#include <ostream>
#include <string>
#include <sstream>

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

    std::string toString() {
        std::stringstream ss;
        ss << "(" << x << ", " << y << ")";
        return ss.str();
    }

    size_t index() const {
        return y * worldSizeX + x;
    }

    static size_t worldSizeX;
};
