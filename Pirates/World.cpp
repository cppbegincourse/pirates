#include "stdafx.h"
#include "World.h"
#include <iostream>
#include "iplatform.h"

using namespace std;

constexpr char CELL_EMPTY = ' ';
constexpr char CELL_WALL = '*';

size_t random(size_t min, size_t max) {
    size_t rnd = static_cast<size_t>(rand());
	return rnd % (max - min) + min;
}

World::World() :
    sizeX(FIELD_WIDTH), sizeY(FIELD_HEIGHT),
    gameField(FIELD_HEIGHT)
{
	//srand(unsigned(std::time(0)));

	pirate.x = 2;
	pirate.y = 2;

    treasure.x = random(1, sizeX - 2);
    treasure.y = random(1, sizeY - 2);

    enemyPirate.x = random(1, sizeX - 2);
    enemyPirate.y = random(1, sizeY - 2);

	initGameField();
}


char World::GetCell(size_t row, size_t col) {
	return gameField[row][col];
}

void World::ClearCell(size_t row, size_t col) {
	gameField[row][col] = CELL_EMPTY;
}

void World::SetCell(size_t row, size_t col, char value) {
	gameField[row][col] = value;
}

void World::initGameField()
{
    gameField[0] = string(sizeX, CELL_WALL);
    gameField[sizeY - 1] = string(sizeX, CELL_WALL);

    for (size_t i = 1; i < sizeY - 1; ++i) {
        gameField[i] = string(sizeX, CELL_EMPTY);
        gameField[i][0] = CELL_WALL;
        gameField[i][sizeX - 1] = CELL_WALL;
    }

    gameField[pirate.y][pirate.x] = '@';
    gameField[enemyPirate.y][enemyPirate.x] = '&';
    gameField[treasure.y][treasure.x] = 'x';
}

bool World::CheckWin()
{
	if (treasure.x == pirate.x && treasure.y == pirate.y) {
        //cout << "You've found the treasure!" << endl;
		return true;
	}

	return false;
}

void World::Draw(IPlatform &platform)
{
    platform.ClearScreen();

    DrawScreen(platform, gameField, 0, 0);

#ifdef PLATFORM_CURSES
    platform.DrawRow("Press q for exit", FIELD_HEIGHT + 2, 2);
#endif
}

void World::DrawScreen(IPlatform &platform, const GameScreen &screen, int startRow, int startCol)
{
    int rowIndex = 0;
    for (const std::string &row : screen) {
        platform.DrawRow(row.c_str(), rowIndex + startRow, startCol);
        ++rowIndex;
    }

	platform.EndDraw();
}
