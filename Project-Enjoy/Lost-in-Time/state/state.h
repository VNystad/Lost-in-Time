#ifndef STATE_STATE_H
#define STATE_STATE_H

#include <SFML/Graphics.hpp>

class Machine;

class State
{
public:
    State() {}
    virtual ~State() {};
    virtual void GoNext(Machine &context, sf::RenderWindow& window) = 0;

    sf::Event event;

};


#endif