#ifndef LOST_IN_TIME_DEATHSCREEN_H
#define LOST_IN_TIME_DEATHSCREEN_H


#include <SFML/Graphics.hpp>
#include "../Framework/font.h"

class Deathscreen {
public:
    Deathscreen() { };
    void init();
    void Display();
    Font font;

    sf::Text GetDeathScreen();
    void SetDeathScreen(sf::Text deathscreen);

protected:
    sf::Text deathscreen;
    sf::RenderWindow window;
};


#endif
