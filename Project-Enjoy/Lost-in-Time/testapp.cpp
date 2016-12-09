#include <iostream>
#include <fstream>
#include "testapp.h"
#include "Framework/physics.h"

TestApp::TestApp(sf::RenderWindow& window, SavedObject so)
{
    if(!so.LoadFromSave())
    {
        this->config = config;
        this->window = &window;

        /*****************
         * Load in images
         ****************/
        LoadImages();

        /*************************************************
         * Making 2D array for collidable tiles
         ************************************************/
        collidableArray = new int*[ArraySize];
        collidableArray[0] = new int[ArraySize * ArraySize];
        for (int i = 1; i < ArraySize; i++)
        {
            collidableArray[i] = collidableArray[i - 1] + ArraySize;
        }

        /*************************************************
         * Load map information from JSON into object list
         ************************************************/
        if (!Map::load("data/map.json", objects, collidableArray))
        {
            std::cout << "Failed to load map data." << std::endl << std::endl;
        }

        /*****************************************
         * Set camera position in middle of screen
         ****************************************/

        sf::View view = window.getDefaultView();
        view.setSize(view.getSize().x, view.getSize().y);
        view.setCenter(view.getCenter().x, view.getCenter().y);
        window.setView(view);

        /********************|
         * Create the player
         *******************/
        p = new PlayerTest(180, 1, *config, &window);

        /***********************************
         * Creating AI
         * Using vector to keep track on AIs
         **********************************/
        AIVectorPointer->push_back(new AIEnemies(730, 671, 300, &window));
        AIVectorPointer->push_back(new AIEnemies(354, 1230, 200, &window));
        AIVectorPointer->push_back(new AIEnemies(1950, 1220, 150, &window));
        AIVectorPointer->push_back(new AIEnemies(2340, 250, 260, &window));
        //AIVectorPointer->push_back(new AIEnemies(3774, 1270, 100, *config, &window));
        AIVectorPointer->push_back(new AIEnemies(1530, 510, 400, &window));

        /********************
         * Create the clock
         * Used to find delta
         *******************/
        clock = new sf::Clock;
        clock->restart();

        //TEST
        currentView = new sf::View;


        /********************
         * Play Music
         *******************/
        music = new Music();
        music->music.setLoop(true);
        music->playMusic("/Jungle Theme 2.ogg");

        /***********************************
         * Creating Timer and text for timer
         **********************************/
        sf::Font font;
        if(!font.loadFromFile("data/TNRfont.ttf"))
            std::cout << "Could not load font from directory 'data/font.ttf'" << std::endl;
        timer = new sf::Clock();
        timerInText = new sf::Text;
        timerInText->setCharacterSize(50);
        //timerInText->setFont(font);
        timerInText->setStyle(sf::Text::Bold);
        timerInText->setColor(sf::Color::Red);
        timerInText->setOutlineColor(sf::Color::Green);
        timerInText->setOutlineThickness(2);
        timerInText->setString("Hi");

    }
        /****************************************************************************
         *                   LOADED FROM SAVE
         ***************************************************************************/
    else
    {
        this->config = config;
        this->window = &window;

        /*****************
         * Load in images
         ****************/
        LoadImages();

        /*************************************************
         * Making 2D array for collidable tiles
         ************************************************/
        collidableArray = new int*[ArraySize];
        collidableArray[0] = new int[ArraySize * ArraySize];
        for (int i = 1; i < ArraySize; i++)
        {
            collidableArray[i] = collidableArray[i - 1] + ArraySize;
        }

        /*************************************************
         * Load map information from JSON into object list
         ************************************************/
        if (!Map::load("data/map.json", objects, collidableArray))
        {
            std::cout << "Failed to load map data." << std::endl << std::endl;
        }

        /*****************************************
         * Set camera position in middle of screen
         ****************************************/

        sf::View view = window.getDefaultView();
        view.setSize(view.getSize().x, view.getSize().y);
        view.setCenter(view.getCenter().x, view.getCenter().y);
        window.setView(view);

        /********************|
         * Create the player
         *******************/
        p = new PlayerTest(so.GetPlayerX(), so.GetPlayerY(), *config, &window);
        p->health.SetActualLifePoints(so.GetPlayerHP());


        /***********************************
         * Creating AI
         * Using vector to keep track on AIs
         **********************************/
        for(int i = 0; i<so.GetAIVectorPointer()->size(); i++)
        {
            int x = so.GetAIVectorPointer()->at(i)->GetPositionX();
            int y = so.GetAIVectorPointer()->at(i)->GetPositionY();
            int patrol = so.GetAIVectorPointer()->at(i)->GetPositionX()-so.GetAIVectorPointer()->at(i)->GetPatrolLeft();
            AIVectorPointer->push_back(new AIEnemies(x, y, patrol, &window));
        }
        /*AIVectorPointer->push_back(new AIEnemies(630, 660, 300, &window));
        AIVectorPointer->push_back(new AIEnemies(354, 1230, 200, &window));
        AIVectorPointer->push_back(new AIEnemies(1950, 1220, 150, &window));
        AIVectorPointer->push_back(new AIEnemies(2340, 250, 260, &window));
        //AIVectorPointer->push_back(new AIEnemies(3774, 1270, 100, &window));
        AIVectorPointer->push_back(new AIEnemies(1530, 510, 400, &window));*/

        /********************
         * Create the clock
         * Used to find delta
         *******************/
        clock = new sf::Clock;
        clock->restart();

        //TEST
        currentView = new sf::View;


        /********************
         * Play Music
         *******************/
        music = new Music();
        music->music.setLoop(true);
        music->playMusic("/Jungle Theme 2.ogg");

        /***********************************
         * Creating Timer and text for timer
         **********************************/
        sf::Font font;
        if(!font.loadFromFile("data/TNRfont.ttf"))
            std::cout << "Could not load font from directory 'data/font.ttf'" << std::endl;
        timer = new sf::Clock();
        timerInText = new sf::Text;
        timerInText->setCharacterSize(50);
        //timerInText->setFont(font);
        timerInText->setStyle(sf::Text::Bold);
        timerInText->setColor(sf::Color::Red);
        timerInText->setOutlineColor(sf::Color::Green);
        timerInText->setOutlineThickness(2);
        timerInText->setString("Hi");

        penaltyTime = so.GetTimeElapsed();
    }
}

