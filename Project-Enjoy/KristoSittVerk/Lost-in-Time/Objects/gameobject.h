#ifndef LOST_IN_TIME_OBJECTSUPER_H
#define LOST_IN_TIME_OBJECTSUPER_H


#include <SFML/Graphics/Texture.hpp>

class GameObject : public sf::Texture
{
public:
    virtual void DrawMe();

    virtual int GetPositionX();
    virtual int GetPositionY();
    virtual void SetPosition(int x, int y);
    virtual void SetPositionX(int x);
    virtual void SetPositionY(int y);

    virtual int GetTilePositionX();
    virtual int GetTilePositionY();
    virtual void SetTilePositionX(int x);
    virtual void SetTilePositionY(int y);
    virtual void SetTilePosition(int x, int y);

    bool IsCollidable() const { return collidable; }

protected:
    int positionX;
    int positionY;
    int tilePositionX;
    int tilePositionY;
    // is object collidable?
    bool collidable;
};


#endif
