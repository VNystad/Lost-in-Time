#ifndef LOST_IN_TIME_FONT_H
#define LOST_IN_TIME_FONT_H

#include <SFML/Graphics/Font.hpp>

class Font {
public:
     void init();

    sf::Font GetFont();
    void SetFont(sf::Font font);

protected:
    sf::Font font;
};


#endif
