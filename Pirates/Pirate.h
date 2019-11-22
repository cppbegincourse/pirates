#pragma once
#include "stdafx.h"
#include "Entity.h"

class World;

constexpr char CELL_PIRATE = '@';
constexpr char CELL_ENEMY = '&';

constexpr int moveTimerInitial = 500;

struct Pirate : public Entity {
	void printCoords(std::string name) { std::cout << std::endl << name << ": [" << x << ", " << y << "]" << std::endl; };

	void Move(World & world, DirectionX dirX, DirectionY dirY);

	void Draw(World & world);

	void Update(int dt, World &world);

	Pirate(char type) : drawChar(type) {}

private:
	char drawChar;
	int moveTimer = moveTimerInitial;
};
