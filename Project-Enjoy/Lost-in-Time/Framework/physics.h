#ifndef LOST_IN_TIME_PHYSICS_H
#define LOST_IN_TIME_PHYSICS_H

#include "../Objects/playertest.h"
#include "../Map/tile.h"

class Physics
{
public:
    static void Gravity(PlayerTest* p, std::map<int, Tile*>* collidabletiles, float delta);
    static void Movement(PlayerTest* p, std::map<int, Tile*>* collidabletiles, float delta);
    static bool Grounded(PlayerTest* p, std::map<int, Tile*>* collidabletiles);


};


#endif
