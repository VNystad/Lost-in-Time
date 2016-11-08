#include <iostream>
#include <SFML/Graphics.hpp>
#include "stategame.h"
#include "machine.h"
#include "../Map/game.h"

void StateGame::GoNext(Machine &machine)
{
    Game game;

    std::cout << "Game Window!" << std::endl << std::endl;

    if (!game.init())
    {
        std::cout << "Failed to initialize the game. Quitting." << std::endl;
        return;
    }
    while(1)
    {
        game.run();
    }

}
