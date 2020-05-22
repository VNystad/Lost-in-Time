#ifndef STATE_STATEMAINMENU_H
#define STATE_STATEMAINMENU_H

#include "state.h"
#include "../Framework/config.h"
#include "../Framework/Sounds.h"
#include "../Interface/highscore.h"

class StateMainMenu : public State
{
public:
    //Functions to load image
    sf::Texture *LoadTexture( std::string path);
    bool loadMedia();

    void ShowHighscore(sf::RenderWindow& window, Highscore& highscore);
    void ShowHowToPlay(sf::RenderWindow& window);

    void GoNext(Machine &machine, sf::RenderWindow& window, SavedObject&, Highscore&);

protected:
    int menuAmount = 0;
    int menu = 1;

    std::map<int, std::string>* highscoreMap;

    bool keypressed;

    Config config;

    sf::Font* font;

    //Pointer to different images
    sf::Texture* BackgroundTexture = nullptr;
    sf::Texture* NewGameTexture = nullptr;
    sf::Texture* NewGameSelectedTexture = nullptr;
    sf::Texture* LoadGameTexture = nullptr;
    sf::Texture* LoadGameSelectedTexture = nullptr;
    sf::Texture* HighscoreTexture = nullptr;
    sf::Texture* HighscoreSelectedTexture = nullptr;
    sf::Texture* HowToPlayPictureTexture = nullptr;
    sf::Texture* HowToPlaySelectedTexture = nullptr;
    sf::Texture* ExitGameTexture = nullptr;
    sf::Texture* ExitGameSelectedTexture = nullptr;
    sf::Texture* HowToPlayTexture = nullptr;

    sf::Sprite backgroundSprite;
    sf::Sprite NewGameSprite;
    sf::Sprite NewGameSelectedSprite;
    sf::Sprite LoadGameSprite;
    sf::Sprite LoadGameSelectedSprite;
    sf::Sprite HighscoreSprite;
    sf::Sprite HighscoreSelectedSprite;
    sf::Sprite HowToPlaySprite;
    sf::Sprite HowToPlaySelectedSprite;
    sf::Sprite HowToPlayPictureSprite;
    sf::Sprite exitGameSprite;
    sf::Sprite exitGameSelectedSprite;

    Sounds* sound;
};


#endif
