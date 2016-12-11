#include <iostream>
#include "savedobject.h"

void SavedObject::LoadPlayer(std::string name, int hp, int x, int y, int timeElapsed)
{
    this->savedObject = true;
    this->playerName = name;
    this->playerHP = hp;
    this->playerX = x;
    this->playerY = y;
    this->timeElapsed = timeElapsed;
    std::cout << "Created SavedObject" << std::endl;
}

void SavedObject::LoadAI(int enemyX, int enemyY, int patrol, boss, sf::RenderWindow& window)
{
    AIVectorPointer->push_back(new AIEnemies(enemyX, enemyY, patrol, boss, &window));
}
