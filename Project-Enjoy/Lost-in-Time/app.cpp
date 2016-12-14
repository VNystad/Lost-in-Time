#include <iostream>
#include <fstream>
#include "app.h"
#include "Framework/physics.h"

TestApp::TestApp(sf::RenderWindow& window, SavedObject so)
{

    this->config = config;
    this->window = &window;

    /*****************
     * Load in images
     ****************/
    LoadImages();

    /********************
     * Load up music
     *******************/
    music = new Music();
    music->music.setLoop(true);
    music->music.setVolume(20);

    /****************************************************************************
     *                            LOADED FROM SAVE
     ***************************************************************************/
    if(so.LoadFromSave())
    {
        /******************************
         * If savename equals EmptySave
         * Go back to main menu
         *****************************/
        if(!so.GetPlayerName().compare("EmptySave"))
        {
            emptySave = true;
        }
        /********************|
         * Create the player
         *******************/
        player = new PlayerObject(so.GetPlayerX(), so.GetPlayerY(), &window);
        player->health.SetActualLifePoints(so.GetPlayerHP());
        playerName = so.GetPlayerName();
        playerNamed = true;
        timeFromLoad = so.GetTimeElapsed();

        /***********************
         *  Create the princess
         **********************/
        princess = new PrincessObject(4862, 558, 50, &window);

        /***********************************
         * Creating AI
         * Using vector to keep track on AIs
         **********************************/
        for(std::vector<AIEnemies*>::iterator it = so.GetAIVectorPointer()->begin(); it != so.GetAIVectorPointer()->end(); ++it)
        {
            int x = (*it)->GetOriginalX();
            int y = (*it)->GetOriginalY();
            int patrol = (*it)->GetOriginalX() - (*it)->GetPatrolLeft();
            bool boss = (*it)->GetBoss();
            AIVectorPointer->push_back(new AIEnemies(x, y, patrol, boss, &window));
        }

        music->playMusic("/Jungle Theme 2.ogg");

    }
    /****************************************************************************
     *                             NEW GAME
     ***************************************************************************/
    else
    {
        /********************|
         * Create the player
         *******************/
        // 160, 398
        //4450, 558
        player = new PlayerObject(4450, 558, &window);

        /***********************
         *  Create the princess
         **********************/
        princess = new PrincessObject(4862, 550, 50, &window);

        /***********************************
         * Creating AI
         * Using vector to keep track on AIs
         **********************************/
        AIVectorPointer->push_back(new AIEnemies(4410, 400, 460, true, &window));
        AIVectorPointer->push_back(new AIEnemies(354, 1230, 200, false, &window));
        AIVectorPointer->push_back(new AIEnemies(1950, 1220, 150, false, &window));
        AIVectorPointer->push_back(new AIEnemies(2340, 250, 260, false, &window));
        //AIVectorPointer->push_back(new AIEnemies(Start X, Start Y, Patrol Each Way From Start, IsBoss?, *config, &window));
        AIVectorPointer->push_back(new AIEnemies(1530, 510, 400, false, &window));
        AIVectorPointer->push_back(new AIEnemies(4562, 878, 10, false, &window));
        AIVectorPointer->push_back(new AIEnemies(4917, 1134, 2, false, &window));
        AIVectorPointer->push_back(new AIEnemies(4157, 1358, 0, false, &window));

    }

    /*************************************************
     * Making 2D array for collidable tiles
     ************************************************/
    collidableArray = new int*[ArraySize];
    collidableArray[0] = new int[ArraySize * ArraySize];
    for (int i = 1; i < ArraySize; i++)
        collidableArray[i] = collidableArray[i - 1] + ArraySize;

    /*************************************************
     * Load map information from JSON into object list
     ************************************************/
    if (!Map::load("data/map.json", objects, collidableArray))
        std::cout << "Failed to load map data." << std::endl << std::endl;

    /*****************************************
     * Set camera position in middle of screen
     ****************************************/
    sf::View view = window.getDefaultView();
    view.setSize(view.getSize().x, view.getSize().y);
    view.setCenter(view.getCenter().x, view.getCenter().y);
    window.setView(view);

    /********************
        * Create the clock
        * Used to find delta
        *******************/
    clock = new sf::Clock;
    clock->restart();

    //TEST
    currentView = new sf::View;


    /***********************************
     * Creating Timer and text for timer
     **********************************/
    font = new sf::Font;
    if(!font->loadFromFile("data/Fonts/Arial/arial.ttf"))
        std::cout << "Could not load font from directory 'data/font.ttf'" << std::endl;
    timer = new sf::Clock();
    timerInText = new sf::Text("hi", *font);
    timerInText->setCharacterSize(20);
    timerInText->setStyle(sf::Text::Regular);
    timerInText->setColor(sf::Color::Black);
    victoryText = new sf::Text("Score: ", *font);
    victoryText->setCharacterSize(50);
    victoryText->setStyle(sf::Text::Regular);
    victoryText->setColor(sf::Color::Red);
    secretText = new sf::Text("Holyshit", *font);
    secretText->setCharacterSize(70);
    secretText->setStyle(sf::Text::Underlined);
    secretText->setColor(sf::Color::Red);

    DialogueDuration = new sf::Clock;
    DialogueDuration->restart();
    dialogue.LoadImages();

}

