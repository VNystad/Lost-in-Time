
#include "AIEnemies.h"


AIEnemies::AIEnemies(int x, int y, int patrol, bool boss, sf::RenderWindow *window) : AI(x, y, window)
{
    this->positionX = x;
    this->positionY = y;
    this->OriginalX = x;
    this->OriginalY = y;

    character = new sf::RectangleShape;
    character->setSize(sf::Vector2f(sizeWidth,sizeHeight));
    animation.init();
    health.init();

    if(boss)
    {
        sf::Vector2f scale = character->getScale();
        character->scale(scale.x*3.5, scale.y*2);

        this->sizeWidth = 55*3.5;
        this->sizeHeight = 44*2;
        this->patrolleft = x - patrol;
        this->patrolright = x + patrol;
        animation.AIBossWalkRight(character);
        health.SetOriginalLifePoints(1000);
        health.SetActualLifePoints(1000);
        health.SetVisibleLifePoints(1000);
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
        this->patrolleft = x - patrol;
        this->patrolright = x + patrol;
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
        this->patrolleft = x - patrol;
        this->patrolright = x + patrol;
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
 * A little more advanced AI. It is based on the basic AI, but will be a bit thougher.
 * This AI should be the biggest obstacle for the character.
 * @param e The AI character.
 * @param p The Player character.
 */
void AIEnemies::MonkeyAI2(AIEnemies* e,PlayerObject* p)
{
    if((p->GetPositionX() - e->GetPositionX() < this->enragerange && p->GetPositionX() - e->GetPositionX() > -this->enragerange) &&
       (p->GetPositionY() - e->GetPositionY() <  this->enragerange && p->GetPositionY() - e->GetPositionY() > -this->enragerange))
    {
        e->SetEnraged(true);
        e->SetEnrageCountdown(e->GetEnrageDuration());
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

void AIEnemies::GotHurt(AIEnemies *e, PlayerObject *p)
{
    if(!e->boss)
    {
        return;
    }
    if((rand() % 100 < 80) && (!(e->GetPositionX() > this->patrolright) && !(e->GetPositionX() < this->patrolleft)))
    {
        if(p->GetLastMoveDirection() == 1)
        {
            e->SetMoveSpeedL(700);
            e->SetRightKey(false);
            e->SetLeftKey(true);
            e->SetUpKey(true);
        }
        else if(p->GetLastMoveDirection() == 0)
        {
            e->SetMoveSpeedR(700);
            e->SetRightKey(true);
            e->SetLeftKey(false);
            e->SetUpKey(true);
        }
    }
    /****************************
     * BOSS THROW DEFENSIVE MOVE
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