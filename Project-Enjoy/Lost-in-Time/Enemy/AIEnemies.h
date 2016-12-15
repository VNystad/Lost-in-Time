
#ifndef LOST_IN_TIME_AIMONKEY_H
#define LOST_IN_TIME_AIMONKEY_H

#include "AI.h"
#include "../Objects/playerobject.h"
#include <stdlib.h>

class AIEnemies: public AI {
public:
    AIEnemies(int x, int y, int patrol, bool boss, sf::RenderWindow *window);

    void MonkeyAI1(AIEnemies* e, PlayerObject* p);
    void MonkeyAI2(AIEnemies* e,PlayerObject* p, float delta);
    void GotHurt(AIEnemies* e, PlayerObject* p);


private:
    //const int sizeWidth = 34;
    //const int sizeHeight = 50;
    int OriginalX;
    int OriginalY;
    int patrolleft;
    int patrolright;

    int enragerange = 150;

    Sounds* sound1;
    Sounds* sound2;
    bool playedEnraged = false;
    int enragedsoundcooldown = 1;
};


#endif //LOST_IN_TIME_AIMONKEY_H
