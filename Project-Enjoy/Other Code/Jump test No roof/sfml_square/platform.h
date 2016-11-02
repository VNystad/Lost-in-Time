
#ifndef SFML_SQUARE_PLATFORM_H
#define SFML_SQUARE_PLATFORM_H

#include <SFML/Graphics.hpp>
#include "config.h"

struct Platform {
    Platform(float x, float y, const Config& config, sf::RenderWindow& window);
    void draw();

    const int width = 500;
    const int height = 20;
    float x, y;

    sf::RectangleShape platform;
    const Config& config;
    sf::RenderWindow& window;

};


#endif //SFML_SQUARE_PLATFORM_H


