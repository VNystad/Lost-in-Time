#ifndef LOST_IN_TIME_STATEGAME_H
#define LOST_IN_TIME_STATEGAME_H

#include "state.h"

class StateGame : public State
{
public:
    void GoNext(Machine &machine, sf::RenderWindow& window);
};


#endif
