#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

constexpr int FIELD_WIDTH = 10;
constexpr int FIELD_HEIGHT = 10;

struct Treasure {
	int x;
	int y;
};

struct Pirate {
	void printCoords(string name) { cout << endl << name << ": [" << x << ", " << y << "]" << endl; };
	int x = 0;
	int y = 0;
};

class World {
public:
	World();
public:
	Treasure treasure;
	Pirate pirate;

	Pirate enemyPirate;
};

World::World() {
	//srand(unsigned(std::time(0)));

	treasure.x = rand() % FIELD_WIDTH;
	treasure.y = rand() % FIELD_HEIGHT;

	enemyPirate.x = rand() % FIELD_WIDTH;
	enemyPirate.y = rand() % FIELD_HEIGHT;
}


void Greeting(World & world);
void MainLoop(World & world);

void MoveLeft(Pirate & pirate);
void MoveRight(Pirate & pirate);
void MoveUp(Pirate & pirate);
void MoveDown(Pirate & pirate);

bool CheckWin(World & world);

int main() {
	World world;
	
	Greeting(world);

	MainLoop(world);

	system("pause");
	return 0;
}

void MoveLeft(Pirate & pirate)
{
	pirate.x--;
	if (pirate.x < 0) {
		pirate.x = FIELD_WIDTH;
	}
}
void MoveRight(Pirate & pirate)
{
	pirate.x++;
	if (pirate.x > FIELD_WIDTH) {
		pirate.x = 0;
	}
}
void MoveUp(Pirate & pirate)
{
	pirate.y++;
	if (pirate.y > FIELD_HEIGHT) {
		pirate.y = 0;
	}
}
void MoveDown(Pirate & pirate)
{
	pirate.y--;
	if (pirate.y < 0) {
		pirate.y = FIELD_HEIGHT;
	}
}

void MainLoop(World & world)
{
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
			MoveUp(world.pirate);
			break;
		}
		case 'a':
		{
			MoveLeft(world.pirate);
			break;
		}
		case 's':
		{
			MoveDown(world.pirate);
			break;
		}
		case 'd':
		{
			MoveRight(world.pirate);
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

		MoveDown(world.enemyPirate);
		MoveRight(world.enemyPirate);

		world.pirate.printCoords("You");
		world.enemyPirate.printCoords("Enemy");

		isGameRunning = !CheckWin(world);
	}
}

bool CheckWin(World & world)
{
	if (world.treasure.x == world.pirate.x && world.treasure.y == world.pirate.y) {
		cout << "You've found the treasure!" << endl;
		return true;
	}
	else {
		cout << "Not here, looser" << endl;
	}

	return false;
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