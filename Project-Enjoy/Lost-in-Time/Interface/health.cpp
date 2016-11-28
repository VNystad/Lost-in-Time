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
    if (!greenHealthTexture.loadFromFile("data/HUD/Health/Lost-in-Time_health-bar-green.png"))
        std::cerr << "Could not load file: data/HUD/Health/Lost-in-Time_health-bar-green.png" << std::endl;
    if (!redHealthTexture.loadFromFile("data/HUD/Health/Lost-in-Time_health-bar-red.png"))
        std::cerr << "Could not load file: data/HUD/Health/Lost-in-Time_health-bar-red.png" << std::endl;
    if (!HealthBorderTexture.loadFromFile("data/HUD/Health/Lost-in-Time_health-bar-border.png"))
        std::cerr << "Could not load file: data/HUD/Health/Lost-in-Time_health-bar-border.png" << std::endl;

    greenHealthbar.setTexture(&greenHealthTexture);
    greenHealthbarFrame = new sf::IntRect(0,0,width,height);
    greenHealthbar.setTextureRect(*greenHealthbarFrame);

    redHealthbar.setTexture(&redHealthTexture);
    redHealthbarFrame = new sf::IntRect(0,0,width,height);
    redHealthbar.setTextureRect(*redHealthbarFrame);

    HealthbarBorder.setTexture(&HealthBorderTexture);
    HealthbarBorderFrame = new sf::IntRect(0,0,width,height);
    HealthbarBorder.setTextureRect(*HealthbarBorderFrame);

    greenHealthbar.setPosition(10,10);
    redHealthbar.setPosition(10,10);
    HealthbarBorder.setPosition(10,10);

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
    else
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
void Health::DrawMe()
{
    float fullWidth = 100;

    greenHealthbarFrame->left = (actuallifepoints / 100) * fullWidth;
    greenHealthbar.setTextureRect(*greenHealthbarFrame);
    redHealthbarFrame->left = (visiblelifepoints / 100) * fullWidth;
    redHealthbar.setTextureRect(*redHealthbarFrame);

    window.draw(greenHealthbar);
    window.draw(redHealthbar);
    window.draw(HealthbarBorder);
    window.display();
}
