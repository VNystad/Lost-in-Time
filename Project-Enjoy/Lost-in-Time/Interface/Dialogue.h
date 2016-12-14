#ifndef LOST_IN_TIME_DIALOGUE_H
#define LOST_IN_TIME_DIALOGUE_H

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include "../Objects/playerobject.h"
#include "../Objects/princessobject.h"



class Dialogue {


public:

    Dialogue();

    void DrawDialogue(PlayerObject* player, sf::RenderWindow& window, sf::View& currentView, sf::Clock &DialogueDuration);

    void DrawVictoryDialogue(PlayerObject* player, PrincessObject* princess, sf::RenderWindow& window, sf::View& currentView, sf::Clock &DialogueDuration);

    void LoadImages();

    sf::Texture* LoadTexture(std::string path); // Function to load in textures




protected:




/**********************
 *  Bools for dialogue
 *********************/

//player Dialogue

    bool isHuhPrinted = false;
    bool isAgainPrinted = false;
    bool isCouldYouPleaseShutUpPrinted = false;
    bool isHowManyTimesCanThishappenPrinted = false;
    bool isJesusChristPrinted = false;
    bool isWellThatHurtPrinted = false;
    bool isWhatWasThatPrinted = false;
    bool isWhereAmIPrinted = false;
    bool isYeahYeahCalmDownPrinted = false;
    bool isAlwaysWithTheYellingPrinted = false;

//Princess Dialogue

    bool isAnyonePrinted = false;
    bool isHeeeelpPrinted = false;
    bool isHeeeelp2Printed = false;
    bool isHelloAnyonePrinted = false;
    bool isHelpPrinted = false;
    bool isHelp2Printed = false;
    bool isHelpMePrinted = false;
    bool isHelpMe2Printed = false;
    bool isHowCouldIEverRepayYouPrinted = false;
    bool isHowDidYouKnowILikeItRoughPrinted = false;
    bool isIveGotHandcuffsPrinted = false;
    bool isMyHeroPrinted = false;
    bool isThankYouForSavingMePrinted = false;
    bool isWhantToGoBackToMyHutPrinted = false;

    /********************************
    * Variables for Player dialogue
    *******************************/

    //Textures
    sf::Texture* Huh = nullptr;
    sf::Texture* Again = nullptr;
    sf::Texture* CouldYouPleaseShutUp = nullptr;
    sf::Texture* HowManyTimesCanThisHappen = nullptr;
    sf::Texture* JesusChrist = nullptr;
    sf::Texture* WellThatHurt = nullptr;
    sf::Texture* WhatWasThat = nullptr;
    sf::Texture* WhereAmI = nullptr;
    sf::Texture* YeahYeahCalmDown = nullptr;
    sf::Texture* AlwaysWithTheyelling = nullptr;

    //Sprites
    sf::Sprite HuhSprite;
    sf::Sprite AgainSprite;
    sf::Sprite CouldYouPleaseShutUpSprite;
    sf::Sprite HowManyTimesCanThisHappenSprite;
    sf::Sprite JesusChristSprite;
    sf::Sprite WellThatHurtSprite;
    sf::Sprite WhatWasThatSprite;
    sf::Sprite WhereAmISprite;
    sf::Sprite YeahYeahCalmDownSprite;
    sf::Sprite AlwaysWithTheYellingSprite;


    /********************************
     * Variables for Princess dialogue
    *********************************/

    //Textures
    sf::Texture* Anyone = nullptr;
    sf::Texture* Heeeelp = nullptr;
    sf::Texture* Heeeelp2 = nullptr;
    sf::Texture* HelloAnyone = nullptr;
    sf::Texture* Help = nullptr;
    sf::Texture* Help2 = nullptr;
    sf::Texture* HelpMe = nullptr;
    sf::Texture* HelpMe2 = nullptr;
    sf::Texture* HowCouldIEverRepayYou = nullptr;
    sf::Texture* HowDidYouKnowILikeItRough = nullptr;
    sf::Texture* IveGotHandcuffs = nullptr;
    sf::Texture* MyHero = nullptr;
    sf::Texture* ThankYouForSavingMe = nullptr;
    sf::Texture* WantToGoBackToMyHut = nullptr;

    //Sprites
    sf::Sprite AnyoneSprite;
    sf::Sprite HeeeelpSprite;
    sf::Sprite Heeeelp2Sprite;
    sf::Sprite HelloAnyoneSprite;
    sf::Sprite HelpSprite;
    sf::Sprite Help2Sprite;
    sf::Sprite HelpMeSprite;
    sf::Sprite HelpMe2Sprite;
    sf::Sprite HowCouldIEverRepayYouSprite;
    sf::Sprite HowDidYouKnowILikeItRoughSprite;
    sf::Sprite IveGotHandcuffsSprite;
    sf::Sprite MyHeroSprite;
    sf::Sprite ThankYouForSavingMeSprite;
    sf::Sprite WantToGoBackToMyHutSprite;

    /**********************/



};


#endif
