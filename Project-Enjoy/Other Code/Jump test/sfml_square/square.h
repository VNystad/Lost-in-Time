#ifndef SFML_SQUARE_SQUARE_H
#define SFML_SQUARE_SQUARE_H

#include <SFML/Graphics.hpp>

#include "config.h"

// Simple structure (a class where everything is public) for our square
struct Square
{
	Square(float x, float y, const Config& config, sf::RenderWindow& window);
	void move(float delta);
	void draw();

	int orgjumpspeed = 22;
	int jumpspeed = orgjumpspeed;
	int fallspeed;

	const int size = 50;
	const float speed = 400;
	float x, y;
	int jumpcheck = 1;
	int apexcheck = 1;
	int gravity = 9;



	sf::RectangleShape rectangle;

	// Dependencies
	const Config& config;
	sf::RenderWindow& window;
};

#endif
