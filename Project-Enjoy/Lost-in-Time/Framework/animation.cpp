#include <iostream>
#include "animation.h"

void Animation::init()
{
    /* **********************************
               PLAYER CHARACTER
       ********************************** */
    // Load the animation textures
    if (!PlayerTextureWalk.loadFromFile("data/Character-Animation/charactermove.png"))
        std::cout << "Failed to load data/Character-Animation/charactermove.png" << std::endl << std::endl;
    if (!PlayerTextureWalkflipped.loadFromFile("data/Character-Animation/charactermoveflipped.png"))
        std::cout << "Failed to load data/Character-Animation/charactermoveflipped.png" << std::endl << std::endl;
    if (!PlayerTextureIdle.loadFromFile("data/Character-Animation/characteridle.png"))
        std::cout << "Failed to load data/Character-Animation/characteridle.png" << std::endl << std::endl;
    if (!PlayerTextureIdleFlipped.loadFromFile("data/Character-Animation/characteridleflipped.png"))
        std::cout << "Failed to load data/Character-Animation/characteridleflipped.png" << std::endl << std::endl;
    if (!PlayerTextureJump.loadFromFile("data/Character-Animation/characterjump.png"))
        std::cout << "Failed to load data/Character-Animation/characterjump.png" << std::endl << std::endl;
    if (!PlayerTextureJumpflipped.loadFromFile("data/Character-Animation/characterjumpflipped.png"))
        std::cout << "Failed to load data/Character-Animation/characterjumpflipped.png" << std::endl << std::endl;
    if (!PlayerTextureDeath.loadFromFile("data/Character-Animation/characterdeath.png"))
        std::cout << "Failed to load data/Character-Animation/characterdeath.png" << std::endl << std::endl;

    frameSelected = new sf::IntRect(0,0,GetSizeWidth(),GetSizeHeight());

    /* **********************************
               MINION CHARACTER
       ********************************** */
    if (!AITextureWalkRight.loadFromFile("data/Character-Animation/apemoveright.png"))
        std::cout << "Failed to load data/Character-Animation/apemoveright.png" << std::endl << std::endl;
    if (!AITextureWalkLeft.loadFromFile("data/Character-Animation/apemoveleft.png"))
        std::cout << "Failed to load data/Character-Animation/apemoveleft.png" << std::endl << std::endl;

    /* **********************************
                BOSS CHARACTER
     ********************************** */
}











    /* **********************************
           PLAYER CHARACTER
    ********************************** */

void Animation::PlayerWalkRight(sf::RectangleShape* character)
{
    character->setTexture(&PlayerTextureWalk);
    if(animationdir == 1)
    {
        if (frameSelected->left < 102)
            frameSelected->left += 34;
        else
        {
            frameSelected->left -= 34;
            animationdir = 0;
        }
    }
    else
    {
        if (frameSelected->left > 0)
            frameSelected->left -= 34;
        else
        {
            frameSelected->left += 34;
            animationdir = 1;
        }
    }

    character->setTextureRect(*frameSelected);
}

void Animation::PlayerWalkLeft(sf::RectangleShape* character)
{
    character->setTexture(&PlayerTextureWalkflipped);
    if(animationdir == 1)
    {
        if (frameSelected->left < 102)
            frameSelected->left += 34;
        else
        {
            frameSelected->left -= 34;
            animationdir = 0;
        }
    }
    else
    {
        if (frameSelected->left > 0)
            frameSelected->left -= 34;
        else
        {
            frameSelected->left += 34;
            animationdir = 1;
        }
    }

    character->setTextureRect(*frameSelected);
}

void Animation::PlayerIdleLeft(sf::RectangleShape* character)
{
    character->setTexture(&PlayerTextureIdleFlipped);
    if(animationdir == 1)
    {
        if (frameSelected->left < 102 && IdleCount>=2)
        {
            frameSelected->left += 34;
            IdleCount = 0;
        }
        else if(IdleCount >= 2)
        {
            frameSelected->left -= 34;
            animationdir = 0;
            IdleCount = 0;
        }
        IdleCount++;
    }
    else
    {
        if (frameSelected->left > 0&& IdleCount>=2)
        {
            frameSelected->left -= 34;
            IdleCount = 0;
        }
        else if(IdleCount >= 2)
        {
            frameSelected->left += 34;
            animationdir = 1;
            IdleCount = 0;
        }
        IdleCount++;
    }

    character->setTextureRect(*frameSelected);
}

void Animation::PlayerIdle(sf::RectangleShape* character)
{
    character->setTexture(&PlayerTextureIdle);
    if(animationdir == 1)
    {
        if (frameSelected->left < 102 && IdleCount>=2)
        {
            frameSelected->left += 34;
            IdleCount = 0;
        }
        else if(IdleCount>=2)
        {
            frameSelected->left -= 34;
            animationdir = 0;
            IdleCount = 0;
        }
        IdleCount++;
    }
    else
    {
        if (frameSelected->left > 0 && IdleCount>=2)
        {
            frameSelected->left -= 34;
            IdleCount = 0;
        }
        else if(IdleCount>=2)
        {
            frameSelected->left += 34;
            animationdir = 1;
            IdleCount = 0;
        }
        IdleCount++;
    }

    character->setTextureRect(*frameSelected);
}

void Animation::PlayerJumpRight(sf::RectangleShape* character)
{
    character->setTexture(&PlayerTextureJump);
    if(animationdir == 1)
    {
        if (frameSelected->left < 102)
            frameSelected->left += 34;
        else
        {
            frameSelected->left -= 34;
            animationdir = 0;
        }
    }
    else
    {
        if (frameSelected->left > 0)
            frameSelected->left -= 34;
        else
        {
            frameSelected->left += 34;
            animationdir = 1;
        }
    }

    character->setTextureRect(*frameSelected);
}

void Animation::PlayerJumpLeft(sf::RectangleShape* character)
{
    character->setTexture(&PlayerTextureJumpflipped);
    if(animationdir == 1)
    {
        if (frameSelected->left < 102)
            frameSelected->left += 34;
        else
        {
            frameSelected->left -= 34;
            animationdir = 0;
        }
    }
    else
    {
        if (frameSelected->left > 0)
            frameSelected->left -= 34;
        else
        {
            frameSelected->left += 34;
            animationdir = 1;
        }
    }

    character->setTextureRect(*frameSelected);
}

void Animation::PlayerDie(sf::RectangleShape* character)
{

}


    /* **********************************
           MINION CHARACTER
    ********************************** */

    void Animation::AIWalkRight(sf::RectangleShape* character)
    {
        character->setTexture(&AITextureWalkRight);
        if(animationdir == 1)
        {
            if (frameSelected->left < 216)
                frameSelected->left += 36;
            else
            {
                frameSelected->left -= 216;
                animationdir = 0;
            }
        }
        else
        {
            if (frameSelected->left > 0)
                frameSelected->left -= 36;
            else
            {
                frameSelected->left += 36;
                animationdir = 1;
            }
        }

        character->setTextureRect(*frameSelected);
    }

void Animation::AIWalkLeft(sf::RectangleShape* character)
{
    character->setTexture(&AITextureWalkLeft);
    if(animationdir == 1)
    {
        if (frameSelected->left < 216)
            frameSelected->left += 36;
        else
        {
            frameSelected->left -= 36;
            animationdir = 0;
        }
    }
    else
    {
        if (frameSelected->left > 0)
            frameSelected->left -= 36;
        else
        {
            frameSelected->left += 36;
            animationdir = 1;
        }
    }

    character->setTextureRect(*frameSelected);
}


    /* **********************************
            BOSS CHARACTER
    ********************************** */