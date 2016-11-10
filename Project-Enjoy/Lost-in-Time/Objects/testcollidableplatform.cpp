#include "testcollidableplatform.h"

TestCollidablePlatform::TestCollidablePlatform(float x, float y, const Config& config, sf::RenderWindow* window)
        : positionX(x), positionY(y),
          config(config),
          window(window)
{
    platform = new sf::RectangleShape;
    platform->setSize(sf::Vector2f(width, height));
    platform->setFillColor(sf::Color::Yellow);
}


void TestCollidablePlatform::DrawMe()
{
    platform->setPosition(positionX, positionY);

    window->draw(*platform);
}