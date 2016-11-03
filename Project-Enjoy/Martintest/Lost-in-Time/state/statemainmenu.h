#ifndef STATE_STATEMAINMENU_H
#define STATE_STATEMAINMENU_H

#include "state.h"
#include "../Framework/config.h"

class StateMainMenu : public State
{
public:
    //Functions to load image
    sf::Texture *LoadTexture( std::string path);
    bool loadMedia();

    void GoNext(Machine &machine);

protected:
    int menuAmount = 0;
    int menu = 1;
    bool success;
    bool keypressed;

    Config config;

    //Pointer to different images
    sf::Texture *BackgroundTexture = NULL;
    sf::Texture *NewGameTexture = NULL;
    sf::Texture *NewGameSelectedTexture = NULL;
    sf::Texture *LoadGameTexture = NULL;
    sf::Texture *LoadGameSelectedTexture = NULL;
    sf::Texture *ExitGameTexture = NULL;
    sf::Texture *ExitGameSelectedTexture = NULL;
};


#endif
