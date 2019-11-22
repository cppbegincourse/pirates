#include "stdafx.h"
#include "Pirate.h"
#include "World.h"

void Pirate::Move(World& world, DirectionX dirX, DirectionY dirY)
{
    int nextX = x + static_cast<int>(dirX);
    int nextY = y + static_cast<int>(dirY);
	
	if (world.GetCell(nextY, nextX) != '*') {
		world.ClearCell(y, x);
		
		x = nextX;
		y = nextY;

        Draw(world);
	}
}

void Pirate::Update(int dt, World &world)
{
	moveTimer -= dt;

	if (moveTimer <= 0)
	{
		Pirate &enemy = world.enemyPirate;
		Pirate &pirate = world.pirate;

		auto path = world.FindPath(enemy, pirate, PathfindingType::AStar);
		if (path.size() != 0)
		{
			Entity nextCell = path.back();
			world.ClearCell(enemy.y, enemy.x);
			enemy.x = nextCell.x;
			enemy.y = nextCell.y;
		}

		moveTimer = moveTimerInitial;
	}
}

void Pirate::Draw(World &world)
{
	world.SetCell(y, x, drawChar);
}
