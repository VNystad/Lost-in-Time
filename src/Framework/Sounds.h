#ifndef LOST_IN_TIME_SOUNDS_H
#define LOST_IN_TIME_SOUNDS_H

#include <iostream>
#include <SFML/Audio.hpp>

class Sounds {

public:

    sf::SoundBuffer Buffer;
    sf::Sound sound;

    bool playSound(const std::string& filename, int volume);


};

#endif //LOST_IN_TIME_SOUNDS_H