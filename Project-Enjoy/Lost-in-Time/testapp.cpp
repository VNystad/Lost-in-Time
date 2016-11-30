#include <iostream>
#include "testapp.h"
#include "Framework/physics.h"

TestApp::TestApp()
{
    this->config = config;
    this->window = window;

    /*************************************************
     * Making 2D array for collidable tiles
     ************************************************/
    collidableArray = new int*[ArraySize];
    collidableArray[0] = new int[ArraySize * ArraySize];
    for (int i = 1; i < ArraySize; i++)
    {
        collidableArray[i] = collidableArray[i - 1] + ArraySize;
    }

    /*************************************************
     * Load map information from JSON into object list
     ************************************************/
    if (!Map::load("data/map.json", objects, collidableArray))
    {
        std::cout << "Failed to load map data." << std::endl << std::endl;
    }

    /*****************************************
     * Create Window
     ****************************************/
    window = new sf::RenderWindow;
    window->create(sf::VideoMode(1024/*config->GetScreenWidth()*/, 576/*config->GetScreenHeight()*/), "Lost in Time");
    window->setVerticalSyncEnabled(true);
    window->setFramerateLimit(60);
    window->setMouseCursorVisible(false);

    /*****************************************
     * Set camera position in middle of screen
     ****************************************/

    sf::View view = window->getDefaultView();
    view.setSize(view.getSize().x, view.getSize().y);
    view.setCenter(view.getCenter().x, view.getCenter().y);
    window->setView(view);

    /********************|
     * Create the player
     *******************/
    p = new PlayerTest(180, 1, *config, window);

    /***********************************
     * Creating AI
     * Using vector to keep track on AIs
     **********************************/
    AIVectorPointer->push_back(new AIEnemies(1003, 694, 25, *config, window));
    AIVectorPointer->push_back(new AIEnemies(354, 1230, 200, *config, window));
    //AIVectorPointer->push_back(new AIEnemies(360, 1230, 200, *config, window));
    //AIVectorPointer->push_back(new AIEnemies(1003, 694, 25, *config, window));
    AIVectorPointer->push_back(new AIEnemies(2830, 500, 100, *config, window));
    AIVectorPointer->push_back(new AIEnemies(500, 150, 60, *config, window));

    /********************
     * Create the clock
     * Used to find delta
     *******************/
    clock = new sf::Clock;
    clock->restart();

    /***********************************
     * Creating Timer and text for timer
     **********************************/
    timer = new sf::Clock();
    timerInText = new sf::Text;
    timerInText->setCharacterSize(20);
    timerInText->setStyle(sf::Text::Bold);
    timerInText->setFillColor(sf::Color::Red);
    timerInText->setOutlineColor(sf::Color::Green);
    timerInText->setOutlineThickness(2);

}

bool TestApp::Tick()
{
    sf::Event event;
    float delta = clock->restart().asSeconds();

    /************************
     * Gets time elapsed and
     * place it in text form
     ***********************/
    int timeelapsed = timer->getElapsedTime().asSeconds() + penaltyTime;
    std::string tempForTime = std::to_string(timeelapsed);
    timerInText->setString(tempForTime);
    // Positioning the timerInText on upper right corner of player
    // Now just for testing above player to the right
    timerInText->setPosition(p->GetPositionX() + 50,p->GetPositionY() - 50);

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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        std::cout << p->GetPositionX() << " " << p->GetPositionY() << std::endl;

    // When player presses G, player character is damaged. For testing purposes
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && p->health.GetActualLifePoints() > 0)
        p->health.Hit(5);

    // When player presses H, player character is healed. For testing purposes
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && p->health.GetActualLifePoints() < 100)
        p->health.Healed(5);

    /* If player hits the bottom of map,
     * the player's lifepoint is reduced to 0 and player death function is called */
    if (p->GetPositionY() >= 2500)
    {
        penaltyTime = penaltyTime + 20;
        p->health.DeathHandle();
        p->PlayerDead();
        timer->restart();
    }

    if (p->health.Dead())
    {
        penaltyTime = penaltyTime + 20;
        p->health.DeathHandle();
        p->PlayerDead();
        timer->restart();
    }

    p->PlayerAnimation();

    /***********************
     * Handles player and AI
     * movements
     **********************/
    Move(delta);

    window->clear(sf::Color::Black);


    // Process and render each object
    for (Object *object : objects)
    {
        //object->process(deltaTime);
        object->draw(*window);
    }

    p->DrawMe();
    p->health.DrawMe();
    window->draw(*timerInText);

    AIHandler(delta);

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
     * The delta| float is there for smoothness
     ****************************************************/
void TestApp::Move(float delta)
{
    Physics::Movement(p, collidableArray, delta);
    Physics::Gravity(p, collidableArray, delta);
}

/**
 * AIHandler handles all the AI, and sends each of them
 * through the same process as the player(animation, drawing, physics
 * and AI ofcourse).
 * @param delta
 */
void TestApp::AIHandler(float delta)
{
    for(unsigned int i = 0; i < AIVector.size(); i++)
    {
        /* If AI hits the bottom of map,
        * the AI's lifepoint is reduced to 0 and AI death function is called */
        if (AIVectorPointer->at(i)->GetPositionY() >= 2500)
        {
            AIVectorPointer->at(i)->health.Hit(AIVectorPointer->at(i)->health.GetOriginalLifePoints());
        }

        if (AIVectorPointer->at(i)->health.GetActualLifePoints() <= 0)//Dead())
        {
            AIVectorPointer->at(i)->health.DeathHandle();
            //AIVectorPointer->at(i)->Death();
            AIVectorPointer->erase(AIVectorPointer->begin() + i);
        }
        else
        {
            AIVectorPointer->at(i)->AnimationAI();
            AIVectorPointer->at(i)->DrawMe();
            AIVectorPointer->at(i)->MonkeyAI1(AIVectorPointer->at(i), p);
            Physics::AIMovement(AIVectorPointer->at(i), p, AIVectorPointer, i, collidableArray, delta);
            Physics::AIGravity(AIVectorPointer->at(i), collidableArray, delta);
        }
    }
}