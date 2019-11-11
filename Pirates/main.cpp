#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "Pirate.h"
#include "Treasure.h"
#include "World.h"

#define PDC_DLL_BUILD
#include "curses.h"
using namespace std;

void Greeting(World & world);
void MainLoop(World & world);

void initCurses()
{
	initscr();              // ������� � curses-�����
	keypad(stdscr, true);   //�������� ����� ������ �������������� ������

	noecho();
	halfdelay(5);

	curs_set(0);
}

int main() {
	initCurses();

	World world;

	Greeting(world);

	MainLoop(world);

	cbreak();

	endwin();

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
		int ch = getch();

		switch (ch)
		{
		case ERR:
			clear();
			world.Draw();
			break;
		case KEY_UP:
		case 'w':
		{
			pirate.Move(world, DirectionX::NONE, DirectionY::UP);
			break;
		}
		case KEY_LEFT:
		case 'a':
		{
			pirate.Move(world, DirectionX::LEFT, DirectionY::NONE);
			break;
		}
		case KEY_DOWN:
		case 's':
		{
			pirate.Move(world, DirectionX::NONE, DirectionY::DOWN);
			break;
		}
		case KEY_RIGHT:
		case 'd':
		{
			pirate.Move(world, DirectionX::RIGHT, DirectionY::NONE);
			break;
		}
		case 'q':
		{
			cout << "Are you tired? Understand. See you." << endl;
			isGameRunning = false;
			continue;
		}
		}
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