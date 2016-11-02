#ifndef SFML_SQUARE_SQUARE_H
#define SFML_SQUARE_SQUARE_H

#include <SFML/Graphics.hpp>

#include "config.h"

// Simple structure (a class where everything is public) for our square
struct Square
{
	Square(float x, float y, const Config& config, sf::RenderWindow& window);
	void draw();

    const int size = 50;

    //Timer for collision, it basically allows the object to land, but not move through the roof
    float verticalcollisioncooldown;
    float horisontalcollisioncooldown;

    //Horisontal braking speeds
    float brakehorslowdown = 2;
    float regularhorslowdown = 1.5;

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

	float x, y;



	sf::RectangleShape rectangle;

	// Dependencies
	const Config& config;
	sf::RenderWindow& window;
};

#endif
