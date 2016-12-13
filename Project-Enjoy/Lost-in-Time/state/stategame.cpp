#include "stategame.h"
#include "machine.h"
#include "../app.h"

void StateGame::GoNext(Machine &machine, sf::RenderWindow& window, SavedObject& so, Highscore& highscore)
{
    TestApp testapp(window, so);


    while(testapp.Tick(machine, highscore));
}
