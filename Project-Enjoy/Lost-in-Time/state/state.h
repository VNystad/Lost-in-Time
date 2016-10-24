#ifndef STATE_STATE_H
#define STATE_STATE_H

#include <SFML/Window/Event.hpp>

class Machine;

class State
{
public:
    sf::Event event;
    State() {}
    virtual ~State() {};
    virtual void GoNext(Machine &context) = 0;

};


#endif //STATE_STATE_H