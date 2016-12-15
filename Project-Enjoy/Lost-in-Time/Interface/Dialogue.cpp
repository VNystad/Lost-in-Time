#include "Dialogue.h"


Dialogue::Dialogue()
{
    LoadImages();
}


    /****************
     * Draws Dialogue
     ****************/

/*********************************************************************
* Function for drawing dialogue boxes for when game is in regular mode
* using the function DrawDialogue
@param player: Where the player is located
@param currentView: What view the camera is displaying
@param DialogueDuration: Timer, how long the dialogue should be displayed
@param window: the address of the window

***********************************************************/

void Dialogue::DrawDialogue(PlayerObject* player, sf::RenderWindow& window, sf::View& currentView, sf::Clock &DialogueDuration)
    {

    /****************************************************************
     * Draws this Dialogue if the players X-position is lower than 3500
     ****************************************************************/

        if (DialogueDuration.getElapsedTime().asSeconds() >= 2 && isHuhPrinted == false)
        {
            HuhSprite.setPosition(player->GetPositionX() - 150, player->GetPositionY() - 200);
            window.draw(HuhSprite);
            if (DialogueDuration.getElapsedTime().asSeconds() >= 5)
            {
                    isHuhPrinted = true;
            }
        }

        if (isHuhPrinted == true && DialogueDuration.getElapsedTime().asSeconds() >= 6 && isWhereAmIPrinted == false)
        {
            WhereAmISprite.setPosition(player->GetPositionX() - 150, player->GetPositionY() - 200);
            window.draw(WhereAmISprite);
            if (DialogueDuration.getElapsedTime().asSeconds() >= 9)
            {
                isWhereAmIPrinted = true;
            }
        }

        if (isWhereAmIPrinted == true && DialogueDuration.getElapsedTime().asSeconds() >= 11 && isJesusChristPrinted == false)
        {
            JesusChristSprite.setPosition(player->GetPositionX() - 150, player->GetPositionY() - 200);
            window.draw(JesusChristSprite);
            if (DialogueDuration.getElapsedTime().asSeconds() >= 13)
            {
                isJesusChristPrinted = true;
            }
        }


        if (isJesusChristPrinted == true && DialogueDuration.getElapsedTime().asSeconds() >= 15 && isHelpPrinted == false)
        {
            HelpSprite.setPosition(currentView.getCenter().x + 250, currentView.getCenter().y - 270);
            window.draw(HelpSprite);
            if (DialogueDuration.getElapsedTime().asSeconds() >= 17)
            {
                isHelpPrinted = true;
            }
        }


        if (isHelpPrinted == true && DialogueDuration.getElapsedTime().asSeconds() >= 19 && isWhatWasThatPrinted == false)
        {
             WhatWasThatSprite.setPosition(player->GetPositionX() - 150, player->GetPositionY() - 200);
             window.draw(WhatWasThatSprite);
             if (DialogueDuration.getElapsedTime().asSeconds() >= 21)
             {
                isWhatWasThatPrinted = true;
             }
        }

        if (isWhatWasThatPrinted == true && DialogueDuration.getElapsedTime().asSeconds() >= 23 && isHelpMePrinted == false)
        {
            HelpMeSprite.setPosition(currentView.getCenter().x + 250, currentView.getCenter().y - 270);
            window.draw(HelpMeSprite);
            if (DialogueDuration.getElapsedTime().asSeconds() >= 25)
            {
               isHelpMePrinted = true;
            }
        }

        if (isHelpMePrinted == true && DialogueDuration.getElapsedTime().asSeconds() >= 27 && isHeeeelpPrinted == false)
        {
            HeeeelpSprite.setPosition(currentView.getCenter().x + 250, currentView.getCenter().y - 270);
            window.draw(HeeeelpSprite);
             if (DialogueDuration.getElapsedTime().asSeconds() >= 29)
             {
               isHeeeelpPrinted = true;
             }
         }

        if (isHeeeelpPrinted == true && DialogueDuration.getElapsedTime().asSeconds() >= 31 && isAlwaysWithTheYellingPrinted == false)
        {
            AlwaysWithTheYellingSprite.setPosition(player->GetPositionX() - 150, player->GetPositionY() - 200);
            window.draw(AlwaysWithTheYellingSprite);
            if (DialogueDuration.getElapsedTime().asSeconds() >= 33)
            {
               isAlwaysWithTheYellingPrinted = true;
            }
        }

        if (isAlwaysWithTheYellingPrinted == true && DialogueDuration.getElapsedTime().asSeconds() >= 35 && isAnyonePrinted == false)
        {
            AnyoneSprite.setPosition(4700, 420);
            window.draw(AnyoneSprite);
            if (DialogueDuration.getElapsedTime().asSeconds() >= 37)
            {
               isAnyonePrinted = true;
            }
        }


        if (isAnyonePrinted == true && DialogueDuration.getElapsedTime().asSeconds() >= 39 && isYeahYeahCalmDownPrinted == false)
        {
            YeahYeahCalmDownSprite.setPosition(player->GetPositionX() - 150, player->GetPositionY() - 200);
            window.draw(YeahYeahCalmDownSprite);
            if (DialogueDuration.getElapsedTime().asSeconds() >= 41)
            {
               isYeahYeahCalmDownPrinted = true;
            }
        }


        if (isYeahYeahCalmDownPrinted == true && DialogueDuration.getElapsedTime().asSeconds() >= 43 && isHelp2Printed == false)
        {
            Help2Sprite.setPosition(4700, 420);
            window.draw(Help2Sprite);
            if (DialogueDuration.getElapsedTime().asSeconds() >= 46)
            {
                isHelp2Printed = true;
            }
        }

        if (isHelp2Printed ==true && DialogueDuration.getElapsedTime().asSeconds() >= 49 && isHeeeelp2Printed == false)
        {
            Heeeelp2Sprite.setPosition(4700, 420);
            window.draw(Heeeelp2Sprite);
            if (DialogueDuration.getElapsedTime().asSeconds() >= 52)
            {
                isHeeeelp2Printed = true;
            }
        }

        if (isHeeeelp2Printed == true && DialogueDuration.getElapsedTime().asSeconds() >= 55 && isHelpMe2Printed == false)
        {
            HelpMe2Sprite.setPosition(4700, 420);
            window.draw(HelpMe2Sprite);
            if (DialogueDuration.getElapsedTime().asSeconds() >= 58)
            {
                isHelpMe2Printed = true;
            }
        }

    }



