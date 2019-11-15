#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "Pirate.h"
#include "Treasure.h"
#include "World.h"
#include "iplatform.h"
#ifdef PLATFORM_CURSES
#include "cursesplatform.h"
#endif
using namespace std;

void Greeting(World & world);
void MainLoop(World & world, IPlatform &platform);
void GameUpdate(Input);

int main() {
#ifdef PLATFORM_CURSES
	CursesPlatfrom cursesPlatform;
	IPlatform& platform = cursesPlatform;
#endif

	platform.Init();

	World world;

	//Greeting(world);

	MainLoop(world, platform);

	system("pause");
	return 0;
}

void GameUpdate(Input input, World &world)
{
	Pirate & pirate = world.pirate;
	switch (input)
	{
	case Input::UP:
	{
		//pirate.Move(world, DirectionX::NONE, DirectionY::UP);
		break;
	}
	case Input::LEFT:
	{
		//pirate.Move(world, DirectionX::LEFT, DirectionY::NONE);
		break;
	}
	case Input::DOWN:
	{
		//pirate.Move(world, DirectionX::NONE, DirectionY::DOWN);
		break;
	}
	case Input::RIGHT:
	{
		//pirate.Move(world, DirectionX::RIGHT, DirectionY::NONE);
		break;
	}
	}
}

void MainLoop(World & world, IPlatform &platform)
{
	Pirate & enemy = world.enemyPirate;

	bool isGameRunning = true;
	while (isGameRunning)
	{
		Input input = platform.Update();

		if (input == Input::EXIT) {
			cout << "Are you tired? Understand. See you." << endl;
			isGameRunning = false;
			break;
		}

		world.Draw(platform);
		
		isGameRunning = !world.CheckWin();
	}
}

void Greeting(World & world)
{
	std::string pirateName;

	/*cout << "Hello, stranger! What is your name? : ";
	cin >> pirateName;

	cout << "Welcome on island, " << pirateName << endl;
	cout << "You can walk around using 'w', 's', 'a', 'd' keys\n";

	cout << "Treasure is here: " << world.treasure.x << ", " << world.treasure.y << endl;*/
}
