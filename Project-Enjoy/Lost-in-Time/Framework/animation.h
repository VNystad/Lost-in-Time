#ifndef LOST_IN_TIME_ANIMATION_H
#define LOST_IN_TIME_ANIMATION_H

#include <SFML/Graphics.hpp>

class Animation {
public:
    Animation() { };
    ~Animation() { };
    void init();

    int GetSizeWidth() { return PlayersizeWidth; };
    int GetSizeHeight() { return PlayersizeHeight; };
    void SetSizeWidth(int width) { this->PlayersizeWidth = width; }
    void SetSizeHeight(int height) { this->PlayersizeHeight = height; }

    void PlayerWalkRight(sf::RectangleShape* character);
    void PlayerWalkLeft(sf::RectangleShape* character);
    void PlayerIdle(sf::RectangleShape* character);
    void PlayerJumpRight(sf::RectangleShape* character);
    void PlayerJumpLeft(sf::RectangleShape* character);
    void PlayerDie(sf::RectangleShape* character);

protected:

    int PlayersizeWidth = 34;
    int PlayersizeHeight = 50;

    // Choose starting frame in texture picture
    sf::IntRect *frameSelected;

    // Textures for animation
    sf::Texture PlayerTextureJump;
    sf::Texture PlayerTextureIdle;
    sf::Texture PlayerTextureWalk;
    sf::Texture PlayerTextureDeath;

    // Textures for flipped animations
    sf::Texture PlayerTextureJumpflipped;
    sf::Texture PlayerTextureWalkflipped;
};


#endif
