#include "stdafx.h"
#include "World.h"
#include <iostream>
#include "iplatform.h"
#include <map>
#include <queue>
#include <set>
#include <ctime>
#include "logstream.h"
#include <queue>
#include <cmath>

using namespace std;

constexpr char CELL_EMPTY = ' ';
constexpr char CELL_WALL = '*';
constexpr char CELL_TREASURE = 'x';

constexpr int INF = 1000000000;

size_t Entity::worldSizeX;

size_t random(size_t min, size_t max) {
    size_t rnd = static_cast<size_t>(rand());
	return rnd % (max - min) + min;
}

int operator< (const Entity &e1, const Entity &e2) {
    return e1.index() < e2.index();
}

World::World()
	: pirate(CELL_PIRATE)
	, enemyPirate(CELL_ENEMY)

{
	srand(unsigned(std::time(0)));

	initGameField();

	if (pirate.x == 0 && pirate.y == 0)
	{
		pirate.x = random(1, sizeX - 1);
		pirate.y = random(1, sizeY - 1);
	}

	if (treasure.x == 0 && treasure.y == 0)
	{
		treasure.x = random(1, sizeX - 1);
		treasure.y = random(1, sizeY - 1);
	}

    enemyPirate.x = random(1, sizeX - 1);
    enemyPirate.y = random(1, sizeY - 1);
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
	string line;
    ifstream lvlFileStream("level.txt");

    size_t row = 0;
    auto findAndSet = [&row](Entity &e, char entityChar, string &line) {
        size_t col;
        if ((col = line.find(entityChar)) != string::npos) {
            e.x = col;
            e.y = row;
        }
    };

	if (lvlFileStream.is_open())
	{
		while (getline(lvlFileStream, line)) {
			gameField.push_back(line);
            findAndSet(treasure, CELL_TREASURE, line);
            findAndSet(pirate, CELL_PIRATE, line);
			++row;
		}

		sizeY = gameField.size();
		sizeX = gameField[0].length();

        Entity::worldSizeX = sizeX;
	}
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

	pirate.Draw(*this);
	enemyPirate.Draw(*this);

#ifdef PLATFORM_CURSES
    platform.DrawRow("Press q for exit", sizeY + 2, 2);
    platform.DrawRow("Press p to show path to treasure", sizeY + 3, 2);
#endif

	platform.EndDraw();
}

void World::DrawScreen(IPlatform &platform, const GameScreen &screen, int startRow, int startCol)
{
    int rowIndex = 0;
    for (const std::string row : screen) {
        platform.DrawRow(row.c_str(), rowIndex + startRow, startCol);
        ++rowIndex;
    }

	platform.EndDraw();
}

void World::DrawPath(IPlatform &platform, std::vector<Entity> path)
{
    for (auto point : path) {
        platform.DrawSprite('.', point.y, point.x);
    }

    platform.EndDraw();
}

void World::DrawPathToTreasure(IPlatform &platform)
{
    vector<Entity> path = FindPath(pirate, treasure, PathfindingType::AStar);
	//vector<Entity> path = FindPath(pirate, treasure);
    DrawPath(platform, path);
}

vector<Entity> World::Neighbours(size_t index)
{
    Entity currCell = CellByIndex(index);
    size_t row = currCell.y;
    size_t col = currCell.x;
    vector<Entity> tmp;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            char candidate = gameField[row + j][col + i];
            // Diagonal movement is not allowed
            if(i != j && i != -j
                    // Check that cell is not Wall
                    && candidate != CELL_WALL)
            {
                tmp.push_back(Entity(col + i, row + j));
            }
        }
    }

    return tmp;
}

vector<Entity> World::Neighbours(Entity cell)
{
    return Neighbours(cell.index());
}

size_t World::GetCost(Graph &g, size_t current, size_t next)
{
    auto &neigbours = g[current];
    for(auto &neigbour : neigbours) {
        if (neigbour.first == next)
            return neigbour.second;
    }

    return INF;
}

bool operator==(const Entity &e1, const Entity &e2) { return (e1.x == e2.x && e1.y == e2.y); }

