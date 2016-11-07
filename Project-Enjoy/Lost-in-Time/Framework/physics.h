#ifndef LOST_IN_TIME_PHYSICS_H
#define LOST_IN_TIME_PHYSICS_H

#include "../Objects/playertest.h"
#include "../Objects/testcollidableplatform.h"

class Physics
{
public:
    static void Gravity(PlayerTest* p, TestCollidablePlatform* platform1, TestCollidablePlatform* platform2, float delta);
    static void Movement(PlayerTest* p, TestCollidablePlatform* platform1, TestCollidablePlatform* platform2, float delta);
    static bool Grounded(PlayerTest* p, TestCollidablePlatform* platform1, TestCollidablePlatform* platform2);


protected:





    // player variables


    /***************
     * Dependencies
     **************/
    TestCollidablePlatform* platform;
};


#endif //LOST_IN_TIME_PHYSICS_H
