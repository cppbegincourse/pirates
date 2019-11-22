#ifndef CLIPLATFORM_H
#define CLIPLATFORM_H
#include "iplatform.h"
#include <map>
#include "Input.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr int SPRITE_SIZE = 64;

class SFMLPlatform : public IPlatform {
public:
    SFMLPlatform(size_t worldSizeX, size_t worldSizeY);
    void Init() override;
    void EndDraw() override { window.display(); }
    void DrawSprite(char sprite, int row, int col) override;
	void DrawRow(const char* string, int row, int col) override {};
    Input Update() override;
    void ClearScreen() override { window.clear(sf::Color::White); };
	const GameScreen& GetWinScreen() override { return GameScreen(); };
	const GameScreen& GetLoseScreen() override { return GameScreen(); };

    ~SFMLPlatform() override {}

private:
    //std::map<int, Input> inputMap{ {KEY_UP, Input::UP}, {'w', Input::UP}, {KEY_DOWN, Input::DOWN}, {'s', Input::DOWN}, {'a', Input::LEFT}, {KEY_LEFT, Input::LEFT}, {'d', Input::RIGHT}, {KEY_RIGHT, Input::RIGHT}, {'q', Input::EXIT}, {ERR, Input::NONE}, {'p', Input::SHOW_PATH}};
    std::map<char, sf::Sprite*> spriteMap{ {'*', &stoneSprite}, {' ', &grassSprite}, {'~', &sandSprite},};
    size_t worldSizeX;
    size_t worldSizeY;

    sf::RenderWindow window;
    sf::Texture textureTerrain;

    sf::Sprite sandSprite;
    sf::Sprite stoneSprite;
    sf::Sprite grassSprite;
};

#endif // CLIPLATFORM_H
