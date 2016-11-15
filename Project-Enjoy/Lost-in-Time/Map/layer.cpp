#include <SFML/Graphics.hpp>
#include <iostream>

#include "layer.h"

void Layer::draw(sf::RenderWindow& window, std::map<int, Tile*>* collidabletiles)
{

    //std::cout << "Counter = " << count << std::endl;
	// Render each tile
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int tileid = tilemap[x][y];
            //std::cout << tileid << std::endl;
			// Skip empty tiles
			if (tilemap[x][y] == 0)
				continue;

			// Texture coordinates
			int tilex, tiley;
			getTileCoords(tileid, tilex, tiley);


            if(count < 100)
            {
                ++count;
                collidabletiles->emplace(count, new Tile(x, y));
            }

			// Using vertex arrays or permanent sprites would be faster
            sf::Sprite sprite(*texture, sf::IntRect(tilex, tiley, tileSize.x, tileSize.y));
            sprite.setPosition((float)(x * tileSize.x), (float)(y * tileSize.y));

			window.draw(sprite);
		}
	}
}
