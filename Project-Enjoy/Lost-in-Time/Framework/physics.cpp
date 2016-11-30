#include <map>
#include "physics.h"
#include <iostream>



//Horisontal movement for player
void Physics::Movement(PlayerTest* p, int** collidableArray, float delta) {
    //This function handles movement to the left or to the right. The object will gradually reach its max velocity
    //which it is limited by, and also gradually slow down at different rates wether one tries to move the
    //object to the other direction or not.


    //Checks if player got hit by enemy
    if(p->GetPlayerHurt() != 5)
    {
        if(p->GetPlayerHurt() == 2)
        {

            p->SetApexCheck(false);
            p->SetJumpSpeed(10);
            p->SetFallSpeed(0);
        }
        else if(p->GetPlayerHurt() == 0)
        {
            p->SetMoveSpeedR(0);
            p->SetMoveSpeedL(400);
            p->health.Hit(50);
        }
        else if(p->GetPlayerHurt() == 1)
        {
            p->SetMoveSpeedL(0);
            p->SetMoveSpeedR(400);
            p->health.Hit(50);
        }
        p->SetPlayerHurt(5);
    }


    //Checks for trying to move to the left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        p->SetMovDir(0); //Means to the left
        p->SetSlowDownL(false);
    }
    else
        p->SetSlowDownL(true); //Object does not accelerate to left, should slow down if moving to left

    //Check for trying to move to the right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
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
                p->SetMovDir(2);
                p->SetLastMoveDirection(0);
            }
            //Prevents the object from moving in the opposite direction if it tries to stop
        }
        else if (p->GetMoveSpeedL() < p->GetMaxMoveSpeed())
            //The current speed is increased if the object has not yet reached its max speed
            p->SetMoveSpeedL(p->GetMoveSpeedL() + p->GetMovePower());

        //The object is actually being moved
        if(!HorisontalCollision(p, collidableArray))
            p->SetPositionX(p->GetPositionX() - p->GetMoveSpeedL() * delta);
        else
            p->SetMoveSpeedL(0);
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
            {
                p->SetMoveSpeedR(0);
                p->SetMovDir(2);
                p->SetLastMoveDirection(1);
            }
            //Prevents the object from moving in the opposite direction if it tries to stop
        }
        else if (p->GetMoveSpeedR() < p->GetMaxMoveSpeed())
            //The current speed is increased if the object has not yet reached its max speed
            p->SetMoveSpeedR(p->GetMoveSpeedR() + p->GetMovePower());

        //The object is actually being moved
        if(!HorisontalCollision(p, collidableArray))
            p->SetPositionX(p->GetPositionX() + p->GetMoveSpeedR() * delta);
        else
            p->SetMoveSpeedR(0);
    }
}


