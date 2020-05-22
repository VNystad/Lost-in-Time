#include "Mace.h"

Mace::Mace()
{
    this->ItemTexture = new sf::Texture;
    this->ItemTexture->loadFromFile("data/Objects/Mace.png");
    this->ItemSprite = new sf::Sprite;
    this->ItemSprite->setTexture(*ItemTexture);
    this->positionX = 50;
    this->positionY = 432;
}
