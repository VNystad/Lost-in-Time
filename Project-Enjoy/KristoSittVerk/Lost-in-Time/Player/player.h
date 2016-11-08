#include <SFML/Graphics.hpp>
#include "../Framework/config.h"

// Simple structure (a class where everything is public) for our square
struct Player
{
    Player(int x, int y, const Config& config, sf::RenderWindow& window);
    void draw();

    const int size = 16;

    float gravity = 9;
    float jumppower = 400;
    const int orgjumpspeed = 15;
    float jumpspeed = orgjumpspeed;

    float fallspeed;
    float maxfallspeed = 800;

    const float maxmovespeed = 400;
    float movepower = 50;

    float movespeedleft = 0;
    float movespeedright = 0;

    //Checks for move direction, 0=Left, 1=Right, 2=Stopped
    int movedirection;

    //Checks if object is slowing down
    bool slowingdownleft;
    bool slowingdownright;

    //Checks for airborne and wether the jump or fall have reached its apex.
    bool jumpcheck = 1;
    bool apexcheck = 1;

    int x, y;

    sf::RectangleShape character;

    // Dependencies
    const Config& config;
    sf::RenderWindow& window;
};