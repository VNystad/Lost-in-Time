
#include "AIEnemies.h"
#include <iostream>


AIEnemies::AIEnemies(float x, float y, float patrol, sf::RenderWindow *window) : AI(x, y, window)
{
    this->OriginalX = x;
    this->OriginalY = y;
    this->positionX = this->OriginalX;
    this->positionY = this->OriginalY;
    this->patrolleft = x - patrol;
    this->patrolright = x + patrol;
    character = new sf::RectangleShape;
    character->setSize(sf::Vector2f(sizeWidth,sizeHeight));

    animation.init();
    animation.AIWalkRight(character);

    health.init();
    health.SetOriginalLifePoints(100);
    health.SetActualLifePoints(100);
    health.SetVisibleLifePoints(100);
}


void AIEnemies::MonkeyAI1(AIEnemies* e,PlayerTest* p)
{
    if((p->GetPositionX() - e->GetPositionX() < this->enragerange && p->GetPositionX() - e->GetPositionX() > -this->enragerange) &&
       (p->GetPositionY() - e->GetPositionY() <  this->enragerange && p->GetPositionY() - e->GetPositionY() > -this->enragerange))
        e->SetEnraged(true);


    // Common enraged behaviour for all AI
    if(e->GetEnraged())
    {
        e->SetMaxMoveSpeed(e->GetEnragedSpeed());
        e->SetEnrageCountdown(e->GetEnrageCountdown()-1);
        if(e->GetEnrageCountdown() <= 0){
            e->SetEnrageCountdown(e->GetEnrageDuration());
            e->SetEnraged(false);
        }
    }
    else
        e->SetMaxMoveSpeed(e->GetCalmSpeed());


    // Specific enraged behaviour for creepy stalking minion
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


