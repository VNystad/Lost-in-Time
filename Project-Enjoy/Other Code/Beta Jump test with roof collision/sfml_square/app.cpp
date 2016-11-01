#include <SFML/Window.hpp>

#include "app.h"
#include <iostream>

App::App() : square(200, 200, config, window), platform1(100, 500, config, window), platform2(300, 350, config, window)
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
            if(square.movespeedleft >= square.movepower*2 && square.movedirection == 1)
            {
                //Trying to move the opposite direction of currently move direction, slows down pretty fast
                square.movespeedleft -= square.movepower*2;
            }
            else if(square.movespeedleft >= square.movepower/2)
            {
                //Not accelerating nor trying to stop, slows down slowly
                square.movespeedleft -= square.movepower/2;
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
        square.x -= square.movespeedleft * delta;
    }

    //Right speed handler
    //If the object is moving to the right OR the movespeed to the right is greater than zero
    if(square.movedirection == 1 || square.movespeedright > 0)
    {
        if(square.slowingdownright == true)
        {
            if(square.movespeedright >= square.movepower*2 && square.movedirection == 0)
            {
                //Trying to move the opposite direction of currently move direction, slows down pretty fast
                square.movespeedright -= square.movepower*2;
            }
            else if(square.movespeedright >= square.movepower/2)
            {
                //Not accelerating nor trying to stop, slows down slowly
                square.movespeedright -= square.movepower/2;
            }
            else
                //Prevents the object from moving in the opposite direction if it tries to stop
                square.movespeedright = 0;
        }
        else if(square.movespeedright < square.maxmovespeed)
            //The current speed is increased if the object has not yet reached its max speed
            square.movespeedright += square.movepower;

        //The object is actually being moved
        square.x += square.movespeedright * delta;
    }
}

void App::gravity(float delta)
{
    //Gravity Start-----------------------------------------------------------------------------------------------------

    //Checks if object is in contact with platform,
    //then marks the object as not airborne(jumpcheck) and current fallspeed as 0.
    //Jumpspeed are also resetted for later use.

    //The code wil now also not jump through the roof.
    //Current bugs: Sometimes falls inside landing platform, which also make the code think it crashed into the roof
    //and gets sent to oblivion. I might try to reverse the roof collide code and also prevent it from landing
    //inside the platform as well.

    square.jumpcooldown += delta;
    if(grounded() == true)
    {
        square.jumpcheck = false;
        square.fallspeed = 0;
        square.jumpspeed = square.orgjumpspeed;
        if(square.jumppixelcounter > 30*delta)
        {
            while(grounded() == true)
            {
                square.y += 1;
                square.draw();
            }
            //square.y += 20;
            square.apexcheck = true;
            square.jumppixelcounter = 0;
        }
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && square.jumpcheck == 0 && square.jumpcooldown > 30*delta)
    {
        square.jumpcooldown = 0;
        square.jumpcheck = true;
        square.apexcheck = false;
    }

    //Functionality for ascending or falling when the object is marked as airborne (jumpcheck).
    if(square.jumpcheck == true)
    {
        //The Object ascends at a decreasing rate when the object is marked as ascending (apexcheck).
        if(square.jumpspeed >= 0 && square.apexcheck == false)
        {
            if(grounded() == true && square.jumppixelcounter > 33)
            {
                square.apexcheck = true;
                square.jumppixelcounter = 0;
            }
            else
            {
                square.y -= ((square.jumppower*square.jumpspeed)/square.gravity)*(delta);
                square.jumpspeed -= 1;
                if(square.jumppixelcounter <= 20)
                    square.jumppixelcounter += ((square.jumppower*square.jumpspeed)/square.gravity)*(delta);
            }

        }
            //The Object is descending (apexcheck) as well ass airborne (jumpcheck),
            //and therefore descends at an increasing rate because of how gravity works.
        else
        {
            square.apexcheck = true;
            square.jumppixelcounter = 0;
            float pixelstomove = ((square.jumppower*square.fallspeed)/square.gravity)*(delta);

            //Meant to improve collision detection, but grounded seems to be false all the time.
            //For some reason, the grounded check earlier in the code checks instead which makes the object
            //move inside the platform a little bit.
            for(float i = pixelstomove; i >= 0; i -= 1 )
            {
                if(grounded() == true)
                {
                    i = -1;
                }

                else
                    square.y += 1;
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
    if(square.rectangle.getGlobalBounds().intersects(platform1.platform.getGlobalBounds()) || (square.rectangle.getGlobalBounds().intersects(platform2.platform.getGlobalBounds())))
    {
     return true;
    }
    else
     return false;
}