bool TestApp::Tick(Machine& machine)
{
    sf::Event event;
    float delta = clock->restart().asSeconds();

    /************************
     * Gets time elapsed and
     * place it in text form
     ***********************/
    int timeelapsed = timer->getElapsedTime().asSeconds() + penaltyTime - EscMenuTime;
    std::string tempForTime = std::to_string(timeelapsed);
    timerInText->setString(tempForTime);
    // Positioning the timerInText on upper right corner of player
    timerInText->setPosition(p->GetPositionX() + 50,p->GetPositionY() - 50);

    // Get events from OS
    while (window->pollEvent(event))
    {
        // Close the window if the user clicks the x button
        if (event.type == sf::Event::Closed)
        {
            delete[] collidableArray[0];
            delete[] collidableArray;
            window->close();
            machine.SetRunning(false);
        }
    }

    /*****************************************************************
     *        KEYBOARD EVENTS ( but not for physical actions )
     ****************************************************************/

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        int tempTime = timer->getElapsedTime().asSeconds();
        EscMenu(machine);
        EscMenuTime = EscMenuTime + timer->getElapsedTime().asSeconds() - tempTime;
    }

        /********************************
         * If player press P Pause game
         * If player press R Resume game
         *******************************/
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        music->music.pause();
        while(!sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            clock->restart();
        }
        music->music.play();
    }
        // For testing only, prints out player position
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        std::cout << p->GetPositionX() << " " << p->GetPositionY() << std::endl;

        // When player presses G, player character is damaged. For testing purposes
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && p->health.GetActualLifePoints() > 0)
        p->health.Hit(5);

        // When player presses H, player character is healed. For testing purposes
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && p->health.GetActualLifePoints() < 100)
        p->health.Healed(5);

        // If player press M, mute music
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
    {
        music->music.pause();
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::T))
        std::cout << timeelapsed << std::endl;

    /* If player hits the bottom of map,
     * the player's lifepoint is reduced to 0 and player death function is called */
    if (p->GetPositionY() >= 2500)
    {


        penaltyTime = penaltyTime + 20;
        p->health.DeathHandle();
        p->PlayerDead();
        timer->restart();
    }

    if (p->health.Dead())
    {
        penaltyTime = penaltyTime + 20;
        p->health.DeathHandle();
        p->PlayerDead();
        timer->restart();
    }


    p->PlayerAnimation();

    /***********************
     * Handles player and AI
     * movements
     **********************/
    Move(delta);

    window->clear(sf::Color::Black);


    // Process and render each object
    for (Object *object : objects)
    {
        //object->process(deltaTime);
        object->draw(*window);
    }

    p->DrawMe();
    p->health.DrawMe();
    window->draw(*timerInText);
    timerInText->~Drawable();


    AIHandler(delta);

    window->display();

    /*****************************************
     * Set camera to follow player position
     ****************************************/

    if (p->GetPositionX() >= 512)
    {
        if (p->GetPositionY() <= 1290)
        {
            sf::View view2 = window->getDefaultView();
            view2.setCenter(p->GetPositionX(), p->GetPositionY());
            *currentView = view2;
            window->setView(view2);
        }
        else if(p->GetPositionY() >= 1290)
        {
            sf::View view2 = window->getDefaultView();
            view2.setCenter(p->GetPositionX(), 1290);
            *currentView = view2;
            window->setView(view2);
        }
    }
    else if (p->GetPositionX() <=  512)
    {
        if (p->GetPositionY() <= 1290)
        {
            sf::View view3 = window->getDefaultView();
            view3.setCenter(512, p->GetPositionY());
            *currentView = view3;
            window->setView(view3);
        }
        else if (p->GetPositionY() >= 1290)
        {
            sf::View view3 = window->getDefaultView();
            view3.setCenter(512, 1290);
            *currentView = view3;
            window->setView(view3);
        }
    }
    else if(p->GetPositionX() >= 3650)
    {
        if(p->GetPositionY() <=1500 )
        {
            sf::View view2 = window->getDefaultView();
            view2.setCenter(3650, p->GetPositionY());
            *currentView = view2;
            window->setView(view2);
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
    Physics::Movement(p, collidableArray, delta);
    Physics::Gravity(p, collidableArray, delta);
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
        if (AIVectorPointer->at(i)->GetPositionY() >= 2500)
        {
            AIVectorPointer->at(i)->health.Hit(AIVectorPointer->at(i)->health.GetOriginalLifePoints());
        }

        if (AIVectorPointer->at(i)->health.GetActualLifePoints() <= 0)//Dead())
        {
            AIVectorPointer->at(i)->health.DeathHandle();
            //AIVectorPointer->at(i)->Death();
            AIVectorPointer->erase(AIVectorPointer->begin() + i);
        }
        else
        {
            AIVectorPointer->at(i)->AnimationAI();
            AIVectorPointer->at(i)->DrawMe();
            AIVectorPointer->at(i)->MonkeyAI1(AIVectorPointer->at(i), p);
            Physics::AIMovement(AIVectorPointer->at(i), p, AIVectorPointer, i, collidableArray, delta);
            Physics::AIGravity(AIVectorPointer->at(i), collidableArray, delta);
        }
    }
}
/**
 * Menu for pressing Esc
 * Options:
 * ResumeGame: Resumes the game
 * SaveGame: Opens new window with saves
 * MainMenu: Returns to mainmenu
 * ExitGame: Exits the game
 * @param machine so we can handle the machine
 *          if you go back to mainmenu og exit game
 */
