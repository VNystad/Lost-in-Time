#include <iostream>
#include <SFML/Window.hpp>
#include "game.h"

bool Game::init()
{
    collidabletiles = new std::map<int, Tile*>;

    // Load map information from JSON into object list
    if (!Map::load("data/map.json", objects))
    {
        std::cout << "Failed to load map data." << std::endl << std::endl;
        return false;
    }

    // Standard SFML setup
    window.create(sf::VideoMode(config.GetScreenWidth(), config.GetScreenHeight()), "Lost in Time");

    // Double the size of the screen
    sf::View view = window.getDefaultView();
    view.setSize(view.getSize().x, view.getSize().y);
    view.setCenter(view.getCenter().x, view.getCenter().y);
    window.setView(view);

    // Window settings
    window.setVerticalSyncEnabled(true);
    window.setMouseCursorVisible(false);
    window.setFramerateLimit(60);

    playergroundbox.character.setFillColor(sf::Color::Transparent);
    playervisbox.character.setFillColor(sf::Color::Red);


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
                exit(0);

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
                // If playergroundbox press esc, window will close
                if (event.key.code == sf::Keyboard::Escape)
                    exit(0);

                break;



            default:
                // Ignore the other events
                break;
        }
    }

    move(deltaTime);

    window.clear(sf::Color::Black);

    // Process and render each object
    for (Object *object : objects)
    {
        //object->process(deltaTime);
        object->draw(window, collidabletiles);
    }

    playergroundbox.draw();
    playervisbox.draw();

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
    /*
    playergroundbox.x = std::max(playergroundbox.x, 0);
    playergroundbox.x = std::min(playergroundbox.x, (config.screenWidth - playergroundbox.size));
    playergroundbox.y = std::max(playergroundbox.y, 0);
    playergroundbox.y = std::min(playergroundbox.y, (config.screenHeight - playergroundbox.size));
     */
}

void Game::movement(float delta)
{
    //This function handles movement to the left or to the right. The object will gradually reach its max velocity
    //which it is limited by, and also gradually slow down at different rates wether one tries to move the
    //object to the other direction or not.

    //Checks for trying to move to the left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        playergroundbox.movedirection = 0; //Means to the left
        playergroundbox.slowingdownleft = false;
    }
    else
        playergroundbox.slowingdownleft = true; //Object does not accelerate to left, should slow down if moving to left

    //Check for trying to move to the right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        playergroundbox.movedirection = 1; //Means to the right
        playergroundbox.slowingdownright = false;
    }
    else
        playergroundbox.slowingdownright = true; //Object does not accelerate to the right, should slow down if moving to the right

    //Left speed handler
    //If the object is moving to the left OR the movespeed to the left is greater than zero
    if(playergroundbox.movedirection == 0 || playergroundbox.movespeedleft > 0)
    {
        if(playergroundbox.slowingdownleft == true)
        {
            if(playergroundbox.movespeedleft >= playergroundbox.movepower*2 && playergroundbox.movedirection == 1)
            {
                //Trying to move the opposite direction of currently move direction, slows down pretty fast
                playergroundbox.movespeedleft -= playergroundbox.movepower*2;
            }
            else if(playergroundbox.movespeedleft >= playergroundbox.movepower/2)
            {
                //Not accelerating nor trying to stop, slows down slowly
                playergroundbox.movespeedleft -= playergroundbox.movepower/2;
            }
            else
            {
                //Prevents the object from moving in the opposite direction if it tries to stop
                playergroundbox.movespeedleft = 0;
            }
        }
        else if(playergroundbox.movespeedleft < playergroundbox.maxmovespeed)
            //The current speed is increased if the object has not yet reached its max speed
            playergroundbox.movespeedleft += playergroundbox.movepower;

        //The object is actually being moved
        playergroundbox.x -= playergroundbox.movespeedleft * delta;
        playervisbox.x -= playergroundbox.movespeedleft * delta;
    }

    //Right speed handler
    //If the object is moving to the right OR the movespeed to the right is greater than zero
    if(playergroundbox.movedirection == 1 || playergroundbox.movespeedright > 0)
    {
        if(playergroundbox.slowingdownright == true)
        {
            if(playergroundbox.movespeedright >= playergroundbox.movepower*2 && playergroundbox.movedirection == 0)
            {
                //Trying to move the opposite direction of currently move direction, slows down pretty fast
                playergroundbox.movespeedright -= playergroundbox.movepower*2;
            }
            else if(playergroundbox.movespeedright >= playergroundbox.movepower/2)
            {
                //Not accelerating nor trying to stop, slows down slowly
                playergroundbox.movespeedright -= playergroundbox.movepower/2;
            }
            else
                //Prevents the object from moving in the opposite direction if it tries to stop
                playergroundbox.movespeedright = 0;
        }
        else if(playergroundbox.movespeedright < playergroundbox.maxmovespeed)
            //The current speed is increased if the object has not yet reached its max speed
            playergroundbox.movespeedright += playergroundbox.movepower;

        //The object is actually being moved
        playergroundbox.x += playergroundbox.movespeedright * delta;
        playervisbox.x += playergroundbox.movespeedright * delta;
    }
}

