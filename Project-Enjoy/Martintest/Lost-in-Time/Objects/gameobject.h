#ifndef LOST_IN_TIME_OBJECTSUPER_H
#define LOST_IN_TIME_OBJECTSUPER_H


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Framework/config.h"

class GameObject : public sf::Texture
{
public:
    GameObject();
    virtual void DrawMe();

    virtual float GetPositionX();
    virtual float GetPositionY();
    virtual void SetPosition(float x, float y);
    virtual void SetPositionX(float x);
    virtual void SetPositionY(float y);

    virtual float GetTilePositionX();
    virtual float GetTilePositionY();
    virtual void SetTilePositionX(float x);
    virtual void SetTilePositionY(float y);
    virtual void SetTilePosition(float x, float y);

    bool IsCollidable() const { return collidable; }

protected:
    float positionX;
    float positionY;
    float tilePositionX;
    float tilePositionY;
    // is object collidable?
    bool collidable;

};


#endif //LOST_IN_TIME_OBJECTSUPER_H
