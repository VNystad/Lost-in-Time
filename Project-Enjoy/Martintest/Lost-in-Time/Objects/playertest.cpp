#include "playertest.h"

PlayerTest::PlayerTest(float positionX, float positionY, const Config& config, sf::RenderWindow* window)
    : config(config),
      window(window)
{
    this->positionX = positionX;
    this->positionY = positionY;
    character = new sf::RectangleShape;
    character->setSize(sf::Vector2f(10,10));
    character->setFillColor(sf::Color::Red);
}

void PlayerTest::SetPosition(float x, float y)
{
    this->positionX = x;
    this->positionY = y;
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

void PlayerTest::DrawMe()
{
    // Position the rectangle used to draw the square
    character->setPosition(positionX, positionY);

    // Draw the square
    window->draw(*character);
}
