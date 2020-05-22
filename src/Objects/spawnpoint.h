#ifndef LOST_IN_TIME_SPAWNPOINTS_H
#define LOST_IN_TIME_SPAWNPOINTS_H

#include <string>

class SpawnPoint
{
    // Map needs to access protected/private data
    friend class Map;

public:
    SpawnPoint(){};

    std::string GetObject() const {return this->typeOfObject; }
    float GetX() const {return this->x; }
    float GetY() const {return this->y; }
    int GetPatrol() const {return this->patrol; }
protected:
    std::string typeOfObject;
    float x;
    float y;
    int patrol;
};


#endif //LOST_IN_TIME_SPAWNPOINTS_H
