#include "stategame.h"
#include "machine.h"
#include "../levelOne.h"

void StateGame::GoNext(Machine &machine, sf::RenderWindow& window, SavedObject& so, Highscore& highscore)
{
    TestApp testapp(window, so);
    if(testapp.LoadedEmptySave())
    {
        machine.SetState(Machine::StateId::MAINMENU);
        return;
    }


    while(testapp.Tick(machine, highscore));
}
