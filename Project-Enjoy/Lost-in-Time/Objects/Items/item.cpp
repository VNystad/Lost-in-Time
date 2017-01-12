#include "item.h"

void Item::PlaceItem(float x, float y)
{
    this->positionX = x;
    this->positionY = y;
}


void Item::drawItem(sf::RenderWindow& window)
{
    ItemSprite->setPosition(this->positionX, this->positionY);
    window.draw(*ItemSprite);
}