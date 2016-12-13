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

    BackgroundTexture = LoadTexture("data/main-menu/backgroundmainmenu.png");

    NewGameTexture = LoadTexture("data/main-menu/NewGame.png");
    NewGameSelectedTexture = LoadTexture("data/main-menu/NewGameSelected.png");

    LoadGameTexture = LoadTexture("data/main-menu/LoadGame.png");
    LoadGameSelectedTexture = LoadTexture("data/main-menu/LoadGameSelected.png");

    HowToPlayTexture = LoadTexture("data/main-menu/HowToPlay2.png");
    HowToPlaySelectedTexture = LoadTexture("data/main-menu/HowToPlaySelected.png");
    HowToPlayPictureTexture = LoadTexture("data/main-menu/HowToPlaySprite.png");

    ExitGameTexture = LoadTexture("data/main-menu/ExitGame.png");
    ExitGameSelectedTexture = LoadTexture("data/main-menu/ExitGameSelected.png");

    return success;
}

void StateMainMenu::GoNext(Machine &machine, sf::RenderWindow& window, SavedObject&, Highscore&)
{
    while(sf::Keyboard::isKeyPressed(sf::Keyboard::Return));
    //Key pressed flag off
    keypressed = false;
    // Loads media
    loadMedia();


    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(*BackgroundTexture);
    backgroundSprite.setPosition(100,0);

    sf::Sprite newGameSprite;
    newGameSprite.setTexture(*NewGameTexture);
    newGameSprite.setPosition(250, 230);

    sf::Sprite newGameSelectedSprite;
    newGameSelectedSprite.setTexture(*NewGameSelectedTexture);
    newGameSelectedSprite.setPosition(250, 230);

    sf::Sprite loadGameSprite;
    loadGameSprite.setTexture(*LoadGameTexture);
    loadGameSprite.setPosition(240, 295);

    sf::Sprite loadGameSelectedSprite;
    loadGameSelectedSprite.setTexture(*LoadGameSelectedTexture);
    loadGameSelectedSprite.setPosition(240, 295);

    sf::Sprite HowToPlaySprite;
    HowToPlaySprite.setTexture(*HowToPlayTexture);
    HowToPlaySprite.setPosition(240, 360);
    sf::Sprite HowToPlaySelectedSprite;
    HowToPlaySelectedSprite.setTexture(*HowToPlaySelectedTexture);
    HowToPlaySelectedSprite.setPosition(240, 360);
    sf::Sprite HowToPlayPictureSprite;
    HowToPlayPictureSprite.setTexture(*HowToPlayPictureTexture);
    HowToPlayPictureSprite.setPosition(250,250);

    sf::Sprite exitGameSprite;
    exitGameSprite.setTexture(*ExitGameTexture);
    exitGameSprite.setPosition(250, 425);

    sf::Sprite exitGameSelectedSprite;
    exitGameSelectedSprite.setTexture(*ExitGameSelectedTexture);
    exitGameSelectedSprite.setPosition(250, 425);




    while (machine.GetRunning()) {

        while (window.pollEvent(event)) {
            //If X clicked on window
            if (event.type == sf::Event::Closed)
            {
                window.close();
                machine.SetRunning(false);
            }
        }

        //If Escape pressed on keyboard
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
            mainmenu = false;
            machine.SetRunning(false);
        }

        /*****************************
         * If you press down or up key
         ****************************/
        if(!keypressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            menu ++;
            if(menu > 4)
                menu = 1;
            keypressed = true;
        }
        if(!keypressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            menu --;
            if(menu <= 0)
                menu = 4;
            keypressed = true;
        }
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            keypressed = false;

        /******************************
         * Check what option user is on
         * and draw new picture
         *****************************/

        window.clear(sf::Color::Black);
        window.draw(backgroundSprite);
        if(menu == 1)
        {
            window.draw(newGameSelectedSprite);
            window.draw(loadGameSprite);
            window.draw(HowToPlaySprite);
            window.draw(exitGameSprite);
        }
        if(menu == 2)
        {
            window.draw(newGameSprite);
            window.draw(loadGameSelectedSprite);
            window.draw(HowToPlaySprite);
            window.draw(exitGameSprite);
        }
        if(menu == 3)
        {
            window.draw(newGameSprite);
            window.draw(loadGameSprite);
            window.draw(HowToPlaySelectedSprite);
            window.draw(exitGameSprite);
        }
        else if(menu == 4)
        {
            window.draw(newGameSprite);
            window.draw(loadGameSprite);
            window.draw(HowToPlaySprite);
            window.draw(exitGameSelectedSprite);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            if(menu == 1)
            {
                machine.SetState(Machine::StateId::GAME);
                mainmenu = false;
                return;
            }
            else if(menu == 2)
            {
                /*machine.SetState(Machine::StateId::LOAD);
                mainmenu = false;*/
                return;
            }
            else if(menu == 3)
            {
                while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                {
                    window.clear(sf::Color::Black);
                    window.draw(HowToPlayPictureSprite);
                    window.display();
                }
            }
            else if(menu == 4)
            {
                window.close();
                mainmenu = false;
                machine.SetRunning(false);
            }
        }

        /********************************
         * Display window with new content
         ********************************/
        window.display();
    }

}