#include <iostream>
#include "AI.h"

AI::AI(float positionX, float positionY, const Config& config, sf::RenderWindow* window) : config(config), window(window)
{
    this->positionX = OriginalX;
    this->positionY = OriginalY;
    character = new sf::RectangleShape;
    character->setSize(sf::Vector2f(sizeWidth,sizeHeight));

    animation.init();
    animation.PlayerIdle(character);

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

void AI::Animation()
{
    counter++;
    if (counter >= 5)
    {
        counter = 0;
        if (jumpcheck == true && movedirection == 1) // If jumping to the right
        {
            animation.PlayerJumpRight(character);
            lastmovedirection = 1;
        }
        else if (jumpcheck == true && movedirection == 0) // If jumping to the left
        {
            animation.PlayerJumpLeft(character);
            lastmovedirection = 0;
        }
        else if (jumpcheck == true) //If jumping upwards.
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
                animation.PlayerIdle(character);
            }
        }
    }
}

void AI::Death()
{
//Delete AI

}

void AI::DrawMe()
{
    // Position the rectangle used to draw the square
    character->setPosition(positionX, positionY);

    // Draw the square
    window->draw(*character);
}
