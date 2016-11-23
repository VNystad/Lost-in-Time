#include "playertest.h"

PlayerTest::PlayerTest(float positionX, float positionY, const Config& config, sf::RenderWindow* window) : config(config), window(window)
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

int PlayerTest::GetPositionX()
{
    return positionX;
}
int PlayerTest::GetPositionY()
{
    return positionY;
}
void PlayerTest::SetPositionX(int x)
{
    this->positionX = x;
}
void PlayerTest::SetPositionY(int y)
{
    this->positionY = y;
}

int PlayerTest::GetOriginalX()
{
    return OriginalX;
}

int PlayerTest::GetOriginalY()
{
    return OriginalY;
}

void PlayerTest::SetOriginalX(int x)
{
    this->OriginalX = x;
}

void PlayerTest::SetOriginalY(int y)
{
    this->OriginalY = y;
}

void PlayerTest::Reset2OriginalX(float x)
{
    x = this->OriginalX;
}

void PlayerTest::Reset2OriginalY(float y)
{
    y = this->OriginalY;
}

void PlayerTest::PlayerAnimation()
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

void PlayerTest::PlayerDead()
{
    health.SetActualLifePoints(100);
    health.SetVisibleLifePoints(100);
    jumpspeed = origjumpspeed;
    fallspeed = 0;
    movedirection = 2;
    positionX = OriginalX;
    positionY = OriginalY;

}

void PlayerTest::DrawMe()
{
    // Position the rectangle used to draw the square
    character->setPosition(positionX, positionY);

    // Draw the square
    window->draw(*character);
}
