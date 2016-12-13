#ifndef LOST_IN_TIME_HIGHSCORE_H
#define LOST_IN_TIME_HIGHSCORE_H

#include <iostream>
#include <map>
#include <fstream>
#include <SFML/Graphics/Text.hpp>

class Highscore
{
public:
    Highscore();

    void SaveToFile();

    sf::Text* SaveNewHighscore(std::string name, int score);
    void LoadHighScore();

protected:
    sf::Font* font = nullptr;
    sf::Text* highscoreText = nullptr;
    std::map <int, std::string> *highscoreMap;
};


#endif //LOST_IN_TIME_HIGHSCORE_H