#include <iostream>
#include "playertest.h"

PlayerTest::PlayerTest(float positionX, float positionY, const Config& config, sf::RenderWindow* window) : config(config), window(window)
{
    this->positionX = 180;
    this->positionY = 250;
    character = new sf::RectangleShape;
    character->setSize(sf::Vector2f(sizeWidth,sizeHeight));

    // Load the animation textures
    if (!PlayerTextureWalk.loadFromFile("data/Character-Animation/charactermove.png"))
        std::cout << "Failed to load data/Character-Animation/charactermove.png" << std::endl << std::endl;

    // Load the animation textures
    if (!PlayerTextureWalkflipped.loadFromFile("data/Character-Animation/charactermoveflipped.png"))
        std::cout << "Failed to load data/Character-Animation/charactermoveflipped.png" << std::endl << std::endl;

    // Load the animation textures
    if (!PlayerTextureIdle.loadFromFile("data/Character-Animation/characteridle.png"))
        std::cout << "Failed to load data/Character-Animation/characteridle.png" << std::endl << std::endl;

    // Load the animation textures
    if (!PlayerTextureJump.loadFromFile("data/Character-Animation/characterjump.png"))
        std::cout << "Failed to load data/Character-Animation/characterjump.png" << std::endl << std::endl;

    // Load the animation textures
    if (!PlayerTextureJumpflipped.loadFromFile("data/Character-Animation/characterjumpflipped.png"))
        std::cout << "Failed to load data/Character-Animation/characterjumpflipped.png" << std::endl << std::endl;

    // Load the animation textures
    if (!PlayerTextureDeath.loadFromFile("data/Character-Animation/characterdeath.png"))
        std::cout << "Failed to load data/Character-Animation/characterdeath.png" << std::endl << std::endl;

    rectSourceCharacter = new sf::IntRect(0,0,sizeWidth,sizeHeight);

    character->setTexture(&PlayerTextureIdle);
    character->setTextureRect(*rectSourceCharacter);
}

float PlayerTest::GetPositionX()
{
    return positionX;
}
float PlayerTest::GetPositionY()
{
    return positionY;
}
void PlayerTest::SetPositionX(float x)
{
    this->positionX = x;
}
void PlayerTest::SetPositionY(float y)
{
    this->positionY = y;
}

float PlayerTest::GetOriginalX()
{
    return OriginalX;
}

float PlayerTest::GetOriginalY()
{
    return OriginalY;
}

void PlayerTest::SetOriginalX(float x)
{
    this->OriginalX = x;
}

void PlayerTest::SetOriginalY(float y)
{
    this->OriginalY = y;
}

void PlayerTest::Reset2OriginalX(float x)
{
    x = this->OriginalX;
}

void PlayerTest::Reset2OriginalY(float y)
{
    y = this->OriginalY;
}

int PlayerTest::GetLifepoints()
{
    return lifepoints;
}

void PlayerTest::SetLifepoints(int lifepoint)
{
    this->lifepoints = lifepoint;
}

void PlayerTest::PlayerDead()
{
    // If player is dead, 0 lifepoints, reset to original spawn point
    if (lifepoints <= 0)
    {
        positionX = OriginalX;
        positionY = OriginalY;
    }
}

void PlayerTest::DrawMe()
{
    // Position the rectangle used to draw the square
    character->setPosition(positionX, positionY);

    // Draw the square
    window->draw(*character);
}