void TestApp::EscMenu(Machine& machine)
{
    music->music.pause();
    // Show up a menu

    int selected = menuSelected("EscMenu");

    std::cout << "Selected: " << selected << std::endl;

    // Resume game
    if(selected == 1)
    {
        music->music.play();
        return;
    }

        // Save game
    else if(selected == 2)
    {
        selected = menuSelected("SaveGameMenu");
        SaveGame(selected);
    }

    else if(selected == 3)
    {
        machine.SetState(Machine::StateId::MAINMENU);
        return;
    }

        // Exit game
    else if(selected == 4)
    {
        delete[] collidableArray[0];
        delete[] collidableArray;
        window->close();
        machine.SetRunning(false);
    }
    clock->restart();
    music->music.play();
}

bool TestApp::SaveGame(int selectedSave)
{
    std::string name;
    std::cout << "Please type name" << std::endl;
    std::getline(std::cin , name);
    int enemyCount = (AIVector.size());
    enemyCount = AIVectorPointer->size();


    std::ofstream savefile;
    if(selectedSave == 1)
        savefile.open("SaveFiles/save1.txt");
    else if(selectedSave == 2)
        savefile.open("SaveFiles/save2.txt");
    else if(selectedSave == 3)
        savefile.open("SaveFiles/save3.txt");

    savefile << name << std::endl;
    savefile << p->health.GetActualLifePoints() << std::endl;
    savefile << p->GetPositionX() << std::endl;
    savefile << p->GetPositionY() << std::endl;
    savefile << timer->getElapsedTime().asSeconds() + penaltyTime;
    while(enemyCount != 0)
    {
        //int positionX = AIVector->at(enemyCount-1)->GetOriginalX();
        int positionX = AIVectorPointer->at(enemyCount-1)->GetPositionX();
        int positionY = AIVectorPointer->at(enemyCount-1)->GetPositionY();
        int patrol = AIVectorPointer->at(enemyCount-1)->GetPositionX() - AIVectorPointer->at(enemyCount-1)->GetPatrolRight();
        savefile << std::endl << positionX;
        savefile << std::endl << positionY;
        savefile << std::endl << patrol;
        enemyCount--;
    }
    savefile.close();
    return true;
}

