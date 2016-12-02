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
#include "Enemy/AIEnemies.h"
#include "Framework/Music.h"

class TestApp
{
public:
    TestApp(sf::RenderWindow& window);
    bool Tick();
    void Move(float delta);
    void AIHandler(float delta);
protected:

    const int ArraySize = 1000;
    int** collidableArray;

    //Dependensies
    PlayerTest* p;

    std::vector<AIEnemies*>* AIVectorPointer = &AIVector;
    std::vector<AIEnemies*> AIVector;

    Config* config;
    std::list<Object*> objects;
    sf::Clock* clock;
    sf::RenderWindow* window;

    // Stuff for timer
    sf::Clock* timer;
    sf::Text* timerInText;
    int penaltyTime = 0;

    Camera camera;
    Music* music;
};


#endif