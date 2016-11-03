#include "gameobject.h"

GameObject::GameObject()
{

}

void GameObject::DrawMe()
{

}

void GameObject::SetPosition(float X, float Y)
{
    positionX = X;
    positionY = Y;
}

void GameObject::SetPositionX(float x)
{
    positionX = x;
}

void GameObject::SetPositionY(float y)
{
    positionY = y;
}

void GameObject::SetTilePositionX(float x)
{
    tilePositionX = x * 32;
}

void GameObject::SetTilePositionY(float y)
{
    tilePositionY = y * 32;
}

void GameObject::SetTilePosition(float x, float y)
{
    tilePositionX = x * 32;
    tilePositionY = y * 32;
}

float GameObject::GetTilePositionX()
{
    return tilePositionX;
}

float GameObject::GetTilePositionY()
{
    return tilePositionY;
}

float GameObject::GetPositionX()
{
    return positionX;
}

float GameObject::GetPositionY()
{
    return positionY;
}
