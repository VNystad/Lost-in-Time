
#include <iostream>
#include <map>
#include "physics.h"

void Physics::Movement(PlayerTest* p, int** collidableArray, float delta) {
    //This function handles movement to the left or to the right. The object will gradually reach its max velocity
    //which it is limited by, and also gradually slow down at different rates wether one tries to move the
    //object to the other direction or not.

    //Checks for trying to move to the left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        p->SetMovDir(0); //Means to the left
        p->SetSlowDownL(false);
    }
    else
        p->SetSlowDownL(true); //Object does not accelerate to left, should slow down if moving to left

    //Check for trying to move to the right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        p->SetMovDir(1); //Means to the right
        p->SetSlowDownR(false);
    }
    else
        //Object does not accelerate to the right, should slow down if moving to the right
        p->SetSlowDownR(true);

    /*********************
     * Left speed handler
     *********************/
    //If the object is moving to the left OR the movespeed to the left is greater than zero

    if (p->GetMovDir() == 0 || p->GetMoveSpeedL() > 0) {
        if (p->GetSlowDownL()) {
            if (p->GetMoveSpeedL() >= p->GetMovePower() * p->GetHorBrake() && p->GetMovDir() == 0)
            {
                //Trying to move the opposite direction of currently move direction, slows down pretty fast
                p->SetMoveSpeedL(p->GetMoveSpeedL() - p->GetMovePower() * p->GetHorBrake());
            }
            else if (p->GetMoveSpeedL() >= p->GetMovePower() * p->GetRegularBrake())
            {
                //Not accelerating nor trying to stop, slows down slowly
                p->SetMoveSpeedL(p->GetMoveSpeedL() - p->GetMovePower() * p->GetRegularBrake());
            }
            else
            {
                p->SetMoveSpeedL(0);
            }
            //Prevents the object from moving in the opposite direction if it tries to stop
        }
        else if (p->GetMoveSpeedL() < p->GetMaxMoveSpeed())
            //The current speed is increased if the object has not yet reached its max speed
            p->SetMoveSpeedL(p->GetMoveSpeedL() + p->GetMovePower());

        //The object is actually being moved

        /*
        if(HorisontalCollision(p, collidabletiles))
        {
            p->SetMoveSpeedL(0);
            p->SetPositionX(p->GetPositionX() + p->GetMoveSpeedL() * delta);
        }
        else
            p->SetPositionX(p->GetPositionX() - p->GetMoveSpeedL() * delta);
        std::cout << p->GetMoveSpeedL() << std::endl;
*/

        int pixelstomove = p->GetMoveSpeedL() * delta;
        if(pixelstomove > 1)
        {
            for(int i = pixelstomove; i >= 0; i -= 1)
            {
                if(HorisontalCollision(p, collidableArray))
                {
                    i = -1;
                    p->SetMoveSpeedL(0);
                    p->SetPositionX(p->GetPositionX() + 1);
                }

                else
                    p->SetPositionX(p->GetPositionX() - 1);
                //p->DrawMe();
            }
        }
    }

    /*********************
     * Right speed handler
     *********************/
    //If the object is moving to the right OR the movespeed to the right is greater than zero
    if (p->GetMovDir() == 1 || p->GetMoveSpeedR() > 0)
    {
        if (p->GetSlowDownR())
        {
            if (p->GetMoveSpeedR() >= p->GetMovePower() * p->GetHorBrake() && p->GetMovDir() == 0)
            {
                //Trying to move the opposite direction of currently move direction, slows down pretty fast
                p->SetMoveSpeedR(p->GetMoveSpeedR() - p->GetMovePower() * p->GetHorBrake());
            }
            else if (p->GetMoveSpeedR() >= p->GetMovePower() * p->GetRegularBrake())
            {
                //Not accelerating nor trying to stop, slows down slowly
                p->SetMoveSpeedR(p->GetMoveSpeedR() - p->GetMovePower() * p->GetRegularBrake());
            }
            else
                //Prevents the object from moving in the opposite direction if it tries to stop
                p->SetMoveSpeedR(0);
        }
        else if (p->GetMoveSpeedR() < p->GetMaxMoveSpeed())
            //The current speed is increased if the object has not yet reached its max speed
            p->SetMoveSpeedR(p->GetMoveSpeedR() + p->GetMovePower());

        //The object is actually being moved
        /*
        if(HorisontalCollision(p, collidabletiles))
        {
            p->SetMoveSpeedL(0);
            p->SetPositionX(p->GetPositionX() - 5);
        }
        else
            p->SetPositionX(p->GetPositionX() + p->GetMoveSpeedR() * delta);
*/


        int pixelstomove = p->GetMoveSpeedR() * delta ;
        //std::cout << pixelstomove << std::endl;
        if(pixelstomove > 1)
        {
            for(int i = pixelstomove; i >= 0; i -= 1)
            {
                if(HorisontalCollision(p, collidableArray))
                {
                    i = -1;
                    p->SetMoveSpeedR(0);
                    p->SetPositionX(p->GetPositionX() - 1);
                }

                else
                    p->SetPositionX(p->GetPositionX() + 1);
                //p->DrawMe();
            }
        }
    }
}

