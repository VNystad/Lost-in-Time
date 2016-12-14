#include <iostream>
#include "statemainmenu.h"
#include "machine.h"


void StateMainMenu::ShowHighscore(sf::RenderWindow& window, Highscore& highscore)
{
    highscoreMap = highscore.GetHighscoreMap();
    std::string score;
    sf::Text highscoreText;
    font = new sf::Font;
    if(!font->loadFromFile("data/Fonts/Arial/arial.ttf"))
        std::cout << "Could not load font from directory 'data/font.ttf'" << std::endl;
    highscoreText.setFont(*font);
    highscoreText.setCharacterSize(30);
    highscoreText.setColor(sf::Color::White);
    highscoreText.setString("Highscores: ");

    for(auto iter = highscoreMap->rbegin(); iter != highscoreMap->rend(); ++iter)
    {
        score = std::to_string(iter->first);
        highscoreText.setString(highscoreText.getString() + "\n" + iter->second + ": " + score);
    }

    while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        window.clear(sf::Color::Black);
        window.draw(highscoreText);
        window.display();
    }
}

void StateMainMenu::ShowHowToPlay(sf::RenderWindow& window)
{
    while(!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        window.clear(sf::Color::Black);
        window.draw(HowToPlayPictureSprite);
        window.display();
    }
}

void StateMainMenu::GoNext(Machine &machine, sf::RenderWindow& window, SavedObject&, Highscore& highscore)
{
    while(sf::Keyboard::isKeyPressed(sf::Keyboard::Return));
    //Key pressed flag off
    keypressed = false;
    // Loads media
    loadMedia();

    while (machine.GetRunning()) {

        while (window.pollEvent(event)) {
            //If X clicked on window
            if (event.type == sf::Event::Closed)
            {
                window.close();
                machine.SetRunning(false);
            }
        }

        /*****************************
         * If you press down or up key
         ****************************/
        if(!keypressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            keypressed = true;
            if(menu == 4)
                menu = 5;
            else if(menu == 5)
                menu = 1;
            else
            {
                menu += 2;
            }

        }
        else if(!keypressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            keypressed = true;
            if(menu == 1 || menu == 2)
                menu = 5;
            else
            {
                menu -= 2;
            }
        }
        else if(!keypressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            keypressed = true;
            if(menu == 5);
            else if(menu % 2 == 1)
            {
                menu += 1;
            }
            else
                menu -= 1;
        }
        else if(!keypressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            keypressed = true;
            if(menu == 5);
            else if(menu % 2 == 0)
            {
                menu -= 1;
            }
            else
                menu += 1;
        }
        else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            keypressed = false;

        /******************************
         * Check what option user is on
         * and draw new picture
         *****************************/

        window.clear(sf::Color::Black);
        window.draw(backgroundSprite);
        if(menu == 1)
        {
            window.draw(NewGameSelectedSprite);
            window.draw(LoadGameSprite);
            window.draw(HighscoreSprite);
            window.draw(HowToPlaySprite);
            window.draw(exitGameSprite);
        }
        if(menu == 2)
        {
            window.draw(NewGameSprite);
            window.draw(LoadGameSelectedSprite);
            window.draw(HighscoreSprite);
            window.draw(HowToPlaySprite);
            window.draw(exitGameSprite);
        }
        if(menu == 3)
        {
            window.draw(NewGameSprite);
            window.draw(LoadGameSprite);
            window.draw(HighscoreSelectedSprite);
            window.draw(HowToPlaySprite);
            window.draw(exitGameSprite);
        }
        else if(menu == 4)
        {
            window.draw(NewGameSprite);
            window.draw(LoadGameSprite);
            window.draw(HighscoreSprite);
            window.draw(HowToPlaySelectedSprite);
            window.draw(exitGameSprite);
        }
        else if(menu == 5)
        {
            window.draw(NewGameSprite);
            window.draw(LoadGameSprite);
            window.draw(HighscoreSprite);
            window.draw(HowToPlaySprite);
            window.draw(exitGameSelectedSprite);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            if(menu == 1)
            {
                machine.SetState(Machine::StateId::GAME);
                return;
            }
            else if(menu == 2)
            {
                machine.SetState(Machine::StateId::LOAD);
                return;
            }
            else if(menu == 3)
            {
                ShowHighscore(window, highscore);
            }
            else if(menu == 4)
            {
                ShowHowToPlay(window);
            }
            else if(menu == 5)
            {
                window.close();
                machine.SetRunning(false);
            }
        }

        /********************************
         * Display window with new content
         ********************************/
        window.display();
    }

}

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

    HighscoreTexture = LoadTexture("data/main-menu/Highscore.png");
    HighscoreSelectedTexture = LoadTexture("data/main-menu/HighScoreSelected.png");

    HowToPlayTexture = LoadTexture("data/main-menu/HowToPlay2.png");
    HowToPlaySelectedTexture = LoadTexture("data/main-menu/HowToPlaySelected.png");
    HowToPlayPictureTexture = LoadTexture("data/main-menu/HowToPlaySprite.png");

    ExitGameTexture = LoadTexture("data/main-menu/ExitGame.png");
    ExitGameSelectedTexture = LoadTexture("data/main-menu/ExitGameSelected.png");


    backgroundSprite.setTexture(*BackgroundTexture);
    backgroundSprite.setPosition(100,0);

    NewGameSprite.setTexture(*NewGameTexture);
    NewGameSprite.setPosition(25, 230);
    NewGameSelectedSprite.setTexture(*NewGameSelectedTexture);
    NewGameSelectedSprite.setPosition(25, 230);

    LoadGameSprite.setTexture(*LoadGameTexture);
    LoadGameSprite.setPosition(500, 230);
    LoadGameSelectedSprite.setTexture(*LoadGameSelectedTexture);
    LoadGameSelectedSprite.setPosition(500, 230);

    HighscoreSprite.setTexture(*HighscoreTexture);
    HighscoreSprite.setPosition(25, 320);
    HighscoreSelectedSprite.setTexture(*HighscoreSelectedTexture);
    HighscoreSelectedSprite.setPosition(25, 320);

    HowToPlaySprite.setTexture(*HowToPlayTexture);
    HowToPlaySprite.setPosition(500, 307);
    HowToPlaySelectedSprite.setTexture(*HowToPlaySelectedTexture);
    HowToPlaySelectedSprite.setPosition(500, 307);
    HowToPlayPictureSprite.setTexture(*HowToPlayPictureTexture);
    HowToPlayPictureSprite.setPosition(0,0);

    exitGameSprite.setTexture(*ExitGameTexture);
    exitGameSprite.setPosition(250, 425);
    exitGameSelectedSprite.setTexture(*ExitGameSelectedTexture);
    exitGameSelectedSprite.setPosition(250, 425);

    return success;
}
