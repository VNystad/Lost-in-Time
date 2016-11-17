#ifndef LOST_IN_TIME_TESTCOLLIDABLEPLATFORM_H
#define LOST_IN_TIME_TESTCOLLIDABLEPLATFORM_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics.hpp>
#include "../Framework/config.h"

class TestCollidablePlatform
{
public:

    TestCollidablePlatform(float x, float y, const Config& config, sf::RenderWindow* window);
    void DrawMe();

    int GetWidth() const { return width; }
    int GetHeight() const { return height; }

    sf::RectangleShape GetPlatform() const { return *platform; }

protected:
    const int width = 400;
    const int height = 20;
    //Platform position
    float positionX;
    float positionY;

    sf::RectangleShape* platform;
    const Config& config;
    sf::RenderWindow* window;
};


#endif //LOST_IN_TIME_TESTCOLLIDABLEPLATFORM_H
