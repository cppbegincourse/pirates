#include "World.h"
#include <iostream>
#define PDC_DLL_BUILD
#include "curses.h"
using namespace std;

constexpr char CELL_EMPTY = ' ';
constexpr char CELL_WALL = '*';

unsigned int random(unsigned int min, unsigned int max) {
	unsigned int rnd = static_cast<unsigned int>(rand());
	return rnd % (max - min) + min;
}

World::World() :
	sizeX(FIELD_WIDTH), sizeY(FIELD_HEIGHT)
{
	//srand(unsigned(std::time(0)));

	pirate.x = 2;
	pirate.y = 2;

	treasure.x = random(1, sizeX - 1);
	treasure.y = random(1, sizeY - 1);

	enemyPirate.x = random(1, sizeX - 1);
	enemyPirate.y = random(1, sizeY - 1);

	initGameField();
}


char World::GetCell(int row, int col) {
	return gameField[row][col];
}

void World::ClearCell(int row, int col) {
	gameField[row][col] = CELL_EMPTY;
}

void World::SetCell(int row, int col, char value) {
	gameField[row][col] = value;
}

char World::GetCell(int row, int col) {
	return gameField[row][col];
}

void World::initGameField()
{
		for (GameFieldArray::size_type i = 0; i < sizeY; ++i) {
			gameField[i][sizeX - 1] = '\0';
		}

		for (GameFieldArray::size_type i = 0; i < sizeX - 1; ++i) {
			gameField[0][i] = CELL_WALL;
			gameField[sizeY - 1][i] = CELL_WALL;
		}

		for (GameFieldArray::size_type i = 1; i < sizeY - 1; ++i) {
			gameField[i][0] = CELL_WALL;
			gameField[i][sizeX - 2] = CELL_WALL;

			for (GameFieldArray::size_type j = 1; j < sizeX - 2; ++j) {
				gameField[i][j] = CELL_EMPTY;
			}
		}

		gameField[pirate.y][pirate.x] = '@';
		gameField[enemyPirate.y][enemyPirate.x] = '&';
		gameField[treasure.y][treasure.x] = 'x';
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


void World::Draw()
{
	// Draw field itself
	for (GameFieldArray::size_type i = 0; i < sizeY; ++i) {
		const char* fieldStr = gameField[i].data();
		mvprintw(static_cast<int>(i), 0, fieldStr);
	}

	refresh();
}