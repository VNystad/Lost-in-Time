#ifndef LOST_IN_TIME_LOADGAMESTATE_H
#define LOST_IN_TIME_LOADGAMESTATE_H


#include "state.h"
#include "../Enemy/AIEnemies.h"
#include "../Objects/savedobject.h"
#include "../Interface/highscore.h"

class StateLoadGame : public State
{
public:
    //Functions to load image
    sf::Texture *LoadTexture( std::string path);
    bool loadMedia();

    void LoadGame(int selected, sf::RenderWindow& window, SavedObject&);

    void GoNext(Machine &machine, sf::RenderWindow& window, SavedObject&, Highscore&);



protected:

    // Flag for keypressed
    bool keyPressed = false;
    // Flag for while loop
    bool inLoad = true;

    // Int values to keep on track of amount of elements in menu
    // And what is selected on the menu
    int selected = 1;
    int menuAmount = 0;

    // Textures and sprites for different images for save files
    sf::Texture* save1 = nullptr;
    sf::Texture* save2 = nullptr;
    sf::Texture* save3 = nullptr;
    sf::Texture* save1Selected = nullptr;
    sf::Texture* save2Selected = nullptr;
    sf::Texture* save3Selected = nullptr;

    sf::Sprite* save1Sprite = nullptr;
    sf::Sprite* save2Sprite = nullptr;
    sf::Sprite* save3Sprite = nullptr;
    sf::Sprite* save1SelectedSprite = nullptr;
    sf::Sprite* save2SelectedSprite = nullptr;
    sf::Sprite* save3SelectedSprite = nullptr;

};


#endif