bool TestApp::Tick(Machine& machine, Highscore& highscore)
{
    /***********************
     * Lets player type name
     **********************/
    while(!playerNamed)
    {
        keyPressed = true;
        sf::Event event;
        std::string nameString;
        window->clear(sf::Color::Black);
        name = new sf::Text("Please type in name", *font);
        name->setCharacterSize(50);
        name->setStyle(sf::Text::Regular);
        name->setColor(sf::Color::White);
        name->setPosition(250, 150);
        window->draw(*name);
        window->display();
        while(1)
        {
            if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
                keyPressed = false;

            while(window->pollEvent(event))
            {
                if(event.type == sf::Event::TextEntered)
                {
                    if(event.text.unicode < 123 && event.text.unicode >47 )
                    {
                        nameString += static_cast<char>(event.text.unicode);
                        name->setString(nameString);
                    }
                }
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && !keyPressed)
            {
                nameString = nameString.substr(0,nameString.size()-1);
                keyPressed = true;
                name->setString(nameString);
            }
            window->draw(*name);
            window->display();
            window->clear(sf::Color::Black);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !keyPressed)
            {
                playerName = nameString;
                playerNamed = true;
                break;
            }
        }
        clock->restart();
        timer->restart();
        music->playMusic("/Jungle Theme 2.ogg");
    }

    sf::Event event;
    float delta = clock->restart().asSeconds();

    /************************
     * Gets time elapsed and
     * place it in text form
     ***********************/
    if(winTime > 9)
        timerX = currentView->getCenter().x + 157;
    else if(winTime > 99)
        timerX = currentView->getCenter().x + 143;
    else
        timerX = currentView->getCenter().x + 163;
    timerY = currentView->getCenter().y - 229;
    winTime = timer->getElapsedTime().asSeconds() + timeFromLoad+ penaltyTime - EscMenuTime;
    std::string tempForTime = std::to_string(winTime);
    timerInText->setString(tempForTime);
    timerInText->setPosition(timerX, timerY);





    /*********************
     * CHECK IF PLAYER WON
     ********************/
    if((princessSpawn) &&((princess->GetPositionX() - player->GetPositionX() < 50 && princess->GetPositionX() - player->GetPositionX() > -50) &&
       (princess->GetPositionY() - player->GetPositionY() <  50 && princess->GetPositionY() - player->GetPositionY() > -50)))
    {
        VictoryHandler(highscore, delta);

        sf::View mainMenuView = window->getDefaultView();
        mainMenuView.setCenter(512, 290);
        *currentView = mainMenuView;
        window->setView(mainMenuView);
        music->music.stop();
        machine.SetState(Machine::StateId::MAINMENU);
        return false;
    }


    // Get events from OS
    while (window->pollEvent(event))
    {
        // Close the window if the user clicks the x button
        if (event.type == sf::Event::Closed)
        {
            delete[] collidableArray[0];
            delete[] collidableArray;
            music->music.stop();
            window->close();
            machine.SetRunning(false);
        }
    }

    /*****************************************************************
     *        KEYBOARD EVENTS ( but not for physical player actions )
     ****************************************************************/

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        int tempTime = timer->getElapsedTime().asSeconds();
        if(!EscMenu(machine))
        {
            sf::View mainMenuView = window->getDefaultView();
            mainMenuView.setCenter(512, 290);
            *currentView = mainMenuView;
            window->setView(mainMenuView);
            music->music.stop();
            machine.SetState(Machine::StateId::MAINMENU);
            return false;
        }

        EscMenuTime = EscMenuTime + timer->getElapsedTime().asSeconds() - tempTime;
        clock->restart();
    }
    /*************
    * KILL ALL AI
    ************/
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
    {
        int count = AIVectorPointer->size();
        while(count != 0)
        {
            AIVectorPointer->at(count-1)->Death();
            count--;
        }
        while(sf::Keyboard::isKeyPressed(sf::Keyboard::K));
    }

        // For testing only, prints out player position
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        std::cout << player->GetPositionX() << " " << player->GetPositionY() << std::endl;

        // When player presses G, player character is damaged. For testing purposes
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && player->health.GetActualLifePoints() > 0)
        player->health.Hit(player->health.GetOriginalLifePoints());

        /*
        // When player presses H, player character is healed. For testing purposes
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && player->health.GetActualLifePoints() < 100)
        player->health.Healed(5);
         */

        // If player press M, mute music
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
    {
        music->music.pause();
    }

    /******************************************************
     * If player hits the bottom of map,
     * player lifepoints = 0, player death function called
     *****************************************************/
    if (player->GetPositionY() >= 1870)
    {
        penaltyTime = penaltyTime + 20;
        player->health.DeathHandle();
        player->PlayerDead();
        timer->restart();
    }

    /*****************
     * if player dead
     ****************/
    if (player->health.Dead())
    {
        penaltyTime = penaltyTime + 20;
        player->health.DeathHandle();
        player->PlayerDead();
        timer->restart();
    }

    // Player player animation
    player->PlayerAnimation(delta);

    /*************************
     * if princess spawned
     * play princess animation
     ************************/
    if(princessSpawn)
    {
        princess->PrincessAnimation(delta);
        princess->SetActivated(true);
    }


    /***************************
     * Handles player movements
     **************************/
    Move(delta);

    /********************
     * POSITION HEALTHBAR
     *******************/
    player->health.SetPosition(currentView->getCenter().x - 70, currentView->getCenter().y - 231);
    HudSprite.setPosition(currentView->getCenter().x - 119, currentView->getCenter().y - 268);

    /***********************
     * Clearing old window
     * Draws background images
     **********************/
    window->clear(sf::Color::Black);
    window->draw(Junglebackground1Sprite);
    window->draw(Cavebackground1Sprite);
    window->draw(Cavebackground2Sprite);
    window->draw(Cavebackground3Sprite);
    window->draw(Treebackground1Sprite);


    /***************
     * Draw the map
     * ( each tile )
     **************/
    for (Object *object : objects)
    {
        //object->process(deltaTime);
        object->draw(*window);
    }

    // Draw player
    player->DrawMe();

    /*********************
     * if princess spawned
     * handle movements
     * draw her
     ********************/
    if(princessSpawn == true)
    {
        // checks if player is nearby? if so handle it
        princess->PrincessAI(princess, player);
        Physics::PrincessMovement(princess, collidableArray, delta);
        Physics::PrincessGravity(princess, collidableArray, delta);
        princess->DrawMe();
    }
    /***********************
     * Draws HUD sprite
     **********************/
    window->draw(HudSprite);
    player->health.DrawMe(*window);

    /****************
     * Draws Dialogue
    ****************/

    dialogue.DrawDialogue(player,*window,*currentView, *DialogueDuration);


    AIHandler(delta);
    window->draw(*timerInText);

    // Update health before displaying it ( Will not be in use in this version )
    // p->health.UpdateHealth();


    window->display();

    /*****************************************
     * Set camera to follow player position
     ****************************************/

    if (player->GetPositionX() >= 512)
    {
        if (player->GetPositionY() <= 1290)
        {
            sf::View view2 = window->getDefaultView();
            view2.setCenter(player->GetPositionX(), player->GetPositionY());
            *currentView = view2;
            window->setView(view2);

            // Positions background movement
            Junglebackground1Sprite.setPosition((player->GetPositionX()*1.5/8)-195,-300);
            Cavebackground2Sprite.setPosition((player->GetPositionX()*1.5/8)-195,600);
        }

        if (player->GetPositionX() >= 5238)
        {
            if (player->GetPositionY() <= 1290) {
                sf::View view5 = window->getDefaultView();
                view5.setCenter(5238, player->GetPositionY());
                *currentView = view5;
                window->setView(view5);
            }
        }
        else if(player->GetPositionY() >= 1290)
        {
            sf::View view2 = window->getDefaultView();
            view2.setCenter(player->GetPositionX(), 1290);
            *currentView = view2;
            window->setView(view2);

            // Positions background movement
            Cavebackground2Sprite.setPosition((player->GetPositionX()*1.5/8)-195,600);
            Junglebackground6Sprite.setPosition(player->GetPositionX()*1.5/8,200);
        }
    }
    else if (player->GetPositionX() <=  512)
    {
        if (player->GetPositionY() <= 1290)
        {
            sf::View view3 = window->getDefaultView();
            view3.setCenter(512, player->GetPositionY());
            *currentView = view3;
            window->setView(view3);

            // Positions background movement
            Junglebackground1Sprite.setPosition(-100,-300);
            Cavebackground2Sprite.setPosition(-100,600);

        }
        else if (player->GetPositionY() >= 1290)
        {
            sf::View view3 = window->getDefaultView();
            view3.setCenter(512, 1290);
            *currentView = view3;
            window->setView(view3);

            // Positions background movement
            Cavebackground2Sprite.setPosition(-100,600);
        }
    }

    return true;
}
/*****************************************************
 * This function will make the object able
 * to move and fall,
 * with correlation to any hinderings such as gravity.
 * The delta| float is there for smoothness
 ****************************************************/
