#include "stdafx.h"
#include "sfmlplatform.h"
#include <iostream>

using std::endl;

SFMLPlatform::SFMLPlatform(size_t worldSizeX, size_t worldSizeY)
    : window(sf::VideoMode(worldSizeX * SPRITE_SIZE, worldSizeY * SPRITE_SIZE), "SFML window")
{}

void SFMLPlatform::Init() {
	// Declare and create a new window

    window.setFramerateLimit(60);

    if (!textureTerrain.loadFromFile("sprites/terrain.png")) {
        std::cerr << "Can't load texture" << endl;
        return;
    }

    sandSprite.setTexture(textureTerrain);
    sandSprite.setTextureRect(sf::IntRect(SPRITE_SIZE * 1, 0, SPRITE_SIZE, SPRITE_SIZE));

    stoneSprite.setTexture(textureTerrain);
    stoneSprite.setTextureRect(sf::IntRect(SPRITE_SIZE * 2, 0, SPRITE_SIZE, SPRITE_SIZE));

    grassSprite.setTexture(textureTerrain);
    grassSprite.setTextureRect(sf::IntRect(SPRITE_SIZE * 0, 0, SPRITE_SIZE, SPRITE_SIZE));

//	// run the program as long as the window is open
//	while (window.isOpen())
//	{
//        window.clear(sf::Color::White);

//        window.draw(sandSprite);
//        window.display();
//	}
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
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (window.pollEvent(event))
    {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
            window.close();
    }

    return Input::NONE;
}
