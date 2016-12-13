#include <iostream>
#include "princessobject.h"
#include <stdlib.h>

PrincessObject::PrincessObject(float x, float y, float patrol, sf::RenderWindow* window) : window(window)
{
    this->OriginalX = x;
    this->OriginalY = y;
    this->positionX = x;
    this->positionY = y;

    this->patrolleft = x - patrol;
    this->patrolright = x + patrol;
    this->maxMoveSpeed = calmSpeed;

    character = new sf::RectangleShape;
    character->setSize(sf::Vector2f(sizeWidth,sizeHeight));

    animation.init();
    animation.PrincessWalkLeft(character);

    health.init();
    health.SetOriginalLifePoints(100);
    health.SetActualLifePoints(100);
    health.SetVisibleLifePoints(100);

    sound = new Sounds();
}


//AI

void PrincessObject::PrincessAI(PlayerObject* p)
{
    if(activated)
    {
        if((p->GetPositionX() - positionX < enragerange && p->GetPositionX() - positionY > -enragerange) &&
           (p->GetPositionY() - positionX <  enragerange && p->GetPositionY() - positionY > -enragerange))
        {
            enraged = true;
            enrageCountdown = enrageDuration;
        }



        // Common enraged behaviour for all AI
        if(enraged)
        {
            maxMoveSpeed = enrageSpeed;
            enrageCountdown = enrageCountdown -1;
            if(enrageCountdown <= 0)
            {
                enrageCountdown = enrageDuration;
                maxMoveSpeed = calmSpeed;
                enraged = false;
            }

        }


        // Specific enraged behaviour for creepy stalking minion, normal as of now.
        if(enraged) {
            //std::cout << "Super Angry" << std::endl;
            if (p->GetPositionX() < positionX)
            {
                leftKey = true;
                rightKey = false;
            }
            else if(p->GetPositionX() > positionX)
            {
                rightKey = true;
                leftKey = false;
            }

            else
            {
                rightKey = false;
                leftKey = false;
            }

        }

            // Common patrol behaviour
        else
        {
            if(positionX > patrolright)
            {
                leftKey = true;
                rightKey = false;
            }
            else if(positionX < patrolleft)
            {
                leftKey = false;
                rightKey = true;
            }
        }
    }
}


float PrincessObject::GetPositionX()
{
    return positionX;
}
float PrincessObject::GetPositionY()
{
    return positionY;
}
void PrincessObject::SetPositionX(float x)
{
    this->positionX = x;
}
void PrincessObject::SetPositionY(float y)
{
    this->positionY = y;
}

float PrincessObject::GetOriginalX()
{
    return OriginalX;
}

float PrincessObject::GetOriginalY()
{
    return OriginalY;
}

void PrincessObject::SetOriginalX(float x)
{
    this->OriginalX = x;
}

void PrincessObject::SetOriginalY(float y)
{
    this->OriginalY = y;
}

void PrincessObject::Reset2OriginalX(float x)
{
    x = this->OriginalX;
}

void PrincessObject::Reset2OriginalY(float y)
{
    y = this->OriginalY;
}

void PrincessObject::PrincessCutsceneAnimation(float delta)
{
    counter += delta;
    if(counter >= 0.2)
    {
        counter = 0;
        animation.PrincessWalkLeft(character);
    }
}


void PrincessObject::PrincessAnimation(float delta)
{
    counter += delta;
    if (counter >= 0.2)
    {
        counter = 0;

        if (movedirection == 0) // If moving to left, play left animation
        {
            animation.PrincessWalkLeft(character);
        }
        if (movedirection == 1) // If moving to right, play right animation
        {
            animation.PrincessWalkRight(character);
        }
        if (movedirection == 2) // If movement stopped, play idle animation
        {
            if(lastmovedirection == 0)
                animation.PrincessWalkLeft(character);
            else
                animation.PrincessWalkRight(character);
        }
    }
}


void PrincessObject:: PrincessSoundHurt()
{
    sound->playSound("/princesslap2.wav", 100);
    /*if(rand() % 20 < 10)

    else
        sound->playSound("/princesslap2.wav", 100);
*/}

/**
 * When princess is dead this function is called.
 * Reset variables that need reseted.
 * Call to health reset function.
 * Set player position back to spawn position.
 * TODO: Draw deathscreen, atm: print out deathmessage
 */
void PrincessObject::PlayerDead()
{
    this->jumpcheck = true;
    this->apexcheck = true;
    jumpspeed = origjumpspeed;
    fallspeed = 0;
    movedirection = 2;
    movespeedleft = 0;
    movespeedright = 0;
    positionX = OriginalX;
    positionY = OriginalY;
    sound->playSound("/Death.wav", 100);
}

/**
 * Set the position for the character at PositionX and Y
 * Draw the character to the window.
 */
void PrincessObject::DrawMe()
{
    // Position the rectangle used to draw the square
    character->setPosition(positionX, positionY);

    // Draw the square
    window->draw(*character);
}