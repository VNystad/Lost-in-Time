#include "Sounds.h"

bool Sounds::playSound(const std::string& filename) {

    if (!Buffer.loadFromFile("data/Sounds" + filename))
    {
        std::cout << "Could not locate sound!";
        return false;
    }


    sound.setBuffer(Buffer);
    sound.play();


    return true;

}