#include "stategame.h"
#include "machine.h"
#include "../testapp.h"

void StateGame::GoNext(Machine &machine, sf::RenderWindow& window)
{
    TestApp testapp(window);

    while(testapp.Tick());
}
