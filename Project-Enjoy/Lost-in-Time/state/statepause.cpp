#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include "statepause.h"
#include "machine.h"

void StatePause::GoNext(Machine &machine, sf::RenderWindow& window)
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