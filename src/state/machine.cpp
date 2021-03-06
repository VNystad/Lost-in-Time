#include "machine.h"
#include "state.h"
#include "statemainmenu.h"
#include "stategame.h"
#include "stateloadgame.h"

// Creating machine
Machine::Machine()
{
    // Start state machine
    running = true;

    // Start in mainmenu
    state = StateId::MAINMENU;

    // Add all states to the map
    states.emplace(StateId::GAME, new StateGame());
    states.emplace(StateId::MAINMENU, new StateMainMenu());
    states.emplace(StateId::LOAD, new StateLoadGame());
}

// Destructing machine
Machine::~Machine()
{
    // Free states from memory
    for (auto state: states)
        delete state.second;

    states.clear();
}

// Go to next state
void Machine::GoNext(sf::RenderWindow& window, SavedObject& SO, Highscore& highscore)
{
    states[state]->GoNext(*this, window, SO, highscore);
}

// Sets state
void Machine::SetState(StateId state)
{
    this->state = state;
}
