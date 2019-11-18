#pragma once
#include <vector>

#include "Treasure.h"
#include "Pirate.h"
#include <array>
class IPlatform;

//constexpr int FIELD_WIDTH = 9;
//constexpr int FIELD_HEIGHT = 5;

using std::vector;
using std::pair;

typedef vector<vector<pair<size_t, size_t>>> Graph;

class World {
private:
    size_t sizeX;
    size_t sizeY;

    GameScreen gameField;
    size_t vertexCount;

private:
	void initGameField();
    vector<Entity> Neighbours(Entity);
    vector<Entity> Neighbours(size_t row, size_t col);
    size_t GetCellIndex(size_t x, size_t y);
    size_t GetCellIndex(Entity&);

    vector<size_t> Dijkstra(Graph &g, Entity &startPoint, Entity &endPoint);
    vector<Entity> ParentsToPath(vector<size_t> parents, Entity &startPoint, Entity &endPoint);
public:
	World();

	bool CheckWin();
    void Draw(IPlatform &platform);
    void DrawPath(IPlatform &platform, vector<Entity>);
    void DrawPathToTreasure(IPlatform &platform);
    void DrawScreen(IPlatform &platform, const GameScreen &screen, int startRow, int startCol);

    char GetCell(size_t row, size_t col);
    void ClearCell(size_t row, size_t col);
    void SetCell(size_t row, size_t col, char value);

    Graph fieldToGraph();
    vector<Entity> FindPathDijkstra(Entity &startPoint, Entity &endPoint);
    vector<Entity> FindPath(Entity &startPoit, Entity &endPoint);

public:
	Treasure treasure;
	Pirate pirate;

	Pirate enemyPirate;

    size_t width() { return sizeX; }
    size_t height() { return sizeY; }
};
