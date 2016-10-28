#ifndef LOST_IN_TIME_LOADGAMESTATE_H
#define LOST_IN_TIME_LOADGAMESTATE_H


#include "state.h"

class loadgamestate : public State
{
public:

    void GoNext(Machine &machine);

};


#endif //LOST_IN_TIME_LOADGAMESTATE_H
