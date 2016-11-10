#ifndef OBJECT_H
#define OBJECT_H

#include "tile.h"

namespace sf
{
	class RenderWindow;
	class Texture;
}

// Small helper struct that contains tile size information
struct TileSize
{
	int x = 32; // Width
	int y = 32; // Height
	int s = 0; // Spacing
};

// Class representing any game object
class Object
{
	// Map needs to access protected/private data
	friend class Map;
    friend class Game;

public:
    // Constructor
	Object(TileSize tileSize) : tileSize(tileSize) { }
	virtual ~Object();

	virtual void process(float deltaTime) {}
	virtual void draw(sf::RenderWindow& window, std::map<int, Tile*> *collidabletiles) {}

	// Calculate x and y position of given tile in the texture
	void getTileCoords(int tile, int& x, int& y);

	const TileSize tileSize;

protected:


	sf::Texture* texture;
};

#endif
