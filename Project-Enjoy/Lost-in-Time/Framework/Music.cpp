#include <iostream>
#include <SFML/Audio.hpp>
#include "Music.h"

/************************************************************
 * Loads music files and plays them
 * using the function playMusic
 @param filename: where the music file is located
 Since we only have one music file we set the sound locally
 in the function
 ***********************************************************/

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