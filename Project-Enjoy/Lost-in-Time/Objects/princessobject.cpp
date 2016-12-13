#include <iostream>
#include "princessobject.h"
#include <stdlib.h>

PrincessObject::PrincessObject(float x, float y, float patrol, sf::RenderWindow* window) : window(window)
{
    this->OriginalX = x;
    this->OriginalY = y;
    this->positionX = x;
    this->positionY = y;
    character = new sf::RectangleShape;
    character->setSize(sf::Vector2f(sizeWidth,sizeHeight));

    animation.init();
    animation.PrincessWalkLeft(character);

    this->patrolleft = x - patrol;
    this->patrolright = x + patrol;
    this->SetMaxMoveSpeed(this->GetCalmSpeed());

    health.init();
    health.SetOriginalLifePoints(100);
    health.SetActualLifePoints(100);
    health.SetVisibleLifePoints(100);

    sound = new Sounds();



}


//AI

void PrincessObject::PrincessAI(PrincessObject* e,PlayerObject* p)
{
    if(e->activated == true)
    {
        if((p->GetPositionX() - e->GetPositionX() < this->enragerange && p->GetPositionX() - e->GetPositionX() > -this->enragerange) &&
           (p->GetPositionY() - e->GetPositionY() <  this->enragerange && p->GetPositionY() - e->GetPositionY() > -this->enragerange))
        {
            e->SetEnraged(true);
            e->SetEnrageCountdown(e->GetEnrageDuration());
        }



        // Common enraged behaviour for all AI
        if(e->GetEnraged())
        {
            e->SetMaxMoveSpeed(e->GetEnragedSpeed());
            e->SetEnrageCountdown(e->GetEnrageCountdown()-1);
            if(e->GetEnrageCountdown() <= 0){
                e->SetEnrageCountdown(e->GetEnrageDuration());
                e->SetMaxMoveSpeed(e->GetCalmSpeed());
                e->SetEnraged(false);
            }
        }


        // Specific enraged behaviour for creepy stalking minion, normal as of now.
        if(e->GetEnraged()) {
            //std::cout << "Super Angry" << std::endl;
            if (p->GetPositionX() < e->GetPositionX())
            {
                e->SetLeftKey(true);
                e->SetRightKey(false);
            }
            else if(p->GetPositionX() > e->GetPositionX())
            {
                e->SetRightKey(true);
                e->SetLeftKey(false);
            }

            else
            {
                e->SetLeftKey(false);
                e->SetRightKey(false);
            }

        }

            // Common patrol behaviour
        else
        {
            if(e->GetPositionX() > this->patrolright)
            {
                e->SetLeftKey(true);
                e->SetRightKey(false);
            }
            else if(e->GetPositionX() < this->patrolleft)
            {
                e->SetLeftKey(false);
                e->SetRightKey(true);
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
 * When player is dead this function is called.
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
    sound = new Sounds();
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