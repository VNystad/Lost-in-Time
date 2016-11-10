#ifndef LOST_IN_TIME_CONFIG_H
#define LOST_IN_TIME_CONFIG_H

class Config
{
public:
    int GetScreenWidth() const { return screenWidth; }
    int GetScreenHeight() const { return screenHeight; }

protected:
    // Screen dimensions
    const int screenWidth = 1024;
    const int screenHeight = 576;
};

#endif
