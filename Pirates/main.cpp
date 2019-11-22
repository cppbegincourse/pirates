#include "stdafx.h"
#include <cstdlib>
#include <ctime>

#include "Pirate.h"
#include "Treasure.h"
#include "World.h"
#include "iplatform.h"
#ifdef PLATFORM_CURSES
#include "cursesplatform.h"
#elif defined PLATFORM_SFML
#include "sfmlplatform.h"
#endif
using namespace std;

void Greeting(World & world);
void MainLoop(World & world, IPlatform &platform);
void GameUpdate(Input&, World&, int dt);

int main() {
    World world;

#ifdef PLATFORM_CURSES
    CursesPlatform cursesPlatform;
	IPlatform& platform = cursesPlatform;
#elif defined PLATFORM_SFML
    SFMLPlatform sfmlPlatorm(world.width(), world.height());
	IPlatform& platform = sfmlPlatorm;
#endif

	platform.Init();

	//Greeting(world);

	MainLoop(world, platform);

	system("pause");
	return 0;
}

void GameUpdate(Input &input, World &world, int dt)
{
	Pirate & pirate = world.pirate;
	switch (input)
	{
	case Input::UP:
	{
        pirate.Move(world, DirectionX::NONE, DirectionY::UP);
        input = Input::NONE;
		break;
	}
	case Input::LEFT:
	{
        pirate.Move(world, DirectionX::LEFT, DirectionY::NONE);
        input = Input::NONE;
		break;
	}
	case Input::DOWN:
	{
        pirate.Move(world, DirectionX::NONE, DirectionY::DOWN);
        input = Input::NONE;
		break;
	}
	case Input::RIGHT:
	{
        pirate.Move(world, DirectionX::RIGHT, DirectionY::NONE);
        input = Input::NONE;
		break;
	}
    default:
        break;
	}

	//world.enemyPirate.Update(dt, world);
}

void MainLoop(World & world, IPlatform &platform)
{
	bool isGameRunning = true;
    bool isWin = false;
    bool drawPath = !false;
	vector<Entity> path;

	int enemyMoveTimeout = 500;

	while (isGameRunning)
	{
		Input input = platform.Update();

        if (!isWin)
            GameUpdate(input, world, platform.GetElapsedTime());

		if (input == Input::EXIT) {
            //cout << "Are you tired? Understand. See you." << endl;
			isGameRunning = false;
            break;
		}

        world.Draw(platform);

        if (input == Input::SHOW_PATH) {
            drawPath = !drawPath;
        }

        if (drawPath)
            world.DrawPathToTreasure(platform);

		platform.EndDraw();

        isWin = world.CheckWin();
        isGameRunning = !isWin;

	}

    if (isWin)
        world.DrawScreen(platform, platform.GetWinScreen(), 5, 5);
    else
        world.DrawScreen(platform, platform.GetLoseScreen(), 5, 5);
    while (platform.Update() == Input::NONE){}
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
