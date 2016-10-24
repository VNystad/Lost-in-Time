#include <iostream>
#include <SFML/Graphics.hpp>
#include "stategame.h"
#include "machine.h"
#include "../Framework/config.h"

void StateGame::GoNext(Machine &machine)
{
    // Make game application window
    Config config;
    sf::RenderWindow gameapp(sf::VideoMode(config.screenWidth, config.screenHeight, 32), "Lost in Time demo v01");
    gameapp.setVerticalSyncEnabled(true);
    gameapp.setFramerateLimit(60);
    gameapp.setMouseCursorVisible(false);

    std::cout << "Game Window!" << std::endl;
    while(1)
    {
        while(gameapp.pollEvent(event))
        {
            //Window closed
            if(event.type == sf::Event::Closed)
            {
                gameapp.close();
                machine.SetRunning(false);
            }
        }
        // If the user click click the esc key
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            gameapp.close();
            machine.SetRunning(false);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
            machine.SetRunning(false);

        // Clear the App, make the bacground white
        gameapp.clear(sf::Color::White);

        // Display the window
        gameapp.display();
    }

}
