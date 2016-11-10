#ifndef LOST_IN_TIME_PLAYER_H
#define LOST_IN_TIME_PLAYER_H


#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../Framework/config.h"
class PlayerTest
{
public:
    PlayerTest(float x, float y, const Config& config, sf::RenderWindow* window);

    void DrawMe();

    int GetSize() const { return size; };

    float GetPositionX();
    float GetPositionY();
    void SetPosition(float x, float y);
    void SetPositionX(float x);
    void SetPositionY(float y);


    //Checks object collision cd
    void SetVertiCollCD(float verticalcollisioncooldown) { this->verticalcollisioncooldown = verticalcollisioncooldown; }
    void SetHoriCollCD(float horisontalcollisioncooldown) { this->horisontalcollisioncooldown = horisontalcollisioncooldown; }
    float GetVertiCollCD() const { return verticalcollisioncooldown; }
    float GetHoriCollCD() const { return horisontalcollisioncooldown; }

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



protected:

    const int size = 50;

    //Timer for collision, it basically allows the object to land, but not move through the roof
    float verticalcollisioncooldown = 0;
    float horisontalcollisioncooldown = 0;

    //Horisontal braking speeds
    float brakehorslowdown = 2;
    float regularhorslowdown = 1.5;


    //Horisontal
    const float maxmovespeed = 400;

    /**********************
     * Vertical variables
     * *******************/

    float gravity = 9;

    const int origjumpspeed = 15;
    float fallspeed;
    float maxfallspeed = 800;

    float jumppower = 250;
    float jumpspeed = 15;




    float movepower = 50;

    float movespeedleft = 0;
    float movespeedright = 0;

    // Different movement directions 0=Left, 1=Right, 2=Stopped
    int movedirection = 2;

    //Checks if player is slowing down
    bool slowingdownleft = false;
    bool slowingdownright = false;

    //Checks for airborne and wether the jump or fall have reached its apex.
    bool jumpcheck = true;
    bool apexcheck = true;

    //Player position
    float positionX = 180;
    float positionY = 250;

    const Config& config;
    sf::RectangleShape* character;
    sf::RenderWindow* window;
    sf::Texture texture;
};


#endif //LOST_IN_TIME_PLAYER_H