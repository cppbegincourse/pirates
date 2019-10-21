#include "World.h"
#include <iostream>

using namespace std;

World::World(int width, int height) :
	sizeX(width), sizeY(height)
{
	//srand(unsigned(std::time(0)));

	treasure.x = rand() % width;
	treasure.y = rand() % height;

	enemyPirate.x = rand() % width;
	enemyPirate.y = rand() % height;
}

bool World::CheckWin()
{
	if (treasure.x == pirate.x && treasure.y == pirate.y) {
		cout << "You've found the treasure!" << endl;
		return true;
	}
	else {
		cout << "Not here, looser" << endl;
	}

	return false;
}