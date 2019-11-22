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
	void DrawRow(const char* string, int row, int col) override;
    Input Update() override;
    void ClearScreen() override {  };
	const GameScreen& GetWinScreen() override { return GameScreen(); };
	const GameScreen& GetLoseScreen() override { return GameScreen(); };

    ~SFMLPlatform() override {}

private:
    std::map<sf::Keyboard::Key, Input> inputMap{ {sf::Keyboard::Up, Input::UP}, {sf::Keyboard::W, Input::UP}, {sf::Keyboard::Down, Input::DOWN}, {sf::Keyboard::S, Input::DOWN}, {sf::Keyboard::Left, Input::LEFT}, {sf::Keyboard::A, Input::LEFT}, {sf::Keyboard::D, Input::RIGHT}, {sf::Keyboard::Right, Input::RIGHT}, {sf::Keyboard::Q, Input::EXIT}, {sf::Keyboard::P, Input::SHOW_PATH}};
	std::map<char, sf::Sprite*> spriteMap{ {'*', &stoneSprite}, {' ', &grassSprite}, {'~', &sandSprite}, {'.', &pathSprite}, {'@', &pirateSprite}, {'&', &enemySprite}, {'x', &treasureSprite} };
    size_t worldSizeX;
    size_t worldSizeY;

    sf::RenderWindow window;
    sf::Texture textureTerrain;

    sf::Sprite sandSprite;
    sf::Sprite stoneSprite;
	sf::Sprite grassSprite;
	sf::Sprite pathSprite;
	sf::Sprite enemySprite;
	sf::Sprite pirateSprite;
	sf::Sprite treasureSprite;

	bool keyPressed;
};

#endif // CLIPLATFORM_H
