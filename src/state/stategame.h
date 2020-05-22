#ifndef LOST_IN_TIME_STATEGAME_H
#define LOST_IN_TIME_STATEGAME_H

#include "state.h"
#include "../Interface/highscore.h"

class StateGame : public State
{
public:
    void GoNext(Machine &machine, sf::RenderWindow& window, SavedObject&, Highscore&);
};


#endif
