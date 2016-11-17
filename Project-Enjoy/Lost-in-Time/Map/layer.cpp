#include <SFML/Graphics.hpp>
#include <iostream>

#include "layer.h"

void Layer::draw(sf::RenderWindow& window)
{
    //std::cout << "Counter = " << count << std::endl;
	// Render each tile
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
            // Skip empty tiles
			if (tilemap[x][y] == 0)
				continue;

			int tileid = tilemap[x][y];

			// Texture coordinates
			int tilex, tiley;
			getTileCoords(tileid, tilex, tiley);

            if(count < height * width)
            {
                ++count;
                //collidableArray[y][x] = tileid;
            }

			// Using vertex arrays or permanent sprites would be faster
            sf::Sprite sprite(*texture, sf::IntRect(tilex, tiley, tileSize.x, tileSize.y));
            sprite.setPosition((float)(x * tileSize.x), (float)(y * tileSize.y));

			window.draw(sprite);
		}
	}
}
