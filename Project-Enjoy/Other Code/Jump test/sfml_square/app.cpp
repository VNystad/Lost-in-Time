#include <SFML/Window.hpp>

#include "app.h"
#include <iostream>

App::App() : square(200, 200, config, window), platform1(100, 500, config, window), platform2(300, 200, config, window)
{
	// Create and configure the window
	window.create(sf::VideoMode(config.screenWidth, config.screenHeight), "The Magic Square");

	// Locks the screen refresh to the monitor refresh (usually 60 fps)
	window.setVerticalSyncEnabled(true);

	clock.restart();
}

bool App::Tick()
{
	sf::Event event;
	float delta = clock.restart().asSeconds();

	// Get events from OS
	while (window.pollEvent(event))
	{
		// Close the window if the user clicks the x button
		if (event.type == sf::Event::Closed)
		{
			window.close();
			return false;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		window.close();
		return false;
	}

	move(delta);

	window.clear(sf::Color::Black);
	square.draw();
    platform1.draw();
	platform2.draw();

	// Flip buffers to show what we've drawn
	window.display();

	return true;
}


void App::move(float delta)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		square.x += square.speed *  delta;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		square.x -= square.speed * delta;

	if(square.rectangle.getGlobalBounds().intersects(platform1.platform.getGlobalBounds()) || square.rectangle.getGlobalBounds().intersects(platform2.platform.getGlobalBounds()))
	{
		square.jumpcheck = 0;
		square.apexcheck = 0;
		square.fallspeed = 0;
		square.jumpspeed = square.orgjumpspeed;
	}

    else if(square.jumpcheck != 1)
    {
        square.jumpcheck = 1;
        square.apexcheck = 1;
    }


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && square.jumpcheck == 0)
	{
		square.jumpcheck = 1;
	}

	if(square.jumpcheck == 1)
    {
		if(square.jumpspeed >= 0 && square.apexcheck == 0)
		{
			square.y -= ((square.speed*square.jumpspeed)/square.gravity)*(delta);
			square.jumpspeed -= 1;
		}
		else
		{
			square.apexcheck = 1;
			square.y += ((square.speed*square.fallspeed)/square.gravity)*(delta);
			square.fallspeed += 1;
		}
	}




	// Keep the box within screen borders
	square.x = std::max(square.x, 0.f);
	square.x = std::min(square.x, (float)(config.screenWidth - square.size));
	square.y = std::max(square.y, 0.f);
	square.y = std::min(square.y, (float)(config.screenHeight - square.size));


}
