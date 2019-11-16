#include "stdafx.h"
#include "cursesplatform.h"
using namespace std;
void CursesPlatform::Init()
{
	initscr();              // Switch to curses-mode
	keypad(stdscr, true);   //Read F-keys

	noecho();
	halfdelay(5);

	curs_set(0);
}

void CursesPlatform::DrawRow(const char* string, int row, int col)
{
    mvprintw(row, col, string);
}

void CursesPlatform::DrawSprite(char sprite, int row, int col)
{
	mvprintw(row, col, &sprite);
}

void CursesPlatform::ClearScreen() {
	clear();
}

Input CursesPlatform::Update()
{
	int ch = getch();

    if (inputMap.find(ch) != inputMap.end())
        return inputMap[ch];
    else {
        return Input::ANY_KEY;
    }
}

const GameScreen& CursesPlatform::GetWinScreen()
{
    static GameScreen winScreen = GameScreen{string(12, '*'), "*" + string(10, ' ') + "*", "* You win! *", "*" + string(10, ' ') + "*", std::string(12, '*')};
    return winScreen;
}

const GameScreen& CursesPlatform::GetLoseScreen()
{
    static GameScreen winScreen = GameScreen{string(12, '*'), "*" + string(10, ' ') + "*", "* You lose *", "*" + string(10, ' ') + "*", std::string(12, '*')};
    return winScreen;
}
