
#include "AIEnemies.h"


AIEnemies::AIEnemies(int x, int y, int patrol, bool boss, sf::RenderWindow *window) : AI(x, y, patrol, window)
{
    this->positionX = x;
    this->positionY = y;
    this->OriginalX = x;
    this->OriginalY = y;

    character = new sf::RectangleShape;
    character->setSize(sf::Vector2f(sizeWidth,sizeHeight));
    animation.init();
    health.init();

    this->patrolleft = x - patrol;
    this->patrolright = x + patrol;

    if(boss)
    {
        sf::Vector2f scale = character->getScale();
        character->scale(scale.x*3.5, scale.y*2);

        this->sizeWidth = 55*3.5;
        this->sizeHeight = 44*2;
        animation.AIBossWalkRight(character);
        health.SetOriginalLifePoints(2000);
        health.SetActualLifePoints(2000);
        health.SetVisibleLifePoints(2000);
        this->rightkey = true;
        this->leftkey = false;
        this->enragerange = 150;
        this->calmspeed = 50;
        this->enragedspeed = 190;
        this->boss = true;
        this->miniboss = false;
    }

    else if(rand() % 100 <20)
    {
        this->miniboss = true;
        animation.AIMiniBossWalkRight(character);
        health.SetOriginalLifePoints(300);
        health.SetActualLifePoints(300);
        health.SetVisibleLifePoints(300);
        this->rightkey = true;
        this->leftkey = false;
        this->enragerange = 200;
        this->enragedspeed = 250;
    }
    else
    {

        animation.AIWalkLeft(character);
        health.SetOriginalLifePoints(100);
        health.SetActualLifePoints(100);
        health.SetVisibleLifePoints(100);
    }
    this->maxmovespeed = calmspeed;
}

/**
 * This function is the basic AI behaviour. It will detect the player and move towards the player.
 * A miniboss also have a random chance of jumping when enraged. When they are not enraged, they will
 * patrol their territory.
 * @param e The AI character.
 * @param p The player character.
 */
void AIEnemies::MonkeyAI1(AIEnemies* e,PlayerObject* p)
{
    if((p->GetPositionX() - e->GetPositionX() < this->enragerange && p->GetPositionX() - e->GetPositionX() > -this->enragerange) &&
       (p->GetPositionY() - e->GetPositionY() <  this->enragerange && p->GetPositionY() - e->GetPositionY() > -this->enragerange))
    {
        e->SetEnraged(true);
        e->SetEnrageCountdown(e->GetEnrageDuration());
    }



    // Common enraged behaviour for all AI
    if(e->GetEnraged())
    {
        e->SetMaxMoveSpeed(e->GetEnragedSpeed());
        e->SetEnrageCountdown(e->GetEnrageCountdown()-1);
        if(e->GetEnrageCountdown() <= 0){
            e->SetEnrageCountdown(e->GetEnrageDuration());
            e->SetMaxMoveSpeed(e->GetCalmSpeed());
            e->SetEnraged(false);
        }
        if(e->GetMiniBoss() && rand() % 100 > 80)
            this->SetUpKey(true);

    }


    // Specific enraged behaviour for creepy stalking minion, normal as of now.
    if(e->GetEnraged()) {
        //std::cout << "Super Angry" << std::endl;
        if (p->GetPositionX() < e->GetPositionX())
        {
            e->SetLeftKey(true);
            e->SetRightKey(false);
        }
        else if(p->GetPositionX() > e->GetPositionX())
        {
            e->SetRightKey(true);
            e->SetLeftKey(false);
        }

        else
        {
            e->SetLeftKey(false);
            e->SetRightKey(false);
        }

    }

        // Common patrol behaviour
    else
    {
        if(e->GetPositionX() > this->patrolright)
        {
            e->SetLeftKey(true);
            e->SetRightKey(false);
        }
        else if(e->GetPositionX() < this->patrolleft)
        {
            e->SetLeftKey(false);
            e->SetRightKey(true);
        }
    }
}


