//
// Created by Fiskesuppe on 12.12.2016.
//

#ifndef LOST_IN_TIME_PRINCESS_H
#define LOST_IN_TIME_PRINCESS_H

#include "../Objects/playertest.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../Framework/config.h"
#include "../Framework/animation.h"
#include "../Interface/health.h"
#include "../Framework/Sounds.h"
#include <stdlib.h>

class PrincessObject {
public:
    PrincessObject(float x, float y, float patrol, const Config& config, sf::RenderWindow* window);

    void PrincessAI(PrincessObject* e, PlayerTest* p);
    sf::RectangleShape* character;
    Animation animation;

    Health health;

    /* ******************************************** */
    //                  FUNCTIONS                   //
    /* ******************************************** */

    void DrawMe();

    int GetSizeWidth() const { return sizeWidth; };
    int GetSizeHeight() const { return sizeHeight; };

    void SetPlayerHurt(int playerhurt) { this->playerhurt = playerhurt; };
    int GetPlayerHurt() const { return playerhurt; }

    void SetLeftKey(bool leftkey) { this->leftkey = leftkey; }
    bool GetLeftKey() const { return leftkey; }
    void SetRightKey(bool rightkey) { this->rightkey = rightkey; }
    bool GetRightKey() const { return rightkey; }
    void SetUpKey(bool upkey) { this->upkey = upkey; }
    bool GetUpKey() const { return upkey; }
    void SetEnraged(bool enraged) { this->enraged = enraged; }
    bool GetEnraged() const { return enraged; }

    int GetEnrageRange() const { return enragerange; }
    int GetEnrageDuration() const { return enrageduration; }

    void SetEnrageCountdown(int enragecountdown) { this->enragecountdown = enragecountdown; };
    int GetEnrageCountdown() const { return enragecountdown; }

    void SetEnragedSpeed(int enragedspeed) { this->enragedspeed = enragedspeed; };
    int GetEnragedSpeed() const { return enragedspeed; }

    void SetCalmSpeed(int calmspeed) { this->calmspeed = calmspeed; };
    int GetCalmSpeed() const { return calmspeed; }

    void SetPatrolLeft(int patrolleft) { this->patrolleft = patrolleft; };
    int GetPatrolLeft() const { return patrolleft; }

    void SetPatrolRight(int patrolright) { this->patrolright = patrolright; };
    int GetPatrolRight() const { return patrolright; }


    float GetPositionX();
    float GetPositionY();
    void SetPositionX(float x);
    void SetPositionY(float y);

    float GetOriginalX();
    float GetOriginalY();
    void SetOriginalX(float x);
    void SetOriginalY(float y);

    void Reset2OriginalX(float x);
    void Reset2OriginalY(float y);

    void PlayerDead();

    void PrincessAnimation();

    void PlayerSoundJump();
    void PlayerSoundHurt();

    //Checks if object is slowing down
    void SetSlowDownR(bool slowingdownright) { this->slowingdownright = slowingdownright; }
    void SetSlowDownL(bool slowingdownleft) { this->slowingdownleft = slowingdownleft; }
    bool GetSlowDownR() const { return slowingdownright; }
    bool GetSlowDownL() const { return slowingdownleft; }

    //Sets and gets movement speeds
    void SetMoveSpeedR(float movespeedright) { this->movespeedright = movespeedright; }
    void SetMoveSpeedL(float movespeedleft) { this->movespeedleft = movespeedleft; }
    float GetMoveSpeedR() const { return movespeedright; }
    float GetMoveSpeedL() const { return movespeedleft; }

    //Get for brakepowers
    float GetHorBrake() const { return brakehorslowdown; }
    float GetRegularBrake() const { return regularhorslowdown; }

    //Get max movement speed and movement power
    void SetMaxMoveSpeed(int maxmovespeed) { this->maxmovespeed = maxmovespeed; };
    float GetMaxMoveSpeed() const { return maxmovespeed; }
    float GetMovePower() const { return movepower; }

    //Checks for move direction, 0=Left, 1=Right, 2=Stopped
    void SetMovDir(int movedirection) { this->movedirection = movedirection; };
    int GetMovDir() const { return movedirection; }

    //Getters and Setters for last move direction
    void SetLastMoveDirection(int lastmovedirection) { this->lastmovedirection = lastmovedirection; }
    int GetLastMoveDirection() const { return lastmovedirection; }

    float GetGravity() const { return gravity; }

    sf::RectangleShape GetCharacter() const { return *character; }

    /***************************************
     * GRAVITY STUFF FUNCTIONS
    ***************************************/

    void SetJumpCheck(bool jumpcheck ) { this->jumpcheck = jumpcheck; }
    void SetApexCheck(bool apexcheck ) { this->apexcheck = apexcheck; }
    bool GetJumpCheck() const { return jumpcheck; }
    bool GetApexCheck() const { return apexcheck; }

    void SetFallSpeed(float fallspeed ) { this->fallspeed = fallspeed; }
    float GetFallSpeed() const { return fallspeed; }
    float GetMaxFallSpeed() const { return maxfallspeed; }

    void SetJumpSpeed(float jumpspeed ) { this->jumpspeed = jumpspeed; }
    float GetJumpSpeed() const { return jumpspeed; }
    float GetOrigJumpSpeed() const { return origjumpspeed; }

    void SetJumpPower(float jumppower ) { this->jumppower = jumppower; }
    float GetJumpPower() const { return jumppower; }

    void SetFallPower(float fallpower ) { this->fallpower = fallpower; }
    float GetFallPower() const { return fallpower; }


protected:
    const int sizeWidth = 34;
    const int sizeHeight = 50;


    /*
 * If player is being hurt, playerhurt will be:
 *  5 = Unharmed
 *  0 = From the left
 *  1 = From the right
 *  2 = From above
 *  3 = From beneath
 */
    int playerhurt = 5;



    /**********************
    * AI Control
    * *******************/

    bool leftkey = true;
    bool rightkey = false;
    bool upkey = false;


    /**********************
    * AI Behaviour
    * *******************/
    bool enraged = false;
    int enragerange = 100;
    int enrageduration = 1000;
    int enragecountdown = enrageduration;
    int enragedspeed = 120;
    int calmspeed = 100;

    int patrolleft;
    int patrolright;






    /**********************
     * Horisontal variables
    * *******************/
    //Horisontal braking speeds
    float brakehorslowdown = 2;
    float regularhorslowdown = 1.5;

    //Horisontal
    float maxmovespeed = 350;
    float movepower = 20;

    float movespeedleft = 0;
    float movespeedright = 0;

    // Different movement directions 0=Left, 1=Right, 2=Stopped
    int movedirection = 2;

    //Checks if player is slowing down
    bool slowingdownleft = false;
    bool slowingdownright = false;

    /**********************
     * Vertical variables
     * *******************/

    float gravity = 9;

    const int origjumpspeed = 15;
    float fallspeed;
    float maxfallspeed = 80;

    float jumppower = 500;
    float fallpower = 250;
    float jumpspeed = 0;


    //Checks for airborne and wether the jump or fall have reached its apex.
    bool jumpcheck = true;
    bool apexcheck = true;

    // Original Player Position
    float OriginalX;
    float OriginalY;

    //Player position
    float positionX = OriginalX;
    float positionY = OriginalY;

    int counter = 0; // Counter for animation
    int lastmovedirection = 2;

    const Config& config;
    sf::RenderWindow* window;

    Sounds* sound;
};


#endif //LOST_IN_TIME_PRINCESS_H
