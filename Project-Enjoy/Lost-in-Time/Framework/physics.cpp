#include "physics.h"

void Physics::Gravity(PlayerTest* p, TestCollidablePlatform* platform1, TestCollidablePlatform* platform2, float delta)
{
    //Gravity Start-----------------------------------------------------------------------------------------------------

    //Checks if object is in contact with platform,
    //then marks the object as not airborne(jumpcheck) and current fallspeed as 0.
    //Jumpspeed are also resetted for later use.
    if(Grounded(p, platform1, platform2))
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

        p->character->setTexture(&p->PlayerTextureJump);

        if (p->rectSourceCharacter->left == 136)
            p->rectSourceCharacter->left -= 34;

        else if (p->rectSourceCharacter->left == 0)
            p->rectSourceCharacter->left += 34;

        p->character->setTextureRect(*p->rectSourceCharacter);
    }

    //Functionality for ascending or falling when the object is marked as airborne (jumpcheck).
    if(p->GetJumpCheck())
    {
        if(p->GetVertiCollCD() <= delta)
            p->SetVertiCollCD(p->GetVertiCollCD() + delta);
        //The Object ascends at a decreasing rate when the object is marked as ascending (apexcheck).
        if(p->GetJumpSpeed() >= 0 && !p->GetApexCheck())
        {
            float pixelstomove = (( p->GetJumpPower() * p->GetJumpSpeed() ) / p->GetGravity() ) * (delta);
            p->SetJumpSpeed(p->GetJumpSpeed() - 1);

            for(float i = pixelstomove; i >= 0; i -= 1 )
            {
                if(Grounded(p, platform1, platform2) && p->GetVertiCollCD() > delta)
                {
                    i = -1;
                    p->SetPositionY(p->GetPositionY() + 1);
                    p->SetApexCheck(true);
                }

                else
                    p->SetPositionY(p->GetPositionY() - 1);
                p->DrawMe();
            }
        }
            //The Object is descending (apexcheck) as well ass airborne (jumpcheck),
            //and therefore descends at an increasing rate because of how gravity works.
        else
        {
            p->SetVertiCollCD(0);
            p->SetApexCheck(true);
            float pixelstomove = (p->GetJumpPower() * p->GetFallSpeed() / p->GetGravity() * (delta));

            //Martins carefull movement mechanism:
            //  -Makes the object check every pixel it moves for collision, prevents object in falling through the ground
            //  Bug: It might move 1 pixel into the ground, must investigate
            for(float i = pixelstomove; i >= 0; i -= 1)
            {
                if(Grounded(p, platform1, platform2))
                {
                    i = -1;
                }

                else
                    p->SetPositionY(p->GetPositionY() + 1);
                p->DrawMe();
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

void Physics::Movement(PlayerTest* p, TestCollidablePlatform* platform1, TestCollidablePlatform* platform2, float delta) {
    //This function handles movement to the left or to the right. The object will gradually reach its max velocity
    //which it is limited by, and also gradually slow down at different rates wether one tries to move the
    //object to the other direction or not.

    // If standing still, play idle animation
    if (p->GetMovDir() == 2)
    {
        p->character->setTexture(&p->PlayerTextureIdle);

        if (p->rectSourceCharacter->left == 136)
            p->rectSourceCharacter->left -= 34;

        else if (p->rectSourceCharacter->left == 0)
            p->rectSourceCharacter->left += 34;

        p->character->setTextureRect(*p->rectSourceCharacter);
    }

    if (Grounded(p, platform1, platform2)) {
        p->SetHoriCollCD(0);
    }
    else
        p->SetHoriCollCD(p->GetHoriCollCD() + delta);

    //Checks for trying to move to the left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        p->SetMovDir(0); //Means to the left
        p->SetSlowDownL(false);

        p->character->setTexture(&p->PlayerTextureWalkflipped);

        if (p->rectSourceCharacter->left == 136)
            p->rectSourceCharacter->left -= 34;

        else if (p->rectSourceCharacter->left == 0)
            p->rectSourceCharacter->left += 34;

        p->character->setTextureRect(*p->rectSourceCharacter);
    }
    else
        p->SetSlowDownL(true); //Object does not accelerate to left, should slow down if moving to left

    //Check for trying to move to the right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        p->SetMovDir(1); //Means to the right
        p->SetSlowDownR(false);

        p->character->setTexture(&p->PlayerTextureWalk);

        if (delta > 1.0f)
        {
            if (p->rectSourceCharacter->left == 0) {
                // Move the frame to the left
                for (int j = 0; j < 0; j = j + 34) {
                    if (p->rectSourceCharacter->left == j)
                        p->rectSourceCharacter->left = j + 34;
                }
            }

            if (p->rectSourceCharacter->left == 136) {
                // If the frame is to the right, move it back to the left
                for (int i = 136; i > 0; i = i - 34) {
                    if (p->rectSourceCharacter->left == i)
                        p->rectSourceCharacter->left = i - 34;
                }
            }
        }
        p->character->setTextureRect(*p->rectSourceCharacter);
    }
    else
        //Object does not accelerate to the right, should slow down if moving to the right
        p->SetSlowDownR(true);

    //Left speed handler
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
                //Prevents the object from moving in the opposite direction if it tries to stop
                p->SetMoveSpeedL(0);
        }
        else if (p->GetMoveSpeedL() < p->GetMaxMoveSpeed())
            //The current speed is increased if the object has not yet reached its max speed
            p->SetMoveSpeedL(p->GetMoveSpeedL() + p->GetMovePower());

        //The object is actually being moved
        float pixelstomove = p->GetMoveSpeedL() * delta;

        for (float i = pixelstomove; i >= 0; i -= 1)
        {
            if (Grounded(p, platform1, platform2) && p->GetHoriCollCD() >= delta)
            {
                i = -1;
                p->SetPositionX(p->GetPositionX() + 1);
            }
            else if (i != 0)
                p->SetPositionX(p->GetPositionX() - 1);
            p->DrawMe();
        }
    }

    //Right speed handler
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
        float pixelstomove = p->GetMoveSpeedR() * delta;

        for (float i = pixelstomove; i >= 0; i -= 1)
        {
            if (Grounded(p, platform1, platform2) && p->GetHoriCollCD() >= delta)
            {
                i = -1;
                p->SetPositionX(p->GetPositionX() - 1);
            }
            else if (i != 0)
                p->SetPositionX(p->GetPositionX() + 1);
            p->DrawMe();
        }
    }
}

bool Physics::Grounded(PlayerTest* p, TestCollidablePlatform* platform1, TestCollidablePlatform* platform2)
{
    //Simply checks if the object is currently on the ground
    if(p->GetCharacter().getGlobalBounds().intersects(platform1->GetPlatform().getGlobalBounds())
       || p->GetCharacter().getGlobalBounds().intersects(platform2->GetPlatform().getGlobalBounds()))
    {
        return true;
    }

    else
    {
        return false;
    }
}
