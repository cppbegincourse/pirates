#include "stdafx.h"
#include "World.h"
#include <iostream>
#include "iplatform.h"
#include <unordered_map>
#include <queue>
#include <set>
#include <fstream>
#include <ctime>

using namespace std;

constexpr char CELL_EMPTY = ' ';
constexpr char CELL_WALL = '*';
constexpr char CELL_TREASURE = 'x';

size_t random(size_t min, size_t max) {
    size_t rnd = static_cast<size_t>(rand());
	return rnd % (max - min) + min;
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

	if (lvlFileStream.is_open())
	{
		int row = 0;
		while (getline(lvlFileStream, line)) {
			gameField.push_back(line);
			int col;
			if ((col = line.find(CELL_PIRATE)) != string::npos) {
				pirate.x = col;
				pirate.y = row;
			}

			if ((col = line.find(CELL_TREASURE)) != string::npos) {
				treasure.x = col;
				treasure.y = row;
			}

			++row;
		}

		sizeY = gameField.size();
		sizeX = gameField[0].length();
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
    for (const std::string &row : screen) {
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
	vector<Entity> path = FindPathDijkstra(pirate, treasure);
	//vector<Entity> path = FindPath(pirate, treasure);
    DrawPath(platform, path);
}

vector<Entity> World::Neighbours(size_t row, size_t col)
{
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
    return Neighbours(cell.y, cell.x);
}

bool operator==(const Entity &e1, const Entity &e2) { return (e1.x == e2.x && e1.y == e2.y); }

constexpr int INF = 1000000000;

size_t World::GetCellIndex(Entity &cell)
{
    return GetCellIndex(cell.x, cell.y);
}

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
                vector<Entity> neighbors = Neighbours(row, col);
                vector<Edge> edges;
                for(auto &n: neighbors) {
                    edges.push_back(make_pair(GetCellIndex(n), 1));
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

vector<Entity> World::FindPathDijkstra(Entity &startPoint, Entity &endPoint)
{
    Graph g = fieldToGraph();

    auto parents = Dijkstra(g, startPoint, endPoint);

	vector<Entity> path;
	if (parents.size() != 0)
		path = ParentsToPath(parents, startPoint, endPoint);

    return path;
}

vector<Entity> World::ParentsToPath(vector<size_t> parents, Entity &startPoint, Entity &endPoint)
{
    auto cellByIndex = [this](size_t index) -> Entity {
        return Entity(index % sizeX, index / sizeX);
    };
    Entity current = endPoint;
    vector<Entity> path;
    while (!(current == startPoint)) {
		path.push_back(current);
        current = cellByIndex(parents[GetCellIndex(current)]);
    }

    // Remove start point, that is last element in the path
    //path.pop_back();

    return path;
}

vector<size_t> World::Dijkstra(Graph &g, Entity &startPoint, Entity &endPoint) {

    size_t n = g.size();
    size_t s = GetCellIndex(startPoint); // start point index

    vector<size_t> cost_so_far(n, INF); // way cost to every vertex
    vector<size_t> came_from(n); // vector of parents for every vertex

    cost_so_far[s] = 0;
    vector<bool> visited(n);
    for (size_t i = 0; i < n; ++i) {
        int v = -1; // visit candidate
        for (size_t j = 0; j < n; ++j)
            if (!visited[j] && (v == -1 || cost_so_far[j] < cost_so_far[v]))
                v = static_cast<int>(j);
        if (cost_so_far[v] == INF)
            break;
        visited[v] = true;

		auto &candidateNeigbours = g[v];

        for (size_t j = 0; j < candidateNeigbours.size(); ++j) {
            size_t to = candidateNeigbours[j].first;
            size_t len = candidateNeigbours[j].second;
            if (cost_so_far[v] + len < cost_so_far[to]) {
                cost_so_far[to] = cost_so_far[v] + len;
                came_from[to] = v;

                if (to == GetCellIndex(endPoint))
                    return came_from;
            }
        }
    }

    return came_from;
}

vector<Entity> World::FindPath(Entity &startPoint, Entity &endPoint)
{
    queue<Entity> frontier;
    frontier.push(startPoint);
    unordered_map<Entity, Entity> came_from{std::make_pair(startPoint, startPoint)};

    while (!frontier.empty()) {
       Entity current = frontier.front();
       frontier.pop();

       vector<Entity> neighbors = Neighbours(current);
       for(auto next : neighbors) {
          if (came_from.find(next) == came_from.end()) {
             frontier.push(next);
             came_from[next] = current;

             if (next == endPoint)
                 break;
          }
       }
    }

    // Create path from visited cells
    // Use Entity, not Entity* to simplify code
    // Entity is very small, so its copiyng is cheap
    Entity current = endPoint;
    vector<Entity> path;
    while (!(current == startPoint)) {
		path.push_back(current);
        current = came_from[current];
    }

    // Remove start point, that is last element in the path
    //path.pop_back();

    return path;
}
