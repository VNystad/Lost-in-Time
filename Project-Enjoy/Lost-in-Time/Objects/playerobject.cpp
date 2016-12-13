#include <iostream>
#include "playerobject.h"
#include <stdlib.h>

PlayerObject::PlayerObject(float x, float y, sf::RenderWindow* window) : window(window)
{
    this->OriginalX = x;
    this->OriginalY = y;
    this->positionX = x;
    this->positionY = y;
    character = new sf::RectangleShape;
    character->setSize(sf::Vector2f(sizeWidth,sizeHeight));

    animation.init();
    animation.PlayerIdle(character);

    health.init();
    health.SetOriginalLifePoints(100);
    health.SetActualLifePoints(100);
    health.SetVisibleLifePoints(100);
}

float PlayerObject::GetPositionX()
{
    return positionX;
}
float PlayerObject::GetPositionY()
{
    return positionY;
}
void PlayerObject::SetPositionX(float x)
{
    this->positionX = x;
}
void PlayerObject::SetPositionY(float y)
{
    this->positionY = y;
}

float PlayerObject::GetOriginalX()
{
    return OriginalX;
}

float PlayerObject::GetOriginalY()
{
    return OriginalY;
}

void PlayerObject::SetOriginalX(float x)
{
    this->OriginalX = x;
}

void PlayerObject::SetOriginalY(float y)
{
    this->OriginalY = y;
}

void PlayerObject::Reset2OriginalX(float x)
{
    x = this->OriginalX;
}

void PlayerObject::Reset2OriginalY(float y)
{
    y = this->OriginalY;
}

void PlayerObject::PlayerAnimation(float delta)
{
    counter += delta;
    if (counter >= 0.07)
    {
        counter = 0;
        if (jumpcheck && movedirection == 1) // If jumping to the right
        {
            animation.PlayerJumpRight(character);
            lastmovedirection = 1;
        }
        else if (jumpcheck && movedirection == 0) // If jumping to the left
        {
            animation.PlayerJumpLeft(character);
            lastmovedirection = 0;
        }
        else if (jumpcheck) //If jumping upwards.
        {
            if (lastmovedirection == 1)
                animation.PlayerJumpRight(character);
            else
                animation.PlayerJumpLeft(character);
        }

        else
        {
            if (movedirection == 0) // If moving to left, play left animation
            {
                animation.PlayerWalkLeft(character);
            }
            if (movedirection == 1) // If moving to right, play right animation
            {
                animation.PlayerWalkRight(character);
            }
            if (movedirection == 2) // If movement stopped, play idle animation
            {
                if(lastmovedirection == 0)
                    animation.PlayerIdleLeft(character);
                else
                    animation.PlayerIdle(character);
            }
        }
    }
}


void PlayerObject::PlayerSoundJump()
{
    sound = new Sounds();
    sound->playSound("/Jump.wav", 100);
}

void PlayerObject:: PlayerSoundHurt()
{
    sound = new Sounds();
    if(rand() % 20 < 10)
        sound->playSound("/manhurt1.wav", 100);
    else
        sound->playSound("/manhurt2.wav", 100);
}


void PlayerObject:: PlayerSoundEnemyLanded()
{
    sound = new Sounds();
    sound->playSound("/jumpedonenemy.wav", 100);
}


/**
 * When player is dead this function is called.
 * Reset variables that need reseted.
 * Call to health reset function.
 * Set player position back to spawn position.
 * TODO: Draw deathscreen, atm: print out deathmessage
 */
void PlayerObject::PlayerDead()
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
void PlayerObject::DrawMe()
{
    // Position the rectangle used to draw the square
    character->setPosition(positionX, positionY);

    // Draw the square
    window->draw(*character);
}