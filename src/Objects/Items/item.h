
#ifndef LOST_IN_TIME_ITEM_H
#define LOST_IN_TIME_ITEM_H


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Item
{
public:
    Item(){};
    void PlaceItem(float x, float y);
    bool setPickedUp(bool pickedUp) { this->pickedUp = pickedUp; };
    bool isPicked() const {return pickedUp; };

    void drawItem(sf::RenderWindow& window);
protected:
    bool pickedUp = false;
    float positionX;
    float positionY;
    sf::Texture* ItemTexture;
    sf::Sprite* ItemSprite;
};


#endif //LOST_IN_TIME_ITEM_H
