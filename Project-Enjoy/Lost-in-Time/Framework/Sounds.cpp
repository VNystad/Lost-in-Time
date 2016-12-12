#include "Sounds.h"

bool Sounds::playSound(const std::string& filename, int volume) {

    if (!Buffer.loadFromFile("data/Sounds" + filename))
    {
        std::cout << "Could not locate sound!";
        return false;
    }

    sound.setVolume(volume);
    sound.setBuffer(Buffer);
    sound.play();


    return true;

}
