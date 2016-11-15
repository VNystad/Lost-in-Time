#include <iostream>
#include "testapp.h"
#include "Framework/physics.h"
#include "Framework/Camera.h"

TestApp::TestApp() : config(config), window(window)
{

    collidabletiles = new std::map<int, Tile*>;

    // Load map information from JSON into object list
    if (!Map::load("data/map.json", objects))
    {
        std::cout << "Failed to load map data." << std::endl << std::endl;
    }

    //Create window
    window = new sf::RenderWindow;
    window->create(sf::VideoMode(1024/*config->GetScreenWidth()*/, 576/*config->GetScreenHeight()*/), "Test game with animation");
    window->setVerticalSyncEnabled(true);

    //
    sf::View view = window->getDefaultView();
    view.setSize(view.getSize().x, view.getSize().y);
    view.setCenter(view.getCenter().x, view.getCenter().y);
    window->setView(view);

    //Create player
    p = new PlayerTest(180, 200, *config, window);

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
            window->close();
            exit(0);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        window->close();
        exit(0);
    }

    /* If player hits the floor,
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
        object->draw(*window, collidabletiles);
    }

    p->DrawMe();
    window->display();

    if(p->GetPositionX() != camera.PositionX) {

        sf::View view2 = window->getDefaultView();

        view2.setCenter(p->GetPositionX(), p->GetPositionY() );
        window->setView(view2);
    }


    return true;
}

void TestApp::Move(float delta)
{
    //This function will make the object able to move and fall, with correlation to any hinderings such as gravity.
    //The delta float is there for smoothness.
    Physics::Movement(p, collidabletiles, delta);
    Physics::Gravity(p, collidabletiles, delta);
}


