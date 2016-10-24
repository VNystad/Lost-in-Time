#include <SFML/Graphics.hpp>

#include "square.h"
#include <iostream>

Square::Square(float x, float y, const Config& config, sf::RenderWindow& window)
		: x(x), y(y),
		  config(config),
		  window(window)

{
	rectangle.setSize(sf::Vector2f(size, size));
	rectangle.setFillColor(sf::Color::Red);
}
/*
void Square::move(float delta)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		x += speed *  delta;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		x -= speed * delta;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && y>=200  && jumpcheck == 0)
	{
		y -= speed * delta;
		jumpcheck = 1;
		std::cout << "jumped" << std::endl;
	}

	if(jumpcheck == 1){
		if(fallspeed>= 0 && apexcheck == 0)
		{
			y -= ((speed*fallspeed)/gravity)*(delta);
			fallspeed -= 1;
		}
		else
		{
			apexcheck = 1;
			y += ((speed*fallspeed)/gravity)*(delta);
			fallspeed += 1;
		}
	}



	if(jumpcheck == 1 && y >= 200)
	{
		jumpcheck = 0;
		fallspeed = orgfallspeed;
		apexcheck = 0;
	}
	/*


	// Keep the box within screen borders
	x = std::max(x, 0.f);
	x = std::min(x, (float)(config.screenWidth - size));
	y = std::max(y, 0.f);
	y = std::min(y, (float)(config.screenHeight - size));
}
*/
/*
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
y += speed * delta;
*/
void Square::draw()
{
	// Position the rectangle used to draw the square
	rectangle.setPosition(x, y);

	// Draw the square
	window.draw(rectangle);
}
