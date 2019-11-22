#include "stdafx.h"
#include "sfmlplatform.h"
#include <iostream>

using std::endl;

SFMLPlatform::SFMLPlatform(size_t worldSizeX, size_t worldSizeY)
    : window(sf::VideoMode(worldSizeX * SPRITE_SIZE, worldSizeY * SPRITE_SIZE), "SFML window")
{}

void SFMLPlatform::Init() {
	IPlatform::Init();
	// Declare and create a new window

    window.setFramerateLimit(60);

    if (!textureTerrain.loadFromFile("sprites/terrain.png")) {
        std::cerr << "Can't load texture" << endl;
        return;
    }

    grassSprite.setTexture(textureTerrain);
    grassSprite.setTextureRect(sf::IntRect(SPRITE_SIZE * 0, SPRITE_SIZE * 0, SPRITE_SIZE, SPRITE_SIZE));

    sandSprite.setTexture(textureTerrain);
    sandSprite.setTextureRect(sf::IntRect(SPRITE_SIZE * 1, SPRITE_SIZE * 0, SPRITE_SIZE, SPRITE_SIZE));

	stoneSprite.setTexture(textureTerrain);
	stoneSprite.setTextureRect(sf::IntRect(SPRITE_SIZE * 2, SPRITE_SIZE * 0, SPRITE_SIZE, SPRITE_SIZE));

	pathSprite.setTexture(textureTerrain);
	pathSprite.setTextureRect(sf::IntRect(SPRITE_SIZE * 3, SPRITE_SIZE * 0, SPRITE_SIZE, SPRITE_SIZE));

	pirateSprite.setTexture(textureTerrain);
	pirateSprite.setTextureRect(sf::IntRect(SPRITE_SIZE * 0, SPRITE_SIZE * 1, SPRITE_SIZE, SPRITE_SIZE));
	
	treasureSprite.setTexture(textureTerrain);
	treasureSprite.setTextureRect(sf::IntRect(SPRITE_SIZE * 1, SPRITE_SIZE * 1, SPRITE_SIZE, SPRITE_SIZE));

	enemySprite.setTexture(textureTerrain);
	enemySprite.setTextureRect(sf::IntRect(SPRITE_SIZE * 2, SPRITE_SIZE * 1, SPRITE_SIZE, SPRITE_SIZE));

//	// run the program as long as the window is open
//	while (window.isOpen())
//	{
//        window.clear(sf::Color::White);

//        window.draw(sandSprite);
//        window.display();
//	}
}

void SFMLPlatform::DrawRow(const char* string, int row, int col)
{
	const char *c = string;
	while (*c != '\0') {
		DrawSprite(*c, row, col++);
		++c;
	}
}

void SFMLPlatform::DrawSprite(char spriteChar, int row, int col)
{
    int x = col * SPRITE_SIZE;
    int y = row * SPRITE_SIZE;

    sf::Sprite* sprite = spriteMap[spriteChar];
    sprite->setPosition(x, y);
    window.draw(*sprite);
}

Input SFMLPlatform::Update() {
	IPlatform::Update();

    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (window.pollEvent(event))
    {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
            window.close();
    }

	Input input = Input::NONE;
	//sf::Keyboard::Key keys[] = { sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::P, sf::Keyboard::Q, sf::Keyboard::A, sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::D };

	bool localKeyPressed = false;
	for (auto pair : inputMap)
	{
		auto key = pair.first;
		if ((localKeyPressed |= sf::Keyboard::isKeyPressed(key)) && !keyPressed)
		{
			input = inputMap[key];
			keyPressed = true;
		}
	}

	keyPressed = localKeyPressed;

    return input;
}
