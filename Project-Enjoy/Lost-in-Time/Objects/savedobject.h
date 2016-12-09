#ifndef LOST_IN_TIME_LOADEDSAVE_H
#define LOST_IN_TIME_LOADEDSAVE_H


#include "../Enemy/AIEnemies.h"

class SavedObject {

public:
    SavedObject(){};

    bool LoadFromSave() const {return savedObject; }

    void LoadPlayer(std::string name, int hp, int x, int y, int timeElapsed);
    void LoadAI(int enemyX, int enemyY, int patrole, sf::RenderWindow& window);

    std::string GetPlayerName() const {return playerName; }
    int GetPlayerHP() const {return playerHP; }
    int GetPlayerX() const {return playerX; }
    int GetPlayerY() const {return playerY; }
    int GetTimeElapsed() const {return timeElapsed; }
    std::vector<AIEnemies*>* GetAIVectorPointer() const {return AIVectorPointer; }


protected:
    bool savedObject = false;

    std::string playerName;
    int playerHP;
    int playerX;
    int playerY;

    int timeElapsed;

    std::vector<AIEnemies*>* AIVectorPointer = &AIVector;
    std::vector<AIEnemies*> AIVector;

};


#endif //LOST_IN_TIME_LOADEDSAVE_H
