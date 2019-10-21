#pragma once
#include <vector>

#include "Treasure.h"
#include "Pirate.h"

class World {
private:
	int sizeX;
	int sizeY;

	std::vector<std::vector<Entity>> gameField;
public:
	World(int width, int height);

	bool CheckWin();
public:
	Treasure treasure;
	Pirate pirate;

	Pirate enemyPirate;

	int width() { return sizeX; };
	int height() { return sizeY; };
};