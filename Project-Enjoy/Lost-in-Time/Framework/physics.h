#ifndef LOST_IN_TIME_PHYSICS_H
#define LOST_IN_TIME_PHYSICS_H

#include "../Objects/playerobject.h"
#include "../Enemy/AIEnemies.h"
#include "../Objects/princessobject.h"
#include "../Map/tile.h"
#include <vector>


class Physics
{
public:
    static void Movement(PlayerObject* p, int** collidableArray, float delta);
    static void Gravity(PlayerObject* p, int** collidableArray, float delta);

    static bool HorisontalCollision(PlayerObject* p, int** collidableArray);
    static bool Grounded(PlayerObject* p, int** collidableArray);
    static bool Roofed(PlayerObject* p, int** collidableArray);


    static void AIMovement(AIEnemies* e, PlayerObject* p, std::vector<AIEnemies*>* AIVector, int i, int** collidableArray, float delta);
    static void AIGravity(AIEnemies* e, int** collidableArray, float delta);

    static bool AIHorisontalCollision(AIEnemies* e, int** collidableArray);
    static bool AIGrounded(AIEnemies* e, int** collidableArray);
    static bool AIRoofed(AIEnemies* e, int** collidableArray);

    static void Hurt(PlayerObject* p, AIEnemies* e, int* i, std::vector<AIEnemies*>* AIVector);
    static void AISelfCollision(AIEnemies* e,  int* i, std::vector<AIEnemies*>* AIVector);

    //Special for special princess
    static void PrincessMovement(PrincessObject* p, int** collidableArray, float delta);
    static void PrincessGravity(PrincessObject* p, int** collidableArray, float delta);
    static bool PrincessHorisontalCollision(PrincessObject* p, int** collidableArray);
    static bool PrincessGrounded(PrincessObject* p, int** collidableArray);
    static bool PrincessRoofed(PrincessObject* p, int** collidableArray);

private:

};


#endif