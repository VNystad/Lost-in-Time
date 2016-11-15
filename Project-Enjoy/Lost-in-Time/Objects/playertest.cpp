#include <iostream>
#include "playertest.h"

PlayerTest::PlayerTest(float positionX, float positionY, const Config& config, sf::RenderWindow* window) : config(config), window(window)
{
    this->positionX = OriginalX;
    this->positionY = OriginalY;
    character = new sf::RectangleShape;
    character->setSize(sf::Vector2f(sizeWidth,sizeHeight));
    //animation->PlayerIdle(character);

    //health->SetActualLifePoints(100);
    //health->SetVisibleLifePoints(100);
}

int PlayerTest::GetPositionX()
{
    return positionX;
}
int PlayerTest::GetPositionY()
{
    return positionY;
}
void PlayerTest::SetPositionX(int x)
{
    this->positionX = x;
}
void PlayerTest::SetPositionY(int y)
{
    this->positionY = y;
}

int PlayerTest::GetOriginalX()
{
    return OriginalX;
}

int PlayerTest::GetOriginalY()
{
    return OriginalY;
}

void PlayerTest::SetOriginalX(int x)
{
    this->OriginalX = x;
}

void PlayerTest::SetOriginalY(int y)
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

void PlayerTest::PlayerDead()
{
    //health->SetActualLifePoints(100);
    //health->SetVisibleLifePoints(100);
    jumpspeed = origjumpspeed;
    fallspeed = 0;
    movedirection = 2;
    positionX = OriginalX;
    positionY = OriginalY;
    std::cout << "Oh deer, you died!" << std::endl;
}

void PlayerTest::DrawMe()
{
    // Position the rectangle used to draw the square
    character->setPosition(positionX, positionY);

    // Draw the square
    window->draw(*character);
}