void TestApp::Move(float delta)
{
    Physics::Movement(player, collidableArray, delta);
    Physics::Gravity(player, collidableArray, delta);
    if(player->health.GetActualLifePoints() > player->health.GetOriginalLifePoints())
    {
        player->health.SetOriginalLifePoints(100);
        player->health.SetActualLifePoints(100);
        player->health.SetVisibleLifePoints(100);
    }
}

/**
 * AIHandler handles all the AI, and sends each of them
 * through the same process as the player(animation, drawing, physics
 * and AI ofcourse).
 * @param delta
 */
void TestApp::AIHandler(float delta)
{
    for(unsigned int i = 0; i < AIVector.size(); i++)
    {
        /* If AI hits the bottom of map,
        * the AI's lifepoint is reduced to 0 and AI death function is called */
        if (AIVectorPointer->at(i)->GetPositionY() >= 1860)
        {
            AIVectorPointer->at(i)->health.Hit(AIVectorPointer->at(i)->health.GetOriginalLifePoints());
            AIVectorPointer->at(i)->health.DeathHandle();
            AIVectorPointer->erase(AIVectorPointer->begin() + i);
        }
        //Meant for fixing invincible AI bug, but Boss get Invincible with this code.
        /*
        if(AIVectorPointer->at(i)->health.GetActualLifePoints() > 2*(AIVectorPointer->at(i)->health.GetOriginalLifePoints()))
        {

            if(AIVectorPointer->at(i)->GetBoss())
            {
                AIVectorPointer->at(i)->health.SetOriginalLifePoints(1000);
                AIVectorPointer->at(i)->health.SetActualLifePoints(1000);
                AIVectorPointer->at(i)->health.SetVisibleLifePoints(1000);
            }

            else if(AIVectorPointer->at(i)->GetMiniBoss())
            {
                AIVectorPointer->at(i)->health.SetOriginalLifePoints(300);
                AIVectorPointer->at(i)->health.SetActualLifePoints(300);
                AIVectorPointer->at(i)->health.SetVisibleLifePoints(300);
            }
            else
            {
                AIVectorPointer->at(i)->health.SetOriginalLifePoints(100);
                AIVectorPointer->at(i)->health.SetActualLifePoints(100);
                AIVectorPointer->at(i)->health.SetVisibleLifePoints(100);
            }
        }
         */

        if (AIVectorPointer->at(i)->health.GetActualLifePoints() <= 0)//Dead())
        {
            if(AIVectorPointer->at(i)->GetBoss())
                princessSpawn = true;
            AIVectorPointer->at(i)->health.DeathHandle();
            AIVectorPointer->erase(AIVectorPointer->begin() + i);
        }
        else
        {
            if(AIVectorPointer->at(i)->GetBoss())
                AIVectorPointer->at(i)->AnimationBoss(delta);
            else if(AIVectorPointer->at(i)->GetMiniBoss())
                AIVectorPointer->at(i)->AnimationAIMiniBoss(delta);
            else
                AIVectorPointer->at(i)->AnimationAI(delta);
            AIVectorPointer->at(i)->DrawMe();
            if(AIVectorPointer->at(i)->GetBoss())
                AIVectorPointer->at(i)->MonkeyAI2(AIVectorPointer->at(i), player);
            else
                AIVectorPointer->at(i)->MonkeyAI1(AIVectorPointer->at(i), player);
            Physics::AIMovement(AIVectorPointer->at(i), player, AIVectorPointer, i, collidableArray, delta);
            Physics::AIGravity(AIVectorPointer->at(i), collidableArray, delta);
        }
    }
}
/*****************************************************************
 * What happens when player wins the level (game for now)
 * @param highscore adress of highscore so we can save new
 * @param score: score of player
 * @param delta: to make thing go with same speed on all computers
 * @return true: go to next lvl as a nice man (not implemented)
 *          false: go to next lvl as an evil man (not implemented
 ****************************************************************/
