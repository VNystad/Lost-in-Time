
#ifndef LOST_IN_TIME_AIMONKEY_H
#define LOST_IN_TIME_AIMONKEY_H

#include "AI.h"
#include "../Objects/playertest.h"

class AIEnemies: public AI {
public:
    AIEnemies(float x, float y, float patrol, const Config &config, sf::RenderWindow *window);

    void MonkeyAI1(AIEnemies* e, PlayerTest* p);

private:
    //const int sizeWidth = 34;
    //const int sizeHeight = 50;
    int OriginalX;
    int OriginalY;

    int patrolleft;
    int patrolright;

    int enragerange = 100;

};


#endif //LOST_IN_TIME_AIMONKEY_H