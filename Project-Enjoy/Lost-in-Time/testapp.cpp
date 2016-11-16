#include <iostream>
#include "testapp.h"
#include "Framework/physics.h"

TestApp::TestApp() : config(config), window(window)
{

    /*************************************************
     * Making 2D array for collidable tiles
     ************************************************/
    collidabletiles = new std::map<int, Tile*>;
    collidableArray = new int*[ArraySize];
    collidableArray[0] = new int[ArraySize * ArraySize];
    for (int i = 1; i < ArraySize; i++)
    {
        collidableArray[i] = collidableArray[i - 1] + ArraySize;
    }

    /*************************************************
     * Load map information from JSON into object list
     ************************************************/
    if (!Map::load("data/map.json", objects))
    {
        std::cout << "Failed to load map data." << std::endl << std::endl;
    }



    /*****************************************
     * Create Window
     ****************************************/
    window = new sf::RenderWindow;
    window->create(sf::VideoMode(1024/*config->GetScreenWidth()*/, 576/*config->GetScreenHeight()*/), "Test game with animation");
    window->setVerticalSyncEnabled(true);

    /*****************************************
     * Set camera position in middle of screen
     ****************************************/

    sf::View view = window->getDefaultView();
    view.setSize(view.getSize().x, view.getSize().y);
    view.setCenter(view.getCenter().x, view.getCenter().y);
    window->setView(view);

    /********************
     * Create the player
     *******************/
    p = new PlayerTest(180, 200, *config, window);

    /********************
     * Create the clock
     * Used to find delta
     *******************/
    clock = new sf::Clock;
    clock->restart();
}

bool TestApp::Tick()
{
    sf::Event event;
    float delta = clock->restart().asSeconds();

    // Get events from OS
    while (window->pollEvent(event))
    {
        // Close the window if the user clicks the x button
        if (event.type == sf::Event::Closed)
        {
            delete[] collidableArray[0];
            delete[] collidableArray;
            window->close();
            exit(0);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        delete[] collidableArray[0];
        delete[] collidableArray;
        window->close();
        exit(0);
    }

    /* If player hits the bottom of map,
     * the player's lifepoint is reduced to 0 and player death function is called */
    if (p->GetPositionY() >= 576/*config->GetScreenHeight()*/ - p->GetSizeHeight())
    {
        p->SetFallSpeed(0);
        //p->health->SetActualLifePoints(0);
        //p->health->SetVisibleLifePoints(0);
        p->PlayerDead();
    }

    Move(delta);

    window->clear(sf::Color::Black);

    // Process and render each object
    for (Object *object : objects)
    {
        //object->process(deltaTime);
        object->draw(*window, collidabletiles, collidableArray);
    }

    p->DrawMe();
    window->display();

    /*****************************************
     * Set camera to follow player position
     ****************************************/
    if(p->GetPositionX() != camera.PositionX) {

        sf::View view2 = window->getDefaultView();

        view2.setCenter(p->GetPositionX()+17, p->GetPositionY()+ 25);
        window->setView(view2);
    }


    return true;
}
    /*****************************************************
     * This function will make the object able
     * to move and fall,
     * with correlation to any hinderings such as gravity.
     * The delta float is there for smoothness
     ****************************************************/
void TestApp::Move(float delta)
{
    Physics::Movement(p, collidableArray, delta);
    Physics::Gravity(p, collidableArray, delta);
}