bool TestApp::VictoryHandler(Highscore& highscore, float delta)
{
    if(true)
    {
        music->music.stop();
        window->clear(sf::Color::Black);
        window->draw(Treebackground1Sprite);
        // Process and render each object
        for (Object *object : objects)
        {
            //object->process(deltaTime);
            object->draw(*window);
        }
        sf::View victoryView = window->getDefaultView();

        sf::Clock end;
        victoryView.setCenter(player->GetPositionX() - 200, player->GetPositionY());
        *currentView = victoryView;
        window->setView(*currentView);

        player->SetMoveSpeedL(0);
        player->SetMoveSpeedR(0);
        player->SetFallSpeed(0);
        player->SetJumpSpeed(0);

        int score = 1000 / winTime;

        /*************************************
         * Handle score
         * If player got new highscore
         * if new player
         * or not new player no new highscore
         ************************************/
        victoryText = highscore.SaveNewHighscore(playerName, score);
        std::string temp = victoryText->getString();
        std::string tempForScore = std::to_string(score);
        if(!temp.compare("high"))
            victoryText->setString(victoryText->getString() + " New score: " + tempForScore);
        else if(!temp.compare("new"))
            victoryText->setString("Welcome " + playerName + "! Score: " + tempForScore);
        else
            victoryText->setString("Score: " + tempForScore);


        /********************************************
         * Position victory texts that pops up at end
         *******************************************/
        victoryText->setPosition(player->GetPositionX() - 500, player->GetPositionY() - 200);
        secretText->setPosition(player->GetPositionX() - 600, player->GetPositionY()- 100);

        sf::Vector2f scale = heartSprite.getScale();

        // Count to end the game
        int count = 0;

        // Draw player and princess
        player->DrawMe();
        princess->DrawMe();

        window->display();
        if(1)
        {
            // True love never ends when finally found the perfect girl
            bool truelove = true;
            bool roughLove = false;
            // Victory speach
            //Making character stand still
            end.restart();
            int slapped = 0;
            DialogueDuration = new sf::Clock;
            DialogueDuration->restart();
            princess->SetActivated(false);
            while (truelove)
            {
                /********************************************
                 * Secret attack ( for now )
                 * If player hits princess
                 * true love SHOULD end
                 * rough love is on
                 * Should activate "evil" player for next lvl
                 *******************************************/
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && slapped <= 5)
                {
                    while(sf::Keyboard::isKeyPressed(sf::Keyboard::A));
                    slapped += 1;
                    roughLove = true;
                    princess->PrincessSoundHurt();
                    score += 1000/end.getElapsedTime().asSeconds();
                    tempForScore = std::to_string(score);
                    victoryText->setString("Score: " + tempForScore);
                    secretText->setString("OMG \n you just slapped the Princess! \n You earn additional points!");
                }

                if(princess->GetPositionX() < player->GetPositionX())
                {
                    player->PlayerCutsceneAnimationLeft(delta);
                    princess->PrincessCutsceneAnimationRight(delta);
                }
                else
                {
                    player->PlayerCutsceneAnimationRight(delta);
                    princess->PrincessCutsceneAnimationLeft(delta);
                }
                if(end.getElapsedTime().asSeconds() >= 20)
                {
                    if(roughLove)
                        highscore.SaveNewHighscore(playerName, score);
                    return true;
                }

                window->clear(sf::Color::Black);
                window->draw(Treebackground1Sprite);
                // Process and render each object
                for (Object *object : objects)
                {
                    //object->process(deltaTime);
                    object->draw(*window);
                }
                if(roughLove)
                    window->draw(*secretText);
                player->DrawMe();
                princess->DrawMe();
                dialogue.DrawVictoryDialogue(player,princess,*window,*currentView, *DialogueDuration);
                window->draw(*victoryText);
                window->display();
            }
        }
    }
}
/**************************************************
 * Menu for pressing Esc
 * Options:
 * ResumeGame: Resumes the game
 * SaveGame: Opens new menu with saves
 * MainMenu: Returns to mainmenu
 * ExitGame: Exits the game
 * @param machine so we can handle the machine
 *          if you go back to mainmenu og exit game
 * @return true if to continue playing
 *          false if to quit
 ************************************************/