//Gravity for player
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
                    p->SetApexCheck(true);
                    break;
                }

                else
                    p->SetPositionY(p->GetPositionY() - 1);
            }
        }
            //The Object is descending (apexcheck) as well ass airborne (jumpcheck),
            //and therefore descends at an increasing rate because of how gravity works.
        else
        {
            p->SetApexCheck(true);
            float pixelstomove = (p->GetFallPower() * p->GetFallSpeed() / p->GetGravity() * (delta));

            //Martins carefull movement mechanism:
            //  -Makes the object check every pixel it moves for collision, prevents object in falling through the ground
            //  Bug: It might move 1 pixel into the ground, must investigate
            for(float i = pixelstomove; i >= 0; i -= 1)
            {
                if(Grounded(p, collidableArray))
                {
                    break;
                }

                else
                    p->SetPositionY(p->GetPositionY() + 1);
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
 * @param collidableArray 2D array with all collidable tiles
 * @return True if there is a block infront of player, false if not
 */
bool Physics::HorisontalCollision(PlayerTest* p, int** collidableArray)
{
    int upperPlayerYArrayCoord = (p->GetPositionY() / 32) >0? (p->GetPositionY()+17)/32 :0; //Experimental bug fix
    int lowerPlayerArrayCoord = upperPlayerYArrayCoord +1;
    int playerWestCoord = (p->GetPositionX() / 32);
    int playerEastCoord = playerWestCoord +1;

    return (p->GetMoveSpeedL() > 0 && (collidableArray[upperPlayerYArrayCoord][playerWestCoord] || collidableArray[lowerPlayerArrayCoord][playerWestCoord]))
           || (p->GetMoveSpeedR() > 0 && (collidableArray[upperPlayerYArrayCoord][playerEastCoord] || collidableArray[lowerPlayerArrayCoord][playerEastCoord]));
    /*
    if((p->GetMoveSpeedL() > 0 && (collidableArray[upperPlayerYArrayCoord][playerWestCoord] || collidableArray[lowerPlayerArrayCoord][playerWestCoord]))
       || (p->GetMoveSpeedR() > 0 && (collidableArray[upperPlayerYArrayCoord][playerEastCoord] || collidableArray[lowerPlayerArrayCoord][playerEastCoord])))
    {
        return true;
    }
    return false;*/
}


/*************************************************************
 * checks if player is in touch with a collidable tile beneath
 * @param p the player
 * @param collidableArray 2d array with all collidable tiles
 * @return true if on top of a tile, else false
 */
bool Physics::Grounded(PlayerTest* p, int** collidableArray)
{
    int playerArrayCoordX = (p->GetPositionX() + 17) / 32;
    int playerSouthCoord = (p->GetPositionY() / 32)>0? (p->GetPositionY()+50) / 32 :0;

    return p->GetApexCheck() && collidableArray[playerSouthCoord][playerArrayCoordX];
    /*if(p->GetApexCheck()&& collidableArray[playerSouthCoord][playerArrayCoordX])
    {
        return true;
    }
    return false;*/
}

/*******************************************************
 * Checks if player "head" is in touch with a tile above
 * @param p the player
 * @param collidableArray 2d array with all collidable tiles
 * @return true if in touch with tile above, else false
 */
bool Physics::Roofed(PlayerTest* p, int** collidableArray)
{
    int playerArrayCoordX = (p->GetPositionX() +17) / 32;
    int playerNorthCoord = (p->GetPositionY() / 32)>0?(p->GetPositionY()+30)/32 -1:0;

    if(collidableArray[playerNorthCoord][playerArrayCoordX] != 0)
    {
        return true;
    }
    return false;
}

/***************************************
 * AI PHYSICS
***************************************/

//Horisontal movement for AI
void Physics::AIMovement(AIEnemies* e, PlayerTest* p, std::vector<AIEnemies*>* AIVector, int i, int** collidableArray, float delta) {
    //This function handles movement to the left or to the right. The object will gradually reach its max velocity
    //which it is limited by, and also gradually slow down at different rates wether one tries to move the
    //object to the other direction or not.

    //Checks if player should be hurt or not
    Hurt(p, e, &i, AIVector);

    if(e->GetAIColliding() != 5)
    {
        if(e->GetAIColliding() == 2)
        {

            e->SetApexCheck(false);
            e->SetJumpSpeed(10);
            e->SetFallSpeed(0);
        }
        else if(e->GetAIColliding() == 0)
        {
            e->SetMoveSpeedR(0);
            e->SetMoveSpeedL(200);
        }
        else if(e->GetAIColliding() == 1)
        {
            e->SetMoveSpeedL(0);
            e->SetMoveSpeedR(200);
        }
        else
        {
            e->SetApexCheck(false);
            e->SetJumpSpeed(10);
            e->SetFallSpeed(0);
            e->SetMoveSpeedR(0);
            e->SetMoveSpeedL(200);
        }
        e->SetAIColliding(5);
    }

    //Checks for trying to move to the left
    if (e->GetLeftKey()) {
        e->SetMovDir(0); //Means to the left
        e->SetSlowDownL(false);
    }
    else
        e->SetSlowDownL(true); //Object does not accelerate to left, should slow down if moving to left

    //Check for trying to move to the right
    if (e->GetRightKey()) {
        e->SetMovDir(1); //Means to the right
        e->SetSlowDownR(false);
    }
    else
        //Object does not accelerate to the right, should slow down if moving to the right
        e->SetSlowDownR(true);

    /*********************
     * Left speed handler
     *********************/
    //If the object is moving to the left OR the movespeed to the left is greater than zero

    if (e->GetMovDir() == 0 || e->GetMoveSpeedL() > 0) {
        if (e->GetSlowDownL()) {
            if (e->GetMoveSpeedL() >= e->GetMovePower() * e->GetHorBrake() && e->GetMovDir() == 0)
            {
                //Trying to move the opposite direction of currently move direction, slows down pretty fast
                e->SetMoveSpeedL(e->GetMoveSpeedL() - e->GetMovePower() * e->GetHorBrake());
            }
            else if (e->GetMoveSpeedL() >= e->GetMovePower() * e->GetRegularBrake())
            {
                //Not accelerating nor trying to stop, slows down slowly
                e->SetMoveSpeedL(e->GetMoveSpeedL() - e->GetMovePower() * e->GetRegularBrake());
            }
            else
            {
                e->SetMoveSpeedL(0);
                e->SetMovDir(2);
                e->SetLastMoveDirection(0);
            }
            //Prevents the object from moving in the opposite direction if it tries to stop
        }
        else if (e->GetMoveSpeedL() < e->GetMaxMoveSpeed())
            //The current speed is increased if the object has not yet reached its max speed
            e->SetMoveSpeedL(e->GetMoveSpeedL() + e->GetMovePower());

        //The object is actually being moved
        if(!AIHorisontalCollision(e, collidableArray))
            e->SetPositionX(e->GetPositionX() - e->GetMoveSpeedL() * delta);
        else
            e->SetMoveSpeedL(0);
    }

    /*********************
     * Right speed handler
     *********************/
    //If the object is moving to the right OR the movespeed to the right is greater than zero
    if (e->GetMovDir() == 1 || e->GetMoveSpeedR() > 0)
    {
        if (e->GetSlowDownR())
        {
            if (e->GetMoveSpeedR() >= e->GetMovePower() * e->GetHorBrake() && e->GetMovDir() == 0)
            {
                //Trying to move the opposite direction of currently move direction, slows down pretty fast
                e->SetMoveSpeedR(e->GetMoveSpeedR() - e->GetMovePower() * e->GetHorBrake());
            }
            else if (e->GetMoveSpeedR() >= e->GetMovePower() * e->GetRegularBrake())
            {
                //Not accelerating nor trying to stop, slows down slowly
                e->SetMoveSpeedR(e->GetMoveSpeedR() - e->GetMovePower() * e->GetRegularBrake());
            }
            else
            {
                e->SetMoveSpeedR(0);
                e->SetMovDir(2);
                e->SetLastMoveDirection(1);
            }
            //Prevents the object from moving in the opposite direction if it tries to stop
        }
        else if (e->GetMoveSpeedR() < e->GetMaxMoveSpeed())
            //The current speed is increased if the object has not yet reached its max speed
            e->SetMoveSpeedR(e->GetMoveSpeedR() + e->GetMovePower());

        //The object is actually being moved
        if(!AIHorisontalCollision(e, collidableArray))
            e->SetPositionX(e->GetPositionX() + e->GetMoveSpeedR() * delta);


        else
            e->SetMoveSpeedR(0);
    }
}


//Gravity for AI
void Physics::AIGravity(AIEnemies* e, int** collidableArray, float delta)
{
    //Gravity Start-----------------------------------------------------------------------------------------------------

    //Checks if object is in contact with platform,
    //then marks the object as not airborne(jumpcheck) and current fallspeed as 0.
    //Jumpspeed are also reseted for later use.
    if(AIGrounded(e, collidableArray))
    {
        e->SetJumpCheck(false);
        e->SetFallSpeed(0);
        float temp = e->GetOrigJumpSpeed();
        e->SetJumpSpeed(temp);
    }

        //Check if falling off a platform
        // If the object is not in contact with a platform, and it was not caused by jumping, the object is marked
        // as airborne (jumpcheck) and falling (apexcheck, reached the apex, on the way down).
    else if(!e->GetJumpCheck())
    {
        e->SetJumpCheck(true);
        e->SetApexCheck(true);
    }

    //Tries to make the object jump when Up key is pressed,
    //but only succeeds if the object is not already airborne (jumpcheck).
    if (e->GetUpKey() && !e->GetJumpCheck())
    {
        e->SetJumpCheck(true);
        e->SetApexCheck(false);
    }

    //Functionality for ascending or falling when the object is marked as airborne (jumpcheck).
    if(e->GetJumpCheck())
    {
        //The Object ascends at a decreasing rate when the object is marked as ascending (apexcheck).
        if(e->GetJumpSpeed() >= 0 && !e->GetApexCheck())
        {

            float pixelstomove = ((( e->GetJumpPower() * e->GetJumpSpeed() ) / e->GetGravity() ) * (delta));
            e->SetJumpSpeed(e->GetJumpSpeed() - 1);
            //Martins carefull movement mechanism:
            //  -Makes the object check every pixel it moves for collision, prevents object in falling through the ground
            //  Bug: It might move 1 pixel into the ground, must investigate
            for(float i = pixelstomove; i >= 0; i -= 1)
            {
                if(AIRoofed(e, collidableArray))
                {
                    e->SetApexCheck(true);
                    break;
                }

                else
                    e->SetPositionY(e->GetPositionY() - 1);
            }
        }
            //The Object is descending (apexcheck) as well ass airborne (jumpcheck),
            //and therefore descends at an increasing rate because of how gravity works.
        else
        {
            e->SetApexCheck(true);
            float pixelstomove = (e->GetJumpPower() * e->GetFallSpeed() / e->GetGravity() * (delta));

            //Martins carefull movement mechanism:
            //  -Makes the object check every pixel it moves for collision, prevents object in falling through the ground
            //  Bug: It might move 1 pixel into the ground, must investigate
            for(float i = pixelstomove; i >= 0; i -= 1)
            {
                if(AIGrounded(e, collidableArray))
                {
                    break;
                }

                else
                    e->SetPositionY(e->GetPositionY() + 1);
            }

            //Fallspeed cannot exceed the max fallspeed, the equivalent of real life air resistance limiting
            //a falling objects fallspeed.
            if(e->GetFallSpeed() < e->GetMaxFallSpeed())
            {
                e->SetFallSpeed(e->GetFallSpeed() + 1);
            }
        }
    }
    e->SetUpKey(false);
    //Gravity End-------------------------------------------------------------------------------------------------------
}

/**
 * Function that checks if there is a horisontal collision
 * @param e the player
 * @param collidabletiles Map with all collidable tiles
 * @return True if there is a block infront of player, false if not
 */
bool Physics::AIHorisontalCollision(AIEnemies* e, int** collidableArray)
{
    int upperPlayerYArrayCoord = (e->GetPositionY() / 32) >0? (e->GetPositionY()-15)/32 :0; //Experimental bug fix
    int lowerPlayerArrayCoord = upperPlayerYArrayCoord +1;
    int playerWestCoord = (e->GetPositionX() / 32);
    int playerEastCoord = playerWestCoord +1;


    if((e->GetMoveSpeedL() > 0 && (collidableArray[upperPlayerYArrayCoord][playerWestCoord] || collidableArray[lowerPlayerArrayCoord][playerWestCoord]))
       || (e->GetMoveSpeedR() > 0 && (collidableArray[upperPlayerYArrayCoord][playerEastCoord] || collidableArray[lowerPlayerArrayCoord][playerEastCoord])))
    {
        e->SetUpKey(true);
        return true;
    }
    return false;
}


/*************************************************************
 * checks if player is in touch with a collidable tile beneath
 * @param e the player
 * @param collidableArray 2d array with all collidable tiles
 * @return true if on top of a tile, else false
 */
bool Physics::AIGrounded(AIEnemies* e, int** collidableArray)
{
    int playerArrayCoordX = (e->GetPositionX() + 16) / 32;
    int playerSouthCoord = (e->GetPositionY()+18) / 32;

    if(e->GetApexCheck() == 1 && collidableArray[playerSouthCoord][playerArrayCoordX] != 0)
    {
        return true;
    }
    return false;
}

/*******************************************************
 * Checks if player "head" is in touch with a tile above
 * @param e the player
 * @param collidableArray 2d array with all collidable tiles
 * @return true if in touch with tile above, else false
 */
bool Physics::AIRoofed(AIEnemies* e, int** collidableArray)
{
    int playerArrayCoordX = (e->GetPositionX() + 17) / 32;
    int playerNorthCoord = (e->GetPositionY() / 32)>0?(e->GetPositionY()+30)/32 -1:0;

    if(collidableArray[playerNorthCoord][playerArrayCoordX] != 0)
    {
        return true;
    }
    return false;
}


/**
 * The AI currently running physics checks wether it hurts the player or not.
 * The playerhurt variable will then be set appropriately as shown below.
 * It will then check if it collides with other AI.
 *
 *  * If player is being hurt, playerhurt will be:
 *  5 = Unharmed
 *  0 = From the left
 *  1 = From the right
 *  2 = From above
 *  3 = From beneath
 * @param p Player
 * @param e Selected AI
 * @param i The index of the selected AI(to hinder self colliding)
 * @param AIVector The whole vector of all the AI
 */
void Physics::Hurt(PlayerTest*p, AIEnemies* e, int* i, std::vector<AIEnemies*>* AIVector)
{
    int px = p->GetPositionX() + p->GetSizeWidth()/2;
    int py = p->GetPositionY() + p->GetSizeHeight()/2;

    int ex = e->GetPositionX() + e->GetSizeWidth()/2;
    int ey = e->GetPositionY() + e->GetSizeHeight()/2;


    if((px - ex < p->GetSizeWidth() && px - ex > -p->GetSizeWidth()) &&
       (py - ey < p->GetSizeHeight() && py - ey > -p->GetSizeHeight()))
    {
        if(px < ex &&  ex - px > ey - py)
            p->SetPlayerHurt(0);
        else if(px > ex && px - ex > ey - py)
            p->SetPlayerHurt(1);
        else if(py < ey)
        {
            p->SetPlayerHurt(2);
            e->health.Hit(e->health.GetOriginalLifePoints());
        }

        else
            p->SetPlayerHurt(3);

    }
    AISelfCollision(e, i, AIVector);
}

/**
 * AI checks wether it collides with another AI or not.
 * If AI collides with other character, AIColliding will be:
 *  5 = Not colliding
 *  0 = From the left
 *  1 = From the right
 *  2 = From above
 *  3 = From beneath
 * @param e Selected AI
 * @param i The index of the selected AI(to hinder self colliding)
 * @param AIVector The whole vector of all the AI
 */
void Physics::AISelfCollision(AIEnemies* e, int* i, std::vector<AIEnemies*>* AIVector)
{
    int ex = e->GetPositionX() + e->GetSizeWidth()/2;
    int ey = e->GetPositionY() + e->GetSizeHeight()/2;

    for(unsigned int a = 0; a < AIVector->size(); a++)
    {
        if(!(*i==a))
        {
            int cx = AIVector->at(a)->GetPositionX() + AIVector->at(a)->GetSizeWidth()/2;
            int cy = AIVector->at(a)->GetPositionY() + AIVector->at(a)->GetSizeHeight()/2;

            if((ex - cx < e->GetSizeWidth() && ex - cx > -e->GetSizeWidth()) &&
               (ey - cy < e->GetSizeHeight() && ey - cy > -e->GetSizeHeight()))
            {
                {
                    if(ex < cx &&  cx - ex > cy - ey)
                    {
                        e->SetAIColliding(0);
                        AIVector->at(a)->SetAIColliding(1);
                    }

                    else if(ex > cx && ex - cx > cy - ey)
                    {
                        e->SetAIColliding(1);
                        AIVector->at(a)->SetAIColliding(0);
                    }

                    else if(ey < cy)
                    {
                        e->SetAIColliding(2);
                        AIVector->at(a)->SetAIColliding(3);
                    }
                    else
                        e->SetAIColliding(3);
                }
            }
        }
    }
}