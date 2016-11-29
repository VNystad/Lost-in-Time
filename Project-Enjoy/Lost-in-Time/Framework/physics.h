#ifndef LOST_IN_TIME_PHYSICS_H
#define LOST_IN_TIME_PHYSICS_H

#include "../Objects/playertest.h"
#include "../Enemy/AIEnemies.h"
#include "../Map/tile.h"
#include <vector>


class Physics
{
public:
    static void Movement(PlayerTest* p, int** collidableArray, float delta);
    static void Gravity(PlayerTest* p, int** collidableArray, float delta);

    static bool HorisontalCollision(PlayerTest* p, int** collidableArray);
    static bool Grounded(PlayerTest* p, int** collidableArray);
    static bool Roofed(PlayerTest* p, int** collidableArray);


    static void AIMovement(AIEnemies* e, PlayerTest* p, std::vector<AIEnemies*>* AIVector, int i, int** collidableArray, float delta);
    static void AIGravity(AIEnemies* e, int** collidableArray, float delta);

    static bool AIHorisontalCollision(AIEnemies* e, int** collidableArray);
    static bool AIGrounded(AIEnemies* e, int** collidableArray);
    static bool AIRoofed(AIEnemies* e, int** collidableArray);


    static void Hurt(PlayerTest* p, AIEnemies* e, int* i, std::vector<AIEnemies*>* AIVector);
    static void AISelfCollision(AIEnemies* e, int* i, std::vector<AIEnemies*>* AIVector);


private:



};


#endif