bool TestApp::EscMenu(Machine& machine)
{
    music->music.pause();

    int selected = menuSelected("EscMenu");

    // Resume game
    if(selected == 1)
    {
        music->music.play();
        return true;
    }

        // Save game
    else if(selected == 2)
    {
        selected = menuSelected("SaveGameMenu");
        SaveGame(selected);
    }
    // Back to mainmenu
    else if(selected == 3)
    {
        music->music.stop();
        return false;
    }

        // Exit game
    else if(selected == 4)
    {
        music->music.stop();
        delete[] collidableArray[0];
        delete[] collidableArray;
        window->close();
        machine.SetRunning(false);
        exit(0);
    }
    clock->restart();
    music->music.play();
    return true;
}

/***********************************************
 * Save Game function
 * @param selectedSave:
 *      Selected save from menuSelected function
 * @return true if it saved
 *          false if something went wrong (not implemented)
 **********************************************/
bool TestApp::SaveGame(int selectedSave)
{
    std::ofstream savefile;
    if(selectedSave == 1)
        savefile.open("SaveFiles/save1.txt");
    else if(selectedSave == 2)
        savefile.open("SaveFiles/save2.txt");
    else if(selectedSave == 3)
        savefile.open("SaveFiles/save3.txt");

    savefile << playerName << std::endl;
    savefile << player->health.GetActualLifePoints() << std::endl;
    savefile << player->GetPositionX() << std::endl;
    savefile << player->GetPositionY() << std::endl;
    savefile << winTime;

    for(std::vector<AIEnemies*>::iterator it = AIVectorPointer->begin(); it != AIVectorPointer->end(); ++it)
    {
        savefile << std::endl << (*it)->GetOriginalX();
        savefile << std::endl << (*it)->GetOriginalY();
        savefile << std::endl << (*it)->GetOriginalX() - (*it)->GetPatrolLeft();
        bool boss = (*it)->GetBoss();
        savefile << std::endl << (*it)->GetBoss();
    }
    savefile.close();
    return true;
}

