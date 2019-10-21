#include "Pirate.h"
#include "World.h"

void Pirate::MoveLeft(World & world)
{
	x--;
	if (x < 0) {
		x = world.width();
	}
}
void Pirate::MoveRight(World & world)
{
	x++;
	if (x > world.width()) {
		x = 0;
	}
}
void Pirate::MoveUp(World & world)
{
	y++;
	if (y > world.height()) {
		y = 0;
	}
}
void Pirate::MoveDown(World & world)
{
	y--;
	if (y < 0) {
		y = world.height();
	}
}