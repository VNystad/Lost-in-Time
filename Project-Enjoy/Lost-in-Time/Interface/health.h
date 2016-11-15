#ifndef LOST_IN_TIME_HEALTH_H
#define LOST_IN_TIME_HEALTH_H


class Health {
public:
    Health() { };

    float GetActualLifePoints();
    void SetActualLifePoints(int value);
    float GetVisibleLifePoints();
    void SetVisibleLifePoints(int value);
    float GetOriginalLifePoints();
    void SetOriginalLifePoints(int value);

    void ResetHealth();
    void Hit(int damage);
    void DrawMe();

    float GetWidth();
    void SetWidth(float width);
    float GetHeight();
    void SetHeight(float height);

protected:
    float actuallifepoints;
    float visiblelifepoints;
    float originalhealth;

    float width;
    float height;

    float fullwidth;
};


#endif
