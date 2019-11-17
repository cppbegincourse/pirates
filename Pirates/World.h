#pragma once
#include <vector>

#include "Treasure.h"
#include "Pirate.h"
#include <array>
class IPlatform;

//constexpr int FIELD_WIDTH = 9;
//constexpr int FIELD_HEIGHT = 5;

class World {
private:
    size_t sizeX;
    size_t sizeY;

    GameScreen gameField;

private:
	void initGameField();
    std::vector<Entity> Neighbours(Entity);
public:
	World();

	bool CheckWin();
    void Draw(IPlatform &platform);
    void DrawPath(IPlatform &platform, std::vector<Entity>);
    void DrawPathToTreasure(IPlatform &platform);
    void DrawScreen(IPlatform &platform, const GameScreen &screen, int startRow, int startCol);

    char GetCell(size_t row, size_t col);
    void ClearCell(size_t row, size_t col);
    void SetCell(size_t row, size_t col, char value);

    std::vector<Entity> FindPath(Entity &startPoit, Entity &endPoint);

public:
	Treasure treasure;
	Pirate pirate;

	Pirate enemyPirate;

    size_t width() { return sizeX; }
    size_t height() { return sizeY; }
};
