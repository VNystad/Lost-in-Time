#ifndef SFML_SQUARE_APP_H
#define SFML_SQUARE_APP_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "config.h"
#include "square.h"
#include "platform.h"

class App
{
public:
	App();
	bool Tick();
    void move(float delta);
    bool grounded();
    void movement(float delta);
    void gravity(float delta);

protected:
	Config config;
	sf::RenderWindow window;

	Square square;
    Platform platform1;
	Platform platform2;


	sf::Clock clock;
};

#endif
