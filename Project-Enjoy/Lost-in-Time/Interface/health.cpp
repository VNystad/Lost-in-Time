#include <iostream>
#include "health.h"

void Health::init()
{
    if (!greenHealth.loadFromFile("data/HUD/Health/Lost-in-Time_health-bar-green.png"))
        std::cerr << "Could not load file: data/HUD/Health/Lost-in-Time_health-bar-green.png" << std::endl;
    if (!redHealth.loadFromFile("data/HUD/Health/Lost-in-Time_health-bar-red.png"))
        std::cerr << "Could not load file: data/HUD/Health/Lost-in-Time_health-bar-red.png" << std::endl;
    if (!HealthBorder.loadFromFile("data/HUD/Health/Lost-in-Time_health-bar-border.png"))
        std::cerr << "Could not load file: data/HUD/Health/Lost-in-Time_health-bar-border.png" << std::endl;

    greenHealthbar.setTexture(&greenHealth);
    greenHealthbarFrame = new sf::IntRect(0,0,width,height);
    redHealthbar.setTexture(&redHealth);
    redHealthbarFrame = new sf::IntRect(0,0,width,height);
    HealthbarBorder.setTexture(&HealthBorder);
    HealthbarBorderFrame = new sf::IntRect(0,0,width,height);

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

void Health::ResetHealth()
{
    this->visiblelifepoints = this->actuallifepoints = originalhealth;
}

void Health::Hit(int damage)
{
    this->actuallifepoints -= damage;
}

// health:   0 => (0 / 100) * fullWidth   = 0    * fullWidth = 0
// health:  25 => (25 / 100) * fullWidth  = 0.25 * fullWidth
// health:  50 => (50 / 100) * fullWidth  = 0.5  * fullWidth
// health:  75 => (75 / 100) * fullWidth  = 0.75 * fullWidth
// health: 100 => (100 / 100) * fullWidth = 1    * fullWidth = fullWidth
void Health::DrawMe()
{
    float fullWidth = 100;
    //greenHealthbarFrame->left = (actuallifepoints / 100) * fullWidth;
    //redHealthbarFrame->left = (visiblelifepoints / 100) * fullWidth;
    window.draw(greenHealthbar);
    window.draw(redHealthbar);
    window.draw(HealthbarBorder);
}