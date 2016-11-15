#ifndef LOST_IN_TIME_TESTAPP_H
#define LOST_IN_TIME_TESTAPP_H


#include "Objects/playertest.h"
#include <list>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include "Framework/config.h"
#include "Objects/playertest.h"
#include "Map/map.h"
#include "Framework/Camera.h"

class TestApp
{
public:
    TestApp();
    bool Tick();
    void Move(float delta);
protected:

    //Init success flag
    bool success;

    //running flag
    bool running;

    //Dependensies
    PlayerTest* p;
    std::map<int, Tile*> *collidabletiles;
    Config* config;
    std::list<Object*> objects;
    sf::RenderWindow* window;
    sf::Clock* clock;

    Camera camera;
};


#endif
