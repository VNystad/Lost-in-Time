#include <iostream>
#include <SFML/Audio.hpp>
#include "Music.h"

bool Music::playMusic(const std::string& filename) {

    if (!music.openFromFile("data/Music" + filename)) {
        std::cout << "Could not locate file!";
        return false;
    }

    if (Music::music.getStatus() == sf::Music::Playing) {

        return false;
    }
    music.setVolume(60);
    music.play();

    return true;
}