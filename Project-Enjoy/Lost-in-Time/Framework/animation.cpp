#include <iostream>
#include "animation.h"

/**
 * Init of the animation
 * Load in the textures
 * Create the frame used to select which picture to use in the animation.
 */
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
    frameSelectedBoss = new sf::IntRect(0,0,55,44);

    /* **********************************
           MINION CHARACTER
    ********************************** */

    if (!AITextureWalkRight.loadFromFile("data/Character-Animation/apemoveright.png"))
        std::cout << "Failed to load data/Character-Animation/apemoveright.png" << std::endl << std::endl;
    if (!AITextureWalkLeft.loadFromFile("data/Character-Animation/apemoveleft.png"))
        std::cout << "Failed to load data/Character-Animation/apemoveleft.png" << std::endl << std::endl;


    /* **********************************
        MINIBOSS CHARACTER
    ********************************** */
    if (!AIMiniBossTextureWalkRight.loadFromFile("data/Character-Animation/minibossapemoveright.png"))
        std::cout << "Failed to load data/Character-Animation/minibossapemoveright.png" << std::endl << std::endl;
    if (!AIMiniBossTextureWalkLeft.loadFromFile("data/Character-Animation/minibossapemoveleft.png"))
        std::cout << "Failed to load data/Character-Animation/minibossapemoveleft.png" << std::endl << std::endl;


    /* **********************************
                BOSS CHARACTER
     ********************************** */
    if (!AIBossTextureWalkRight.loadFromFile("data/Character-Animation/gorillamoveright.png"))
        std::cout << "Failed to load data/Character-Animation/gorillamoveright.png" << std::endl << std::endl;
    if (!AIBossTextureWalkLeft.loadFromFile("data/Character-Animation/gorillamoveleft.png"))
        std::cout << "Failed to load data/Character-Animation/gorillamoveleft.png" << std::endl << std::endl;

    /* **********************************
                PRINCESS CHARACTER
     ********************************** */

    if (!PrincessTextureWalkRight.loadFromFile("data/Character-Animation/princessidleright.png"))
        std::cout << "Failed to load data/Character-Animation/princessidleright.png" << std::endl << std::endl;
    if (!PrincessTextureWalkLeft.loadFromFile("data/Character-Animation/princessidleleft.png"))
        std::cout << "Failed to load data/Character-Animation/princessidleleft.png" << std::endl << std::endl;
}
/**
 * @param character, which character the texture is being applied for.
 * @param lastplayeranimationplayed, is used to check what animation is played last.
 * So that it always start at the beginning.
 * @param frameSelected, is the actual frame used to select which picture to use as texture.
 * frameSelected->left is where the picture begins.
 * Animation goes from left to right, then right to left.
 */
