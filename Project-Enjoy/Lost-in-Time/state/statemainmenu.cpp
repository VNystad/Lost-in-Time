#include <iostream>
#include "statemainmenu.h"
#include "machine.h"
/****************************************
 * Loads images from path into temp texture
 * @param path = file path where image is
 ****************************************/
sf::Texture *StateMainMenu::LoadTexture( std::string path)
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
/***********************************
 * Loads texture pointers
 * using the function above, making sprites
 * of them
 **********************************/
bool StateMainMenu::loadMedia()
{
    //Load success flag
    bool success = true;
    BackgroundTexture = LoadTexture("Resources/Pictures/backgroundmainmenu.png");
    NewGameTexture = LoadTexture("Resources/Pictures/newgame.png");
    NewGameSelectedTexture = LoadTexture("Resources/Pictures/newgameselected.png");
    LoadGameTexture = LoadTexture("Resources/Pictures/loadgame.png");
    LoadGameSelectedTexture = LoadTexture("Resources/Pictures/loadgameselected.png");
    ExitGameTexture = LoadTexture("Resources/Pictures/exitgame.png");
    ExitGameSelectedTexture = LoadTexture("Resources/Pictures/exitgameselected.png");

    return success;
}

void StateMainMenu::GoNext(Machine &machine)
{
    //Key pressed flag off
    keypressed = false;
    // Loads media
    loadMedia();
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(*BackgroundTexture);
    backgroundSprite.setScale(
            config.screenWidth / backgroundSprite.getLocalBounds().width,
            config.screenHeight / backgroundSprite.getLocalBounds().height);

    sf::Sprite newGameSprite;
    newGameSprite.setTexture(*NewGameTexture);
    newGameSprite.setPosition(-60, -200);
    sf::Sprite newGameSelectedSprite;
    newGameSelectedSprite.setTexture(*NewGameSelectedTexture);
    newGameSelectedSprite.setPosition(-60, -200);
    sf::Sprite loadGameSprite;
    loadGameSprite.setTexture(*LoadGameTexture);
    loadGameSprite.setPosition(10, 200);
    sf::Sprite loadGameSelectedSprite;
    loadGameSelectedSprite.setTexture(*LoadGameSelectedTexture);
    loadGameSelectedSprite.setPosition(10, 200);
    sf::Sprite exitGameSprite;
    exitGameSprite.setTexture(*ExitGameTexture);
    exitGameSprite.setPosition(10, 400);
    sf::Sprite exitGameSelectedSprite;
    exitGameSelectedSprite.setTexture(*ExitGameSelectedTexture);
    exitGameSelectedSprite.setPosition(10, 400);

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
            if(menu > 3)
                menu = 1;
            keypressed = true;
        }
        if(!keypressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            menu --;
            if(menu <= 0)
                menu = 3;
            keypressed = true;
        }
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            keypressed = false;

        /******************************
         * Check what option user is on
         * and draw new picture
         *****************************/

        MainMenuWindow.clear(sf::Color::Black);
        MainMenuWindow.draw(backgroundSprite);
        if(menu == 1)
        {
            MainMenuWindow.draw(newGameSelectedSprite);
            MainMenuWindow.draw(loadGameSprite);
            MainMenuWindow.draw(exitGameSprite);
        }
        if(menu == 2)
        {
            MainMenuWindow.draw(newGameSprite);
            MainMenuWindow.draw(loadGameSelectedSprite);
            MainMenuWindow.draw(exitGameSprite);
        }
        if(menu == 3)
        {
            MainMenuWindow.draw(newGameSprite);
            MainMenuWindow.draw(loadGameSprite);
            MainMenuWindow.draw(exitGameSelectedSprite);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            if(menu == 1)
            {
                machine.SetState(Machine::StateId::GAME);
            }
            if(menu == 2)
            {
                //machine.SetState(Machine::StateId::LOAD);
            }
            if(menu == 3)
            {
                MainMenuWindow.close();
                machine.SetRunning(false);
            }
        }

        /********************************
         * Display window with new content
         ********************************/
        MainMenuWindow.display();
    }

}