#ifndef LOST_IN_TIME_TESTAPP_H
#define LOST_IN_TIME_TESTAPP_H


#include <list>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include "Framework/config.h"
#include "Objects/playerobject.h"
#include "Objects/princessobject.h"
#include "Map/map.h"
#include "Framework/Camera.h"
#include "Enemy/AIEnemies.h"
#include "Framework/Music.h"
#include "state/machine.h"

class TestApp
{
public:
    TestApp(sf::RenderWindow& window, SavedObject);
    bool Tick(Machine& machine, Highscore& highscore);
    void Move(float delta);
    void AIHandler(float delta);

    bool VictoryHandler(Highscore& highscore, int score, float delta);


    bool EscMenu(Machine& machine); // Menu when u press Esc
    bool SaveGame(int selectedSave); // Function under the Esc menu, savegame
    int menuSelected(std::string menu); // Function to choose in menus
    void LoadImages();
    sf::Texture* LoadTexture( std::string path, int &menuAmount); // Function to load in textures
protected:
    bool keyPressed = false;
    bool playerNamed = false;
    bool menuUp = false;

    /****************
     *  Victory stuff
     ****************/
    // princess?
    bool princessSpawn = false;
    sf::Text* victoryText;
    sf::Texture* heart = nullptr;
    sf::Sprite heartSprite;
    int winTime = 0;

    std::string playerName;

    /***********************
     * Variables for EscMenu
     **********************/
    // Text for name
    sf::Text* name;
    // The amount of saves
    int amountOfSaves = 0;
    // The amount of options in EscMenu
    int amountOfEscOptions = 0;

    sf::Texture* save1 = nullptr;
    sf::Texture* save2 = nullptr;
    sf::Texture* save3 = nullptr;

    sf::Texture* selected = nullptr;

    sf::Texture* resumeGame = nullptr;
    sf::Texture* saveGame = nullptr;
    sf::Texture* mainMenu = nullptr;
    sf::Texture* exitGame = nullptr;

    sf::Sprite save1Sprite;
    sf::Sprite save2Sprite;
    sf::Sprite save3Sprite;

    sf::Sprite selectedSprite;

    sf::Sprite resumeGameSprite;
    sf::Sprite saveGameSprite;
    sf::Sprite mainMenuSprite;
    sf::Sprite exitGameSprite;


    /***********************
     * Variables for Background
     **********************/

    sf::Texture* Junglebackground1 = nullptr;
    sf::Texture* Cavebackground1 = nullptr;
    sf::Texture* Treebackground1 = nullptr;
    sf::Texture* Hud = nullptr;

    sf::Sprite Junglebackground1Sprite;
    sf::Sprite Junglebackground6Sprite;
    sf::Sprite Cavebackground1Sprite;
    sf::Sprite Cavebackground2Sprite;
    sf::Sprite Cavebackground3Sprite;
    sf::Sprite Treebackground1Sprite;
    sf::Sprite HudSprite;

    /**********************/


    const int ArraySize = 1000;
    int** collidableArray;

    //Dependensies
    PlayerObject* player;

    PrincessObject* princess;

    std::vector<AIEnemies*>* AIVectorPointer = &AIVector;
    std::vector<AIEnemies*> AIVector;

    Config* config;
    std::list<Object*> objects;
    sf::Clock* clock;
    sf::RenderWindow* window;

    // Stuff for timer
    sf::Clock* timer;
    sf::Text* timerInText;
    sf::Font* font;
    int timerX;
    int timerY;
    int penaltyTime = 0;
    int EscMenuTime = 0;

    sf::View* currentView;
    Camera camera;
    Music* music;
};


#endif