void Animation::PlayerWalkRight(sf::RectangleShape* character)
{
    if(lastplayeranimationplayed != 3)
    {
        frameSelected->left = 0;
        lastplayeranimationplayed = 3;
    }
    else if(frameSelected->left > 102)
        frameSelected->left = 0;
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
/**
 * @param character, which character the texture is being applied for.
 * @param lastplayeranimationplayed, is used to check what animation is played last.
 * So that it always start at the beginning.
 * @param frameSelected, is the actual frame used to select which picture to use as texture.
 * frameSelected->left is where the picture begins.
 * Animation goes from left to right, then right to left.
 */
void Animation::PlayerWalkLeft(sf::RectangleShape* character)
{
    if(lastplayeranimationplayed != 2)
    {
        frameSelected->left = 0;
        lastplayeranimationplayed = 2;
    }
    else if(frameSelected->left > 102)
        frameSelected->left = 0;
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
/**
 * @param character, which character the texture is being applied for.
 * @param lastplayeranimationplayed, is used to check what animation is played last.
 * So that it always start at the beginning.
 * @param frameSelected, is the actual frame used to select which picture to use as texture.
 * frameSelected->left is where the picture begins.
 * Animation goes from left to right, then right to left.
 */
void Animation::PlayerIdleLeft(sf::RectangleShape* character)
{
    if(lastplayeranimationplayed != 3)
    {
        frameSelected->left = 0;
        lastplayeranimationplayed = 3;
    }
    else if(frameSelected->left > 102)
        frameSelected->left = 0;
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
/**
 * @param character, which character the texture is being applied for.
 * @param lastplayeranimationplayed, is used to check what animation is played last.
 * So that it always start at the beginning.
 * @param frameSelected, is the actual frame used to select which picture to use as texture.
 * frameSelected->left is where the picture begins.
 * Animation goes from left to right, then right to left.
 */
void Animation::PlayerIdle(sf::RectangleShape* character)
{
    if(lastplayeranimationplayed != 5)
    {
        frameSelected->left = 0;
        lastplayeranimationplayed = 5;
    }
    else if(frameSelected->left > 102)
        frameSelected->left = 0;
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
/**
 * @param character, which character the texture is being applied for.
 * @param lastplayeranimationplayed, is used to check what animation is played last.
 * So that it always start at the beginning.
 * @param frameSelected, is the actual frame used to select which picture to use as texture.
 * frameSelected->left is where the picture begins.
 * Animation goes from left to right, then right to left.
 */
void Animation::PlayerJumpRight(sf::RectangleShape* character)
{
    if(lastplayeranimationplayed != 1)
    {
        frameSelected->left = 0;
        lastplayeranimationplayed = 1;
    }
    else if(frameSelected->left > 136)
        frameSelected->left = 0;
    character->setTexture(&PlayerTextureJump);
    if(animationdir == 1)
    {
        if (frameSelected->left < 136)
            frameSelected->left += 34;
        else
        {
            frameSelected->left -= 34;
            animationdir = 0;
        }
    }
    else
    {
        if (frameSelected->left > 68)
            frameSelected->left -= 34;
        else
        {
            frameSelected->left += 34;
            animationdir = 1;
        }
    }

    character->setTextureRect(*frameSelected);
}
/**
 * @param character, which character the texture is being applied for.
 * @param lastplayeranimationplayed, is used to check what animation is played last.
 * So that it always start at the beginning.
 * @param frameSelected, is the actual frame used to select which picture to use as texture.
 * frameSelected->left is where the picture begins.
 * Animation goes from left to right, then right to left.
 */
void Animation::PlayerJumpLeft(sf::RectangleShape* character)
{
    if(lastplayeranimationplayed != 1)
    {
        frameSelected->left = 0;
        lastplayeranimationplayed = 1;
    }
    else if(frameSelected->left > 136)
        frameSelected->left = 0;
    character->setTexture(&PlayerTextureJumpflipped);
    if(animationdir == 1)
    {
        if (frameSelected->left < 136)
            frameSelected->left += 34;
        else
        {
            frameSelected->left -= 34;
            animationdir = 0;
        }
    }
    else
    {
        if (frameSelected->left > 68)
            frameSelected->left -= 34;
        else
        {
            frameSelected->left += 34;
            animationdir = 1;
        }
    }

    character->setTextureRect(*frameSelected);
}
/**
 * TODO: not implemented yet. Due to the pictures being so different in sizes
 * @param character, which character the texture is being applied for.
 * So that it always start at the beginning.
 * @param frameSelected, is the actual frame used to select which picture to use as texture.
 * frameSelected->left is where the picture begins.
 * Animation goes from left to right, then right to left.
 */
void Animation::PlayerDie(sf::RectangleShape* character)
{

}
/**
 * @param character, which character the texture is being applied for.
 * So that it always start at the beginning.
 * @param frameSelected, is the actual frame used to select which picture to use as texture.
 * frameSelected->left is where the picture begins.
 * Animation goes from left to right, then right to left.
 */
void Animation::AIWalkRight(sf::RectangleShape* character)
{
    if(frameSelected->left > 216)
        frameSelected->left = 0;
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
/**
 * @param character, which character the texture is being applied for.
 * So that it always start at the beginning.
 * @param frameSelected, is the actual frame used to select which picture to use as texture.
 * frameSelected->left is where the picture begins.
 * Animation goes from left to right, then right to left.
 */
void Animation::AIWalkLeft(sf::RectangleShape* character)
{
    if(frameSelected->left > 216)
        frameSelected->left = 0;
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

/**
 * @param character, which character the texture is being applied for.
 * So that it always start at the beginning.
 * @param frameSelected, is the actual frame used to select which picture to use as texture.
 * frameSelected->left is where the picture begins.
 * Animation goes from left to right, then right to left.
 */
void Animation::AIMiniBossWalkRight(sf::RectangleShape* character)
{
    if(frameSelected->left > 216)
        frameSelected->left = 0;
    character->setTexture(&AIMiniBossTextureWalkRight);
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
/**
 * @param character, which character the texture is being applied for.
 * So that it always start at the beginning.
 * @param frameSelected, is the actual frame used to select which picture to use as texture.
 * frameSelected->left is where the picture begins.
 * Animation goes from left to right, then right to left.
 */
void Animation::AIMiniBossWalkLeft(sf::RectangleShape* character)
{
    if(frameSelected->left > 216)
        frameSelected->left = 0;
    character->setTexture(&AIMiniBossTextureWalkLeft);
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

/**
 * @param character, which character the texture is being applied for.
 * So that it always start at the beginning.
 * @param frameSelected, is the actual frame used to select which picture to use as texture.
 * frameSelected->left is where the picture begins.
 * Animation goes from left to right, then right to left.
 */
void Animation::AIBossWalkRight(sf::RectangleShape* character)
{
    if(frameSelected->left > 605)
        frameSelected->left = 0;
    character->setTexture(&AIBossTextureWalkRight);
    if(animationdir == 1)
    {
        if (frameSelectedBoss->left < 605)
            frameSelectedBoss->left += 55;
        else
        {
            frameSelectedBoss->left -= 55;
            animationdir = 0;
        }
    }
    else
    {
        if (frameSelectedBoss->left > 0)
            frameSelectedBoss->left -= 55;
        else
        {
            frameSelectedBoss->left += 55;
            animationdir = 1;
        }
    }

    character->setTextureRect(*frameSelectedBoss);
}
/**
 * @param character, which character the texture is being applied for.
 * So that it always start at the beginning.
 * @param frameSelected, is the actual frame used to select which picture to use as texture.
 * frameSelected->left is where the picture begins.
 * Animation goes from left to right, then right to left.
 */
void Animation::AIBossWalkLeft(sf::RectangleShape* character)
{
    if(frameSelected->left > 605)
        frameSelected->left = 0;
    character->setTexture(&AIBossTextureWalkLeft);
    if(animationdir == 1)
    {
        if (frameSelectedBoss->left < 605)
            frameSelectedBoss->left += 55;
        else
        {
            frameSelectedBoss->left -= 55;
            animationdir = 0;
        }
    }
    else
    {
        if (frameSelectedBoss->left > 0)
            frameSelectedBoss->left -= 55;
        else
        {
            frameSelectedBoss->left += 55;
            animationdir = 1;
        }
    }

    character->setTextureRect(*frameSelectedBoss);
}

/**
 * @param character, which character the texture is being applied for.
 * So that it always start at the beginning.
 * @param frameSelected, is the actual frame used to select which picture to use as texture.
 * frameSelected->left is where the picture begins.
 * Animation goes from left to right, then right to left.
 */
void Animation::PrincessWalkRight(sf::RectangleShape* character)
{
    if(frameSelected->left > 68)
        frameSelected->left = 0;
    character->setTexture(&PrincessTextureWalkRight);
    if(animationdir == 1)
    {
        if (frameSelected->left < 68)
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
/**
 * @param character, which character the texture is being applied for.
 * So that it always start at the beginning.
 * @param frameSelected, is the actual frame used to select which picture to use as texture.
 * frameSelected->left is where the picture begins.
 * Animation goes from left to right, then right to left.
 */
void Animation::PrincessWalkLeft(sf::RectangleShape* character)
{
    if(frameSelected->left > 102)
        frameSelected->left = 34;
    character->setTexture(&PrincessTextureWalkLeft);
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
        if (frameSelected->left > 34)
            frameSelected->left -= 34;
        else
        {
            frameSelected->left += 34;
            animationdir = 1;
        }
    }

    character->setTextureRect(*frameSelected);
}