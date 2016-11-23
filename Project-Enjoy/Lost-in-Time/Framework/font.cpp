#include <iostream>
#include "font.h"

void Font::init()
{
    if (!font.loadFromFile("data/Character-Animation/Font/BitMapFont.TTF")) {
        std::cerr << "data/Character-Animation/Font/BitMapFont.TTF" << std::endl;
    }
}

sf::Font Font::GetFont()
{
    return font;
}

void Font::SetFont(sf::Font font)
{
    this->font = font;
}
