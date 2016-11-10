#ifndef LOST_IN_TIME_TESTAPP_H
#define LOST_IN_TIME_TESTAPP_H


#include "Objects/playertest.h"
#include "Objects/testcollidableplatform.h"

class TestApp
{
public:
    TestApp();
    bool Tick();
    bool Grounded();
    void Move(float delta);
    void Movement(float delta);
protected:
    //Pointers to different objects
    PlayerTest* p;
    TestCollidablePlatform* platform1;
    TestCollidablePlatform* platform2;

    //Init success flag
    bool success;

    //running flag
    bool running;

    //Dependensies
    Config* config;
    sf::RenderWindow* window;
    sf::Clock* clock;
};


#endif