size_t World::GetCellIndex(size_t x, size_t y)
{
    return y * sizeX + x;
}

Graph World::fieldToGraph()
{
    typedef pair<size_t, size_t> Edge;
    set<pair<size_t, vector<Edge>>> vertexSet;

    vertexCount = 0;
    for (size_t col = 0; col < sizeX; ++col) {
        for (size_t row = 0; row < sizeY; ++row) {
            char cell = gameField[row][col];
            if (cell != CELL_WALL) {
                ++vertexCount;
                auto neighbors = Neighbours(GetCellIndex(col, row));
                vector<Edge> edges;
                for(auto &n: neighbors) {
                    edges.push_back(make_pair(n.index(), 1));
                }

                vertexSet.insert(make_pair(GetCellIndex(col, row), edges));
            }
        }
    }

    Graph g(sizeX * sizeY);

    // set to Graph
    for(auto &p : vertexSet) {
        size_t vIndex = p.first;
        const vector<Edge> &vEdges = p.second;
        g[vIndex] = vEdges;
    }

    return g;
}

vector<Entity> World::ParentsToPath(vector<Entity> &parents, size_t startIndex, size_t endIndex)
{
    size_t current = endIndex;
    vector<Entity> path;
    while (current != startIndex) {
        current = parents[current].index();
        path.push_back(CellByIndex(current));
    }

    // Remove start point, that is last element in the path
    path.pop_back();

    return path;
}

vector<Entity> World::ParentsToPath(vector<size_t> &parents, size_t startIndex, size_t endIndex)
{
    size_t current = endIndex;
    vector<Entity> path;
    while (current != startIndex) {
        current = parents[current];
        path.push_back(CellByIndex(current));
    }

    // Remove start point, that is last element in the path
    path.pop_back();

    return path;
}

size_t World::Heuristic(Entity &from, Entity to)
{
    return std::abs(static_cast<int>(from.x - to.x)) + std::abs(static_cast<int>(from.y - to.y));
//    return std::sqrt(std::pow(static_cast<int>(e1.x - e2.x), 2) + std::pow(static_cast<int>(e1.y - e2.y), 2));
}

vector<Entity> World::AStarImpl(Graph &g, Entity &startPoint, Entity &endPoint) {
    size_t n = g.size();
    size_t s = startPoint.index(); // start point index

    vector<size_t> cost_so_far(n, INF); // way cost to every vertex
    vector<Entity> came_from(n); // vector of parents for every vertex

    LogStream log("logAStar.txt");

    log << "From: " << startPoint.index() << startPoint.toString() << "\n";
    log << "To: " << endPoint.index() << endPoint.toString() << "\n";

    cost_so_far[s] = 0;

    // Priority, node index
    PriorityQueue<Entity, size_t> frontier;
    frontier.put(startPoint, 0);

    size_t visitedCnt = 0;
    while(!frontier.empty()) {
        Entity current = frontier.get();
        size_t currIdx = current.index();

        log << "Current node: " << currIdx << current.toString() << "\n";

        auto neigbours = Neighbours(current);

        log << "Check neigbours" << "\n";

        for (auto &next : neigbours) {
            size_t nextIdx = next.index();
            size_t new_cost = cost_so_far[currIdx] + GetCost(g, currIdx, nextIdx);

            if ( cost_so_far[nextIdx] == INF
                 || new_cost < cost_so_far[nextIdx])
            {
                cost_so_far[nextIdx] = new_cost;
                size_t priority = new_cost + Heuristic(next, endPoint);
                frontier.put(next, priority);

                came_from[nextIdx] = current;
                ++visitedCnt;

                log << "to = " << nextIdx << next.toString() << "\n";

                if (nextIdx == endPoint.index())
                {
                    log << "Total cells number: " << n << "\n";
                    log << "Visited cells: " << visitedCnt << "\n";
                    log.Close();

                    return came_from;
                }
            }
        }
    }

    return came_from;
}

