#ifndef STATE_STATE_H
#define STATE_STATE_H

#include <SFML/Graphics.hpp>
#include "../Objects/savedobject.h"

class Machine;

class State
{
public:
    State() {}
    virtual ~State() {};
    virtual void GoNext(Machine &context, sf::RenderWindow& window, SavedObject&) = 0;

    sf::Event event;

};


#endif