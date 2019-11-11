#include "Pirate.h"

constexpr char CELL_PIRATE = '@';

void Pirate::Move(World & world, DirectionX dirX, DirectionY dirY)
{
	int nextX = x + (int)dirX;
	int nextY = y + (int)dirY;
	
	if (world.GetCell(nextY, nextX) != '*') {
		world.ClearCell(y, x);
		
		x = nextX;
		y = nextY;

		Draw(world);
	}
}

void Pirate::Draw(World &world) {
	world.SetCell(y, x, CELL_PIRATE);
}