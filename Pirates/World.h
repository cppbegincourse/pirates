#pragma once
#include <vector>

#include "Treasure.h"
#include "Pirate.h"
#include <array>
#include <queue>

template<typename T, typename priority_t>
struct PriorityQueue {
  typedef std::pair<priority_t, T> PQElement;
  std::priority_queue<PQElement, std::vector<PQElement>,
                 std::greater<PQElement>> elements;

  inline bool empty() const {
     return elements.empty();
  }

  inline void put(T item, priority_t priority) {
    elements.emplace(priority, item);
  }

  T get() {
    T best_item = elements.top().second;
    elements.pop();
    return best_item;
  }
};

class IPlatform;

//constexpr int FIELD_WIDTH = 9;
//constexpr int FIELD_HEIGHT = 5;

using std::vector;
using std::pair;

typedef vector<vector<pair<size_t, size_t>>> Graph;

enum class PathfindingType {
    BFS, Dijkstra, AStar
};

class World {
private:
    size_t sizeX;
    size_t sizeY;

    GameScreen gameField;
    size_t vertexCount;

private:
	void initGameField();
    vector<Entity> Neighbours(Entity);
    vector<Entity> Neighbours(size_t index);
    size_t GetCellIndex(size_t x, size_t y);
    Entity CellByIndex(size_t index);

    vector<Entity> DijkstraImpl(Graph &g, Entity &startPoint, Entity &endPoint);
    vector<Entity> AStarImpl(Graph &g, Entity &startPoint, Entity &endPoint);
    vector<Entity> ParentsToPath(vector<size_t> &parents,  size_t startIndex, size_t endIndex);
    vector<Entity> ParentsToPath(vector<Entity> &parents, size_t startIndex, size_t endIndex);

    vector<Entity> FindPathAStar(Entity &startPoint, Entity &endPoint);
    vector<Entity> FindPathDijkstra(Entity &startPoint, Entity &endPoint);
    vector<size_t> FindPathBFS(Entity &startPoint, Entity &endPoint);
    size_t GetCost(Graph &g, size_t current, size_t next);

    size_t Heuristic(Entity &e1, Entity e2);
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
    vector<Entity> FindPath(Entity &startPoit, Entity &endPoint, PathfindingType type);

public:
	Treasure treasure;
	Pirate pirate;

	Pirate enemyPirate;

    size_t width() { return sizeX; }
    size_t height() { return sizeY; }
};
