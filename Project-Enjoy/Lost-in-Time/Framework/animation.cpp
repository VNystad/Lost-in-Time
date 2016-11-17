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


    /* **********************************
                BOSS CHARACTER
     ********************************** */
}

void Animation::PlayerWalkRight(sf::RectangleShape* character)
{
    character->setTexture(&PlayerTextureWalk);
    if (frameSelected->left >= 0 && frameSelected->left < 102)
        frameSelected->left += 34;
    else
        frameSelected->left = 0;
    character->setTextureRect(*frameSelected);
}

void Animation::PlayerWalkLeft(sf::RectangleShape* character)
{
    character->setTexture(&PlayerTextureWalkflipped);
    if (frameSelected->left >= 0 && frameSelected->left < 102)
    {
        frameSelected->left += 34;
    }
    else
    {
        frameSelected->left = 0;
    }
    character->setTextureRect(*frameSelected);
}

void Animation::PlayerIdle(sf::RectangleShape* character)
{
    character->setTexture(&PlayerTextureIdle);
    if (frameSelected->left >= 0 && frameSelected->left < 102)
        frameSelected->left += 34;
    else
        frameSelected->left = 0;
    character->setTextureRect(*frameSelected);
}

void Animation::PlayerJumpRight(sf::RectangleShape* character)
{
    character->setTexture(&PlayerTextureJump);
    if (frameSelected->left >= 0 && frameSelected->left < 136)
        frameSelected->left += 34;
    else
        frameSelected->left = 0;
    character->setTextureRect(*frameSelected);
}

void Animation::PlayerJumpLeft(sf::RectangleShape* character)
{
    character->setTexture(&PlayerTextureJumpflipped);
    if (frameSelected->left >= 0 && frameSelected->left < 136)
        frameSelected->left += 34;
    else
        frameSelected->left = 0;
    character->setTextureRect(*frameSelected);
}

void Animation::PlayerDie(sf::RectangleShape* character)
{

}
