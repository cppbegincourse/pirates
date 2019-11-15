#pragma once
#include <vector>

#include "Treasure.h"
#include "Pirate.h"
#include <array>
class IPlatform;

constexpr int FIELD_WIDTH = 10;
constexpr int FIELD_HEIGHT = 10;

typedef std::array<std::array<char, FIELD_WIDTH>, FIELD_HEIGHT> GameFieldArray;

class World {
private:
	int sizeX;
	int sizeY;

	GameFieldArray gameField;

private:
	void initGameField();
public:
	World();

	bool CheckWin();
	void Draw(IPlatform &platform);

	char GetCell(int row, int col);
	void ClearCell(int row, int col);
	void SetCell(int row, int col, char value);

public:
	Treasure treasure;
	Pirate pirate;

	Pirate enemyPirate;

	int width() { return sizeX; };
	int height() { return sizeY; };
};
