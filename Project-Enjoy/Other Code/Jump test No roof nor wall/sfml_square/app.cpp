#include <SFML/Window.hpp>

#include "app.h"
#include <iostream>

App::App() : square(200, 200, config, window), platform1(100, 500, config, window), platform2(300, 400, config, window)
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
    //This function will make the object able to move and fall, with correlation to any hinderings such as gravity.
    //The delta float is there for smoothness.

    movement(delta);
    gravity(delta);

	// Keep the box within screen borders
	square.x = std::max(square.x, 0.f);
	square.x = std::min(square.x, (float)(config.screenWidth - square.size));
	square.y = std::max(square.y, 0.f);
	square.y = std::min(square.y, (float)(config.screenHeight - square.size));


}

void App::movement(float delta)
{
    //This function handles movement to the left or to the right. The object will gradually reach its max velocity
    //which it is limited by, and also gradually slow down at different rates wether one tries to move the
    //object to the other direction or not.

    if(grounded() == true)
    {
        square.horisontalcollisioncooldown = 0;
    }
    else
        square.horisontalcollisioncooldown += delta;

    //Checks for trying to move to the left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        square.movedirection = 0; //Means to the left
        square.slowingdownleft = false;
    }
    else
        square.slowingdownleft = true; //Object does not accelerate to left, should slow down if moving to left

    //Check for trying to move to the right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        square.movedirection = 1; //Means to the right
        square.slowingdownright = false;
    }
    else
        square.slowingdownright = true; //Object does not accelerate to the right, should slow down if moving to the right

    //Left speed handler
    //If the object is moving to the left OR the movespeed to the left is greater than zero


    if(square.movedirection == 0 || square.movespeedleft > 0)
    {
        if(square.slowingdownleft == true)
        {
            if(square.movespeedleft >= square.movepower*square.brakehorslowdown && square.movedirection == 1)
            {
                //Trying to move the opposite direction of currently move direction, slows down pretty fast
                square.movespeedleft -= square.movepower*square.brakehorslowdown;
            }
            else if(square.movespeedleft >= square.movepower*square.regularhorslowdown)
            {
                //Not accelerating nor trying to stop, slows down slowly
                square.movespeedleft -= square.movepower*square.regularhorslowdown;
            }
            else
            {
                //Prevents the object from moving in the opposite direction if it tries to stop
                square.movespeedleft = 0;
            }
        }
        else if(square.movespeedleft < square.maxmovespeed)
            //The current speed is increased if the object has not yet reached its max speed
            square.movespeedleft += square.movepower;

        //The object is actually being moved
        float pixelstomove = square.movespeedleft * delta;

        for(float i = pixelstomove; i >= 0; i -= 1 )
        {
            if(grounded() == true && square.horisontalcollisioncooldown >= delta)
            {
                i = -1;
                square.x += 1;
            }

            else if(i != 0)
                square.x -= 1;
            square.draw();
        }
    }

    //Right speed handler
    //If the object is moving to the right OR the movespeed to the right is greater than zero
    if(square.movedirection == 1 || square.movespeedright > 0)
    {
        if(square.slowingdownright == true)
        {
            if(square.movespeedright >= square.movepower*square.brakehorslowdown && square.movedirection == 0)
            {
                //Trying to move the opposite direction of currently move direction, slows down pretty fast
                square.movespeedright -= square.movepower*square.brakehorslowdown;
            }
            else if(square.movespeedright >= square.movepower*square.regularhorslowdown)
            {
                //Not accelerating nor trying to stop, slows down slowly
                square.movespeedright -= square.movepower*square.regularhorslowdown;
            }
            else
                //Prevents the object from moving in the opposite direction if it tries to stop
                square.movespeedright = 0;
        }
        else if(square.movespeedright < square.maxmovespeed)
            //The current speed is increased if the object has not yet reached its max speed
            square.movespeedright += square.movepower;

        //The object is actually being moved
        float pixelstomove = square.movespeedright * delta;

        for(float i = pixelstomove; i >= 0; i -= 1 )
        {
            if(grounded() == true && square.horisontalcollisioncooldown >= delta)
            {
                i = -1;
                square.x -= 1;
            }

            else if(i != 0)
                square.x += 1;
            square.draw();
        }
    }
}

void App::gravity(float delta)
{
    //Gravity Start-----------------------------------------------------------------------------------------------------

    //Checks if object is in contact with platform,
    //then marks the object as not airborne(jumpcheck) and current fallspeed as 0.
    //Jumpspeed are also resetted for later use.
    if(grounded() == true)
    {
        square.jumpcheck = 0;
        square.fallspeed = 0;
        square.jumpspeed = square.orgjumpspeed;
    }

        //Check if falling off a platform
        // If the object is not in contact with a platform, and it was not caused by jumping, the object is marked
        // as airborne (jumpcheck) and falling (apexcheck, reached the apex, on the way down).
    else if(square.jumpcheck != true)
    {
        square.jumpcheck = true;
        square.apexcheck = true;
    }

    //Tries to make the object jump when Up key is pressed,
    //but only succeeds if the object is not already airborne (jumpcheck).
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && square.jumpcheck == 0)
    {
        square.jumpcheck = true;
        square.apexcheck = false;
    }

    //Functionality for ascending or falling when the object is marked as airborne (jumpcheck).
    if(square.jumpcheck == true)
    {
        if(square.verticalcollisioncooldown <= delta)
            square.verticalcollisioncooldown += delta;
        //The Object ascends at a decreasing rate when the object is marked as ascending (apexcheck).
        if(square.jumpspeed >= 0 && square.apexcheck == false)
        {
            float pixelstomove = ((square.jumppower*square.jumpspeed)/square.gravity)*(delta);
            square.jumpspeed -= 1;

            for(float i = pixelstomove; i >= 0; i -= 1 )
            {
                if(grounded() == true && square.verticalcollisioncooldown > delta)
                {
                    i = -1;
                    square.y += 1;
                    square.apexcheck = true;
                }

                else
                    square.y -= 1;
                square.draw();
            }
        }
            //The Object is descending (apexcheck) as well ass airborne (jumpcheck),
            //and therefore descends at an increasing rate because of how gravity works.
        else
        {
            square.verticalcollisioncooldown = 0;
            square.apexcheck = true;
            float pixelstomove = ((square.jumppower*square.fallspeed)/square.gravity)*(delta);

            //Martins carefull movement mechanism:
            //  -Makes the object check every pixel it moves for collision, prevents object in falling through the ground
            //  Bug: It might move 1 pixel into the ground, must investigate
            for(float i = pixelstomove; i >= 0; i -= 1)
            {
                if(grounded() == true)
                {
                    i = -1;
                }

                else
                    square.y += 1;
                square.draw();
            }

            //Fallspeed cannot exceed the max fallspeed, the real life equivalent of wind resistance limiting
            //a falling objects fallspeed.
            if(square.fallspeed < square.maxfallspeed)
            {
                square.fallspeed += 1;
            }
        }
    }
    //Gravity End-------------------------------------------------------------------------------------------------------
}

bool App::grounded()
{
    //Simply checks if the object is currently on the ground
 if(square.rectangle.getGlobalBounds().intersects(platform1.platform.getGlobalBounds()) || square.rectangle.getGlobalBounds().intersects(platform2.platform.getGlobalBounds()))
 {
     return true;
 }
    else
     return false;
}
