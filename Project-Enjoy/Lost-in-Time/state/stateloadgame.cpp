#include <iostream>
#include <fstream>
#include "stateloadgame.h"
#include "machine.h"


sf::Texture *StateLoadGame::LoadTexture( std::string path)
{
    //temp texture
    sf::Texture *newTexture = new sf::Texture();
    //newTexture->loadFromFile(path);

    if(!newTexture->loadFromFile(path))
    {
        std::cout << "Could not load image on path: " << path << std::endl;
    }
    menuAmount++;
    return newTexture;
}
bool StateLoadGame::loadMedia()
{
    save1 = LoadTexture("data/loadgame/save1.png");
    save2 = LoadTexture("data/loadgame/save2.png");
    save3 = LoadTexture("data/loadgame/save3.png");

    save1Sprite = new sf::Sprite;
    save1Sprite->setTexture(*save1);
    save1Sprite->setPosition(-70, -20);
    save2Sprite = new sf::Sprite;
    save2Sprite->setTexture(*save2);
    save2Sprite->setPosition(-70, 80);
    save3Sprite = new sf::Sprite;
    save3Sprite->setTexture(*save3);
    save3Sprite->setPosition(-70, 180);

    return true;
}
/**
 * Loads the selected game:
 * Player name
 * Player position
 * Player hp
 * Player elapsed time
 * Score?
 * Alive enemies position
 * @param selected The selected int value of a save
 */
void StateLoadGame::LoadGame(int selected)
{
    std::ifstream saveFile;
    std::string test;
    if(selected == 1) // Selected save 1
    {
        // Open save file 1
        saveFile.open("SaveFiles/save1.txt");

        // Read information from file
        if(saveFile.is_open())
            // While saveFile end of file flag not set
            while(!saveFile.eof())
            {
                std::getline(saveFile, test);
                std::cout << test << std::endl;
            }
        saveFile.close();
        std::cout << "Loaded save file 1" << std::endl;

        // Place player on saved location
        // Load player HP

        // Place alive enemies on saved location
        // Load score
        // Load time elapsed

        // Start up game 1
    }
    else if(selected == 2) // Selected save 2
    {
        //saveFile.open("SaveFiles/save2.txt");
        // Read information from file save 2
        // Place player on saved location
        // Place alive enemies on saved location
        // Load score
        // Load time elapsed

        // Start up game 2
    }
    else if(selected == 3) // Selected save 3
    {
        //saveFile.open("SaveFiles/save2.txt");
        // Read information from file save 3
        // Place player on saved location
        // Place alive enemies on saved location
        // Load score
        // Load time elapsed

        // Start up game 3
    }
}

void StateLoadGame::GoNext(Machine &machine, sf::RenderWindow& window)
{
    loadMedia();



    while (inLoad) {


        while (window.pollEvent(event)) {
            //If X clicked on window
            if (event.type == sf::Event::Closed) {
                window.close();
                exit(0);
            }
        }

        //If Escape pressed on keyboard
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
            machine.SetState(Machine::StateId::MAINMENU);
            inLoad = false;
            return;
        }

        /*****************************
         * If you press down or up key
         ****************************/
        if (!keyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            selected++;
            if (selected > menuAmount)
                selected = 1;
            keyPressed = true;
        }
        if (!keyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            selected--;
            if (selected <= 0)
                selected = menuAmount;
            keyPressed = true;
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            keyPressed = false;

        // Clear window
        window.clear(sf::Color::Black);

        if(selected == 1)
        {
            window.draw(*save1Sprite); // Change to save1SpriteSelected later
            window.draw(*save2Sprite);
            window.draw(*save3Sprite);
        }
        else if(selected == 2)
        {
            window.draw(*save1Sprite);
            window.draw(*save2Sprite); // Change to save2SpriteSelected later
            window.draw(*save3Sprite);
        }
        else if(selected == 3)
        {
            window.draw(*save1Sprite);
            window.draw(*save2Sprite);
            window.draw(*save3Sprite); // Change to save3SpriteSelected later
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && keyPressed)
        {
            LoadGame(selected);
        }

        window.display();
    }
}