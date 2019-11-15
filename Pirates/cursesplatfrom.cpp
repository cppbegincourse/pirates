#include "stdafx.h"
#include "cursesplatform.h"

void CursesPlatfrom::Init()
{
	initscr();              // Switch to curses-mode
	keypad(stdscr, true);   //Read F-keys

	noecho();
	halfdelay(5);

	curs_set(0);
}

void CursesPlatfrom::DrawSprite(char sprite, int row, int col)
{
	mvprintw(row, col, &sprite);
}