/*********************************************************************
* Function for drawing dialogue boxes for when game is in victory mode
* using the function DrawVictoryDialogue
@param player = Where the player is located
@param princess = Where the princess is located
@param currentView = What view the camera is displaying
@param DialogueDuration = Timer, how long the dialogue should be displayed
@param window = the address of the window

***********************************************************/

void Dialogue::DrawVictoryDialogue(PlayerObject* player, PrincessObject* princess, sf::RenderWindow& window, sf::View& currentView, sf::Clock &DialogueDuration)
{

    if (DialogueDuration.getElapsedTime().asSeconds() >= 1 && isMyHeroPrinted == false)
    {
        MyHeroSprite.setPosition(princess->GetPositionX() - 150, princess->GetPositionY() - 200);
        window.draw(MyHeroSprite);
        if (DialogueDuration.getElapsedTime().asSeconds() >= 5)
        {
            isMyHeroPrinted = true;
        }
    }

    if(isMyHeroPrinted == true && DialogueDuration.getElapsedTime().asSeconds() >= 6 && isHowCouldIEverRepayYouPrinted == false)
    {
        HowCouldIEverRepayYouSprite.setPosition(princess->GetPositionX() - 150, princess->GetPositionY() - 200);
        window.draw(HowCouldIEverRepayYouSprite);
        if(DialogueDuration.getElapsedTime().asSeconds() >= 8)
        {
            isHowCouldIEverRepayYouPrinted = true;
        }
    }
    if(isHowCouldIEverRepayYouPrinted == true && DialogueDuration.getElapsedTime().asSeconds() >= 9 && isCouldYouPleaseShutUpPrinted == false )
    {
        CouldYouPleaseShutUpSprite.setPosition(player->GetPositionX() - 150, player->GetPositionY() - 200);
        window.draw(CouldYouPleaseShutUpSprite);
        if(DialogueDuration.getElapsedTime().asSeconds() >= 11)
        {
            isCouldYouPleaseShutUpPrinted = true;
        }

    }









}

