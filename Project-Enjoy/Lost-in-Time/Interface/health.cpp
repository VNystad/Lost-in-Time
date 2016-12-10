#include <iostream>
#include "health.h"

/**
 * Initialize health class.
 * Load in textures from files.
 * Set the textures to the different healthbars and border.
 * Decide how much of the healthbar is visible with IntRect.
 * Set position for the healthbar
 */
void Health::init()
{
    greenHealthTexture = new sf::Texture;
    redHealthTexture = new sf::Texture;
    HealthBorderTexture = new sf::Texture;
    if (!greenHealthTexture->loadFromFile("data/HUD/Health/Lost-in-Time_health-bar-green.png"))
        std::cerr << "Could not load file: data/HUD/Health/Lost-in-Time_health-bar-green.png" << std::endl;
    if (!redHealthTexture->loadFromFile("data/HUD/Health/Lost-in-Time_health-bar-red.png"))
        std::cerr << "Could not load file: data/HUD/Health/Lost-in-Time_health-bar-red.png" << std::endl;
    if (!HealthBorderTexture->loadFromFile("data/HUD/Health/Lost-in-Time_health-bar-border.png"))
        std::cerr << "Could not load file: data/HUD/Health/Lost-in-Time_health-bar-border.png" << std::endl;

    greenHealthFrame = new sf::IntRect(0,0,width,height);
    greenHealthSprite = new sf::Sprite;
    greenHealthSprite->setTexture(*greenHealthTexture);

    redHealthFrame = new sf::IntRect(0,0,width,height);
    redHealthSprite = new sf::Sprite;
    redHealthSprite->setTexture(*redHealthTexture);

    HealthBorderSprite = new sf::Sprite;
    HealthBorderSprite->setTexture(*HealthBorderTexture);

}

void Health::SetPosition(int x, int y)
{
    greenHealthSprite->setPosition(x, y);
    redHealthSprite->setPosition(x, y);
    HealthBorderSprite->setPosition(x, y);
    this->x = x;
    this->y = y;
}

float Health::GetOriginalLifePoints()
{
    return originalhealth;
}

void Health::SetOriginalLifePoints(int value)
{
    this->originalhealth = originalhealth;
}

float Health::GetActualLifePoints()
{
    return actuallifepoints;
}

void Health::SetActualLifePoints(int value)
{
    this->actuallifepoints = value;
}

float Health::GetVisibleLifePoints()
{
    return visiblelifepoints;
}

void Health::SetVisibleLifePoints(int value)
{
    this->visiblelifepoints = value;
}

/**
 * Update lifepoint variable.
 * If the actual life points are less than the visible life point,
 * the actual life point is decreased by 1 until they are equal.
 * If we go over, set visiblelifepoints equal to actuallifepoints.
 */
void Health::UpdateHealth()
{
    if (actuallifepoints < visiblelifepoints)
        visiblelifepoints -= 1;
    else if (actuallifepoints != visiblelifepoints)
    {
        // Make sure we don't go over
        visiblelifepoints = actuallifepoints;
    }

/*    if (actuallifepoints > visiblelifepoints)
        visiblelifepoints += 1;
    else if (actuallifepoints != visiblelifepoints)
    {
        // Make sure we don't go over
        visiblelifepoints = actuallifepoints;
    }
*/
}

/**
 * Handle death scenario
 * Set both lifepoints to 0
 * Call to UpdateHealth() function,
 * then to ResetHealth() function.
 */
void Health::DeathHandle()
{
    actuallifepoints = 0;
    visiblelifepoints = 0;
    UpdateHealth();
    ResetHealth();
}

/**
 * Check if the player is dead.
 * @return true, if actuallifepoints is less or equal than 0
 *         false, if actuallifepoints is more than 0
 */
bool Health::Dead()
{
    if (actuallifepoints <= 0)
        return true;

    return false;
}

/**
 * Set visiblelifepoints and actuallifepoints back to their originalvalue.
 * Then call to the UpdateHealth() function.
 */
void Health::ResetHealth()
{
    this->visiblelifepoints = this->actuallifepoints = this->originalhealth;
    std::cout << "actual: " << actuallifepoints << " visible: " << visiblelifepoints << std::endl;
    UpdateHealth();
}

/**
 * Decrease the health by a certain amount.
 * @param damage, amount the health is decreased by.
 * Then call to the UpdateHealth() function.
 */
void Health::Hit(int damage)
{
    this->actuallifepoints -= damage;
    std::cout << this->actuallifepoints << std::endl;
    UpdateHealth();
}

/**
 * Increase the health by a certain amount.
 * @param health, amount the health is increased by.
 * Then call to the UpdateHeatlh() function.
 */
void Health::Healed(int health)
{
    this->actuallifepoints += health;
    std::cout << this->actuallifepoints << std::endl;
    UpdateHealth();
}

// health:   0 => (0 / 100) * fullWidth   = 0    * fullWidth = 0
// health:  25 => (25 / 100) * fullWidth  = 0.25 * fullWidth
// health:  50 => (50 / 100) * fullWidth  = 0.5  * fullWidth
// health:  75 => (75 / 100) * fullWidth  = 0.75 * fullWidth
// health: 100 => (100 / 100) * fullWidth = 1    * fullWidth = fullWidth
void Health::DrawMe(sf::RenderWindow& window)
{
    int fullWidth = 100;

    greenHealthFrame->width = (actuallifepoints / 100) * fullWidth;
    greenHealthSprite->setTextureRect(*greenHealthFrame);
    redHealthFrame->width = (visiblelifepoints / 100) * fullWidth;
    redHealthSprite->setTextureRect(*redHealthFrame);

    //window.draw(*greenHealthbar);
    window.draw(*HealthBorderSprite);
    window.draw(*redHealthSprite);
    window.draw(*greenHealthSprite);
}