void Game::gravity(float delta)
{
    //Gravity Start-----------------------------------------------------------------------------------------------------

    //Checks if object is in contact with platform,
    //then marks the object as not airborne(jumpcheck) and current fallspeed as 0.
    //Jumpspeed are also resetted for later use.
    if(grounded())
    {
        playergroundbox.jumpcheck = 0;
        playergroundbox.fallspeed = 0;
        playergroundbox.jumpspeed = playergroundbox.orgjumpspeed;
    }

        //Check if falling off a platform
        // If the object is not in contact with a platform, and it was not caused by jumping, the object is marked
        // as airborne (jumpcheck) and falling (apexcheck, reached the apex, on the way down).
    else if(!playergroundbox.jumpcheck)
    {
        playergroundbox.jumpcheck = true;
        playergroundbox.apexcheck = true;
    }

    //Tries to make the object jump when Up key is pressed,
    //but only succeeds if the object is not already airborne (jumpcheck).
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && playergroundbox.jumpcheck == 0)
    {
        playergroundbox.jumpcheck = true;
        playergroundbox.apexcheck = false;
    }

    //Functionality for ascending or falling when the object is marked as airborne (jumpcheck).
    if(playergroundbox.jumpcheck)
    {
        //The Object ascends at a decreasing rate when the object is marked as ascending (apexcheck).
        if(playergroundbox.jumpspeed >= 0 && !playergroundbox.apexcheck)
        {
            playergroundbox.y -= ((playergroundbox.jumppower*playergroundbox.jumpspeed)/((playergroundbox.gravity*playergroundbox.gravity)/2))*(delta);
            playervisbox.y -= ((playergroundbox.jumppower*playergroundbox.jumpspeed)/((playergroundbox.gravity*playergroundbox.gravity)/2))*(delta);
            playergroundbox.jumpspeed -= 1;
        }
            //The Object is descending (apexcheck) as well ass airborne (jumpcheck),
            //and therefore descends at an increasing rate because of how gravity works.
        else
        {
            playergroundbox.apexcheck = true;
            float pixelstomove = ((playergroundbox.fallspeed)*playergroundbox.gravity*playergroundbox.gravity/2)*(delta);

            //Meant to improve collision detection, but grounded seems to be false all the time.
            //For some reason, the grounded check earlier in the code checks instead which makes the object
            //move inside the platform a little bit.
            for(float i = pixelstomove; i >= 0; i -= 1 )
            {
                if(grounded())
                {
                    i = -1;
                    //playergroundbox.y -= playergroundbox.size*0.75;
                }

                else
                {
                    playergroundbox.y += 1;
                    playervisbox.y += 1;
                }

                //playergroundbox.draw();
            }

            //Fallspeed cannot exceed the max fallspeed, the real life equivalent of wind resistance limiting
            //a falling objects fallspeed.
            if(playergroundbox.fallspeed < playergroundbox.maxfallspeed)
            {
                playergroundbox.fallspeed += 1;
            }
        }
    }
    //Gravity End-------------------------------------------------------------------------------------------------------
}

bool Game::grounded()
{
    //Layer tempLayer(tileSize);

    for (auto x : *collidabletiles )
    {
        //std::cout << "playergroundbox x, playergroundbox y: " << playergroundbox.x / 32 << " " << playergroundbox.y % 32 << std::endl;
        //std::cout << "x , y: " << x.second->GetXCoord() << " " << x.second->GetYCoord() << std::endl;

        if((playergroundbox.x / 32) == x.second->GetXCoord()  && (playergroundbox.y / 32) == (x.second->GetYCoord()))
        {
            std::cout << "playergroundbox x, playergroundbox y: " << playergroundbox.x  << " " << playergroundbox.y  << std::endl;
            std::cout << "x , y: " << x.second->GetXCoord() * 32 << " " << x.second->GetYCoord() * 32 << std::endl;

            //std::cout << "COLLISION" << std::endl;
            return true;
        }
    }
    /*if (playergroundbox.y > 150 && playergroundbox.y < 250) // Gives error when running
    if (tempLayer.collidable[playergroundbox.x][playergroundbox.y] != 0)
    else
      //  return true;*/
    return false;
}
