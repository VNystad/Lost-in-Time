#include <iostream>
#include "AI.h"

AI::AI(int x, int y, int patrol, sf::RenderWindow* window) : window(window)
{
    this->positionX = x;
    this->positionY = y;
    this->OriginalX = x;
    this->OriginalY = y;
    //this->patrol = patrol;
    //this->patrolleft = x - patrol;
    //this->patrolright = x + patrol;
    character = new sf::RectangleShape;
    character->setSize(sf::Vector2f(sizeWidth,sizeHeight));

    animation.init();
    animation.AIWalkLeft(character);

    health.init();
    health.SetOriginalLifePoints(100);
    health.SetActualLifePoints(100);
    health.SetVisibleLifePoints(100);
}

int AI::GetPositionX()
{
    return positionX;
}
int AI::GetPositionY()
{
    return positionY;
}
void AI::SetPositionX(int x)
{
    this->positionX = x;
}
void AI::SetPositionY(int y)
{
    this->positionY = y;
}

int AI::GetOriginalX()
{
    return OriginalX;
}

int AI::GetOriginalY()
{
    return OriginalY;
}

void AI::SetOriginalX(int x)
{
    this->OriginalX = x;
}

void AI::SetOriginalY(int y)
{
    this->OriginalY = y;
}

void AI::Reset2OriginalX(float x)
{
    x = this->OriginalX;
}

void AI::Reset2OriginalY(float y)
{
    y = this->OriginalY;
}

void AI::AnimationAI(float delta)
{
    counter += delta;
    if (counter >= 0.1)
    {
        counter = 0;
        if (jumpcheck && movedirection == 1) // If jumping to the right
        {
            animation.AIWalkRight(character);
            lastmovedirection = 1;
        }
        else if (jumpcheck && movedirection == 0) // If jumping to the left
        {
            animation.AIWalkLeft(character);
            lastmovedirection = 0;
        }
        else if (jumpcheck) //If jumping upwards.
        {
            if (lastmovedirection == 1)
                animation.AIWalkRight(character);
            else
                animation.AIWalkLeft(character);
        }

        else
        {
            if (movedirection == 0) // If moving to left, play left animation
            {
                animation.AIWalkLeft(character);
            }
            if (movedirection == 1) // If moving to right, play right animation
            {
                animation.AIWalkRight(character);
            }
            if (movedirection == 2) // If movement stopped, play idle animation
            {
                if(lastmovedirection == 0)
                    animation.AIWalkLeft(character);
                else
                    animation.AIWalkRight(character);

            }
        }
    }
}


void AI::AnimationAIMiniBoss(float delta)
{
    counter += delta;
    if (counter >= 0.1)
    {
        counter = 0;
        if (jumpcheck && movedirection == 1) // If jumping to the right
        {
            animation.AIMiniBossWalkRight(character);
            lastmovedirection = 1;
        }
        else if (jumpcheck && movedirection == 0) // If jumping to the left
        {
            animation.AIMiniBossWalkLeft(character);
            lastmovedirection = 0;
        }
        else if (jumpcheck) //If jumping upwards.
        {
            if (lastmovedirection == 1)
                animation.AIMiniBossWalkRight(character);
            else
                animation.AIMiniBossWalkLeft(character);
        }

        else
        {
            if (movedirection == 0) // If moving to left, play left animation
            {
                animation.AIMiniBossWalkLeft(character);
            }
            if (movedirection == 1) // If moving to right, play right animation
            {
                animation.AIMiniBossWalkRight(character);
            }
            if (movedirection == 2) // If movement stopped, play idle animation
            {
                if(lastmovedirection == 0)
                    animation.AIMiniBossWalkLeft(character);
                else
                    animation.AIMiniBossWalkRight(character);
            }
        }
    }
}

void AI::AnimationBoss(float delta)
{
    counter += delta;
    if (counter >= 0.1)
    {
        counter = 0;
        if (jumpcheck && movedirection == 1) // If jumping to the right
        {
            animation.AIBossWalkRight(character);
            lastmovedirection = 1;
        }
        else if (jumpcheck && movedirection == 0) // If jumping to the left
        {
            animation.AIBossWalkLeft(character);
            lastmovedirection = 0;
        }
        else if (jumpcheck) //If jumping upwards.
        {
            if (lastmovedirection == 1)
                animation.AIBossWalkRight(character);
            else
                animation.AIBossWalkLeft(character);
        }

        else
        {
            if (movedirection == 0) // If moving to left, play left animation
            {
                animation.AIBossWalkLeft(character);
            }
            if (movedirection == 1) // If moving to right, play right animation
            {
                animation.AIBossWalkRight(character);
            }
            if (movedirection == 2) // If movement stopped, play idle animation
            {
                if(lastmovedirection == 0)
                    animation.AIBossWalkLeft(character);
                else
                    animation.AIBossWalkRight(character);
            }
        }
    }
}

void AI::Death()
{
//Delete AI
    this->health.Hit(100000000000);

}

void AI::DrawMe()
{
    // Position the rectangle used to draw the square
    character->setPosition(positionX, positionY);

    // Draw the square
    window->draw(*character);
}
