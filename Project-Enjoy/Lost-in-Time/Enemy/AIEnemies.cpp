
#include "AIEnemies.h"
#include <iostream>


AIEnemies::AIEnemies(float x, float y, float patrol, sf::RenderWindow *window) : AI(x, y, window)
{
    this->OriginalX = x;
    this->OriginalY = y;
    this->positionX = this->OriginalX;
    this->positionY = this->OriginalY;
    this->SetMiniBoss(true);
    if(rand() % 100 < 20)
        this->SetMiniBoss(true);



    character = new sf::RectangleShape;
    character->setSize(sf::Vector2f(sizeWidth,sizeHeight));
    animation.init();
    health.init();

    if(this->GetMiniBoss() == true)
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
            e->SetEnraged(false);
        }
        if(e->GetMiniBoss() && rand() % 100 > 80)
            this->SetUpKey(true);

    }
    else
        e->SetMaxMoveSpeed(e->GetCalmSpeed());


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


