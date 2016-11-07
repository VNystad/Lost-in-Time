#include <iostream>
#include "testapp.h"
#include "Framework/physics.h"

TestApp::TestApp() : config(config), window(window)
{
    //Create window
    window = new sf::RenderWindow;
    window->create(sf::VideoMode(800, 600), "Test game with animation");
    window->setVerticalSyncEnabled(true);

    //Create player
    p = new PlayerTest(180, 250, config, window);

    //Create platforms
    platform1 = new TestCollidablePlatform(200, 200, config, window);
    platform2 = new TestCollidablePlatform(100, 300, config, window);

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

            return false;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        window->close();
        return false;
    }

    Move(delta);

    window->clear(sf::Color::Black);

    p->DrawMe();
    platform1->DrawMe();
    platform2->DrawMe();

    window->display();

    return true;
}

void TestApp::Move(float delta)
{
    //This function will make the object able to move and fall, with correlation to any hinderings such as gravity.
    //The delta float is there for smoothness.

    Physics::Movement(p, platform1, platform2,delta);
    Physics::Gravity(p, platform1, platform2, delta);

    // Keep the box within screen borders
    p->SetPositionX(std::max(p->GetPositionX(), 0.f));
    p->SetPositionX(std::min(p->GetPositionX(), (float) (800 - p->GetSize())));
    //p->SetPositionX(std::min(p->GetPositionX(), (float) (config.screenWidth - p->GetSize())));
    p->SetPositionY(std::max(p->GetPositionY(), 0.f));
    p->SetPositionY(std::min(p->GetPositionY(), (float) (600 - p->GetSize())));
    //p->SetPositionY(std::min(p->GetPositionY(), (float) (config.screenHeight - p->GetSize())));
}


