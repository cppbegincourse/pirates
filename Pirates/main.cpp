#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "Pirate.h"
#include "Treasure.h"
#include "World.h"
using namespace std;

constexpr int FIELD_WIDTH = 10;
constexpr int FIELD_HEIGHT = 10;

void Greeting(World & world);
void MainLoop(World & world);

int main() {
	World world(FIELD_WIDTH, FIELD_HEIGHT);

	Greeting(world);

	MainLoop(world);

	system("pause");
	return 0;
}

void MainLoop(World & world)
{
	Pirate & pirate = world.pirate;
	Pirate & enemy = world.enemyPirate;

	char inputDirection;

	bool isGameRunning = true;
	while (isGameRunning)
	{
		cout << "Choose your direction: ";
		cin >> inputDirection;

		switch (inputDirection)
		{
		case 'w':
		{
			pirate.MoveUp(world);
			break;
		}
		case 'a':
		{
			pirate.MoveLeft(world);
			break;
		}
		case 's':
		{
			pirate.MoveDown(world);
			break;
		}
		case 'd':
		{
			pirate.MoveRight(world);
			break;
		}
		case 'q':
		{
			cout << "Are you tired? Understand. See you." << endl;
			isGameRunning = false;
			continue;
		}
		default:
			break;
		}

		enemy.MoveDown(world);
		enemy.MoveRight(world);

		pirate.printCoords("You");
		enemy.printCoords("Enemy");

		isGameRunning = !world.CheckWin();
	}
}

void Greeting(World & world)
{
	std::string pirateName;

	cout << "Hello, stranger! What is your name? : ";
	cin >> pirateName;

	cout << "Welcome on island, " << pirateName << endl;
	cout << "You can walk around using 'w', 's', 'a', 'd' keys\n";

	cout << "Treasure is here: " << world.treasure.x << ", " << world.treasure.y << endl;
}