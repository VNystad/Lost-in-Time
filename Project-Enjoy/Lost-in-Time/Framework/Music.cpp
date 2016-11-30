//
// Created by Vetle Norman on 30/11/16.
//

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

    music.play();

    music.setLoop(true);

    return true;
}
