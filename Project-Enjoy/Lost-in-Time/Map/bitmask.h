#ifndef LOST_IN_TIME_BITMASK_H
#define LOST_IN_TIME_BITMASK_H

#include <SFML/Graphics.hpp>

class BitmaskManager
{
public:
    ~BitmaskManager() {
        std::map<const sf::Texture*, sf::Uint8*>::const_iterator end = Bitmasks.end();
        for (std::map<const sf::Texture*, sf::Uint8*>::const_iterator iter = Bitmasks.begin(); iter!=end; iter++)
            delete [] iter->second;
    }

    sf::Uint8 GetPixel (const sf::Uint8* mask, const sf::Texture* tex, unsigned int x, unsigned int y) {
        if (x>tex->getSize().x||y>tex->getSize().y)
            return 0;

        return mask[x+y*tex->getSize().x];
    }

    sf::Uint8* GetMask (const sf::Texture* tex) {
        sf::Uint8* mask;
        std::map<const sf::Texture*, sf::Uint8*>::iterator pair = Bitmasks.find(tex);
        if (pair==Bitmasks.end())
        {
            sf::Image img = tex->copyToImage();
            mask = CreateMask (tex, img);
        }
        else
            mask = pair->second;

        return mask;
    }

    sf::Uint8* CreateMask (const sf::Texture* tex, const sf::Image& img) {
        sf::Uint8* mask = new sf::Uint8[tex->getSize().y*tex->getSize().x];

        for (unsigned int y = 0; y<tex->getSize().y; y++)
        {
            for (unsigned int x = 0; x<tex->getSize().x; x++)
                mask[x+y*tex->getSize().x] = img.getPixel(x,y).a;
        }

        Bitmasks.insert(std::pair<const sf::Texture*, sf::Uint8*>(tex,mask));

        return mask;
    }
private:
    std::map<const sf::Texture*, sf::Uint8*> Bitmasks;
};

#endif
