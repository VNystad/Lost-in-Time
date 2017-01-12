#ifndef LOST_IN_TIME_PLAYER_H
#define LOST_IN_TIME_PLAYER_H


#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../Framework/config.h"
#include "../Framework/animation.h"
#include "../Interface/health.h"
#include "../Framework/Sounds.h"
#include <stdlib.h>

class PlayerObject
{
public:
    PlayerObject(float x, float y, sf::RenderWindow* window);

    sf::RectangleShape* character;
    Animation animation;

    Health health;

    /* ******************************************** */
    //                  FUNCTIONS                   //
    /* ******************************************** */

    bool GotWeap() const { return weapon; };
    void setWeap(bool weapon){ this->weapon = weapon; }

    void DrawMe();

    int GetSizeWidth() const { return sizeWidth; };
    int GetSizeHeight() const { return sizeHeight; };

    void SetPlayerHurt(int playerhurt) { this->playerhurt = playerhurt; };
    int GetPlayerHurt() const { return playerhurt; }

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

    void PlayerCutsceneAnimationLeft(float delta);
    void PlayerCutsceneAnimationRight(float delta);
    void PlayerAnimation(float delta, bool attack);

    void PlayerSoundJump();
    void PlayerSoundHurt();
    void PlayerSoundEnemyLanded();

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
    bool weapon = false;
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
     * Horisontal variables
    * *******************/
    //Horisontal braking speeds
    float brakehorslowdown = 2;
    float regularhorslowdown = 1.5;

    //Horisontal
    const float maxmovespeed = 350;
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

    float counter = 0; // Counter for animation
    int lastmovedirection = 2;

    sf::RenderWindow* window;

    Sounds* sound;
};


#endif