#include "Sounds.h"


/************************************************************
 * Loads sound files and plays them
 * using the function playSound
 @param filename: where the sound file is located
 @param volume: sets the volume of the sound that is played
 ***********************************************************/

bool Sounds::playSound(const std::string& filename, int volume) {

    if (!Buffer.loadFromFile("data/Sounds" + filename)) {
        std::cout << "Could not locate sound!";
        return false;
    }

    sound.setVolume(volume);
    sound.setBuffer(Buffer);
    sound.play();

    return true;
}

