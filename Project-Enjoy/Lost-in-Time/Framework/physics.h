#ifndef LOST_IN_TIME_PHYSICS_H
#define LOST_IN_TIME_PHYSICS_H

#include "../Objects/playertest.h"
#include "../Map/tile.h"

class Physics
{
public:
    static void Movement(PlayerTest* p, int** collidableArray, float delta);
    static bool HorisontalCollision(PlayerTest* p, int** collidableArray);

    static void Gravity(PlayerTest* p, int** collidableArray, float delta);
    static bool Grounded(PlayerTest* p, int** collidableArray);
    static bool Roofed(PlayerTest* p, int** collidableArray);

};


#endif
