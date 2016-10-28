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
void App::move(float delta)
{
    //This function will make the object able to move and fall, with correlation to any hinderings such as gravity.
    //The delta float is there for smoothness.

    //Movement to the right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		square.x += square.speed *  delta;
    //Movement to the left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		square.x -= square.speed * delta;


    //Gravity Start-----------------------------------------------------------------------------------------------------

    //Checks if object is in contact with platform,
    //then marks the object as not airborne(jumpcheck) and current fallspeed as 0.
    //Jumpspeed are also resetted for later use.
	if(square.rectangle.getGlobalBounds().intersects(platform1.platform.getGlobalBounds()) || square.rectangle.getGlobalBounds().intersects(platform2.platform.getGlobalBounds()))
	{
		square.jumpcheck = 0;
		square.fallspeed = 0;
		square.jumpspeed = square.orgjumpspeed;
	}

    //Check if falling off a platform
        // If the object is not in contact with a platform, and it was not caused by jumping, the object is marked
        // as airborne (jumpcheck) and falling (apexcheck, reached the apex, on the way down).
    else if(square.jumpcheck != 1)
    {
        square.jumpcheck = 1;
        square.apexcheck = 1;
    }

    //Tries to make the object jump when Up key is pressed,
    //but only succeeds if the object is not already airborne (jumpcheck).
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && square.jumpcheck == 0)
	{
		square.jumpcheck = 1;
        square.apexcheck = 0;
	}

    //Functionality for ascending or falling when the object is marked as airborne (jumpcheck).
	if(square.jumpcheck == 1)
    {
        //The Object ascends at a decreasing rate when the object is marked as ascending (apexcheck).
		if(square.jumpspeed >= 0 && square.apexcheck == 0)
		{
			square.y -= ((square.speed*square.jumpspeed)/square.gravity)*(delta);
			square.jumpspeed -= 1;
		}
        //The Object is descending (apexcheck) as well ass airborne (jumpcheck),
        //and therefore descends at an increasing rate because of how gravity works.
		else
		{
			square.apexcheck = 1;
			square.y += ((square.speed*square.fallspeed)/square.gravity)*(delta);
            if(square.fallspeed < square.orgjumpspeed)
            {
                square.fallspeed += 1;
            }
		}
	}
    //Gravity End-------------------------------------------------------------------------------------------------------


	// Keep the box within screen borders
	square.x = std::max(square.x, 0.f);
	square.x = std::min(square.x, (float)(config.screenWidth - square.size));
	square.y = std::max(square.y, 0.f);
	square.y = std::min(square.y, (float)(config.screenHeight - square.size));


}
*/
void Square::draw()
{
	// Position the rectangle used to draw the square
	rectangle.setPosition(x, y);

	// Draw the square
	window.draw(rectangle);
}
