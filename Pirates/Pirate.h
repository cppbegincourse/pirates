#pragma once

#include <string>
#include <iostream>

#include "Entity.h"

class World;

struct Pirate : public Entity {
	void printCoords(std::string name) { std::cout << std::endl << name << ": [" << x << ", " << y << "]" << std::endl; };

	void MoveLeft(World & world);
	void MoveRight(World & world);
	void MoveUp(World & world);
	void MoveDown(World & world);
};