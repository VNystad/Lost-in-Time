#ifndef LOST_IN_TIME_OBJECT_H
#define LOST_IN_TIME_OBJECT_H


class Object
{
public:
    virtual void DrawMe();
    int GetPosition();

protected:
    int positionX;
    int positionY;
};


#endif
