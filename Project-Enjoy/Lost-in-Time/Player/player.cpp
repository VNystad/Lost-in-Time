#include <SFML/Graphics.hpp>
#include "player.h"

Player::Player(int x, int y, const Config& config, sf::RenderWindow& window)
        : x(x), y(y),
          config(config),
          window(window)

{
    character.setSize(sf::Vector2f(size, size));
    character.setFillColor(sf::Color::Red);
}

void Player::draw()
{
    // Position the rectangle used to draw the square
    character.setPosition(x, y);

    // Draw the square
    window.draw(character);
}
