#include <iostream>
#include <SFML/Window.hpp>
#include "game.h"

bool Game::init()
{
    // Load map information from JSON into object list
    if (!Map::load("data/map.json", objects))
    {
        std::cout << "Failed to load map data." << std::endl << std::endl;
        return false;
    }

    objects.back();

    // Standard SFML setup
    window.create(sf::VideoMode(config.screenWidth, config.screenHeight), "Lost in Time");

    // Double the size of the screen
    sf::View view = window.getDefaultView();
    view.setSize(view.getSize().x, view.getSize().y);
    view.setCenter(view.getCenter().x, view.getCenter().y);
    window.setView(view);

    // Window settings
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);

    return true;
}

void Game::run()
{
    float deltaTime = 0;
    clock.restart();

    // Game loop
    while (!gameTick(window, objects, deltaTime))
    {
        deltaTime = clock.getElapsedTime().asSeconds();
        clock.restart();
    }
}

// Process and draws one frame of the game
bool Game::gameTick(sf::RenderWindow& window, std::list<Object*>& objects, float deltaTime)
{
    sf::Event event;

    // Process events from the OS
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                return true;

            case sf::Event::KeyReleased:
                // Reload map on F5
                if (event.key.code == sf::Keyboard::F5)
                {
                    objects.clear();

                    if (!Map::load("data/map.json", objects))
                    {
                        std::cout << "Failed to reload map data." << std::endl << std::endl;
                        return true;
                    }
                }
                // If player press esc, window will close
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();

                break;



            default:
                // Ignore the other events
                break;
        }
    }

    move(deltaTime);

    window.clear(sf::Color::Black);

    // Process and render each object
    for (Object* object : objects)
    {
        object->process(deltaTime);
        object->draw(window);
    }

    player.draw();

    window.display();

    return false;
}

void Game::move(float delta)
{
    // This function will make the object able to move and fall, with correlation to any hinderings such as gravity.
    // The delta float is there for smoothness.

    movement(delta);
    gravity(delta);

    // Keep the box within screen borders
    player.x = std::max(player.x, 0);
    player.x = std::min(player.x, (config.screenWidth - player.size));
    player.y = std::max(player.y, 0);
    player.y = std::min(player.y, (config.screenHeight - player.size));
}

void Game::movement(float delta)
{
    //This function handles movement to the left or to the right. The object will gradually reach its max velocity
    //which it is limited by, and also gradually slow down at different rates wether one tries to move the
    //object to the other direction or not.

    //Checks for trying to move to the left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        player.movedirection = 0; //Means to the left
        player.slowingdownleft = false;
    }
    else
        player.slowingdownleft = true; //Object does not accelerate to left, should slow down if moving to left

    //Check for trying to move to the right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        player.movedirection = 1; //Means to the right
        player.slowingdownright = false;
    }
    else
        player.slowingdownright = true; //Object does not accelerate to the right, should slow down if moving to the right

    //Left speed handler
    //If the object is moving to the left OR the movespeed to the left is greater than zero
    if(player.movedirection == 0 || player.movespeedleft > 0)
    {
        if(player.slowingdownleft == true)
        {
            if(player.movespeedleft >= player.movepower*2 && player.movedirection == 1)
            {
                //Trying to move the opposite direction of currently move direction, slows down pretty fast
                player.movespeedleft -= player.movepower*2;
            }
            else if(player.movespeedleft >= player.movepower/2)
            {
                //Not accelerating nor trying to stop, slows down slowly
                player.movespeedleft -= player.movepower/2;
            }
            else
            {
                //Prevents the object from moving in the opposite direction if it tries to stop
                player.movespeedleft = 0;
            }
        }
        else if(player.movespeedleft < player.maxmovespeed)
            //The current speed is increased if the object has not yet reached its max speed
            player.movespeedleft += player.movepower;

        //The object is actually being moved
        player.x -= player.movespeedleft * delta;
    }

    //Right speed handler
    //If the object is moving to the right OR the movespeed to the right is greater than zero
    if(player.movedirection == 1 || player.movespeedright > 0)
    {
        if(player.slowingdownright == true)
        {
            if(player.movespeedright >= player.movepower*2 && player.movedirection == 0)
            {
                //Trying to move the opposite direction of currently move direction, slows down pretty fast
                player.movespeedright -= player.movepower*2;
            }
            else if(player.movespeedright >= player.movepower/2)
            {
                //Not accelerating nor trying to stop, slows down slowly
                player.movespeedright -= player.movepower/2;
            }
            else
                //Prevents the object from moving in the opposite direction if it tries to stop
                player.movespeedright = 0;
        }
        else if(player.movespeedright < player.maxmovespeed)
            //The current speed is increased if the object has not yet reached its max speed
            player.movespeedright += player.movepower;

        //The object is actually being moved
        player.x += player.movespeedright * delta;
    }
}

void Game::gravity(float delta)
{
    //Gravity Start-----------------------------------------------------------------------------------------------------

    //Checks if object is in contact with platform,
    //then marks the object as not airborne(jumpcheck) and current fallspeed as 0.
    //Jumpspeed are also resetted for later use.
    if(colliding() == true)
    {
        player.jumpcheck = 0;
        player.fallspeed = 0;
        player.jumpspeed = player.orgjumpspeed;
    }

        //Check if falling off a platform
        // If the object is not in contact with a platform, and it was not caused by jumping, the object is marked
        // as airborne (jumpcheck) and falling (apexcheck, reached the apex, on the way down).
    else if(player.jumpcheck != true)
    {
        player.jumpcheck = true;
        player.apexcheck = true;
    }

    //Tries to make the object jump when Up key is pressed,
    //but only succeeds if the object is not already airborne (jumpcheck).
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.jumpcheck == 0)
    {
        player.jumpcheck = true;
        player.apexcheck = false;
    }

    //Functionality for ascending or falling when the object is marked as airborne (jumpcheck).
    if(player.jumpcheck == true)
    {
        //The Object ascends at a decreasing rate when the object is marked as ascending (apexcheck).
        if(player.jumpspeed >= 0 && player.apexcheck == false)
        {
            player.y -= ((player.jumppower*player.jumpspeed)/player.gravity)*(delta);
            player.jumpspeed -= 1;
        }
            //The Object is descending (apexcheck) as well ass airborne (jumpcheck),
            //and therefore descends at an increasing rate because of how gravity works.
        else
        {
            player.apexcheck = true;
            float pixelstomove = ((player.jumppower*player.fallspeed)/player.gravity)*(delta);

            //Meant to improve collision detection, but colliding seems to be false all the time.
            //For some reason, the colliding check earlier in the code checks instead which makes the object
            //move inside the platform a little bit.
            for(float i = pixelstomove; i >= 0; i -= 1 )
            {
                if(colliding() == true)
                {
                    i = -1;
                }

                else
                    player.y += 1;
            }

            //Fallspeed cannot exceed the max fallspeed, the real life equivalent of wind resistance limiting
            //a falling objects fallspeed.
            if(player.fallspeed < player.maxfallspeed)
            {
                player.fallspeed += 1;
            }
        }
    }
    //Gravity End-------------------------------------------------------------------------------------------------------
}

bool Game::colliding()
{
    tileSize.x = 32;
    tileSize.y = 32;
    tileSize.s = 0;
    Layer tempLayer(tileSize);

    //if (player.y > 150 && player.y < 250)
    //if (tempLayer.collidable[player.x][player.y] != 0) // Gives error when running
        //return true;

    //else
        return false;
}