vector<Entity> World::DijkstraImpl(Graph &g, Entity &startPoint, Entity &endPoint) {
    size_t n = g.size();
    size_t s = startPoint.index(); // start point index

    vector<size_t> cost_so_far(n, INF); // way cost to every vertex
    vector<Entity> came_from(n); // vector of parents for every vertex

    LogStream log("logDijkstra.txt");

    log << "From: " << startPoint.index() << startPoint.toString() << "\n";
    log << "To: " << endPoint.index() << endPoint.toString() << "\n";

    cost_so_far[s] = 0;

    // Priority, node index
    PriorityQueue<Entity, size_t> frontier;
    frontier.put(startPoint, 0);

    size_t visitedCnt = 0;
    while(!frontier.empty()) {
        Entity current = frontier.get();
        size_t currIdx = current.index();

        log << "Current node: " << currIdx << current.toString() << "\n";

        auto neigbours = Neighbours(current);

        log << "Check neigbours" << "\n";

        for (auto &next : neigbours) {
            size_t nextIdx = next.index();
            size_t new_cost = cost_so_far[currIdx] + GetCost(g, currIdx, nextIdx);

            if ( cost_so_far[nextIdx] == INF
                 || new_cost < cost_so_far[nextIdx])
            {
                cost_so_far[nextIdx] = new_cost;
                size_t priority = new_cost;
                frontier.put(next, priority);

                came_from[nextIdx] = current;
                ++visitedCnt;

                log << "to = " << nextIdx << next.toString() << "\n";

                if (nextIdx == endPoint.index())
                {
                    log << "Total cells number: " << n << "\n";
                    log << "Visited cells: " << visitedCnt << "\n";
                    log.Close();

                    return came_from;
                }
            }
        }
    }

    return came_from;
}

vector<Entity> World::FindPath(Entity &startPoint, Entity &endPoint, PathfindingType type)
{
    // Create path from visited cells
    size_t startIndex = startPoint.index();
    size_t endIndex = endPoint.index();

    vector<size_t> result;
    if (type == PathfindingType::BFS)
        result = FindPathBFS(startPoint, endPoint);
    else if (type == PathfindingType::Dijkstra)
    {
        vector<Entity> tmp = FindPathDijkstra(startPoint, endPoint);
        return ParentsToPath(tmp, startIndex, endIndex);
    }
    else if (type == PathfindingType::AStar)
    {
        vector<Entity> tmp = FindPathAStar(startPoint, endPoint);
        return ParentsToPath(tmp, startIndex, endIndex);
    }

    vector<Entity> path;
    if (result.size() != 0)
        path = ParentsToPath(result, startIndex, endIndex);

    return path;
}

Entity World::CellByIndex(size_t index)
{
    size_t x = index % sizeX;
    size_t y = index / sizeX;
    return Entity(x, y);
}

// breadth-first search
vector<size_t> World::FindPathBFS(Entity &startPoint, Entity &endPoint)
{
    size_t startIndex = startPoint.index();
    size_t endIndex = endPoint.index();
    queue<size_t> frontier;
    frontier.push(startIndex);
    vector<size_t> came_from(sizeX * sizeY);
    vector<bool> visited(sizeX * sizeY);

    while (!frontier.empty()) {
       size_t current = frontier.front();
       frontier.pop();

       auto neighbors = Neighbours(current);
       for(auto next : neighbors) {
           size_t nextIdx = next.index();
          if (!visited[nextIdx]) {
             frontier.push(nextIdx);
             came_from[nextIdx] = current;
             visited[nextIdx] = true;

             if (nextIdx == endIndex)
                 break;
          }
       }
    }

    return came_from;
}

vector<Entity> World::FindPathDijkstra(Entity &startPoint, Entity &endPoint)
{
    Graph g = fieldToGraph();

    auto parents = DijkstraImpl(g, startPoint, endPoint);

    return parents;
}

vector<Entity> World::FindPathAStar(Entity &startPoint, Entity &endPoint)
{
    Graph g = fieldToGraph();

    auto parents = AStarImpl(g, startPoint, endPoint);

    return parents;
}
