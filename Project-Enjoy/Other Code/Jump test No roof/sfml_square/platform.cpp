
#include "platform.h"

Platform::Platform(float x, float y, const Config& config, sf::RenderWindow& window)
        : x(x), y(y),
          config(config),
          window(window)
{
    platform.setSize(sf::Vector2f(width, height));
    platform.setFillColor(sf::Color::Yellow);
}

void Platform::draw(){
    platform.setPosition(x,y);
    window.draw(platform);
}