void Physics::Gravity(PlayerTest* p, int** collidableArray, float delta)
{
    //Gravity Start-----------------------------------------------------------------------------------------------------

    //Checks if object is in contact with platform,
    //then marks the object as not airborne(jumpcheck) and current fallspeed as 0.
    //Jumpspeed are also resetted for later use.
    if(Grounded(p, collidableArray))
    {
        p->SetJumpCheck(false);
        p->SetFallSpeed(0);
        float temp = p->GetOrigJumpSpeed();
        p->SetJumpSpeed(temp);
    }

        //Check if falling off a platform
        // If the object is not in contact with a platform, and it was not caused by jumping, the object is marked
        // as airborne (jumpcheck) and falling (apexcheck, reached the apex, on the way down).
    else if(!p->GetJumpCheck())
    {
        p->SetJumpCheck(true);
        p->SetApexCheck(true);
    }

    //Tries to make the object jump when Up key is pressed,
    //but only succeeds if the object is not already airborne (jumpcheck).
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !p->GetJumpCheck())
    {
        p->SetJumpCheck(true);
        p->SetApexCheck(false);
    }

    //Functionality for ascending or falling when the object is marked as airborne (jumpcheck).
    if(p->GetJumpCheck())
    {
        //The Object ascends at a decreasing rate when the object is marked as ascending (apexcheck).
        if(p->GetJumpSpeed() >= 0 && !p->GetApexCheck())
        {

            float pixelstomove = ((( p->GetJumpPower() * p->GetJumpSpeed() ) / p->GetGravity() ) * (delta));
            p->SetJumpSpeed(p->GetJumpSpeed() - 1);
            //Martins carefull movement mechanism:
            //  -Makes the object check every pixel it moves for collision, prevents object in falling through the ground
            //  Bug: It might move 1 pixel into the ground, must investigate
            for(float i = pixelstomove; i >= 0; i -= 1)
            {
                if(Roofed(p, collidableArray))
                {
                    i = -1;
                    p->SetApexCheck(true);
                }

                else
                    p->SetPositionY(p->GetPositionY() - 1);
                //p->DrawMe();
            }
        }
            //The Object is descending (apexcheck) as well ass airborne (jumpcheck),
            //and therefore descends at an increasing rate because of how gravity works.
        else
        {
            p->SetApexCheck(true);
            float pixelstomove = (p->GetJumpPower() * p->GetFallSpeed() / p->GetGravity() * (delta));

            //Martins carefull movement mechanism:
            //  -Makes the object check every pixel it moves for collision, prevents object in falling through the ground
            //  Bug: It might move 1 pixel into the ground, must investigate
            for(float i = pixelstomove; i >= 0; i -= 1)
            {
                if(Grounded(p, collidableArray))
                {
                    i = -1;
                }

                else
                    p->SetPositionY(p->GetPositionY() + 1);
                //p->DrawMe();
            }

            //Fallspeed cannot exceed the max fallspeed, the real life equivalent of wind resistance limiting
            //a falling objects fallspeed.
            if(p->GetFallSpeed() < p->GetMaxFallSpeed())
            {
                p->SetFallSpeed(p->GetFallSpeed() + 1);
            }
        }
    }
    //Gravity End-------------------------------------------------------------------------------------------------------
}


/**
 * Function that checks if there is a horisontal collision
 * @param p the player
 * @param collidabletiles Map with all collidable tiles
 * @return True if there is a block infront of player, false if not
 */
bool Physics::HorisontalCollision(PlayerTest* p, int** collidableArray)
{
    int upperPlayerYArrayCoord = p->GetPositionY() / 32;
    int lowerPlayerArrayCoord = upperPlayerYArrayCoord +1;
    int playerWestCoord = (p->GetPositionX() / 32) -1;
    int playerEastCoord = playerWestCoord +1;


    if(collidableArray[upperPlayerYArrayCoord][playerWestCoord] || collidableArray[upperPlayerYArrayCoord][playerEastCoord] ||
        collidableArray[lowerPlayerArrayCoord][playerWestCoord] || collidableArray[lowerPlayerArrayCoord][playerEastCoord])
    {
        return true;
    }
}


/*************************************************************
 * checks if player is in touch with a collidable tile beneath
 * @param p the player
 * @param collidableArray 2d array with all collidable tiles
 * @return true if on top of a tile, else false
 */
bool Physics::Grounded(PlayerTest* p, int** collidableArray)
{
    int playerArrayCoordX = p->GetPositionX() / 32;
    int playerSouthCoord = (p->GetPositionY()+50) / 32;

    if(collidableArray[playerSouthCoord][playerArrayCoordX] != 0)
    {
        return true;
    }
}

/*******************************************************
 * Checks if player "head" is in touch with a tile above
 * @param p the player
 * @param collidableArray 2d array with all collidable tiles
 * @return true if in touch with tile above, else false
 */
bool Physics::Roofed(PlayerTest* p, int** collidableArray)
{
    int playerArrayCoordX = p->GetPositionX() / 32;
    int playerNorthCoord = (p->GetPositionY()) / 32;

    if(collidableArray[playerNorthCoord -1][playerArrayCoordX] != 0)
    {
        return true;
    }
}