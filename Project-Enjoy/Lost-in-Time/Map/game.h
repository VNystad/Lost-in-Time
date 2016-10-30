#ifndef GAME_H
#define GAME_H

#include <list>
#include "../Framework/config.h"
#include "../Player/player.h"
#include "bitmask.h"
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
    bool PixelPerfectTest(const sf::Sprite& Object1, const sf::Sprite& Object2, sf::Uint8 AlphaLimit);
    bool gameTick(sf::RenderWindow& window, std::list<Object*>& objects, float deltaTime);

    std::list<Object*> objects;
    sf::Clock clock;
    Player player;
    Config config;
    sf::RenderWindow window;
};

#endif
