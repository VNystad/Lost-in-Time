#include "health.h"

float Health::GetOriginalLifePoints()
{
    return originalhealth;
}

void Health::SetOriginalLifePoints(int value)
{
    this->originalhealth = originalhealth;
}

float Health::GetActualLifePoints()
{
    return actuallifepoints;
}

void Health::SetActualLifePoints(int value)
{
    this->actuallifepoints = value;
}

float Health::GetVisibleLifePoints()
{
    return visiblelifepoints;
}

void Health::SetVisibleLifePoints(int value)
{
    this->visiblelifepoints = value;
}

void Health::ResetHealth()
{
    this->visiblelifepoints = this->actuallifepoints = originalhealth;
}

void Health::Hit(int damage)
{
    this->actuallifepoints -= damage;
}

float Health::GetWidth()
{
    return width;
}

void Health::SetWidth(float width)
{
    this->width = width;
}

float Health::GetHeight()
{
    return height;
}

void Health::SetHeight(float height)
{
    this->height = height;
}

void Health::DrawMe()
{
    // @Kristoffer, this is where you left off.
}