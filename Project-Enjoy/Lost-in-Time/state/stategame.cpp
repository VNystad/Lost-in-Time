#include "stategame.h"
#include "machine.h"
#include "../testapp.h"

void StateGame::GoNext(Machine &machine, sf::RenderWindow& window, SavedObject& so)
{
    TestApp testapp(window, so);


    while(testapp.Tick(machine));
}