/************************************************************
 * Universal(almost) function used to choose options in menus
 * @param menu: the menu you want to use function for
 * @return returns the choice player chose
 ***********************************************************/
int TestApp::menuSelected(std::string menu)
{
    // Go until Return is not pressed, to prevent program going through several "Menuselected" functions on 1 return press
    while(sf::Keyboard::isKeyPressed(sf::Keyboard::Return));
    int amountOfChoices = 0;
    int choice = 1;
    int MenuPositionX = currentView->getCenter().x -250;
    int MenuPositionY = currentView->getCenter().y -230;
    bool save = false;

    while(1){
        if(!menu.compare("EscMenu"))
        {
            resumeGameSprite.setPosition(MenuPositionX, MenuPositionY);
            resumeGameSelectedSprite.setPosition(MenuPositionX, MenuPositionY);
            saveGameSprite.setPosition(MenuPositionX, MenuPositionY + 100);
            saveGameSelectedSprite.setPosition(MenuPositionX, MenuPositionY + 100);
            mainMenuSprite.setPosition(MenuPositionX, MenuPositionY + 200);
            mainMenuSelectedSprite.setPosition(MenuPositionX, MenuPositionY + 200);
            exitGameSprite.setPosition(MenuPositionX, MenuPositionY + 300);
            exitGameSelectedSprite.setPosition(MenuPositionX, MenuPositionY + 300);
            window->clear(sf::Color::Black);
            // Load images for esc menu
            window->draw(resumeGameSprite);
            window->draw(saveGameSprite);
            window->draw(mainMenuSprite);
            window->draw(exitGameSprite);
            amountOfChoices = amountOfEscOptions;
        }

        else if(!menu.compare("SaveGameMenu")) // If menu equals "SaveGameMenu";
        {
            save = true;
            window->clear(sf::Color::Black);
            save1Sprite.setPosition(MenuPositionX, MenuPositionY);
            save1SelectedSprite.setPosition(MenuPositionX, MenuPositionY);
            save2Sprite.setPosition(MenuPositionX, MenuPositionY + 100);
            save2SelectedSprite.setPosition(MenuPositionX, MenuPositionY + 100);
            save3Sprite.setPosition(MenuPositionX, MenuPositionY + 200);
            save3SelectedSprite.setPosition(MenuPositionX, MenuPositionY + 200);
            // Load images for savegame menu
            window->draw(save1Sprite);
            window->draw(save2Sprite);
            window->draw(save3Sprite);
            amountOfChoices = amountOfSaves;
        }

        if(save)
        {
            if(choice == 1)
                window->draw(save1SelectedSprite);
            else if(choice == 2)
                window->draw(save2SelectedSprite);
            else if(choice == 3)
                window->draw(save3SelectedSprite);
        }
        else
        {
            if(choice == 1)
            {
                window->draw(resumeGameSelectedSprite);
            }

            else if(choice == 2)
            {
                window->draw(saveGameSelectedSprite);
            }
            else if(choice == 3)
            {
                window->draw(mainMenuSelectedSprite);
            }
            else if(choice == 4)
            {
                window->draw(exitGameSelectedSprite);
            }
        }
        window->display();
        if(!keyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            choice++;
            if (choice > amountOfChoices)
                choice = 1;
            keyPressed = true;
        }
        else if(!keyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            choice--;
            if (choice <= 0)
                choice = amountOfChoices;
            keyPressed = true;
        }
        else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            keyPressed = false;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            return choice;



    }
}

