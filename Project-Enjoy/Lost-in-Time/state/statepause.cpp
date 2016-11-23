#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include "statepause.h"
#include "machine.h"

/* When changing to Pause state, when user press 'R' resume game applcation
 *  When in pause state, show menu. Save Game, Load Game, Main Menu, Settings, Exit
 */

void StatePause::GoNext(Machine &machine)
{
    std::cout << "Paused" << std::endl;
    while(1)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            machine.SetState(Machine::StateId::GAME);
            break;
        }
    }

}