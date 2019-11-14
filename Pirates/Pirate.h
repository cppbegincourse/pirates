#pragma once

#include <string>
#include <iostream>
#include "Entity.h"

class World;

struct Pirate : public Entity {
	void printCoords(std::string name) { std::cout << std::endl << name << ": [" << x << ", " << y << "]" << std::endl; };

	void Move(World & world, DirectionX dirX, DirectionY dirY);

	void Draw(World & world);
};