/***********************************
 * Loads texture pointers
 * using the function LoadTexture
 * Placing all textures into sprites
 **********************************/
void TestApp::LoadImages()
{
    int nothing;
    heart = LoadTexture("data/victory/heart.png",nothing);

    save1 = LoadTexture("data/loadgame/Save1.png", amountOfSaves);
    save2 = LoadTexture("data/loadgame/Save2.png", amountOfSaves);
    save3 = LoadTexture("data/loadgame/Save3.png", amountOfSaves);
    save1Selected = LoadTexture("data/loadgame/Save1Selected.png", nothing);
    save2Selected = LoadTexture("data/loadgame/Save2Selected.png", nothing);
    save3Selected = LoadTexture("data/loadgame/Save3Selected.png", nothing);

    resumeGame = LoadTexture("data/EscMenu/ResumeGame.png", amountOfEscOptions);
    resumeGameSelected = LoadTexture("data/EscMenu/ResumeGameSelected.png", nothing);
    mainMenu = LoadTexture("data/EscMenu/mainmenu.png", amountOfEscOptions);
    mainMenuSelected = LoadTexture("data/EscMenu/MainMenuSelected.png", nothing);
    saveGame = LoadTexture("data/EscMenu/savegame.png", amountOfEscOptions);
    saveGameSelected = LoadTexture("data/EscMenu/SaveGameSelected.png", nothing);
    exitGame = LoadTexture("data/main-menu/ExitGame.png", amountOfEscOptions);
    exitGameSelected = LoadTexture("data/main-menu/ExitGameSelected.png", nothing);

    heartSprite.setTexture(*heart);

    save1Sprite.setTexture(*save1);
    save2Sprite.setTexture(*save2);
    save3Sprite.setTexture(*save3);
    save1SelectedSprite.setTexture(*save1Selected);
    save2SelectedSprite.setTexture(*save2Selected);
    save3SelectedSprite.setTexture(*save3Selected);

    resumeGameSprite.setTexture(*resumeGame);
    resumeGameSelectedSprite.setTexture(*resumeGameSelected);
    saveGameSprite.setTexture(*saveGame);
    saveGameSelectedSprite.setTexture(*saveGameSelected);
    mainMenuSprite.setTexture(*mainMenu);
    mainMenuSelectedSprite.setTexture(*mainMenuSelected);
    exitGameSprite.setTexture(*exitGame);
    exitGameSelectedSprite.setTexture(*exitGameSelected);

    Junglebackground1 = LoadTexture("data/Backgrounds/Jungle11.png", nothing);
    Cavebackground1 = LoadTexture("data/Backgrounds/Cave3.png", nothing);
    Treebackground1 = LoadTexture("data/Backgrounds/Tree.png", nothing);
    Hud = LoadTexture("data/Backgrounds/Hud.png", nothing);

    Cavebackground1Sprite.setTexture(*Cavebackground1);
    Cavebackground1Sprite.setPosition(0,600);

    Cavebackground2Sprite.setTexture(*Cavebackground1);
    Cavebackground2Sprite.setPosition(1200,600);

    Treebackground1Sprite.setTexture(*Treebackground1);
    Treebackground1Sprite.setPosition(3150,-10);

    Junglebackground1Sprite.setTexture(*Junglebackground1);
    Junglebackground1Sprite.setPosition(0,-300);

    HudSprite.setTexture(*Hud);
    HudSprite.setPosition(0,300);

}

/**********************************************
 * Loads image from file into texture
 * @param path: where file is placed
 * @param menuAmount: int counter to easy find
 *          the amount of options on a menu
 *          (ONLY USED FOR ESC & SAVE MENU)
 * @return returns the texture loaded
 *********************************************/
sf::Texture *TestApp::LoadTexture(std::string path, int &menuAmount)
{
    //temp texture
    sf::Texture *newTexture = new sf::Texture();
    //newTexture->loadFromFile(path);

    if(!newTexture->loadFromFile(path))
        std::cout << "Could not load image on path: " << path << std::endl;
    menuAmount++;
    return newTexture;
}
