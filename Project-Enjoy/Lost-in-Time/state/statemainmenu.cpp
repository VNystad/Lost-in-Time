#include <iostream>
#include "statemainmenu.h"
#include "machine.h"

sf::Texture *StateMainMenu::LoadTexture( std::string path)
{
    //Final texture
    sf::Texture *newTexture = new sf::Texture();
    newTexture->loadFromFile(path);

    if(!newTexture->loadFromFile(path))
    {
        std::cout << "Could not load image on path: " << path << std::endl;
    }
    menuAmount++;
    return newTexture;
}
/***********************************
 * Loads images to texture pointers
 * using the function above
 **********************************/
bool StateMainMenu::loadMedia()
{
    //Load success flag
    bool success = true;

    NewGameTexture = LoadTexture("Resources/Pictures/newgame.png");
    LoadGameTexture = LoadTexture("Resources/Pictures/loadgame.png");
    ExitGameTexture = LoadTexture("Resources/Pictures/exitgame.png");

    return success;
}

void StateMainMenu::GoNext(Machine &machine)
{
    //Key pressed flag off
    keypressed = false;
    // Loads media
    loadMedia();
    sf::Sprite sprite1;
    sprite1.setTexture(*NewGameTexture);
    sprite1.setPosition(100, 50);
    sf::Sprite sprite2;
    sprite2.setTexture(*LoadGameTexture);
    sprite2.setPosition(100, 300);
    sf::Sprite sprite3;
    sprite3.setTexture(*ExitGameTexture);
    sprite3.setPosition(100, 500);

    sf::RenderWindow MainMenuWindow;
    MainMenuWindow.create(sf::VideoMode(config.screenWidth, config.screenHeight,32), "Lost in Time demo v01");
    MainMenuWindow.setMouseCursorVisible(false);


    while (machine.GetRunning()) {

        while (MainMenuWindow.pollEvent(event)) {
            //If X clicked on window
            if (event.type == sf::Event::Closed)
            {
                MainMenuWindow.close();
                machine.SetRunning(false);
            }
        }

        //If Escape pressed on keyboard
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            MainMenuWindow.close();
            machine.SetRunning(false);
        }

        /*****************************
         * If you press down or up key
         ****************************/
        if(!keypressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            menu ++;
            if(menu > menuAmount)
                menu = 1;
            keypressed = true;
        }
        if(!keypressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            menu --;
            if(menu <= 0)
                menu = menuAmount;
            keypressed = true;
        }
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            keypressed = false;

        /******************************
         * Check what option user is on
         * and change make it clearly what
         * he/she is on
         *****************************/
        if(menu == 1)
        {
            sprite1.setColor(sf::Color::Red);
            sprite2.setColor(sf::Color::White);
            sprite3.setColor(sf::Color::White);
        }
        if(menu == 2)
        {
            sprite1.setColor(sf::Color::White);
            sprite2.setColor(sf::Color::Red);
            sprite3.setColor(sf::Color::White);
        }
        if(menu == 3)
        {
            sprite1.setColor(sf::Color::White);
            sprite2.setColor(sf::Color::White);
            sprite3.setColor(sf::Color::Red);
        }



        /**************
         * draw objects, first clear window
         *************/
        MainMenuWindow.clear(sf::Color::Black);
        MainMenuWindow.draw(sprite1);
        MainMenuWindow.draw(sprite2);
        MainMenuWindow.draw(sprite3);

        /********************************
         * Display window with new content
         ********************************/
        MainMenuWindow.display();
    }

}