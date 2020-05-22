#include <sstream>
#include "deathscreen.h"

void Deathscreen::init()
{
    std::stringstream ss;
    ss << "Oh deer, you died!"
       << "(      )\n"
               "     ))    ((\n"
               "    //      \\\\\n"
               "   | \\\\____// |\n"
               "  \\~/ ~    ~\\/~~/\n"
               "   (|    _/o  ~~\n"
               "    /  /     ,|\n"
               "   (~~~)__.-\\ |\n"
               "    ``~~    | |\n"
               "     |      | |\n"
               "     |        |\n"
               "    /          \\\n"
               "   `\\          /'\n"
               "     `\\_    _/'\n"
               "        ~~~~"
       << "Press 'Enter' to continue.." << std::endl << std::endl;
    deathscreen.setFont(font.GetFont());
    deathscreen.setCharacterSize(25);
    deathscreen.setPosition(320,480);
    deathscreen.setColor(sf::Color::Red);
    deathscreen.setString(ss.str());
}

void Deathscreen::Display()
{
    window.draw(deathscreen);
}

sf::Text Deathscreen::GetDeathScreen()
{
    return deathscreen;
}

void Deathscreen::SetDeathScreen(sf::Text deathscreen)
{
    this->deathscreen = deathscreen;
}
