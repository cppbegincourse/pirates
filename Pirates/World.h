#pragma once
#include <vector>

#include "Treasure.h"
#include "Pirate.h"
#include <array>
class IPlatform;

constexpr int FIELD_WIDTH = 30;
constexpr int FIELD_HEIGHT = 30;

class World {
private:
    size_t sizeX;
    size_t sizeY;

    GameScreen gameField;

private:
	void initGameField();
public:
	World();

	bool CheckWin();
    void Draw(IPlatform &platform);
    void DrawScreen(IPlatform &platform, const GameScreen &screen, int startRow, int startCol);

    char GetCell(size_t row, size_t col);
    void ClearCell(size_t row, size_t col);
    void SetCell(size_t row, size_t col, char value);

public:
	Treasure treasure;
	Pirate pirate;

	Pirate enemyPirate;

    size_t width() { return sizeX; }
    size_t height() { return sizeY; }
};