/**
 * Boss AI. It is based on the basic AI, but a bit thougher.
 * The boss is controlled by this function and AIEnemies::GotHurt().
 * MonkeyAI2 is a modified copy of MonkeyAI1, but will instead of
 * following the player character blindly, it will stop following
 * the player character if it reaches the end of it's patrol area.
 * @param e The AI character.
 * @param p The Player character.
 */
void AIEnemies::MonkeyAI2(AIEnemies* e,PlayerObject* p)
{
    if((p->GetPositionX() - e->GetPositionX() < this->enragerange && p->GetPositionX() - e->GetPositionX() > -this->enragerange) &&
       (p->GetPositionY() - e->GetPositionY() <  this->enragerange && p->GetPositionY() - e->GetPositionY() > -this->enragerange))
    {
        if(!(e->GetPositionX() > this->patrolright) && !(e->GetPositionX() < this->patrolleft))
        {
            e->SetEnraged(true);
            e->SetEnrageCountdown(e->GetEnrageDuration());
        }
    }


    // Specific enraged behaviour for creepy stalking minion, normal as of now.
    if(e->GetEnraged()) {
        //std::cout << "Super Angry" << std::endl;
        e->SetMaxMoveSpeed(e->GetEnragedSpeed());
        e->SetEnrageCountdown(e->GetEnrageCountdown() - 1);
        if (e->GetEnrageCountdown() <= 0) {
            e->SetEnrageCountdown(e->GetEnrageDuration());
            e->SetMaxMoveSpeed(e->GetCalmSpeed());
            e->SetEnraged(false);
        }
        //if (rand() % 100 > 1)
          //  this->SetUpKey(true);

        if(!(e->GetPositionX() > this->patrolright) && !(e->GetPositionX() < this->patrolleft))
        {
            if (p->GetPositionX() < e->GetPositionX())
            {
                e->SetLeftKey(true);
                e->SetRightKey(false);
            }
            else if(p->GetPositionX() > e->GetPositionX())
            {
                e->SetRightKey(true);
                e->SetLeftKey(false);
            }
        }
        else
        {
            e->SetEnrageCountdown(e->GetEnrageDuration());
            e->SetMaxMoveSpeed(e->GetCalmSpeed());
            e->SetEnraged(false);
        }
    }
        // Common patrol behaviour
    else
    {
        if(e->GetPositionX() > this->patrolright)
        {
            e->SetLeftKey(true);
            e->SetRightKey(false);
        }
        else if(e->GetPositionX() < this->patrolleft)
        {
            e->SetLeftKey(false);
            e->SetRightKey(true);
        }
    }
}

/**
 * GotHurt gets called whenever the player harms an enemy.
 * It will enable only the boss to perform two moves
 * individually or combined. Either jump back a little bit
 * or throw the player character really far away.
 * @param e AI calling the function
 * @param p The player character
 */
void AIEnemies::GotHurt(AIEnemies *e, PlayerObject *p)
{
    if(!e->boss)
    {
        return;
    }
    if((rand() % 100 < 80) && (!(e->GetPositionX() > (this->patrolright + 100)) && !(e->GetPositionX() < (this->patrolleft + 100))))
    {
        if(p->GetLastMoveDirection() == 1)
        {
            e->SetMoveSpeedL(250);
            e->SetRightKey(false);
            e->SetLeftKey(true);
            e->SetUpKey(true);
        }
        else if(p->GetLastMoveDirection() == 0)
        {
            e->SetMoveSpeedR(250);
            e->SetRightKey(true);
            e->SetLeftKey(false);
            e->SetUpKey(true);
        }
    }
    /****************************
     * BOSS THROW DEFENSIVE MOVE
     * This function makes the boss
     * perform a move that throws
     * the player away.
     ***********************'***/
    if((rand() % 3) + 1 == 3)
    {
        p->SetJumpCheck(true);
        p->SetApexCheck(false);
        p->SetJumpSpeed(100);
        if(e->GetMovDir() == 1)
            p->SetMoveSpeedR(1000);
        else
            p->SetMoveSpeedL(1000);
    }
}