int TestApp::menuSelected(std::string menu)
{
    // Go until Return is not pressed, to prevent program going through several "Menuselected" functions on 1 return press
    while(sf::Keyboard::isKeyPressed(sf::Keyboard::Return));
    int amountOfChoices = 0;
    int choice = 1;
    int MenuPositionX = p->GetPositionX() -200;
    int MenuPositionY = p->GetPositionY() - 200;

    while(1){
        if(!menu.compare("EscMenu"))
        {

            resumeGameSprite.setPosition(MenuPositionX, MenuPositionY);
            saveGameSprite.setPosition(MenuPositionX, MenuPositionY + 100);
            mainMenuSprite.setPosition(MenuPositionX, MenuPositionY + 200);
            exitGameSprite.setPosition(MenuPositionX, MenuPositionY + 300);
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
            window->clear(sf::Color::Black);
            save1Sprite.setPosition(MenuPositionX, MenuPositionY);
            save2Sprite.setPosition(MenuPositionX, MenuPositionY + 100);
            save3Sprite.setPosition(MenuPositionX, MenuPositionY + 200);
            // Load images for savegame menu
            window->draw(save1Sprite);
            window->draw(save2Sprite);
            window->draw(save3Sprite);
            amountOfChoices = amountOfSaves;
        }


        if(!keyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            choice++;
            if (choice > amountOfChoices)
                choice = 1;
            keyPressed = true;
            std::cout << choice << std::endl;
        }
        else if(!keyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            choice--;
            if (choice <= 0)
                choice = amountOfChoices;
            keyPressed = true;
            std::cout << choice << std::endl;
        }
        else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            keyPressed = false;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            return choice;

        selectedSprite.setPosition(p->GetPositionX() + 250, p->GetPositionY() - 300 + choice*100);
        window->draw(selectedSprite);
        window->display();
        if(amountOfChoices == amountOfEscOptions)
        {
            // Handle esc options
        }
        else if (amountOfChoices == amountOfSaves)
        {
            // Handle save options
        }
    }
}

void TestApp::LoadImages()
{
    int nothing;
    /*
     * TIL VETLE!!!
     * du gjør nesten akkurat som på skolen, men legger inn ", nothing" bak pathen
     * background1 = LoadTexture("pathen", nothing)
     */
    save1 = LoadTexture("data/loadgame/save1.png", amountOfSaves);
    save2 = LoadTexture("data/loadgame/save2.png", amountOfSaves);
    save3 = LoadTexture("data/loadgame/save3.png", amountOfSaves);

    selected = LoadTexture("data/EscMenu/selected.png", nothing);

    resumeGame = LoadTexture("data/EscMenu/resume.png", amountOfEscOptions);
    mainMenu = LoadTexture("data/EscMenu/mainmenu.png", amountOfEscOptions);
    saveGame = LoadTexture("data/EscMenu/savegame.png", amountOfEscOptions);
    exitGame = LoadTexture("data/EscMenu/exitgame.png", amountOfEscOptions);

    save1Sprite.setTexture(*save1);
    save2Sprite.setTexture(*save2);
    save3Sprite.setTexture(*save3);

    selectedSprite.setTexture(*selected);
    resumeGameSprite.setTexture(*resumeGame);
    saveGameSprite.setTexture(*saveGame);
    mainMenuSprite.setTexture(*mainMenu);
    exitGameSprite.setTexture(*exitGame);

}

sf::Texture *TestApp::LoadTexture(std::string path, int &menuAmount)
{
    //temp texture
    sf::Texture *newTexture = new sf::Texture();
    //newTexture->loadFromFile(path);

    if(!newTexture->loadFromFile(path))
    {
        std::cout << "Could not load image on path: " << path << std::endl;
    }
    menuAmount++;
    return newTexture;
}
