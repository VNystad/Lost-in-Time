#include <iostream>
#include "playertest.h"

PlayerTest::PlayerTest(float positionX, float positionY, const Config& config, sf::RenderWindow* window) : config(config), window(window)
{
    this->OriginalX = positionX;
    this->OriginalY = positionY;
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

float PlayerTest::GetPositionX()
{
    return positionX;
}
float PlayerTest::GetPositionY()
{
    return positionY;
}
void PlayerTest::SetPositionX(float x)
{
    this->positionX = x;
}
void PlayerTest::SetPositionY(float y)
{
    this->positionY = y;
}

float PlayerTest::GetOriginalX()
{
    return OriginalX;
}

float PlayerTest::GetOriginalY()
{
    return OriginalY;
}

void PlayerTest::SetOriginalX(float x)
{
    this->OriginalX = x;
}

void PlayerTest::SetOriginalY(float y)
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
        if (jumpcheck && movedirection == 1) // If jumping to the right
        {
            animation.PlayerJumpRight(character);
            lastmovedirection = 1;
            //VETLE AKTIVERER LYD FOR HOPP
            jumpsoundplayed = true;
        }
        else if (jumpcheck && movedirection == 0) // If jumping to the left
        {
            animation.PlayerJumpLeft(character);
            lastmovedirection = 0;
            //VETLE AKTIVERER LYD FOR HOPP
            jumpsoundplayed = true;
        }
        else if (jumpcheck) //If jumping upwards.
        {
            if (lastmovedirection == 1)
                animation.PlayerJumpRight(character);
            else
                animation.PlayerJumpLeft(character);
            //VETLE AKTIVERER LYD FOR HOPP
            jumpsoundplayed = true;
        }

        else
        {
            jumpsoundplayed = false;
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

/**
 * When player is dead this function is called.
 * Reset variables that need reseted.
 * Call to health reset function.
 * Set player position back to spawn position.
 * TODO: Draw deathscreen, atm: print out deathmessage
 */
void PlayerTest::PlayerDead()
{
    jumpspeed = origjumpspeed;
    fallspeed = 0;
    movedirection = 2;
    positionX = OriginalX;
    positionY = OriginalY;
    sound = new Sounds();
    sound->playSound("/Death.wav");
    std::cout << "Oh deer, you died!" << std::endl;
    std::cout << "     (      )\n"
            "     ))    ((\n"
            "    //      \\\\\n"
            "   | \\\\____// |\n"
            "  \\~/ ~    ~\\/~~/\n"
            "   (|    _/o  ~~\n"
            "    /  /     ,|\n"
            "   (~~~)__.-\\ |\n"
            "    ``~~    | |\n"
            "     |      | |\n"
            "     |        |\n"
            "    /          \\\n"
            "   `\\          /'\n"
            "     `\\_    _/'\n"
            "        ~~~~"
              << std::endl << std::endl;

}

/**
 * Set the position for the character at PositionX and Y
 * Draw the character to the window.
 */
void PlayerTest::DrawMe()
{
    // Position the rectangle used to draw the square
    character->setPosition(positionX, positionY);

    // Draw the square
    window->draw(*character);
}
