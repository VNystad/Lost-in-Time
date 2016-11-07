#ifndef SPRITE_H
#define SPRITE_H

#include <SFML/System/Clock.hpp>

#include "object.h"

class Sprite : public Object
{
	// Map needs to access protected/private data
	friend class Map;
    friend class Game;

public:
    // Constructor
	Sprite(TileSize tileSize) : Object(tileSize) { }

	void process(float time);
	void draw(sf::RenderWindow& window);

protected:

    // Location on screen
    int x, y;

	// Id of first tile
	int id;

	// Current animation frame
	int frame;

	//Frame count (duh)
	int frameCount;

	// Length of one frame in ms
	int frameDuration;

	// Times the animation
	sf::Clock clock;
};

#endif
