#include "stdafx.h"
#include "World.h"
#include <iostream>
#include "iplatform.h"
#include <unordered_map>
#include <list>

using namespace std;

constexpr char CELL_EMPTY = ' ';
constexpr char CELL_WALL = '*';

size_t random(size_t min, size_t max) {
    size_t rnd = static_cast<size_t>(rand());
	return rnd % (max - min) + min;
}

World::World()
    //: sizeX(FIELD_WIDTH), sizeY(FIELD_HEIGHT)
    //, gameField(FIELD_HEIGHT)
{
	//srand(unsigned(std::time(0)));

    pirate.x = 2;
    pirate.y = 1;

//    treasure.x = random(1, sizeX - 2);
//    treasure.y = random(1, sizeY - 2);
    treasure.x = 6;
    treasure.y = 1;

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
    gameField.push_back("*********");
    gameField.push_back("* @ * x *");
    gameField.push_back("*   *   *");
    gameField.push_back("*       *");
    gameField.push_back("*********");

    sizeY = gameField.size();
    sizeX = gameField[0].length();

//    gameField.push_back("******************************");
//    gameField.push_back("* @ * x    *                 *");
//    gameField.push_back("*   *      *                 *");
//    gameField.push_back("*          *                 *");
//    gameField.push_back("*          *          *      *");
//    gameField.push_back("*          *          *      *");
//    gameField.push_back("*          ************      *");
//    gameField.push_back("*                            *");
//    gameField.push_back("*                            *");
//    gameField.push_back("*                            *");
//    gameField.push_back("*                            *");
//    gameField.push_back("*                            *");
//    gameField.push_back("*                            *");
//    gameField.push_back("*                            *");
//    gameField.push_back("*                            *");
//    gameField.push_back("*                            *");
//    gameField.push_back("*                            *");
//    gameField.push_back("*                            *");
//    gameField.push_back("*                            *");
//    gameField.push_back("*                            *");
//    gameField.push_back("*                            *");
//    gameField.push_back("*                            *");
//    gameField.push_back("*                            *");
//    gameField.push_back("*                            *");
//    gameField.push_back("*                            *");
//    gameField.push_back("*                            *");
//    gameField.push_back("*                            *");
//    gameField.push_back("*                            *");
//    gameField.push_back("*                            *");
//    gameField.push_back("******************************");
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
    platform.DrawRow("Press q for exit", sizeY + 2, 2);
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

void World::DrawPath(IPlatform &platform, std::vector<Entity> path)
{
    for (auto &point : path) {
        platform.DrawSprite('.', point.y, point.x);
    }
}

vector<Entity> World::Neighbours(Entity& cell)
{
    vector<Entity> tmp;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            char &candidate = gameField[cell.y + j][cell.x + i];
            // Diagonal movement is not allowed
            if(i != j
                    // Check that cell is not Wall
                    && candidate != CELL_WALL)
            {
                tmp.push_back(Entity(cell.x + i, cell.y + j));
            }
        }
    }

    return tmp;
}

bool operator==(const Entity &e1, const Entity &e2) { return (e1.x == e2.x && e1.y == e2.y); }

vector<Entity> World::FindPath(Entity &startPoint, Entity &endPoint)
{
    list<Entity> frontier;
    frontier.push_back(startPoint);
    unordered_map<Entity, Entity> came_from;

    while (!frontier.empty())
    {
       Entity &current = frontier.front();
       frontier.pop_front();

       if (current == endPoint)
           break;

       vector<Entity> neighbors = Neighbours(current);
       for(auto &next : neighbors) {
          if (came_from.find(next) == came_from.end()) {
             frontier.push_back(next);
             came_from[next] = current;
          }
       }
    }

    // Create path from visited cells
    // Use Entity, not Entity* to simplify code
    // Entity is very small, so its copiyng is cheap
    Entity current = endPoint;
    vector<Entity> path = {current};
    while (!(current == startPoint)) {
       current = came_from[current];
       path.push_back(current);
    }
}
