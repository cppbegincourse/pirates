#ifndef CLIPLATFORM_H
#define CLIPLATFORM_H
#include "iplatform.h"
#include <map>
#include "Input.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

class SFMLPlatform : public IPlatform {
public:
    void Init() override;
    void EndDraw() override { }
	void DrawSprite(char sprite, int row, int col) override {};
	void DrawRow(const char* string, int row, int col) override {};
	Input Update() override { return Input::NONE; };
	void ClearScreen() override {};
	const GameScreen& GetWinScreen() override { return GameScreen(); };
	const GameScreen& GetLoseScreen() override { return GameScreen(); };

    ~SFMLPlatform() override {}

private:
    //std::map<int, Input> inputMap{ {KEY_UP, Input::UP}, {'w', Input::UP}, {KEY_DOWN, Input::DOWN}, {'s', Input::DOWN}, {'a', Input::LEFT}, {KEY_LEFT, Input::LEFT}, {'d', Input::RIGHT}, {KEY_RIGHT, Input::RIGHT}, {'q', Input::EXIT}, {ERR, Input::NONE}, {'p', Input::SHOW_PATH}};
};

#endif // CLIPLATFORM_H
