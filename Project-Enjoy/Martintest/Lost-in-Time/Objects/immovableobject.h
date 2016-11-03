#ifndef LOST_IN_TIME_IMMOVABLEOBJECT_H
#define LOST_IN_TIME_IMMOVABLEOBJECT_H


#include "gameobject.h"

class ImmovableObject : public GameObject
{
public:
    ImmovableObject(int x, int y);
    ~ImmovableObject();
};

#endif //LOST_IN_TIME_IMMOVABLEOBJECT_H
