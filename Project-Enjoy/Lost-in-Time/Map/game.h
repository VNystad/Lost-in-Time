#ifndef GAME_H
#define GAME_H

#include <list>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include "../Framework/config.h"
#include "../Player/player.h"
#include "map.h"

class Object;

class Game {
public:
    // Constructor
    Game() : player(200, 200, config, window) {}

    bool init();
    void run();

    void move(float delta);
    bool colliding();
    void movement(float delta);
    void gravity(float delta);

protected:
    bool gameTick(sf::RenderWindow& window, std::list<Object*>& objects, float deltaTime);
    Player player;
    TileSize tileSize;
    Config config;
    std::list<Object*> objects;
    sf::Clock clock;
    sf::RenderWindow window;
};

#endif
