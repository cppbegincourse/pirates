#ifndef CLIPLATFORM_H
#define CLIPLATFORM_H
#include "iplatform.h"
#include <map>
#include "Input.h"

#ifdef _WIN32
#define PDC_DLL_BUILD
#include "curses.h"
#else
#include <ncurses.h>
#endif

class CursesPlatform : public IPlatform {
public:
    void Init() override;
    void EndDraw() override { refresh(); }
	void DrawSprite(char sprite, int row, int col) override;
    void DrawRow(const char* string, int row, int col) override;
	Input Update() override;
	void ClearScreen() override;
    const GameScreen& GetWinScreen() override;
    const GameScreen& GetLoseScreen() override;

    ~CursesPlatform() override {
		cbreak();
		endwin();
    }

private:
    std::map<int, Input> inputMap{ {KEY_UP, Input::UP}, {'w', Input::UP}, {KEY_DOWN, Input::DOWN}, {'s', Input::DOWN}, {'a', Input::LEFT}, {KEY_LEFT, Input::LEFT}, {'d', Input::RIGHT}, {KEY_RIGHT, Input::RIGHT}, {'q', Input::EXIT}, {ERR, Input::NONE}, {'p', Input::SHOW_PATH}};
};

#endif // CLIPLATFORM_H
