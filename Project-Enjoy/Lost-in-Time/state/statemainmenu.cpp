#include <iostream>
#include <SFML/Graphics.hpp>
#include "statemainmenu.h"
#include "machine.h"

void StateMainMenu::GoNext(Machine &machine)
{
    std::cout << "Main menu!" << std::endl;
    while(1)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            machine.SetRunning(false);
    }

}