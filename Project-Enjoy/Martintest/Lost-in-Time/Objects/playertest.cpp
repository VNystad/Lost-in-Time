#include "playertest.h"

PlayerTest::PlayerTest(float x, float y, const Config& config, sf::RenderWindow* window)
    : x(x), y(y),
      config(config),
      window(window)
{
    character = new sf::RectangleShape;
    character->setSize(sf::Vector2f(10,10));
    character->setFillColor(sf::Color::Red);
}

void PlayerTest::DrawMe()
{
    // Position the rectangle used to draw the square
    character->setPosition(x, y);

    // Draw the square
    window->draw(*character);
}
