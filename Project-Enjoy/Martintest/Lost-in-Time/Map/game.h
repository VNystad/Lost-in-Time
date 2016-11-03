#ifndef GAME_H
#define GAME_H

#include <list>
#include "../Framework/config.h"
#include "../Player/player.h"
#include "map.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>

class Object;

class Game {
public:
    Game();
    bool init();
    void run();

    void move(float delta);
    bool grounded();
    void movement(float delta);
    void gravity(float delta);

protected:
    bool gameTick(sf::RenderWindow& window, std::list<Object*>& objects, float deltaTime);

    std::list<Object*> objects;
    sf::Clock clock;
    Player player;
    Config config;
    sf::RenderWindow window;
};

#endif
