#include "machine.h"
#include "state.h"
#include "statemainmenu.h"
#include "statepause.h"
#include "stategame.h"

// Creating machine
Machine::Machine()
{
    // Start state machine
    running = true;

    // Start in mainmenu
    state = StateId::GAME;

    // Add all states to the map
    states.emplace(StateId::GAME, new StateGame());
    states.emplace(StateId::MAINMENU, new StateMainMenu());
    states.emplace(StateId::PAUSE, new StatePause());
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
void Machine::GoNext()
{
    states[state]->GoNext(*this);
}

// Sets state
void Machine::SetState(StateId state)
{
    this->state = state;
}
