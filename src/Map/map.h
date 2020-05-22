#ifndef MAP_H
#define MAP_H

#include <string>
#include <list>
#include <map>
#include "object.h"
#include "layer.h"
#include "../Objects/spawnpoint.h"

namespace Json
{
	class Value;
}

// Class with a single public static function that loads a map into an object list
class Map
{
public:
    // Construtor
    Map() { }

	// Load map from Tiled JSON file
	static bool load(std::string filename, std::list<Object*>& objects, int** collidableArray, std::list<SpawnPoint*>& spawnpointList);

private:

	// Handles regular layers
	static void loadLayer(Json::Value& layer, std::list<Object*>& objects, TileSize tileSize, int** collidableArray);

	// Handles object layers
	static void loadObjects(Json::Value& root, Json::Value& layer, std::list<Object*>& objects, TileSize tileSize);

    // Handles spawn points
	static void loadSpawnPoints(Json::Value& root, Json::Value& layer, std::list<SpawnPoint*>& spawnpoint);
};

#endif
