#pragma once

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
	int x = 0;
	int y = 0;
};
