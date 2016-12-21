#include "tileobject.h"

TileObject::TileObject(int x, int y, int id, bool collidable)
{
    this->x = x;
    this->y = y;
    this->id = id;
    this->collidable = collidable;
}
