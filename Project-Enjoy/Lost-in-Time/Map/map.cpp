#include <fstream>
#include <cstring>
#include <jsoncpp/json/json.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"
#include "sprite.h"

bool Map::load(std::string filename, std::list<Object*>& objects, int** collidableArray)
{
	// Will contain the data we read in
	Json::Value root;

	// Parses the file
	Json::Reader reader;

	// Stream used for reading the data file. The data file has been saved as JSON in Tiled
	std::ifstream file(filename);

	// Read data from file into root object
	bool parsingSuccessful = reader.parse(file, root);
    if (parsingSuccessful)
        std::cout << "Succesfully read from file into root object." << std::endl << std::endl;

	// Get tile size information
	TileSize tileSize;
    tileSize.x = root["tilesets"][0u]["tilewidth"].asInt();
    tileSize.y = root["tilesets"][0u]["tileheight"].asInt();
    tileSize.s = root["tilesets"][0u]["spacing"].asInt();

	// Read in each layer
	for (Json::Value& layer: root["layers"])
	{
		if (layer["name"].asString() != "objects")
			loadLayer(layer, objects, tileSize, collidableArray);
        else
			loadObjects(root, layer, objects, tileSize);
	}

	// Read in tileset (Should be handled by a resource handler)
	sf::Texture* tileset = new sf::Texture();
	tileset->loadFromFile("data/tileset.png");

	// Assign tileset to every object
	for (Object* object: objects)
		object->texture = tileset;

	return true;
}

void Map::loadLayer(Json::Value& layer, std::list<Object*>& objects, TileSize tileSize, int** collidableArray)
{
	Layer* tmp = new Layer(tileSize);

	// Store info on layer
	tmp->width = layer["width"].asInt();
	tmp->height = layer["height"].asInt();

	// Clear tilemap
	memset(tmp->tilemap, 0, sizeof(tmp->tilemap));

	// Read in tilemap
	for (size_t i = 0; i < layer["data"].size(); i++)
    {
		tmp->tilemap[i % tmp->width][i / tmp->width] = layer["data"][(int) i].asInt();


    }

	if((layer["name"].asString() == "foreground"))
    {
		int count = 0;

		// Add tile id to array from layer"data"
        for (int y = 0; y < tmp->height; y++)
        {
            for (int x = 0; x < tmp->width; x++)
            {
				collidableArray[y][x] = layer["data"][count].asInt();
				count++;
            }
        }
    }

	objects.push_back(tmp);
}

void Map::loadObjects(Json::Value& root, Json::Value& layer, std::list<Object*>& objects, TileSize tileSize)
{
	// Get all objects from layer
	for (Json::Value& object: layer["objects"])
	{
		Sprite* sprite = new Sprite(tileSize);

		// Load basic object info
		sprite->x = object["x"].asInt();
		sprite->y = object["y"].asInt() - sprite->tileSize.y;
		sprite->id = object["gid"].asInt();

		// Load animation data
		Json::Value& tileInfo = root["tilesets"][0u]["tiles"][std::to_string(sprite->id - 1)];
		sprite->frame = 0;
		sprite->frameCount = tileInfo["animation"].size();
		sprite->frameDuration = tileInfo["animation"][0u]["duration"].asInt();

		objects.push_back(sprite);
	}

}