/***********************************
 * Loads texture pointers
 * using the function LoadTexture
 * Placing all textures into sprites
 **********************************/

void Dialogue::LoadImages()
        {

/*****************************************
 * Dialogue for player
 ****************************************/

    Huh = LoadTexture("data/Dialogue/Player/Huh.png");
    Again = LoadTexture("data/Dialogue/Player/Again.png");
    CouldYouPleaseShutUp = LoadTexture("data/Dialogue/Player/CouldYouPleaseShutTheFuckUp.png");
    HowManyTimesCanThisHappen = LoadTexture("data/Dialogue/Player/HowManyTimesCanThisHappen.png");
    JesusChrist = LoadTexture("data/Dialogue/Player/JesusChrist.png");
    WellThatHurt = LoadTexture("data/Dialogue/Player/WellThatHurt.png");
    WhatWasThat = LoadTexture("data/Dialogue/Player/WhatWasThat.png");
    WhereAmI = LoadTexture("data/Dialogue/Player/WhereAmI.png");
    YeahYeahCalmDown = LoadTexture("data/Dialogue/Player/YeahYeahCalmDown.png");
    AlwaysWithTheyelling = LoadTexture("data/Dialogue/Player/AlwaysWithTheYelling.png");


    HuhSprite.setTexture(*Huh);
    HuhSprite.scale(HuhSprite.getScale().x*0.7,HuhSprite.getScale().y*0.7);

    WhereAmISprite.setTexture(*WhereAmI);
    WhereAmISprite.scale(WhereAmISprite.getScale().x*0.7,WhereAmISprite.getScale().y*0.7);

    CouldYouPleaseShutUpSprite.setTexture(*CouldYouPleaseShutUp);
    CouldYouPleaseShutUpSprite.scale( CouldYouPleaseShutUpSprite.getScale().x*0.7, CouldYouPleaseShutUpSprite.getScale().y*0.7);

    HowManyTimesCanThisHappenSprite.setTexture(*HowManyTimesCanThisHappen);
    HowManyTimesCanThisHappenSprite.scale(HowManyTimesCanThisHappenSprite.getScale().x*0.7,HowManyTimesCanThisHappenSprite.getScale().y*0.7);

    JesusChristSprite.setTexture(*JesusChrist);
    JesusChristSprite.scale(JesusChristSprite.getScale().x*0.7,JesusChristSprite.getScale().y*0.7);

    WellThatHurtSprite.setTexture(*WellThatHurt);
    WellThatHurtSprite.scale(WellThatHurtSprite.getScale().x*0.7,WellThatHurtSprite.getScale().y*0.7);

    WhatWasThatSprite.setTexture(*WhatWasThat);
    WhatWasThatSprite.scale(WhatWasThatSprite.getScale().x*0.7,WhatWasThatSprite.getScale().y*0.7);

    YeahYeahCalmDownSprite.setTexture(*YeahYeahCalmDown);
    YeahYeahCalmDownSprite.scale(YeahYeahCalmDownSprite.getScale().x*0.88,YeahYeahCalmDownSprite.getScale().y*0.88);

    AlwaysWithTheYellingSprite.setTexture(*AlwaysWithTheyelling);
    AlwaysWithTheYellingSprite.scale(YeahYeahCalmDownSprite.getScale().x*0.7,YeahYeahCalmDownSprite.getScale().y*0.7);



    /*****************************************
    * Dialogue for princess
     ****************************************/

    Anyone = LoadTexture("data/Dialogue/Princess/Anyone.png");
    Heeeelp = LoadTexture("data/Dialogue/Princess/Heeeelp.png");
    Heeeelp2 = LoadTexture("data/Dialogue/Princess/Heeeelp.png");
    HelloAnyone = LoadTexture("data/Dialogue/Princess/HelloAnyone.png");
    Help = LoadTexture("data/Dialogue/Princess/Help.png");
    Help2 = LoadTexture("data/Dialogue/Princess/Help.png");
    HelpMe = LoadTexture("data/Dialogue/Princess/HelpMe.png");
    HelpMe2 = LoadTexture("data/Dialogue/Princess/HelpMe.png");
    HowCouldIEverRepayYou = LoadTexture("data/Dialogue/Princess/HowCouldIEverRepayYou.png");
    HowDidYouKnowILikeItRough = LoadTexture("data/Dialogue/Princess/HowDidYouKnowILikeItRough.png");
    IveGotHandcuffs = LoadTexture("data/Dialogue/Princess/IgotHandcuffs.png");
    MyHero = LoadTexture("data/Dialogue/Princess/MyHero.png");
    ThankYouForSavingMe = LoadTexture("data/Dialogue/Princess/ThankYouForSavingMe.png");
    WantToGoBackToMyHut = LoadTexture("data/Dialogue/Princess/WantToGoBackToMyHut.png");


    AnyoneSprite.setTexture(*Anyone);
    AnyoneSprite.scale(AnyoneSprite.getScale().x*0.7,AnyoneSprite.getScale().y*0.7);

    HeeeelpSprite.setTexture(*Heeeelp);
    HeeeelpSprite.scale(HeeeelpSprite.getScale().x*0.7,HeeeelpSprite.getScale().y*0.7);

    Heeeelp2Sprite.setTexture(*Heeeelp2);
    Heeeelp2Sprite.scale(Heeeelp2Sprite.getScale().x*0.7,Heeeelp2Sprite.getScale().y*0.7);

    HelloAnyoneSprite.setTexture(*HelloAnyone);
    HelloAnyoneSprite.scale(HelloAnyoneSprite.getScale().x*0.7,HelloAnyoneSprite.getScale().y*0.7);

    HelpSprite.setTexture(*Help);
    HelpSprite.scale(HelpSprite.getScale().x*0.7,HelpSprite.getScale().y*0.7);

    Help2Sprite.setTexture(*Help2);
    Help2Sprite.scale(Help2Sprite.getScale().x*0.7,Help2Sprite.getScale().y*0.7);

    HelpMeSprite.setTexture(*HelpMe);
    HelpMeSprite.scale(HelpMeSprite.getScale().x*0.7,HelpMeSprite.getScale().y*0.7);

    HelpMe2Sprite.setTexture(*HelpMe2);
    HelpMe2Sprite.scale(HelpMe2Sprite.getScale().x*0.7,HelpMe2Sprite.getScale().y*0.7);

    HowCouldIEverRepayYouSprite.setTexture(*HowCouldIEverRepayYou);
    HowCouldIEverRepayYouSprite.scale(HowCouldIEverRepayYouSprite.getScale().x*0.7,HowCouldIEverRepayYouSprite.getScale().y*0.7);

    HowDidYouKnowILikeItRoughSprite.setTexture(*HowDidYouKnowILikeItRough);
    HowDidYouKnowILikeItRoughSprite.scale(HowDidYouKnowILikeItRoughSprite.getScale().x*0.7,HowDidYouKnowILikeItRoughSprite.getScale().y*0.7);

    IveGotHandcuffsSprite.setTexture(*IveGotHandcuffs);
    IveGotHandcuffsSprite.scale(IveGotHandcuffsSprite.getScale().x*0.7,IveGotHandcuffsSprite.getScale().y*0.7);

    MyHeroSprite.setTexture(*MyHero);
    MyHeroSprite.scale(MyHeroSprite.getScale().x*0.7,MyHeroSprite.getScale().y*0.7);

    ThankYouForSavingMeSprite.setTexture(*ThankYouForSavingMe);
    ThankYouForSavingMeSprite.scale(ThankYouForSavingMeSprite.getScale().x*0.7,ThankYouForSavingMeSprite.getScale().y*0.7);

    WantToGoBackToMyHutSprite.setTexture(*WantToGoBackToMyHut);
    WantToGoBackToMyHutSprite.scale(WantToGoBackToMyHutSprite.getScale().x*0.7,WantToGoBackToMyHutSprite.getScale().y*0.7);


    }

/**********************************************
 * Loads image from file into texture
 * @param path: where file is placed
 * @param menuAmount: int counter to easy find
 *          the amount of options on a menu
 *          (ONLY USED FOR ESC & SAVE MENU)
 * @return returns the texture loaded
 *********************************************/

sf::Texture *Dialogue::LoadTexture(std::string path)
{
    //temp texture
    sf::Texture *newTexture = new sf::Texture();
    //newTexture->loadFromFile(path);

    if(!newTexture->loadFromFile(path))
        std::cout << "Could not load image on path: " << path << std::endl;

    return newTexture;
}