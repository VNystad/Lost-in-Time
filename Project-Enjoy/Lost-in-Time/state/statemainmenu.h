#ifndef STATE_STATEMAINMENU_H
#define STATE_STATEMAINMENU_H

#include "state.h"
#include "../Framework/config.h"
#include "../Interface/highscore.h"

class StateMainMenu : public State
{
public:
    //Functions to load image
    sf::Texture *LoadTexture( std::string path);
    bool loadMedia();

    void GoNext(Machine &machine, sf::RenderWindow& window, SavedObject&, Highscore&);

protected:
    int menuAmount = 0;
    int menu = 1;
    bool mainmenu = false;
    bool success;
    bool keypressed;

    Config config;

    //Pointer to different images
    sf::Texture* BackgroundTexture = nullptr;
    sf::Texture* NewGameTexture = nullptr;
    sf::Texture* NewGameSelectedTexture = nullptr;
    sf::Texture* LoadGameTexture = nullptr;
    sf::Texture* LoadGameSelectedTexture = nullptr;
    sf::Texture* ExitGameTexture = nullptr;
    sf::Texture* ExitGameSelectedTexture = nullptr;
    sf::Texture* HowToPlayTexture = nullptr;
    sf::Texture* HowToPlayPictureTexture = nullptr;
    sf::Texture* HowToPlaySelectedTexture = nullptr;
};


#endif
