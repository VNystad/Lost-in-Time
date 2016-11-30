#ifndef LOST_IN_TIME_TESTSTATE_H
#define LOST_IN_TIME_TESTSTATE_H


#include "state.h"

class TestState : public State
{
public:
    void GoNext(Machine &machine);
};


#endif //LOST_IN_TIME_TESTSTATE_H
