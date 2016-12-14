#include "highscore.h"

/***********************
 * Highscore constructor
 **********************/
Highscore::Highscore()
{
    font = new sf::Font;
    if(!font->loadFromFile("data/Fonts/Arial/arial.ttf"))
        std::cout << "Could not load font from directory 'data/font.ttf'" << std::endl;
    highscoreText = new sf::Text("hi" , *font);
    highscoreText->setCharacterSize(50);
    highscoreText->setStyle(sf::Text::Regular);
    highscoreText->setColor(sf::Color::White);
    highscoreMap = new std::map<int, std::string>;
    LoadHighScore();
}
/********************************************
 * Saves all highscores from map back to file
 *******************************************/
void Highscore::SaveToFile()
{
    std::ofstream savefile;
    savefile.open("data/highscore.txt");

    for(auto x: *highscoreMap)
    {
        savefile << std::endl << x.second;
        savefile << std::endl << x.first;
    }
    savefile.close();
}
/**
 * Adds highscore or a new players score to map, returns string depending on score and player
 * @param name playername
 * @param score score of the player
 * @return returns a Text with "new" if new player,
 *          returns "high" if new highscore of excisting player
 *          returns empty string if excisting player but no highscore
 */
sf::Text* Highscore::SaveNewHighscore(std::string name, int score)
{
    for(auto x : *highscoreMap)
    {
        if(!x.second.compare(name))
        {
            if(x.first < score)
            {
                highscoreMap->emplace(score, name);
                highscoreMap->erase(x.first);
                highscoreText->setString("high");
                SaveToFile();
            }
            else
                highscoreText->setString("");
            return  highscoreText;
        }
    }

    highscoreMap->emplace(score, name);
    highscoreText->setString("new");
    SaveToFile();
    return highscoreText;
}
/**********************************
 * Loads highscore from file to map
 *********************************/
void Highscore::LoadHighScore()
{
    std::ifstream highscoreFile;
    std::string temp;
    std::string playerName;
    int playerScore;
    highscoreFile.open("data/highscore.txt");

    std::getline(highscoreFile, temp);

    // Read information from file
    while(highscoreFile.is_open())
    {
        if(highscoreFile.eof())
            highscoreFile.close();
        else
        {
            std::getline(highscoreFile, playerName);
            std::getline(highscoreFile, temp);
            //std::cout << temp << std::endl;
            playerScore = std::stoul(temp);
            highscoreMap->emplace(playerScore, playerName);
        }
    }

    //std::cout << "Loaded highscore" << std::endl;
}