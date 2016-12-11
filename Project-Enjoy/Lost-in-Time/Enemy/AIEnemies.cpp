
#include <stdlib.h>
#include "AIEnemies.h"


AIEnemies::AIEnemies(float x, float y, float patrol, bool boss, sf::RenderWindow *window) : AI(x, y, window)
{
    this->OriginalX = x;
    this->OriginalY = y;
    this->positionX = this->OriginalX;
    this->positionY = this->OriginalY;
    if(rand() % 100 < 20)
        this->SetMiniBoss(true);



    character = new sf::RectangleShape;
    character->setSize(sf::Vector2f(sizeWidth,sizeHeight));
    animation.init();
    health.init();

    if(boss == true)
    {
        this->SetSizeHeight(49);
        this->SetSizeWidth(47);
        this->patrolleft = x - patrol;
        this->patrolright = x + patrol;
        animation.AIBossWalkRight(character);
        health.SetOriginalLifePoints(3000);
        health.SetActualLifePoints(3000);
        health.SetVisibleLifePoints(3000);
        this->SetRightKey(true);
        this->SetLeftKey(false);
        this->enragerange = 300;
        this->SetEnragedSpeed(190);
    }

    else if(this->GetMiniBoss() == true)
    {
        this->patrolleft = x - patrol;
        this->patrolright = x + patrol;
        animation.AIMiniBossWalkRight(character);
        health.SetOriginalLifePoints(300);
        health.SetActualLifePoints(300);
        health.SetVisibleLifePoints(300);
        this->SetRightKey(true);
        this->SetLeftKey(false);
        this->enragerange = 200;
        this->SetEnragedSpeed(250);
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
}

/**
 * This function is the basic AI behaviour. It will detect the player and move towards the player.
 * A miniboss also have a random chance of jumping when enraged. When they are not enraged, they will
 * patrol their territory.
 * @param e The AI character.
 * @param p The player character.
 */
void AIEnemies::MonkeyAI1(AIEnemies* e,PlayerTest* p)
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
void AIEnemies::MonkeyAI2(AIEnemies* e,PlayerTest* p)
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
        if (rand() % 100 > 60)
            this->SetUpKey(true);

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

void AIEnemies::GotHurt(AIEnemies *e, PlayerTest *p)
{
    if(!e->boss)
    {
        return;
    }
    if(rand() % 100 < 80)
    {
        if(p->GetLastMoveDirection() == 0)
        {
            e->SetMoveSpeedL(200);
            e->SetRightKey(false);
            e->SetLeftKey(true);
            e->SetUpKey(true);
        }
        else if(p->GetLastMoveDirection() == 1)
        {
            e->SetMoveSpeedR(200);
            e->SetRightKey(true);
            e->SetLeftKey(false);
            e->SetUpKey(true);
        }
    }
}