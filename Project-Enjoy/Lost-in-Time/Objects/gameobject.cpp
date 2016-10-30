#include "gameobject.h"

void GameObject::DrawMe()
{

}

void GameObject::SetPosition(int X, int Y)
{
    positionX = X;
    positionY = Y;
}

void GameObject::SetPositionX(int x)
{
    positionX = x;
}

void GameObject::SetPositionY(int y)
{
    positionY = y;
}

void GameObject::SetTilePositionX(int x)
{
    tilePositionX = x * 32;
}

void GameObject::SetTilePositionY(int y)
{
    tilePositionY = y * 32;
}

void GameObject::SetTilePosition(int x, int y)
{
    tilePositionX = x * 32;
    tilePositionY = y * 32;
}

int GameObject::GetTilePositionX()
{
    return tilePositionX;
}

int GameObject::GetTilePositionY()
{
    return tilePositionY;
}

int GameObject::GetPositionX()
{
    return positionX;
}

int GameObject::GetPositionY()
{
    return positionY;
}
