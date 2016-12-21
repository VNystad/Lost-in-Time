#ifndef LOST_IN_TIME_TILEOBJECT_H
#define LOST_IN_TIME_TILEOBJECT_H


class TileObject
{
public:
    TileObject(int x, int y, int id, bool collidable);


protected:
    int x;
    int y;
    int id;
    bool collidable = false;
};


#endif //LOST_IN_TIME_TILEOBJECT_H
