#ifndef LOST_IN_TIME_OBJECTSUPER_H
#define LOST_IN_TIME_OBJECTSUPER_H


class ObjectSuper
{
public:
    virtual void DrawMe();
    virtual int GetPosition();
    virtual void SetPosition(int X, int Y);

    bool GetAlive();

protected:
    int positionX;
    int positionY;
    // Alive flag, skal/skal ikke tegnes
    bool Alive;
};


#endif
