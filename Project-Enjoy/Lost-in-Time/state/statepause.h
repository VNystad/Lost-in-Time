#ifndef STATE_STATEPAUSE_H
#define STATE_STATEPAUSE_H

#include "state.h"

class StatePause : public State
{
public:
    void GoNext(Machine &machine, sf::RenderWindow& window);
};


#endif
