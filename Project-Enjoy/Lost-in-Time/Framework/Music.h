//
// Created by Vetle Norman on 30/11/16.
//

#ifndef LOST_IN_TIME_MUSIC_H
#define LOST_IN_TIME_MUSIC_H

#include <iostream>
#include <SFML/Audio.hpp>

class Music {

public:

    sf::Music music;

    bool playMusic(const std::string& filename);

};


#endif //LOST_IN_TIME_MUSIC_H
