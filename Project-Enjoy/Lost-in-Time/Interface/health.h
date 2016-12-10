#ifndef LOST_IN_TIME_HEALTH_H
#define LOST_IN_TIME_HEALTH_H


#include <SFML/Graphics.hpp>
#include "../Framework/config.h"

class Health {
public:
    Health(){ this->config = config; };
    void init();

    float GetActualLifePoints();
    void SetActualLifePoints(int value);
    float GetVisibleLifePoints();
    void SetVisibleLifePoints(int value);
    float GetOriginalLifePoints();
    void SetOriginalLifePoints(int value);

    void SetPosition(int x, int y);

    void DeathHandle();
    bool Dead();
    void UpdateHealth();
    void ResetHealth();
    void Hit(int damage);
    void Healed(int health);
    void DrawMe(sf::RenderWindow& window);

    float GetWidth() { return width; }
    void SetWidth(float width) { this->width = width; }
    float GetHeight() { return height; }
    void SetHeight(float height) { this->height = height; }

    /*sf::Texture GetgreenHealthTexture() { return greenHealthTexture; }
    void SetgreenHealthTexture(sf::Texture texture) { this->greenHealthTexture = texture; }
    sf::Texture GetredHealthTexture() { return redHealthTexture; }
    void SetredHealthTexture(sf::Texture texture) { this->redHealthTexture = texture; }
    sf::Texture GetHealthBorderTexture() { return HealthBorderTexture; }
    void SetHealthBorderTexture(sf::Texture texture) { this->HealthBorderTexture = texture; }
*/
/*
    sf::RectangleShape GetgreenHealthbar() { return greenHealthbar; }
    void SetgreenHealthbar(sf::RectangleShape healthbar) { this->greenHealthbar = healthbar; }
    sf::RectangleShape GetredHealthbar() { return redHealthbar; }
    void SetredHealthbar(sf::RectangleShape healthbar) { this->redHealthbar = healthbar; }*/

    sf::IntRect GetgreenHealthbarFrame() { return *greenHealthFrame; }
    void SetgreenHealthbar(sf::IntRect *frame) { this->greenHealthFrame = frame; }
    sf::IntRect GetredHealthbarFrame() { return *redHealthFrame; }
    void SetredHealthbar(sf::IntRect *frame) { this->redHealthFrame = frame; }

protected:
    float actuallifepoints = 100;
    float visiblelifepoints = 100;
    float originalhealth = 100;
    int x;
    int y;

    sf::Texture* greenHealthTexture;
    sf::Sprite* greenHealthSprite;
    sf::IntRect *greenHealthFrame;

    sf::Texture* redHealthTexture;
    sf::Sprite* redHealthSprite;
    sf::IntRect *redHealthFrame;

    sf::Texture* HealthBorderTexture;
    sf::Sprite* HealthBorderSprite;

    float width = 100;
    float height = 20;

    const Config* config;
};


#endif
