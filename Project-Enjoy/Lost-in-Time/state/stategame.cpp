#include "stategame.h"
#include "machine.h"
#include "../testapp.h"

void StateGame::GoNext(Machine &machine)
{
    TestApp testapp;

    while(testapp.Tick());

    // When game application closes, change to main menu state
    machine.SetState(Machine::StateId::MAINMENU);
}
